#include <iostream>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include <climits>
#include <cmath>
#include <math.h>

using namespace std;

int main (int argc, char* argv[])
{
	ifstream oldInFile("sample_sound.bin", fstream::in | ifstream::binary);
	ifstream convertedFile("out.raw", fstream::in | ifstream::binary);

	unsigned char temp[sizeof(float)];
	unsigned char temp2[sizeof(float)];
    float floVar;
    float otherFloVar;
    int j = 0;
    vector<float> newValue;
    vector<float> oldValue;
    float mse = 0;
    float psnr = 0;
    float max = powf(2,31);
    float theH = 0;
	float theH2 = 0;

	while(convertedFile.read(reinterpret_cast<char*>(temp), sizeof(float)))
	{

		unsigned char t = temp[0];
    	temp[0] = temp[3];
	    temp[3] = t;
	    t = temp[1];
	    temp[1] = temp[2];
	    temp[2] = t;
	    floVar = reinterpret_cast<float&>(temp);
		
	    if (floVar > 1 || floVar < -1)
	    {
	    	cout << "OUT OF BOUNDS!!" << endl;
	    	break;
	    }

	    newValue.push_back(floVar);

	    oldInFile.read(reinterpret_cast<char*>(temp2), sizeof(float));

	    unsigned char t2 = temp2[0];
    	temp2[0] = temp2[3];
	    temp2[3] = t2;
	    t2 = temp2[1];
	    temp2[1] = temp2[2];
	    temp2[2] = t2;
	    otherFloVar = reinterpret_cast<float&>(temp2);
	    if(otherFloVar > 1 || otherFloVar < -1)
	    {
	    	cout << "WRONG INPUT" << endl;
	    	break;
	    }
	    oldValue.push_back(otherFloVar);
	    j++;

	}
	for (int i=0;i<j;i++)
	{
		mse = static_cast<float>(mse) + powf((static_cast<float>(oldValue[i]) - static_cast<float>(newValue[i])),2);
	}
	mse = static_cast<float>(mse)/static_cast<float>(j);
	theH = static_cast<float>(20) * log10(max);
	theH2 = static_cast<float>(10) * log10(static_cast<float>(mse));
	psnr = static_cast<float>(theH) - static_cast<float>(theH2);
	cout << psnr << endl;

	oldInFile.close();
	convertedFile.close();
	return 0;
}