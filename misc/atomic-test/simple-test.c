#include <stdio.h>
#include "octeon-atomic.h"

int main()
{
	int iv;
	long lv;
	__sync_add_and_fetch(&iv, 1);
}
