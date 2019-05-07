#include "pch.h"
#include <iostream>
#include <string>
#include <bitset>
#include <time.h>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <cmath>
#include <stdio.h>
#include <boost/dynamic_bitset.hpp>

#define nleafMask 8
#define nvalidMask 8
#define nfar 1
#define nchildPointer 15
#define ncontourPointer 24
#define ncontourMask 8
#define nBits (nleafMask + nvalidMask + nfar + nchildPointer + ncontourPointer + ncontourMask)
#define pageSize 8 //page size in kb
#define bitset boost::dynamic_bitset<>
using namespace std;
struct BitFormat {
	bitset leafMask;
	bitset validMask;
	bitset far;
	bitset  childPointer;
	bitset contourPointer;
	bitset contourMask;
	bitset all;
};
BitFormat bitFormat;

template <typename T>
inline T const& Max(T const& a, T const& b) {
	return a < b ? b : a;
}

double GetRandomFloat() {
	boost::random_device dev;
	boost::mt19937 gen(dev);
	//boost::mt19937 gen(2014/*time(NULL)*/);
	boost::uniform_real<> dist(0, 1);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<> > random(gen, dist);
	double sourceID = (random());
	//std::cout << sourceID << std::endl;
	return sourceID;
}

void ShuffleBitset(bitset* bs) {
	string s = "";
	for (int i = 0; i < nBits; i++) {
		if (GetRandomFloat() > 0.50f)
			(*bs).flip(i);
		s += to_string((*bs)[i]) + ",";
	}
	//cout << s;
}

string bitsetToString(bitset bs) {
	string s = "";
	for (int i = 0; i < bs.size(); i++) {
		s += bs[i];
	}
	return s;
}

int main() {
	const double binMax = pow(2, 10);
	const int randDouble = binMax * GetRandomFloat();
	const unsigned long int totalBits = 8 * pageSize*pow(2, 10);
	printf("total bits:%d\n",totalBits);
	boost::dynamic_bitset<unsigned long int> b1Ptr;
	b1Ptr.resize(totalBits);
	//bitset b2Ptr(nBits);
	while (true) {
		string s,bits,line; 
		boost::to_string(b1Ptr, s);
		printf("size(): %d\n", b1Ptr.size());
		//printf("%X\n%s\n", &b1Ptr, s.c_str());
		printf("pageSize: %d kilobytes (%s bits)\n", pageSize,  to_string((long int)(8*pageSize*pow(2, 10))).c_str());
		//printf("page size in memory:%d\n", sizeof(b1Ptr));
		printf("blocks: %d\n", b1Ptr.num_blocks());
		printf("bits per block: %d", b1Ptr.bits_per_block);
		for (int i = 0; i < b1Ptr.size(); i+=nBits) {
			line += to_string(i)+"\t";
			for (int j = i; j < i + nBits; j++) {
				line += to_string(b1Ptr[j]);
			}
			line += "\n";
		}
		//cout << line;
		cin.get();
	}
	return 0;
}
