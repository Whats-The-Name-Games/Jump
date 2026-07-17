#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <random>
#include <vector>
#include "Character.hpp"
#include "Platform.hpp"
#include "PoolAllocator.hpp"

/*
 *  Code by: Luke Deany and Michael Khan
 *  Artwork by: Ted Freakdogshow
 */

constexpr int WIDTH = 720;
constexpr int HEIGHT = 1280;

typedef struct AppState {
    PoolAllocator<Platform> allocator {20};
    std::vector<Platform*> platforms {};
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    Character *player{};
    std::random_device randomSeed;
    std::mt19937 rng {randomSeed()};
    std::uniform_real_distribution<float> positionDistribution {0, WIDTH - 100};
    std::uniform_real_distribution<float> heightDistribution {-100, 100};
    Uint64 score {0};
    Uint64 lastSpawned {0};
    Uint64 PreviousTick{0};
    bool is_running{};
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_SetAppMetadata("Jig is Up", "0.1", "com.whatsthenamegames.jigisup");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *state{new AppState()};
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("Jig is Up", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &state->window,
                                     &state->renderer)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(state->renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    state->player = new Character(state->renderer);

    SDL_SetRenderVSync(state->renderer, 1);

    state->platforms.reserve(20);

    Platform* pPlatform = state->allocator.construct(500, 900);
    Platform* pPlatform2 = state->allocator.construct(200, -100);
    Platform* pPlatform3 = state->allocator.construct(300, 400);
    state->platforms.push_back(pPlatform);
    state->platforms.push_back(pPlatform2);
    state->platforms.push_back(pPlatform3);


    return SDL_APP_CONTINUE;
}

// Every frame? Maybe? Something like that
SDL_AppResult SDL_AppIterate(void *appstate) {

    const auto state{static_cast<AppState *>(appstate)};

    const Uint64 currentTick{SDL_GetTicks()};

    const Uint64 delta = currentTick - state->PreviousTick;

    state->PreviousTick = currentTick;

    // Set fill color to background color
    SDL_SetRenderDrawColor(state->renderer, 173, 216, 230, SDL_ALPHA_OPAQUE_FLOAT);

    // Render all "clear" pixels on screen w/ bg color
    SDL_RenderClear(state->renderer);

    std::vector<BoundingBox*> boxes {};

    SDL_SetRenderDrawColor(state->renderer, 255 ,0 ,0, SDL_ALPHA_OPAQUE_FLOAT);

    state->player->Render(state->renderer);

    for (const auto platform : state->platforms) {
        boxes.push_back(&platform->getBoundingBox());

        platform->Render(state->renderer);
    }

    const Uint64 scoreDelta = state->player->VelocityTick(delta, boxes);
    state->score += scoreDelta;

    const Uint64 scoreDifference = state->score - state->lastSpawned;

    const Uint64 lowerScoreNormalized = state->lastSpawned - (state->lastSpawned % 300);
    const Uint64 upperScoreNormalized = state->score - (state->score % 300);

    const Uint64 amountToSpawn = (upperScoreNormalized - lowerScoreNormalized) / 300;

    Uint64 lastSpawnPosition = lowerScoreNormalized;

    for (int i = 0; i < amountToSpawn; i++) {
        lastSpawnPosition = lastSpawnPosition + 300;

        state->platforms.push_back(state->allocator.construct( state->positionDistribution(state->rng) , -10.f + static_cast<float>(state->score - lastSpawnPosition) + state->heightDistribution(state->rng)));
    }

    state->lastSpawned = state->score;

    // Only update all platforms if our score difference is not 0
    if (scoreDelta != 0) {
        for (const auto platform: state->platforms) {
            platform->MoveDown(scoreDelta);

            // Deallocate box if moved out
            if (platform->getBoundingBox().getRect()->y > HEIGHT) {
                state->allocator.destroy(platform);

                SDL_Log("Platform destroyed!");

                // Delete the platform
                std::erase(state->platforms, platform);
            }
        }
    }

    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    // Get mouse input and set player to where it is at
    const auto state{static_cast<AppState *>(appstate)};

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        state->player->MoveX(event->motion.x);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    const auto state{static_cast<AppState *>(appstate)};

    SDL_DestroyRenderer(state->renderer);
    state->renderer = nullptr;

    SDL_DestroyWindow(state->window);
    state->window = nullptr;

    delete state;
}
