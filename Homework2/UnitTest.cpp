#include "pch.h"
#include "CppUnitTest.h"
#include "../Project3/code.h"
#include "../Project3/code.cpp"
#include<cstring>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int f[100];
			memset(f, 0, sizeof f);
			int num1[6] = {0 ,1,2,3,4};
			Assert::AreEqual(10, solution(4, num1, f));
		}
		TEST_METHOD(TestMethod2)
		{
			int f[100];
			memset(f, 0, sizeof f);
			int num2[6] = { 0,1,-10,8 };
			Assert::AreEqual(8, solution(3, num2, f));
		}
		TEST_METHOD(TestMethod3)
		{
			int f[100];
			memset(f, 0, sizeof f);
			int num2[6] = { 0,-1,-2 };
			Assert::AreEqual(0, solution(2, num2, f));
		}
	};
}
