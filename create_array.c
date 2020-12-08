#include <stdio.h>

#include "ezJSON/ezJSON.h"

int main(int argc, char *argv[])
{
    char jsonStr[1024];

    char* string[3] = {"one", "two", "three"};
    float number[3] = {1, 2, 3};

    ezJSON(jsonStr)
    {
        // 使用索引
        ARR("array1", 3) { STR(NULL, string[_IDX]); }}

        // 不使用索引
        ARR("array2", -1)
        {
            NUM(NULL, number[0]);
            NUM(NULL, number[1]);
            NUM(NULL, number[2]);
        }}

        ARR("array3", 3) {OBJ(NULL) 
        {
            STR("string", string[_IDX]);
            NUM("number", number[_IDX]);
        }}}}
        
        ARR("array4", -1)
        {
            ARR(NULL, 3) { STR(NULL, string[_IDX]); }}
            ARR(NULL, 3) { NUM(NULL, number[_IDX]); }}
        }}
    }}

    printf("%s\n", jsonStr);

    return 0;
}