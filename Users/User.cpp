#include "User.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Admin/Operator.h"

using namespace std;

User::User(string username, string password)
{
    this->username = username;
    this->password = password;
}

int User::login(string username, string password)
{
    ifstream file("../Data/user_login.txt");
    if (!file.is_open())
    {
        throw invalid_argument("Login File not found");
    }
    vector<credentials> user_cred;
    string line;
    while (getline(file, line))
    {
        credentials cred;
        cred.username = line.substr(0, line.find(','));
        cred.password = line.substr(line.find(',') + 1);
        user_cred.push_back(cred);
    }
    file.close();
    for (auto& cred : user_cred)
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

int User::authentification()
{
    cout << "Enter name:" << endl;
    string name;
    cin >> name;
    this->username = name;
    cout << "Enter password:" << endl;
    string password;
    cin >> password;
    this->password = password;
    ifstream file_read("../Data/user_login.txt");
    if (!file_read.is_open())
    {
        throw invalid_argument("File not found");
    }
    string line;
    while (getline(file_read, line))
    {
        if (line.find(name) != string::npos)
        {
            throw invalid_argument("User already exists");
        }
    }
    file_read.close();

    ofstream file("../Data/user_login.txt", ios::app);
    if (!file.is_open())
    {
        throw invalid_argument("File not found");
    }
    file << name << "," << password << endl;
    file.close();

    return 1;
}

void User::search_ride(string origin, string destination)
{
    ifstream file("../Data/rides.txt");
    if (!file.is_open())
    {
        throw invalid_argument("File not found");
    }
    string line;
    int found = 0;
    while (getline(file, line))
    {
        string name, date, time, start, end;
        int first_class_wagons, second_class_wagons;
        int pos = line.find(',');
        name = line.substr(0, line.find(','));
        line = line.substr(pos + 1);

        pos = line.find(',');
        date = line.substr(0, line.find(','));
        line = line.substr(pos + 1);

        pos = line.find(',');
        time = line.substr(0, line.find(','));
        line = line.substr(pos + 1);

        pos = line.find(',');
        start = line.substr(0, line.find(','));
        line = line.substr(pos + 1);

        pos = line.find(',');
        end = line.substr(0, line.find(','));

        if (start == origin && end == destination)
        {
            cout << "Ride found" << endl;
            cout << "Name: " << name << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "Start: " << start << endl;
            cout << "End: " << end << endl;
            found = 1;
        }
    }
    if (!found)
    {
        throw invalid_argument("Ride not found");
    }
}

TrainRide User::search_ride_by_name(string train_name)
{
    ifstream file("../Data/rides.txt");
    if (!file.is_open())
    {
        throw invalid_argument("File not found");
    }
    string line;
    int found = 0;
    while (getline(file, line))
    {
        string name, date, time, start, end;
        int first_class_wagons, second_class_wagons;
        int pos = line.find(',');
        name = line.substr(0, line.find(','));
        line = line.substr(pos + 1);

        if (name == train_name)
        {
            found = 1;
            pos = line.find(',');
            date = line.substr(0, line.find(','));
            line = line.substr(pos + 1);

            pos = line.find(',');
            time = line.substr(0, line.find(','));
            line = line.substr(pos + 1);

            pos = line.find(',');
            start = line.substr(0, line.find(','));
            line = line.substr(pos + 1);

            pos = line.find(',');
            end = line.substr(0, line.find(','));

            pos = line.find(',');
            line = line.substr(pos + 1);

            first_class_wagons = stoi(line.substr(0, line.find(',')));
            pos = line.find(',');
            line = line.substr(pos + 1);

            second_class_wagons = stoi(line);

            return TrainRide(name, date, time, end, start, first_class_wagons, second_class_wagons);
        }
    }
    if (!found)
    {
        throw invalid_argument("Ride not found");
    }
}

int User::buy_ticket(string train_name, int class_type)
{
    TrainRide found_ride = search_ride_by_name(train_name);
    found_ride.find_reserved_seats();
    SeatInfo seat = found_ride.reserve_any_seat(class_type);
    cout << "Seat reserved: " << seat.seat_number << " in wagon " << seat.wagon_number + 1 << endl;
    ofstream file("../Data/Trains/" + train_name + ".csv", ios::app);
    if (!file.is_open())
    {
        throw invalid_argument("File not found");
    }
    file << seat.wagon_number << "," << seat.seat_number << "," << this->username << endl;
    file.close();
    return 1;
}