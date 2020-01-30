#ifndef LIB_ARG_CPP
#define LIB_ARG_CPP

#ifdef DEBUG
	#include <iostream>
#endif

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

bool is_digit(const char* str)
{
	for(int i = 0; i < len4str(str); i++)
	{
		bool is = false;
		for(int k = 0; k < 11; k++)
		{
			if(str[i] == digits[k]) {
				is = true;
				break;
			}
		}
		if(!is) return false;
	}
	return true;
}

int len4str(const char *str, const char breaker)
{
	int k = 0;
	while(str[k] != '\0' && str[k] != breaker)
	{
		k++;
	}
	return k;
}

int len4str(int from,const char *str, const char breaker)
{
	int s = 0;
	while(str[from] != '\0' && str[from] != breaker)
	{
		s++;
		from++;
	}
	return s;
}

bool cstr(const char *str1, const char *str2)
{
	if(!str1 && !str2) return false;
	if(len4str(str1) != len4str(str2)) return false;
	for(int i = 0; i < len4str(str1); i++)
		if(str1[i] != str2[i]) return false;

	return true;
}

void strcpy(char *str, const char *str2)
{
	while(*str2 != '\0')
	{
		*str++ = *str2++;
	}
}

bool is_key(const char *str ,const char startsWith = '-')
{
	if(!str) return false;
	if(str[0] == startsWith) return true;
	return false;
}

char *getObject(int from = 0, const char *str = NULL, const char parser = ' ') //Required free returned str
{
	if(!str) return NULL;
	int len = len4str(from,str,parser);
	char *buff = new char[len];
	for(int i = 0; i < len; i++)
	{
		buff[i] = str[i+from];
	}

	return buff;
}

class Arg
{
	class pair
	{
		public:
			char *key; //always not NULL
			char *val; //may be NULL
			void set(char *key, char *val);
			pair();
			~pair();
	};
	int argc;
	pair *pairs;
public:
	char *find(const char *str);
	bool has(const char *str);
	bool has(const char *str, const char *str2);
	Arg(int argc, char **argv);
	~Arg();
	
};

Arg::Arg(int argc, char **argv)
{
	this->argc = argc;
	if(this->argc == 1) this->pairs = NULL;
	else
	{
		int size = 0;
		for(int i = 1; i < this->argc; i++)
		{
			if(is_key(argv[i]))
				if(i+1 < this->argc)
					if(!is_key(argv[i+1]))
					{
						i++;
					}
			size++;
		}
		this->pairs = new pair[size];
		for(int i = 0, k = 1; k < this->argc; i++,k++)
		{
			if(is_key(argv[k]))
			{
				if(k+1 < this->argc)
				{
					if(!is_key(argv[k+1]))
					{
						this->pairs[i].set(argv[k],argv[k+1]);
						k++;
					}
					else
					{
						this->pairs[i].set(argv[k],NULL);
					}
				}
				else
				{
					this->pairs[i].set(argv[k],argv[k+1]);
				}
			}
			else
			{
				this->pairs[i].set(argv[k],NULL);
			}
			#ifdef DEBUG
				if(this->pairs[i].key)
					std::cout << "Pair key: " << this->pairs[i].key << '\n';
				if(this->pairs[i].val)
					std::cout << "Pair val: " << this->pairs[i].val << '\n';
			#endif
		}
		this->argc = size;
	}
}

bool Arg::has(const char *str)
{
	if(!this->pairs) return false;
	for(int i = 0; i < this->argc; i++)
	{
		if(cstr(this->pairs[i].key,str)) return true;
	}
	return false;
}

bool Arg::has(const char *str, const char *str2)
{
	if(!this->pairs) return false;
	for(int i = 0; i < this->argc; i++)
	{
		if(this->pairs[i].val != NULL)
			if(cstr(this->pairs[i].key,str) && cstr(this->pairs[i].val,str2)) return true;
	}
	return false;
}

char *Arg::find(const char *str)
{
	if(!this->pairs) return NULL;
	for(int i = 0; i < this->argc; i++)
	{
		if(this->pairs[i].val != NULL)
			if(cstr(this->pairs[i].key,str)) return this->pairs[i].val;
	}

	return NULL;
}

Arg::~Arg() { delete []this->pairs; }

Arg::pair::pair() { this->set(NULL,NULL); }

void Arg::pair::set(char *key, char *val)
{
	this->key = key;
	this->val = val;
}

Arg::pair::~pair() {}

#endif