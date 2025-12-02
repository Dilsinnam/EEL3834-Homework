#ifndef TRIANGLE_H           
#define TRIANGLE_H           

#include "shape.h"           
#include <string>            

class Triangle : public Shape { 
private:
    double base;             // private base
    double height;           // private base height
public:
    Triangle(double b, double h);                   
    virtual ~Triangle() = default;                  
    virtual double area() const override;           
    virtual double perimeter() const override;      
    virtual void scale(double factor) override;     
    virtual std::string describe() const override;  
};

#endif 
