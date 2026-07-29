#ifndef JUMP_CHARACTER_H
#define JUMP_CHARACTER_H
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <array>
#include "BoundingBox.hpp"

class Character {
public:
    /* Constructor & Destructor */
    explicit Character(SDL_Renderer *);
    ~Character();

    /* Physics Functions (Delta Time) */
    // Given the time elapsed since the last tick, calculate the player's current velocity.
    // Returns how much the player is above y = 500
    Uint64 VelocityTick(Uint64, const std::vector<BoundingBox *> &);

    /* Graphics Functions */
    void Render(SDL_Renderer *) const;
    void RenderTick();

    // "Move" in the physical sense, not memory.
    // Move character's x position relative to the mouse's current X position
    void MoveX(float);

    // Returns true if the character fell off the map
    bool checkForFailure() const;

    // Resets the players Y position
    void Reset();

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

    // Bounding Box
    BoundingBox *m_boundingBox;
    BoundingBox *m_feetBox;

    Uint64 m_lastAnimationTick{0};

    // The current frame we're on of the jump animation
    int m_animationFrame{0};

    // the current frame of the overall sprite we're on
    int m_frame {0};

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

    static constexpr std::array<int, 7> s_jump = {3, 6, 7, 8, 9, 5, 3};
};

#endif // JUMP_CHARACTER_H
