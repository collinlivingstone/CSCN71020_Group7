#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "RectangleSolver.h"
#include "TriangleSolver.h"

int side = 0;
double points[4][2];

int main() 
{
	//triangle variables
	double triangleSideA, triangleSideB, triangleSideC;
	double triangleAngleA, triangleAngleB, triangleAngleC;

	bool continueProgram = true;
	while (continueProgram) 
	{
		PrintWelcome();

		int shapeChoice = PrintShapeMenu();

		//Menu
		switch (shapeChoice)
		{
		case 1://triangle Selected

			printf("Please enter the side lengths of the triangle:\n");
			triangleSideA = GetSideLength("Side 1: ");
			triangleSideB = GetSideLength("Side 2: ");
			triangleSideC = GetSideLength("Side 3: ");

			if (CanFormTriangle(triangleSideA, triangleSideB, triangleSideC)) {
				printf("The side lengths can form a triangle.\n");

				CalculateAngles(triangleSideA, triangleSideB, triangleSideC, &triangleAngleA, &triangleAngleB, &triangleAngleC);

				printf("The angles of the triangle are:\n");
				printf("Angle A: %.2f°\n", triangleAngleA);
				printf("Angle B: %.2f°\n", triangleAngleB);
				printf("Angle C: %.2f°\n", triangleAngleC);
			}
			else
			{
				printf("The side lengths cannot form a triangle.\n");
				break;
			}


		case 2: //rectangle Selected

			//Get rectangle input
			InputPointsRectangle(points);

			//If the points form a rectangle
			if (IsRectangle(points)) {
				double perimeter = CalculatePerimeter(points);
				double area = CalculateRectangleArea(points);

				printf("\n");
				printf("The points you entered form a rectangle\n");
				printf("Perimeter: %.2f\n", perimeter);
				printf("Area: %.2f\n", area);
			}
			//If points dont create rectangle
			else { 

				double perimeter = CalculatePerimeter(points);

				printf("These points do not form a rectangle.\n");
				printf("The perimeter of this shape is: %.2f\n", perimeter);
			}

			break;

		case 0: //exit

			continueProgram = false;
			break;

		default: //invalid entry
			printf_s("Invalid value entered.\n");
			break;
		}
	}

	return 0;
}

void PrintWelcome() 
{
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
	printf("\n");
}

int PrintShapeMenu() 
{
	printf_s("1. Triangle\n");

	printf_s("2. Rectangle\n"); 

	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

