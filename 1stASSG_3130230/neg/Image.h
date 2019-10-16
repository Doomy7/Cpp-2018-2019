//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _IMAGE
#define _IMAGE

#include "Color.h"
#include <string>
#include <fstream>
#include "ppm/ppm.h"

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
namespace imaging
{

//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Image class alone does not provide 
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure. 
	 *
	 * The internal buffer of an image object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */ 
	class Image
	{
	public:

	protected:
		Color * buffer;                              //! Holds the image data.

		unsigned int width, 						 //! The width of the image (in pixels)
			height;		                 //! The height of the image (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the image
		 */
		const unsigned int getWidth() const {
			return width;
		}

		/*! Returns the height of the image
		 */
		const unsigned int getHeight() const {
			return height;
		}

		// data accessors

		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal image data, but rather a pointer
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
		 */
		Color * getRawDataPtr() {
			//?CORRECT?//
			return &buffer[0];
		}

		/*! Obtains the color of the image at location (x,y).
		 *
		 *  The method should do any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get.
		 *  \param y is the (zero-based) vertical index of the pixel to get.
		 *
		 *  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		Color getPixel(unsigned int x, unsigned int y) const {
			if (x > width || y > height) {
				//return black
				return Color();
			}
			else {
				//to find pixel y-th row (row = times x width | plus column (column = x))
				return buffer[((y * width) + x)];
			}
		}

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		 *
		 *  The method should perform any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to set.
		 *  \param y is the (zero-based) vertical index of the pixel to set.
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setPixel(unsigned int x, unsigned int y, Color & value) {
			getPixel(x, y)[0] = value[0];
			getPixel(x, y)[1] = value[1];
			getPixel(x, y)[2] = value[2];
		}
		                                                         
		/*! Copies the image data from an external raw buffer to the internal image buffer. 
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the 
		 *  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the 
		 *  width or height of the image are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		 */
		void setData(const Color * & data_ptr) {
			//allocation buffer size <- array pointed by data_ptr
			buffer = new Color[width * height];
			for (unsigned i = 0; i < height*width; i++) {
				buffer[i] = data_ptr[i];
			}
		}

		// constructors and destructor

		/*! Default constructor.
		 * 
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Image() {
			buffer = nullptr;
			width = 0;
			height = 0;
		}
		
		/*! Constructor with width and height specification.
		 * 
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */ 
		Image(unsigned int width, unsigned int height) {
			width = width;
			height = height;
		}
		
		/*! Constructor with data initialization.
		 * 
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 * 
		 * \see setData
		 */ 
		Image(unsigned int width, unsigned int height, const Color * data_ptr) {
			Image(width, height);
			setData(data_ptr);
		}
		
		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Image(const Image &src) {
			Image(src.getWidth(), src.getHeight(), src.buffer);
		}
		
		/*! The Image destructor.
		 */
		~Image() {
			delete []buffer;
		}

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Image & operator = (const Image & right) {
			buffer = right.buffer;
			width = right.width;
			height = right.height;
		}

		/*!
		 * Loads the image data from the specified file, if the extension of the filename matches the format string.
		 *
		 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the 
		 * Image object is initialized, its contents are wiped out before initializing it to the width, height and data
		 * read from the file.
		 * 
		 * \param filename is the string of the file to read the image data from.
		 * \param format specifies the file format according to which the image data should be decoded from the file.
		 * Only the "ppm" format is a valid format string for now.
		 * 
		 * \return true if the loading completes successfully, false otherwise.
		 */
		bool load(const std::string & filename, const std::string & format) {
			//default init
			if(buffer != nullptr){
				delete[]buffer;
				Image();
			}
			else {
				Image();
			}
			//temporary for width / height
			int theImageWidth = width;
			int theImageHeight = height;
			//string to char array
			const char *filenamePointer = filename.c_str();
			//addresses of temp width height
			float * imagePointer = ReadPPM(filenamePointer, &theImageWidth, &theImageHeight);

			//if null
			if (imagePointer == nullptr) {
				return false;
			}
			//else
			else {
				//return the values to Image width height
				width = unsigned(theImageWidth);
				height = unsigned(theImageHeight);
				//allocating color buffer
				Color *imageColorArray = new Color[width * height];
				//float to color
				for (unsigned int i = 0; i < (width * height); i++) {
					Color pixelColor (imagePointer[3*i], imagePointer[3*i+1], imagePointer[3*i+2]);
					imageColorArray[i] = pixelColor;
				}
				//color pointer to buffer color
				const Color * dataPointer = imageColorArray;
				//set the data
				setData(dataPointer);
				//delete float pointer
				delete[] imagePointer;
				return true;
			}
		}

		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is not initialized, the method should return immediately with a false return value.
		*
		* \param filename is the string of the file to write the image data to.
		* \param format specifies the file format according to which the image data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool save(const std::string & filename, const std::string & format) {
			//if null
			if (buffer == nullptr) {
				return false;
			}
			//else
			else {
				//string to char
				const char *filenamePointer = filename.c_str();
				//allocate float pointer
				float * data = new float[3 * width*height];
				//color to float (negative image)
				Color white(1.f, 1.f, 1.f);
				for (unsigned int i = 0; i < width*height; i++) {
					Color negativeColor = white - buffer[i];
					data[i*3] = negativeColor[0];
					data[i*3 + 1] = negativeColor[1];
					data[i*3 + 2] = negativeColor[2];
				}
				bool ok = WritePPM(data, int(width), int(height), filenamePointer);
				//delete float pointer
				delete[]data;
				return ok;
			}
		}

	};

} //namespace imaging

#endif