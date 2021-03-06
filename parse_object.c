#include <stdio.h>

#include "ezJSON/ezJSON.h"

typedef struct DATASTRUCT
{
    char    title[64];
    struct 
    {
        char    string[64];
        float   number;
        int     bool;
        struct
        {
            char    string[64];
            float   number;
            int     bool;
            
        }object_2;
        
    }object_1;

} Data;

int main(int argc, char *argv[])
{
    char jsonStr[1024];
    Data data;

    FILE *pFile = fopen("parse_object.json", "r");

    fseek(pFile, 0L, SEEK_END);
    long lenFile = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);

    jsonStr[fread(jsonStr, 1, lenFile, pFile)] = '\0';

    fclose(pFile);

    _ezJSON(NULL, jsonStr)
    {
        _VAL("title", data.title);

        _OBJ("object_1")
        {
            _VAL("string", data.object_1.string);
            _VAL("number", data.object_1.number);
            _VAL("bool",   data.object_1.bool);

            _OBJ("object_2")
            {
                _VAL("string", data.object_1.object_2.string);
                _VAL("number", data.object_1.object_2.number);
                _VAL("bool",   data.object_1.object_2.bool);
            }}
        }}

    }_END_}

    return 0;
}
