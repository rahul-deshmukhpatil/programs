#include "iostream"
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
	printf("\n");
	va_end(args);
}



class sample
{
	int data;
	int *dataPtr;

	public:
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u", data, dataPtr);}
		void getData(int &a, int* &b)const{a=data; b=dataPtr; log(DEBUG,"getting data=%d dataPtr=%u", data, dataPtr);}
		~sample() { delete dataPtr; data =0; log(DEBUG, "Sample destructor %d:%u", data, dataPtr);}
		sample(const sample &obj)
		{
			log(DEBUG, "sample copy constructor");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		sample& operator =(const sample &obj)
		{
			log(DEBUG, "sample = operator");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}

#if 0
		operator sample2()
		{
			sample2 sam2;
			log(DEBUG, "sample2 sample1sample1");
			sam2.data = data;
			sam2.dataPtr = dataPtr;
			return sam2;
		}
#endif
		operator int()
		{
			log(DEBUG, "sampe to int operator");
			return data;
		}
		
};

class sample2
{
	int data;
	int *dataPtr;

	public:
		sample2(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample2 constructor %d:%u", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u", data, dataPtr);}
		~sample2() { delete dataPtr; data =0; log(DEBUG, "Sample2 destructor %d:%u", data, dataPtr);}
		sample2(const sample2 &obj)
		{
			log(DEBUG, "sample copy constructor");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		sample2(const sample &obj)
		{
			log(DEBUG, "sample2 1 arg constructor");
			obj.getData(data, dataPtr);
		}
#if 1
		sample2& operator =(const sample2 &obj)
		{
			log(DEBUG, "sample2 = operator");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}
#endif
		operator int()
		{
			log(DEBUG, "sample2 int operator");
			return data;
		}
		
};
#define MAX 4

int main()
{
	sample sam = 5;
#if 0
	sample2 sam2 = 5;
	int i = sam;
	sam = i;
	sam2 = sam;
#endif
	sample2 s = sam;
	sample2 s1 = s;
	s = 1;
	return 0;
}

