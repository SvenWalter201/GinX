#include "pch.h"
#include "CppUnitTest.h"
#include "GinX.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GinXUnitTest
{
	TEST_CLASS(GinXUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int i = 13, j = 1;
			int actual = i + j;
			Assert::AreEqual(actual, 13);
		}

		TEST_METHOD(TestMethod2)
		{
			int i = 13, j = 1;
			int actual = i + j;
			Assert::AreEqual(actual, 14);
		}
	};
}

class TestApplication : public GinX::Application
{

public:
	TestApplication()
	{
	}

	~TestApplication()
	{

	}
};

GinX::Application* GinX::CreateApplication()
{
	return new TestApplication();
}