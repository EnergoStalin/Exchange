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
    public:
    class Polygon
	{
		public:
			std::vector<int> vvi; 
			std::vector<int> vti;
			std::vector<int> vni;
			std::vector<int> vpi;
	};


    Obj();
    Obj(std::string);
    std::string &getName();
    std::vector<Vertex<float>> &getVV();
    std::vector<Vertex<float>> &getVN();
    std::vector<Vertex<float>> &getVT();
	std::vector<Vertex<float>> &getVP();
	std::vector<Polygon> &getVF();
	void pushVT(Vertex<float>&);
	void pushVN(Vertex<float>&);
	void pushVV(Vertex<float>&);
	void pushVP(Vertex<float>&);
	void pushVF(Polygon&);
	void setName(std::string);

	#ifdef __gl_h_
		GLfloat *glVertexData = 0;
		GLint *glIndexData = 0;
		int vi = 0;
		void glprepare();
		void gldraw();
	#endif

	private:
	std::vector<Vertex<float>> vv;
    std::vector<Vertex<float>> vt;
    std::vector<Vertex<float>> vn;
	std::vector<Vertex<float>> vp;
	std::vector<Polygon> vf;

    std::string n; //name
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
    Obj *getObj(std::string);
    std::vector<Obj>::iterator begin();
    std::vector<Obj>::iterator end();
    Obj &operator[](int); //Return obj by index (last == first) or null if not find
    #ifdef __gl_h_
    	void gldraw();
	#endif
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
    ObjGroup *getGroup(std::string); //Return group by name or null if not find
    std::vector<ObjGroup>::iterator begin();
    std::vector<ObjGroup>::iterator end();
	int gCount();
	ObjGroup &operator[](int); //Return group by index (last == first) or null if not find

    
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