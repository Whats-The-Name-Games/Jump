#include "Platform.hpp"
#include "BoundingBox.hpp"

Platform::Platform(SDL_Renderer *) {
    m_boundingBox = new BoundingBox(500, 900, 50, 10);
}

Platform::~Platform() {
    delete m_boundingBox;
}
