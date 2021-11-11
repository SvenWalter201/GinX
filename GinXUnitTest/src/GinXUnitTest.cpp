#include "pch.h"
#include "CppUnitTest.h"
#include "GinX.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GinXUnitTest
{
	TEST_CLASS(GinXECSTest)
	{
	public:

		TEST_METHOD(ECS) 
		{
			GinX::Manager m = GinX::Manager();
			std::string name = "Player";
			uint32_t id =  m.CreateEntity(name);
			m.GetEntity(id);
			Assert::AreEqual(name, m.GetEntity(id).GetName());
		}
	};

	TEST_CLASS(GinXUnitTest)
	{
	public:
	
		TEST_METHOD(DynamicArray_char)
		{
			GinX::DynamicArray<char> dynamicArray(3);
			char
				index0 = 'a',
				index1 = 'b',
				index2 = 'c',
				index3 = 'd',
				index4 = 'e';
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
			//Assert::AreEqual('0', dynamicArray.Get(4));

			dynamicArray.Delete(3);
			//Assert::AreEqual('0', dynamicArray.Get(3));

			dynamicArray.Delete(0);
			Assert::AreEqual(index1, dynamicArray.Get(0));
			Assert::AreEqual(index3, dynamicArray.Get(1));

			char v = 'g';
			dynamicArray[0] = v;
			Assert::AreEqual(v, dynamicArray.Get(0));
			Assert::AreEqual(v, dynamicArray[0]);

			//check reserved slots
			uint32_t reserved = dynamicArray.Reserved();
			uint32_t act = 3;
			Assert::AreEqual(act, reserved);

			//reserve 2 more slots
			dynamicArray.Reserve(2);
			reserved = dynamicArray.Reserved();
			act = 5;
			Assert::AreEqual(act, reserved);
		}

		/*
		TEST_METHOD(DynamicArray_CustomType) 
		{
			struct CustomType
			{
				float Fl = 0.0f;
				uint32_t UI = 0;

				bool operator==(const CustomType& rhs) const {
					return rhs.Fl == Fl && rhs.UI == UI;
				}

				bool operator!=(const CustomType& rhs) const {
					return rhs.Fl != Fl || rhs.UI != UI;
				}
			};

			GinX::DynamicArray<CustomType> dynamicArray(3);
			CustomType 
				index0 = {0.3f, 0.1f}, 
				index1 = { 0.3f, 0.1f }, 
				index2 = { 0.3f, 0.1f }, 
				index3 = { 0.3f, 0.1f }, 
				index4 = { 0.3f, 0.1f };
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
			Assert::AreEqual({0.0f, 0}, dynamicArray.Get(4));

			dynamicArray.Delete(3);
			Assert::AreEqual({ 0.0f, 0 }, dynamicArray.Get(3));

			dynamicArray.Delete(0);
			Assert::AreEqual(index1, dynamicArray.Get(0));
			Assert::AreEqual(index3, dynamicArray.Get(1));

			CustomType v = { 20.0f, 10 };
			dynamicArray[0] = v;
			Assert::AreEqual(v, dynamicArray.Get(0));
			Assert::AreEqual(v, dynamicArray[0]);

			//check reserved slots
			uint32_t reserved = dynamicArray.Reserved();
			uint32_t act = 3;
			Assert::AreEqual(act, reserved);

			//reserve 2 more slots
			dynamicArray.Reserve(2);
			reserved = dynamicArray.Reserved();
			act = 5;
			Assert::AreEqual(act, reserved);
		}
		*/

		TEST_METHOD(DynamicArray_Append) 
		{
			GinX::BufferLayout layout({});
			GinX::DynamicArray<int> dynamicArray(3);
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
			//Assert::AreEqual(0, dynamicArray.Get(4));

			dynamicArray.Delete(3);
			//Assert::AreEqual(0, dynamicArray.Get(3));

			dynamicArray.Delete(0);
			Assert::AreEqual(index1, dynamicArray.Get(0));
			Assert::AreEqual(index3, dynamicArray.Get(1));

			dynamicArray[0] = 20;
			Assert::AreEqual(20, dynamicArray.Get(0));
			Assert::AreEqual(20, dynamicArray[0]);

			//check reserved slots
			uint32_t reserved = dynamicArray.Reserved();
			uint32_t act = 3;
			Assert::AreEqual(act, reserved);

			//reserve 2 more slots
			dynamicArray.Reserve(2);
			reserved = dynamicArray.Reserved();
			act = 5;
			Assert::AreEqual(act, reserved);
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