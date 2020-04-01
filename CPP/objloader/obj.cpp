template<class T>
Vertex<T>::Vertex()
{
	this->varr[0] = \
	this->varr[1] = \
	this->varr[2] = \
	this->varr[3] = 0;
}

template<class T>
Vertex<T>::Vertex(T x,T y,T z,T w)
{
	this->varr[0] = x;
	this->varr[1] = y;
	this->varr[2] = z;
	this->varr[3] = w;
}

template<class T>
T *Vertex<T>::operator*()
{
	return this->varr;
}

template<class T>
T &Vertex<T>::operator[](int n)
{
	return this->varr[n];
}

template<class T>
Vertex<T> &Vertex<T>::operator=(Vertex<T> &v)
{
	this[0] = v[0];
	this[1] = v[1];
	this[2] = v[2];
	this[3] = v[3];
}

template<class T>
std::istream &operator>>(std::istream &is, Vertex<T> &v)
{
	is >> \
	v.varr[0] >> \
	v.varr[1] >> \
	v.varr[2] >> \
	v.varr[3];

	return is;
}

Obj::Obj()
{

}

Obj::Obj(std::string name) : n(name)
{
	
}

std::string &Obj::getName() { return this->n; }

void Obj::pushVT(Vertex<float> &vt) { this->vt.push_back(vt); }
void Obj::pushVN(Vertex<float> &vn) { this->vn.push_back(vn); }
void Obj::pushVV(Vertex<float> &vv) { this->vv.push_back(vv); }
void Obj::pushVP(Vertex<float> &vp) { this->vv.push_back(vp); }

std::vector<Vertex<float>> &Obj::getVV() { return this->vv; }
std::vector<Vertex<float>> &Obj::getVT() { return this->vt; }
std::vector<Vertex<float>> &Obj::getVN() { return this->vn; }
std::vector<Vertex<float>> &Obj::getVP() { return this->vp; }

ObjGroup::ObjGroup()
{
	
}

ObjGroup::ObjGroup(std::string name) : n(name)
{
	
}

void ObjGroup::setName(std::string name) { this->n = name; }
std::string &ObjGroup::getName() { return this->n; }

void ObjGroup::push(Obj o) { this->vo.push_back(o); }

bool ObjGroup::empty() { return this->vo.empty(); }

Obj *ObjGroup::getObj(int i)
{
	return &this->vo[i];
}

int ObjGroup::objCount() { return this->vo.size(); }

Obj *ObjGroup::getObj(std::string on)
{
	for(std::vector<Obj>::iterator it = this->vo.begin(); it != this->vo.end(); it++)
	{
		if(it->getName() == on) return &(*it);
	} return 0;
}

Obj &ObjGroup::top()
{
	return this->vo.back();
}

ObjLoader::ObjLoader(std::string fn)
{
	this->load(fn);
}
ObjLoader::RWException::RWException(std::string msg) : msg(msg) {}
std::string &ObjLoader::RWException::what() { return msg; }

void ObjLoader::load()
{
	if(!fn.empty()) this->load(fn);
}

ObjGroup *ObjLoader::getGroup(int i)
{
	return &this->vg[i];
}

ObjGroup *ObjLoader::getGroup(std::string gn)
{
	for(std::vector<ObjGroup>::iterator it = this->vg.begin(); it != this->vg.end(); it++)
	{
		if(it->getName() == gn) return &(*it);
	} return 0;
}

int ObjLoader::gCount() { return this->vg.size(); }

void ObjLoader::load(std::string &fn)
{
    this->vg.clear();
	this->vg.push_back(ObjGroup("root"));

	this->fn = fn;
	std::ifstream obj(fn);

	std::string stbuff;

	if(!obj.is_open()) throw RWException("Cant open file "+this->fn);

	while(getline(obj,stbuff,'\n'))
	{
		std::istringstream iss(stbuff);
		iss >> stbuff;

		if(stbuff == "g")
		{
			iss >> stbuff;
			this->vg.push_back(ObjGroup(stbuff));
			std::cout << "New object group[" << this->vg.back().getName() << "]\n";
		}
		else if(stbuff == "o")
		{
			iss >> stbuff;
			this->vg.back().push(Obj(stbuff));
			std::cout << "New object in group " << this->vg.back().getName() << '[' << this->vg.back().top().getName() << "]\n";
		}
		else if(stbuff == "v")
		{
			Vertex<float> v;
			iss >> v;
			this->vg.back().top().pushVV(v);
		}
		else if(stbuff == "vt")
		{
			Vertex<float> v;
			iss >> v;
			this->vg.back().top().pushVT(v);
		}
        else if(stbuff == "vn")
		{
			Vertex<float> v;
			iss >> v;
			this->vg.back().top().pushVN(v);
		}
		else if(stbuff == "vp")
		{
			Vertex<float> v;
			iss >> v;
			this->vg.back().top().pushVP(v);
		}
	}

	obj.close();
}