#include "Image.h"

#ifndef _FILTER_H_
#define _FILTER_H_
namespace imaging {
	class Filter {

	protected:
		int numberOfFilters;
		std::vector<std::string> filters;
	public:

		Filter() : numberOfFilters(0), filters({}) {}

		Filter(Filter &thefilter) {
			this->numberOfFilters = thefilter.numberOfFilters;
			for (unsigned int i = 0; i < thefilter.filters.size(); i++) {
				this->filters[i] = thefilter.filters[i];
			}
		}
		
		virtual Image operator << (const Image & image) = 0;
	};
}

#endif // !_FILTER_H_


