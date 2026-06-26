#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/*
 *  Code by: Luke Deany and Michael Khan
 *  Artwork by: Ted Freakdogshow
*/

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
} AppState;

constexpr int WIDTH = 720;
constexpr int HEIGHT = 1280;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_SetAppMetadata("Jig is Up", "0.1", "com.whatsthenamegames.jigisup");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState* state {new AppState()};
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("Jig is Up", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(state->renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

// Every frame? Maybe? Something like that
SDL_AppResult SDL_AppIterate(void *appstate) {

    const AppState* state { static_cast<AppState *>(appstate) };

    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(state->renderer);

    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    // Get mouse input and set player to where it is at

    const AppState* state { static_cast<AppState *>(appstate) };

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    const AppState* state { static_cast<AppState *>(appstate) };

    delete state;
}