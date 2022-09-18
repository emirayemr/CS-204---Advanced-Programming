/* Emir Ay
 date created: 17/03/2022
 date finished: 22/03/2022
 I used both xCode and Visual Studio for coding homework2.
 As far as I know, it runs properly on VS2012. */
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct node
{
    char ch;
    node* next;
    
    // constructor
    node ()
        :ch(), next(NULL)
    {}
};

void updateList(node* &List, ifstream& input)
/* with this function, I can obtain linked lists for each word */
{
    node* p = List;
    while (input >> p->ch)
    {
        p->next = new node();
        
        p = p->next;
    }
}

bool isLowerCase (char L)
{
    bool check = true;
    if (! ('a' <= L && L <= 'z'))
    {
        check = false;
    }
    return check;
}

void getInputs(char no, ifstream& input)
/* just opens the txt files */
{
    do
    {
        string fileName;
        cout << "Please enter the file " << no << " name: ";
        cin >> fileName; /* get file name */
        input.open(fileName.c_str());
    } while(input.fail()); // if fail do it again
}

void printWord (node* List)
/* prints current list when it's called */
{
    node* p = List;
    while (p != NULL)
    {
        cout << p->ch;
        p = p->next;
    }
    cout << endl;
}

void giveScreen(node* List, char no)
/* displays the lists to the screen as:
    List1: word1
    List2: word2 */
{
    cout << "List" << no << ": ";
    printWord(List);
}

bool isCommandValid(string c)
/* just checks command validity */
{
    bool check = true;
    if (c != "sim" && c != "del1" && c != "del2" && c != "insert1" && c != "insert2" && c != "exit")
        check = false;
    
    if (check == false)
        cout << "Invalid command." << endl << endl;
    return check;
}

string getCommand(char& L1, char& L2)
/* gets command string from the user until user enters "exit" */
{
    string c;
    do
    {
        cout << "Enter a command and its corresponding argument(s), if any: ";
        cin >> c;
        
        if (c == "del1" || c == "del2")
            cin >> L1;
        else if (c == "insert1" || c == "insert2")
            cin >> L1 >> L2;
        
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
            // ignore any other inputs
    } while (! isCommandValid(c));
    
    return c;
}

/* Begin: code taken from linkedList.cpp */
node * GetNthNode(node *head, int n)
{
    int counter=0;
    node *ptr = head;
    while (ptr != NULL && counter<n-1)
    {
        ptr = ptr->next;
        counter++;
    }
    return ptr;
}
/* End: code taken from linkedList.cpp */

int getNULLnodePos(node* List)
/* so that I can reach the last node and "its position = n" */
{
    int n = 0;
	node* p = List;
	while (p != NULL)
	{
		p = p->next;
		n++;
	}
	return n;
}

void Sim(node* List1, node* List2)
/* displays sim command*/
{
    cout << "Displaying the contents of the two lists:\n";
    giveScreen(List1, '1');
    giveScreen(List2, '2');
    
    node *p1 = List1, *p2 = List2;
    int count = 0;
    while (p1->next != NULL && p2->next != NULL)
    {
		if (isLowerCase(p1->ch) && isLowerCase(p2->ch) && p1->ch == p2->ch)
			count++;
        
        p1 = p1->next;
        p2 = p2->next;
    }
    cout << "There is/are " << count << " letter(s) matched in the same positions in both lists." << endl << endl;
}

void Insert(node* &List, char let1, char let2)
/* displays insert1 and insert2 commands*/
{
    node *p = List;
    int count = 0; // to prevent insertion to happen more than once
    for (int i=0; p != NULL; i++)
    {
        if (count == 0 && p->ch == let2)
        {
			int last = getNULLnodePos(List);
            for (int j=last; i < j; j--)
            {
                 node* q  = GetNthNode(List, j);
                    // to begin from the end
                
                if (j == last)
                    q->next = new node();
                else
                    (q->next)->ch = q->ch;
                // place every letter to next node
            }
            (p->next)->ch = let1; // insert let1 next to the let1
            
            count ++; // it happened, no more will happen
            
            // I'm sure count!=0 here
            cout << "The node with " << let1 << " has been inserted after the first occurrence of a node with " << let2 << " value.\n";
        }
        p = p->next;
    }
    /*
     WHAT IF: let2 not in List
        -> Insert let1 on first node
    */
    p = List; // start from first node
    if (count == 0) // means that no p->ch == let2
    {
        cout << "The node with " << let2 << " value does not exist. Therefore, Inserting " << let1 << " at the beginning of the list.\n";
        
        int last = getNULLnodePos(List);
        for (int i=last; 0 < i; i--)
        {
            node* q = GetNthNode(List, i);
            if (i == last)
                q->next = new node();
            else
                (q->next)->ch = q->ch;
        }
        p->ch = let1; // here let1 is inserted on the first node of the list
    }
}

bool Del(node* &List, char let)
/* if it's bool value is true, it displays del1 and del2 commands
   otherwise not */
{
    node* p = List;
    bool check = false;
    for (int i=0; p != NULL; i++)
    {
        if (p->ch == let)
        {
			node* q = p;
            for (int j=i; q != NULL; j++)
            {
                q = GetNthNode(List, j+1); // right here, I realized that List index starts from 1 :D
                if (q->next == NULL)
                    q = NULL;
                else
                {
                    q->ch = (q->next)->ch;
                }
            }
            i = -1; /* at the end of the loop -> i++ -> i=0 */
            check = true;
        }
        p = p->next;
        if (i == -1)
            p = List; // to start from first position
    }
    return check;
}

/* Begin: code taken from linkedList.cpp */
void ClearList(node *head)
{
    node *ptr;
    while(head!=NULL)
    {
        ptr=head;
        head=head->next;
        delete ptr;
    }
}
/* End: code taken from linkedList.cpp */

void giveOutput(string com, node* &List1, node* &List2, char let1, char let2)
/* displays whole code since first command */
{
    /* SIM */
    if (com == "sim")
        Sim(List1, List2);
    /* INSERT1 */
    else if (com == "insert1")
    {
        if (! isLowerCase(let1) || ! isLowerCase(let2))
			cout << "Invalid arguments." << endl;
		else
        {
            cout << "Inserting " << let1 << " after " << let2 << " in List1.\n";
            Insert(List1, let1, let2);
            cout << "The current content of List1 is: ";
            printWord(List1);
        }
        cout << endl;
            
    }
    /* INSERT2 */
    else if (com == "insert2")
    {
        if (! isLowerCase(let1) || ! isLowerCase(let2))
			cout << "Invalid arguments." << endl;
		else
        {
            cout << "Inserting " << let1 << " after " << let2 << " in List2.\n";
            Insert(List2, let1, let2);
            cout << "The current content of List2 is: ";
            printWord(List2);
        }
        cout << endl;
    }
    /* DEL1 */
    else if (com == "del1")
    {
        if (! isLowerCase(let1))
			cout << "Invalid arguments." << endl;
        else if (Del(List1, let1))
        {
            cout << "Deleting all occurrences of " << let1 << " in List1.\n";
            cout << "The current content of List1 is: ";
			printWord(List1);
        }
		else
			cout << "No deletion as the value " << let1 << " was not found in the list\n";
        cout << endl;
    }
    /* DEL2 */
    else if (com == "del2")
    {
        if (! isLowerCase(let1))
			cout << "Invalid arguments." << endl;
        else if (Del(List2, let1))
        {
			cout << "Deleting all occurrences of " << let1 << " in List2.\n";
            cout << "The current content of List2 is: ";
            printWord(List2);
        }
        else
			cout << "No deletion as the value " << let1 << " was not found in the list\n";
        cout << endl;
    }
    /* EXIT */
    else if (com == "exit")
    {
        cout << "Clearing the two lists and saying Goodbye!\n";
        ClearList(List1);
        ClearList(List2);
    }
}

int main()
{
    node* wordList1, * wordList2; // 2 words will be stored
    wordList1 = new node;
    wordList2 = new node;
    /* first node -> zero, next node -> null */
    
    ifstream input1, input2;
    getInputs('1', input1);
    getInputs('2', input2);
    /* ask user the file names until to get proper ones */
    
    updateList(wordList1, input1);
    updateList(wordList2, input2);
    /* get linked lists */
    
    giveScreen(wordList1, '1');
    giveScreen(wordList2, '2');
    cout << endl;
    
    // commands and linked list processes
    string command;
    char let1 = ' ', let2 = ' ';
    do
    {
        command = getCommand(let1, let2);
        giveOutput(command, wordList1, wordList2, let1, let2);
    } while (command != "exit");
    
    return 0;
}
