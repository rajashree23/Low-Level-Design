#include <string>
#include <map>
#include <stdexcept>
#include <iostream>

class HttpRequest {
private:
    std::string url;
    std::string method;
    std::map<std::string, std::string> headers;
    std::string body;

public:

    class Builder {
    private:
        std::string urlValue;
        std::string methodValue;
        std::map<std::string, std::string> headersValue;
        std::string bodyValue;

    public:
        Builder& url(const std::string& value) {
            urlValue = value;
            return *this;
        }

        Builder& method(const std::string& value) {
            methodValue = value;
            return *this;
        }

        Builder& header(const std::string& key,
                        const std::string& value) {
            headersValue[key] = value;
            return *this;
        }

        Builder& body(const std::string& value) {
            bodyValue = value;
            return *this;
        }

        HttpRequest build() {
            if (urlValue.empty()) {
                throw std::invalid_argument("URL is required");
            }

            HttpRequest request;

            request.url = urlValue;
            request.method = methodValue;
            request.headers = headersValue;
            request.body = bodyValue;

            return request;
        }
    };

    const std::string& getUrl() const {
        return url;
    }

    const std::string& getMethod() const {
        return method;
    }

    const std::map<std::string, std::string>& getHeaders() const {
        return headers;
    }

    const std::string& getBody() const {
        return body;
    }
};

int main() {
    HttpRequest request =
        HttpRequest::Builder()
            .url("https://api.example.com")
            .method("POST")
            .header("Content-Type", "application/json")
            .body("{\"key\": \"value\"}")
            .build();

    std::cout << request.getUrl()<<"\n";

    return 0;
}