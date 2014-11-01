#include <stdio.h>
#include "octeon-atomic.h"

#define ut_atomic(func, type, para_num) \
do { \
	type v, ret, v1, v2; \
	printf("before test [%s]:v=%d, v1=%d, v2=%d\n", #func, v, v1, v2); \
	if (para_num == 1) \
		ret = func(&v, v1); \
	else \
		ret = func(&v, v1, v2); \
	printf("after test [%s]:v=%d, ret=%d\n", #func, v, ret); \
}while(0)

#define ut_test_round(type) \
do { \
	ut_atomic(__sync_fetch_and_add, type, 1); \
	ut_atomic(__sync_add_and_fetch, type, 1); \
	ut_atomic(__sync_fetch_and_sub, type, 1); \
	ut_atomic(__sync_sub_and_fetch, type, 1); \
	ut_atomic(__sync_lock_test_and_set, type, 1); \
	ut_atomic(__sync_bool_compare_and_swap, type, 2); \
}while(0)
	

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 10; i++) {
		printf("==================%d===================\n", i);
		ut_test_round(long);
		ut_test_round(unsigned long);
		ut_test_round(int);
		ut_test_round(unsigned int);
		ut_test_round(short);
		ut_test_round(unsigned short);
		ut_test_round(char);
		ut_test_round(unsigned char);
	}
	return 0;
}
