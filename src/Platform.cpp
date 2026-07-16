#include "Platform.hpp"
#include "BoundingBox.hpp"

Platform::Platform(float x, float y) {
    m_boundingBox = new BoundingBox{x, y, 100, 5};
}

void Platform::Render(SDL_Renderer * renderer) const {
    SDL_RenderRect(renderer, m_boundingBox->getRect());
}

void Platform::MoveDown(const Uint64 height) const {
    const SDL_FRect* box = m_boundingBox->getRect();

    m_boundingBox->setCoordinates(box->x, box->y + static_cast<float>(height));
}

Platform::~Platform() {
    delete m_boundingBox;
}
