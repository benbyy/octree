#pragma once
#include <iostream>
#include <bitset>
#include "BenbyTools.h"
using namespace std;

template <class V>
struct Vector3
{
	static float tolerance;
	V x, y, z;
	//Overload string operator for printing
	explicit operator string() const {
		string s = "(";
		s += to_string(x) + ",";
		s += to_string(y) + ",";
		s += to_string(z) + ")";
		return s;
	}
	void operator += (Vector3<V> const &other)
	{
		this->x += other.x; this->y += other.y; this->z += other.z;
	}
	//default constructor that assigns each value to zero
	Vector3() {}
	//when 1 value is passed, assign it all variables
	Vector3(V D) : x(V(D)), y(V(D)), z(V(D)) {}
	//when 3 values are passed, assign to corresponding variables
	Vector3(V X, V Y, V Z) : x(V(X)), y(V(Y)), z(V(Z)) {}
	Vector3(V*C) : x(V(C[0])), y(V(C[1])), z(V(C[2])) {}
	Vector3(tuple<V, V, V> T) : x(get<0>(T)), y(get<1>(T)), z(get<2>(T)) {}

	void print() {
		cout << string(*this) << endl;
	}
	void MultiplyByScalar(V _scalar, Vector3<double>& _vector) {
		if (!&_vector) {
			_vector = Vector3<double>();
		}
			_vector.x = x * _scalar;
			_vector.y = y * _scalar;
			_vector.z = z * _scalar;
		
}

	static unsigned short Compare(Vector3 &_a, Vector3 &_b) {
		unsigned short val = 0;
		val += (_b.x > _a.x ? 4 : 0);
		val += (_b.y > _a.y ? 2 : 0);
		val += (_b.z > _a.z ? 1 : 0);
		return val;
	}
	static bitset<3> BitCompare(Vector3 &_a, Vector3 &_b) {
		return bitset<3>(Compare(_a, _b));
	}

	tuple<V, V, V> toTuple() {
		return make_tuple(this->x, this->y, this->z);
	}

};
