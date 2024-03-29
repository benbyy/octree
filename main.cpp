// Octree.cpp : Defines the entry point for the console application.
//
#pragma once
#include "pch.h"
#include <iostream>
#include <math.h>   
#include <string>
#include "Octree.h"
#include <bitset>
#include "CubeBox.h"
#include "Octant.h"
#include "Vector3.h"
using namespace std;


int main()
{
	Octree<double> octree;
	Octant<double> octant;
	octant.ChildCheck();
	octant.InitChildren();
	octant.ChildCheck();
	octant.children[0].ChildCheck();
	printf("size of octant: %zi\n", sizeof(octant));
	CubeBox box(make_tuple(1.0f, 1.0f, 1.0f), 10.0f);
	//CubeBox box(5.0f);
	printf("box relativeCenter:%f\n", box.width());
	printf("box width:%f\n", box.width());
	printf("box radius:%f\n", box.radius());

	for(unsigned i=0; i<8; i++) {
		printf("box[%i][%s]:\t", i, bitset<3>(i).to_string().c_str()); 
		Vector3<double>(box.GetQuadrantWorldCenter(i)).print();
	}

	CubeBox bq = box.GetQuadrant(1);
	printf("\n\nbq\nbq radius:%f\n", bq.radius());
	for (unsigned i = 0; i < 8; i++) {
		printf("bq.corner[%i][%s]:\t", i, bitset<3>(i).to_string().c_str());
		Vector3<double>(bq.GetQuadrantRelativeCenter(i)).print();
	}

	CubeBox* bp = &box;
	queue<unsigned> traceQueue;
	printf("\n------\nbp\thalfwidth/radius/width:\n");
	const char* format = "bp.corner[%i][%s]:\t%f/%f/%f\n";
	for (int i = 7; i >= 0; i--) {
		bp->print(to_string(i).c_str());
		bp = &(bp->GetQuadrant(unsigned(i)));
		traceQueue.push(unsigned(i));
	}
	cout << "\n---\n\n" << endl;
	CubeBox btr = box;
	btr.print("beforeTrace");
	box.ConsumeTrace(btr, traceQueue);
	btr.print("afterTrace");
	cout << "yep" << endl;
	tuple_double tmpB;
	btr.GetCenter(tmpB);
		//box.contains(tmpB);
	//btr->print("TRACE-BUILT");
	


	system("pause");
}
//
//unsigned long long maxvoxels(int depth, double scale, int bytes);
//
//unsigned long long expsum(unsigned short num, unsigned int i) {
//	return (unsigned long long) (i > 0 ? pow(num, i) + expsum(num, i - 1) : pow(num, i));
//}
//template <class t>
//unsigned long long maxsize(unsigned short depth) {
//	string* units = new string[6]{ "b","kb","mb","gb", "tb","pb" };
//	unsigned long long size = sizeof(t) * expsum(8, depth);
//	unsigned long long sarry[6]{ 0,0,0,0,0,0 };
//	string s = "";
//	for (int i = 5; i >= 0; i--) {
//		unsigned long long a = size / (unsigned long long) pow(1000, i);
//		s = to_string(a) + units[i];
//		if (!(a == 0))break;
//	}
//	cout << s << endl;
//	return size;
//}
//
//
//unsigned long long maxvoxels(int depth, double scale, int bytes) {
//	string sep = "\t";
//	double  scale = scale;
//	unsigned long long n = 0;
//	for (int i = 0; i <= depth; i++) {
//		n += pow(8, i);
//		
//		cout << "depth:"<<i << sep+"scale:"<< scale <<"m" <<sep+"voxels:"<<n <<sep+"total size:"<<((n) * bytes)/1000000000<<"gb" << endl;
//		scale -= scale / 2.00000f;
//	}
//	return n;
//}
