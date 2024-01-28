
using namespace std;
class userAccount;
// check if email or username already exist
bool checkUserExist(list<userAccount>, string);
bool checkEmail(list<userAccount> li, string email);
string passwordCheck();

class userAccount
{
    string name;
    string address;
    string password;
    vector<string> hobby;
    string userID;
    static int ID;
    string creationDate;
    string email;

public:
    userAccount() {}
    // list of user is passed so that each email and username can be checked
    userAccount(list<userAccount> li)
    {
        while (true)
        {
            string user;
            cout << "Enter Your Username : ";
            getline(cin, user);
            if (checkUserExist(li, user))
            {
                name = user;
                break;
            }
        }

        cout << "Enter Your Address : ";
        getline(cin, address);
        password = passwordCheck();
        while (true)
        {
            string input;
            cout << "Enter Your Hobbies (enter quit to stop adding): ";
            getline(cin, input);
            if (input == "quit")
            {
                break;
            }
            else
            {
                hobby.push_back(input);
            }
        }
        ID++;
        userID = "ACC" + to_string(ID);
        time_t currentTime = time(0);
        creationDate = ctime(&currentTime);
        while (true)
        {
            string mail;
            cout << "Enter your email : ";
            getline(cin, mail);
            if (checkEmail(li, mail))
            {
                email = mail;
                break;
            }
        }
    }
    userAccount(string name, string address, vector<string> hobby, string password, string email)
    {
        this->name = name;
        this->address = address;
        this->hobby = hobby;
        this->password = password;
        ID++;
        userID = "ACC" + to_string(ID);
        time_t currentTime = time(0);
        creationDate = ctime(&currentTime);
        this->email = email;
    }
    string return_name()
    {
        return name;
    }
    void change_name(string name)
    {
        this->name = name;
    }
    string return_email()
    {
        return email;
    }
    string returnID()
    {
        return userID;
    }
    void printHobby()
    {
        cout << "Hobbies : ";
        for (string hob : hobby)
        {
            cout << hob << ",";
        }
        cout << endl;
    }
    // display details
    void display()
    {
        cout << "\n************************************\n";
        cout << "Name : " << name << endl;
        cout << "Address : " << address << endl;
        printHobby();
        cout << "User ID : " << userID << endl;
        cout << "Account Creation Data : " << creationDate << endl;
        cout << "Email : " << email << endl;
    }
    // if name is empty means user wasnt valid
    bool isValid()
    {
        return !(name == "");
    }
    void changeDetails(list<userAccount> li)
    {
        string user;
        string pass;
        cout << "Enter your ID and password to confirm your Identity.\n";
        cout << "Enter Your Username : ";
        getline(cin, user);
        if (user != userID)
        {
            cout << "Incorrect ID.....\n";
            return;
        }
        cout << "Enter Your Password : ";
        getline(cin, pass);
        if (pass != password)
        {
            cout << "Incorrect password.....\n";
            return;
        }
        while (true)
        {
            int choice = 0;
            cout << "1- Change Your Username.\n";
            cout << "2- Change Your Password.\n";
            cout << "3- Change Your Email.\n";
            cout << "4- Add Hobbies.\n";
            cout << "5- Update Your Address.\n";
            cout << "6- Exit.\n";
            cout << "\nEnter : ";

            cin >> choice;
            system("cls");
            cin.ignore();
            switch (choice)
            {
            case 1:
                while (true)
                {
                    string user;
                    cout << "Enter Your Username : ";
                    getline(cin, user);
                    if (checkUserExist(li, user))
                    {
                        name = user;
                        break;
                    }
                }

                break;
            case 2:
                cout << "Enter Your New Password : ";
                getline(cin, password);

                break;
            case 3:
                while (true)
                {
                    string mail;
                    cout << "Enter your new email : ";
                    getline(cin, mail);
                    if (checkEmail(li, mail))
                    {
                        email = mail;
                        break;
                    }
                }

                break;
            case 4:
                while (true)
                {
                    string input;
                    cout << "Enter Your Hobbies (enter quit to stop adding): ";
                    getline(cin, input);
                    if (input == "quit")
                    {
                        break;
                    }
                    else
                    {
                        hobby.push_back(input);
                    }
                }

                break;
            case 5:
                cout << "Enter Your Address : ";
                getline(cin, address);
                break;
            case 6:
                return;
            default:
                break;
            }
        }
    }
    friend userAccount login(list<userAccount> l1);
};
int userAccount::ID = 1000;
// function to check passoword
userAccount login(list<userAccount> l1)
{
    cout << "Enter your Username : ";
    string username;
    getline(cin, username);
    // ranged based for loop is used
    for (userAccount &acc : l1)
    {
        if (acc.return_name() == username)
        {
            cout << "Username Exist.......\n";
            string pass;
            cout << "Enter password :";
            getline(cin, pass);
            if (acc.password == pass)
            {
                cout << "Access granted ";
                return acc;
            }
            else
            {
                cout << "Incorrect password\n";
            }
        }
    }
    cout << "Username not found\n";

    return userAccount();
}
bool checkUserExist(list<userAccount> li, string name)
{

    for (userAccount obj : li)
    {
        if (name == obj.return_name())
        {
            cout << "\nThis user name exist already you cant Have this Username....\n";
            return false;
        }
    }
    return true;
}
bool checkEmail(list<userAccount> li, string email)
{

    regex pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    if (!regex_match(email, pattern))
    {
        cout << "Enter Valid Email....\n";
        return false;
    }
    for (userAccount obj : li)
    {
        if (email == obj.return_email())
        {
            cout << "Account with this email aleady exist....\n";
            return false;
        }
    }
    return true;
}
// push new user in the link list
void createUser(list<userAccount> &l1)
{
    l1.push_back(userAccount(l1));
    cout << "Account created successfully!\n";
}
string passwordCheck()
{
    string password;
    while (true)
    {
        cout << "Enter your Password : ";
        getline(cin, password);
        if (password.length() >= 8)
        {
            return password;
        }
        cout << "Make sure password is atleast 8 characters\n";
    }
}