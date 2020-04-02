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

#ifdef __gl_h_
void Obj::glprepare()
{
	this->glVertexData = new GLfloat[this->vv.size()*4];
	for(auto it = this->vv.begin(); it != this->vv.end(); it++,this->vi+=4)
	{
		this->glVertexData[this->vi] = **it[0];
		this->glVertexData[this->vi+1] = **it[1];
		this->glVertexData[this->vi+2] = **it[2];
		this->glVertexData[this->vi+3] = **it[3];
	}
	this->vv.clear();
}
void Obj::gldraw()
{
	glVertexPointer(3,GL_FLOAT,0,glVertexData);
	glBegin(GL_LINES);
		for(int i = 0; i < this->vi; i+=4)
			glArrayElement(i);
	glEnd();

	glFlush();
}
#endif

std::string &Obj::getName() { return this->n; }

void Obj::setName(std::string name) { this->n = name; }
void Obj::pushVT(Vertex<float> &vt) { this->vt.push_back(vt); }
void Obj::pushVN(Vertex<float> &vn) { this->vn.push_back(vn); }
void Obj::pushVV(Vertex<float> &vv) { this->vv.push_back(vv); }
void Obj::pushVP(Vertex<float> &vp) { this->vv.push_back(vp); }
void Obj::pushVF(Obj::Polygon &vf) { this->vf.push_back(vf); }

std::vector<Vertex<float>> &Obj::getVV() { return this->vv; }
std::vector<Vertex<float>> &Obj::getVT() { return this->vt; }
std::vector<Vertex<float>> &Obj::getVN() { return this->vn; }
std::vector<Vertex<float>> &Obj::getVP() { return this->vp; }
std::vector<Obj::Polygon> &Obj::getVF() { return this->vf; }

ObjGroup::ObjGroup()
{
	
}

ObjGroup::ObjGroup(std::string name) : n(name)
{
	
}

#ifdef __gl_h_
void ObjGroup::gldraw()
{
	for(auto it = this->vo.begin(); it != this->vo.end(); it++)
	{
		it->gldraw();
	}
}
#endif

Obj &ObjGroup::operator[](int i) { return this->vo[i]; }

std::vector<Obj>::iterator ObjGroup::begin() { return this->vo.begin(); }
std::vector<Obj>::iterator ObjGroup::end() { return this->vo.end(); }

void ObjGroup::setName(std::string name) { this->n = name; }
std::string &ObjGroup::getName() { return this->n; }

void ObjGroup::push(Obj o) { this->vo.push_back(o); }

bool ObjGroup::empty() { return this->vo.empty(); }

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

ObjGroup &ObjLoader::operator[](int i) { return this->vg[i]; }

std::vector<ObjGroup>::iterator ObjLoader::begin() { return this->vg.begin(); }
std::vector<ObjGroup>::iterator ObjLoader::end() { return this->vg.end(); }

ObjLoader::RWException::RWException(std::string msg) : msg(msg) {}
std::string &ObjLoader::RWException::what() { return msg; }

void ObjLoader::load()
{
	if(!fn.empty()) this->load(fn);
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

	std::size_t lcount = 0;

	while(getline(obj,stbuff,'\n'))
	{
		lcount++;
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
			#ifdef __gl_h_
				if(!this->vg.back().empty()) this->vg.back().top().glprepare();
			#endif
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
		else if(stbuff == "f")
		{
			int vcount = 0, i = 0;
			stbuff = iss.str().substr(2);
			while(i != std::string::npos)
			{
				vcount++;
				i = stbuff.find(' ',i+1);
			}
			Obj::Polygon pol;
			for(i = 0; i < vcount; i++)
			{
				iss >> stbuff;
				int match;
				if((match = stbuff.find("//")) != std::string::npos)
				{
					pol.vvi.push_back(std::stoi(stbuff.substr(0,match),nullptr));
					pol.vni.push_back(std::stoi(stbuff.substr(match+2),nullptr));
				}
				else if((match = stbuff.find('/')) != std::string::npos)
				{
					pol.vvi.push_back(std::stoi(stbuff.substr(0,match),nullptr));
					pol.vti.push_back(std::stoi(stbuff.substr(match+1,stbuff.rfind('/')),nullptr));
					pol.vti.push_back(std::stoi(stbuff.substr(stbuff.rfind('/')+1),nullptr));
				}
				else
				{
					pol.vvi.push_back(std::stoi(stbuff));
				}
			}
			this->vg.back().top().pushVF(pol);
		}
		else if(stbuff == "mtllib")
		{
			iss >> stbuff;
			std::cout << "Ignored mtllib [" << stbuff << ']' << '\n';
		}
		else
		{
			iss >> stbuff;
			std::cout << "Ignored [" << stbuff << ']' << '\n';
		}
	}

	obj.close();
}