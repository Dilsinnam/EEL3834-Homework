class Pet:
    
    def __init__(self, name: str):
        # initial values
        self.name = name
        self.health = 80
        self.hunger = 50
        self.happiness = 50

    # helper 
    def _clamp_stat(self, value: int) -> int:
        if value < 0:
            return 0
        if value > 100:
            return 100
        return value

    # helper to clamp
    def _clamp_all(self):
        self.health = self._clamp_stat(self.health)
        self.hunger = self._clamp_stat(self.hunger)
        self.happiness = self._clamp_stat(self.happiness)

    # interface
    def feed(self, amount: int):
        raise NotImplementedError

    def play(self):
        raise NotImplementedError

    def show_status(self):
        raise NotImplementedError


class Dog(Pet):
    # Dog rules
    def feed(self, amount: int):
        # base update
        self.hunger -= 10 * amount
        self.health += 2 * amount

        # hunger levels
        if self.hunger < 0:
            self.hunger = 0
            self.health -= 5

        # dog happiness gain
        self.happiness += amount

        # clamp stats after the change
        self._clamp_all()

    def play(self):
        # base effects for play
        self.hunger += 10
        self.happiness += 15
        self.health -= 5

        # dog happiness before clamping
        self.happiness += 5

        # clamp changes
        self._clamp_all()

    def show_status(self):
        
        print(f"Name: {self.name} (Dog)")
        print(f"Health: {self.health} Hunger: {self.hunger} Happiness: {self.happiness}")


class Cat(Pet):
    # cat subclass
    def feed(self, amount: int):
        # base update
        self.hunger -= 10 * amount
        self.health += 2 * amount

        # Overfeed 
        if self.hunger < 0:
            self.hunger = 0
            self.health -= 5

        # Cat happiness goals
        self.happiness += 2 * amount

        # clamp stats
        self._clamp_all()

    def play(self):
        # Base effects for play
        self.hunger += 10
        self.happiness += 15
        self.health -= 5

        # Cat extra health  before clamp
        self.health += 3

        # clamp changes
        self._clamp_all()

    def show_status(self):
        
        print(f"Name: {self.name} (Cat)")
        print(f"Health: {self.health} Hunger: {self.hunger} Happiness: {self.happiness}")


def _trim(s: str) -> str:
    # whitespace trim
    return s.strip()


def _input_line(prompt: str) -> str:
    # Wrapper 
    return input(prompt)


def main():
    pet = None

    
    while True:
        line = _input_line("Choose pet type (1=Dog, 2=Cat): ")
        
        try:
            t = int(line.strip())
        except ValueError:
            print("Invalid input.")
            continue

        if t not in (1, 2):
            print("Invalid choice.")
            continue

        
        while True:
            name = _input_line("Enter pet name: ")
            trimmed = _trim(name)
            if len(trimmed) == 0:
                print("Name cannot be empty.")
                continue
            name = trimmed
            break


        if t == 1:
            pet = Dog(name)
        else:
            pet = Cat(name)

        
        print()
        break

    
    while True:
        print("Virtual Pet")
        print("1. Feed pet")
        print("2. Play with pet")
        print("3. Show status")
        print("4. Exit")

        while True:
            line = _input_line("Enter choice: ")
            try:
                choice = int(line.strip())
            except ValueError:
                print("Invalid input.")
                continue

            if choice < 1 or choice > 4:
                print("Invalid choice.")
                print()
                choice = 0
                break
            break

        if choice == 0:
            continue

        if choice == 1:
            while True:
                line = _input_line("Enter food amount (1-10): ")
                try:
                    amount = int(line.strip())
                except ValueError:
                    print("Invalid input.")
                    continue
                if amount < 1 or amount > 10:
                    print("Error: amount must be between 1 and 10.")
                    continue
                break

            pet.feed(amount)
            print(f"You feed {pet.name}.")

            if pet.health <= 0:
                print("Your pet's health has reached 0. Game over.")
                return
            else:
                print()  

        elif choice == 2:
            pet.play()
            print(f"You play with {pet.name}.")

            
            if pet.health <= 0:
                print("Your pet's health has reached 0. Game over.")
                return
            else:
                print()  

        elif choice == 3:
            pet.show_status()
            print()  

        elif choice == 4:
            print("Goodbye!")
            return


if __name__ == "__main__":
    main()