#ifndef _FENGZ_JSON_H_
#define _FENGZ_JSON_H_

typedef enum {
    FENGZ_NULL,
    FENGZ_FALSE,
    FENGZ_TRUE,
    FENGZ_NUMBER,
    FENGZ_STRING,
    FENGZ_ARRAY,
    FENGZ_OBJECT
} fengz_type;

typedef struct {
    fengz_type type;
} fengz_value;

enum {
    FENGZ_PARSE_OK = 0,
    FENGZ_PARSE_EXPECT_VALUE,
    FENGZ_PARSE_INVALID_VALUE,
    FENGZ_PARSE_ROOT_NOT_SINGULAR
};

int fengz_parse(fengz_value *v, const char *json);
fengz_type fengz_get_type(const fengz_value *v);

#endif