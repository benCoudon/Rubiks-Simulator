#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{
	TEST_CLASS(MoveInvalidTest)
	{
	public:

		TEST_METHOD(EMPTY)
		{
			std::string expectedValue = ".";
			Move m;
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(A)
		{
			std::string initialValue = "A";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(FF)
		{
			std::string initialValue = "FF";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(DoubleWide)
		{
			std::string initialValue = "uw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		// Wide moves on rotations should be invalid
		TEST_METHOD(XWide)
		{
			std::string initialValue = "xw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(XWideUpper)
		{
			std::string initialValue = "Xw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(YWide)
		{
			std::string initialValue = "yw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(YWideUpper)
		{
			std::string initialValue = "Yw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(ZWide)
		{
			std::string initialValue = "zw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(ZWideUpper)
		{
			std::string initialValue = "Zw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		// Wide moves on slices should be invalid
		TEST_METHOD(MWide)
		{
			std::string initialValue = "Mw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(EWide)
		{
			std::string initialValue = "Ew";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(SWide)
		{
			std::string initialValue = "Sw";
			std::string expectedValue = ".";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}
	};
}
