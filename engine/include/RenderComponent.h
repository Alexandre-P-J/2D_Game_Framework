#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include "Camera.h"

class RenderComponent {
		struct RenderTask {
			const bool usesRotation;
        	SDL_Texture* const texture;
            const SDL_Rect srcrect;
            const SDL_Rect dstrect;
			const int z;
            const double angle = 0;
			const SDL_Point center = {0,0};
			const SDL_RendererFlip flip = SDL_FLIP_NONE;
			RenderTask(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect,
				const int z, const double angle, const SDL_Point center, const SDL_RendererFlip flip);
			RenderTask(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect, const int z);
		};

		std::vector<std::queue<RenderTask>> PQueue; //not a regular Pqueue
		unsigned int TaskNum = 0;
		std::unordered_map<std::string, SDL_Texture* const> Textures;
		SDL_Renderer* const Renderer;
		SDL_Window* const Window;
		Camera* Viewport;

		inline std::pair<int,int> getPositionOnScreen(const Position Local);

	public:
		RenderComponent(SDL_Renderer* Renderer, SDL_Window* Window, int maxPriorities);
		~RenderComponent();

		SDL_Texture* GetTexture(const std::string& Path);

		void ScheduleDraw(unsigned int priority, SDL_Texture* texture,
		  const SDL_Rect srcrect, const Position Pos, const int w, const int h,
		  const double angle, const SDL_Point angleCenter, const SDL_RendererFlip flip);

		void ScheduleDraw(unsigned int priority, SDL_Texture* texture,
		  const SDL_Rect srcrect, const Position Pos, const int w, const int h);

		void ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  		  const SDL_Rect srcrect, SDL_Rect onScreenInfo, const int z);

		void Draw();

		Camera* const GetViewport();

		std::pair<int,int> getWindowSize();

		unsigned int getTaskNum();
};
