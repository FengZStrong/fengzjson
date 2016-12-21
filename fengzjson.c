#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */
#include "fengzjson.h"

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char *json;
} fengz_context;

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void fengz_parse_whitespace(fengz_context *c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* null  = "null" */
static int fengz_parse_null(fengz_context *c, fengz_value *v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return FENGZ_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = FENGZ_NULL;
    return FENGZ_PARSE_OK;
}

static int fengz_parse_false(fengz_context *c, fengz_value *v) {
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return FENGZ_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = FENGZ_FALSE;
    return FENGZ_PARSE_OK;
}

static int fengz_parse_true(fengz_context *c, fengz_value *v) {
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return FENGZ_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = FENGZ_TRUE;
    return FENGZ_PARSE_OK;
}

/* value = null / false / true */
static int fengz_parse_value(fengz_context *c, fengz_value *v) {
    switch (*c->json) {
        case 'n':
            return fengz_parse_null(c, v);
        case 'f':
            return fengz_parse_false(c, v);
        case 't':
            return fengz_parse_true(c, v);
        case '\0':
            return FENGZ_PARSE_EXPECT_VALUE;
        default:
            return FENGZ_PARSE_INVALID_VALUE;
    }
}

int fengz_parse(fengz_value *v, const char *json) {
    assert(v != NULL);
    fengz_context c;
    int ret;
    v->type = FENGZ_NULL;
    c.json = json;
    fengz_parse_whitespace(&c);
    if ((ret = fengz_parse_value(&c, v)) == FENGZ_PARSE_OK) {
        fengz_parse_whitespace(&c);
        if (c.json[0] != '\0')
            ret = FENGZ_PARSE_ROOT_NOT_SINGULAR;
    }

    return ret;
}

fengz_type fengz_get_type(const fengz_value *v) {
    assert(v != NULL);
    return v->type;
}