#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Image.h"

using namespace std;

int main(int argc, char* argv[]) {

	system("CLS");
	cout << "3130230 C++ 1st Assignment" << endl;
	//if more/less arguments not valid command
	if (argc < 0 || argc > 2) {
		cerr << "Wrong command. Exiting..." << endl;
		return -1;
	}
	//1st method of execution ''neg''
	else if (argc == 1) {
		string input;
		cout << "command >> " << argv[0] << endl;
		cout << "File name of the image to load: ";
		//reading filename
		while (true) {
			cin >> input;
			if (input.length() > 4) {
				string filename(input.begin(), input.end() - 4);
				string prefix(input.begin() + (input.length() - 4), input.end());
				//check if valid prefix and check until correct given
				if (prefix != ".ppm") {
					cerr << "Wrong file format. Try again..." << "\n>>";
				}
				else {
					//load save print
					cout << "Reading " + filename + "..." << endl;
					imaging::Image theImage;
					//if image loaded
					if (theImage.load(input, "ppm")) {
						//if image saved
						cout << "Image loaded!" << endl;
						cout << "Creating negative..." << endl;
						if (theImage.save(filename + "_neg.ppm", "ppm")) {
							cout << "Negative created!" << endl;
							cout << "Negative file saved as " << filename + "_neg.ppm" << endl;
							return 0;
						}
					}
					return -2;
				}
			}
			else {
				cerr << "Wrong input. Try again... \n>>" << endl;
			}
		}
	//2nd method of execution ''neg (file)''
	} else {
		cout << "command >> " << argv[0] << " " << argv[1] << endl;
		//getting filename from arguments
		string file(argv[1]);
		if (file.length() > 4) {
			string filename(file.begin(), file.end() - 4);
			string prefix(file.begin() + (file.length() - 4), file.end());
			//check if prefix valid
			if (prefix != ".ppm") {
				cerr << "Wrong file format. Exiting..." << endl;
				return -1;
			}
			else {
				//load save print
				cout << "It is indeed ppm..." << endl;
				cout << "Reading " + file + "..." << endl;
				imaging::Image theImage;
				//if file loaded
				if (theImage.load(file, "ppm")) {
					//if image saved
					cout << "Image loaded!" << endl;
					cout << "Creating negative..." << endl;
					if (theImage.save(filename + "_neg.ppm", "ppm")) {
						cout << "Negative created!" << endl;
						cout << "Image dimensions are: " << theImage.getWidth() << "x" << theImage.getHeight() << endl;
						cout << "Negative file saved as " << filename + "_neg.ppm" << endl;
						return 0;
					}
				}
			}
		}
		else {
			cerr << "Wrong file input. Exiting..." << endl;
			return -2;
		}
	}
	//you should not have come here
	return -2;
}