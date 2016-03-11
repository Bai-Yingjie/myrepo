#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if 0

#define __sync_add_and_fetch(ptr, value) octeon__sync_add_and_fetch((long *)(ptr),(long)(value),sizeof(*(ptr)))

static inline long octeon__sync_add_and_fetch(long *ptr, long value, const long bytes)
{
	if (bytes == 8) {
		printf("calling func for 8 bytes\n");
		return 8;
	}
	else if (bytes == 4) {
		printf("calling func for 4 bytes\n");
		return 4;
	}
	else {
		printf("NNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n");
		return -1;
	}
}

#define __sync_do(flag, func_64, func_32, ptr, args...) \
({ \
	typeof(*ptr) octeon_ret; \
	int octeon_size = sizeof(typeof(*ptr)); \
	if (__builtin_constant_p(octeon_size) && octeon_size  == 8) { \
		octeon_ret = func_64((flag long *)ptr, (flag long)args); \
	} else if (__builtin_constant_p(octeon_size) && octeon_size  == 4) { \
		octeon_ret = func_32((flag int *)ptr, (flag int)args); \
	} else { \
		printf("NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN atomic op is %d byte NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n", octeon_size); \
	} \
	octeon_ret; \
})
#define __sync_fetch_and_add(ptr, amount) __sync_do(,cvmx_atomic_fetch_and_add64, cvmx_atomic_fetch_and_add32, (ptr), (amount))
#define __sync_add_and_fetch(ptr, amount) __sync_do(,cvmx_atomic_add_and_fetch64, cvmx_atomic_add_and_fetch32, (ptr), (amount))
#define __sync_fetch_and_sub(ptr, amount) __sync_do(,cvmx_atomic_fetch_and_sub64, cvmx_atomic_fetch_and_sub32, (ptr), (amount))
#define __sync_sub_and_fetch(ptr, amount) __sync_do(,cvmx_atomic_sub_and_fetch64, cvmx_atomic_sub_and_fetch32, (ptr), (amount))
#define __sync_lock_test_and_set(ptr, new_val) __sync_do(unsigned, cvmx_atomic_swap64, cvmx_atomic_swap32, (ptr), (new_val))
#define __sync_bool_compare_and_swap(ptr, old_val, new_val) __sync_do(unsigned, cvmx_atomic_compare_and_store64, cvmx_atomic_compare_and_store32, (ptr), (old_val), (new_val))

#else

long cvmx_atomic_fetch_and_add64(long *ptr, long value)
{
	printf("%s\n", __FUNCTION__);
}

int cvmx_atomic_fetch_and_add32(int *ptr, int value)
{
	printf("%s\n", __FUNCTION__);
}

#define __sync_fetch_and_add(ptr, value) \
({ \
	typeof(*(ptr)) octeon_ret; \
	if (__builtin_types_compatible_p(typeof(*(ptr)), long)) \
		octeon_ret = cvmx_atomic_fetch_and_add64((long *)(ptr), (value)); \
	else if (__builtin_types_compatible_p(typeof(*(ptr)), int)) \
		octeon_ret = cvmx_atomic_fetch_and_add32((int *)(ptr), (value)); \
	else \
		assert(("atomic not 8 or 4 bytes!",0)); \
	octeon_ret; \
})

#define __sync_do(func64, type64, func32, type32, ptr, value, args...) \
({ \
	typeof(*ptr) octeon_ret; \
	if (__builtin_types_compatible_p(typeof(*ptr), type64)) \
		octeon_ret = func64((type64 *)ptr, (type64)value, ##(type64)args); \
	else if (__builtin_types_compatible_p(typeof(*ptr), type32)) \
		octeon_ret = func32((type32 *)ptr, (type32)value, ##(type32)args); \
	else \
		assert(("atomic not 8 or 4 bytes!",0)); \
	octeon_ret; \
})

#define __sync_fetch_and_add(ptr, amount) __sync_do(cvmx_atomic_fetch_and_add64, long, cvmx_atomic_fetch_and_add32, int, (ptr), (amount))
#define __sync_add_and_fetch(ptr, amount) __sync_do(cvmx_atomic_add_and_fetch64, long, cvmx_atomic_add_and_fetch32, int, (ptr), (amount))
#define __sync_fetch_and_sub(ptr, amount) __sync_do(cvmx_atomic_fetch_and_sub64, long, cvmx_atomic_fetch_and_sub32, int, (ptr), (amount))
#define __sync_sub_and_fetch(ptr, amount) __sync_do(cvmx_atomic_sub_and_fetch64, long, cvmx_atomic_sub_and_fetch32, int, (ptr), (amount))
#define __sync_lock_test_and_set(ptr, new_val) __sync_do(cvmx_atomic_swap64, unsigned long, cvmx_atomic_swap32, unsigned int, (ptr), (new_val))
#define __sync_bool_compare_and_swap(ptr, old_val, new_val) __sync_do(cvmx_atomic_compare_and_store64, unsigned long, cvmx_atomic_compare_and_store32, unsigned int, (ptr), (old_val), (new_val))
#endif

void test_func1(int *ptr, int val1, int val2)
{
	*ptr = val1 + val2;	
}
void test_func2(int *ptr, int val1)
{
	*ptr = val1;
}
#define test_args(func, ptr, args...) \
({ \
	func(ptr, (int)args); \
})

int main(int argc, char *argv[])
{
	int vint;
	long vlong;
	char vchar;
	__sync_fetch_and_add(&vlong,1);
	__sync_fetch_and_add(&vint,1);
	__sync_fetch_and_add(&vchar,1);

	/*({ test_func1(&vint, (int)1,2); });*/
	test_args(test_func1, &vint, 1,2);
	/*({ test_func2(&vint, (int)1); });*/
	test_args(test_func2, &vint, 1);
	return 0;
}
