#include "pch.h"
#include "CppUnitTest.h"

//•	"type of triangle" functionality.
//•	"triangle inside angle" functionality.
//•	"4 points" functionality.


//Triangle testing functions
extern "C" void CalculateAngles(double, double, double, double*, double*, double*);
extern "C" int CanFormTriangle(double, double, double);
extern "C" void CalculateAngles(double, double, double, double*, double*, double*);

//Rectangle testing functions
extern "C" double Distance(double, double, double, double);
extern "C" double DistanceSquared(double, double, double, double);
extern "C" bool IsRectangle(double points[4][2]);
extern "C" bool CalculatePerimeter(double points[4][2]);
extern "C" bool CalculateRectangleArea(double points[4][2]);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolygonCheckerUnitTests //Functionality Tests
{
	TEST_CLASS(CheckInputPointsForRectangleClockwise)
	{
	public:
		
		//Clockwise functionality tests
		TEST_METHOD(CheckPositiveValues)
		{
			double points[4][2] = { {3,4}, {3,0}, {0,0}, {0,4} };

			Assert::IsTrue(IsRectangle(points));
		}

		TEST_METHOD(CheckNegativeValues)
		{
			double points[4][2] = { {-1,1}, {-6,1}, {-6,4}, {-1,4} };

			Assert::IsTrue(IsRectangle(points));
		}

		TEST_METHOD(CheckPositiveAndNegative)
		{
			double points[4][2] = { {-1,1}, {-6,1}, {-6,4}, {-1,4} };

			Assert::IsTrue(IsRectangle(points));
		}

		TEST_METHOD(CheckSamePoints1)
		{
			double points[4][2] = { {1,1}, {1,1}, {1,1}, {1,1} };

			Assert::IsFalse(IsRectangle(points));
		}

		TEST_METHOD(CheckSamePoints2)
		{
			double points[4][2] = { {2,2}, {2,2}, {2,2}, {2,2} };

			Assert::IsFalse(IsRectangle(points));
		}

		TEST_METHOD(CheckSamePoints3)
		{
			double points[4][2] = { {3,3}, {3,3}, {3,3}, {3,3} };

			Assert::IsFalse(IsRectangle(points));
		}

		TEST_METHOD(CheckSamePointsNegative1)
		{
			double points[4][2] = { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} };

			Assert::IsFalse(IsRectangle(points));
		}

		TEST_METHOD(CheckDecimalPairs)
		{
			double points[4][2] = { {0.5,0.5}, {0.5,-0.5}, {-0.7,-0.5}, {-0.7,0.5} };

			Assert::IsTrue(IsRectangle(points));
		}

	};

	TEST_CLASS(CheckSquaresInputClockwise)
	{
	public:

		TEST_METHOD(CheckSquare1)
		{
			double points[4][2] = { {-1,1}, {1,1}, {1,-1}, {-1,-1} };

			Assert::IsTrue(IsRectangle(points));

		}
		TEST_METHOD(CheckSquare2)
		{
			double points[4][2] = { {-2,2}, {2,2}, {2,-2}, {-2,-2} };

			Assert::IsTrue(IsRectangle(points));

		}

		TEST_METHOD(CheckPositiveSquare)
		{
			double points[4][2] = { {1,2}, {1,4}, {3,2}, {3,4} };

			Assert::IsTrue(IsRectangle(points));

		}

		TEST_METHOD(CheckNegativeSquare)
		{
			double points[4][2] = { {-1,-1}, {-3,-1}, {-3,-3}, {-1,-3} };

			Assert::IsTrue(IsRectangle(points));

		}
	};

	TEST_CLASS(CheckDiagonalRectanglesClockwise) //Return true
	{
	public:

		TEST_METHOD(DialgonalRectangleTest1)
		{
			double points[4][2] = { {4,0}, {-4,8}, {-8,-4}, {0,4} };

			Assert::IsTrue(IsRectangle(points));

		}

		TEST_METHOD(DiagonalSquareRectangle)
		{
			double points[4][2] = { {2,0}, {0,-2}, {-2,0}, {0,2} };

			Assert::IsTrue(IsRectangle(points));

		}

		TEST_METHOD(RectangleSolverBoundryTests)
		{
			double points[4][2] = { {2,0}, {0,-2}, {-2,0}, {0,2} };

			Assert::IsTrue(IsRectangle(points));

		}
	};

	TEST_CLASS(CheckQuadShapes) //Return false
	{
	public:
		TEST_METHOD(CheckPosNegQuadShape)
		{
			double points[4][2] = { {1,3}, {4,-2}, {-1,-5}, {-7,3} };

			Assert::IsFalse(IsRectangle(points));

		}

		TEST_METHOD(CheckNegQuadShape)
		{
			double points[4][2] = { {-1,3}, {4,7}, {-1,-5}, {9,8} };

			Assert::IsFalse(IsRectangle(points));

		}

		TEST_METHOD(CheckPosQuadShape)
		{
			double points[4][2] = { {90,54}, {-94,53}, {-80,-65}, {7,-89} };

			Assert::IsFalse(IsRectangle(points));

		}
	};



	//Perimeter Tests -----------------------------------------------

	TEST_CLASS(PerimeterClockwiseFunctionalityTests) 
	{
	public:
		TEST_METHOD(CheckPerimeterSquare)
		{
			double points[4][2] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };
			double result = CalculatePerimeter(points);

			Assert::AreEqual(8.0, result);

		}

	
	};

	//Area Tests -----------------------------------------------

	TEST_CLASS(AreaClockwiseFunctionalityTests)
	{
	public:
		TEST_METHOD(CheckPerimeterSquare)
		{
			double points[4][2] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };

			double result = CalculateRectangleArea(points);

			Assert::AreEqual(4.0, result);

		}


	};



	//Triangle Functions======================================================

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
			int side1 = -0.5;
			int side2 = -0.5;
			int side3 = -0.5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}

		TEST_METHOD(CheckIfTriangleNegative2)
		{
			int side1 = -5;
			int side2 = -5;
			int side3 = -5;

			Assert::IsFalse(CanFormTriangle(side1, side2, side3));
		}


	};


	//Calculate angle tests ----------------------------------------------
}
