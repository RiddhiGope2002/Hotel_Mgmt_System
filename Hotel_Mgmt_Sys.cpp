// Here it's a project of Hotel Management System where User will give his details as input and all his inputs will be stored in Guest.txt file for future reference and availability of rooms will be updated in Hotel.txt file.

#include <iostream>
#include <fstream> //For data storing in File
#include <ctime>   //To get the timing of Guests at our Hotel
using namespace std;

class Guests
{ // This class will hold all the details of every guest.
private:
    string name;
    int members;
    int rooms;
    string room_type; // ac or non-ac
    string ph_no;
    int rent;

public: // Getters and setters
    void setName(string setter_name)
    {
        name = setter_name;
    }
    void setMembers(int setter_Members)
    {
        members = setter_Members;
    }
    void setrooms(int setter_rooms)
    {
        rooms = setter_rooms;
    }
    void setPhone_no(string setter_Phone_no)
    {
        ph_no = setter_Phone_no;
    }

    void setrent(int setter_rent)
    {
        rent = setter_rent;
    }
    void setroom_type(string setter_room_type)
    {
        room_type = setter_room_type;
    }

    string getName()
    {
        return name;
    }
    int getMembers()
    {
        return members;
    }
    int getrooms()
    {
        return rooms;
    }
    string getPhone_no()
    {
        return ph_no;
    }

    int getrent()
    {
        return rent;
    }
    string getroom_type()
    {
        return room_type;
    }
};

class Hotel
{ // This class will hold all the details of the Hotel
private:
    int ac_room_rent = 2000;
    int non_ac_room_rent = 1500;
    int Total_rooms = 40;

public:
    int getAc()
    {
        return ac_room_rent;
    }
    int getNonAc()
    {
        return non_ac_room_rent;
    }
    int getTotal_rooms()
    {
        return Total_rooms;
    }
};

int main()
{

    // variables for user input. These variables will set the values of Guest class's private data members.
    string g_name, g_address, g_roomtype,g_ph_no;
    char g_consent;
    int g_member, g_rooms, g_rent;
     

    // Objects of the above classes
    Guests guest;
    Hotel h;

    // There is a file called Hotel.txt where I am updating number of available rooms in the hotel after every guest entry. In that file only that availability number is there. I am taking the number from there and converting that into int(bcoz from file I will get the data as string), to check whether I have available rooms for upcoming Guests.
    // To start the pgm,for 1st time,  I have given the value of Total_rooms=40 manually..
    ifstream file("Hotel.txt"); // Reading the file.
    string line;
    while (getline(file, line))
    {
    }
    int available_rooms = stoi(line); // converting string data to int

    cout << "\n*********WELCOME TO HOTEL LEXION***********\n";
    cout << "Tell us!!\n"
         << "Your Name:\n";
    getline(cin, g_name);
    guest.setName(g_name); // name done

    cout << "How many members are you?\n";
    cin >> g_member; // member done
    guest.setMembers(g_member);
    cout << "In our Facility we allow maximum 3 persons in a room\n";
    if (g_member % 3 == 0)
    {
        g_rooms = g_member / 3;
    }
    else
    {
        g_rooms = (g_member / 3) + 1;
    }

    // Checking if the user is planning to stay in our hotel or not!
    cout << "Are you planning to stay here?\nwrite y for 'y' for Yes and 'n' for No\n";
    cin >> g_consent;
    while (true)
    {
        if (g_consent != 'y' && g_consent != 'n')
        {
            cout << "Invalid Input\nPlease give the correct input!\n";
            cin >> g_consent;
        }

        if (g_consent == 'n')
        {
            break;
        }
        else if (g_consent == 'y')
        {
            if (available_rooms <= g_rooms)
            {
                cout << "Sorry, We don't have that many rooms available!!";
                break;
            }
            else
            {
                cout << "Total rooms allocated for you: " << g_rooms;
                guest.setrooms(g_rooms); // rooms done

                cout << "\nEnter Phone No:\n";
                cin >> g_ph_no;
                guest.setPhone_no(g_ph_no); // phone no done

                cout << "Our Ac Rooms are available at " << h.getAc() << "/- and Non-Ac Rooms are available at " << h.getNonAc() << "/-\n What will you prefer?\nPress 1 for AC,2 for Non-AC\n";
                cin >> g_roomtype;
                guest.setroom_type(g_roomtype);
                if (g_roomtype == "1")
                {
                    cout << "So your rent will be " << g_rooms * h.getAc();
                    guest.setrent(g_rooms * h.getAc());
                }
                else
                {
                    cout << "So your rent will be " << g_rooms * h.getNonAc();
                    guest.setrent(g_rooms * h.getNonAc());
                }

                // To get the arrival time of our Guest.I am filling this information directly to Guest.txt. Where all data of all guest is there.
                time_t timestamp;
                time(&timestamp);

                cout << "\n********\n";
                cout << "So I will confirm all your details for you:\n";
                cout << "Name: " << guest.getName() << "\nMembers: " << guest.getMembers() << "\nRooms: " << guest.getrooms() << "\nPhone No: " << guest.getPhone_no() << "\nStaying: " << guest.getroom_type() << "(1-> AC,2->NON AC)"<< "\nTotal Bill: " << guest.getrent();

                // Storing All these data in the file Guest.txt
                ofstream out("Guest.txt", ios::app); // ios::app is used so that new data can't override previous data
                out << ctime(&timestamp);
                out << "Name:" << guest.getName() << endl;
                out << "No of Members" << guest.getMembers() << endl;
                out << "No of Rooms" << guest.getrooms() << endl;
                out << "Phone No: " << guest.getPhone_no() << endl;
                out << "Rent Charged" << guest.getrent() << endl;
                out << "Room-type: " << guest.getroom_type() << "(1-> AC,2->NON AC)" << endl
                    << endl
                    << endl;
                out.close();

                // Here I am updating the available rooms and store it in file Hotel.txt
                ofstream in("Hotel.txt");
                available_rooms -= guest.getrooms();
                in << "\n"
                   << available_rooms;

                break;
            }
        }
    }

    return 0;
}