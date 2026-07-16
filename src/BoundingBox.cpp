#include "BoundingBox.hpp"
#include <SDL3/SDL_log.h>

// Arguments work just as they do in the SDL_FRect constructor, that is:
// - The (x,y) coordinate pair represents the top left of the bounding box
// - Increasing x values correlate to moving right, for example: x = 0 is to the left of x = 5. The right most pixel
// will be the pixel with the greatest possible x value.
// - Increasing y values correlate to moving down, for example: y = 0 represents the top of the screen. Any values
// greater than it will be further down. y = 15 is higher than y = 50.

// Assumes an AABB (Axis Aligned Bounding Box)
BoundingBox::BoundingBox(float x, float y, float width, float height) : m_rect{new SDL_FRect{x, y, width, height}} {}

BoundingBox::~BoundingBox() {
    delete m_rect;
}

// If another bounding box intersects with this bounding box on both the X and Y axes, we can say that the bounding
// boxes collide with one another.
bool BoundingBox::collidesWith(BoundingBox const &otherBox) const {
    // Error Detection
    if (m_rect == nullptr || otherBox.m_rect == nullptr) {
        SDL_Log("Collision Detection attempted with nonexistent bounding box(es). Initating box: %s | Other box: %s\n",
                (m_rect == nullptr) ? "nullptr" : "not nullptr", (m_rect == nullptr) ? "nullptr" : "not nullptr");
        return false;
    }
    return SDL_HasRectIntersectionFloat(m_rect, otherBox.m_rect);
}

void BoundingBox::setCoordinates(float x, float y) {
    m_rect->x = x;
    m_rect->y = y;
}
