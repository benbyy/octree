#pragma once
#include <map>
#include <cmath>
#include <queue>

using namespace std;
typedef tuple<double, double, double> tuple_double;

class CubeBox {
private:
public:
	tuple<double, double, double> worldCenter;
	double halfWidth;
	CubeBox(): worldCenter(make_tuple(0.0f,0.0f,0.0f)), halfWidth(0.5f){}
	CubeBox(double _width):worldCenter(make_tuple(0.0f, 0.0f, 0.0f)), halfWidth(_width/2.0f){}
	CubeBox(tuple<double, double, double> _center, double _width) :worldCenter(_center), halfWidth(_width / 2.0f) {}
	
	void operator=(const CubeBox & b) {
		printf("\nOperatorCalled!\n");
		this->print("before");
		this->worldCenter = tuple_double(b.worldCenter);
		this->halfWidth = double(b.halfWidth);
		this->print("after");
		system("pause");
	}
	pair<double, double> MinMaxPair(double _a, double _b) {
		return (_a > _b ? make_pair(_a, _b) : make_pair(_b, _a));
	}
	
	double hwidth() {
		return double((this->halfWidth));
	}
	double hwidth(bool _negative) {
		return (_negative ? -hwidth() : hwidth());
	}

	double width(){
		return double(2)*(this->halfWidth);
	}
	double width(bool _negative) {
		return (_negative ? -width() : width());
	}

	double radius() {
		return(sqrt(double(2)*pow(halfWidth, double(2))));
	}
	double radius(bool _negative) {
		return (_negative ? -radius() : radius());
	}

	CubeBox GetQuadrant(unsigned _requestedQuadrant) {
		return CubeBox(this->GetQuadrantWorldCenter(_requestedQuadrant), this->radius());
	}
	tuple<double, double, double> GetCenter() {
		return tuple<double, double, double>(this->worldCenter);
	}
	void GetCenter(tuple_double &_tuple) {
		_tuple=tuple_double(this->worldCenter);
	}

	tuple<double, double, double> GetQuadrantRelativeCenter(unsigned _quadrant) {
		auto bits = SplitBits(_quadrant);
		//cout << "bits:" << _quadrant << (get<0>(bits))<< (get<1>(bits)) << (get<2>(bits)) << endl;
		return make_tuple<double, double, double>(
			hwidth(!bool(get<0>(bits))) / double(2),
			hwidth(!bool(get<1>(bits))) / double(2),
			hwidth(!bool(get<2>(bits))) / double(2));
	}
	tuple<double, double, double> GetQuadrantWorldCenter(unsigned _quadrant) {
		auto bits = SplitBits(_quadrant);
		return AddTuples(GetQuadrantRelativeCenter(_quadrant), (this->worldCenter));
	}
	tuple<double, double, double> GetCorner(unsigned _corner) {
		auto bits = SplitBits(_corner);
		return make_tuple<double, double, double>(
			width(!bool(get<0>(bits))),
			width(!bool(get<1>(bits))),
			width(!bool(get<2>(bits))));
	}
	tuple<unsigned, unsigned, unsigned> SplitBits(unsigned _n) {
		return make_tuple<unsigned>(((_n&(unsigned)4) >> 2), ((_n&(unsigned)2) >> 1), (_n&(unsigned)1));
	}

	unsigned short CombineBits(tuple<unsigned, unsigned, unsigned> &_bits) {
		return (get<0>(_bits) + get<1>(_bits) + get<2>(_bits));
	}

	tuple<double, double, double> AddTuples(tuple<double, double, double> _a, tuple<double, double, double> _b) {
		return make_tuple(get<0>(_a) + get<0>(_b), get<1>(_a) + get<1>(_b), get<2>(_a) + get<2>(_b));
	}


	//Vertex<short> GetQuadrantCenter(Vertex<unsigned> _bits) {
	//	return Vertex<short>(ConvertBit(_bits.x), ConvertBit(_bits.y), ConvertBit(_bits.z));
	//}
	void Subdivide(CubeBox &_box) {
		//CubeBox* _newBoxPtr = new CubeBox[8];

		//delete _newBoxPtr;

	}

	void contains(tuple_double &_point) {
		cout << "PrintTuple()" << endl;
		printTuple(_point);
		system("pause");
	}
	
	void ConsumeTrace(CubeBox &_ptrIn, queue<unsigned> &trace) {
		CubeBox* _cbPtr = this;
		while (!trace.empty()) {
			cout << "Consuming..." << trace.front() << endl;
			_cbPtr->print(to_string(trace.front()).c_str());
			_cbPtr = &(_cbPtr->GetQuadrant(trace.front())); trace.pop();
		}
		cout << "here" << endl;		
		cout << (_cbPtr ? "yeah!\n" : "nah...\n");	
		_ptrIn = *_cbPtr;
		_cbPtr->print("cbPtr");
		_ptrIn.print("ptrIn");
	}
	void printTuple(tuple_double &_tuple) {
		const char* format = "(%f/%f/%f/%f)\n";
		printf(format, get<0>(_tuple), get<1>(_tuple), get<2>(_tuple));
	}
	void print(const char* _label) {
		const char* format = "CubeBox[%s][&%p](q/w/W/r)(x,y,z):\t(%f/%f/%f/%f)\t(%f/%f/%f)\n";
		printf(format, _label, this, (this->hwidth() / double(2)), this->hwidth(), this->width(), this->radius(),
			get<0>(this->worldCenter), get<1>(this->worldCenter), get<2>(this->worldCenter));
	}

};
//
//class BoundingBox {
//private:
//public:
//	map<int, pair<double, double>> limits;
//	BoundingBox() {
//		limits[0] = make_pair(-1.0f, 1.0f);
//		limits[1] = make_pair(-1.0f, 1.0f);
//		limits[2] = make_pair(-1.0f, 1.0f);
//	}
//	BoundingBox(double _radius) {
//		limits[0] = MinMaxPair(-_radius, _radius);
//		limits[1] = MinMaxPair(-_radius, _radius);
//		limits[2] = MinMaxPair(-_radius, _radius);
//	}
//	pair<double, double> MinMaxPair(double _a, double _b) {
//		return (_a > _b ? make_pair(_a, _b) : make_pair(_b, _a));
//	}
//
//	double width() {//Assuming BoundingBox is a Cube
//
//	}
//	double halfWidth() {
//
//	}
//	void Subdivide(BoundingBox &_box) {
//		BoundingBox* _newBoxPtr = new BoundingBox[8];
//
//		delete _newBoxPtr;
//
//	}
//
//};


