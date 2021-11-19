#include "pch.h"
#include "CppUnitTest.h"
#include "GinX.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GinXUnitTest
{
	struct S1
	{
		float A, B, C; //size : 12 aligned Size: 16
	};

	struct S2
	{
		float A, B; //size : 8 aligned Size: 8
	};

	TEST_CLASS(GinXPoolAllocatorTest)
	{
	public:
		TEST_METHOD(PoolAllocator) 
		{
			auto poolAlloc = GinX::PoolAllocator(3, sizeof(S1));
			Assert::AreEqual(poolAlloc.GetPoolSize(), (size_t)48, 
				L"PoolAllocator is the wrong size");
		
			S1* s1 = static_cast<S1*>(poolAlloc.AllocateMemory(sizeof(S1)));
			if (s1 == nullptr)
			{
				Assert::IsFalse(true, L"Couldn't allocate s1");
				return;
			}
			new (s1) S1();

			S1* s1_1 = static_cast<S1*>(poolAlloc.AllocateMemory(sizeof(S1)));
			if (s1_1 == nullptr)
			{
				Assert::IsFalse(true, L"Couldn't allocate s1_1");
				return;
			}
			new (s1_1) S1();

			S1* s1_2 = static_cast<S1*>(poolAlloc.AllocateMemory(sizeof(S1)));
			if (s1_2 == nullptr)
			{
				Assert::IsFalse(true, L"Couldn't allocate s1_2");
				return;
			}
			new (s1_2) S1();

			poolAlloc.FreeMemory(s1_1, sizeof(S1));

			S2* s2 = static_cast<S2*>(poolAlloc.AllocateMemory(sizeof(S2)));
			if (s2 == nullptr)
			{
				Assert::IsFalse(true, L"Couldn't allocate s2");
				return;
			}
			new (s2) S2();

			poolAlloc.FreeMemory(s1_2, sizeof(S1));
			poolAlloc.FreeMemory(s1, sizeof(S1));
			poolAlloc.FreeMemory(s2, sizeof(S2));

		}
	};

	TEST_CLASS(GinXStackAllocatorTest)
	{
	public:

		TEST_METHOD(StackMarkers)
		{
			
			auto stackAlloc = GinX::StackAllocator(25);
			Assert::AreEqual(stackAlloc.GetStackSize(), (size_t)32,
				L"SizeAlignment didn't work");
			
			S1* s1 = static_cast<S1*>(stackAlloc.AllocateMemory(sizeof(S1)));
			if (s1 == nullptr)
			{
				Assert::IsFalse(true, L"Not enough Stack-Size_s1");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)16,
				L"Stack-Size is wrong");

			new (s1) S1();

			auto marker = stackAlloc.GetMarker();

			S2* s2 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2 == nullptr)
			{
				Assert::IsFalse(true, L"Not enough Stack-Size s2");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)24,
				L"Stack-Size is wrong");
			new (s2) S2();

			S2* s2_1 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2_1 == nullptr)
			{
				Assert::IsFalse(true, L"Not enough Stack-Size s2_1");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)32,
				L"Stack-Size is wrong");
			new (s2_1) S2();

			stackAlloc.FreeToMarker(marker);
			
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)16,
				L"Stack-Size is wrong");
			
			S2* s2_2 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2_2 == nullptr)
			{
				Assert::IsFalse(true, L"Not enough Stack-Size s2_2");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)24,
				L"Stack-Size is wrong");
			new (s2_2) S2();
			
			S2* s2_3 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2_3 == nullptr)
			{
				Assert::IsFalse(true, L"Not enough Stack-Size s2_2");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)32,
				L"Stack-Size is wrong");
			new (s2_3) S2();
			
			stackAlloc.Wipe();

			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)0,
				L"Stack-Size is wrong");
		}

		TEST_METHOD(StackAlloc) 
		{

			auto stackAlloc = GinX::StackAllocator(33);
			Assert::AreEqual(stackAlloc.GetStackSize(), (size_t)40,
				L"SizeAlignment didn't work");

			S1* s1 = static_cast<S1*>(stackAlloc.AllocateMemory(sizeof(S1)));
			if (s1 == nullptr)
			{
				Assert::IsFalse(true,
					L"Not enough Stack-Size_s1");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)16,
				L"Stack-Size is wrong");

			new (s1) S1();

			S2* s2 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2 == nullptr)
			{
				Assert::IsFalse(true,
					L"Not enough Stack-Size s2");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)24,
				L"Stack-Size is wrong");
			new (s2) S2();
			
			S2* s2_1 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2_1 == nullptr)
			{
				Assert::IsFalse(true,
					L"Not enough Stack-Size s2_1");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)32,
				L"Stack-Size is wrong");
			new (s2_1) S2();
			
			S2* s2_2 = static_cast<S2*>(stackAlloc.AllocateMemory(sizeof(S2)));
			if (s2_2 == nullptr)
			{
				Assert::IsFalse(true,
					L"Not enough Stack-Size s2_2");
				return;
			}
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)40,
				L"Stack-Size is wrong");
			new (s2_2) S2();

			stackAlloc.FreeMemory(s2_2, sizeof(S2));
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)32,
				L"Stack-Size is wrong");

			stackAlloc.FreeMemory(s2_1, sizeof(S2));
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)24,
				L"Stack-Size is wrong");

			stackAlloc.FreeMemory(s2, sizeof(S2));
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)16,
				L"Stack-Size is wrong");

			stackAlloc.FreeMemory(s1, sizeof(S1));
			Assert::AreEqual(stackAlloc.GetCurrentStackSize(), (size_t)0,
				L"Stack-Size is wrong");
		}
	};

	TEST_CLASS(GinXUnitTest)
	{
	public:

		int GetWrapper(GinX::DynamicArray<int> dynamicArray)
		{
			return dynamicArray.Get(0);
		}

		TEST_METHOD(DynamicArray_copyAndMove) 
		{
			GinX::DynamicArray<int> dynamicArray(3);
			dynamicArray.Append(3);
			int rWrapper = GetWrapper(dynamicArray);
			int r = dynamicArray.Get(0);

			Assert::AreEqual(rWrapper, 3);
			Assert::AreEqual(r, 3);


			GinX::DynamicArray<int> dynamicArray2(3);
			dynamicArray2.Append(4);
			
			//move dynamic array2 into the function, invalidating the original
			int rWrapper2 = GetWrapper(std::move(dynamicArray2));
			

			Assert::AreEqual(rWrapper2, 4);

			void* p = dynamicArray2.GetDataPointer();

			//check if original is invalidated correctly
			Assert::AreEqual(p, (void*)nullptr);
		}

		TEST_METHOD(DynamicArray_assignments) 
		{
			GinX::DynamicArray<float> dynamicArray1(2);
			dynamicArray1.Append(0.03f);
			GinX::DynamicArray<float> dynamicArray2;
			dynamicArray2 = dynamicArray1;
			GinX::DynamicArray<float> dynamicArray3;
			dynamicArray3 = std::move(dynamicArray2);

			Assert::AreEqual(dynamicArray3.Get(0), 0.03f);
		}

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

			dynamicArray.Del(2);
			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index3, dynamicArray.Get(2));
			Assert::AreEqual(index4, dynamicArray.Get(3));
			//Assert::AreEqual('0', dynamicArray.Get(4));

			dynamicArray.Del(3);
			//Assert::AreEqual('0', dynamicArray.Get(3));

			dynamicArray.Del(0);
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

			dynamicArray.Del(2);
			Assert::AreEqual(index0, dynamicArray.Get(0));
			Assert::AreEqual(index1, dynamicArray.Get(1));
			Assert::AreEqual(index3, dynamicArray.Get(2));
			Assert::AreEqual(index4, dynamicArray.Get(3));
			//Assert::AreEqual(0, dynamicArray.Get(4));

			dynamicArray.Del(3);
			//Assert::AreEqual(0, dynamicArray.Get(3));

			dynamicArray.Del(0);
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