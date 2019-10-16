#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "FilterGamma.h"
#include "FilterLinear.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"

using namespace std;
using namespace imaging;


int main(int argc, char* argv[]) {

	system("CLS");
	cout << "3130230 C++ 2nd Assignment" << endl;
	string fparam = "-f";
	if (argc > 3) {
		string file = argv[argc - 1];
		cout << "Processing command..." << endl;
		if (file.length() > 4) {
			
			string prefix(file.begin() + (file.length() - 4), file.end());
			if (prefix == ".ppm") {
				cout << "Valid file name" << endl;
				//reading file
				//load save print
				cout << "It is indeed ppm..." << endl;
				cout << "Reading " + file + "..." << endl;
				imaging::Image theImage;
				//if file loaded
				if (theImage.load(file, "ppm")) {
					cout << "File loaded!" << endl;
					cout << "Processing filter parameters..." << endl;
					for (int i = 1; i < argc - 1; i++) {	
						if (argv[i] == fparam) {
							i += 1;
							string filter(argv[i]);
							//GAMMA
							if (filter == "gamma") {
								i += 1;
								try {
									float gamma_force = stof(argv[i]);
									if (gamma_force > 2.f || gamma_force < 0.5f) {
										cerr << "Wrong gamma value -> correct range 0.5 - 2.0" << endl;
										return -2;
									}
									imaging::FilterGamma gamma(gamma_force);
									theImage = gamma << theImage;				
								}
								catch (string e) {
									cerr << "Wrong gamma value" << e << endl;
									return -2;
								}
							}
							//LINEAR
							else if (filter == "linear") {
								i += 1;
								try {
									math::Vec3<float> a (stof(argv[i]), stof(argv[i + 1]), stof(argv[i + 2]));
									math::Vec3<float> c (stof(argv[i + 3]), stof(argv[i + 4]), stof(argv[i + 5]));
									imaging::FilterLinear linear(a, c);
									theImage = linear << theImage;
									i += 5;
								}catch (string e){
									cerr << "Linear filter parameter error" << e << endl;
									return -2;
								}						
							}
							//LAPLACE
							else if (filter == "laplace") {
								imaging::FilterLaplace laplace;
								theImage = laplace << theImage;
							}
							//BLUR
							else if (filter == "blur") {
								i += 1;
								try {
									int blur_weight = stoi(argv[i]);
									imaging::FilterBlur blur(blur_weight);

									theImage = blur << theImage;
								}
								catch (string e) {
									cerr << "Wrong gamma value" << e << endl;
									return -2;
								}
							}
							else {
								cerr << "Unknown or unsupported filter" << endl;
								return -1;
							}
						}
						else {
							cerr << "Wrong command input" << endl;
							cout << "Reference command" << endl;
							cout << "filter -f [filter 1] [param] … -f [filter2 k] [param] [image file name]" << endl;
						}
					}
					cout << "Creating filtered image..." << endl;
					if (theImage.save("filtered_" + file, "ppm")) {
						cout << "Filtered created!" << endl;
						cout << "Image dimensions are: " << theImage.getWidth() << "x" << theImage.getHeight() << endl;
						cout << "Filtered file saved as " << "filtered_" + file << endl;
						return 0;
					}
				}
				
			}
			else {
				cerr << "Wrong file type" << endl;
				return -1;
			}
		}
		else {
			cerr << "Not valid file" << endl;
			return -1;
		}	
	}
	return -666;
}

