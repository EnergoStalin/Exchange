#ifndef LIB_ARG_CPP
#define LIB_ARG_CPP

#ifndef NULL
	#define NULL 0
#endif

char digits[11] = {'0','1','2','3','4','5','6','7','8','9','.'};

int len4str(const char *str)
{
	int k = 0;
	while(str[k] != '\0')
		k++;
	return k;
}

bool cstr(const char *str1, const char *str2)
{
	if(len4str(str1) != len4str(str2)) return false;
	for(int i = 0; i < len4str(str1); i++)
		if(str1[i] != str2[i]) return false;

	return true;
}

void strcpy(char *str, const char *str2)
{
	delete []str;
	str = new char[len4str(str2)];
	for(int i = 0; i < len4str(str2); i++)
	{
		str[i] = str2[i];
	}
}

class Arg
{
	class pair
	{
		public:
			int num;
			char *str;
			void set(int num, char *str);
			pair();
			~pair();
	};
	int argc;
	pair *pairs;
public:
	pair *lookUpFor(const char *str);
	bool has(const char *str);
	Arg(int argc, char **argv, bool ignore1 = true);
	~Arg();
	
};

Arg::Arg(int argc, char **argv, bool ignore1)
{
	if(argc == 0)
	{
		this->argc = 0;
		this->pairs = NULL;
	}
	if(ignore1)
	{
		this->argc = argc;
		this->pairs = new pair[this->argc-1];
		for(int i = 1; i < this->argc; i++)
		{
			pairs[i-1].set(i,argv[i]);
		}
		this->argc--;
	} 
	else
	{
		this->argc = argc;
		this->pairs = new pair[this->argc];
		for(int i = 0; i < this->argc; i++)
		{
			pairs[i].set(i,argv[i]);
		}
	}
}

bool Arg::has(const char *str)
{
	for(int i = 0; i < this->argc; i++)
	{
		if(cstr(this->pairs[i].str,str)) return true;
	}
	return false;
}

Arg::pair *Arg::lookUpFor(const char *str)
{
	for(int i = 0; i < this->argc; i++)
	{
		if(cstr(this->pairs[i].str,str)) return &(this->pairs[i]);
	}

	return NULL;
}

Arg::~Arg() { delete []this->pairs; }

Arg::pair::pair() { this->set(0,NULL); }

void Arg::pair::set(int num, char *str)
{
	this->num = num;
	this->str = str;
}

Arg::pair::~pair() {}

#endif