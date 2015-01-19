#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define INC_TO 1000

#define INIT_VAL 10000

volatile long unsigned int global_int = INIT_VAL;

# define os_atomic_test_and_set_ulint(ptr, new_val) __sync_lock_test_and_set(ptr, new_val)

typedef struct {
	long unsigned int lock;
}mutex_t;

mutex_t g_m;

void mutex_enter(mutex_t *m)
{
	while(os_atomic_test_and_set_ulint(&m->lock, 1));
}

void mutex_exit(mutex_t *m)
{
	os_atomic_test_and_set_ulint(&m->lock, 0);
}

pid_t gettid( void )
{
	return syscall( __NR_gettid );
}

void *thread_routine( void *arg )
{
	int i;
	int proc_num = (int)(long)arg;
	cpu_set_t set;

	CPU_ZERO( &set );
	CPU_SET( proc_num, &set );

	if (sched_setaffinity( gettid(), sizeof( cpu_set_t ), &set ))
	{
		perror( "sched_setaffinity" );
		return NULL;
	}

	for (i = 0; i < INC_TO; i++)
	{
		mutex_enter(&g_m);
		global_int += 5;
		global_int = global_int;
		global_int -= 5;
		mutex_exit(&g_m);
	}

	return NULL;
}

int main()
{
	int procs = 0;
	int i;
	pthread_t *thrs;

	// Getting number of CPUs
	procs = (int)sysconf( _SC_NPROCESSORS_ONLN );
	if (procs < 0)
	{
		perror( "sysconf" );
		return -1;
	}

	thrs = malloc( sizeof( pthread_t ) * procs );
	if (thrs == NULL)
	{
		perror( "malloc" );
		return -1;
	}

	printf( "Starting %d threads...\n", procs );

	for (i = 0; i < procs; i++)
	{
		if (pthread_create( &thrs[i], NULL, thread_routine, (void *)(long)i ))
		{
			perror( "pthread_create" );
			procs = i;
			break;
		}
	}

	for (i = 0; i < procs; i++)
		pthread_join( thrs[i], NULL );

	free( thrs );

	printf( "After doing all the math, global_int value is: %d\n", global_int );
	printf( "Expected value is: %d\n", INIT_VAL);

	return 0;
}
