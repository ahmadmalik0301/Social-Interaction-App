#include <ctime>
using namespace std;

struct node
{
    int postID;
    static int ID;
    string postContent;
    vector<node *> replies;
    string name;
    string postingTime;
    node(string name)
    {
        ID++;
        postID = ID;
        this->name = name;
        time_t currentTime = time(0);
        postingTime = ctime(&currentTime);
    }
    void addmsg()
    {
        cout << "Enter Your Message : ";
        getline(cin, postContent);
    }
    void addReply(node *reply)
    {
        replies.push_back(reply);
    }
};
class postingArea
{
    node *root;

public:
    // add a msg to a post
    postingArea(string name)
    {
        root = new node(name);
        root->addmsg();
    }
    void addPost()
    {
    }
    void addReply(int postID, string name)
    {
        // find the post and return it to parent
        node *parent = findPost(root, postID);
        // if parent is not null create a new reply and add it to replies vector pointers of the post
        if (parent != NULL)
        {
            node *reply = new node(name);
            reply->addmsg();
            parent->addReply(reply);
        }
        else
        {
            cout << "No Post found with this ID....\n";
        }
    }
    node *findPost(node *cur, int postID)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }
        if (cur->postID == postID)
        {
            return cur;
        }
        // go through all the substrees of the replies
        for (int i = 0; i < cur->replies.size(); i++)
        {
            node *reply = cur->replies[i];
            node *foundPost = findPost(reply, postID);
            if (foundPost != nullptr)
            {
                return foundPost;
            }
        }
        return nullptr;
    }

    void printTree(node *currentNode, int depth)
    {
        if (currentNode == NULL)
        {
            return;
        }
        cout << "\n\n";
        // for each depth add a space
        for (int i = 0; i < depth; ++i)
        {
            cout << "  ";
        }
        cout << "|-- Post ID: " << currentNode->postID << " Message: " << currentNode->postContent << endl;
        // for each subtree add a depth
        for (int i = 0; i < currentNode->replies.size(); i++)
        {
            node *reply = currentNode->replies[i];
            printTree(reply, depth + 1);
        }
        cout << "\n\n";
    }
    void printPostingArea()
    {
        printTree(root, 0);
    }
    int returnRootID()
    {
        return root->postID;
    }
    void printPostOnly()
    {
        cout << "+--------------------------------------------------+\n";
        cout << " Post ID       : " << root->postID << "\n";
        cout << " User          : " << root->name << "\n";
        cout << "+--------------------------------------------------+\n\n";
        cout << " " << root->postContent << "\n\n";
        cout << "+--------------------------------------------------+\n";
        cout << " Posting Time  : " << root->postingTime << "\b\n";
        cout << "+--------------------------------------------------+\n";
        cout << "\n\n";
    }
    void deletePost(int postID, string name)
    {
        // if root match with ID delete it
        if (root->postID == postID && root->name == name)
        {
            delete root;
            cout << "Post Deleted Successfully.\n";
            return;
        }
        // find post with tha ID and delete it
        node *cur = findPost(root, postID);
        if (cur->name == name && cur != nullptr)
        {
            delete cur;
            cout << "Reply deleted SuccessFully\n";
            return;
        }
        else
        {
            cout << "No such post With ID exist\n";
        }
    }
    node *returnRoot()
    {
        return root;
    }
};
int node::ID = 1000;
void postManager(list<postingArea> &p1, string name)
{

    int choice = 0;
    while (true)
    {
        cout << "1- Enter 1 to create a Post\n";
        cout << "2- Enter 2 to Open comment Section of a Post\n";
        cout << "3- Enter 3 to View all Posts\n";
        cout << "3- Enter 4 to Delete a Post or Reply\n";
        cout << "4- Enter 5 to return\n";
        cout << "Enter : ";
        cin >> choice;
        system("cls");
        cin.ignore();
        switch (choice)
        {
        case 1:
            p1.push_back(postingArea(name));
            break;
        case 2:
        {
            int postID;
            cout << "Enter Post You want to View : ";
            cin >> postID;
            cin.ignore();
            list<postingArea>::iterator post;
            // for each post made check if is match with the entred post and display the whole tree
            for (post = p1.begin(); post != p1.end(); post++)
            {
                if (post->returnRootID() == postID)
                {
                    post->printPostingArea();
                    break;
                }
            }
            cout << "Enter ID you wanna reply to : ";
            cin >> postID;
            cin.ignore();
            post->addReply(postID, name);
        }
        break;

        case 3:
            // display only the root of the each tree
            for (postingArea post : p1)
            {
                post.printPostOnly();
                cout << "| ********************************************************* |\n\n";
            }
            break;
        case 4:
        {
            int postID;
            cout << "Enter the ID of the post or reply you want to delete: ";
            cin >> postID;
            cin.ignore();
            list<postingArea>::iterator post;
            for (post = p1.begin(); post != p1.end();)
            {
                // travese all the tree in the list and find the post
                if (post->returnRootID() == postID)
                {
                    // delete the post and t
                    post->deletePost(postID, name);
                    post = p1.erase(post);
                    break;
                }
                else if (post->findPost(post->returnRoot(), postID) != nullptr)
                {
                    post->deletePost(postID, name);
                }
                else
                {
                    ++post;
                }
            }
        }
        break;
        case 5:
            return;
        default:
            cout << "Invaid Command.\n";
        }
    }
}