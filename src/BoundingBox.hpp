#ifndef JUMP_BOUNDINGBOX_H
#define JUMP_BOUNDINGBOX_H
#include <SDL3_image/SDL_image.h>

class BoundingBox {
public:
    BoundingBox(float x, float y, float width, float height);
    ~BoundingBox();

    /* Collision Detection API */
    bool collidesWith(BoundingBox const &) const;

    /* Graphics Functions */
    // TODO: Impl rendering. Should be called by main if some debug value is true. Perhaps passed in game state?
    void render(SDL_Renderer *);

    void setDimensions(float x, float y);

    SDL_FRect* getRect() const {
        return m_rect;
    }

private:
    SDL_FRect* const m_rect;
};

#endif // !JUMP_BOUNDINGBOX_H
