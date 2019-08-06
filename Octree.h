#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>

#include <map>
#include <tuple>
#include "Vector3.h"
#include "Octant.h"
#include "CubeBox.h"
using namespace std;

template <class T> //T type of values octants hold.
class Octree {
	//Variables
	//allocator<Octant> octantAllo;
public:
	Octant<T>* rootOctant;
	CubeBox rootBox;
	Vector3<double> rootPosition;
	double rootScale;
	unsigned short maxDepth = 10;

	Octree() :
		rootOctant(new Octant<T>()),
		rootPosition(Vector3<double>(0.0f)),
		rootScale(100.0f),
		rootBox(rootPosition.toTuple(), rootScale)
		{
		Octant<T>::MAX_DEPTH = 10;
		//cout << "root depth:" << GetDepth(*rootOctant) << endl;
		//rootOctant->ChildCheck();
		//rootOctant->DestroyChildren();

		//PrintStatus(*rootOctant, "root");
		//PrintStatus(*child1, "child1");
		//PrintStatus(*child2, "child2");
		//PrintTrace(trace);
		//GetLocation(*child2);
	};

	//Octant* Insert(Vertex<double> _location, T* _values) {if(GetDepth)}
	short GetDepth(Octant<T> & _octant) {
		if (_octant.parent) {
			//printf("GetDepth:%i\n", 1 + GetDepth(*_octant.parent));
			return 1 + GetDepth(*_octant.parent);
		}
		else {
			//printf("nGetDepth:%i\n", 0);
			return 0;
		}
	}
	double GetLocalScale(double _rootScale, short _depth) {
		return (_rootScale / pow(2.0, _depth));
	}
	void Insert( Vector3<double> _location, T& _value) {
		//Octant* newOctant = new Octant(rootOctant);
		rootOctant->Adopt(new Octant(rootOctant));
		/*Octant* currentParent = rootOctant;
		for (int i = 0; i < maxDepth; i++) {
			rootOctant->Adopt(*newOctant);
		}*/
		
		//Octant o = new Octant
	}
	
	Vector3<double> GetCenter(Octant<T> &_octant) {
		if (rootOctant == &_octant) {
			return rootPosition;
		}
		auto trace = GetOctantTrace(_octant);
		Vector3<double> loc(0.0f);
		return loc;
	}
	Vector3<unsigned> GetPositionBits(unsigned _n) {
		return Vector3<unsigned>(((_n&(unsigned)4) >> 2), ((_n&(unsigned)2) >> 1), (_n&(unsigned)1));
	}
	Vector3<short> GetPositionRelation( Vector3<unsigned> _bits) {
		return Vector3<short>(ConvertBit(_bits.x), ConvertBit(_bits.y), ConvertBit(_bits.z));
	}
	short ConvertBit(unsigned _bit) { return (_bit == 1 ? 1 : -1); }
	short GetChildDesignation(Octant<T> &_octant) {
		if (_octant.parent) {
			for (unsigned short i = 0; i < 8; i++) {
				if (&(_octant.parent->children[i]) == &_octant)
					return i;
			}
		}
		return -1;
	}
	stack<unsigned short> GetTrace(Octant<T> &_octant) {
		stack<unsigned short> trace;
		Octant* current = &_octant;
		while (current->parent) {
			trace.push(GetChildDesignation(*current));
			current = current->parent;
		}
		return trace;
	}
	//void GetTrace(queue<unsigned> &_queueIO, Octant<T> &_octant) {
	//	Vector<unsigned> trace;
	//	Octant* current = &_octant;
	//	while (current->parent) {
	//		trace.push(GetChildDesignation(*current));
	//		current = current->parent;
	//	}
	//	return trace;
	//}
	map<short, Octant<T>*> GetOctantTrace(Octant<T> &_octant) {
		//Produce a map that traces an octant's heritage by matching each generation with its ancestor <depth, child[i]>
		map<short, Octant<T>*> traceMap;
		traceMap.insert(make_pair(GetChildDesignation(_octant), &_octant));
		for (Octant* po = _octant.parent; po; po = po->parent) {
			traceMap.insert(make_pair(GetChildDesignation(*po), po));
			cout << "Inserted..." << endl;
		}
		return traceMap;
	}
	void PrintTrace(map<short, Octant<T>*> &_traceMap) {
		cout << "Printing Trace Stack:" << endl;
		printf("Trace Size:%i\n", _traceMap.size());
		vector<Octant<T>*> octs;
		for(auto it : _traceMap)
		{
			//PrintStatus();
			octs.push_back(it.second);
			PrintStatus(*(it.second));
		}
		cout << "End of Trace Stack:" << endl;
	}
	void PrintTrace(stack<unsigned short>& _stack) {
		cout << "Printing Trace Stack:" << endl;
		while (!_stack.empty()) {
			cout << (unsigned short)_stack.top() << endl;
			_stack.pop();
		}
		cout << "End of Trace Stack:" << endl;
	}
	void PrintStatus(Octant<T> &_octant) {
		auto sep = "---------";
		printf("\n%sSTART%s\t\n", sep, sep);
		printf("parent:%p\tself:%p\tchildren:%p\n", _octant.parent, &_octant, _octant.children);
		printf("depth:%i\tdesignation:%i\tvalue(s):%p\n", GetDepth(_octant), GetChildDesignation(_octant), _octant.values);
		printf("%sEND%s\t\n", sep, sep);
	}
	void PrintStatus(Octant<T> &_octant, string _name) {
		auto sep = "---------";
		printf("\n%s%s START%s\t\n", sep, _name.c_str(), sep);
		printf("parent:%p\tself:%p\tchildren:%p\n", _octant.parent, &_octant, _octant.children);
		printf("depth:%i\tdesignation:%i\tvalue(s):%p\n", GetDepth(_octant), GetChildDesignation(_octant), _octant.values);
		printf("%s%s END%s\t\n", sep, _name.c_str(), sep);
	}
	void MakeOctant(Octant<T> &_toReturn, Octant<T> &_parent) {
		_toReturn = Octant<T>(_parent);
	}
};









//template <class T>
//class OctTree
//{
//	BoundingBox m_region;
//	T* m_objects;
//	/// 
//	/// These are items which we're waiting to insert into the data structure. 
//	/// We want to accrue as many objects in here as possible before we inject them into the tree. This is slightly more cache friendly. 
//	/// 
//
//	static Queue m_pendingInsertion = new Queue();
//
//	/// 
//	/// These are all of the possible child octants for this node in the tree. 
//	/// 
//	OctTree[] m_childNode = new OctTree[8];
//
//	///
//	/// This is a bitmask indicating which child nodes are actively being used. 
//	/// It adds slightly more complexity, but is faster for performance since there is only one comparison instead of 8. 
//	///
//	byte m_activeNodes = 0;
//
//	///
//	/// The minumum size for enclosing region is a 1x1x1 cube. 
//	///
//	const int MIN_SIZE = 1;
//
//	///
//	/// this is how many frames we'll wait before deleting an empty tree branch. Note that this is not a constant. The maximum lifespan doubles
//	/// every time a node is reused, until it hits a hard coded constant of 64 
//	/// 
//	int m_maxLifespan = 8; // 
//	int m_curLife = -1; //this is a countdown time showing how much time we have left to live 
//
//	/// 
//	/// A reference to the parent node is nice to have when we're trying to do a tree update. 
//	/// 
//	OctTree _parent;
//	static bool m_treeReady = false; //the tree has a few objects which need to be inserted before it is complete 
//	static bool m_treeBuilt = false; //there is no pre-existing tree yet. 
//}
//

//
//template <class T>
//class Octree
//{
//	float radius;
//	Vector3<float> location;
//	
//	struct Octant {
//	public:
//		Octant** node;
//		T* value;
//		Octant() :node(new (nothrow) Octant*[1]{ this }), value((T*) new T(123)) { cout << "New Octant Created" << endl; };
//		void Subdivide() {
//			if (!isBranch()) {
//				node = new (nothrow) Octant*[9]{ nullptr, *node };
//			}
//		}
//		bool isBranch() {
//			return (!*node);
//		}
//		void GetType() {
//			if (*node) {
//				cout << "LEAF: " << *node << "\tValue:" << to_string(*value) << endl;
//				(*value)++;
//			}
//			else {
//				Octant tv = *(node[1]);
//				cout << "BRANCH" << "\tValue:" << to_string(*(tv.value)) << endl;
//				
//			}
//		}
//	};
//	std::allocator<T> allo;
//
//public:
//	unsigned short MAXDEPTH = 5;
//	Octant* root;
//	
//	Octree<T>() : root(){
//		root = allo.allocate(1);
//		allo.construct(root);
//		location = Vector3<float>();
//		radius = 1.0f;
//		//root->GetType();
//		//root->Subdivide();
//		//root->GetType();
//	}
//
//	~Octree<T>() {}
//};
//
//
//
//
////class Octree
////{
////public:
////	
////	Octree<T>** family;
////	T* value;
////
////	Octree<T>() : family(new Octree<T>*[N]()), value(new T) {
////		*family = nullptr;
////	}
////	/*Octree<T>(Octree<T>& PARENT) : family(new Octree<T>*[N]()), value(new T) {
////		family[0] = &PARENT;
////	}*/
////	Octree<T>(Octree<T>& PARENT, uint16_t I) : family(new Octree<T>*[N]()), value(new T) {
////		family[0] = &PARENT;
////		//PARENT.family[I+1] = this;
////	}
////	void Print(string& s, string& SEP) {
////		for (int i = 1; i < N; i++) {
////			s += to_string(i) + ":";
////			if (family[i]) { family[i]->Print(s, SEP); }
////			else { s += "NULL"; };
////			s += "\n";
////		}
////	}
////	~Octree<T>() {}
////};

// Octree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


