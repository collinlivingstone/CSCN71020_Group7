#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "triangleSolver.h"
#include "rectangleSolver.h"
#include "triangleChecker.h"

int side = 0;

int main() 
{
	double a, b, c;
	double A, B, C;

	bool continueProgram = true;
	while (continueProgram) 
	{
		printWelcome();

		int shapeChoice = printShapeMenu();

		switch (shapeChoice)
		{
		case 1:

			printf("Enter the side lengths of the triangle:\n");
			a = get_side_length("Side 1: ");
			b = get_side_length("Side 2: ");
			c = get_side_length("Side 3: ");

			if (can_form_triangle(a, b, c)) {
				printf("The side lengths can form a triangle.\n");
				calculate_angles(a, b, c, &A, &B, &C);
				printf("The angles of the triangle are:\n");
				printf("Angle A: %.2f°\n", A);
				printf("Angle B: %.2f°\n", B);
				printf("Angle C: %.2f°\n", C);
			}
			else
			{
				printf("The side lengths cannot form a triangle.\n");
			}


			//case 2: printf_s(Rectangle selected. \n");
			//
			//
			//
			//
			//break;
		case 0:
			continueProgram = false;
			break;
		default:
			printf_s("Invalid value entered.\n");
			break;
		}
	}
	return 0;
}

void printWelcome() 
{
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

int printShapeMenu() 
{
	printf_s("1. Triangle\n");

	//printf_s(2. Rectangle\n"); 

	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

