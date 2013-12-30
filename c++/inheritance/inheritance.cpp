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
	va_end(args);
}

class sample
{

	public:
	int data;
	int *dataPtr;
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u\n", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample() { delete dataPtr; data =0; log(DEBUG, "Sample destructor %d:%u\n", data, dataPtr);}
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
};

class sample1
{

	public:
	int data;
	int *dataPtr;
		sample1(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample1 constructor %d:%u\n", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample1() { delete dataPtr; data =0; log(DEBUG, "Sample1 destructor %d:%u\n", data, dataPtr);}
		sample1(const sample1 &obj)
		{
			log(DEBUG, "sample1 copy constructor");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		sample1& operator =(const sample1 &obj)
		{
			log(DEBUG, "sample1 = operator");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}
};

class sample2:public sample, public sample1
{
	public:
		void setData(int i, int*ptr)
		{
			sample::setData(i, ptr);
		}
		void showData(){log(DEBUG,"sample2 data=%d dataPtr=%u\n", sample::data, sample::dataPtr);}
};

#define MAX 4

int main()
{
	sample2 *sam = new sample2();
	sam->setData(10, new int(3));
	delete  sam;
	return 0;
}

