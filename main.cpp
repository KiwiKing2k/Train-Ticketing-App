#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Admin/Operator.h"
#include "Users/User.h"
using namespace std;


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
