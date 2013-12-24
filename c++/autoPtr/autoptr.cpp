#include "iostream"

using namespace std;

class at
{
	int a;

	public:
		at(int aI=0):a(aI){ cout << "auto const" << endl;}
		~at(){ cout << "auto  dest" << endl;}
		void print(){cout << "ptr:" << this << " a:" << a << endl; throw 34;};
}; 

template <class A>
class auto_pt
{
	A *p;

	public:
		auto_pt(A *ptr):p(ptr){ cout << "autoPtr const" << endl;}
		~auto_pt(){ delete p; cout << "autoPtr dest" << endl;}
		A operator *() {return *p;}
		A* operator ->() {return p;}
}; 

int main()
{
	try {
		auto_pt<at> itPtr(new at(57));
		itPtr->print();	
		cout << "This will not print because of exception" << endl;
	} catch(int j) 
	{
		cout << "Exception occured!!! see if destructor is called for class at above this line, Exception : "<< j << endl;
	}
}
