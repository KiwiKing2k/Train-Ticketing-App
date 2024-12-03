#include "Operator.h"

Operator::Operator(string username, string password)
{
    this->username = username;
    this->password = password;
}

int Operator::login(string username, string password)
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

void Operator::add_ride()
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
    file << name << "," << date << "," << time << "," << start << "," << end << "," << first_class_wagons << "," << second_class_wagons <<
        endl;
    string file_name = "../Data/Trains/" + name + ".csv";
    ofstream file2(file_name);
}

void Operator::remove_ride()
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
    file2.close();
    string file_name = "../Data/Trains/" + name + ".txt";
    try
    {
        remove(file_name.c_str());
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }
}
