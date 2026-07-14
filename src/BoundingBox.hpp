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

private:
    // SDL FRect functions require a const FRect (likely to deal with potential multithreading problems?)
    // Underlying rect therefore stored in pointer. Pointer can change to a NEW rect, but actual rect cannot be modified
    // directly.
    const SDL_FRect *m_rect;
};

#endif // !JUMP_BOUNDINGBOX_H
