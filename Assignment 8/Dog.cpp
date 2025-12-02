#include "Dog.h"
#include <iostream>

void Dog::feed(int amount) {
   // base update
    hunger -= 10 * amount;
    health += 2 * amount;

    // if hunger below 0, lower health
    if (hunger < 0) {
        hunger = 0;
        health -= 5;
    }

    // Dog gain
    happiness += amount;

    // stat boundry
    clamp_all_stats_after_update();
}

void Dog::play() {
    // play effects
    hunger += 10;
    happiness += 15;
    health -= 5;

    // dog happiness
    happiness += 5;

    // stat boundary
    clamp_all_stats_after_update();
}

void Dog::showStatus() const {
    std::cout << "Name: " << name << " (Dog)\n";
    std::cout << "Health: " << health << " Hunger: " << hunger << " Happiness: " << happiness << "\n";
}