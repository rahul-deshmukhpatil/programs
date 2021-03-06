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
		sample(const sample &obj)
		{
			log(DEBUG, "sample copy constructor \n");
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

class sample1:public sample
{
	int data;
	int *dataPtr;

	public:
		sample1(int a=0, int *b=0):data(a),dataPtr(b) { log(DEBUG, "sample1 constructor %d:%u\n", data, dataPtr);}
		void showData(){log(DEBUG,"data=%d dataPtr=%u\n", data, dataPtr);}
		void setData(int a, int *b){data=a; dataPtr= b; log(DEBUG,"sample1 setting data=%d dataPtr=%u\n", data, dataPtr);}
		~sample1() { delete dataPtr; data =0; log(DEBUG, "sample1 destructor %d:%u\n", data, dataPtr);}
		sample1(const sample1 &obj)
		{
			log(DEBUG, "sample1 copy constructor\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
		}

		sample1& operator =(const sample1 &obj)
		{
			const sample &ref = obj;
			*(sample* )this = ref;
			log(DEBUG, "sample1 = operator\n");
			data = obj.data;
			dataPtr = obj.dataPtr;
			return *this;
		}
};

#define MAX 4

int main()
{
	sample *sam = new sample(10, new int(12));
	sample1 *sam1 = new sample1(10, new int(12));

	sample &s = *sam;
	sample &s1 = *sam1;

	sam =sam1;	
	sam->setData( 2, new int(45));
	sam1->setData(4, new int(34));
	s.setData( 2, new int(45));
	s1.setData(4, new int(34));

	*sam1 = *sam1;	
	delete  sam;
	return 0;
}

