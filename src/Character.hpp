#ifndef JUMP_CHARACTER_H
#define JUMP_CHARACTER_H
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "BoundingBox.hpp"

class Character {
public:
    /* Constructor & Destructor */
    explicit Character(SDL_Renderer *);
    ~Character();

    /* Physics Functions (Delta Time) */
    // Bounding Box
    BoundingBox *m_boundingBox;
    // Given the time elapsed since the last tick, calculate the player's current velocity.
    void VelocityTick(Uint64, const std::vector<BoundingBox*>&);

    /* Graphics Functions */
    void Render(SDL_Renderer *) const;
    // "Move" in the physical sense, not memory.
    // Move character's x position relative to the mouse's current X position
    void MoveX(float);

    /* Remove unused default class functions */
    // Remove Copy Constructor
    Character(const Character &) = delete;
    // Remove Copy Assignment
    Character &operator=(const Character &) = delete;
    // Remove Move Constructor
    Character(Character &&) = delete;
    // Remove Move Assignment
    Character &operator=(Character &&) = delete;

private:
    // Texture Data
    SDL_Texture *m_texture;

    // X and Y coordinate positions respectively
    float m_x{50};
    float m_y{640};

    // Character width and height. Values updated to match texture size upon load
    int m_width{0};
    int m_height{0};

    // If most recently went right, flip is false, if most recently went right, flip is true
    bool m_flip{false};

    // The character's current vertical velocity.
    float m_velocity{0};
};

#endif // JUMP_CHARACTER_H
