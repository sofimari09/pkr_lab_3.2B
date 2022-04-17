#include "pch.h"
#include "CppUnitTest.h"
#include "../3.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student* p = new Student;
			p->prizv = "b";
			p->prog = 4;
			int s = BinSearch(p, 1, "b", 4, 4);
			Assert::AreEqual(s, -1);
		}
	};
}
