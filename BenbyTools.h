#pragma once
#include "boost/random.hpp"
#include <iostream>
#include <ctime>
#include <cstdint>
#include <limits>
#include <boost/random/random_device.hpp>

double randPercent();
double randRange(float min, float max);

typedef boost::mt19937 RNGType;
double randRange(float min, float max) {
		boost::random::random_device gen;
		return (max-min)*randPercent()+min;
	}
double randPercent() {
		boost::random::random_device gen;
		return ((float)gen()/(float)gen.max());
	}

template <class T>
double* randVertex(T min, T max) {
	return new T[3]{ randRange(min,max),randRange(min,max),randRange(min,max) };
}