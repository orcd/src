
#include <cjson/cJSON.h>
#include <stdio.h>
/*
    {
        name: "tom",
        age: 10,
        mobile: null,
        man: true,
        bike:
        {
            branch: "yongjiu"
        }
        score:[
            90,
            20,
            30,
            40
        ]
    }


    [

    ]
*/

void parse(char* jsonbuf)
{
    cJSON* root = cJSON_Parse(jsonbuf);

    cJSON* name = cJSON_GetObjectItem(root, "name");
    printf("%s=%s\n", name->string, name->valuestring);

    cJSON* age = cJSON_GetObjectItem(root, "age");
    printf("%s=%g\n", age->string, age->valuedouble);

    cJSON* mobile = cJSON_GetObjectItem(root, "mobile");
    printf("%d\n", mobile->type);


     cJSON*bike = cJSON_GetObjectItem(root, "bike");
     cJSON* branch = cJSON_GetObjectItem(bike, "branch");

     cJSON* score = cJSON_GetObjectItem(root, "score");
     cJSON* score2 = cJSON_GetArrayItem(score, 1);
     printf("score2 = %g\n", score2->valuedouble);
}

int main()
{

    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "tom");
    cJSON_AddNumberToObject(root, "age", 10);
    cJSON_AddNullToObject(root, "mobile");
    cJSON_AddBoolToObject(root, "man", 1);

    cJSON* bike = cJSON_CreateObject();
    cJSON_AddStringToObject(bike, "branch", "yongjiu");
    cJSON_AddItemToObject(root, "bike", bike);

    cJSON* score = cJSON_CreateArray();
    cJSON_AddItemToArray(score, cJSON_CreateNumber(90));
    cJSON_AddItemToArray(score, cJSON_CreateNumber(20));
    cJSON_AddItemToArray(score, cJSON_CreateNumber(30));
    cJSON_AddItemToArray(score, cJSON_CreateNumber(40));

    cJSON_AddItemToObject(root, "score", score);

    char* data = cJSON_Print(root);
    printf("%s\n", data);
    parse(data);

}

