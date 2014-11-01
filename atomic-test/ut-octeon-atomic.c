#include <stdio.h>
#include "octeon-atomic.h"

#define ut_atomic1(func, type) \
do { \
	type v, ret, v1; \
	printf("before test [%s]:v=%d, v1=%d\n", #func, v, v1); \
	ret = func(&v, v1); \
	printf("after test [%s]:v=%d, ret=%d\n", #func, v, ret); \
}while(0)

#define ut_atomic2(func, type) \
do { \
	type v, ret, v1, v2; \
	printf("before test [%s]:v=%d, v1=%d, v2=%d\n", #func, v, v1, v2); \
	ret = func(&v, v1, v2); \
	printf("after test [%s]:v=%d, ret=%d\n", #func, v, ret); \
}while(0)

#define ut_test_round(type) \
do { \
	ut_atomic1(__sync_fetch_and_add, type); \
	ut_atomic1(__sync_add_and_fetch, type); \
	ut_atomic1(__sync_fetch_and_sub, type); \
	ut_atomic1(__sync_sub_and_fetch, type); \
	ut_atomic1(__sync_lock_test_and_set, type); \
	ut_atomic2(__sync_bool_compare_and_swap, type); \
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
