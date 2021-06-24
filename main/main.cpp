#include <stdio.h>
#include <curl/curl.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>


size_t dataSize=0;
size_t curlWriteFunction(void* ptr, size_t size/*always==1*/,
                         size_t nmemb, void* userdata)
{
    printf("Came here\n");
    char** stringToWrite=(char**)userdata;
    const char* input=(const char*)ptr;
    if(nmemb==0) return 0;
    if(!*stringToWrite)
        *stringToWrite=(char*)malloc(nmemb+1);
    else
        *stringToWrite=(char*)realloc(*stringToWrite, dataSize+nmemb+1);
    memcpy(*stringToWrite+dataSize, input, nmemb);
    dataSize+=nmemb;
    (*stringToWrite)[dataSize]='\0';
    return nmemb;
}

int main(int argc, char const *argv[])
{
    char* data=0;
    CURL * curl = curl_easy_init();
    if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://check.torproject.org");
    curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_PROXY, "socks5h://localhost:9050");
    curl_easy_setopt(curl, CURLOPT_PROXYPORT, 9050L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curlWriteFunction);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    CURLcode res = curl_easy_perform(curl);

        if(res !=CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              return -1;
        }

         curl_easy_cleanup(curl);

    if(!data)
    {
        fprintf(stderr, "Got no data\n");
        return 1;
    }

    printf("Page data:\n\n%s\n", data);
    free(data);
    }
    return 0;
}
