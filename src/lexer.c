#include "lexer.h"





/*
!!! The file should be preprocessed before lexing
| Lexed tokens:
| - special charaters
| - numeric literals (including char, wchar_t and const char[])
| - identifiers (at this stage, all alphanumeric sequences)
*/
token_t_vector_t* wcall_lexer(wchar_vector_t* file_content)
{
    token_t_vector_t* tokenvec = new_token_t_vector_hijack(malloc(sizeof(token_t) * 128), 0, 128);
    token_t token = { 0 };
    const wchar* flstr = file_content->dat_ptr;
    index_t strsize = wchar_vector_size(file_content);
    for (index_t i = 0; i < strsize;)
    {
        if (iswspace(flstr[i])) continue;
        if (wis_special_char(flstr[i]))
        {
            memset(&token, 0, sizeof(token));
            token.type = token_special_character;
            token.subtype = token_special_character;
            token.val = flstr[i];
            token_t_vector_push_back_ref(tokenvec, &token);
            i++;
            continue;
        }
        if (wisid0(flstr[i]))
        {
            // if L, check if parsing a literal
            index_t j = i;
            if (flstr[i] == L'L' && flstr[i + 1] != 0)
            {
                if (flstr[i] == L'"')
                {
                    j++;
                    while (flstr[j] != L'"')
                    {
                        if (flstr[j] == 0)
                        {
                            index_t line, column;
                            wget_line_column(flstr, j, &line, &column);
                            wchar buf[256] = { 0 };
                            swprintf(buf, L"Expected \" @ line %d, column %d", line, column);
                            wcrash_with_error(buf);
                        }
                        if (flstr[j] == L'\\')
                        {
                            j++;
                            // Resolve escaped character
                        }
                        j++;
                    }
                }
                if (flstr[i] == L'\'')
                {
                    index_t j = i + 1;
                    while (flstr[j] != L'\'')
                    {
                        if (flstr[j] == 0)
                        {
                            index_t line, column;
                            wget_line_column(flstr, j, &line, &column);
                            wchar buf[256] = { 0 };
                            swprintf(buf, 256, L"Expected \" @ line %d, column %d", line, column);
                            wcrash_with_error(buf);
                        }
                        if (flstr[j] == L'\\')
                        {
                            j++;
                            // Resolve escaped character
                        }
                        j++;
                    }
                    continue;
                }
            }
            while (wisid(flstr[j]))
            {
                j++;
            }
            memset(&token, 0, sizeof(token));
            token.type = token_identifier;
            token.subtype = token_identifier;
            token.val = wcs_capture(flstr, i, j);
            token_t_vector_push_back_ref(tokenvec, &token);
            i = j;
            continue;
        }
        if (wis_digit(flstr[i]))
        {
            memset(&token, 0, sizeof(token));
            index_t j = i + 1;
            if (flstr[i] == L'0')
            {
                if (j == strsize || iswspace(flstr[j]))
                {
                    token.type = token_numeric_dig_literal;
                    token.subtype = token_int32_literal;
                    token.type_data = primitive_types[find_primitive_type_data("int")];
                    token.eval = 0;
                    i = j;
                    continue;
                }
                else if (flstr[j] == L'x' || flstr[j] == L'X')
                {
                    if (!wishex(flstr[j + 1]))
                    {
                        index_t line, column;
                        wget_line_column(flstr, j, &line, &column);
                        wchar buf[256] = { 0 };
                        swprintf(buf, 256, L"Invalid hexadecimal integer literal @ line %d, column %d", line, column);
                        wcrash_with_error(buf);
                    }
                    j++;
                    do
                    {
                        j++;
                    } while (wishex(flstr[j]));
                    token.type = token_numeric_hex_literal;
                    token.eval = wcstoll(flstr + i, 0, 0x10);
                    i = j;
                }
                else if (flstr[j] == 'b' || flstr[j] == 'B')
                {
                    if (!wis01(flstr[j + 1]))
                    {
                        index_t line, column;
                        wget_line_column(flstr, j, &line, &column);
                        wchar buf[256] = { 0 };
                        swprintf(buf, 256, L"Invalid binary integer literal @ line %d, column %d", line, column);
                        wcrash_with_error(buf);
                    }
                    j++;
                    do
                    {
                        j++;
                    } while (wis01(flstr[j]));
                    token.type = token_numeric_bin_literal;
                    token.eval = wcstoll(flstr + i, 0, 0b10);
                    i = j;
                }
                else
                {
                    if (!wisoct(flstr[j + 1]))
                    {
                        index_t line, column;
                        wget_line_column(flstr, j, &line, &column);
                        wchar buf[256] = { 0 };
                        swprintf(buf, 256, L"Invalid octal integer literal @ line %d, column %d", line, column);
                        wcrash_with_error(buf);
                    }
                    j++;
                    do
                    {
                        j++;
                    } while (wisoct(flstr[j]));
                    token.type = token_numeric_bin_literal;
                    token.eval = wcstoll(flstr + i, 0, 010);
                    i = j;
                }
            }
            else
            {
                while (wis_digit(flstr[j]))
                {
                    j++;
                }
                token.type = token_numeric_dig_literal;
                token.eval = wcstoll(flstr + i, 0, 10);
                i = j;
            }
            if ((strsize - j) <= 3 && wcsnicmp(flstr + j, L"ULL", 3) == 0)
            {
                token.subtype = token_uint64_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"unsigned long long")];
                j += 3;
            }
            else if ((strsize - j) <= 2 && wcsnicmp(flstr + j, L"UL", 2) == 0)
            {
                token.subtype = token_uint32_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"unsigned long")];
                j += 2;
            }
            else if ((strsize - j) <= 2 && wcsnicmp(flstr + j, L"LL", 2) == 0)
            {
                token.subtype = token_int64_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"long long")];
                j += 2;
            }
            else if ((strsize - j) <= 1 && wcsnicmp(flstr + j, L"U", 1) == 0)
            {
                token.subtype = token_uint32_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"unsigned int")];
                j += 1;
            }
            else if ((strsize - j) <= 1 && wcsnicmp(flstr + j, L"L", 1) == 0)
            {
                token.subtype = token_int32_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"long")];
                j += 1;
            }
            else
            {
                token.subtype = token_int32_literal;
                token.type_data = primitive_types[find_primitive_type_data(L"int")];
            }
            if (wisid(flstr[j]))
            {
                index_t line, column;
                wget_line_column(flstr, j, &line, &column);
                wchar buf[256] = { 0 };
                swprintf(buf, 256, L"Expected end of numeric literal @ line %d, column %d", line, column);
                wcrash_with_error(buf);
            }
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

index_t wfind_keyword(const wchar* str)
{
    for (int i = 0; i < n_wkeywords; i++)
    {
        if (wcscmp(wkeywords_g[i], str) == 0)
        {
            return i;
        }
    }
    return INDEX_T_NOT_FOUND;
}
