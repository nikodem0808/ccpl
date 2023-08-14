
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

int is01(char ch);

int isoct(char ch);

int wisletter(wchar ch);

int wisid0(wchar ch);

int wis_digit(wchar ch);

int wisid(wchar ch);

int wishexletter(wchar ch);

int wishex(wchar ch);

int wis_special_char(wchar ch);

int wis01(wchar ch);

int wisoct(wchar ch);

char* str_capture(const char* str, index_t i, index_t j);

wchar* wcs_capture(const wchar* wstr, index_t i, index_t j);

char_vector_t* read_file(const char* file_name);

wchar_vector_t* wread_file(const char* file_name);

void lpstr_destructor(lpstr* ptr);

void lpwcs_destructor(lpwcs* ptr);

void enum_value_t_destructor(enum_value_t* ptr);

void type_data_t_destructor(type_data_t* ptr);

void get_line_column(const char* file_content, index_t position, index_t* lpline, index_t* lpcolumn);

void wget_line_column(const wchar* wfile_content, index_t position, index_t* lpline, index_t* lpcolumn);

void crash_with_error(const char* error_message);

void wcrash_with_error(const wchar* werror_message);

#endif
