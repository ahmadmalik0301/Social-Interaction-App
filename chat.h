using namespace std;
class chatBox
{
    string name1, name2;
    list<string> chatBoxMsg;

public:
    chatBox(string name1, string name2)
    {
        this->name1 = name1;
        this->name2 = name2;
    }
    void addUser(string name1, string name2)
    {
        this->name1 = name1;
        this->name2 = name2;
    }
    string returnChatUser1()
    {
        return name1;
    }
    string returnChatUser2()
    {
        return name2;
    }
    // function thats add a message in a link list
    void chat()
    {
        string input;
        bool done = false;
        while (!done)
        {
            cout << name1 << ", enter a message or 'quit' to end the chat: ";
            getline(cin, input);
            if (input == "quit")
            {
                done = true;
            }
            else
            {
                push_msg(BLUE_TEXT + name1 + RESET_TEXT + ": " + input);
                system("cls");
                print_history();
            }
        }
    }
    void push_msg(string message)
    {
        chatBoxMsg.push_back(message);
    }
    void print_history()
    {
        for (string message : chatBoxMsg)
        {
            cout << message << endl;
        }
    }
};
void ChatBoxCreater(list<chatBox> &cbox, string name, string personChatWith);
void chatMananging(list<chatBox> &cbox, string name)
{
    int choice = 0;
    while (true)
    {

        cout << "\n\n\n1- Start a Chat." << endl;
        cout << "2- View All Your Existing Chats." << endl;
        cout << "3- Quit." << endl;
        cout << "Enter : ";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            string personChatWith;
            cout << "\n\n\n";
            cout << "Enter person you wanna chat With : ";
            cin >> personChatWith;
            ChatBoxCreater(cbox, name, personChatWith);
        }
        break;
        case 2:
        {
            int i = 1;
            bool exist = false;
            cout << "\n\n";
            // for loop is used to print all the objects in which user match with the caller
            for (list<chatBox>::iterator it = cbox.begin(); it != cbox.end(); it++)
            {
                if (it->returnChatUser1() == name || it->returnChatUser2() == name)
                {
                    cout << i << " - " << it->returnChatUser1() << " and " << it->returnChatUser2() << endl;
                    exist = true;
                    i++;
                }
            }
            if (!exist)
            {
                cout << "No chat Exist...!\n";
            }
        }
        break;
        case 3:

            return;
        default:
            cout << "Invalid Input.";
        }
    }
}
void ChatBoxCreater(list<chatBox> &cbox, string name, string personChatWith)
{

    cout << endl;
    cout << endl;
    bool chatBoxFound = false;
    // if cahtbox exist work on it
    for (list<chatBox>::iterator it2 = cbox.begin(); it2 != cbox.end(); it2++)
    {
        if ((it2->returnChatUser1() == name && it2->returnChatUser2() == personChatWith) || (it2->returnChatUser1() == personChatWith && it2->returnChatUser2() == name))

        {
            cin.ignore();
            cout << "Hi chatbox was found\n";
            system("pause");
            it2->addUser(name, personChatWith);
            it2->chat();
            chatBoxFound = true;
            break;
        }
    }
    // if chatbox is not found create a new one and push it in the list
    if (!chatBoxFound)
    {
        cin.ignore();
        cout << "New Chat Room is Created.\n";
        cbox.push_back(chatBox(name, personChatWith));
        auto it2 = prev(cbox.end(), 1);
        it2->chat();
    }
}