
#include "Character.h"

Character::Character() {

}

void Character::MoveX(const float x) {
    // TODO: maybe mutex this or something /shrug
    m_x = x;
}
