#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "../Train Utils/TrainRide.h"

class User
{
private:
    std::string username;
    std::string password;
    bool authenticated = false;

public:
    User(std::string username, std::string password);
    int login(std::string username, std::string password, string secret_password);
    int authentification(string secret_password);
    void search_ride(std::string origin, std::string destination);
    TrainRide search_ride_by_name(std::string train_name);
    int buy_ticket(std::string train_name, int class_type);
};

#endif // USER_H