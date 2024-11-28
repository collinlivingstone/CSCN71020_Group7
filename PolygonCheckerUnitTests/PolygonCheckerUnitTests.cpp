#include "pch.h"
#include "CppUnitTest.h"

//Triangle testing functions
extern "C" void CalculateAngles(double, double, double, double*, double*, double*); //Tested
extern "C" int CanFormTriangle(double, double, double); //Tested
extern "C" char* FindTypeOfTriangle(double, double, double); // Tested

//Rectangle testing functions
extern "C" double Distance(double, double, double, double);
extern "C" double DistanceSquared(double, double, double, double);

extern "C" bool IsRectangle(double[4]); //Tested
extern "C" double CalculatePerimeter(double[4]); //Need to test
extern "C" double CalculateRectangleArea(double[4]);
extern "C" void GetSides(double points[4][2], double[4]); //Need to test

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolygonCheckerUnitTests 
{
	//Checks to see basic rectangles return true ----------------------------------------------------
	TEST_CLASS(CheckInputPointsForIsRectangle)
	{
	public:
		
		//Clockwise functionality tests
		TEST_METHOD(CheckBasicRectangle)
		{
			double sides[] = { 3,3,4,4 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(CheckLargeRectangle)
		{
			double sides[] = { 100, 100, 500, 500 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(CheckRectangleLessThanZero)
		{
			double sides[] = { 0.01, 0.01, 0.02, 0.02 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(CheckRectangleDecimals)
		{
			double sides[] = { 5.5, 5.5, 6.6, 6.6 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(CheckNegativeSidesValidation)
		{
			double sides[] = { -5, -5, -7, -7 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(CheckSquareIsNotRectangle)
		{
			double sides[] = { 5, 5, 5, 5 };

			Assert::IsFalse(IsRectangle(sides));
		}

	};

	//Check same points validation to make sure a single point is not a rectangle -----------------------------------

	TEST_CLASS(CheckSameSidesValidation)
	{
	public:

		TEST_METHOD(CheckSameSides)
		{
			double sides[] = { 3, 3, 3, 3 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(CheckSamePointsLarge)
		{
			double sides[] = { 10000, 10000, 10000, 10000 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(CheckSameSidesNegative)
		{
			double sides[] = { -5,-5, -5, -5 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(CheckSameSidesDecimal)
		{
			double sides[] = { 0.1, 0.1, 0.1, 0.1 };

			Assert::IsFalse(IsRectangle(sides));
		}

	};

	//Check same points validation to make sure a single point is not a rectangle -----------------------------------

	TEST_CLASS(CheckSamePointInputs)
	{
	public:

	

	};






	//Checks to see the side outcomes of collecting points ---------------------------------------------------

	TEST_CLASS(GetSidesFunctionality)
	{
	public:

		TEST_METHOD(GetSidesSquareNoOrder)
		{
			double points[4][2] = {{1,1}, {-1,-1}, {1,-1}, {-1,1}};

			double sides[4];

			GetSides(points, sides);

			//Check each side
			Assert::AreEqual(2.0, sides[0]);
			Assert::AreEqual(2.0, sides[1]);
			Assert::AreEqual(2.0, sides[2]);
			Assert::AreEqual(2.0, sides[3]);

		}

		TEST_METHOD(GetSidesDiagonalRectangleNoOrder)
		{
			double points[4][2] = { {1,3}, {4,0}, {0,-4}, {-3,-1} };

			double sides[4];

			GetSides(points, sides);

			//Check each side
			Assert::AreEqual(4.24, sides[0], 0.01);
			Assert::AreEqual(4.24, sides[1], 0.01);
			Assert::AreEqual(5.66, sides[2], 0.01);
			Assert::AreEqual(5.66, sides[3], 0.01);

		}

		
	
	};

	//============================================================= Triangle Test Functions ============================================================

	TEST_CLASS(TriangleFunctionalityTests)
	{
	public:

		// Can form triangle equalateral functionality checks
		TEST_METHOD(CheckIfTrianglePositive)
		{
			double side1 = 5;
			double side2 = 5;
			double side3 = 5;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(CheckIfTriangleDecimals)
		{
			double side1 = 3.3;
			double side2 = 3.3;
			double side3 = 3.3;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(CheckIfTriangleLessThanOne)
		{
			double side1 = 0.5;
			double side2 = 0.5;
			double side3 = 0.5;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}


	};

	//Is triangle validation tests----------------------------------------------
	TEST_CLASS(IsTriangleValidationTests)
	{
	public:

		TEST_METHOD(CheckIfTriangleNegative1)
		{
			double side1 = -0.5;
			double side2 = -0.5;
			double side3 = -0.5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(CheckIfTriangleNegative2)
		{
			double side1 = -5;
			double side2 = -5;
			double side3 = -5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(CheckIfTriangleBadLengths)
		{
			double side1 = 100;
			double side2 = 2;
			double side3 = 2;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

	};


	//Calculate angle tests --------------------------------------------------------

	TEST_CLASS(CalculateAnglesTests)
	{
	public:

		TEST_METHOD(CalculateTriangleAnglesEqu)
		{
			//Sides
			double side1 = 5;
			double side2 = 5;
			double side3 = 5;

			//Anlges
			double angleA;
			double angleB;
			double angleC;

			//Run function
			CalculateAngles(side1, side2, side3, &angleA, &angleB, &angleC);

			//Floating point number accuracy allowance
			double fpErrorAllowance = 0.01;

			Assert::AreEqual(60.0, angleA, fpErrorAllowance);
			Assert::AreEqual(60.0, angleA, fpErrorAllowance);
			Assert::AreEqual(60.0, angleA, fpErrorAllowance);
		}

		TEST_METHOD(CalculateTriangleAnglesIso)
		{
			//Sides
			double side1 = 10;
			double side2 = 10;
			double side3 = 5;

			//Anlges
			double angleA = 0;
			double angleB = 0;
			double angleC = 0;

			//Run function
			CalculateAngles(side1, side2, side3, &angleA, &angleB, &angleC);

			//Floating point number accuracy allowance
			double fpErrorAllowance = 0.01;

			Assert::AreEqual(75.52, angleA, fpErrorAllowance);
			Assert::AreEqual(75.52, angleB, fpErrorAllowance);
			Assert::AreEqual(28.95, angleC, fpErrorAllowance);
		}

		TEST_METHOD(CalculateTriangleAnglesObt)
		{
			//Sides
			double side1 = 10;
			double side2 = 5;
			double side3 = 7;

			//Anlges
			double angleA = 0;
			double angleB = 0;
			double angleC = 0;

			//Run function
			CalculateAngles(side1, side2, side3, &angleA, &angleB, &angleC);

			//Floating point number accuracy allowance
			double fpErrorAllowance = 0.01;

			Assert::AreEqual(111.80, angleA, fpErrorAllowance);
			Assert::AreEqual(27.66, angleB, fpErrorAllowance);
			Assert::AreEqual(40.53, angleC, fpErrorAllowance);
		}


		TEST_METHOD(CalculateTriangleAnglesDecimals)
		{
			//Sides
			double side1 = 5.24;
			double side2 = 10.53;
			double side3 = 6.45;

			//Anlges
			double angleA = 0;
			double angleB = 0;
			double angleC = 0;

			//Run function
			CalculateAngles(side1, side2, side3, &angleA, &angleB, &angleC);

			//Floating point number accuracy allowance
			double fpErrorAllowance = 0.01;

			Assert::AreEqual(23.01, angleA, fpErrorAllowance);
			Assert::AreEqual(128.22, angleB, fpErrorAllowance);
			Assert::AreEqual(28.76, angleC, fpErrorAllowance);
		}

	};


	//Find type of triangle tests ----------------------------------------------------

	TEST_CLASS(TestTypeOfTriangle)
	{
	public:

		TEST_METHOD(FindEquilateralTriangle)
		{
			//Equilateral angle triangle
			double angleA = 60;
			double angleB = 60;
			double angleC = 60;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("Equilateral", result);
			
		}

		TEST_METHOD(FindIsosceleseTriangle)
		{
			//Isoscelese angle triangle
			double angleA = 36;
			double angleB = 72;
			double angleC = 72;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("AIsosceles", result);

		}

		TEST_METHOD(FindObtuseTriangle)
		{
			//Obtuse angle triangle
			double angleA = 50;
			double angleB = 110;
			double angleC = 20;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("OScalene", result);

		}

		TEST_METHOD(FindRightTriangle)
		{
			//Right angle triangle 
			double angleA = 45;
			double angleB = 45;
			double angleC = 90;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("Right", result);

		}

		TEST_METHOD(FindScaleneTriangle)
		{
			//Right angle triangle 
			double angleA = 40;
			double angleB = 30;
			double angleC = 110;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("OScalene", result);

		}

		TEST_METHOD(ValidateNotATriangle)
		{
			//Not a triangle validation
			double angleA = 180;
			double angleB = 105;
			double angleC = 200;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("NTriangle", result);

		}
	};

}
