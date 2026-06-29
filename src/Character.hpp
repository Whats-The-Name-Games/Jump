#ifndef JUMP_CHARACTER_H
#define JUMP_CHARACTER_H
#include <SDL3_image/SDL_image.h>

class Character {
public:
    explicit Character(SDL_Renderer *);
    ~Character();

    void VelocityTick(Uint64);

    void Render(SDL_Renderer *) const;
    // Where the x should be
    void MoveX(float);

private:
    SDL_Texture *m_texture;

    float m_x{50};
    float m_y{640};

    int m_width{0};
    int m_height{0};

    float m_velocity{0};
};

#endif // JUMP_CHARACTER_H
