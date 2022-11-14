#include <string.h>
#include <stdio.h>

#include <dtc/str.h>

#define STR_TEST_1 "Hello"
#define STR_TEST_2 "World!"

int main()
{
    char *buf;
    dtc_str *str;
    char c;

    dtc_str_init(&str);

    dtc_str_sets(str, STR_TEST_2);
    dtc_str_buf(str, &buf);

    if(strcmp(buf, STR_TEST_2))
        return 1;
    
    dtc_str_sets(str, STR_TEST_1);
    dtc_str_buf(str, &buf);

    if(strcmp(buf, STR_TEST_1))
        return 2;

    dtc_str_appends(str, STR_TEST_2);
    dtc_str_buf(str, &buf);

    if(strcmp(buf, STR_TEST_1 STR_TEST_2))
        return 3;

    dtc_str_appendc(str, 'w');
    dtc_str_buf(str, &buf);

    if(strcmp(buf, STR_TEST_1 STR_TEST_2 "w"))
        return 4;
    
    dtc_str_getc(str, 0, &c);
    dtc_str_buf(str, &buf);

    if(c != STR_TEST_1[0])
        return 5;

    dtc_str_setc(str, 'R', 0);
    dtc_str_getc(str, 0, &c);
    dtc_str_buf(str, &buf);

    if(c != 'R')
        return 6;

    dtc_str_fini(str);
}
