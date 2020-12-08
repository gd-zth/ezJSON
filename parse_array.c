#include <stdio.h>

#include "ezJSON/ezJSON.h"

typedef struct DATASTRUCT
{
    char    strings[3][16];
    float   numbers[3];
    struct 
    {
        char    string[16];
        float   number;

    }objects[3];
    struct
    {
        char    string[3][16];
        float   number[3];

    }arrays;

}Data;

int main(int argc, char *argv[])
{
    char jsonStr[1024];
    Data data;
    int err;

    FILE *pFile = fopen("parse_array.json", "r");

    fseek(pFile, 0L, SEEK_END);
    long lenFile = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);

    jsonStr[fread(jsonStr, 1, lenFile, pFile)] = '\0';

    fclose(pFile);

    _ezJSON(NULL, jsonStr)
    {
        _ARR("strings") {_VAL(NULL, data.strings[_IDX]); }}

        _ARR("numbers")
        {
            _VAL(NULL, data.numbers[_IDX]); 
        }}

        _ARR("objects") {_OBJ(NULL) {
            _VAL("string", data.objects[_IDX].string);
            _VAL("number", data.objects[_IDX].number);
        }}}}

        _ARR("arrays") {
            _ARR(NULL) {_VAL(NULL, data.arrays.string[_IDX]); }}
            _ARR(NULL) {_VAL(NULL, data.arrays.number[_IDX]); }}
        }}

    }_END_}

    return 0;
}
