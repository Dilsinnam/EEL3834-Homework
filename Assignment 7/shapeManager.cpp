#include "shapeManager.h"     
#include <iostream>           
#include <iomanip>            

ShapeManager::ShapeManager() {   
    
}

ShapeManager::~ShapeManager() {  
    for (Shape* s : shapes) {   // iterate shape
        delete s;               // save memory
    }
    shapes.clear();             // clear vector
}

void ShapeManager::addShape(Shape* s) { // add shape to pointer
    shapes.push_back(s);                // add pointer to vector
}

void ShapeManager::viewAll() const {    
    if (shapes.empty()) {               
        std::cout << "No shapes." << std::endl; 
        std::cout << std::endl;         
        return;                         
    }
    for (const Shape* s : shapes) {     // iterate shape
        std::cout << s->describe() << std::endl; 
    }
    std::cout << std::endl;             
}

void ShapeManager::scaleAll(double factor) { // scale through factor
    for (Shape* s : shapes) {                 // iterate shapes
        s->scale(factor);                     
    }
}

void ShapeManager::describeAll() const {      
    if (shapes.empty()) {                     
        std::cout << "No shapes." << std::endl;
        std::cout << std::endl;
        return;
    }
    for (const Shape* s : shapes) {           // iterate line
        std::cout << s->describe() << std::endl;
    }
    std::cout << std::endl;                   
}

bool ShapeManager::empty() const {            
    return shapes.empty();                    
}
