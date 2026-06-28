
#include "Character.h"
#include "SDL3/SDL_log.h"

Character::Character(SDL_Renderer *renderer) {
    SDL_Log("Character Constructed\n");

    SDL_Surface* loadedSurface = IMG_Load("../assets/character.png");

    if (loadedSurface != nullptr) {
        m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        m_height = loadedSurface->h;
        m_width = loadedSurface->w;

        SDL_DestroySurface(loadedSurface);
    } else {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load character.png");
    }
}

void Character::Render(SDL_Renderer* renderer) const {
    const SDL_FRect destinationRectangle {  m_x - ( static_cast<float>(150.f) / 2.0f)  , m_y, static_cast<float>(150), static_cast<float>(150) };

    SDL_RenderTexture(renderer, m_texture, nullptr, &destinationRectangle);
}

Character::~Character() {
    // Clear texture if exists
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

void Character::MoveX(const float x) {
    // TODO: maybe mutex this or something /shrug
    m_x = x;
}
