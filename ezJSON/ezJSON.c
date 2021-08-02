/*
  MIT License

  Copyright (c) 2020 zhoutianhao

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ezJSON.h"

void _ezJsonCreate(char *content)
{
    *(content++) = '{';
    *content = '\0';
}

void _ezJsonCreateEnd(char *content)
{
    content += strlen(content) - 1;

    *(content++) = '}';
    *content = '\0';
}

void _ezJsonPostObject(char *content, char *key)
{
    content += strlen(content);

    if (NULL != key)
    {
        int idx;

        *(content++) = '\"';

        int sizeKey = strlen(key);
        for (idx = 0; idx < sizeKey; idx++)
            *(content++) = *(key + idx);

        *(content++) = '\"';
        *(content++) = ':';
    }

    *(content++) = '{';
    *content = '\0';
}

void _ezJsonPostObjectEnd(char *content)
{
    content += strlen(content) - 1;

    if (',' != *content)
        content++;

    *(content++) = '}';
    *(content++) = ',';
    *content = '\0';
}

void _ezJsonPostArray(char *content, char *key)
{
    int idx;

    content += strlen(content);

    if (NULL != key)
    {
        *(content++) = '\"';
        int sizeKey = strlen(key);
        for (idx = 0; idx < sizeKey; idx++)
            *(content++) = *(key + idx);
        *(content++) = '\"';
        *(content++) = ':';
    }

    *(content++) = '[';
    *content = '\0';
}

void _ezJsonPostArrayEnd(char *content)
{
    content += strlen(content) - 1;

    if (',' != *content)
        content++;

    *(content++) = ']';
    *(content++) = ',';
    *content = '\0';
}

void _ezJsonPostString(char *content, char *key, char *value)
{
    int idx;

    content += strlen(content);

    if (NULL != key)
    {
        *(content++) = '\"';

        int sizeKey = strlen(key);
        for (idx = 0; idx < sizeKey; idx++)
            *(content++) = *(key + idx);

        *(content++) = '\"';
        *(content++) = ':';
    }

    *(content++) = '\"';

    int sizeValue = strlen(value);
    for (idx = 0; idx < sizeValue; idx++)
    {
        if (32 > *(value + idx) || '\\' == *(value + idx) || '\"' == *(value + idx))
        {
            *(content++) = '\\';
            switch (*(value + idx))
            {
            case '\\':
                *(content++) = '\\';
                break;
            case '\"':
                *(content++) = '\"';
                break;
            case '\b':
                *(content++) = 'b';
                break;
            case '\f':
                *(content++) = 'f';
                break;
            case '\n':
                *(content++) = 'n';
                break;
            case '\r':
                *(content++) = 'r';
                break;
            case '\t':
                *(content++) = 't';
                break;
            default:
                *(content++) = '?';
            }
        }
        else
        {
            *(content++) = *(value + idx);
        }
    }

    *(content++) = '\"';
    *(content++) = ',';
    *content = '\0';
}

void _ezJsonPostNumber(char *content, char *key, double value)
{
    char _value[16];
    int idx;

    sprintf(_value, "%lf", value);

    int sizeValue = strlen(_value);
    for (idx = sizeValue - 1; idx >= 0; idx--)
    {
        if ('.' == *(_value + idx))
        {
            for (idx = sizeValue - 1; idx >= 0; idx--)
            {
                if ('0' == *(_value + idx))
                    *(_value + idx) = '\0';
                else
                {
                    if ('.' == *(_value + idx))
                        *(_value + idx) = '\0';
                    break;
                }
            }
            break;
        }
    }

    content += strlen(content);

    if (NULL != key)
    {
        *(content++) = '\"';

        int sizeKey = strlen(key);
        for (idx = 0; idx < sizeKey; idx++)
            *(content++) = *(key + idx);

        *(content++) = '\"';
        *(content++) = ':';
    }

    sizeValue = strlen(_value);
    for (idx = 0; idx < sizeValue; idx++)
        *(content++) = *(_value + idx);

    *(content++) = ',';
    *content = '\0';
}

void _ezJsonPostBool(char *content, char *key, int value)
{
    content += strlen(content);

    if (NULL != key)
    {
        int idx;

        *(content++) = '\"';

        int sizeKey = strlen(key);
        for (idx = 0; idx < sizeKey; idx++)
        {
            *(content++) = *(key + idx);
        }

        *(content++) = '\"';
        *(content++) = ':';
    }

    if (0 == value)
    {
        *(content++) = 'f';
        *(content++) = 'a';
        *(content++) = 'l';
        *(content++) = 's';
    }
    else
    {
        *(content++) = 't';
        *(content++) = 'r';
        *(content++) = 'u';
    }

    *(content++) = 'e';
    *(content++) = ',';
    *content = '\0';
}

void _ezJsonPostNull(char *content, char *key)
{
    int idx;

    content += strlen(content);

    *(content++) = '\"';

    int sizeKey = strlen(key);
    for (idx = 0; idx < sizeKey; idx++)
    {
        *(content++) = *(key + idx);
    }

    *(content++) = '\"';
    *(content++) = ':';
    *(content++) = 'n';
    *(content++) = 'u';
    *(content++) = 'l';
    *(content++) = 'l';
    *(content++) = ',';
    *content = '\0';
}

void _ezJsonClear(char *content)
{
    int _doubleQuotes = 1;
    int idx = 0;

    char *point = content;

    while (*point)
    {
        switch (*point)
        {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        {
            if (0 > _doubleQuotes)
                content[idx++] = *point;
        }
        break;
        case '\"':
        {
            int _existSlash = 1;
            char *_point = point - 1;

            while (content <= _point && '\\' == *_point)
            {
                _existSlash = -_existSlash;
                _point--;
            }

            if (0 < _existSlash)
                _doubleQuotes = -_doubleQuotes;

            content[idx++] = *point;
        }
        break;
        default:
            content[idx++] = *point;
            break;
        }

        point++;
    }

    content[idx] = '\0';
}

int _ezJsonErr(int err)
{
    return err;
}

static char *__ezJsonGetValueStart(char *content, int *err)
{
    *err = 0;

    char *endPtr = content + strlen(content);

    for (; '\0' != *content && content < endPtr; content++)
    {
        switch (*content)
        {
        case ' ':
        case '\b':
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case ',':
            break;
        case '\"':
        case '{':
        case '[':
        case 't':
        case 'f':
        case 'n':
        case '-':
        case ']':
        {
            return content;
        }
        break;
        default:
        {
            if (0x30 > *content || 0x39 < *content)
                *err = ezJSON_ERR_FORMAT;

            return content;
        }
        break;
        }
    }

    return content;
}

static char *__ezJsonGetTargetStart(char *content, int *err, char *key)
{
    *err = 0;

    int _curlyBraces = -1;
    int _doubleQuotes = 1;

    char *_object;
    char *_point;

    int sizeKey = strlen(key);
    char *endPtr = content + strlen(content);

FIND:
    _object = strstr(content, key);

    if (NULL == _object)
    {
        *err = ezJSON_ERR_NOTEXIST;
        return content;
    }

    _point = content;

    for (; _point < _object + sizeKey && '\0' != *_point && endPtr > _point; _point++)
    {
        switch (*_point)
        {
        case '{':
        case '[':
        {
            if (0 < _doubleQuotes)
                _curlyBraces++;
        }
        break;
        case ']':
        case '}':
        {
            if (0 < _doubleQuotes)
                _curlyBraces--;
        }
        break;
        case '\"':
        {
            int _existSlash = 1;
            char *__point = _point - 1;

            while (content <= __point && '\\' == *__point)
            {
                _existSlash = -_existSlash;
                __point--;
            }

            if (0 < _existSlash)
                _doubleQuotes = -_doubleQuotes;
        }
        break;
        }
    }

    content = _object + sizeKey;

    if ('\"' == *(_object - 1) && '\"' == *content)
    {
        for (content++; '\0' != *content && content < endPtr; content++)
        {
            switch (*content)
            {
            case ' ':
                break;
            default:
            {
                if (':' == *content && 0 == _curlyBraces)
                    goto NEXT;

                content = _object + sizeKey;
                goto FIND;
            }
            break;
            }
        }
    NEXT:
        content = __ezJsonGetValueStart(content + 1, err);
        if (0 > *err)
            return content;
    }
    else
        goto FIND;

    return content;
}

static char *__ezJsonGetTargetStop(char *content, int *err, int *type)
{
    *err = 0;

    char *revalue = NULL;
    char *_point = content;
    char *endPtr = content + strlen(content);

    switch (*_point)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
    case '-':
    {
        *type = ezJSON_NUMBER;

        for (; '\0' != *_point && endPtr > _point; _point++)
        {
            if ('.' != *_point && ('0' > *_point || '9' < *_point))
            {
                revalue = _point;
                return revalue;
            }
        }

        *err = ezJSON_ERR_FORMAT;
        return revalue;
    }
    break;
    case 't':
    case 'f':
    {
        *type = ezJSON_BOOL;

        if (*_point == 't' && *(_point + 1) == 'r' && *(_point + 2) == 'u' && *(_point + 3) == 'e')
            revalue = _point + 4;
        else if (*_point == 'f' && *(_point + 1) == 'a' && *(_point + 2) == 'l' && *(_point + 3) == 's' && *(_point + 4) == 'e')
            revalue = _point + 5;
        else
            *err = ezJSON_ERR_FORMAT;

        return revalue;
    }
    break;
    case 'n':
    {
        *type = ezJSON_NULL;

        if (*_point == 'n' && *(_point + 1) == 'u' && *(_point + 2) == 'l' && *(_point + 3) == 'l')
            revalue = _point + 4;
        else
            *err = ezJSON_ERR_FORMAT;

        return revalue;
    }
    break;
    case '{':
    {
        *type = ezJSON_OBJECT;

        int _existBraces = 1;
        int _doubleQuotes = 1;

        for (_point++; '\0' != *_point && endPtr > _point; _point++)
        {
            switch (*_point)
            {
            case '{':
            {
                if (0 < _doubleQuotes)
                    _existBraces++;
            }
            break;
            case '}':
            {
                if (0 < _doubleQuotes)
                    _existBraces--;
            }
            break;
            case '\"':
            {
                int _existSlash = 1;
                char *__point = _point - 1;

                while (content <= __point && '\\' == *__point)
                {
                    _existSlash = -_existSlash;
                    __point--;
                }

                if (0 < _existSlash)
                    _doubleQuotes = -_doubleQuotes;
            }
            break;
            }

            if (1 > _existBraces)
            {
                revalue = _point + 1;
                return revalue;
            }
        }

        *err = ezJSON_ERR_FORMAT;
        return revalue;
    }
    break;
    case '[':
    {
        *type = ezJSON_ARRAY;

        int _existBraces = 1;
        int _doubleQuotes = 1;

        for (_point++; '\0' != *_point && endPtr > _point; _point++)
        {
            switch (*_point)
            {
            case '[':
            {
                if (0 < _doubleQuotes)
                    _existBraces++;
            }
            break;
            case ']':
            {
                if (0 < _doubleQuotes)
                    _existBraces--;
            }
            break;
            case '\"':
            {
                int _existSlash = 1;
                char *__point = _point - 1;

                while (content <= __point && '\\' == *__point)
                {
                    _existSlash = -_existSlash;
                    __point--;
                }

                if (0 < _existSlash)
                    _doubleQuotes = -_doubleQuotes;
            }
            break;
            }

            if (1 > _existBraces)
            {
                revalue = _point + 1;
                return revalue;
            }
        }

        *err = ezJSON_ERR_FORMAT;
        return revalue;
    }
    break;
    case '\"':
    {
        *type = ezJSON_STRING;

        for (_point++; '\0' != *_point; _point++)
        {
            if ('\"' == *_point)
            {
                int _existSlash = 1;
                char *__point = _point - 1;

                while (content <= __point && '\\' == *__point)
                {
                    _existSlash = -_existSlash;
                    __point--;
                }

                if (0 < _existSlash)
                {
                    revalue = _point + 1;
                    return revalue;
                }
            }
        }

        *err = ezJSON_ERR_FORMAT;
        return revalue;
    }
    break;
    default:
        *err = ezJSON_ERR_SYMBOL;
        return revalue;
    }

    return revalue;
}

int _ezJsonGetType(char *content, int *err, char *key)
{
    *err = 0;

    int revalue = 0;
    char *begin = content;

    if (NULL != key)
    {
        begin = __ezJsonGetTargetStart(content, err, key);
        if (0 > *err)
        {
            revalue = *err;
            return revalue;
        }
    }
    else
        revalue = ezJSON_ERR_NONE;

    __ezJsonGetTargetStop(begin, err, &revalue);
    if (0 > *err)
        revalue = *err;

    return revalue;
}

char *_ezJsonGetObject(char *content, int *err, char *key)
{
    *err = 0;

    char *revalue = content;
    char *begin = content;

    if (NULL != key)
    {
        begin = __ezJsonGetTargetStart(content, err, key);
        if (0 > *err)
            return revalue;

        revalue = begin;
    }
    else
    {
        begin = __ezJsonGetValueStart(begin, err);
        if (0 > *err)
            return revalue;

        int type;
        char *end = __ezJsonGetTargetStop(begin, err, &type);
        if (0 > *err)
            return revalue;

        revalue = end + 1;
    }

    return revalue;
}

char *_ezJsonGetArray(char **content, int *err, int *size, char *key)
{
    *err = 0;
    char *revalue = *content;
    char *begin = *content;

    char *endPtr = *content + strlen(*content);

    if (NULL != key)
        begin = __ezJsonGetTargetStart(*content, err, key);
    else
        begin = __ezJsonGetValueStart(*content, err);

    int type;
    __ezJsonGetTargetStop(begin, err, &type);
    if (0 > *err)
        return revalue;

    if (ezJSON_ARRAY != type)
    {
        *err = ezJSON_ERR_FORMAT;
        return revalue;
    }

    int _existComma = 0;
    int _doubleQuotes = 1;
    int _curlyBraces = 0;
    char *_point = begin;

    for (; '\0' != *_point && endPtr > _point && (']' != *(_point - 1) || 0 != _curlyBraces); _point++)
    {
        switch (*_point)
        {
        case ',':
        {
            if (0 < _doubleQuotes && 1 == _curlyBraces)
                _existComma++;
        }
        break;
        case '{':
        case '[':
        {
            if (0 < _doubleQuotes)
                _curlyBraces++;
        }
        break;
        case ']':
        case '}':
        {
            if (0 < _doubleQuotes)
                _curlyBraces--;
        }
        break;
        case '\"':
        {
            int _existSlash = 1;
            char *__point = _point - 1;

            while (*content <= __point && '\\' == *__point)
            {
                _existSlash = -_existSlash;
                __point--;
            }

            if (0 < _existSlash)
                _doubleQuotes = -_doubleQuotes;
        }
        break;
        }
    }

    *size = _existComma + 1;

    if (0 == _existComma)
        *size = 0;

    if (NULL == key)
        revalue = __ezJsonGetValueStart(_point, err);

    *content = begin + 1;

    return revalue;
}

char *_ezJsonGetValue(char *content, int *err, char *key, void *value)
{
    *err = 0;

    char *revalue = content;
    char *begin = content;

    if (NULL != key)
    {
        begin = __ezJsonGetTargetStart(content, err, key);
        if (0 > *err)
            return revalue;
    }
    begin = __ezJsonGetValueStart(begin, err);
    if (0 > *err)
        return revalue;

    int type;
    char *end = __ezJsonGetTargetStop(begin, err, &type);
    if (0 > *err)
        return revalue;

    if (NULL == key)
    {
        revalue = __ezJsonGetValueStart(end, err);
        if (0 > *err)
            return revalue;
    }

    switch (type)
    {
    case ezJSON_NULL:
    {
    }
    break;
    case ezJSON_BOOL:
    {
        if ('t' == *begin)
            *((int *)value) = 1;
        else
            *((int *)value) = 0;
    }
    break;
    case ezJSON_NUMBER:
    {
        char _value[16];

        sprintf(_value, "%.*s", (int)(end - begin), begin);
        *((float *)value) = atof(_value);
    }
    break;
    case ezJSON_STRING:
    {
        char *_value = (char *)value;
        char *_point = begin + 1;

        int idx;
        for (idx = 0; idx < end - begin - 2; idx++)
        {
            if ('\\' == _point[idx])
            {
                switch (_point[++idx])
                {
                case '\\':
                case '\"':
                case '/':
                    *(_value++) = _point[idx];
                    break;
                case 'b':
                    *(_value++) = '\b';
                    break;
                case 'f':
                    *(_value++) = '\f';
                    break;
                case 'n':
                    *(_value++) = '\n';
                    break;
                case 'r':
                    *(_value++) = '\r';
                    break;
                case 't':
                    *(_value++) = '\t';
                    break;
                default:
                    *err = ezJSON_ERR_FORMAT;
                    return revalue;
                }
            }
            else
                *(_value++) = _point[idx];
        }

        *_value = '\0';
    }
    break;
    }

    *err = type;

    return revalue;
}
