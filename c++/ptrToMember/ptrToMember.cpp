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
			log(DEBUG, "sample copy constructor\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		static void sd(int d, int *ptr);
		sample& operator =(const sample &obj)
		{
			log(DEBUG, "sample = operator\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}
};

#define MAX 4

typedef void (*sdPtr)(int , int *);

void sd(int a , int *ptr)
{
	log(DEBUG, "static %d %u\n", a , ptr);
}

void sample::sd(int a , int *ptr)
{
	log(DEBUG, "static %d %u\n", a , ptr);
}

typedef void (sample::*sdPtr1) (int , int *);

int main()
{
	sample *sam = new sample(10, new int(12));
	sample s;
	sdPtr pt = sd;
	pt = sample::sd;


	int sample::*ptr = &sample::data;

	sam->*ptr = 4;
	s.*ptr = 4;
		
	sam->showData();
	s.showData();

	void (sample::* sampleSDPtr) (int, int *) = &sample::setData;

	sdPtr1 ptr1[2] = {&sample::setData, NULL};
	(sam->*sampleSDPtr)(34, new int);
	(sam->*ptr1[0])(24,new int);
	
	sam->showData();
	pt(1, new int);	
	delete  sam;
	return 0;
}

