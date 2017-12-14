#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <string.h>

int main()
{
    char username[1024];
    fgets(username, sizeof(username), stdin);
    username[strlen(username)-1]=0;
    char password[1024];
    fgets(password, sizeof(password), stdin);
    password[strlen(password)-1] = 0;

    /*
        {
            username: username,
            password: password
        }

        {}
    */

    cJSON* json = cJSON_CreateObject();
    cJSON_AddItemToObject(json, "username", cJSON_CreateString(username));
    cJSON_AddItemToObject(json, "password", cJSON_CreateString(password));

    char* json_buf = cJSON_Print(json);
    printf("%s\n", json_buf);

    // 上传
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:10098");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_buf);

    curl_easy_perform(curl);
}
