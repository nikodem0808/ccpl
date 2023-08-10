
#ifndef UTILS_H
#define UTILS_H

#include "unidef.h"

extern index_t n_special_characters;
extern char special_characters[];

int isid0(char ch);

int is_digit(char ch);

int isid(char ch);

int ishexletter(char ch);

int ishex(char ch);

int is_special_char(char ch);

char* str_capture(const char* str, index_t i, index_t j);

char_vector_t* read_file(const char* file_name);

void lpstr_destructor(lpstr* ptr);

void enum_value_t_destructor(enum_value_t* ptr);

void type_data_t_destructor(type_data_t* ptr);

void get_line_column(const char* file_content, index_t position, index_t* lpline, index_t* lpcolumn);

void crash_with_error(const char* error_message);

#endif
