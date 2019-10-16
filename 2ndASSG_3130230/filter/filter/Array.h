#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
#include <vector>

namespace math {

	template <class T>

	class Array {

		protected:

			std::vector<T> buffer;
			unsigned int width, height;

		public:

			// metric accessors

			/*! Returns the width of the image
			 */
			const unsigned int getWidth() const {
				return this->width;
			}

			/*! Returns the height of the image
			 */
			const unsigned int getHeight() const {
				return this->height;
			}

			// data accessors

			/*! Obtains a pointer to the internal data.
			 *
			 *  This is NOT a copy of the internal image data, but rather a pointer
			 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
			 */
			std::vector<T> * getRawDataPtr() {
				return &buffer.at[0];
			}

			/*! Obtains the color of the image at location (x,y).
			 *
			 *  The method should do any necessary bounds checking.
			 *
			 *  \param x is the (zero-based) horizontal index of the cell to get.
			 *  \param y is the (zero-based) vertical index of the cell to get.
			 *
			 *  \return The color of the (x,y) cell as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
			*/
			T getCell(unsigned int x, unsigned int y) const {
				if (x > width || y > height) {
					return T();
				}
				else {
					return this->buffer.at((y * this->width) + x);
				}
			}

			// data mutators

			/*! Sets the RGB values for an (x,y) cell.
			 *
			 *  The method should perform any necessary bounds checking.
			 *
			 *  \param x is the (zero-based) horizontal index of the cell to set.
			 *  \param y is the (zero-based) vertical index of the cell to set.
			 *  \param value is the new color for the (x,y) cell.
			 */
			void setCell(unsigned int x, unsigned int y, T & value) {
				getCell(x, y) = value;
			}
	
			/*! Copies the image data from an external raw buffer to the internal image buffer.
			 *
			 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
			 *  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
			 *  width or height of the image are 0, the method should exit immediately.
			 *
			 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
			 */
			void setData(const T * & data_ptr) {
				buffer.resize(width*height);
				for (unsigned i = 0; i < buffer.size(); i++) {
					this->buffer[i] = data_ptr[i];
				}
			}

			// constructors and destructor

			/*! Default constructor.
			 *
			 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
			 */
			Array() {
				this->buffer = {};
				this->width = 0;
				this->height = 0;
			}

			/*! Constructor with width and height specification.
			 *
			 * \param width is the desired width of the new image.
			 * \param height is the desired height of the new image.
			 */
			Array(unsigned int width, unsigned int height) {
				this->width = width;
				this->height = height;
			}

			/*! Constructor with data initialization.
			 *
			 * \param width is the desired width of the new image.
			 * \param height is the desired height of the new image.
			 * \param data_ptr is the source of the data to copy to the internal image buffer.
			 *
			 * \see setData
			 */
			Array(unsigned int width, unsigned int height, const T * data_ptr) {
				this->width = width;
				this->height = height;
				setData(data_ptr);
			}

			/*! Copy constructor.
			 *
			 * \param src is the source image to replicate in this object.
			 */
			Array(const Array &src) {
				this->width = src.width;
				this->height = src.height;
				this->buffer.resize(width * height);
				for (unsigned i = 0; i < buffer.size(); i++) {
					buffer[i] = src.buffer[i];
				}
			}

			/*! The Image destructor.
			 */
			~Array() {
				this->buffer.clear();
			}

			/*! Copy assignment operator.
			 *
			 * \param right is the source image.
			 */
			Array & operator = (const Array & right) {
				this->width = right.width;
				this->height = right.height;
				this->buffer.resize(width * height);
				for (unsigned i = 0; i < height*width; i++) {
					this->buffer[i] = right.buffer[i];
				}			
				return *this;
			}
			
			/* Parenthesis operator.
			*
			* \get cell value at coordinate y * width + x
			*/
			T & operator () (unsigned int i, unsigned int j) {
				return this->buffer.at((j * this->width) + i);
			}
	};
}
#endif