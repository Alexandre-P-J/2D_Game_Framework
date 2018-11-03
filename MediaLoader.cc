#include "MediaLoader.h"
#include <iostream>

MediaLoader::MediaLoader(SDL_Renderer* Renderer) : pRenderer(Renderer){}

MediaLoader::~MediaLoader() {
	auto it = Textures.begin();
	while (it != Textures.end()) {
		SDL_DestroyTexture(it->second);
		++it;
	}
}

SDL_Texture* MediaLoader::GetTexture(const std::string& Path) {
	auto search = Textures.find(Path);
	if (search != Textures.end()) //found
		return search->second;
	else {
		SDL_Texture* texture = IMG_LoadTexture(pRenderer, Path.c_str());
		Textures.insert({Path, texture});
		std::cout << "HI" << std::endl;
		return texture;
	}
}
