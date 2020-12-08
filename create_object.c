#include <stdio.h>

#include "ezJSON/ezJSON.h"

int main(int argc, char *argv[])
{
    char jsonStr[1024];

    ezJSON(jsonStr)
    {
        OBJ("object_1")
        {
            STR("string", "this is object_1 string");
            NUM("number", 23.62);
            BOL("bool", 1);
            OBJ("object_2")
            {
                STR("string", "this is object_2 string");
            }}
        }}
    }}
    
    printf("%s\n", jsonStr);

    return 0;
}