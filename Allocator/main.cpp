#include "Allocator.h"

int main()
{
	Allocator a{2048};
	void* tmp = a.allocate(32);
	a.deallocate(tmp);
	void* t = a.allocate(16);
	a.deallocate(t);
	
}