#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fengzjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, except, actual, format) \
    do { \
        test_count++; \
        if (equality) \
            test_pass++; \
        else { \
            fprintf(stderr, "%s:%d: except: " format " actual: " format "\n", __FILE__, __LINE__, except, actual); \
            main_ret = 1; \
        } \
    } while(0) \

#define EXPECT_EQ_INT(except, actual) EXPECT_EQ_BASE((except) == (actual), except, actual, "%d")

static void test_parse_null() {
    fengz_value v;
    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_OK, fengz_parse(&v, "null"));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));
}

static void test_parse() {
    test_parse_null();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}