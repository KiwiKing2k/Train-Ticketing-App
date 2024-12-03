#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TrainRide.h"
#include "Admin/Operator.h"
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
    else
    {
        /// to be continued
    }

    return 0;
}
