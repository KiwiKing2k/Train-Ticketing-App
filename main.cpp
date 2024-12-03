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
        ifstream file("../Data/op_login.txt");
        if (!file.is_open())
        {
            throw invalid_argument("Login File not found");
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
        for (auto& cred : admin_cred)
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

    void add_ride()
    {
        if (!authenticated)
        {
            throw invalid_argument("Not authenticated");
        }
        cout << "Enter ride name:" << endl;
        string name;
        cin >> name;
        cout << "Enter date:" << endl;
        string date;
        cin >> date;
        cout << "Enter time:" << endl;
        string time;
        cin >> time;
        cout << "Enter start city:" << endl;
        string start;
        cin.ignore();
        getline(cin, start);
        cout << "Enter end city:" << endl;
        string end;
        cin.ignore();
        getline(cin, end);
        cout << "Enter number of first class wagons:" << endl;
        int first_class_wagons;
        cin >> first_class_wagons;
        cout << "Enter number of second class wagons:" << endl;
        int second_class_wagons;
        cin >> second_class_wagons;

        TrainRide ride(name, date, time, start, end, first_class_wagons, second_class_wagons);

        ofstream file("../Data/rides.txt", ios::app);
        if (!file.is_open())
        {
            throw invalid_argument("File not found");
        }
        file << name << "," << date << "," << time << "," << start << "," << end << "," << first_class_wagons << "," <<
            second_class_wagons << endl;
    }

    void remove_ride()
    {
        if (!authenticated)
        {
            throw invalid_argument("Not authenticated");
        }
        cout << "Enter ride name to remove:" << endl;
        string name;
        cin >> name;

        ifstream file("../Data/rides.txt");
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
        ofstream file2("../Data/rides.txt");
        if (!file2.is_open())
        {
            throw invalid_argument("File not found");
        }
        for (auto& l : lines)
        {
            file2 << l << endl;
        }
    }
};

int main()
{

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
    else
    {
        /// to be continued
    }

    return 0;
}
