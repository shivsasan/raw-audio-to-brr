#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>

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

void quantize(int arr[], int range)
{
    cout<<"quaztize1"<<endl;
    int step_size[13] = {1,2,4,8,16,32,64,256,512,1024,2048,4096};
    for (int i = 0; i < 16 ; i++)
    {
        cout<<"arr["<<i<<"]: "<<arr[i]<<endl;
        cout<<"stepsize: "<<step_size[range]<<endl;
        cout<<"range : "<<range<<endl;
        arr[i] = arr[i]/(step_size[range]);
        cout<<arr[i]<<" ";
    }
    cout<<"quaztize2"<<endl;

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

    inStream.open(inFile, ios::binary);
    outStream.open("out.brr");

    float value;
    vector <float> converted;
    int scale = 32768; //scale
    unsigned char temp[sizeof(float)];
    int currentArr[16]; // each index holds 16 bit ints
    int iter = 0;
    int max, min;
    int range;
//    int step_size[13] = {1,2,4,8,16,32,64,256,512,1024,2048,4096};

    while(inStream.read(reinterpret_cast < char*> (temp), sizeof(float)))
    {       
        unsigned char t  = temp[0];
        temp[0] = temp[3];
        temp[3] = t;
        t = temp[1];
        temp[1] = temp[2];
        temp[2] = t;
        value = reinterpret_cast<float&>(temp);
 //       cout<<"iter: "<<iter<<"\tvalue: "<<value<<endl;
        if(value > 1 || value < -1)
        {
            cout<<"out of range"<<endl;
            break;
        }
        //converted.push_back(int(value*scale));
        if (iter <= 15)
        {
            currentArr[iter] = int(value*scale);
//            cout<<currentArr[iter]<<endl;
        }
        if (iter == 16 ) //after 16 samples
        {
            iter = 0;   //reset iter
            max = *max_element(currentArr,currentArr+16);
            min = *min_element(currentArr,currentArr+16);

            cout<<"max: " << max<<" min: "<<min<<endl; 

            //range here

            if ( max <= 7 && min >= -8 ){range = 0;}
            if ( max <= 14 && min >= -16 ){range = 1;}
            if ( max <= 28 && min >= -32 ){range = 2;}
            if ( max <= 56 && min >= -64 ){range = 3;}
            if ( max <= 112 && min >= -128 ){range = 4;}
            if ( max <= 224 && min >= -256 ){range = 5;}
            if ( max <= 448 && min >= -512 ){range = 6;}
            if ( max <= 896 && min >= -1024 ){range = 7;}
            if ( max <= 1792 && min >= -2048 ){range = 8;}
            if ( max <= 3584 && min >= -4096 ){range = 9;}
            if ( max <= 7168 && min >= -8192 ){range = 10;}
            if ( max <= 14336 && min >= -16384 ){range = 11;}
            if ( max <= 28672 && min >= -32768 ){range = 12;}
            else{cout<<"OUT OF RANGE!!!"<<endl;}

            //if (range != 0){quantize(currentArr,range);} //quantizing to nibble
            quantize(currentArr,range);

            continue;
        }
        iter++;
//        cout<<"iter: "<<iter<<endl;

    }

    for (auto i = converted.begin(); i != converted.end(); ++i) 
    {
        //cout<< *i << " ";
        //outStream<<*i<< " ";
        for (auto j = converted.begin() ; iter != 16 ; j++) //read the 16 bits
        {
            currentArr[iter] = *j;
        }
        iter = 0; //reset iter

    }

    inStream.close();       //close connection with file

    return 0;
}