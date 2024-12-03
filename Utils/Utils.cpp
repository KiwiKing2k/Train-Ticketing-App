#include "Utils.h"
#include <regex>


bool is_valid_date_format(const std::string& date) {
    std::regex pattern("\\d{1,2}[\\./\\-_ ]\\d{2}[\\./\\-_ ]\\d{4}");
    if (!std::regex_match(date, pattern)) {
        return false;
    }
    return true;
}

bool is_valid_date(const std::string& date) {
    int day, month, year;
    char sep = date.find('-') != std::string::npos ? '-' :
               date.find('_') != std::string::npos ? '_' :
               date.find('.') != std::string::npos ? '.' :
               date.find('/') != std::string::npos ? '/' : ' ';
    sscanf(date.c_str(), "%d%c%d%c%d", &day, &sep, &month, &sep, &year);

    if (year < 2025) {
        throw std::invalid_argument("Year must be 2025 or later.");
    }

    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 1 and 12.");
    }

    if (day < 1 || day > 31) {
        throw std::invalid_argument("Day must be between 1 and 31.");
    }

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        throw std::invalid_argument("Invalid day for the given month.");
    }

    // Check for February
    if (month == 2) {
        bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !is_leap_year)) {
            throw std::invalid_argument("Invalid day for February.");
        }
    }

    return true;
}

bool is_valid_time(const std::string& time) {
    std::regex time_pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
    if (!std::regex_match(time, time_pattern)) {
        throw std::invalid_argument("Invalid time format.");
    }
    return true;
}

bool is_valid_city_name(const std::string& cityName) {
    std::regex city_pattern("^[A-Z][a-zA-Z\\- ]*$");
    return std::regex_match(cityName, city_pattern);
}