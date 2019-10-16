#include "Filter.h"

namespace imaging{
	class FilterGamma : public Filter {

	protected:
		float gamma;
	public:

		FilterGamma() : gamma(1.f) {}

		FilterGamma(float gamma) {
			this->gamma = gamma;
		}

		FilterGamma(const FilterGamma &fgamma) {
			this->gamma = fgamma.gamma;
		}

		Image operator << (const Image & image);
	};
}