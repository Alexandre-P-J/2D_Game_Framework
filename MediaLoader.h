#include "SDL2/SDL_image.h"
#include <unordered_map>

class MediaLoader {
		std::unordered_map<std::string, SDL_Texture* const> Textures;
		SDL_Renderer* const pRenderer;
	public:
		MediaLoader(SDL_Renderer* Renderer);
		~MediaLoader();
		SDL_Texture* GetTexture(const std::string& Path);
};
