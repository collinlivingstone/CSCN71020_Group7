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
	TEST_CLASS(TestInputPointsForIsRectangle)
	{
	public:
		
		//Clockwise functionality tests
		TEST_METHOD(TestBasicRectangle)
		{
			double sides[] = { 3,3,4,4 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(TestLargeRectangle)
		{
			double sides[] = { 100, 100, 500, 500 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(TestRectangleLessThanZero)
		{
			double sides[] = { 0.01, 0.01, 0.02, 0.02 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(TestRectangleDecimals)
		{
			double sides[] = { 5.5, 5.5, 6.6, 6.6 };

			Assert::IsTrue(IsRectangle(sides));
		}

		TEST_METHOD(TestNegativeSidesValidation)
		{
			double sides[] = { -5, -5, -7, -7 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(TestSquareIsNotRectangle)
		{
			double sides[] = { 5, 5, 5, 5 };

			Assert::IsFalse(IsRectangle(sides));
		}

	};

	//Check same points validation to make sure a single point is not a rectangle -----------------------------------

	TEST_CLASS(TestSameSidesValidation)
	{
	public:

		TEST_METHOD(TestSameSides)
		{
			double sides[] = { 3, 3, 3, 3 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(TestSamePointsLarge)
		{
			double sides[] = { 10000, 10000, 10000, 10000 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(TestSameSidesNegative)
		{
			double sides[] = { -5,-5, -5, -5 };

			Assert::IsFalse(IsRectangle(sides));
		}

		TEST_METHOD(TestSameSidesDecimal)
		{
			double sides[] = { 0.1, 0.1, 0.1, 0.1 };

			Assert::IsFalse(IsRectangle(sides));
		}

	};

	//Checks to see the side outcomes of collecting points ---------------------------------------------------

	TEST_CLASS(TestGetSidesFunctionality)
	{
	public:

		TEST_METHOD(GetSidesBasicRectangle)
		{
			double points[4][2] = { {1,2}, {-1,2}, {-1,-2}, {1,-2} };

			double sides[4];

			GetSides(points, sides);

			//Check each side
			Assert::AreEqual(2.0, sides[0], 0.01);
			Assert::AreEqual(2.0, sides[1], 0.01);
			Assert::AreEqual(4.0, sides[2], 0.01);
			Assert::AreEqual(4.0, sides[3], 0.01);

		}

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

		//Test failed becasue we didnt account for shapes with diagnols smaller than quad
		TEST_METHOD(GetSidesTrapezoidNoOrder)
		{
			double points[4][2] = { {0,0}, {4,0}, {2,2}, {6,2} };

			double sides[4];

			GetSides(points, sides);

			//Check each side
			Assert::AreEqual(2.83, sides[0], 0.01);
			Assert::AreEqual(2.83, sides[1], 0.01);
			Assert::AreEqual(4.0, sides[2], 0.01);
			Assert::AreEqual(4.0, sides[3], 0.01);

		}

		TEST_METHOD(CollinearPointsTest)
		{
			double points[4][2] = { {1,0}, {2,0}, {3,0}, {4,0} };

			double sides[4];

			GetSides(points, sides);

			//Check each side
			Assert::AreEqual(0, sides[0], 0.01);
			Assert::AreEqual(0, sides[1], 0.01);
			Assert::AreEqual(0, sides[2], 0.01);
			Assert::AreEqual(0, sides[3], 0.01);

		}

		
	
	};


	//Checks to see different conditions of calculating Area ---------------------------------------------------

	TEST_CLASS(TestAreaOfRectangle)
	{
	public:

		TEST_METHOD(AreaTestOfBasicRectangle)
		{
			double sides[4] = { 50, 50, 100, 100 };
			double result = CalculateRectangleArea(sides);

			Assert::AreEqual(5000.0, result);
		}

		TEST_METHOD(AreaTestOfBasicRectangle2)
		{
			double sides[4] = { 25, 25, 75, 75 };
			double result = CalculateRectangleArea(sides);

			Assert::AreEqual(1875.0, result);
		}

		TEST_METHOD(AreaTestOfDecimalRectangle)
		{
			double sides[4] = { 4.5, 4.5, 5.5, 5.5 };
			double result = CalculateRectangleArea(sides);

			Assert::AreEqual(24.75, result);
		}

		TEST_METHOD(AreaTestOfRectangleLessThanZero)
		{
			double sides[4] = { 0.01, 0.01, 0.05, 0.05 };
			double result = CalculateRectangleArea(sides);

			Assert::AreEqual(0.0005, result, 0.0001);
		}

	};


	//Checks to see different conditions of calculating Perimeter ---------------------------------------------------

	TEST_CLASS(TestPerimeterOfRectangle)
	{
	public:

		TEST_METHOD(PerimeterTestOfBasicRectangle)
		{
			double sides[4] = { 50, 50, 100, 100 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(300.0, result);
		}

		TEST_METHOD(PerimeterTestOfBasicRectangle2)
		{
			double sides[4] = { 25, 25, 75, 75 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(200.0, result);
		}

		TEST_METHOD(PerimeterTestOfDecimalRectangle)
		{
			double sides[4] = { 4.5, 4.5, 5.5, 5.5 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(20.0, result);
		}

		TEST_METHOD(PerimeterTestOfRectangleLessThanZero)
		{
			double sides[4] = { 0.01, 0.01, 0.05, 0.05 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(0.12, result, 0.01);
		}

		TEST_METHOD(PerimeterTestLessThanZero)
		{
			double sides[4] = { 0.01, 0.015, 0.05, 0.06 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(0.135, result);
		}

		TEST_METHOD(PerimeterTestOfAllDifferentSides)
		{
			double sides[4] = { 0.5, 100, 20, 0.2 };
			double result = CalculatePerimeter(sides);

			Assert::AreEqual(120.7, result);
		}

	};


	//============================================================= Triangle Test Functions ============================================================

	TEST_CLASS(TestIsTriangleFunctionality)
	{
	public:

		// Can form triangle equalateral functionality checks
		TEST_METHOD(TestIfTrianglePositive)
		{
			double side1 = 5;
			double side2 = 5;
			double side3 = 5;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(TestIfTriangleDecimals)
		{
			double side1 = 3.3;
			double side2 = 3.3;
			double side3 = 3.3;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(TestIfTriangleLessThanOne)
		{
			double side1 = 0.5;
			double side2 = 0.5;
			double side3 = 0.5;

			Assert::IsTrue(CanFormTriangle(side1, side2, side3));
		}

	};

	//Is triangle validation tests----------------------------------------------
	TEST_CLASS(TestIsTriangleValidation)
	{
	public:

		TEST_METHOD(TestIfTriangleNegativeDecimal)
		{
			double side1 = -0.5;
			double side2 = -0.5;
			double side3 = -0.5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(TestIfTriangleNegative)
		{
			double side1 = -5;
			double side2 = -5;
			double side3 = -5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(TestIfNotTriangleLengths)
		{
			double side1 = 100;
			double side2 = 2;
			double side3 = 2;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(TestIfTriangleHasNegative)
		{
			double side1 = -100;
			double side2 = 20;
			double side3 = 20;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}


	};


	//Calculate angle tests --------------------------------------------------------

	TEST_CLASS(TestCalculateAngles)
	{
	public:

		TEST_METHOD(TestCalculateTriangleAnglesEqu)
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

		TEST_METHOD(TestCalculateTriangleAnglesIso)
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

		TEST_METHOD(TestCalculateTriangleAnglesObt)
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


		TEST_METHOD(TestCalculateTriangleAnglesDecimals)
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

		TEST_METHOD(TestFindEquilateralTriangle)
		{
			//Equilateral angle triangle
			double angleA = 60;
			double angleB = 60;
			double angleC = 60;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("Equilateral", result);
			
		}

		TEST_METHOD(TestFindIsosceleseTriangle)
		{
			//Isoscelese angle triangle
			double angleA = 36;
			double angleB = 72;
			double angleC = 72;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("AIsosceles", result);

		}

		TEST_METHOD(TestFindObtuseTriangle)
		{
			//Obtuse angle triangle
			double angleA = 50;
			double angleB = 110;
			double angleC = 20;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("OScalene", result);

		}

		TEST_METHOD(TestFindRightTriangle)
		{
			//Right angle triangle 
			double angleA = 45;
			double angleB = 45;
			double angleC = 90;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("Right", result);

		}

		TEST_METHOD(TestFindScaleneTriangle)
		{
			//Right angle triangle 
			double angleA = 40;
			double angleB = 30;
			double angleC = 110;

			char* result = FindTypeOfTriangle(angleA, angleB, angleC);

			Assert::AreEqual("OScalene", result);

		}

		TEST_METHOD(TestValidateNotATriangle)
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
