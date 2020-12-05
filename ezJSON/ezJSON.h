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

#ifndef _EZJSON_H_
#define _EZJSON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ezJSON_NULL     1
#define ezJSON_OBJECT   2
#define ezJSON_ARRAY    3
#define ezJSON_STRING   4
#define ezJSON_NUMBER   5
#define ezJSON_BOOL     6

#define ezJSON_ERR_NONE      0
#define ezJSON_ERR_SYMBOL   -1
#define ezJSON_ERR_NOTEXIST -2
#define ezJSON_ERR_FORMAT   -3

void _ezJsonCreate(char *content) ;
void _ezJsonCreateEnd(char *content) ;
void _ezJsonPostObject(char *content, char *key) ;
void _ezJsonPostObjectEnd(char *content) ;
void _ezJsonPostArray(char *content, char *key) ;
void _ezJsonPostArrayEnd(char *content) ;
void _ezJsonPostString(char *content, char *key, char *value) ;
void _ezJsonPostNumber(char *content, char *key, double value) ;
void _ezJsonPostBool(char *_ezJSONContent, char *_ezJSONKey, int _ezJSONValue) ;
void _ezJsonPostNull(char *content, char *key) ;

void _ezJsonClear(char *content) ;
int _ezJsonErr(int err) ;
int _ezJsonGetType(char *content, int *err, char *key) ;
char *_ezJsonGetObject(char *content, int *err, char *key) ;
char *_ezJsonGetArray(char *content, int *err, int *size, char *key) ;
char *_ezJsonGetValue(char *content, int *err, char *key, void *value) ;

#define ezJSON(_CONTENT) {\
            char *_ezJSON_CONTENT = _CONTENT;\
            _ezJsonCreate(_ezJSON_CONTENT);\
            int ezJSON_IDX;\
            for (ezJSON_IDX = 0; ezJSON_IDX++ < 1; _ezJsonCreateEnd(_ezJSON_CONTENT))

#define OBJ(_ezJSON_KEY) {\
            _ezJsonPostObject(_ezJSON_CONTENT, _ezJSON_KEY);\
            int ezJSON_IDX;\
            for (ezJSON_IDX = 0; ezJSON_IDX++ < 1; _ezJsonPostObjectEnd(_ezJSON_CONTENT))

#define ARR(_ezJSON_KEY, _ezJSON_ARRAY_SIZE) {\
            _ezJsonPostArray(_ezJSON_CONTENT, _ezJSON_KEY);\
            int ezJSON_IDX;\
            int _IDX;\
            for (ezJSON_IDX = 0; ezJSON_IDX++ < 1; _ezJsonPostArrayEnd(_ezJSON_CONTENT))\
                if (0 > _ezJSON_ARRAY_SIZE)\
                    for (_IDX = 0; _IDX < _ezJSON_ARRAY_SIZE; _IDX ++)

#define NUM(_ezJSON_KEY, _ezJSON_VALUE)\
            _ezJsonPostNumber(_ezJSON_CONTENT, _ezJSON_KEY, _ezJSON_VALUE);

#define STR(_ezJSON_KEY, _ezJSON_VALUE)\
            _ezJsonPostString(_ezJSON_CONTENT, _ezJSON_KEY, _ezJSON_VALUE);

#define BOL(_ezJSON_KEY, _ezJSON_VALUE)\
            _ezJsonPostBool(_ezJSON_CONTENT, _ezJSON_KEY, _ezJSON_VALUE);

#define NUL(_ezJSON_KEY)\
            _ezJsonPostNull(_ezJSON_CONTENT, _ezJSON_KEY);

#define _ezJSON(_ERR, _CONTENT) {\
            char *_ezJSON_CONTENT = _CONTENT;\
            int _ezJSON_ERR = ezJSON_ERR_NONE;\
            int *_ezJSON_ERR_P = &_ezJSON_ERR;\
            if (NULL != _ERR)\
                _ezJSON_ERR_P = _ERR;\
            int ezJSON_IDX;\
            for (ezJSON_IDX = 0; ezJSON_IDX++ < 1; *_ezJSON_ERR_P = _ezJSON_ERR)

#define _OBJ(_ezJSON_KEY) _ezJsonErr(_ezJSON_ERR); {\
            char **__ezJSON_CONTENT = &_ezJSON_CONTENT;\
            char *_ezJSON_CONTENT = *__ezJSON_CONTENT;\
            if (0 == _ezJSON_ERR)\
                if (NULL == _ezJSON_KEY)\
                    *__ezJSON_CONTENT = _ezJsonGetObject(_ezJSON_CONTENT, &_ezJSON_ERR, _ezJSON_KEY);\
                else\
                    _ezJSON_CONTENT = _ezJsonGetObject(_ezJSON_CONTENT, &_ezJSON_ERR, _ezJSON_KEY);

#define _ARR(_ezJSON_KEY) _ezJsonErr(_ezJSON_ERR); {\
            char **__ezJSON_CONTENT = &_ezJSON_CONTENT;\
            char *_ezJSON_CONTENT = *__ezJSON_CONTENT;\
            int zJSON_ARRAY_SIZE = 0;\
            if (0 == _ezJSON_ERR)\
                _ezJSON_CONTENT = _ezJsonGetArray(_ezJSON_CONTENT, &_ezJSON_ERR, &zJSON_ARRAY_SIZE, _ezJSON_KEY);\
            int _IDX;\
            for(_IDX = 0; _IDX < zJSON_ARRAY_SIZE; _IDX ++)

#define _VAL(_ezJSON_KEY, _ezJSON_VALUE) _ezJsonErr(_ezJSON_ERR);\
            if (0 == _ezJSON_ERR)\
                if (NULL == _ezJSON_KEY)\
                    _ezJSON_CONTENT = _ezJsonGetValue(_ezJSON_CONTENT, &_ezJSON_ERR, _ezJSON_KEY, &_ezJSON_VALUE);\
                else\
                    _ezJsonGetValue(_ezJSON_CONTENT, &_ezJSON_ERR, _ezJSON_KEY, (void *)(&_ezJSON_VALUE));

#define _TYPE(_ezJSON_KEY)\
                _ezJsonGetType(_ezJSON_CONTENT, &_ezJSON_ERR, _ezJSON_KEY)

#define _CLR(_CONTENT)\
            _ezJsonClear(_CONTENT);

#ifdef __cplusplus
}
#endif

#endif
