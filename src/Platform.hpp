
#ifndef JUMP_PLATFORM_H
#define JUMP_PLATFORM_H
#include <SDL3_image/SDL_image.h>

class BoundingBox;

class Platform {
public:
    Platform(float, float);

    ~Platform();

    /* Remove unused default class functions */
    // Remove Copy Constructor
    Platform(const Platform &) = delete;
    // Remove Copy Assignment
    Platform &operator=(const Platform &) = delete;
    // Remove Move Constructor
    Platform(Platform &&) = delete;
    // Remove Move Assignment
    Platform &operator=(Platform &&) = delete;

    void Render(SDL_Renderer *) const;

    // Used to move down platforms when the player goes up
    void MoveDown(Uint64 height) const;

    BoundingBox& getBoundingBox() const {
        return *m_boundingBox;
    }

private:
    BoundingBox *m_boundingBox;
};


#endif // JUMP_PLATFORM_H
