
#ifndef DOG_H
#define DOG_H

#include "Pet.h"

class Dog : public Pet {
public:
    // Making dog
    explicit Dog(const std::string& petName) : Pet(petName) {}

    // Feed, play, status rules
    void feed(int amount) override;
    void play() override;
    void showStatus() const override;
};

#endif 