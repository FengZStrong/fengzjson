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

static void test_parse_true() {
    fengz_value v;
    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_OK, fengz_parse(&v, "true"));
    EXPECT_EQ_INT(FENGZ_TRUE, fengz_get_type(&v));
}

static void test_parse_false() {
    fengz_value v;
    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_OK, fengz_parse(&v, "false"));
    EXPECT_EQ_INT(FENGZ_FALSE, fengz_get_type(&v));
}

static void test_parse_expect_value() {
    fengz_value v;

    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_EXPECT_VALUE, fengz_parse(&v, ""));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));

    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_EXPECT_VALUE, fengz_parse(&v, " "));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));
}

static void test_parse_invalid_value() {
    fengz_value v;

    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_INVALID_VALUE, fengz_parse(&v, "nul"));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));

    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_INVALID_VALUE, fengz_parse(&v, "?"));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));
}

static void test_parse_root_not_singular() {
    fengz_value v;
    v.type = FENGZ_FALSE;
    EXPECT_EQ_INT(FENGZ_PARSE_ROOT_NOT_SINGULAR, fengz_parse(&v, "null x"));
    EXPECT_EQ_INT(FENGZ_NULL, fengz_get_type(&v));
}

static void test_parse() {
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}