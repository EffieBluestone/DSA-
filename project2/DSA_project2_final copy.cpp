#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

template <typename Data>
class SimpleList
{
    class Node
    {
    private:
        Data data;
        Node *nextNode;

    public:
        Node(Data myInfo, Node *nextAddress)
        {
            data = myInfo;
            nextNode = nextAddress;
        }
        Node(Data myInfo)
        {
            data = myInfo;
            nextNode = NULL;
        }
        void setnextNode(Node *newNode)
        {
            nextNode = newNode;
        }
        Data getData()
        {
            return data;
        }
        Node *getnextNode()
        {
            return nextNode;
        }
    };

private:
    string name;
    Node *start;
    Node *end;

protected:
public:
    virtual void push(Data value) = 0;
    virtual Data pop() = 0;
    SimpleList(string n)
    {
        end = NULL;
        start = NULL;
        name = n;
    }
    void addNodeToStart(Data dataValue)
    {
        Node *newNode = new Node(dataValue);
        if (end == NULL)
        {
            end = newNode;
        }
        Node *temp = start;
        start = newNode;
        newNode->setnextNode(temp);
    }
    Data removeFromStart()
    {
        Node *temp = start->getnextNode();
        Data val = start->getData();
        // add delete start here
        start = temp;
        return val;
    }
    void addNodeToEnd(Data dataValue)
    {
        Node *newNode = new Node(dataValue);
        if (end == NULL)
        {
            addNodeToStart(dataValue);
        }
        else
        {
            end->setnextNode(newNode);
            end = newNode;
        }
    }

    void printStartEnd()
    {
        cout << start->getData() << endl;
        cout << end->getData() << endl;
    }
    string getName()
    {
        return name;
    }

    bool isEmpty()
    {
        if (start == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

template <typename Data>
class Stack : public SimpleList<Data>
{
public:
    Stack(string name) : SimpleList<Data>(name){};

    void push(Data dataValue)
    {
        return this->addNodeToStart(dataValue);
    }
    Data pop()
    {
        return this->removeFromStart();
    }
};

template <typename Data>
class Queue : public SimpleList<Data>
{
public:
    Queue(string name) : SimpleList<Data>(name){};

    void push(Data dataValue)
    {
        return this->addNodeToEnd(dataValue);
    }
    Data pop()
    {
        return this->removeFromStart();
    }
};

template <class Data>
SimpleList<Data> *exists(string name, list<SimpleList<Data> *> *list)
{
    for (auto object : *list)
    {
        if (object->getName() == name)
        {
            return object;
        }
    }

    return NULL;
}

string create(string name, string type, list<SimpleList<int> *> *listSLi, list<SimpleList<double> *> *listSLd, list<SimpleList<string> *> *listSLs)
{
    if (name[0] == 'i')
    {
        SimpleList<int> *SLi = exists(name, listSLi);

        if (SLi == NULL)
        {
            if (type == "stack")
            {
                listSLi->push_back(new Stack<int>(name));
            }
            else if (type == "queue")
            {
                listSLi->push_back(new Queue<int>(name));
            }
        }
        else
        {
            return "ERROR: This name already exists!\n";
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *SLi = exists(name, listSLd);

        if (SLi == NULL)
        {
            if (type == "stack")
            {
                listSLd->push_back(new Stack<double>(name));
            }
            else if (type == "queue")
            {
                listSLd->push_back(new Queue<double>(name));
            }
        }
        else
        {
            return "ERROR: This name already exists!\n";
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *SLi = exists(name, listSLs);

        if (SLi == NULL)
        {
            if (type == "stack")
            {
                listSLs->push_back(new Stack<string>(name));
            }
            else if (type == "queue")
            {
                listSLs->push_back(new Queue<string>(name));
            }
        }
        else
        {
            return "ERROR: This name already exists!\n";
        }
    }

    return "";
}

string push(string name, string value, list<SimpleList<int> *> *listSLi, list<SimpleList<double> *> *listSLd, list<SimpleList<string> *> *listSLs)
{

    if (name[0] == 'i')
    {
        SimpleList<int> *SLi = exists(name, listSLi);
        if (SLi == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            SLi->push(stoi(value));
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *SLd = exists(name, listSLd);
        if (SLd == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            SLd->push(stod(value));
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *SLs = exists(name, listSLs);
        if (SLs == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            SLs->push(value);
        }
    }

    return "";
}

string pop(string name, list<SimpleList<int> *> *listSLi, list<SimpleList<double> *> *listSLd, list<SimpleList<string> *> *listSLs)
{
    if (name[0] == 'i')
    {
        SimpleList<int> *SLi = exists(name, listSLi);
        if (SLi == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            if (SLi->isEmpty())
            {
                return "ERROR: This list is empty!\n";
            }
            else
            {
                int p = SLi->pop();
                return "Value popped: " + to_string(p) + "\n";
            }
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *SLd = exists(name, listSLd);
        if (SLd == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            if (SLd->isEmpty())
            {
                return "ERROR: This list is empty!\n";
            }
            else
            {
                double p = SLd->pop();
                cout << "test" << p << endl;

                stringstream ss;
                ss << p;
                string str = ss.str();

                return "Value popped: " + str + "\n";
            }
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *SLs = exists(name, listSLs);
        if (SLs == NULL)
        {
            return "ERROR: This name does not exist!\n";
        }
        else
        {
            if (SLs->isEmpty())
            {
                return "ERROR: This list is empty!\n";
            }
            else
            {
                string p = SLs->pop();
                return "Value popped: " + p + "\n";
            }
        }
    }

    return "";
}

void parse(string line, list<SimpleList<int> *> *listSLi, list<SimpleList<double> *> *listSLd, list<SimpleList<string> *> *listSLs, ofstream *outputStream)
{
    stringstream ss(line);
    string command, name, type;
    ss >> command >> name >> type;

    *outputStream << "PROCESSING COMMAND: " << line << endl;

    if (command == "create")
    {
        *outputStream << create(name, type, listSLi, listSLd, listSLs);
    }
    else if (command == "push")
    {
        *outputStream << push(name, type, listSLi, listSLd, listSLs);
    }
    else if (command == "pop")
    {
        *outputStream << pop(name, listSLi, listSLd, listSLs);
    }
}

void getFileNames(string &fileIn, string &fileOut)
{ // code to get the file names
    cout << "Enter the name of the input file: ";
    cin >> fileIn;
    cout << "Enter the name of the output file: ";
    cin >> fileOut;
}

int main()
{
    list<SimpleList<int> *> listSLi;
    list<SimpleList<double> *> listSLd;
    list<SimpleList<string> *> listSLs;

    string fileIn, fileOut;
    getFileNames(fileIn, fileOut);

    ifstream inputStream(fileIn);
    ofstream outputStream(fileOut);
    string line;
    if (inputStream.is_open())
    {
        while (getline(inputStream, line))
        {
            parse(line, &listSLi, &listSLd, &listSLs, &outputStream);
        }
    }
}