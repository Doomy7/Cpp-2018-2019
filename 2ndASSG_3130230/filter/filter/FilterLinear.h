#include "Filter.h"

namespace imaging {
	class FilterLinear : public Filter {

	protected:
		math::Vec3<float> a, c;
	public:

		FilterLinear() : a({ 1, 1, 1 }), c({ 0, 0, 0 }) {}

		FilterLinear(math::Vec3<float> a, math::Vec3<float> c) {
			this->a = a;
			this->c = c;
		}

		FilterLinear(const FilterLinear &linearFilter) {
			this->a = linearFilter.a;
			this->c = linearFilter.c;
		}

		Image operator << (const Image & image);

	};
}