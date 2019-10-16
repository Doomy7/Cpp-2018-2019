#include <string>
#include "Image.h"
#include "ppm.h"

namespace imaging{

	bool Image::load(const std::string & filename, const std::string & format) {
		//default init
		if (!this->buffer.empty()) {
			this->buffer.clear();
			Image();
		}
		else {
			Image();
		}
		//temporary for width / height
		int vectorWidth = width;
		int vectorHeight = height;
		//string to char array
		const char *filenamePointer = filename.c_str();
		//addresses of temp width height
		float * vecPointer = ReadPPM(filenamePointer, &vectorWidth, &vectorHeight);

		//if null
		if (vecPointer == nullptr) {
			return false;
		}
		//else
		else {
			//return the values to Image width height
			this->width = unsigned(vectorWidth);
			this->height = unsigned(vectorHeight);
			//allocating color buffer
			math::Vec3<float> * VecArray = new math::Vec3<float>[width * height];
			//float to color
			for (unsigned int i = 0; i < (width * height); i++) {
				math::Vec3<float> pixelColor(vecPointer[3 * i], vecPointer[3 * i + 1], vecPointer[3 * i + 2]);
				VecArray[i] = pixelColor;
			}
			//color pointer to buffer color
			const math::Vec3<float> * dataPointer = VecArray;
			//set the data
			this->setData(dataPointer);
			//delete float pointer
			delete[]dataPointer;
			return true;
		}
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		//if null
		if (this->buffer.empty()) {
			return false;
		}
		//else
		else {
			//string to char
			const char *filenamePointer = filename.c_str();
			//allocate float pointer
			float * data = new float[3 * width*height];

			for (unsigned int i = 0; i < width*height; i++) {
				data[i * 3] = buffer[i][0];
				data[i * 3 + 1] = buffer[i][1];
				data[i * 3 + 2] = buffer[i][2];
			}
			bool ok = WritePPM(data, int(width), int(height), filenamePointer);
			//delete float pointer
			delete[] data;
			return ok;
		}
	}

}
