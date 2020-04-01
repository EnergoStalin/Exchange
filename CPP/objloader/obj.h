#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <sstream>

template<class T>
class Vertex
{
	template<class T2>
	friend std::istream &operator>>(std::istream &is, Vertex<T2> &v);
	T varr[4];

	public:
		Vertex();
		Vertex(T,T,T = 0,T = 1);
		T &operator[](int);
		T *operator*();
		Vertex<T> &operator=(Vertex<T>&);
};

class Obj
{
    std::vector<Vertex<float>> vv;
    std::vector<Vertex<float>> vt;
    std::vector<Vertex<float>> vn;
	std::vector<Vertex<float>> vp;

    std::string n; //name

    public:
    Obj();
    Obj(std::string);
    std::string &getName();
    std::vector<Vertex<float>> &getVV();
    std::vector<Vertex<float>> &getVN();
    std::vector<Vertex<float>> &getVT();
	std::vector<Vertex<float>> &getVP();
	void pushVT(Vertex<float>&);
	void pushVN(Vertex<float>&);
	void pushVV(Vertex<float>&);
	void pushVP(Vertex<float>&);
};

class ObjGroup
{
    std::vector<Obj> vo;
    std::string n; //group name
    public:
    ObjGroup();
    ObjGroup(std::string);
    void push(Obj);
    std::string &getName();
	void setName(std::string);
	bool empty();
	int objCount();
	Obj &top();
	Obj *getObj(int);
    Obj *getObj(std::string);
};

class ObjLoader
{
    std::vector<ObjGroup> vg;
    int cg = 0; //current group in vector
    std::string fn; //filename
    public:
    ObjLoader(std::string);
    void load(std::string&);
    void load();
    ObjGroup *getGroup(int);
    ObjGroup *getGroup(std::string);
	int gCount();

    
	class RWException
	{
		std::string msg;
		public:
			RWException(std::string msg);
			std::string &what();
	};
};

#include "obj.cpp"

#endif