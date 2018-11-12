#include "Map.h"
#include <rapidxml/rapidxml.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <tuple>
#include <algorithm>
#include "EngineUtils.h"

using namespace rapidxml;

int sibling_count(xml_node<>* pNode) {
	int counter = 0;
	while (pNode) {
		++counter;
		pNode = pNode->next_sibling();
	}
	return counter;
}

inline int stosi(const std::string& str) {//string to signed integer
	int i = 0;
	char sign = 1;
	for (const auto c : str) {
		if (c == '-' && !i)
			sign = sign * -1;
		else if ((c < '0' || c > '9'))
			break;
		else
			i = i*10+c-'0';
	}
	return i*sign;
}


template<typename T> int PromiscuousBinSearch(const std::vector<T>& V, const T& X) { //returns index even if element not in the vector
	int low = 0;
	int high = V.size()-1;
	while(low <= high) {
		int mid = (low+high)/2;
		if (V[mid] > X)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

Map::Map() {}

Map::Map(const std::string& MapFile) {
	Reload(MapFile);
}


void Map::Reload(const std::string& MapFile) {
	// Free up map from memory
	Levels.clear();
	Levels.shrink_to_fit();

	//Load Map File
	xml_document<> doc;
	std::ifstream file(MapFile);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	xml_node<>* pRoot = doc.first_node();
	auto RS = getRenderScheduler();

	//Parsing Tileset (Texture->tile info) : UBoundTexture vector
	xml_node<>* pNode0 = pRoot->first_node("tileset");
	std::vector<std::tuple<int,SDL_Texture*,int,int>> LBoundTexture; //interval lower bound, Tex. ptr, tile W, tile H
	while(pNode0) {
		int firstgid = atoi(pNode0->first_attribute("firstgid")->value());
		int tileWidth = atoi(pNode0->first_attribute("tilewidth")->value());
		int tileHeight = atoi(pNode0->first_attribute("tileheight")->value());
		std::string Path = pNode0->first_node("image")->first_attribute("source")->value();

		SDL_Texture* texture = nullptr;
		if (Path.find("Behaviour") == std::string::npos) //If texture has Behaviour in path, omit
			texture = RS->GetTexture(Path);
		LBoundTexture.push_back(std::make_tuple(firstgid, texture, tileWidth, tileHeight));
		pNode0 = pNode0->next_sibling("tileset");
	}
	sort(LBoundTexture.begin(), LBoundTexture.end(), [](const auto& lhs, const auto& rhs)
		{return std::get<0>(lhs) < std::get<0>(rhs);});

	//Parsing Layers Step1: Filtering types of layers
	pNode0 = pRoot->first_node("layer");
	std::vector<xml_node<>*> TileTexures;
	std::vector<xml_node<>*> TileBehaviours;
	std::vector<xml_node<>*> TileObjects;
	while(pNode0) {
		std::string name = pNode0->first_attribute("name")->value();
		if (name.find("Behaviour") != std::string::npos)
			TileBehaviours.push_back(pNode0);
		else if (name.find("Object") != std::string::npos)
			TileObjects.push_back(pNode0);
		else if (name.find_first_not_of("-0123456789") == std::string::npos) {
			TileTexures.push_back(pNode0);
			minLevel = std::min(minLevel, stosi(name));
		}
		pNode0 = pNode0->next_sibling("layer");
	}

	//Parsing Layers Step2.1: writing Texture and SrcRect in Levels vector
	std::vector<Level> tmp(TileTexures.size());
	Levels = std::move(tmp);
	for (auto & element : TileTexures) {
		int index = stosi(element->first_attribute("name")->value()) - minLevel;
		int width = std::stoi(element->first_attribute("width")->value());
		int height = std::stoi(element->first_attribute("height")->value());
		Levels[index].Width = width;
		Levels[index].Height = height;
		std::vector<MapTile> Tiles(width*height);
		pNode0 = element->first_node("data")->first_node("tile");
		for (int i = 0; pNode0; ++i) {
			auto attr = pNode0->first_attribute("gid");
			if (attr) {
				int gid = stosi(attr->value());
				int low = 0;
				int high = LBoundTexture.size()-1;
				while(low <= high) { //get texture pointer from gid
					int mid = (low+high)/2;
					if (std::get<0>(LBoundTexture[mid]) > gid)
						high = mid - 1;
					else
						low = mid + 1;
				}
				int lbpos = std::max(0, low-1);
				Tiles[i].Texture = std::get<1>(LBoundTexture[lbpos]);
				int pos_tex = gid - std::get<0>(LBoundTexture[lbpos]);
				int tileWidth = std::get<2>(LBoundTexture[lbpos]);
				int tileHeight = std::get<3>(LBoundTexture[lbpos]);
				int columns;
				SDL_QueryTexture(Tiles[i].Texture, nullptr, nullptr, &columns, nullptr);
				columns = columns / tileWidth; // columns%tileWidth == 0
				int x0 = tileWidth*(pos_tex%columns);
				int y0 = tileHeight*(pos_tex/columns);
				Tiles[i].SrcRect = {x0, y0, tileWidth, tileHeight};
			}
			pNode0 = pNode0->next_sibling("tile");
		}
		Levels[index].Tiles = std::move(Tiles);
	}

	//Parsing Layers Step2.2: writing Behaviour in Levels vector
	for (auto & element : TileBehaviours) {
		int index = stosi(element->first_attribute("name")->value()) - minLevel; //stosi shall omit non numeric and non '-'
		pNode0 = element->first_node("data")->first_node("tile");
		for (int i = 0; pNode0; ++i) {
			auto attr = pNode0->first_attribute("gid");
			if (attr) {
				int gid = stosi(attr->value());
				int low = 0;
				int high = LBoundTexture.size()-1;
				while(low <= high) { //get texture pointer from gid
					int mid = (low+high)/2;
					if (std::get<0>(LBoundTexture[mid]) > gid)
						high = mid - 1;
					else
						low = mid + 1;
				}
				int lbpos = std::max(0, low-1);
				Levels[index].Tiles[i].Behaviour = gid - std::get<0>(LBoundTexture[lbpos]);
			}
			pNode0 = pNode0->next_sibling("tile");
		}
	}

	//Parsing Objects
	//WIP

}




Level* Map::getLevel(const int Level) {
	return &Levels[Level-minLevel]; //vectors do not accept negative index
}


void Map::Update(const Camera& cam) {
	auto RS = getRenderScheduler();
	float Zoom = (cam.Get()).Zoom;
	//Tile
	int Tdim = 32*Zoom; //EVERY MAP TILE SHALL BE 32X32 IN TEXTURE!!!
	// Camera:
	int HorizontalPx = (cam.Get()).HorizontalPx + Tdim;
	int VerticalPx = (cam.Get()).VerticalPx + Tdim;
	int x = std::get<0>((cam.Get()).P)*Zoom; //Position from top left
	int y = std::get<1>((cam.Get()).P)*Zoom;
	int Level = std::get<2>((cam.Get()).P) - minLevel;
	//Map
	int MapWidth = Levels[Level].Width;
	//Screen:
	auto Res = RS->getWindowSize();
	int ScreenWidth = Res.first;
	int ScreenHeight = Res.second;

	for (int i = y/Tdim; i < (y+VerticalPx)/Tdim; ++i)
		for (int j = x/Tdim; j < (x+HorizontalPx)/Tdim; ++j) {
			int index = j + i*MapWidth;
			SDL_Rect dstrect = {(j*Tdim)-x, (i*Tdim)-i, Tdim, Tdim};
			RS->ScheduleDraw(1, Levels[Level].Tiles[index].Texture, Levels[Level].Tiles[index].SrcRect, dstrect);
		}
}
/*
void Map::Update(const Camera& cam) {
	auto Width = (cam.Get()).HorizontalUnits; //in world sizes
	auto x = std::get<0>((cam.Get()).P); //Position from top left
	auto y = std::get<1>((cam.Get()).P);
	auto z = std::get<2>((cam.Get()).P) - minLevel;
	auto Res = RS->getWindowSize();
	int StileSize = Res.first / Width + 1;
	int Height = Res.second / StileSize;
	for (int i = y; i < StileSize*Height-y; i += StileSize)
		for (int j = x; j < StileSize*Width-x; j += StileSize) {
			SDL_Rect dstrect = {j, i, StileSize, StileSize};
			int index = (j/StileSize) + i;
			RS->ScheduleDraw(1, Levels[z].Tiles[index].Texture, Levels[z].Tiles[index].SrcRect, dstrect);
			std::cout << j << ' ' << i << ' ' << StileSize << ' ' << StileSize << std::endl;
		}
	//while(1);

}
*/
