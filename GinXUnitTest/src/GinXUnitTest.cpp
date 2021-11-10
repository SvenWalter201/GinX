#include "pch.h"
#include "CppUnitTest.h"
#include "GinX.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GinXUnitTest
{
	TEST_CLASS(GinXUnitTest)
	{
	public:
		
		TEST_METHOD(DynamicArray_Append) 
		{
			GinX::BufferLayout layout({});
			GinX::DynamicArray dynamicArray = GinX::DynamicArray(3);
			int index0 = 3, index1 = 4, index2 = 2, index3 = 8, index4 = 12;
			dynamicArray.Append(index0);
			dynamicArray.Append(index1);
			dynamicArray.Append(index2);

			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index2, dynamicArray.Get(2));

			dynamicArray.Append(index3);

			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index2, dynamicArray.Get(2));
			Assert::AreEqual(index3, dynamicArray.Get(3));

			dynamicArray.Append(index4);

			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index2, dynamicArray.Get(2));
			Assert::AreEqual(index3, dynamicArray.Get(3));
			Assert::AreEqual(index4, dynamicArray.Get(4));

			dynamicArray.Delete(2);
			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index3, dynamicArray.Get(2));
			Assert::AreEqual(index4, dynamicArray.Get(3));
			Assert::AreEqual(0, dynamicArray.Get(4));

			dynamicArray.Delete(3);
			Assert::AreEqual(0, dynamicArray.Get(3));

			dynamicArray.Delete(0);
			Assert::AreEqual(index1, dynamicArray.Get(0));
			Assert::AreEqual(index3, dynamicArray.Get(1));

			dynamicArray[0] = 20;
			Assert::AreEqual(20, dynamicArray.Get(0));
			Assert::AreEqual(20, dynamicArray[0]);
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