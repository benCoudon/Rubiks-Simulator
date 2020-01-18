#include "CppUnitTest.h"

#include <string>

#include "../Rubiks Simulator/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RubiksTests
{		
	TEST_CLASS(MoveFaceTest)
	{
	public:

		TEST_METHOD(U)
		{
			std::string initialValue = "U";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(UCCW)
		{
			std::string initialValue = "U'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(U2)
		{
			std::string initialValue = "U2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(ULower)
		{
			std::string initialValue = "u";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(ULowerCCW)
		{
			std::string initialValue = "u'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(ULower2)
		{
			std::string initialValue = "u2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Uw)
		{
			std::string initialValue = "Uw";
			std::string expectedValue = "u";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(UwCCW)
		{
			std::string initialValue = "Uw'";
			std::string expectedValue = "u'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(Uw2)
		{
			std::string initialValue = "Uw2";
			std::string expectedValue = "u2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(expectedValue, m.toStr());
		}

		TEST_METHOD(F)
		{
			std::string initialValue = "F";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(FCCW)
		{
			std::string initialValue = "F'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(F2)
		{
			std::string initialValue = "F2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(FLower)
		{
			std::string initialValue = "f";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(FLowerCCW)
		{
			std::string initialValue = "f'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(FLower2)
		{
			std::string initialValue = "f2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Fw)
		{
			std::string initialValue = "Fw";
			std::string efpectedValue = "f";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(efpectedValue, m.toStr());
		}

		TEST_METHOD(FwCCW)
		{
			std::string initialValue = "Fw'";
			std::string efpectedValue = "f'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(efpectedValue, m.toStr());
		}

		TEST_METHOD(Fw2)
		{
			std::string initialValue = "Fw2";
			std::string efpectedValue = "f2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(efpectedValue, m.toStr());
		}

		TEST_METHOD(R)
		{
			std::string initialValue = "R";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(RCCW)
		{
			std::string initialValue = "R'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(R2)
		{
			std::string initialValue = "R2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(RLower)
		{
			std::string initialValue = "r";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(RLowerCCW)
		{
			std::string initialValue = "r'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(RLower2)
		{
			std::string initialValue = "r2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Rw)
		{
			std::string initialValue = "Rw";
			std::string erpectedValue = "r";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(erpectedValue, m.toStr());
		}

		TEST_METHOD(RwCCW)
		{
			std::string initialValue = "Rw'";
			std::string erpectedValue = "r'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(erpectedValue, m.toStr());
		}

		TEST_METHOD(Rw2)
		{
			std::string initialValue = "Rw2";
			std::string erpectedValue = "r2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(erpectedValue, m.toStr());
		}

		TEST_METHOD(B)
		{
			std::string initialValue = "B";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(BCCW)
		{
			std::string initialValue = "B'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(B2)
		{
			std::string initialValue = "B2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(BLower)
		{
			std::string initialValue = "b";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(BLowerCCW)
		{
			std::string initialValue = "b'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(BLower2)
		{
			std::string initialValue = "b2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Bw)
		{
			std::string initialValue = "Bw";
			std::string ebpectedValue = "b";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(ebpectedValue, m.toStr());
		}

		TEST_METHOD(BwCCW)
		{
			std::string initialValue = "Bw'";
			std::string ebpectedValue = "b'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(ebpectedValue, m.toStr());
		}

		TEST_METHOD(Bw2)
		{
			std::string initialValue = "Bw2";
			std::string ebpectedValue = "b2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(ebpectedValue, m.toStr());
		}

		TEST_METHOD(L)
		{
			std::string initialValue = "L";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(LCCW)
		{
			std::string initialValue = "L'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(L2)
		{
			std::string initialValue = "L2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(LLower)
		{
			std::string initialValue = "l";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(LLowerCCW)
		{
			std::string initialValue = "l'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(LLower2)
		{
			std::string initialValue = "l2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Lw)
		{
			std::string initialValue = "Lw";
			std::string elpectedValue = "l";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(elpectedValue, m.toStr());
		}

		TEST_METHOD(LwCCW)
		{
			std::string initialValue = "Lw'";
			std::string elpectedValue = "l'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(elpectedValue, m.toStr());
		}

		TEST_METHOD(Lw2)
		{
			std::string initialValue = "Lw2";
			std::string elpectedValue = "l2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(elpectedValue, m.toStr());
		}

		TEST_METHOD(D)
		{
			std::string initialValue = "D";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(DCCW)
		{
			std::string initialValue = "D'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(D2)
		{
			std::string initialValue = "D2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(DLower)
		{
			std::string initialValue = "d";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(DLowerCCW)
		{
			std::string initialValue = "d'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(DLower2)
		{
			std::string initialValue = "d2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(initialValue, m.toStr());
		}

		TEST_METHOD(Dw)
		{
			std::string initialValue = "Dw";
			std::string edpectedValue = "d";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(edpectedValue, m.toStr());
		}

		TEST_METHOD(DwCCW)
		{
			std::string initialValue = "Dw'";
			std::string edpectedValue = "d'";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(edpectedValue, m.toStr());
		}

		TEST_METHOD(Dw2)
		{
			std::string initialValue = "Dw2";
			std::string edpectedValue = "d2";
			Move m;
			int validMove = m.setMove(initialValue);
			Assert::AreEqual(edpectedValue, m.toStr());
		}
	};
}
