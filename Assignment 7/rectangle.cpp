#include "rectangle.h"        
#include <sstream>            
#include <iomanip>            

Rectangle::Rectangle(double w, double h) : width(w), height(h) { // make width and height
    
}

double Rectangle::area() const {                     
    return width * height;                           // area = width * height
}

double Rectangle::perimeter() const {                
    return 2.0 * (width + height);                   // perimeter = 2*(width + height)
}

void Rectangle::scale(double factor) {               // scale dimension
    width *= factor;                                 
    height *= factor;                                
}

std::string Rectangle::describe() const {            
    std::ostringstream oss;                          
    oss << std::fixed << std::setprecision(2);       
    oss << "Rectangle: width=" << width              // append width
        << " height=" << height                      // append height
        << " area=" << area()                        // append area
        << " perimeter=" << perimeter();             // append perimeter
    return oss.str();                                
}
