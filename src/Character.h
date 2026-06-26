#ifndef JUMP_CHARACTER_H
#define JUMP_CHARACTER_H

class Character {
    public:
        Character();

        // Where the x should be
        void MoveX(const float);

        void MoveX(float&&);

    private:
        float m_x {0};
        float m_y {0};
};

#endif //JUMP_CHARACTER_H
