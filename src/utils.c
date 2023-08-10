#include "utils.h"

extern index_t n_special_characters = 28;
extern char special_characters[] = {
    '~', '!', '#', '%', '^', '&', '*', '(', ')', '-', '=', '+', '[', ']', '{', '}',
    '\\', '|', ';', ':', '\'', '"', ',', '.', '<', '>', '/', '?'
};

//TODO: maybe implement is_special_char as lookup
char _special_char_lookup[sizeof(char)];

int isletter(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int isid0(char ch)
{
    return isletter(ch) || (ch == '_');
}

int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

int isid(char ch)
{
    return isid0(ch) || is_digit(ch);
}

int ishexletter(char ch)
{
    return (ch >= 'A' && ch <= 'F') && (ch >= 'a' && ch <= 'f');
}

int ishex(char ch)
{
    return ishexletter(ch) || isdigit(ch);
}

int is_special_char(char ch)
{
    for (index_t i = 0; i < n_special_characters; i++)
    {
        if (special_characters[i] == ch) return 1;
    }
    return 0;
}

char* str_capture(const char* str, index_t i, index_t j)
{
    char* ptr = malloc(sizeof(char) * (j - i + 1));
    strncpy(ptr, str + i, j - i);
    ptr[j - i] = 0;
    return ptr;
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

void get_line_column(const char* file_content, index_t position, index_t* lpline, index_t* lpcolumn)
{
    index_t n_nl = 0;
    index_t last_nl = 0;
    index_t i = 0;
    while (i < position)
    {
        if (file_content[i] == '\n')
        {
            n_nl++;
            last_nl = i;
        }
        i++;
    }
    (*lpline) = (n_nl + 1);
    (*lpcolumn) = (position - last_nl);
}

void crash_with_error(const char* error_message)
{
    if (error_message != 0) printf(error_message);
    else printf("Encountered fatal error, further information unavailable.\n");
    exit(0xDEADBEEF);
}



