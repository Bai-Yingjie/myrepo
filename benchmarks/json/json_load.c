#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

/*
 * gcc -I.... hello.c -ljansson
 *
 * LD_LIBRARY_PATH=/to/your/jansson-lib-dir ./a.out <json-filename> <count>
 */
void json_load_dump_test(char *filename, int test_count)
{
    int i;
    json_t *json;
    json_error_t error;

    for (i = 0; i < test_count; i++) {
        json = json_load_file(filename, 0, &error);

        if (!json) {
            printf("load json file failed, file: %s\n", filename);
            break;
        }

        json_dumpfd(json, 1, 0);
        json_decref(json);
    }

    //printf("\n\n\n#### done, test count: %d\n", i);
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    int  test_count = atoi(argv[2]);

    //printf("json file: %s, test count: %d\n", filename, test_count);

    json_load_dump_test(filename, test_count);

    return 0;
}

