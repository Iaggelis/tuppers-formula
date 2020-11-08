#include "./tupper_visual.h"

Field field = {0};

int main(int argc, char *argv[]) {

  scc(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window *const window =
      scp(SDL_CreateWindow("Tupper's self-referential formula", 0, 0,
                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE));

  SDL_Renderer *const renderer =
      scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

  scc(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));

  tupper_loop(&field);
  int quit = 0;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: {
        quit = 1;
      } break;
      }
    }

    SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR));
    scc(SDL_RenderClear(renderer));

    render_field_grid(renderer);
    render_field(renderer, &field);

    SDL_RenderPresent(renderer);
    SDL_Delay(300);
  }

  SDL_Quit();

  return 0;
}
