#ifndef SHAPEMANAGER_H       
#define SHAPEMANAGER_H       

#include "shape.h"           
#include <vector>            
#include <string>            

class ShapeManager {         
private:
    std::vector<Shape*> shapes; // private vector 
public:
    ShapeManager();
    ~ShapeManager();         // to delete shapes
    void addShape(Shape* s); 
    void viewAll() const;    
    void scaleAll(double factor); 
    void describeAll() const; 
    bool empty() const;      
};

#endif 
