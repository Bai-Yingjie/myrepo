#ifndef OCTEON_ATOMIC_H
#define OCTEON_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

/*begin orig cvmx-atomic.h*/

#define CVMX_SYNCWS_OCTEON2 asm volatile ("syncws\n" : : :"memory")
#define CVMX_SYNCWS CVMX_SYNCWS_OCTEON2

/* Macros to PUSH and POP Octeon2 ISA. */
#define CVMX_PUSH_OCTEON2    asm volatile (".set push\n.set arch=octeon2")
#define CVMX_POP_OCTEON2     asm volatile (".set pop")

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline long cvmx_atomic_fetch_and_add64_nosync(long *ptr, long incr)
{
    unsigned long ret;

	CVMX_PUSH_OCTEON2;
	if (__builtin_constant_p(incr) && incr == 1)
	{
	    __asm__ __volatile__(
		"laid  %0,(%2)"
		: "=r" (ret), "+m" (ptr) : "r" (ptr) : "memory");
	}
	else if (__builtin_constant_p(incr) && incr == -1)
        {
	    __asm__ __volatile__(
		"ladd  %0,(%2)"
		: "=r" (ret), "+m" (ptr) : "r" (ptr) : "memory");
        }
        else
        {
	    __asm__ __volatile__(
		"laad  %0,(%2),%3"
		: "=r" (ret), "+m" (ptr) : "r" (ptr), "r" (incr) : "memory");
        }
	CVMX_POP_OCTEON2;

    return (ret);
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline long cvmx_atomic_fetch_and_add64(long * ptr, long incr)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add64_nosync(ptr, incr);
	CVMX_SYNCWS;
	return ret;
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location,
 * and returns new value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location after increment
 */
static inline long cvmx_atomic_add_and_fetch64(long * ptr, long incr)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add64_nosync(ptr, incr);
	CVMX_SYNCWS;
	return (ret+incr);
}

/**
 * Atomically subs a signed value to a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to decrement memory location by (signed)
 *
 * @return Value of memory location after decrement
 */
static inline long cvmx_atomic_fetch_and_sub64(long * ptr, long incr)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add64_nosync(ptr, -incr);
	CVMX_SYNCWS;
	return (ret);
}

/**
 * Atomically subs a signed value to a 64 bit (aligned) memory location,
 * and returns new value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to decrement memory location by (signed)
 *
 * @return Value of memory location after decrement
 */
static inline long cvmx_atomic_sub_and_fetch64(long * ptr, long incr)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add64_nosync(ptr, -incr);
	CVMX_SYNCWS;
	return (ret-incr);
}

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int cvmx_atomic_fetch_and_add32_nosync(int *ptr, int incr)
{
    unsigned int ret;

	CVMX_PUSH_OCTEON2;
	if (__builtin_constant_p(incr) && incr == 1)
	{
	    __asm__ __volatile__(
		"lai  %0,(%2)"
		: "=r" (ret), "+m" (ptr) : "r" (ptr) : "memory");
	}
	else if (__builtin_constant_p(incr) && incr == -1)
        {
	    __asm__ __volatile__(
		"lad  %0,(%2)"
		: "=r" (ret), "+m" (ptr) : "r" (ptr) : "memory");
        }
        else
        {
	    __asm__ __volatile__(
		"laa  %0,(%2),%3"
		: "=r" (ret), "+m" (ptr) : "r" (ptr), "r" (incr) : "memory");
        }
	CVMX_POP_OCTEON2;

    return (ret);
}

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int cvmx_atomic_fetch_and_add32(int * ptr, int incr)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add32_nosync(ptr, incr);
	CVMX_SYNCWS;
	return ret;
}

/**__sync_add_and_fetch
 * Atomically adds a signed value to a 32 bit (aligned) memory location,
 * and returns new value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location after increment
 */
static inline int cvmx_atomic_add_and_fetch32(int * ptr, int incr)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add32_nosync(ptr, incr);
	CVMX_SYNCWS;
	return (ret+incr);
}

/**__sync_sub_and_fetch
 * Atomically subs a signed value to a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to decrement memory location by (signed)
 *
 * @return Value of memory location after decrement
 */
static inline int cvmx_atomic_fetch_and_sub32(int * ptr, int incr)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add32_nosync(ptr, -incr);
	CVMX_SYNCWS;
	return (ret);
}

/**__sync_sub_and_fetch
 * Atomically subs a signed value to a 32 bit (aligned) memory location,
 * and returns new value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to decrement memory location by (signed)
 *
 * @return Value of memory location after decrement
 */
static inline int cvmx_atomic_sub_and_fetch32(int * ptr, int incr)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_fetch_and_add32_nosync(ptr, -incr);
	CVMX_SYNCWS;
	return (ret-incr);
}

/**
 * Atomically swaps value in 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr       address in memory
 * @param new_val   new value to write
 *
 * @return Value of memory location before swap operation
 */
static inline unsigned long cvmx_atomic_swap64_nosync(unsigned long *ptr, unsigned long new_val)
{
    unsigned long ret;

	CVMX_PUSH_OCTEON2;
	if (__builtin_constant_p(new_val) && new_val == 0)
	{
	    __asm__ __volatile__(
		"lacd  %0,(%1)"
		: "=r" (ret) : "r" (ptr) : "memory");
	}
	else if (__builtin_constant_p(new_val) && new_val == ~0ull)
        {
	    __asm__ __volatile__(
		"lasd  %0,(%1)"
		: "=r" (ret) : "r" (ptr) : "memory");
        }
        else
        {
	    __asm__ __volatile__(
		"lawd  %0,(%1),%2"
		: "=r" (ret) : "r" (ptr), "r" (new_val) : "memory");
        }
	CVMX_POP_OCTEON2;

    return (ret);
}

static inline unsigned long cvmx_atomic_swap64(unsigned long * ptr, unsigned long new_val)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_swap64_nosync(ptr, new_val);
	CVMX_SYNCWS;
	return ret;
}

/**
 * Atomically swaps value in 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr       address in memory
 * @param new_val   new value to write
 *
 * @return Value of memory location before swap operation
 */
static inline unsigned int cvmx_atomic_swap32_nosync(unsigned int *ptr, unsigned int new_val)
{
    unsigned int ret;

	CVMX_PUSH_OCTEON2;
	if (__builtin_constant_p(new_val) && new_val == 0)
	{
	    __asm__ __volatile__(
		"lac  %0,(%1)"
		: "=r" (ret) : "r" (ptr) : "memory");
	}
	else if (__builtin_constant_p(new_val) && new_val == ~0u)
        {
	    __asm__ __volatile__(
		"las  %0,(%1)"
		: "=r" (ret) : "r" (ptr) : "memory");
        }
        else
        {
	    __asm__ __volatile__(
		"law  %0,(%1),%2"
		: "=r" (ret) : "r" (ptr), "r" (new_val) : "memory");
        }
	CVMX_POP_OCTEON2;

    return (ret);
}

static inline unsigned int cvmx_atomic_swap32(unsigned int * ptr, unsigned int new_val)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_swap32_nosync(ptr, new_val);
	CVMX_SYNCWS;
	return ret;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does no memory synchronization.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline unsigned long cvmx_atomic_compare_and_store64_nosync(unsigned long *ptr, unsigned long old_val, unsigned long new_val)
{
    unsigned long tmp, ret;

    __asm__ __volatile__(
    ".set noreorder         \n"
    "1: lld  %[tmp], %[val] \n"
    "   li   %[ret], 0     \n"
    "   bne  %[tmp], %[old], 2f \n"
    "   move %[tmp], %[new_val] \n"
    "   scd  %[tmp], %[val] \n"
    "   beqz %[tmp], 1b     \n"
    "   li   %[ret], 1      \n"
    "2: nop               \n"
    ".set reorder           \n"
    : [val] "+m" (*ptr), [tmp] "=&r" (tmp), [ret] "=&r" (ret)
    : [old] "r" (old_val), [new_val] "r" (new_val)
    : "memory");

    return(ret);

}

/**__sync_bool_compare_and_swap
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does memory synchronization that is required to use this as a locking primitive.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline unsigned long cvmx_atomic_compare_and_store64(unsigned long * ptr, unsigned long old_val, unsigned long new_val)
{
	unsigned long ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_compare_and_store64_nosync(ptr, old_val, new_val);
	CVMX_SYNCWS;
	return ret;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does no memory synchronization.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline unsigned int cvmx_atomic_compare_and_store32_nosync(unsigned int *ptr, unsigned int old_val, unsigned int new_val)
{
    unsigned int tmp, ret;

    __asm__ __volatile__(
    ".set noreorder         \n"
    "1: ll   %[tmp], %[val] \n"
    "   li   %[ret], 0     \n"
    "   bne  %[tmp], %[old], 2f \n"
    "   move %[tmp], %[new_val] \n"
    "   sc   %[tmp], %[val] \n"
    "   beqz %[tmp], 1b     \n"
    "   li   %[ret], 1      \n"
    "2: nop               \n"
    ".set reorder           \n"
    : [val] "+m" (*ptr), [tmp] "=&r" (tmp), [ret] "=&r" (ret)
    : [old] "r" (old_val), [new_val] "r" (new_val)
    : "memory");

    return(ret);

}

/**__sync_bool_compare_and_swap
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does memory synchronization that is required to use this as a locking primitive.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline unsigned int cvmx_atomic_compare_and_store32(unsigned int * ptr, unsigned int old_val, unsigned int new_val)
{
	unsigned int ret;
	CVMX_SYNCWS;
	ret = cvmx_atomic_compare_and_store32_nosync(ptr, old_val, new_val);
	CVMX_SYNCWS;
	return ret;

}

/*end orig cvmx-atomic.h*/

#define __sync_do1(func64, type64, func32, type32, ptr, val) \
({ \
	typeof(*ptr) octeon_ret; \
	if (__builtin_types_compatible_p(typeof(*ptr), type64)) \
		octeon_ret = func64((type64 *)ptr, (type64)val); \
	else if (__builtin_types_compatible_p(typeof(*ptr), type32)) \
		octeon_ret = func32((type32 *)ptr, (type32)val); \
	else \
		assert(("atomic not 8 or 4 bytes!",0)); \
	octeon_ret; \
})

#define __sync_do2(func64, type64, func32, type32, ptr, val1, val2) \
({ \
	typeof(*ptr) octeon_ret; \
	if (__builtin_types_compatible_p(typeof(*ptr), type64)) \
		octeon_ret = func64((type64 *)ptr, (type64)val1, (type64)val2); \
	else if (__builtin_types_compatible_p(typeof(*ptr), type32)) \
		octeon_ret = func32((type32 *)ptr, (type32)val1, (type32)val2); \
	else \
		assert(("atomic not 8 or 4 bytes!",0)); \
	octeon_ret; \
})

#define __sync_fetch_and_add(ptr, amount) __sync_do1(cvmx_atomic_fetch_and_add64, long, cvmx_atomic_fetch_and_add32, int, (ptr), (amount))
#define __sync_add_and_fetch(ptr, amount) __sync_do1(cvmx_atomic_add_and_fetch64, long, cvmx_atomic_add_and_fetch32, int, (ptr), (amount))

#define __sync_fetch_and_sub(ptr, amount) __sync_do1(cvmx_atomic_fetch_and_sub64, long, cvmx_atomic_fetch_and_sub32, int, (ptr), (amount))
#define __sync_sub_and_fetch(ptr, amount) __sync_do1(cvmx_atomic_sub_and_fetch64, long, cvmx_atomic_sub_and_fetch32, int, (ptr), (amount))

#define __sync_lock_test_and_set(ptr, new_val) __sync_do1(cvmx_atomic_swap64, unsigned long, cvmx_atomic_swap32, unsigned int, (ptr), (new_val))
#define __sync_bool_compare_and_swap(ptr, old_val, new_val) __sync_do2(cvmx_atomic_compare_and_store64, unsigned long, cvmx_atomic_compare_and_store32, unsigned int, (ptr), (old_val), (new_val))


#ifdef __cplusplus
      }
#endif
#endif
