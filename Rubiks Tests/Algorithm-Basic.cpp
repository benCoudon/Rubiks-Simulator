#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Algorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{
	TEST_CLASS(AlgorithmTests)
	{
	public:

		TEST_METHOD(Algorithm1)
		{
			std::string initialValue = "U U' r Lw2";
			std::string expectedValue = "U U' r l2";
			Algorithm alg(initialValue);
			Assert::AreEqual(expectedValue, alg.toStr());
		}

		TEST_METHOD(Algorithm2)
		{

			std::string initialValue = "U   U   x A";
			std::string expectedValue = "U U x .";
			Algorithm alg(initialValue);
			Assert::AreEqual(expectedValue, alg.toStr());
		}
	};
}
