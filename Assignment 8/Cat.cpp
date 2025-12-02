#include "Cat.h"
#include <iostream>

void Cat::feed(int amount) {
    // Base update
    hunger -= 10 * amount;
    health += 2 * amount;

    // Hunger check
    if (hunger < 0) {
        hunger = 0;
        health -= 5;
    }

    // Cat happiness gain
    happiness += 2 * amount;

    // stat boundary
    clamp_all_stats_after_update();
}

void Cat::play() {
    // play effects
    hunger += 10;
    happiness += 15;
    health -= 5;

    // cat extra health
    health += 3;

    // stat boundary
    clamp_all_stats_after_update();
}

void Cat::showStatus() const {
    std::cout << "Name: " << name << " (Cat)\n";
    std::cout << "Health: " << health << " Hunger: " << hunger << " Happiness: " << happiness << "\n";
}