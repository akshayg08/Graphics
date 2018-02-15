#include "life.h"
#include "main.h"

#include "heart.h"

Life::Life() {
    life = 3;
}

void Life::init() {
    for (int i = 0; i < 5; i++) hearts[i] = Heart(-3.7+i*0.5, 3.7);
}

bool Life::decrease() {
    life--;
    return (life == 0);
}

void Life::draw(glm::mat4 VP) {
    for (int i = 0; i < life; i++) hearts[i].draw(VP);
}
