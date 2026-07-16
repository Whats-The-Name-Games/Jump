
#include "Character.hpp"
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cmath>
#include "BoundingBox.hpp"

// Probably best somewhere else, but i'm tired of looking up best practices for today and just want this done
constexpr float GRAVITY = 9.81f;

Character::Character(SDL_Renderer *renderer) {
    SDL_Log("Character Constructed\n");

    SDL_Surface *loadedSurface = IMG_Load("../assets/character.png");

    if (loadedSurface != nullptr) {
        // Load PNG, load as surface, convert to texture, clean up surface from memory and reap important information
        // from time as a surface.
        m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        m_height = loadedSurface->h;
        m_width = loadedSurface->w;

        SDL_DestroySurface(loadedSurface);

        // Create Bounding Box!
        m_boundingBox = new BoundingBox(m_x, m_y, m_width, m_height);
    } else {
        // TODO: This failure means we cannot provide collision for the player. Should this crash the program or lead it
        // to default to a predefined size?
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load character.png");
    }
}

// Have the character fall over time
Uint64 Character::VelocityTick(const Uint64 delta, const std::vector<BoundingBox *> &possibleCollisions) {
    // Using the delta of frames, calculate how far we should fall (assuming velocity should change per second)
    const float velocity_tick = static_cast<float>(delta) / 1000.0f;

    m_velocity = std::max(-30.0f, m_velocity - GRAVITY * velocity_tick);

    float new_y = m_y - m_velocity;

    // Calculate if we would have collided with a platform
    // For now just assume a platform is there
    // Platform X1, Platform X2, platform Y
    /*const int x1 = 300;
    const int x2 = 500;
    const int y = 900;

    // If we're in bounds, then increase velocity upward!
    if (m_velocity < 0 && (m_x >= x1 && m_x <= x2) && (m_y <= y && new_y >= y)) {
        m_velocity = 10;
    }
    */
    // Subtraction because higher Y values are at the top of the screen, so negative velocity would go up
    m_y -= m_velocity;
    if (m_y > 1280) {
        m_y = -200;
    }

    Uint64 scoreDelta = 0;

    // If the player is above the defined y height, for now 500, then just move the score up that amount and set the y to 500!
    if (m_y < 500) {
        scoreDelta = static_cast<Uint64>(500.f - m_y);
        m_y = 500;
    }

    // TODO: Better way of handling mouse position
    m_boundingBox->setCoordinates(m_x - (static_cast<float>(m_width) / 2.0f) , m_y - (static_cast<float>(m_height) / 2.0f));

    // Check with all the possible collisions
    for (const auto& box: possibleCollisions) {
        // TODO: Update this with some sort of logic (variant/visitor?) to determine if we're colliding with a platform
        // or enemy)
        if (box->collidesWith(*m_boundingBox)) {
            m_velocity = 10;
        }
    }

    return scoreDelta;
}

void Character::Render(SDL_Renderer *renderer) const {
    const SDL_FRect destinationRectangle{m_x - (static_cast<float>(m_width) / 2.0f),
                                         m_y - (static_cast<float>(m_height) / 2.0f), static_cast<float>(m_width),
                                         static_cast<float>(m_height)};

    SDL_FlipMode flip = m_flip ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    SDL_RenderTextureRotated(renderer, m_texture, nullptr, &destinationRectangle, 0, nullptr,  flip);

    SDL_RenderRect(renderer, m_boundingBox->getRect());
}

Character::~Character() {
    // Clear texture if exists
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    delete m_boundingBox;
}

void Character::MoveX(const float x) {
    // Logic of flipping the character based on mouse delta
    bool diff = std::abs(m_x - x) >= 2.5f;

    if (diff) {
        m_flip = m_x < x;
    }

    // TODO: maybe mutex this or something /shrug
    m_x = x;
}
