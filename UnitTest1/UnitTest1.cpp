#include "pch.h"
#include "CppUnitTest.h"
#include "../ReversePolishNotation/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestExpToRPN_SimpleAddition)
		{
			std::string result = expToRPN("3+4");
			Assert::AreEqual(std::string("34+"), result);
		}

		TEST_METHOD(TestCalculateRPN_SimpleAddition)
		{
			int result = calculateRPN("34+");
			Assert::AreEqual(7, result);
		}

		TEST_METHOD(TestExpToRPN_ComplexExpression)
		{
			std::string result = expToRPN("3+4*2/(1-5)+2");
			Assert::AreEqual(std::string("342*15-/+2+"), result);
		}

		TEST_METHOD(TestCalculateRPN_DivisionByZero)
		{
			auto func = [] { calculateRPN("42/0"); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(TestCalculateRPN_InvalidPostfixExpression)
		{
			auto func = [] { calculateRPN("34+*"); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(TestCalculateRPN_ComplexExpression)
		{
			int result = calculateRPN("342*15-/+2+");
			Assert::AreEqual(3, result);
		}

		TEST_METHOD(TestCalculateRPN_ZeroResult)
		{
			int result = calculateRPN("242/-");
			Assert::AreEqual(0, result);
		}
	};
}
