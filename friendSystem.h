#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

class friendGraph
{
    // unorder map for both friendList and requestList
    unordered_map<string, list<string>> friendList;
    unordered_map<string, list<string>> requestList;

public:
    void addFriend(string user, string addent)
    {
        if (existInFriendList(user, addent))
        {
            cout << "He is already your friend.\n";
            return;
        }
        // find the key and add they user to its link list
        friendList[user].push_back(addent);
        friendList[addent].push_back(user);
    }

    bool existInFriendList(string user, string addent)
    {
        for (auto friendName : friendList[user])
        {
            if (friendName == addent)
            {
                return true;
            }
        }
        return false;
    }

    void displayUserFriend(string name)
    {
        if (friendList.find(name) != friendList.end())
        {
            cout << "\nFriends of " << name << " are: ";
            for (auto friendName : friendList[name])
            {
                cout << friendName << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "No user found with this name.\n";
        }
    }

    void displayUserRequests(string name)
    {
        if (requestList.find(name) != requestList.end())
        {
            cout << "\nRequests of " << name << " are: ";
            for (auto request : requestList[name])
            {
                cout << request << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "No pending requests for " << name << ".\n";
        }
    }

    void sendRequest(string sender, string receiver)
    {
        requestList[receiver].push_back(sender);
    }

    void removeRequest(string receiver, string sender)
    {
        requestList[receiver].remove(sender);
    }

    void acceptRequest(string user, string sender)
    {
        addFriend(user, sender);
        removeRequest(sender, user);
    }
    bool requestAlreadySent(string sender, string receiver)
    {
        if (requestList.find(receiver) != requestList.end())
        {
            for (auto request : requestList[receiver])
            {
                if (request == sender)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

void friendManaging(string name, friendGraph &graph, list<userAccount> li)
{
    int choice = 0;
    graph.sendRequest("Bilal", name);
    graph.sendRequest("Umar", name);

    while (true)
    {
        cout << "1-Enter 1 to Send a Request.\n";
        cout << "2-Enter 2 to Remove a Request.\n";
        cout << "3-Enter 3 to View all Request.\n";
        cout << "4-Enter 4 to Accept a Request.\n";
        cout << "5-Enter 5 to View All your Friends.\n";
        cout << "\nEnter: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            cout << "Enter person name you want to Send Request: ";
            string sendRequestTo;
            cin >> sendRequestTo;
            if (!graph.existInFriendList(name, sendRequestTo) &&
                !graph.requestAlreadySent(name, sendRequestTo))
            {
                graph.sendRequest(name, sendRequestTo);
            }
            else
            {
                cout << "Invalid request. Already friends or request exists.\n";
            }
        }
        break;

        case 2:
        {
            cout << "Enter person name to Remove Request: ";
            string removeRequestTo;
            cin >> removeRequestTo;
            graph.removeRequest(name, removeRequestTo);
        }
        break;

        case 3:
            graph.displayUserRequests(name);
            break;

        case 4:
        {
            cout << "Enter person name to Accept Request: ";
            string acceptRequestFrom;
            cin >> acceptRequestFrom;
            graph.acceptRequest(name, acceptRequestFrom);
        }
        break;

        case 5:
            graph.displayUserFriend(name);
            break;

        default:
            cout << "Invalid Input.\n";
        }
    }
}
