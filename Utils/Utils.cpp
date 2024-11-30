#include "Utils.h"
#include <regex>


bool is_valid_date_format(const std::string& date) {
    std::regex pattern("\\d{2}[\\.-_ ]\\d{2}[\\.-_ ]\\d{4}");
    if (!std::regex_match(date, pattern)) {
        return false;
    }

    int day, month, year;
    char sep = date.find('-') != std::string::npos ? '-' : date.find('_') != std::string::npos ? '_' : date.find('.') ? '.' : ' ';
    sscanf(date.c_str(), "%d%c%d%c%d", &day, &sep, &month, &sep, &year);

    if (year < 2025) {
        return false;
    }

    return true;
}

bool is_valid_year(const std::string& date)
{
    int day, month, year;
    char sep = date.find('-') != std::string::npos ? '-' : date.find('_') != std::string::npos ? '_' : date.find('.') ? '.' : ' ';
    sscanf(date.c_str(), "%d%c%d%c%d", &day, &sep, &month, &sep, &year);

    if (year < 2025)
    {
        return false;
    }
    return true;
}

bool is_valid_city_name(const std::string& cityName) {
    std::regex city_pattern("^[A-Z][a-zA-Z\\- ]*$");
    return std::regex_match(cityName, city_pattern);
}