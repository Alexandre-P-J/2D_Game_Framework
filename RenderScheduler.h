#pragma once
#include "SDL2/SDL_image.h"
#include <unordered_map>
#include <vector>
#include <queue>

class RenderScheduler {
		struct RenderTask {

			const bool usesRotation;
        	SDL_Texture* const texture;
            const SDL_Rect srcrect;
            const SDL_Rect dstrect;
            const double angle = 0;
			const SDL_Point* center;
			const SDL_RendererFlip flip = SDL_FLIP_NONE;

			RenderTask(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect,
				const double angle, const SDL_Point* center, const SDL_RendererFlip flip);

			RenderTask(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect);
		};

		std::vector<std::queue<RenderTask>> PQueue; //not a regular Pqueue
		unsigned int TaskNum = 0;
		std::unordered_map<std::string, SDL_Texture* const> Textures;
		SDL_Renderer* const Renderer;

	public:
		RenderScheduler(SDL_Renderer* Renderer, int maxPriorities);

		~RenderScheduler();

		SDL_Texture* GetTexture(const std::string& Path);

		void ScheduleDraw(unsigned int priority, SDL_Texture* texture,
		  const SDL_Rect srcrect, const SDL_Rect dstrect, const double angle,
		  const SDL_Point* center, const SDL_RendererFlip flip);

		void ScheduleDraw(unsigned int priority, SDL_Texture* texture,
		  const SDL_Rect srcrect, const SDL_Rect dstrect);

		void Draw();

		unsigned int getTaskNum();
};
