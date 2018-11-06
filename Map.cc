#include "Map.h"
#include <rapidxml/rapidxml.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "RenderScheduler.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace rapidxml;

int sibling_count(xml_node<>* pNode) {
	int counter = 0;
	while (pNode) {
		++counter;
		pNode = pNode->next_sibling();
	}
	return counter;
}

int stosi(const std::string& str) {//string to signed integer
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

Map::Map(const std::string& MapFile, RenderScheduler* const RS) : RS(RS) {
	Reload(MapFile);
}

void Map::Reload(const std::string& MapFile) {
	//Dealocate (Reduce mem usage peak)
	Levels = std::vector<Level>();

	//Loading MapFile
	xml_document<> doc;
	std::ifstream file(MapFile);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	xml_node<>* pRoot = doc.first_node();
	xml_node<>* pNode;


	std::string TexPath = (pRoot->first_node("tileset")->first_node("image")->first_attribute("source"))->value();
	MapSpriteSheet = RS->GetTexture(TexPath);


	//Updating variables
	minLevel = 0;
	pNode = pRoot->first_node("layer");
	std::vector<xml_node<>*> InfoLayers;
	std::vector<xml_node<>*> SpriteLayers;
	while (pNode) {
		//separating Info and Sprite layers
		xml_attribute<> *pAttr = pNode->first_attribute("name");
		std::string str = pAttr->value();
		if (str.find("Behaviour") != std::string::npos)
			InfoLayers.push_back(pNode);
		else { //str shall contain only integers
			SpriteLayers.push_back(pNode);
			int LName = stosi(str);
			if (LName < minLevel)
				minLevel = LName;
		}
		pNode = pNode->next_sibling();
	}

	//Updating Levels vector
	std::vector<Level> tmp(SpriteLayers.size());
	Levels = std::move(tmp);

	for (int i = 0; i < SpriteLayers.size(); ++i) {
		pNode = SpriteLayers[i];
		int width = std::stoi((pNode->first_attribute("width"))->value());
		int height = std::stoi((pNode->first_attribute("height"))->value());
		int size = width*height;
		pNode = pNode->first_node("data")->first_node("tile");
		std::vector<int> Tiles(size, 0);
		for(int j = 0; j < size; ++j) {
			if (pNode->first_attribute("gid"))
				Tiles[j] = std::stoi(pNode->first_attribute()->value());
			pNode = pNode->next_sibling();
		}
		int index = stosi(SpriteLayers[i]->first_attribute("name")->value()) - minLevel;
		Levels[index].Tiles = std::move(Tiles);
		Levels[index].Size = std::make_pair(width, height);
	}
}

SDL_Texture* Map::getMapSpriteSheet() {
	return MapSpriteSheet;
}

Level* Map::getLevel(const int Level) {
	return &Levels[Level-minLevel]; //vectors do not accept negative index
}

void Map::idToSprite(int id, SDL_Texture*& texture, SDL_Rect& srcrect) {
	if (id < 1)
		id = 1;
	texture = MapSpriteSheet; //MODIFY THIS FOR MULTIPLE TEXTURE SUPPORT
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	int x0 = ((id-1)%w)*32;
	int y0 = ((id-1)/w)*32;
	srcrect = {x0, y0, x0+32, y0+32};
}

void Map::Update(const Camera& cam) {
	auto Height = (cam.Get()).VisionHeight;
	auto Width = (cam.Get()).VisionWidth;
	auto x = std::get<0>((cam.Get()).P);
	auto y = std::get<1>((cam.Get()).P);
	auto z = std::get<2>((cam.Get()).P);

	for (int i = x; i < Width; i += 32) {
		int id = (Levels[0].Tiles)[i/32];
		std::cout << Width << std::endl;
		int w, h;
		SDL_Texture* texture;
		SDL_Rect srcrect;
		idToSprite(id, texture, srcrect);

		SDL_Rect dstrect = { i, 0, i+32, 32 };
		RS->ScheduleDraw(0, texture, srcrect, dstrect);
	}

	/*
	for (int i = 0; i < 5; ++i) {
		SDL_Rect srcrect = { 0, 0, 32*i, 32 };
		SDL_Rect dstrect = { 0, 0, 32*i, 32 };
		RS->ScheduleDraw(0, MapSpriteSheet, srcrect, dstrect);
	}
	*/
}
