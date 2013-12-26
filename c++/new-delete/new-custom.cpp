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
	int data;
	int *dataPtr;

	public:
		sample(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "Sample constructor %d:%u\n", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample() { delete dataPtr; data =0; log(DEBUG, "Sample destructor %d:%u\n", data, dataPtr);}

		void * operator new(long unsigned int size)
		{
			log(DEBUG, "calling sample::new\n");
			return malloc(size);
		}
	
		void operator delete(void *ptr)
		{
			log(DEBUG, "calling sample::delete\n");
			free(ptr);	
		}
};

#define MAX 4

int main()
{
	sample *sam = new sample(10, new int(12));
	delete  sam;
	return 0;
}

