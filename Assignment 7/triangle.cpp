#include "triangle.h"         
#include <cmath>              
#include <sstream>            
#include <iomanip>            

Triangle::Triangle(double b, double h) : base(b), height(h) { 
}

double Triangle::area() const {                        
    return 0.5 * base * height;                        // area = 0.5 * base * height
}

double Triangle::perimeter() const {                   // perimeter
    double hyp = std::sqrt(base * base + height * height); 
    return base + height + hyp;                        // perimeter = base + height + hypotenuse
}

void Triangle::scale(double factor) {                   // scale base and height by factor
    base *= factor;                                    
    height *= factor;                                  
}

std::string Triangle::describe() const {                
    std::ostringstream oss;                            
    oss << std::fixed << std::setprecision(2);         
    oss << "Triangle: base=" << base                   // append base
        << " height=" << height                        // append height
        << " area=" << area()                          // append area
        << " perimeter=" << perimeter();               // append perimeter
    return oss.str();                                  
}
