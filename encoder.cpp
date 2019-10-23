#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

char nibba[9];

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
    int stepsize[13] = {1,2,4,8,16,32,64,256,512,1024,2048,4096};
//    char arrHex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    for (int i = 0; i < 16 ; i++)
    {
        arr[i] = arr[i]/(stepsize[range]);
        /*for(int i = 0; i<=15 ; i++)
        {
            
        }*/
    }
}

/*void makeNibble(int srcArr[], int decArr[])
{
//    char arrHex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
//    int arrNib[] = {0000,0001,0010,0011,0100,0101,0110,0111,1000,1001,1010,1011,1100,1101,1110,1111};
//    short int haha;
    for (int i = 0; i <= 16; i++)
    {
        
    }
}*/

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
    string nibble;
//    char hit;
    bitset <4> nib;
    int fiveCount = 0;
    int fortyCount = 0;
    
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

//            cout<<"max: " << max<<" min: "<<min<<endl; 

            //range here

            if ( max >= -32768 && max <= 28672 && min <= 28672 && min >= -32768 )
            {
                range = 12;
                if ( max <= 14336 && max >= -16384 && min <= 14336 && min >= -16384 )
                {
                    range = 11;
                    if ( max <= 7168 && max >= -8192 && min <= 7168 && min >= -8192 )
                    {
                        range = 10;
                        if ( max <= 3584 && max >= -4096 && min <= 3584 && min >= -4096 )
                        {
                            range = 9;
                            if ( max <= 1792 && max >= -2048 && min <= 1792 && min >= -2048 )
                            {
                                range = 8;
                                if ( max <= 896 && max >= -1024 && min <= 896 && min >= -1024 )
                                {
                                    range = 7;
                                    if ( max <= 448 && max >= -512 && min <= 448 && min >= -512 )
                                    {
                                        range = 6;
                                        if ( max <= 224 && max >= -256 && min <= 224 && min >= -256 )
                                            {
                                                range = 5;
                                                if ( max <= 112 && max >= -128 && min <= 112 && min >= -128 ){
                                                    range = 4;
                                                    if ( max <= 56 && max >= -64 && min <= 56 && min >= -64 ){
                                                        range = 3;
                                                        if ( max <= 28 && max >= -32 && min <= 28 && min >= -32 ){
                                                            range = 2;
                                                            if ( max <= 14 && max >= -16 && min <= 14 && min >= -16 ){
                                                                range = 1;
                                                                if ( max <= 7 && max >= -8 && min <= 7 && min >= -8 ){
                                                                    range = 0;}}}}}}}}}}}}}
            else if (max > 28692 || max < -38768 || min < -32768 || min > 28692) {cout<<"OUT OF RANGE!!!"<<endl;return 0;}
            //cout<<"range: "<<range<<endl;

            //if (range != 0){quantize(currentArr,range);} //quantizing to nibble

            quantize(currentArr,range);
            for(int i = 0 ; i <= 15 ; i++)
            {
                if (currentArr[i] == 0){outStream << "0";fiveCount++;fortyCount++;}
                if (currentArr[i] == 1){outStream << "1";fiveCount++;fortyCount++;}
                if (currentArr[i] == 2){outStream << "2";fiveCount++;fortyCount++;}
                if (currentArr[i] == 3){outStream << "3";fiveCount++;fortyCount++;}
                if (currentArr[i] == 4){outStream << "4";fiveCount++;fortyCount++;}
                if (currentArr[i] == 5){outStream << "5";fiveCount++;fortyCount++;}
                if (currentArr[i] == 6){outStream << "6";fiveCount++;fortyCount++;}
                if (currentArr[i] == 7){outStream << "7";fiveCount++;fortyCount++;}
                if (currentArr[i] == 8){outStream << "8";fiveCount++;fortyCount++;}
                if (currentArr[i] == 9){outStream << "9";fiveCount++;fortyCount++;}
                if (currentArr[i] == 10){outStream << "a";fiveCount++;fortyCount++;}
                if (currentArr[i] == 11){outStream << "b";fiveCount++;fortyCount++;}
                if (currentArr[i] == 12){outStream << "c";fiveCount++;fortyCount++;}
                if (currentArr[i] == 13){outStream << "d";fiveCount++;fortyCount++;}
                if (currentArr[i] == 14){outStream << "e";fiveCount++;fortyCount++;}
                if (currentArr[i] == 15){outStream << "f";fiveCount++;fortyCount++;}

                //outStream << hit;
                if(fiveCount==4)
                {
                    outStream<< " ";
                    fiveCount = 0;
                    if (fortyCount == 40)
                    {
                        outStream<< "\n";
                        fortyCount = 0;
                    }
                }
            }

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
    outStream.close();

    return 0;
}