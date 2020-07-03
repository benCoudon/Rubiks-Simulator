#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Cube.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{
	TEST_CLASS(CubeTests)
	{
	public:

		TEST_METHOD(Cube1)
		{
			Cube cubeA(Algorithm("U U"));
			Cube cubeB(Algorithm("U2"));
			cubeA.executeAlg();
			cubeB.executeAlg();
			Assert::AreEqual(cubeA == cubeB, true);
		}
	};
}
