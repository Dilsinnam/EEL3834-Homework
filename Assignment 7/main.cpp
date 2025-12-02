#include <iostream>          
#include <string>        
#include <sstream>            
#include <limits>            
#include <cctype>          
#include <memory>            
#include <iomanip>            
  
#include "shapeManager.h"
#include "circle.h"          
#include "rectangle.h"      
#include "triangle.h"        
  
int choose_Menu_Option();                                
int get_Shape_Type();                                
double get_Positive_Dimension_Of_Shape(const std::string& prompt);
double get_Positive_Scale_Factor_Of_Shape();                    
  
int main() {                                        
    ShapeManager manager;                           // pulling Shapemanager
    while (true) {                                  
        std::cout << "Shape Catalog" << std::endl;  
        std::cout << "1. Add Shape" << std::endl;  
        std::cout << "2. List All Shapes" << std::endl;
        std::cout << "3. Scale All Shapes" << std::endl;
        std::cout << "4. Describe All" << std::endl;
        std::cout << "5. Exit" << std::endl;        
        std::cout << "Enter choice: ";              
        int choice = choose_Menu_Option();               // get choice

        if (choice == -1) {                           // invalid, redisplay  menu
            continue;
        }
  
        if (choice == 1) {                          // add shape
            int type = get_Shape_Type();              // ask shape type
            if (type == 1) {                        // circle
                double r = get_Positive_Dimension_Of_Shape("Enter radius: "); // ask radius
                // make circle
                Shape* s = new Circle(r);          // add circle
                manager.addShape(s);              
                std::cout << "Shape added." << std::endl;
                std::cout << std::endl;            
            } else if (type == 2) { // rectangle
                double w = get_Positive_Dimension_Of_Shape("Enter width: ");  
                double h = get_Positive_Dimension_Of_Shape("Enter height: ");
                Shape* s = new Rectangle(w, h);    // add rectangle
                manager.addShape(s);              
                std::cout << "Shape added." << std::endl;
                std::cout << std::endl;            
            } else {                                // triangle
                double b = get_Positive_Dimension_Of_Shape("Enter base: ");  
                double h = get_Positive_Dimension_Of_Shape("Enter height: ");
                Shape* s = new Triangle(b, h);
                manager.addShape(s);               // add shape
                std::cout << "Shape added." << std::endl;
                std::cout << std::endl;            
            }
        } else if (choice == 2) {                  
            manager.viewAll();                      
        } else if (choice == 3) {                   // scale
            double factor;                          
            factor = get_Positive_Scale_Factor_Of_Shape();      
            manager.scaleAll(factor);               // scale shapes in database
            std::cout << "All shapes scaled." << std::endl;
            std::cout << std::endl;                
        } else if (choice == 4) {                  
            manager.describeAll();                  
        } else if (choice == 5) {                  
            std::cout << "Goodbye!" << std::endl;  
            break;                                  
        }
    }
    return 0;                                    
}
  
  
int choose_Menu_Option() {
    while (true) {                                // loop until passes
        std::string line;                        
        std::getline(std::cin, line);            
        std::stringstream ss(line);              
        int val;                                  // holding int
        if (!(ss >> val) || !(ss.eof())) {        // failure/whitespace
            std::cout << "Invalid choice." << std::endl;
            std::cout << std::endl;              
            return -1;                            // return to redisplay main menu
        } else {
            if (val < 1 || val > 5) {            
                std::cout << "Invalid choice." << std::endl;
                std::cout << std::endl;          
                return -1;                        // return to redisplay main menu
            } else {
                return val;                      
            }
        }
    }
}
  
int get_Shape_Type() {
    while (true) {                                // loop until passes
        std::cout << "Enter shape type (1=Circle, 2=Rectangle, 3=Triangle): ";
        std::string line;                        
        std::getline(std::cin, line);            
        std::stringstream ss(line);              
        int val;                                  // store int
        if (!(ss >> val) || !(ss.eof())) {        
            std::cout << "Invalid choice." << std::endl;
        } else {
            if (val < 1 || val > 3) {             // checking int in 1 - 3
                std::cout << "Invalid choice." << std::endl;
            } else {
                return val;                      
            }
        }
    }
}
  
  
double get_Positive_Dimension_Of_Shape(const std::string& prompt) {
    while (true) {                                // loop until passes
        std::cout << prompt;                      
        std::string line;                        
        std::getline(std::cin, line);            
        std::stringstream ss(line);               // checking value
        double val;
        if (!(ss >> val) || !(ss.eof())) {
            std::cout << "Invalid input." << std::endl;
        } else {
            if (!(val > 0.0)) {                   // checking if its a number, but but positive
                std::cout << "Error: Dimension must be greater than 0." << std::endl;
            } else {
                return val;                      
            }
        }
    }
}
  
double get_Positive_Scale_Factor_Of_Shape() {
    while (true) {                                // loop until passes
        std::cout << "Enter scale factor: ";      
        std::string line;
        std::getline(std::cin, line);            
        std::stringstream ss(line);               // checking input
        double val;                              
        if (!(ss >> val) || !(ss.eof())) {        // input not a number
            std::cout << "Invalid input." << std::endl;
        } else {
            if (!(val > 0.0)) {                  
                std::cout << "Error: Scale factor must be greater than 0." << std::endl;
            } else {
                return val;
            }
        }
    }
}