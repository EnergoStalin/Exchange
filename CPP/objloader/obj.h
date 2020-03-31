#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include <fstream>
#include <cstring>


class Obj
{
    std::vector<float[4]> vv;
    std::vector<float[4]> vt;
    std::vector<float[4]> vn;

   const char *n; //name

    public:
    Obj();
    Obj(const char*);
    const char *getName();
    std::vector<float> *getVVector();
    std::vector<float> *getTVector();
    std::vector<float> *getNVector();
    

};

class ObjGroup
{
    std::vector<ObjGroup> vo;
    const char *n; //group name
    public:
    ObjGrpup();
    ObjGroup(const char*);
    void push(Obj);
    const char *getName();

};

class ObjLoader
{
    std::vector<ObjGroup> vg;
    int cg = 0; //current group in vector
    const char *fp = 0; //filename
    public:
    ObjLoader();
    ObjLoader(const char *);
    void load(const char *);
    void load();
    ObjGroup *getGroup(int);
    Obj *getObj(int,int);
    ObjGroup *getGroup(const char*);
    Obj *getObj(const char*,int);
    Obj *getObj(const char*,const char*);
    


};

#include "obj.cpp"

#endif