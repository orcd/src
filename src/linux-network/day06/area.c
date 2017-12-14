

#include <curl/curl.h>

int main()
{
    CURL* curl = curl_easy_init();

    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "Authorization: APPCODE 5e195a5cb68c4a42b8d32849aab1c41b");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, "http://ali-city.showapi.com/areaDetail?parentId=440100000000");

    curl_easy_perform(curl);

}
