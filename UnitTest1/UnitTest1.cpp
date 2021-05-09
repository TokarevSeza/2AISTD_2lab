#include "pch.h"
#include "CppUnitTest.h"
#include "../2AISTD_lab2/Huffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		bool* code;
		char* decode;
		
		TEST_METHOD(test_1)
		{
			char str[] = { 'I','t','s',' ','n','o','t','h','i','n','g', ' ', 't', 'o', ' ', 's', 'e', 'e', ' ', 'h', 'e', 'r', 'e', '\n' };
			Huffman ForCode(str);
			int codeSize;
			int decodeSize;
			code = ForCode.Code(codeSize);
			decode = ForCode.Decode(decodeSize);
			for (size_t i = 0; i < decodeSize; i++)
			{
				Assert::AreEqual(str[i], decode[i]);
			}
		}
		TEST_METHOD(test_2)
		{
			char str[] = { 'S','t','o','p',' ','r','i','g','h','t',' ','t','h','e','r','e',',',' ','c','r','i','m','i','n','a','l',' ','s','k','u','m','!','\n' };
			Huffman ForCode(str);
			int codeSize;
			int decodeSize;
			code = ForCode.Code(codeSize);	
			decode = ForCode.Decode(decodeSize);
			for (size_t i = 0; i < decodeSize; i++)
			{
				Assert::AreEqual(str[i], decode[i]);
			}
		}
		TEST_METHOD(test_3)
		{
			char str[] = { 'H','e','l','l','o',' ','t','h','e','r','e',',','G','e','n','e','r','a','l',' ','K','e','n','o','b','i','\n' };
			Huffman ForCode(str);
			int codeSize;
			int decodeSize;
			code = ForCode.Code(codeSize);
			decode = ForCode.Decode(decodeSize);
			for (size_t i = 0; i < decodeSize; i++)
			{
				Assert::AreEqual(str[i], decode[i]);
			}
		}
	};
}
