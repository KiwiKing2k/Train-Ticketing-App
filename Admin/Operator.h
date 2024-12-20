#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Train Utils\TrainRide.h"
#include "Encryption/Encryption.h"
#include <algorithm>

using namespace std;

typedef struct credentials
{
    string username;
    string password;
};

class Operator
{
private:
    string username;
    string password;
    bool authenticated = false;

public:
    Operator(string username, string password);
    int login(string username, string password, string secret_password);
    void add_ride();
    void remove_ride();
};

#endif // OPERATOR_H