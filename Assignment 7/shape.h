#ifndef SHAPE_H               
#define SHAPE_H               

#include <string>             
                               
class Shape {                
public:                      
    virtual ~Shape() = default;                 
    virtual double area() const = 0;            
    virtual double perimeter() const = 0;       
    virtual void scale(double factor) = 0;      
    virtual std::string describe() const = 0;   
};

#endif 
