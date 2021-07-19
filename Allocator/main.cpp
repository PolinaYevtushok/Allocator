#include "Allocator.h"

int main()
{
	Allocator a{2048};
	void* tmp = a.allocate(16);
	a.deallocate(tmp);
	void* t = a.allocate(16);
	void* z = a.allocate(16);
	a.deallocate(t);
	
}