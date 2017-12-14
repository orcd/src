#include <string.h>
#include <stdio.h>
#include <curl/curl.h>

// ptr: 从服务器收到的数据的头指针
// size: 一个unit的长度
// nmemb: 有多少个unit
//          总长度 = size * nmemb fwrite(...)
// userdata:
// 返回值：要求等于size*nmemb

struct UserData
{
    char buf[1024];
    int len;
};

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    UserData* d = (char*)userdata;
    memcpy(d->buf+d->len, ptr, size*nmemb);
    d->len += size*nmemb;
    return size*nmemb;
}

int main()
{
    // 创建一个curl对象
    CURL* curl = curl_easy_init();

    const char* data ="hello from curl";

    // 设置URL
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:10099");
    // 设置curl，使用POST方法发请求
//    curl_easy_setopt(curl, CURLOPT_POST, 1);
//    curl_easy_setopt(curl, CURLOPT_PORT, 10099);
    // 设置curl，POST的数据内容
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
//    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    UserData data1;
    data1.len = 0;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data1);

    // 执行请求  向服务器发送http请求
    // 从服务器接收响应，并且解析，并且打印
    curl_easy_perform(curl);
    /*
        send_data_to_server(...);
        while(1)
        {
            char buf[1024];
            int ret = read_data_from_server(..);
            if(write_callback(buf, ret, 1, NULL) != ret)
                break;
        }
    */
    printf("%s\n", buf);
    len = 0;

}
