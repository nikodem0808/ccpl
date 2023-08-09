#include "utils.h"

int isid0(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '_');
}

int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

int isid(char ch)
{
    return isid0(ch) || is_digit(ch);
}

char_vector_t* read_file(const char* file_name)
{
	char_vector_t* file_content = new_char_vector_hijack(malloc(sizeof(char) * 128), 0, 128);
	char buf[512] = { 0 };
	size_t n_read = 0;
	FILE* fl = fopen(file_name, "r");
	do
	{
		n_read = fread(buf, sizeof(char), 512, fl);
		char_vector_push_back_n(file_content, buf, n_read);
	} while(n_read == 512);
	char_vector_push_back(file_content, '\0');
	fclose(fl);
    return file_content;
}

void lpstr_destructor(lpstr* ptr)
{
    free(*ptr);
}

void enum_value_t_destructor(enum_value_t* ptr)
{
    free(ptr->name);
}

void type_data_t_destructor(type_data_t* ptr)
{
    type_data_t_destructor(ptr->next);
    free(ptr->next);
    free(ptr->full_name);
    free(ptr->immediate_name);
    free(ptr->real_name);
    if (ptr->kind != TK_ARRAY) free(ptr->param);
}



