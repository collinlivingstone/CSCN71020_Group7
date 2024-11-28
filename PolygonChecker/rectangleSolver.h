#ifndef RECTANGLE_SOLVER_H
#define RECTANGLE_SOLVER_H

#include <stdbool.h>

// Function to calculate distance between two points
double Distance(double x1, double y1, double x2, double y2);

//Get 4 sdes of shape
void GetSides(double points[4][2], double[4]);

// Function to get input from user
void InputPointsRectangle(double points[4][2]);

// Function to calculate squared distance between two points
double DistanceSquared(double x1, double y1, double x2, double y2);

// Function to determine if the points form a rectangle
//bool IsRectangle(double points[4][2]);
bool IsRectangle(double[4]);

//Function to calculate perimeter
double CalculatePerimeter(double[4]);

//Function for calculating rectangle
double CalculateRectangleArea(double[4]);

#endif 

