#include <iostream>
#include "FilterLinear.h"

namespace imaging {
	
	Image FilterLinear::operator<<(const Image & image)
	{
		Image newImage(image);
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			for (unsigned int i = 0; i < image.getWidth(); i++) {
				newImage(i, j) = a* newImage(i,j) + c;	
				newImage(i, j) = newImage(i, j).clampToUpperBound(1.0f);
				newImage(i, j) = newImage(i, j).clampToLowerBound(0.0f);
			}
		}
		return newImage;
	}

}