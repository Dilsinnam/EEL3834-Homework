
#ifndef PET_H
#define PET_H

#include <string>

class Pet {
protected:
    std::string name;
    int health;
    int hunger;
    int happiness;

    // Helper
    void clamp_stat_0_to_100(int& stat) {
        if (stat < 0) stat = 0;
        else if (stat > 100) stat = 100;
    }

    // Helper to clamp all stats after any update, keeps the game valid
    void clamp_all_stats_after_update() {
        clamp_stat_0_to_100(health);
        clamp_stat_0_to_100(hunger);
        clamp_stat_0_to_100(happiness);
    }

public:
    // Seting initial values
    explicit Pet(const std::string& petName)
        : name(petName), health(80), hunger(50), happiness(50) {}

    // destructor for cleanup
    virtual ~Pet() = default;

    virtual void feed(int amount) = 0;
    virtual void play() = 0;
    virtual void showStatus() const = 0;

    // Accessors for loop to read name, health
    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
};

#endif