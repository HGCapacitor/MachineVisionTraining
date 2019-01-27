#include "stdafx.h"
#include "Prewitt.h"

Prewitt::Prewitt()
{
}


Prewitt::~Prewitt()
{
}

/*private*/ const std::vector<std::vector<uint32_t>> Prewitt::Convolve(
	const std::vector<std::vector<uint32_t>>& aImage,
	const std::vector<std::vector<uint32_t>>& aMask)
{
	//Check mask size, must be uneven square
	size_t maskSize = aMask.size();
	size_t maskMid = (maskSize - 1) / 2;
	bool maskIsValid = maskSize % 2 == 1 && (aMask.size() == aMask[0].size());

	auto output = std::vector<std::vector<uint32_t>>();
	for (size_t imageY(0); imageY < aImage.size(); ++imageY)
	{
		output.push_back(std::vector<uint32_t>());
		for (size_t imageX(0); imageX < aImage[0].size(); ++imageX)
		{
			uint32_t value = 0;
			for (size_t maskY(0); maskY < maskSize; ++maskY)
			{
				if ((imageY + maskY) < maskMid) continue;
				if ((imageY + maskY) > (aImage.size() - 1 + maskMid)) continue;
				for (size_t maskX(0); maskX < maskSize; ++maskX)
				{
					if ((imageX + maskX) < maskMid) continue;
					if ((imageX + maskX) > (aImage[0].size() - 1 + maskMid)) continue;
					size_t imageYRead = imageY + maskY - maskMid;
					size_t imageXRead = imageX + maskX - maskMid;
					value += aImage[imageYRead][imageXRead] * aMask[maskY][maskX];
				}
			}
			output.back().push_back(value);
		}
	}
	return output;
}