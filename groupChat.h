#include <iostream>
#include <list>
#include <string>

using namespace std;

class groupChat
{
    list<string> names;
    list<string> msg;
    string groupName;
    string owner;
    bool type;
    string topic;
    string location;
    static int ID;
    string groupID;

public:
    groupChat(list<string> names, bool type, string groupName, string owner, string location, string topic)
    {
        this->names = names;
        this->type = type;
        this->groupName = groupName;
        this->owner = owner;
        this->topic = topic;
        this->location = location;
        ID++;
        groupID = "GRP" + to_string(ID);
    }
    // DISPLAY all msg in the chatbox
    void display_history()
    {
        for (string message : msg)
        {
            cout << message << endl;
        }
    }
    // check if you are a member of a groupchat already
    bool memberChecker(string name)
    {
        for (string name2 : names)
        {
            if (name2 == name)
            {
                return true;
            }
        }
        return false;
    }
    // add yourself only if the group is public
    void addYourSelf(string name)
    {
        if (type)
        {
            cout << "Sorry this Group chat is Private Ask Owner to add You\n";
            return;
        }
        names.push_back(name);
        msg.push_back(RED_TEXT + name + "was added in the Group Chat." + RESET_TEXT);
    }
    void chat(string name)
    {
        bool exist = false;
        bool done = false;
        for (list<string>::iterator it = names.begin(); it != names.end(); it++)
        {
            if (*it == name)
            {
                cout << "You are part of this group chat.";
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            cout << "Sorry You are not part of this chat.\n";
        }
        while (!done)
        {
            cin.ignore();
            string input;
            cout << name << ", enter a message or 'quit' to end the chat: ";
            getline(cin, input);
            if (input == "quit")
            {
                done = true;
            }
            else
            {
                msg.push_back(BLUE_TEXT + name + RESET_TEXT + ": " + input);
                system("cls");
                display_history();
            }
        }
    }
    string returnGroupName()
    {
        return groupName;
    }
    string returnID()
    {
        return groupID;
    }
    bool privacy()
    {
        return type;
    }
    void displayDetails()
    {
        cout << "Group Name :" << groupName << endl;
        cout << "Group Topic : " << topic << endl;
        cout << "Group Owner :" << owner << endl;
        cout << "Group Location :" << location << endl;
        cout << "Total Group Members :" << names.size() << endl;
        cout << "Group ID : " << groupID << endl;
    }
};
int groupChat ::ID = 4000;
void groupChatManager(string name, list<groupChat> &g1)
{
    int choice = 0;
    list<string> friendsName;
    while (true)
    {
        cout << "\n\nHi " << name << ".\n1- Create a New Group Chat\n";
        cout << "2- Browse Group Chats.\n";
        cout << "3- View Group Chats You Are a Member Of\n";
        cout << "4- Exit\n";
        cout << "5- Browse Public Group Chats\n";
        cout << "\n\nEnter : ";

        cin >> choice;
        system("cls");
        cin.ignore();
        switch (choice)
        {
            // create group chat
        case 1:
        {
            string groupChatName;
            cout << "Enter name of your Group chat : ";
            getline(cin, groupChatName);
            string inputName = "";
            while (inputName != "quit")
            {
                cout << "Enter name of People you wanna add to group or enter 'quit' to not adding : ";

                getline(cin, inputName);
                friendsName.push_back(inputName);
            }
            friendsName.push_back(name);
            cout << "Enter 1 to make it Public and 2 to make it Private : ";
            int num;
            cin >> num;
            bool type;
            if (num == 1)
            {
                type = false;
            }
            else
            {
                type = true;
            }
            cin.ignore();
            cout << "Enter Group Topic : ";
            string topic;
            getline(cin, topic);
            cout << "Enter Group Location : ";
            string location;
            getline(cin, location);
            cout << "Creating GroupChat......." << endl;
            system("pause");
            g1.push_back(groupChat(friendsName, type, groupChatName, name, location, topic));
            friendsName.clear();
        }
        break;
        // to chat is a group
        case 2:
        {
            bool isInGroupChat = false;
            for (list<groupChat>::iterator it = g1.begin(); it != g1.end(); it++)
            {
                if (it->memberChecker(name))
                {
                    cout << "\n\n";
                    it->displayDetails();
                    isInGroupChat = true;
                }
            }
            if (!isInGroupChat)
            {
                cout << "You are not in any Group Chat." << endl;
                break;
            }
            cout << "\n\nEnter GroupChat ID you wanna chat in : ";
            string groupChatID;
            getline(cin, groupChatID);
            for (list<groupChat>::iterator it = g1.begin(); it != g1.end(); it++)
            {
                if (it->returnID() == groupChatID && it->memberChecker(name))
                {
                    it->chat(name);
                    break;
                }
            }
        }
        break;
        // to check all the groups you are memeber of
        case 3:
        {
            int i = 1;
            for (groupChat &chat : g1)
            {
                if (chat.memberChecker(name))
                {
                    cout << "******************  " << i << "  **********************" << endl;
                    chat.displayDetails();
                }
                i++;
            }
            system("pause");
        }
        break;
        case 4:
            return;
            break;
        case 5:
        {
            // add yourself in the public groupchat
            int i = 0;
            cout << "All Public Group chats are Following : " << endl
                 << endl;
            for (groupChat chat : g1)
            {
                if (!chat.privacy() && !chat.memberChecker(name))
                {
                    cout << "******************  " << i << "  **********************" << endl;
                    chat.displayDetails();
                }
            }
            cout << "Enter ID of Group you wanna get added to : ";
            string ID;
            cin >> ID;
            for (list<groupChat>::iterator it = g1.begin(); it != g1.end(); it++)
            {
                if (it->returnID() == ID)
                {
                    it->addYourSelf(name);
                    cout << "You are added in this Group.....\n";
                    break;
                }
            }
        }
        break;

        default:
            break;
        }
    }
}