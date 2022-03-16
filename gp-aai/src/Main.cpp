#include <SDL.h>
#include "game/World.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "tests/Vector2DTests.hpp"

using std::thread, std::cout, std::endl;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

void display_loop(World* world) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                world->render(renderer);


                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    } else if(event.type == SDL_MOUSEBUTTONDOWN) {
                        SDL_MouseButtonEvent ev = event.button;
                        world->event(WorldEvent::mouseClick, Vector2D(ev.x, ev.y));
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}

void logic_loop(World* world, bool* running) {
    while(*running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        world->update(1);
    }
}

int main(int argc, char* argv[])  {
    // Run tests first
    run_Vector2D_tests();

    World* world = new World(WINDOW_WIDTH, WINDOW_HEIGHT);
    bool running = true;

    // We're haning out references since this all isn't threadsafe anyways
    thread display_thread = thread(display_loop, world);
    thread logic_thread = thread(logic_loop, world, &running);

    // Wait for display thread to finish
    display_thread.join();
    running = false;
    logic_thread.join();
    return 0;
}
