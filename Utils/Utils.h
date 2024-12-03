#ifndef UTILS_H
#define UTILS_H

#include <string>

bool is_valid_date_format(const std::string& date);
bool is_valid_date(const std::string& date);
bool is_valid_time(const std::string& time);
bool is_valid_city_name(const std::string& cityName);

#endif // UTILS_H
