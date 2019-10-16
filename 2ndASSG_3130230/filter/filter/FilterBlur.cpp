#include "FilterBlur.h"
namespace imaging {
	
	Image FilterBlur::operator<<(const Image & image)
	{
		Image newImage(image);
		// when N%2 != 0 loop omits pixels 
		int upperbound;
		if (N % 2 == 0) {
			upperbound = N / 2;
		}
		else {
			upperbound = (N / 2) + 1;
		}
		//scan whole image
		for (int i = 0; i < newImage.getWidth(); i++) {
			for (int j = 0; j < newImage.getHeight(); j++) {
				//init black cell
				math::Vec3<float> cellValue(0.f, 0.f, 0.f);
				//execute algorithm loop
				for (int m = -N / 2; m < upperbound; m++) {
					for (int n = -N / 2; n < upperbound; n++) {
						//check boundaries
						if (i+m > -1 && j+n > -1 && i+m < newImage.getWidth() && j+n < newImage.getHeight()) {
							//sum values
							cellValue += newImage(i + m, j + n) * blur(m + (N / 2), n + (N / 2));
						}
					}
				}
				//new cell value
				newImage(i, j) = cellValue;

			}
		}
		return newImage;
	}
}