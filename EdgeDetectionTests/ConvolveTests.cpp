#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../EdgeDetection/Prewitt.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EdgeDetectionTests
{		
	TEST_CLASS(ConvolveTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto image = std::vector<std::vector<uint32_t>>
			{
				std::vector<uint32_t> {1,2,3,4,5,6},
				std::vector<uint32_t> {2,3,4,5,6,7},
				std::vector<uint32_t> {3,4,5,6,7,8},
				std::vector<uint32_t> {4,5,6,7,8,9},
				std::vector<uint32_t> {5,6,7,8,9,10},
				std::vector<uint32_t> {6,7,8,9,10,11}
			};
			auto mask = std::vector<std::vector<uint32_t>>
			{
				std::vector<uint32_t> {1,1,1},
				std::vector<uint32_t> {0,0,0},
				std::vector<uint32_t> {1,1,1}
			};
			auto expectedResult = std::vector < std::vector<uint32_t>>
			{
				std::vector<uint32_t> {5,9,12,15,18,13},
				std::vector<uint32_t> {10,18,24,30,36,26},
				std::vector<uint32_t> {14,24,30,36,42,30},
				std::vector<uint32_t> {18,30,36,42,48,34},
				std::vector<uint32_t> {22,36,42,48,54,38},
				std::vector<uint32_t> {11,18,21,24,27,19}
			};

			Prewitt specimen = Prewitt();
			auto result = specimen.Convolve(image, mask);
			Assert::IsTrue(expectedResult == result);
		}
	};
}