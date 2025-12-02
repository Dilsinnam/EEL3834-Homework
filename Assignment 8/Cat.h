#ifndef CAT_H
#define CAT_H

#include "Pet.h"

class Cat : public Pet {
public:
    // creating a cat
    explicit Cat(const std::string& petName) : Pet(petName) {}

    // 
    void feed(int amount) override;
    void play() override;
    void showStatus() const override;
};

#endif 