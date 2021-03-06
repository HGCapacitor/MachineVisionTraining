// FindEdges.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Magick++.h>
#include <iostream>

#include "Prewitt.h"

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Please provide an image to convert" << std::endl;
	}
	std::cout << "Going to convert " << argv[1] << std::endl;
	auto test = new Prewitt();

	Magick::Image Model = Magick::Image(argv[1]);
	Magick::Pixels PixColor(Model);
	std::cout << "Color picture is " << Model.columns() << "x" << Model.rows() << std::endl;
	std::cout << "Color channels: " << Model.channels() << std::endl;
	std::cout << "Color depth :" << Model.depth() << std::endl;
	std::cout << "Color has alpha channel: " << Model.alpha() << std::endl;
	std::cout << "Red Offset: " << PixColor.offset(Magick::PixelChannel::RedPixelChannel) << std::endl;
	std::cout << "Green Offset: " << PixColor.offset(Magick::PixelChannel::GreenPixelChannel) << std::endl;
	std::cout << "Blue Offset: " << PixColor.offset(Magick::PixelChannel::BluePixelChannel) << std::endl;
	Magick::Quantum * PixelsColor = PixColor.get(0, 0, Model.columns(), Model.rows());

	std::cout << "Classtype: " << Model.classType() << std::endl;

	Magick::Image BWModel(Model);
	BWModel.type(Magick::GrayscaleType);
	BWModel.write("F14bw.jpg");
	Magick::Pixels PixBW(BWModel);
	std::cout << "Black & White picture is " << BWModel.columns() << "x" << BWModel.rows() << std::endl;
	std::cout << "Black & White channels: " << BWModel.channels() << std::endl;
	std::cout << "Black & White depth: " << BWModel.depth() << std::endl;
	std::cout << "Black & White has alpha channel: " << BWModel.alpha() << std::endl;
	std::cout << "Gray Offset: " << PixColor.offset(Magick::PixelChannel::GrayPixelChannel) << std::endl;
	Magick::Quantum * PixelsBW = PixBW.get(0, 0, BWModel.columns(), BWModel.rows());

	for (unsigned int i(0); i < 4; ++i)
	{
		std::cout << "Color " << std::dec << PixelsColor[i] << " [0x" << std::hex << PixelsColor[i]
			<< "] Black & White " << std::dec << PixelsBW[i] << " [0x" << std::hex << PixelsBW[i] << "]  " << i << std::endl;
	}
	std::cout << std::dec;

	std::cout << "  convolve ..." << std::endl;
	Magick::Image convolvedH = Model;
	convolvedH.label("ConvolveH");
	{
		// 3x3 matrix
		const double kernel[] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
		convolvedH.convolve(3, kernel);
	}
	std::cout << "Write convovled output... " << std::endl;
	convolvedH.write("F14ConvolveH.jpg");

	Magick::Image convolvedV = Model;
	convolvedV.label("ConvolveV");
	{
		// 3x3 matrix
		const double kernel[] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
		convolvedV.convolve(3, kernel);
	}
	std::cout << "Write convovled output... " << std::endl;
	convolvedV.write("F14ConvolveV.jpg");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
