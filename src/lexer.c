#include "lexer.h"





/*
| Lexed tokens:
| - preprocessor directives
| - special charaters
| - numeric literals (including char, wchar_t and const char[])
| - identifiers (at this stage, all alphanumeric sequences)
*/
token_t_vector_t* call_lexer(char_vector_t* file_content)
{
    token_t_vector_t* tokenvec = new_token_t_vector_hijack(malloc(sizeof(token_t) * 128), 0, 128);
    token_t token = { 0 };
    const char* flstr = file_content->dat_ptr;
    index_t strsize = char_vector_size(file_content);
    for (index_t i = 0; i < strsize;)
    {
        if (isspace(flstr[i])) continue;
        if (flstr[i] == '#')
        {
            index_t j = i;
            while (flstr[j] != '\n' && flstr[j] != 0)
            {
                if (flstr[j] == '\\')
                {
                    j++;
                    if (j == strsize) break;
                }
                j++;
                if (j == strsize) break;
            }
            memset(&token, 0, sizeof(token));
            token.type = token_preprocessor_directive;
            token.subtype = token_preprocessor_directive;
            token.val = str_capture(flstr, i, j);
            token_t_vector_push_back_ref(tokenvec, &token);
            i = j;
            continue;
        }
        if (is_special_char(flstr[i]))
        {
            memset(&token, 0, sizeof(token));
            token.type = token_special_character;
            token.subtype = token_special_character;
            token.val = flstr[i];
            token_t_vector_push_back_ref(tokenvec, &token);
            i++;
            continue;
        }
        if (isid0(flstr[i]))
        {
            // if L, check if parsing a literal
            index_t j = i;
            if (flstr[i] == 'L' && flstr[i + 1] != 0)
            {
                if (flstr[i] == '\'')
                {
                    index_t j = i + 1;
                    while (flstr[j] != /**/)
                    {
                        ;
                    }
                    continue;
                }
            }
            while (isid(flstr[j]))
            {
                j++;
            }
            memset(&token, 0, sizeof(token));
            token.type = token_identifier;
            token.subtype = token_identifier;
            token.val = str_capture(flstr, i, j);
            token_t_vector_push_back_ref(tokenvec, &token);
            i = j;
            continue;
        }
        if (is_digit(flstr[i]))
        {
            memset(&token, 0, sizeof(token));
            index_t j = i + 1;
            if (flstr[i] == '0')
            {
                if (j == strsize || isspace(flstr[j]))
                {
                    token.type = token_numeric_dig_literal;
                    token.subtype = token_int32_literal;
                    token.type_data = primitive_types[find_primitive_type_data("int")];
                    token.eval = 0;
                    break;
                }
                else if (flstr[j] == 'x' || flstr[j] == 'X')
                {
                    if (!ishex(flstr[j + 1]))
                    {
                        index_t line, column;
                        get_line_column(flstr, j, &line, &column);
                        char buf[256] = { 0 };
                        sprintf(buf, "Invalid hexadecimal integer literal @ line %d, column %d", line, column);
                        crash_with_error(buf);
                    }
                    //
                }
                else if (flstr[j] == 'b' || flstr[j] == 'B')
                {
                    if (!ishex(flstr[j + 1]))
                    {
                        index_t line, column;
                        get_line_column(flstr, j, &line, &column);
                        char buf[256] = { 0 };
                        sprintf(buf, "Invalid binary integer literal @ line %d, column %d", line, column);
                        crash_with_error(buf);
                    }
                    //
                }
                else
                {
                    ;
                }
            }
            else
            {
                ;
            }
            token.type = token_preprocessor_directive;
            token.subtype = token_preprocessor_directive;
            token.val = str_capture(flstr, i, j);
            token_t_vector_push_back_ref(tokenvec, &token);
            i = j;
            continue;
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


