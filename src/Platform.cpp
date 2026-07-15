#include "Platform.hpp"
#include "BoundingBox.hpp"

Platform::Platform() {
    m_boundingBox = new BoundingBox{500, 900, 100, 5};
}

void Platform::Render(SDL_Renderer * renderer) const {
    SDL_RenderRect(renderer, m_boundingBox->getRect());
}

Platform::~Platform() {
    delete m_boundingBox;
}
