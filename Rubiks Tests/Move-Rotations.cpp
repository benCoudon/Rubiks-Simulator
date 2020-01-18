#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{
	TEST_CLASS(MoveRotationTest)
	{
	public:

		TEST_METHOD(X)
		{
			std::string initialValue = "x";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(XUpper)
		{
			std::string initialValue = "X";
			std::string expectedValue = "x";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(XCCW)
		{
			std::string initialValue = "x'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(XUpperCCW)
		{
			std::string initialValue = "X'";
			std::string expectedValue = "x'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(X2)
		{
			std::string initialValue = "x2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Y)
		{
			std::string initialValue = "y";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(YUpper)
		{
			std::string initialValue = "Y";
			std::string eypectedValue = "y";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(eypectedValue, m.toStr());
		}

		TEST_METHOD(YCCW)
		{
			std::string initialValue = "y'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(YUpperCCW)
		{
			std::string initialValue = "Y'";
			std::string eypectedValue = "y'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(eypectedValue, m.toStr());
		}

		TEST_METHOD(Y2)
		{
			std::string initialValue = "y2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Z)
		{
			std::string initialValue = "z";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(ZUpper)
		{
			std::string initialValue = "Z";
			std::string ezpectedValue = "z";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(ezpectedValue, m.toStr());
		}

		TEST_METHOD(ZCCW)
		{
			std::string initialValue = "z'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(ZUpperCCW)
		{
			std::string initialValue = "Z'";
			std::string ezpectedValue = "z'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(ezpectedValue, m.toStr());
		}

		TEST_METHOD(Z2)
		{
			std::string initialValue = "z2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}
	};
}
