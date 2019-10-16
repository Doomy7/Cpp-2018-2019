#include "FilterLaplace.h"

namespace imaging {

	Image FilterLaplace::operator<<(const Image & image)
	{
		Image newImage(image);
		
		for (int i = 0; i < newImage.getWidth(); i++) {		
			for (int j = 0; j < newImage.getHeight(); j++) {
				//execute algorithm loop
				math::Vec3<float> cellValue ( 0.0f, 0.0f, 0.0f );
				//kernel 3 x 3
				for (int m = -1; m <= 1; m++) {
					for (int n = -1; n <= 1; n++) {
						if (i + m > -1 && j + n > -1 && i + m < newImage.getWidth() && j + n < newImage.getHeight()) {
							cellValue += newImage(i + m, j + n) * laplace[m + 1][n + 1];
						}
					}
				}			
				//clamping
				cellValue = cellValue.clampToUpperBound(1.0f);
				cellValue = cellValue.clampToLowerBound(0.0f);
				//then assign
				newImage(i, j) = cellValue;
			}
		}
		return newImage;
	}
}
