#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720
SDL_Window *window;
SDL_Renderer *renderer;
int up, down, left, right;
void doInit(){
    SDL_INIT_EVERYTHING;

    window = SDL_CreateWindow("Luu",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,0);
    SDL_GetRenderDrawColor(renderer,0,0,0,0);

}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename);

	return texture;
}
void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			right = 1;
		}
	}
}
void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
		up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			right = 0;
		}
	}
}
void doInput()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
            case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
			default:
				break;
		}
	}
}
struct character{
    int x;
	int y;
	SDL_Texture *texture;
};

int main(int argc,char*argv[]){
    character player;
    doInit();
    player.x = 200;
    player.y = 200;
    player.texture = loadTexture("SurfaceBl1.png");
    while(1){
        doInput();
        if (up)
		{
            player.y -= 4;
		}

		if (down)
		{
            player.y += 4;
		}

		if (left)
		{
			player.x -= 4;
		}

		if (right)
		{
			player.x += 4;
		}
        blit(player.texture, player.x, player.y);

        SDL_RenderPresent(renderer);SDL_RenderClear(renderer);

        SDL_Delay(50);
    }
}
