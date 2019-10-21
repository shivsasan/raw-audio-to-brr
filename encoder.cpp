#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

string convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i+=8) { 
        s = s + a[i]; 
    } 
    return s; 
} 

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

    inStream.open(inFile);//, ios::binary);

//    float value;
//    int i = 0; 
/*    char buf[sizeof(float)];
    while (inStream.read(buf, sizeof(float)))
    {
        memcpy(&value, buf, sizeof(value));
        std::cout << value << " ";
        float temp =  stof (buf);
        cout<<"this is a float value -> "<< temp<<endl; 
        i++;
    }*/
    
    int index = 0;          // array index
    char currentArr[256];   // 9-byte block
    char inChar;            // current char from the read

    while(!inStream.eof())  //loops till the end of file
    {
        index = 0;          // array index
        //currentArr[256];          // 9-byte block
        //inChar = '';            // current char from the read 

        while (inStream.get(inChar) && index < 256) //get 1 byte at a time
        {
            if(inChar == ' ')   //skip space character
            {
                inStream.get(inChar);
            }
//            cout<<inChar;
            currentArr[index] = inChar; // move the read char to the current 32 byte sample
            index = index + 8;          //increment by 1 byte at a time
        }
    
        cout<<endl;
        currentArr[256] = '\0';
        string daString = convertToString(currentArr,256);
//      cout<<currentArr[0]<<currentArr[8]<<currentArr[16]<<currentArr[24]<<endl;       //first 4 bytes of currentArr
//      cout<<currentArr[32]<<currentArr[40]<<currentArr[48]<<currentArr[56]<<endl;     //second 4 bytes of currentArr

        cout << "index: " << index <<endl;
        cout <<"strBro: " << daString <<endl;
    }

//    cout<< "converted:" << stof currentArr)<<endl;

//   std::cout << endl << "Total count: " << i << endl;

    inStream.close();       //close connection with file

    return 0;
}