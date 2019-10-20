#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2){
		fprintf( stderr, "Error: Unsufficient arguments!\n" );
		exit(EXIT_FAILURE); 
	} 
	else if(argc > 2){
		fprintf( stderr, "Error: Too many arguments!\n" );
		exit(EXIT_FAILURE);
	}

    string inFile = argv[1];         // string variable to get the input file format
//    string outFile = argv[2];        // string variable to get the output file format

    ifstream inStream;  //input file stream
    ofstream outStream; //output file stream

    inStream.open(inFile, ios::binary);

    double value;
    int i = 0;
    char buf[sizeof(double)];
    while (inStream.read(buf, sizeof(buf)))
    {
        memcpy(&value, buf, sizeof(value));
        std::cout << value << " ";
        i++;
    }

    std::cout << endl << "Total count: " << i << endl;

    inStream.close();

    return 0;
}