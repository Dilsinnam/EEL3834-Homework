    #define _USE_MATH_DEFINES
    #include "circle.h"          
    #include <cmath>            
    #include <sstream>           
    #include <iomanip>           

    Circle::Circle(double r) : radius(r) {            
    }

    double Circle::area() const {                        
        return M_PI * radius * radius;                   // area = pi * r^2
    }

    double Circle::perimeter() const {                   // circumference
        return 2.0 * M_PI * radius;                      // perimeter = 2 * pi * r
    }

    void Circle::scale(double factor) {                  // scale by factor
        radius *= factor;                                // multiply radius by scale
    }

    std::string Circle::describe() const {               // produce string
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);       
        oss << "Circle: radius=" << radius               // append name and radius
            << " area=" << area()                       
            << " perimeter=" << perimeter();             
        return oss.str();                                
    }
