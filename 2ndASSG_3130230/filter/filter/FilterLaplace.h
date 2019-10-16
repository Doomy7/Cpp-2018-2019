#include "FilterBlur.h"

namespace imaging {
	class FilterLaplace : public FilterBlur {
		protected:

			//given kernel (weak results)
			//float laplace[3][3] = {{0.0f, 1.0f, 0.0f},{1.0f, -4.0f, 1.0f}, {0.0f, 1.0f, 0.0f }};
			
			//alternative kernel
			float laplace[3][3] = { {-1.0f, -1.0f, -1.0f}, {-1.0f, 4.0f, -1.0f}, {-1.0f, -1.0f, -1.0f } };

		public:
			//def constructor
			FilterLaplace(){}
			//copy constructor
			FilterLaplace(const FilterLaplace &lap) {}

			Image operator << (const Image & image);
		};
}

