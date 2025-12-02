#ifndef RECTANGLE_H          
#define RECTANGLE_H          

#include "shape.h"           
#include <string>            

class Rectangle : public Shape { 
private:
    double width;            // private width and height
    double height;           
public:
    Rectangle(double w, double h);                  
    virtual ~Rectangle() = default;                 
    virtual double area() const override;           
    virtual double perimeter() const override;      
    virtual void scale(double factor) override;    
    virtual std::string describe() const override;  
};

#endif 
