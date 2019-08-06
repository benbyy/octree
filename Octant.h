#pragma once
#include<stack>

template <class T>
class Octant {
public:
	static unsigned short MAX_DEPTH;
	
	Octant* parent;
	Octant* children;
	stack<T>* values;

	Octant() :
		parent(nullptr),
		children(nullptr),
		values(nullptr) {}
	Octant(Octant& _parent) :
		parent(&_parent),
		children(nullptr),
		values(nullptr) {}
	bool Insert(Octant &_octant, unsigned short _i) {
		if (!this->children) {
			this->InitChildren();
		}
		_octant.parent = this;
		auto childI = GetChildDesignation(_octant);
		this->children[childI] = &_octant;
	}
	Octant* InitChildren() {
		children = new Octant[8];
		return children;
	}
	Octant* DestroyChildren() {
		delete[] children;
		children = nullptr;
		return children;
	}
	Octant* DisownChildren(Octant* _adopter) {
		_adopter = children;
		children = nullptr;
		return _adopter;
	}
	void Insert(Octant& _octant) {}

	void ChildCheck() {
		printf("\tchildren[]:%p\n", this->children);
		if (children) {
			for (int i = 0; i < 8; i++) {
				printf("\t\tchildren[%i]:%p\n", i,&((this->children)[i]));
			}
		}
	}
};
template <class T>
unsigned short Octant<T>::MAX_DEPTH = 5;



