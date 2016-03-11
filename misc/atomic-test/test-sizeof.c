#include <stdio.h>

#define test_type(type) \
do { \
	printf("sizeof %s is %d\n", #type, sizeof(type)); \
}while(0)

#define test_compatible(type1, type2) \
do { \
	printf("check %s and %s are compatible... %s\n", #type1, #type2, __builtin_types_compatible_p(type1, type2) ? "Yes" : "No"); \
}while(0)

int main(int argc, char *argv[])
{
	test_type(char);	
	test_type(short);	
	test_type(int);	
	test_type(long);	
	test_type(long long);	
	test_type(void);	
	test_type(void *);	
	test_type(short int);	
	test_type(long int);	
	test_type(int long);	

	test_compatible(int, long);
	test_compatible(int, unsigned int);
	test_compatible(long, unsigned long);
	test_compatible(long unsigned long, unsigned long long);
	test_compatible(long int, long);
	test_compatible(long long, long);
	test_compatible(int, long int);
	test_compatible(int *, long *);
	test_compatible(int *, void *);
	test_compatible(char *, void *);

}
