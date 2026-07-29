#ifndef JUMP_BOUNDINGBOX_H
#define JUMP_BOUNDINGBOX_H
#include <SDL3_image/SDL_image.h>
#include <memory>

class BoundingBox {
public:
    BoundingBox(float x, float y, float width, float height);
    ~BoundingBox();

    /* Collision Detection API */
    bool collidesWith(BoundingBox const &) const;

    /* Graphics Functions */
    // TODO: Impl rendering. Should be called by main if some debug value is true. Perhaps passed in game state?
    void render(SDL_Renderer *);

    void setCoordinates(float x, float y);

    // Return by value as we want the rectangle to be maintained even if the bounding box dies to avoid exceptions
    [[nodiscard]]
    SDL_FRect getRect() const {
        return *m_rect;
    }

private:
    std::unique_ptr<SDL_FRect> m_rect;
};

#endif // !JUMP_BOUNDINGBOX_H
