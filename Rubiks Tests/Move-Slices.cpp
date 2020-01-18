#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{
	TEST_CLASS(MoveSliceTest)
	{
	public:

		TEST_METHOD(SliceM)
		{
			std::string initialValue = "M";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceMCCW)
		{
			std::string initialValue = "M'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceM2)
		{
			std::string initialValue = "M2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceS)
		{
			std::string initialValue = "S";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceSCCW)
		{
			std::string initialValue = "S'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceS2)
		{
			std::string initialValue = "S2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceE)
		{
			std::string initialValue = "E";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceECCW)
		{
			std::string initialValue = "E'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(SliceE2)
		{
			std::string initialValue = "E2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}
	};
}
