#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Admin/Operator.h"
using namespace std;

class User
{
private:
    string username;
    string password;
    bool authenticated = false;

public:
    User(string username, string password)
    {
        this->username = username;
        this->password = password;
    }

    int login(string username, string password)
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

    int authentification()
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

    void search_ride(string origin, string destination)
    {
        // we only search by cities
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

    TrainRide search_ride_by_name(string train_name)
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

    int buy_ticket(string train_name, int class_type)
    {
        try
        {
            TrainRide ride = this->search_ride_by_name(train_name);
            ifstream file_read("../Data/Trains/" + train_name + ".csv");
            if (!file_read.is_open())
            {
                throw invalid_argument("File not found");
            }
            string line;
            while (getline(file_read, line))
            {
                if (line.empty())
                {
                    continue;
                }
                int wagon_number = stoi(line.substr(0, line.find(',')));
                line = line.substr(line.find(',') + 1);
                int seat_number = stoi(line.substr(0, line.find(',')));
                ride.reserve_specific_seat(wagon_number, seat_number);
            }// we reserve the seats that are already bought
            file_read.close();

            string file_name = "../Data/Trains/" + train_name + ".csv";
            ofstream file(file_name, ios::app);
            if (!file.is_open())
            {
                throw invalid_argument("File not found");
            }
            SeatInfo seat = ride.reserve_any_seat(class_type);
            file << seat.wagon_number << "," << seat.seat_number << endl;
            // we reserve a new seat
        }catch (const std::invalid_argument& e)
        {
            throw;
        }
    }
};

int main()
{
    User user("", "");
    user.buy_ticket("IR1932", 2);


    return 0;
    cout << "Welcome to the TrainRide application " << endl;

    bool logged_in = false;

    cout << "Please login to continue" << endl;
    cout << "If you are an user type 1" << endl;
    cout << "If you are an operator type 0" << endl;
    int choice;
    cin >> choice;
    if (!choice) /// Operator
    {
        while (!logged_in) // login attempt
        {
            try
            {
                cout << "Enter name:" << endl;
                string name;
                cin >> name;
                cout << "Enter password:" << endl;
                string password;
                cin >> password;
                Operator smooth_operator(name, password);
                smooth_operator.login(name, password);
                cout << "Logged in" << endl;
                logged_in = true;

                // operation loops
                int continue_operation = 1;
                while (continue_operation)
                {
                    cout << "If you want to add a ride type 1" << endl;
                    cout << "If you want to remove a ride type 0" << endl;
                    int choice1;
                    cin >> choice1;

                    if (choice1) //add ride
                    {
                        try
                        {
                            smooth_operator.add_ride();
                        }
                        catch (const std::invalid_argument& e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    else //remove ride
                    {
                        try
                        {
                            smooth_operator.remove_ride();
                        }
                        catch (const std::invalid_argument& e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    cout << "If you want to continue type 1" << endl;
                    cout << "If you want to exit type 0" << endl;
                    cin >> continue_operation;
                }
            }
            catch (const std::invalid_argument& e)
            {
                cout << e.what() << endl;
                cout << "Please try again" << endl;
            }
        }
    }
    else /// User
    {
        cout << "If you are a new user type 1" << endl;
        cout << "If you are an existing user type 2" << endl;
        int choice1;
        cin >> choice1;
        if (choice1 == 1) //new user
        {
            User user("", "");
            try
            {
                user.authentification();
            }
            catch (const std::invalid_argument& e)
            {
                cout << e.what() << endl;
                cout << "Please try again" << endl;
                cout << "Enter 1 to continue or 0 to exit" << endl;
                int continue_operation;
                cin >> continue_operation;
                if (!continue_operation)
                {
                    return 0;
                }
            }

            cout << "User created" << endl;
        }

        cout << "Please login to continue" << endl;

        while (!logged_in) // login attempt
        {
            try
            {
                cout << "Enter name:" << endl;
                string name;
                cin >> name;
                cout << "Enter password:" << endl;
                string password;
                cin >> password;
                User user(name, password);
                user.login(name, password);
                cout << "Logged in" << endl;
                logged_in = true;

                cout << "If you want to search for a ride type 1" << endl;
                cout << "If you want to buy a ticket type 2" << endl;
                cout << "If you want to exit type 0" << endl;
                int choice2;
                cin >> choice2;

                while (choice2) // operation loops
                {
                    if (choice2 == 1)
                    {
                        cout << "Enter origin city:" << endl;
                        string origin;
                        cin.ignore();
                        getline(cin, origin);
                        cout << "Enter destination city:" << endl;
                        string destination;
                        getline(cin, destination);
                        try
                        {
                            user.search_ride(origin, destination);
                        }
                        catch (const std::invalid_argument& e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    else if (choice2 == 2)
                    {
                        cout << "Enter train name:" << endl;
                        string train_name;
                        cin.ignore();
                        getline(cin, train_name);
                        cout << "Enter class type (1 or 2):" << endl;
                        int class_type;
                        cin >> class_type;
                        try
                        {
                            user.buy_ticket(train_name, class_type);
                        }
                        catch (const std::invalid_argument& e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    cout << "If you want to search for a ride type 1" << endl;
                    cout << "If you want to buy a ticket type 2" << endl;
                    cout << "If you want to exit type 0" << endl;
                    cin >> choice2;
                }
            }
            catch (const std::invalid_argument& e)
            {
                cout << e.what() << endl;
                cout << "Please try again" << endl;
                cout << "Enter 1 to continue or 0 to exit" << endl;
                int continue_operation;
                cin >> continue_operation;
                if (!continue_operation)
                {
                    return 0;
                }
            }
        }
    }

    return 0;
}
