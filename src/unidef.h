#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#ifndef UNIDEF_H
#define UNIDEF_H

typedef uint64_t index_t;
#define INDEX_T_NOT_FOUND (-1)

static inline index_t n_keywords = 25;
static inline const char* keywords_g[] = {
    "auto",
    "break",
    "case",
    "const",
    "continue",
    "default",
    "do",
    "else",
    "enum",
    "extern",
    "for",
    "goto",
    "if",
    "inline",
    "register",
    "restrict",
    "return",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "volatile",
    "while"
};

typedef enum _token_type_base
{
	token_NA = 0,
	token_numeric_oct_literal,
	token_numeric_hex_literal,
	token_numeric_dig_literal,
	token_int8_literal,
	token_int16_literal,
	token_int32_literal,
	token_int64_literal,
	token_uint8_literal,
	token_uint16_literal,
	token_uint32_literal,
	token_uint64_literal,
	token_float_literal,
	token_double_literal,
	token_cstr_literal,
	token_cwstr_literal,
	token_struct_literal,
	token_aggregate_literal,
	token_pointer,
	token_keyword,
	token_preprocessor_directive,
	token_typename,
	token_identifier,
	token_special_character,
	token_operator,
	token_function_name,
	token_variable_name,
	token_N_TYPES
} token_type_t;

typedef enum _type_kind_base
{
	TK_NA = 0,
	TK_PRIMITIVE,
	TK_ARRAY,
	TK_ENUM,
	TK_STRUCT,
	TK_UNION
} type_kind_t;

typedef struct _type_data_base type_data_t;
typedef struct _type_data_base
{
	size_t byte_size;
	type_kind_t kind;
	const char* full_name;
	const char* real_name;
	const char* immediate_name;
	void* param;
	type_data_t* next;
} type_data_t;

typedef struct _token_base
{
	char* val;
	token_type_t type;
	token_type_t subtype;
	void* eval;
	type_data_t type_data;
} token_t;

typedef struct _enum_value_base
{
	const char* name;
	long long value;
} enum_value_t;

#define T int
#include "vector.h"

#define T float
#include "vector.h"

typedef char* lpstr;
#define T lpstr
#include "vector.h"

#define T token_t
#include "vector.h"

#define T char
#include "vector.h"

#define T type_data_t
#include "vector.h"

#define T enum_value_t
#include "vector.h"

#endif
