#include "unidef.h"
#include "utils.h"

extern index_t n_special_characters;
extern char special_character[];

token_t_vector_t* call_lexer(const char* file_name);

index_t find_keyword(const char* str);

