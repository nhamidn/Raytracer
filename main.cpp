#include "raytracer.h"

//Function that inisialize the SDL instance
int init_instance(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}

	instance->window = SDL_CreateWindow("RayTracer Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0);
	if (instance->window == NULL)
	{
		SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

//Entrypoint of the program
int main(int argc, char* argv[]) {

	SDL_Instance instance;
	Scene scene;

	//A file_name if necessary fto be passed to the program
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input_filename>" << std::endl;
		return (1);
	}

	const std::string filename = argv[1];

	if (parse_file(filename, scene) != 0)
		return (1);

	if (init_instance(&instance) != 0)
		return (1);

	raytracer(&instance, scene);
	SDL_RenderPresent(instance.renderer);
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();

	return (0);
}

