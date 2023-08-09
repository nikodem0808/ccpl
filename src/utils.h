
#ifndef UTILS_H
#define UTILS_H

#include "unidef.h"


int isid0(char ch);

int is_digit(char ch);

int isid(char ch);

char_vector_t* read_file(const char* file_name);

void lpstr_destructor(lpstr* ptr);

void enum_value_t_destructor(enum_value_t* ptr);

void type_data_t_destructor(type_data_t* ptr);

#endif
