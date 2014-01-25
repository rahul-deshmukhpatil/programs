#include "iostream"
#include "typeinfo"
#include "stdarg.h"
#include "stdio.h"
#include "malloc.h"

using namespace std;

enum logLevel{DEBUG=1, INFO=2, WARN=3, ERROR=4};

void log(int level, const char *str, ...)
{
	va_list args;
	
	va_start(args, str);
	if(level >= LOG_LEVEL)	
		vprintf(str, args);
	va_end(args);
}
template<class T, class V>
class sample
{
	T a;
	V b;
	int data;
	int *dataPtr;

	public:
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u ", data, dataPtr); // cout << typeid(a) << "-"<< typeid(b) << endl;
		}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample() { delete dataPtr; data =0; log(DEBUG, "Sample destructor %d:%u\n", data, dataPtr);}
		T defineOut(); 
		sample(const sample &obj)
		{
			log(DEBUG, "sample copy constructor\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		sample& operator =(const sample &obj)
		{
			log(DEBUG, "sample = operator\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}
};

template<>
class sample<int, int>
{
	public:
	sample(int a=0, int *ptr=0){ log(DEBUG, "spcialized version:");}
	int defineOut();
};

//template<int, int>
//int sample<int, int>::defineOut(){}

template<class T, class V>
T sample<T, V>::defineOut() {}

template<class T,class V, class W>
class sample1:public sample<T, W>
{
	public:
		sample1(int a, int* b):sample<T,W>(a, b){log(DEBUG, "child class calls");}
};
#define MAX 4

template<class T, class V>
T func(V a, T b) {log(DEBUG, "takes T and retruns V\n");}

template<>
int func(int a, int b) {log(DEBUG, "takes int and retruns int\n");}


int main()
{
	sample<int, int> *sam = new sample<int, int> (10, new int(12));
	sample1<int, float, int> *sam1 = new sample1<int, float, int> (10, new int(12));
	
	if(typeid(sam) == typeid(sam1))
		printf("\n same\n");
	else
		printf("\n not same\n");


	int a = func(5, 6);
	int b = func(5, 4.5);

	delete sam1;
	return 0;
}

