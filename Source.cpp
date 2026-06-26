#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class user;

// facility class having detaisl about facilities
class facility
{
    int id;
    string name;
    double rate;
    bool available;

public:
    facility(int i, string n, double r, bool a = true)
        : id(i), name(n), rate(r), available(a) {
    }
    // facility getters function
    int getid() {
        return id; 
    }
    string getname() {
        return name; 
    }
    double getrate() {
        return rate; 
    }
    bool isavailable() { 
        return available;
    }
    void setavailable(bool a) {
        available = a;
    }
    // view facility function for facilities
    void viewfacility()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Rate: " << rate << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
    }
};

//  Booking class having info about the bookings
class booking
{
    int bookingid;
    int userid;
    int facilityid;
    string date;
    int hours;
    string status;

public:
    booking(int b, int u, int f, string d, int h): bookingid(b), userid(u), facilityid(f), date(d), hours(h), status("Pending") {
    }
    // getters function for class booking
    int getbookingid() {
        return bookingid;
    }
    int getuserid() {
        return userid; 
    
}
    int getfacilityid() {
        return facilityid; 
    }
    string getdate() {
        return date;
    }
    int gethours() {
        return hours;
    }
    string getstatus() {
        return status;
    }

    // approve or reject function for booking
    void approve() {
        status = "Approved";
    }
    void reject() {
        status = "Rejected"; 
    }

    // show booking function that use later in classes
    void showbooking()
    {
        cout << "Booking ID: " << bookingid << endl;
        cout << "Facility ID: " << facilityid << endl;
        cout << "Date: " << date << endl;
        cout << "Hours: " << hours << endl;
        cout << "Status: " << status << endl;
    }
};

//  System Manager class holds the vector of other classes
class systemmanager
{
public:
    // vectors of other classes
    vector<user*> users;

    vector<facility*> facilities;

    vector<booking*> bookings;

    virtual ~systemmanager()
    {
        for (int i = 0; i < users.size(); i++)

            delete users[i];
        for (int i = 0; i < facilities.size(); i++)

            delete facilities[i];
        for (int i = 0; i < bookings.size(); i++)

            delete bookings[i];
    }
    // virtual functions in this class that show polymorphism and use by later classes
    virtual void loaddata() = 0;
    virtual void registeruser() = 0;
    virtual user* login() = 0;
    virtual void savedata() = 0;
};

//  User base class which hav ethe common attributtes offurther classes that inherited
class user
{
protected:
    int id;
    string name;
    string password;
    string role;
    systemmanager* sm;

public:
    user(int i, string n, string p, string r, systemmanager* sys)
        : id(i), name(n), password(p), role(r), sm(sys) {
    }

    virtual ~user() {}

    // getters function for class user
    int getid() { 
        return id;
    }
    string getname() {
        return name;
    }
    string getpassword() {
        return password; 
    }
    string getrole() {
        return role; 
    }

    virtual void showmenu() = 0;
};

// Student class that inherited from the base class uswr
class student : public user
{
public:
    student(int i, string n, string p, systemmanager* s)
        : user(i, n, p, "Student", s) {
    }

    // view facilities function
    void viewfacilities()
    {
        for (int i = 0; i < sm->facilities.size(); i++)
        {
            sm->facilities[i]->viewfacility();
        }
    }
    // request booking function that used by student and faculty menu
    void requestbooking()
    {
        int fid, hours;
        string date;

        cout << "Enter Facility ID: ";
        cin >> fid;

        cin.ignore();

        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Hours: ";
        cin >> hours;
        cin.ignore();

        for (int i = 0; i < sm->facilities.size(); i++)
        {
            if (sm->facilities[i]->getid() == fid && sm->facilities[i]->isavailable())
            {
                sm->bookings.push_back(new booking(sm->bookings.size() + 1, id, fid, date, hours));
                sm->facilities[i]->setavailable(false);

                cout << "Booking Requested" << endl;
                return;
            }
        }
        cout << "Facility Not Available" << endl;
    }

    // view facility function taht use i student and faculty menu
    void viewmybookings()
    {
        for (int i = 0; i < sm->bookings.size(); i++)
        {
            if (sm->bookings[i]->getuserid() == id)
            {
                sm->bookings[i]->showbooking();
            }
        }
    }

    // cancel booking function that use in student menu
    void cancelbooking()
    {
        int bid;

        cout << "Enter Booking ID: ";
        cin >> bid;

        cin.ignore();
        for (int i = 0; i < sm->bookings.size(); i++)
        {
            if (sm->bookings[i]->getbookingid() == bid && sm->bookings[i]->getuserid() == id)
            {
                for (int j = 0; j < sm->facilities.size(); j++)
                {
                    if (sm->facilities[j]->getid() == sm->bookings[i]->getfacilityid())
                    {
                        sm->facilities[j]->setavailable(true);
                    }
                }
                delete sm->bookings[i];

                sm->bookings.erase(sm->bookings.begin() + i);
                cout << "Booking Cancelled" << endl;

                return;
            }
        }
    }
    // show menu function for student
    void showmenu() override
    {
        int choice;
        do
        {
            cout << "=====Student Menu=====" << endl;
            cout << "1.View Facilities" << endl;
            cout << "2.Request Booking" << endl;
            cout << "3.View My Bookings" << endl;
            cout << "4.Cancel Booking" << endl;
            cout << "5.Logout" << endl;
            cout << "Choice: ";
            cin >> choice;

            cin.ignore();

            if (choice == 1)
                viewfacilities();

            else if (choice == 2)
                requestbooking();

            else if (choice == 3)
                viewmybookings();


            else if (choice == 4)
                cancelbooking();


        } while (choice != 5);
    }
};

// faculty class derieved from the base class student bcz both having same menu
class faculty : public student
{
public:
    faculty(int i, string n, string p, systemmanager* s)
        : student(i, n, p, s)
    {
        this->role = "Faculty";
    }

    // getters function fro class faculty memebers
    int getid() const { 

        return id; 
    }
    string getname() {
        return name; 
    }
    string getpassword() {
        return password; 
    
}
    string getrole() {
        return role;
    }
};

// admin class taht deriecved from the base class user
class admin : public user
{
public:

    admin(int i, string n, string p, systemmanager* s)
        : user(i, n, p, "Admin", s) {
    }

    // add facility function that use by admin menu
    void addfacility()
    {
        int id;
        string name;

        double rate;
        cout << "Facility ID: ";
        cin >> id;

        cin.ignore();
        cout << "Name: ";

        getline(cin, name);
        cout << "Rate: ";

        cin >> rate;
        cin.ignore();

        sm->facilities.push_back(new facility(id, name, rate));
        cout << "Facility Added" << endl;
    }

    // remove facility function that use in admin menu

    void removefacility()
    {
        int id;
        cout << "Enter Facility ID: ";
        cin >> id;
        cin.ignore();
        for (int i = 0; i < sm->facilities.size(); i++)
        {
            if (sm->facilities[i]->getid() == id)
            {
                delete sm->facilities[i];

                sm->facilities.erase(sm->facilities.begin() + i);
                cout << "Facility Removed" << endl;
                return;
            }
        }
    }
    // aprove or reject booking that use by class admin taht accept or reject booking
    void approverejectbooking()
    {
        bool anyPending = false;

        // it show the pending bookings

        cout << "Pending Bookings:" << endl;
        for (int i = 0; i < sm->bookings.size(); i++)
        {
            if (sm->bookings[i]->getstatus() == "Pending")
            {
                sm->bookings[i]->showbooking();
                anyPending = true;
            }
        }

        if (!anyPending)
        {
            cout << "No pending bookings available." << endl;
            return;
        }

        int bid, choice;
        cout << "-----------------------------------" << endl;
        cout << "Enter Booking ID to Approve/Reject: ";
        cin >> bid;
        cin.ignore();

        cout << "1. Approve" << endl;
        cout << "2. Reject" << endl;
        cout << "Choice: ";
        cin >> choice;

        cin.ignore();

        // it take the choice to accept or reject
        for (int i = 0; i < sm->bookings.size(); i++)
        {
            if (sm->bookings[i]->getbookingid() == bid)
            {
                if (choice == 1)
                {
                    sm->bookings[i]->approve();
                    cout << "Booking Approved" << endl;
                }
                else if (choice == 2)
                {
                    sm->bookings[i]->reject();
                    cout << "Booking Rejected" << endl;
                }
                else
                {
                    cout << "Invalid choice." << endl;
                }
                return;
            }
        }

        // show when there is no booking found fro admin
        cout << "Booking ID not found." << endl;
    }
    // show menu function that override by class user that show polymorphism
    void showmenu() override
    {
        int choice;
        do
        {
            cout << "=====Admin Menu=====" << endl;
            cout << "1.Add Facility" << endl;
            cout << "2.Remove Facility" << endl;
            cout << "3.Approve or Reject Booking" << endl;
            cout << "4.Logout" << endl;
            cout << "Choice: ";
            cin >> choice;

            cin.ignore();

            if (choice == 1)
                addfacility();

            else if (choice == 2)
                removefacility();

            else if (choice == 3)
                approverejectbooking();


        } while (choice != 4);
    }
};

// final manager inherited from the class system manager having vectors
class finalmanager : public systemmanager
{
public:
    finalmanager()
    {
        // these are the files that created and than close immediately
        ofstream("users.txt", ios::app).close();

        ofstream("facilities.txt", ios::app).close();

        ofstream("bookings.txt", ios::app).close();
        loaddata();

        loaddefaultfacilities();
    }
    ~finalmanager() { savedata(); }

    // load default facilities if the facilities vector is empty
    void loaddefaultfacilities()
    {
        if (facilities.empty())
        {
            facilities.push_back(new facility(1, "Extra Room", 100.0));
            facilities.push_back(new facility(2, "Seminar Hall", 100.0));
            facilities.push_back(new facility(3, "Computer Lab", 1750.0));
            facilities.push_back(new facility(4, "Auditorium", 150.0));
        }
    }

    void loaddata() override
    {
        // Load users from the user.txt file
        ifstream fusers("users.txt");
        if (fusers.is_open())
        {
            string line;
            while (getline(fusers, line))
            {
                if (line.empty()) continue;
                istringstream iss(line);

                int id;
                string name, pass, role;
                iss >> id;

                getline(iss, name, ' ');
                iss >> pass >> role;

                if (role == "Student")

                    users.push_back(new student(id, name, pass, this));
                else if (role == "Faculty")

                    users.push_back(new faculty(id, name, pass, this));
                else if (role == "Admin")

                    users.push_back(new admin(id, name, pass, this));
            }
        }
        fusers.close();

        // Load facilities
        ifstream ffac("facilities.txt");
        if (ffac.is_open())
        {
            string line;
            while (getline(ffac, line))
            {
                if (line.empty()) continue;
                istringstream iss(line);
                int id;

                double rate;
                bool avail;
                string name;

                iss >> id >> rate >> avail;
                iss.ignore();

                getline(iss, name);
                facilities.push_back(new facility(id, name, rate, avail));
            }
        }
        ffac.close();

        // Load bookings
        ifstream fbook("bookings.txt");
        if (fbook.is_open())
        {
            string line;
            while (getline(fbook, line))
            {
                if (line.empty()) continue;

                istringstream iss(line);
                int bid, uid, fid, hours;

                string date, status;

                iss >> bid >> uid >> fid >> date >> hours >> status;
                booking* b = new booking(bid, uid, fid, date, hours);
                if (status == "Approved")

                    b->approve();
                else if (status == "Rejected")

                    b->reject();
                bookings.push_back(b);
            }
        }
        fbook.close();
    }

    void savedata() override
    {
        // Save users
        ofstream fusers("users.txt");

        for (int i=0;i<users.size();i++)
        {
            fusers << users[i]->getid() << " " << users[i]->getname() << " " << users[i]->getpassword() << " " << users[i]->getrole() << endl;
        }
        fusers.close();

        // Save facilities
        ofstream ffacilities("facilities.txt");

        for (int i=0;i<facilities.size();i++)
        {
            ffacilities << facilities[i]->getid() << " " << facilities[i]->getrate() << " " << facilities[i]->isavailable() << " " << facilities[i]->getname() << endl;
        }
        ffacilities.close();

        // Save bookings
        ofstream fbookings("bookings.txt");


        for (int i = 0; i < bookings.size(); i++)
        {

            fbookings << bookings[i]->getbookingid() << " "<< bookings[i]->getuserid() << " "<< bookings[i]->getfacilityid() << " "<< bookings[i]->getdate() << " "<< bookings[i]->gethours() << " "<< bookings[i]->getstatus() << endl;
        }

        fbookings.close();
    }

    // register user function that use in mian menu of facility sysytem
    void registeruser() override
    {
        int id, type;
        string name, pass;

        cout << "ID: ";
        cin >> id;

        cin.ignore();
        cout << "Name: ";
        getline(cin, name);

        cout << "Password: ";
        getline(cin, pass);

        cout << "Role: 1.Student 2.Faculty 3.Admin" << endl
            << "Choice: ";
        
        cin >> type;
        cin.ignore();

        if (type == 1)

            users.push_back(new student(id, name, pass, this));
        else if (type == 2)

            users.push_back(new faculty(id, name, pass, this));
        else
            users.push_back(new admin(id, name, pass, this));
    }

    // login function that also use in main menu  of campus facility system
    user* login() override
    {
        string name, pass;
        cin.ignore();

        cout << "Name: ";
        getline(cin, name);

        cout << "Password: ";
        getline(cin, pass);

        for (auto u : users)
        {
            if (u->getname() == name && u->getpassword() == pass)
                return u;
        }
        return nullptr;
    }
};

// main function of all code in which the object final manager class
int main()
{
    finalmanager sm;
    int choice;
    do
    {
        cout << "=====Campus Facility System=====" << endl;
        cout << "1.Register\n2.Login\n3.Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
            sm.registeruser();
        else if (choice == 2)
        {
            user* u = sm.login();
            if (u != nullptr)
                u->showmenu();
        }
    } while (choice != 3);
    return 0;
}