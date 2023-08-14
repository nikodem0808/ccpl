#include "utils.h"

extern index_t n_special_characters = 28;
extern char special_characters[] = {
    '~', '!', '#', '%', '^', '&', '*', '(', ')', '-', '=', '+', '[', ']', '{', '}',
    '\\', '|', ';', ':', '\'', '"', ',', '.', '<', '>', '/', '?'
};

extern index_t n_special_wcharacters = 28;
extern wchar special_wcharacters[] = {
    L'~', L'!', L'#', L'%', L'^', L'&', L'*', L'(', L')', L'-', L'=', L'+', L'[', L']', L'{', L'}',
    L'\\', L'|', L';', L':', L'\'', L'"', L',', L'.', L'<', L'>', L'/', L'?'
};

//TODO: maybe implement is_special_char as lookup
unsigned char _special_char_lookup[sizeof(char)];
unsigned char _special_wchar_lookup[sizeof(wchar)];

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

int is01(char ch)
{
    return ch == '0' || ch == '1';
}

int isoct(char ch)
{
    return (ch >= '0') && (ch <= '8');
}

int wisletter(wchar ch)
{
    return (ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z');
}

int wisid0(wchar ch)
{
    return wisletter(ch) || (ch == L'_');
}

int wis_digit(wchar ch)
{
    return (ch >= L'0' && ch <= L'9');
}

int wisid(wchar ch)
{
    return wisid0(ch) || wis_digit(ch);
}

int wishexletter(wchar ch)
{
    return (ch >= L'A' && ch <= L'F') && (ch >= L'a' && ch <= L'f');
}

int wishex(wchar ch)
{
    return wishexletter(ch) || wisdigit(ch);
}

int wis_special_char(wchar ch)
{
    for (index_t i = 0; i < n_special_wcharacters; i++)
    {
        if (special_wcharacters[i] == ch) return 1;
    }
    return 0;
}

int wis01(wchar ch)
{
    return (ch == L'0') || (ch == L'1');
}

int wisoct(wchar ch)
{
    return (ch >= L'0') && (ch <= L'8');
}

char* str_capture(const char* str, index_t i, index_t j)
{
    char* ptr = malloc(sizeof(char) * (j - i + 1));
    strncpy(ptr, str + i, j - i);
    ptr[j - i] = 0;
    return ptr;
}

wchar* wcs_capture(const wchar* wstr, index_t i, index_t j)
{
    wchar* ptr = malloc(sizeof(wchar) * (j - i + 1));
    wcscpy(ptr, wstr + i, j - i);
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

wchar_vector_t* wread_file(const char* file_name)
{
	wchar_vector_t* wfile_content = new_char_vector_hijack(malloc(sizeof(wchar) * 128), 0, 128);
	wchar buf[513] = { 0 };
	size_t n_read = 0;
	FILE* fl = fopen(file_name, "r");
	do
	{
        fgetws(buf, 513, fl);
		n_read = wcslen(buf);
		wchar_vector_push_back_n(wfile_content, buf, n_read);
	} while(n_read == 512);
	wchar_vector_push_back(wfile_content, L'\0');
	fclose(fl);
    return wfile_content;
}

void lpstr_destructor(lpstr* ptr)
{
    free(*ptr);
}

void lpwcs_destructor(lpwcs* ptr)
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

void wget_line_column(const wchar* wfile_content, index_t position, index_t* lpline, index_t* lpcolumn)
{
    index_t n_nl = 0;
    index_t last_nl = 0;
    index_t i = 0;
    while (i < position)
    {
        if (wfile_content[i] == L'\n')
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

void wcrash_with_error(const wchar* error_message)
{
    if (error_message != 0) wprintf(error_message);
    else wprintf(L"Encountered fatal error, further information unavailable.\n");
    exit(0xDEADBEEF);
}

