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

class sampleException
{
	public:
		sampleException()
		{
			log(DEBUG, "sampleException constrctr\n");
		}
};

class sampleException1
{
	public:
		sampleException1()
		{
			log(DEBUG, "sampleException1 constrctr\n");
		}
};

class sample
{
	int data;
	int *dataPtr;

	public:
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u\n", data, dataPtr);}
		void showData(){ log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);throw sampleException1();}
		void showData1(){showData();}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample() { delete dataPtr; data =0; log(DEBUG, "Sample destructor %d:%u\n", data, dataPtr);}
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

#define MAX 4

int main()
{
	try {
		sample sam;// = new sample(10, new int(12));
		sam.showData1();
	} catch (sampleException)
	{
		log(DEBUG, "sampleException Handling\n");
	} catch (sampleException1)
	{
		log(DEBUG, "sampleException Handling1\n");
	}
	return 0;
}

