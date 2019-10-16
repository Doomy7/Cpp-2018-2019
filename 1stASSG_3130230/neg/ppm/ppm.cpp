#include <fstream>
#include <iostream>
#include <string>
#include "ppm.h"

float * imaging::ReadPPM(const char * filename, int * w, int * h){

	std::string ppmFormat, width, height, max;
	std::fstream ppmImage(filename, std::ios::in | std::ios::binary);
	//Try opening file
	if (ppmImage.is_open()) {
		//Reading the basics
		ppmImage >> ppmFormat >> width >> height >> max;
		//Secondary validations
		if (ppmFormat == "P6") {
			try {
				if (stoi(width) > 0 && stoi(height) > 0) {
					try {
						if (stoi(max) == 255) {
							//returning values to width and  height
							*w = stoi(width);
							*h = stoi(height);
							//token for ppmImage.get()
							char color;
							char r, g, b;
							//initialize constant size of array and the pointer to it
							const unsigned int arrayLength = 3 * stoi(width)*stoi(height);
							float *pixelColorArray = new float[arrayLength];
							//position correction
							ppmImage.seekg(1, std::ios_base::cur);
							for (unsigned int i = 0; i < stoi(width)*stoi(height); i++) {
								ppmImage.get(color);//r
								pixelColorArray[3 * i] = (1.0f / 255) * color;
								ppmImage.get(color);//g
								pixelColorArray[3 * i + 1] = (1.0f / 255) * color;
								ppmImage.get(color);//b
								pixelColorArray[3 * i + 2] = (1.0f / 255) * color;
							}
							//close filestream
							ppmImage.close();
							//return pointer
							return pixelColorArray;
						}
						/* bit format error */
						else {
							std::cerr << "Unsupported bit format" << std::endl;
							ppmImage.close();
							return nullptr;
						}
					}
					catch (std::invalid_argument& ia) {
						std::cerr << "Something wrong bit format ->" << ia.what() << std::endl;
						ppmImage.close();
						return nullptr;
					}
				}
				/* width or height error */
				else {
					std::cerr << "Something wrong with dimensions" << std::endl;
					ppmImage.close();
					return nullptr;
				}
			}
			catch (std::invalid_argument& ia) {
				std::cerr << "Something wrong with dimensions ->" << ia.what() << std::endl;
				ppmImage.close();
				return nullptr;
			}
		}
		/* wrong format error */
		else {
			std::cerr << "Wrong or unsupported format" << std::endl;
			ppmImage.close();
			return nullptr;
		}
	}
	/* read error */
	else {
		std::cerr << "File read error" << std::endl;
		ppmImage.close();
		return nullptr;
	}
	
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename){

	//Buffer is null check
	if (data == nullptr) {
		std::cerr << "Buffer is null" << std::endl;
		return false;
	}
	else {
		//open file for reading
		std::fstream ppmImage(filename, std::ios::out | std::ios::binary);
		if (ppmImage.is_open()) {
			//Printing info for file description
			ppmImage << "P6" << " " << w << " " << h << " " << 255 << "\n";
			unsigned char r, g, b;
			//calculate the negative then to byte conversion
			for (unsigned i = 0; i < h*w; i++) {
				r = data[3*i] * 255;
				g = data[3*i + 1] * 255;
				b = data[3*i + 2] * 255;
				//writing data
				ppmImage << r << g << b;
			}
			//closing stream
			ppmImage.close();
			return true;
		}
		else {
			//file read/write error
			std::cerr << "File read/write error" << std::endl;
			ppmImage.close();
			return false;
		}
	}
}
