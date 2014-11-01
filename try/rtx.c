#include <stdio.h>

struct rtx_def;
//typedef struct rtx_def *rtx;
typedef void *rtx;

static inline rtx dummy_func(rtx *addr, rtx val)
{
	rtx tmp;
	tmp = *addr;
	*addr = val;
	return tmp;
}

#define DUMMY_FUNC(a,b) dummy_func((rtx *)(a), (rtx)(b))

int main(int argc, char *argv[])
{
	long val, tmp;
	tmp = DUMMY_FUNC(&val, 5);

	tmp = DUMMY_FUNC(&val, 8);

	printf("===0x%lx\n", (long)tmp);
	return 0;
}
