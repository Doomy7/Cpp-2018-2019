#include "Filter.h"
#include "Array.h"

#ifndef _FILTERBLUR_H_
#define _FILTERBLUR_H_
namespace imaging {
	class FilterBlur : public Filter, math::Array<float> {
	protected:
		int N;
		math::Array<float> blur;
	public:

		FilterBlur() : N(1) {
			math::Array<float>();
		}

		FilterBlur(int N) {
			
			float *fpointer = new float[N*N];
			this->N = N;
			for (int i = 0; i < N*N; i++) {
				fpointer[i] = float(1/pow(N,2));
			}
			const float * dataPointer = fpointer;
			math::Array<float> temp(N, N, dataPointer);
			this->blur = temp;
		}

		FilterBlur(const FilterBlur &blur) {
			this->N = blur.N;
			this->width = blur.width;
			this->height = blur.height;
			this->buffer = blur.buffer;
		}

		Image operator << (const Image & image);
	};

}
#endif // !_FILTERBLUR_H_



