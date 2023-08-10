#include "lexer.h"

extern index_t n_special_characters = 28;
extern char special_character[] = {
    '~', '!', '#', '%', '^', '&', '*', '(', ')', '-', '=', '+', '[', ']', '{', '}',
    '\\', '|', ';', ':', '\'', '"', ',', '.', '<', '>', '/', '?'
};

/*
| Lexed tokens:
| - preprocessor directives
| - special charaters
| - identifiers (at this stage, words)
*/
token_t_vector_t* call_lexer(char_vector_t* file_content)
{
    token_t_vector_t* tokenvec = new_token_t_vector_hijack(malloc(sizeof(token_t) * 128), 0, 128);
    token_t token = { 0 };
    const char* flstr = file_content->dat_ptr;
    index_t strsize = char_vector_size(file_content);
    token_type_t current_token_type = token_NA; // maybe unused
    for (index_t i = 0; i < strsize; i++)
    {
        if (isspace(flstr[i])) continue;
        if (flstr[i] == '#')
        {
            index_t j = i;
            while (flstr[j] != '\n')
            {
                if (flstr[j] == '\\')
                {
                    j++;
                    if (j == strsize) break;
                }
                j++;
                if (j == strsize) break;
            }
            token.type = token_preprocessor_directive;
            token.subtype = token_preprocessor_directive;
            token.val = str_capture(flstr, i, j);
            i = j;
        }
        if (isid0(flstr[i]))
        {
            index_t j = i;
            while (isid(flstr[j]))
            {
                j++;
            }
        }
    }
    return tokenvec;
}

index_t find_keyword(const char* str)
{
    for (int i = 0; i < n_keywords; i++)
    {
        if (strcmp(keywords_g[i], str) == 0)
        {
            return i;
        }
    }
    return INDEX_T_NOT_FOUND;
}


