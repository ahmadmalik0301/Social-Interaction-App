
#include "allHeader.h"

using namespace std;

void mainManager(list<chatBox> &cbox, list<groupChat> &g1, userAccount user, list<userAccount> &l1, list<postingArea> &p1, friendGraph &graph);

int main()
{
    system("cls");
    // link list to store postes, chatbox, grouochat and friendship connections;
    list<userAccount> l1;
    list<postingArea> p1;
    list<chatBox> cbox;
    list<groupChat> g1;
    friendGraph graph;
    // adding hobbies for default users
    vector<string> tempHobby;
    tempHobby.push_back("Football");
    tempHobby.push_back("Programming");
    tempHobby.push_back("Gaming");
    l1.push_back(userAccount("Ahmad", "Allama,Iqbal,Colony", tempHobby, "1234", "mahmadmalik421@gmail.com"));
    l1.push_back(userAccount("Bilal", "Allama,Iqbal,Colony", tempHobby, "1234", "mahmadmalik421@gmail.com"));
    l1.push_back(userAccount("Umar", "Allama,Iqbal,Colony", tempHobby, "1234", "mahmadmalik421@gmail.com"));
    int choice = 0;
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Create a new account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");
        cin.ignore();

        switch (choice)
        {
        case 1:
            createUser(l1);
            break;
        case 2:
        {
            // return object from the list if name and password matches
            userAccount user = login(l1);

            if (user.isValid())
            {
                mainManager(cbox, g1, user, l1, p1, graph);
            }
            else
            {
                cout << "\nWrong Username or Password....\n";
            }
        }
        break;
        case 3:
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
// function to manage all the modules
void mainManager(list<chatBox> &cbox, list<groupChat> &g1, userAccount user, list<userAccount> &l1, list<postingArea> &p1, friendGraph &graph)
{
    int choice = 0;
    while (true)
    {
        cout << "\n\n\n1- Access Chat Module\n";
        cout << "2- Access Group Chat Module\n";
        cout << "3- Access Post Module\n";
        cout << "4- Access Friendship Module\n";
        cout << "5- Print Your Details\n";
        cout << "6- Update Your Information\n";
        cout << "7- Exit\n\n";
        cout << "Enter : ";

        cin >> choice;
        system("cls");
        cin.ignore();
        switch (choice)
        {
        case 1:
        {

            chatMananging(cbox, user.return_name());
        }

        break;

        case 2:
            groupChatManager(user.return_name(), g1);
            break;
        case 3:
        {
            postManager(p1, user.return_name());
        }
        break;

        case 4:
            friendManaging(user.return_name(), graph, l1);
            break;
        case 5:
            user.display();
            break;
        case 6:
            user.changeDetails(l1);
            break;
        case 7:
            // directly change the details of user from the link list
            for (userAccount &obj : l1)
            {
                if (obj.returnID() == user.returnID())
                {
                    obj = user;
                }
            }
            return;

        default:
            cout << "Invalid Input. Enter Again\n";
            break;
        }
    }
}