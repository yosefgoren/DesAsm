#pragma once

#include <string>
#include <vector>
#include <map>

std::string createJson(
    const std::map<std::string, std::string>& items,
    const std::string& newline_prefix = "",
    bool quote_values = false
);

std::string createJson(
    const std::vector<std::string>& items,
    const std::string& newline_prefix = "",
    bool quote_elements = false
);