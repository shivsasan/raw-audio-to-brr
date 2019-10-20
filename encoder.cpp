#include <iostream?
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
    string outFile = argv[2];        // string variable to get the output file format

    ifstream inStream;  //input file stream
    ofstream outStream; //output file stream
}