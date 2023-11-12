#include <stdio.h>
#include <curl/curl.h>

// Callback function to handle the received data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    printf("%.*s", (int)total_size, (char *)contents);
    return total_size;
}

int main(void) {
    CURL *curl;
    CURLcode res;

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        // Set the URL to OpenAI's GPT-3.5-turbo API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        // Set the Content-Type header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer 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");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the request payload
        const char *payload = "{\"model\": \"gpt-3.5-turbo-1106\", \"messages\": [{\"role\": \"system\", \"content\": \"You are a helpful assistant.\"}, {\"role\": \"user\", \"content\": \"Hello!\"}]}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

        // Set the callback function to handle the received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return 0;
}

