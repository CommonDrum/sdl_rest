#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window* window;
SDL_Renderer* renderer;

bool initialize_window(void){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    return false;
  }

  window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);

  if (!window){
    return false;
  }

  renderer= SDL_CreateRenderer(window, -1, 0);
  if (!renderer){
    return false;
  }

  return true;
}

int main{
  
  initialize_window();

  return 0;
}
