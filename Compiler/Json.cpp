#include "Json.h"

using namespace std;

string createJson(
    const map<string, string>& items,
    const std::string& newline_prefix,
    bool quote_values
){
    std::string out = newline_prefix+"{\n";
    int cnt = 0;
    const char* optq = quote_values ? "\"" : "";
    for(const auto& [key, value]: items) {
        out += newline_prefix+"\t\"" + key + "\":" + optq+value+optq + (++cnt != items.size() ? "," : "" ) + "\n";
    }
    out += newline_prefix+"}";
    return out;
}

std::string createJson(
    const std::vector<std::string>& items,
    const std::string& newline_prefix,
    bool quote_elements
) {
    std::string out = newline_prefix+"[\n";
    int cnt = 0;
    const char* optq = quote_elements ? "\"" : "";
    for(const auto& elem: items) {
        out += newline_prefix+"\t" + optq+elem+optq + (++cnt != items.size() ? "," : "" ) + "\n";
    }
    out += newline_prefix+"]";
    return out;
}