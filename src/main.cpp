#include <SDL.h>
#include <array>
#include <cstdint>

constexpr int GB_W = 160, GB_H = 144, SCALE = 4;

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("gbemu",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        GB_W * SCALE, GB_H * SCALE, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GB_W, GB_H);

    // The 4 shades of the original DMG screen
    const uint32_t palette[4] = {0xFFE0F8D0, 0xFF88C070, 0xFF346856, 0xFF081820};

    std::array<uint32_t, GB_W * GB_H> framebuffer{};
    for (int y = 0; y < GB_H; y++)
        for (int x = 0; x < GB_W; x++)
            framebuffer[y * GB_W + x] = palette[((x / 8) + (y / 8)) % 4];

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = false;

        SDL_UpdateTexture(texture, nullptr, framebuffer.data(), GB_W * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}