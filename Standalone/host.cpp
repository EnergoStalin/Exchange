#include <stdio.h>

template<class T>
void array_copy(T *&arr, const T *src, size_t _len)
{
	for(int i = 0; i < _len; i++)
	{
		arr[i] = src[i];
	}
}

void help()
{
	printf("Pipe Host programm may used for\nlaunch programms wit their args.\nUntil this programm cant handle interactive input\nbut later it may be possibale.\nWrited by EnergoStalin.\nFree to use.\n");
	printf("[-Warning] !!!Only text input no graphic or dynamic console interfaces performed.\n");
}

const char *prepare_args(int argc, char **argv)
{
	if(argc < 3) { return argv[1]; }
	size_t _len = 0,len = 0;
	len = strlen(argv[1]);
	for(int i = 2; i < argc; i++)
	{
		_len += strlen(argv[i])+1;
	}
	char *buff = new char[_len+len+1];
	array_copy(buff,argv[1],len);
	buff[len] = ' ';
	char *it = buff+len+1;
	for(int i = 2; i < argc; i++)
	{
		_len = strlen(argv[i]);
		array_copy(it,argv[i],_len);
		it = (it+_len);
		*it = ' ';
		it++;
	}
	*it = '\0';

	return buff;
}

int main(int argc, char **argv)
{

	if(!argv[1]) { help(); return 1; }
	else if(strcmp(argv[1],"-h") == 0)
	{ help(); return 0; }
	FILE *ptr = popen(prepare_args(argc,argv),"r");
	char buff[1024];
	if(ptr)
	{
		while(fgets(buff,sizeof(buff),ptr))
		{
			printf("%s",buff);
		}

		pclose(ptr);
	}


	return 0;
}
