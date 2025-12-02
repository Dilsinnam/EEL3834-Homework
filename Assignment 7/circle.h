#ifndef CIRCLE_H             
#define CIRCLE_H             

#include "shape.h"          
#include <string>           

class Circle : public Shape { 
private:                     
    double radius;           // storing radius as private
public:                      
    Circle(double r);        
    virtual ~Circle() = default;
    virtual double area() const override;
    virtual double perimeter() const override;     
    virtual void scale(double factor) override;    
    virtual std::string describe() const override; 
};                          

#endif 
