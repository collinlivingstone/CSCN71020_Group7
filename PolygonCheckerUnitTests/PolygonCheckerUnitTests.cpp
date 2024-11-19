#include "pch.h"
#include "CppUnitTest.h"

//Triangle testing functions
extern "C" void CalculateAngles(double, double, double, double*, double*, double*);
extern "C" int CanFormTriangle(double, double, double);
extern "C" void CalculateAngles(double, double, double, double*, double*, double*);

//Rectangle testing functions
extern "C" double distance(double, double, double, double);
extern "C" double DistanceSquared(double, double, double, double);
extern "C" bool IsRectangle(double points[4][2]);
extern "C" void RectangleSolver();

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolygonCheckerUnitTests
{
	TEST_CLASS(TriangleCheckerUnitTests)
	{
	public:
		
		//functionality Tests
		TEST_METHOD(TriangleCheckerFunctionalityTests)
		{

		}

		//exception tests
		TEST_METHOD(TriangleCheckerExceptionTests)
		{

		}

		//boundry tests/validation
		TEST_METHOD(TriangleCheckerBoundryTests)
		{

		}

	};

	TEST_CLASS(RectangleSolverUnitTests)
	{
	public:
		//functionality Tests
		TEST_METHOD(RectangleSolverFunctionalityTests)
		{

		}
		//exception tests
		TEST_METHOD(RectangleSolverExceptionTests)
		{

		}
		//boundry tests/validation
		TEST_METHOD(RectangleSolverBoundryTests)
		{

		}
	};
}
