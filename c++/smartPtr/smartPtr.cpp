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
	int data2;
	int *dataPtr;
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u\n", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d data2=%d dataPtr=%u\n", data, data2, dataPtr);}
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
	sample *sam = new sample(10, new int(12));
	sample sam2(30);
	int sample::*p1 = &sample::data;
	
	sam->*p1 = 5;
	sam2.*p1 = 5;
	sam->showData();
	sam2.showData();

	p1 = &sample::data2;	
	sam->*p1 = 15;
	sam2.*p1 = 15;
	sam->showData();
	sam2.showData();
		
	return 0;
}

