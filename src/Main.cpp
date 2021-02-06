#define SDL_MAIN_HANDLED "SDL_MAIN"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <exception>
#include <array>

//directorios

void init();
SDL_Texture* surface_loader(SDL_Renderer* renderer, const std::string &filename);
void game_loop();
void handle_events(SDL_Event &events, bool &is_active);
void update();
void render();
void clear();

uint32_t WIDHT{720};
uint32_t HEIGHT{480};

SDL_Window* window{};
SDL_Renderer* renderer{};
SDL_Texture* sprite{};
SDL_Rect sprite_rect{};

int main() {
    init();
    game_loop();

    return EXIT_SUCCESS;
}

void init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error{"ERROR SDL_Init()"};

    if(IMG_Init(IMG_INIT_PNG) < 0)
        throw std::runtime_error{"ERROR IMG_Init()"};

    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!window) std::runtime_error{"ERROR SDL_CreateWindow()"};

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) std::runtime_error{"ERROR SDL_CreateRenderer()"};

    sprite = surface_loader(renderer, "icon.png");

    sprite_rect.x = 200;
	sprite_rect.y = 200;
	sprite_rect.w = 128;
	sprite_rect.h = 128;
}

SDL_Texture* surface_loader(SDL_Renderer* renderer, const std::string &filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    SDL_Texture* texture_output = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture_output;
}

void game_loop() {
    bool is_active{true};
    SDL_Event events{};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while(is_active) {
        handle_events(events, is_active);
        update();
        render();
    }

    clear();
}

void handle_events(SDL_Event &events, bool &is_active) {
    while(SDL_PollEvent(&events))
        if(events.type == SDL_QUIT) is_active = false;
}

void update() {
    const uint8_t* keys{SDL_GetKeyboardState(nullptr)};

    if(keys[SDL_SCANCODE_A]) sprite_rect.x -= 4;
    if(keys[SDL_SCANCODE_D]) sprite_rect.x += 4;
    if(keys[SDL_SCANCODE_S]) sprite_rect.y += 4;
    if(keys[SDL_SCANCODE_W]) sprite_rect.y -= 4;
}

void render() {
    SDL_RenderClear(renderer);

    //BEGIN RENDER

    SDL_RenderCopy(renderer, sprite, nullptr, &sprite_rect);

    //END RENDER

    SDL_RenderPresent(renderer);
}

void clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}