import math


class Circle:
    def __init__(self, radius: float):
        # checking dimensions
        if radius <= 0:
            raise ValueError("radius must be > 0")
        self.radius = float(radius)

    def area(self):
        # Area of a circle 
        return math.pi * self.radius * self.radius

    def perimeter(self):
        # Perimeter 
        return 2 * math.pi * self.radius

    def scale(self, factor):
        # scaling
        self.radius *= factor

    def describe(self):
        # formatting
        return f"Circle: radius={self.radius:.2f} area={self.area():.2f} perimeter={self.perimeter():.2f}"


class Rectangle:
    def __init__(self, width: float, height: float):
        # checking dimensions
        if width <= 0 or height <= 0:
            raise ValueError("width and height must be > 0")
        self.width = float(width)
        self.height = float(height)

    def area(self):
        # Area = width * height
        return self.width * self.height

    def perimeter(self):
        # Perimeter
        return 2 * (self.width + self.height)

    def scale(self, factor):
        # scaling
        self.width *= factor
        self.height *= factor

    def describe(self):
        # formatting
        return f"Rectangle: width={self.width:.2f} height={self.height:.2f} area={self.area():.2f} perimeter={self.perimeter():.2f}"


class Triangle:
    # right triangle with legs, base, height
    def __init__(self, base: float, height: float):
        # checking size
        if base <= 0 or height <= 0:
            raise ValueError("base and height must be > 0")
        self.base = float(base)
        self.height = float(height)

    def area(self):
        # Area of right triangle 
        return 0.5 * self.base * self.height

    def perimeter(self):
        # Perimeter 
        hyp = math.sqrt(self.base * self.base + self.height * self.height)
        return self.base + self.height + hyp

    def scale(self, factor):
        # scaling 
        self.base *= factor
        self.height *= factor

    def describe(self):
        # formatting
        return f"Triangle: base={self.base:.2f} height={self.height:.2f} area={self.area():.2f} perimeter={self.perimeter():.2f}"


class ShapeManager:
    # using duck typing
    def __init__(self):
        self._shapes = []

    def add_shape(self, obj):
        # store shape objects
        self._shapes.append(obj)

    def list_all(self):
        if not self._shapes:
            print("No shapes.")
            print()
            return
        for s in self._shapes:
            print(s.describe())
        print()

    def scale_all(self, factor):
        # Scale stored shapes by factor
        for s in self._shapes:
            s.scale(factor)

    def describe_all(self):
        for s in self._shapes:
            print(s.describe())
        print()


def print_menu():
    print("Shape Catalog")
    print("1. Add Shape")
    print("2. List All Shapes")
    print("3. Scale All Shapes")
    print("4. Describe All")
    print("5. Exit")
    print("Enter choice:", end=" ")


def get_menu_choice():
    # integer between 1 and 5
    while True:
        print_menu()
        choice_str = input()
        try:
            choice = int(choice_str)
        except ValueError:
            print("Invalid choice.")
            print()  
            continue
        if 1 <= choice <= 5:
            return choice
        else:
            print("Invalid choice.")
            print()  


def get_shape_type():
    # prompt loop
    while True:
        print("Enter shape type (1=Circle, 2=Rectangle, 3=Triangle):", end=" ")
        s = input()
        try:
            t = int(s)
        except ValueError:
            print("Invalid choice.")
            continue
        if t in (1, 2, 3):
            return t
        else:
            print("Invalid choice.")


def get_positive_float(prompt: str, error_msg: str):
    # reading float
    while True:
        print(prompt, end=" ")
        s = input()
        try:
            val = float(s)
        except ValueError:
            print("Invalid input.")
            continue
        if val <= 0:
            print(error_msg)
            continue
        return val


def main():
    mgr = ShapeManager()
    while True:
        choice = get_menu_choice()
        if choice == 1:
            # Add Shape
            t = get_shape_type()
            if t == 1:
                # Circle
                r = get_positive_float("Enter radius:", "Error: Dimension must be greater than 0.")
                try:
                    mgr.add_shape(Circle(r))
                except ValueError:
                    print("Error: Dimension must be greater than 0.")
                    continue
                print("Shape added.")
                print()  
            elif t == 2:
                # Rectangle
                w = get_positive_float("Enter width:", "Error: Dimension must be greater than 0.")
                h = get_positive_float("Enter height:", "Error: Dimension must be greater than 0.")
                try:
                    mgr.add_shape(Rectangle(w, h))
                except ValueError:
                    print("Error: Dimension must be greater than 0.")
                    continue
                print("Shape added.")
                print()
            else:
                # Triangle
                b = get_positive_float("Enter base:", "Error: Dimension must be greater than 0.")
                h = get_positive_float("Enter height:", "Error: Dimension must be greater than 0.")
                try:
                    mgr.add_shape(Triangle(b, h))
                except ValueError:
                    print("Error: Dimension must be greater than 0.")
                    continue
                print("Shape added.")
                print()
        elif choice == 2:
            # List All Shapes
            mgr.list_all()
        elif choice == 3:
            # Scale All Shapes
            factor = get_positive_float("Enter scale factor:", "Error: Scale factor must be greater than 0.")
            mgr.scale_all(factor)
            print("All shapes scaled.")
            print()
        elif choice == 4:
            # Describe All
            mgr.describe_all()
        else:
            
            print("Goodbye!")
            break


if __name__ == "__main__":
    main()