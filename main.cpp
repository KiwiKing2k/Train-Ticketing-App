#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "TrainRide.h"
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
    Operator(string username, string password)
    {
        this->username = username;
        this->password = password;
    }

    int login(string username, string password)
    {
        ifstream file("op_login.txt");
        if (!file.is_open())
        {
            throw invalid_argument("File not found");
        }
        vector<credentials> admin_cred;
        string line;
        while (getline(file, line))
        {
            credentials cred;
            cred.username = line.substr(0, line.find(','));
            cred.password = line.substr(line.find(',') + 1);
            admin_cred.push_back(cred);
        }
        file.close();
        for (auto & cred : admin_cred)
        {
            if (cred.username == username && cred.password == password)
            {
                authenticated = true;
                return 1;
            }
        }
        if (!authenticated)
        {
            throw invalid_argument("Invalid credentials");
        }
    }
    void add_ride(string name, string date, string time, string start, string end, int first_class_wagons, int second_class_wagons)
    {
        if (!authenticated)
        {
            throw invalid_argument("Not authenticated");
        }
        ofstream file("rides.txt", ios::app);
        if (!file.is_open())
        {
            throw invalid_argument("File not found");
        }
        file << name << "," << date << "," << time << "," << start << "," << end << "," << first_class_wagons << "," <<
        second_class_wagons << endl;
    }
    void remove_ride(string name)
    {
        if (!authenticated)
        {
            throw invalid_argument("Not authenticated");
        }
        ifstream file("rides.txt");
        if (!file.is_open())
        {
            throw invalid_argument("File not found");
        }
        vector<string> lines;
        string line;
        bool found = false;
        while (getline(file, line))
        {
            if (line.find(name) == string::npos)
            {
                found = true;
                lines.push_back(line);
            }
        }
        file.close();
        if (!found)
        {
            throw invalid_argument("Ride not found");
        }
        ofstream file2("rides.txt");
        if (!file2.is_open())
        {
            throw invalid_argument("File not found");
        }
        for (auto & l : lines)
        {
            file2 << l << endl;
        }


    }
};

int main()
{
    try
    {
        TrainRide train("Train1", "12.12.2025", "12:00", "Bucharest", "Clu&j", 2, 3);
        cout << train.reserve_any_seat(1) << endl;
    }
    catch (const std::invalid_argument& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
