#include "FilterGamma.h"

namespace imaging {
	
	Image FilterGamma::operator<<(const Image & image)
	{
		Image newImage(image);
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			for (unsigned int i = 0; i < image.getWidth(); i++) {
				newImage(i, j)[0] = pow(newImage(i, j)[0], gamma);
				newImage(i, j)[1] = pow(newImage(i, j)[1], gamma);
				newImage(i, j)[2] = pow(newImage(i, j)[2], gamma);
			}
		}	
		return newImage;
	}
}
