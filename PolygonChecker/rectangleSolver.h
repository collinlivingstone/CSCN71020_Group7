#ifndef RECTANGLE_SOLVER_H
#define RECTANGLE_SOLVER_H

#include <stdbool.h>

// Function to calculate distance between two points
double distance(double x1, double y1, double x2, double y2);

// Function to calculate squared distance between two points
double distance_squared(double x1, double y1, double x2, double y2);

// Function to determine if the points form a rectangle
bool is_rectangle(double points[4][2]);

// Main function to drive the rectangle solver
void rectangleSolver();

#endif 

