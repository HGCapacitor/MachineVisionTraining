#pragma once
#include <vector>

namespace EdgeDetectionTests
{
	class ConvolveTests;
}

class Prewitt
{
public:
	Prewitt();
	~Prewitt();
	friend class EdgeDetectionTests::ConvolveTests;

private:
	const std::vector<std::vector<uint32_t>> Convolve(
		const std::vector<std::vector<uint32_t>>& aImage,
		const std::vector<std::vector<uint32_t>>& aMask,
		unsigned char aStride = 1,
		bool aUsePadding = true);
};

