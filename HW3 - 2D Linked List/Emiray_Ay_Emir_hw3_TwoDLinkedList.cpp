/* Emir Ay
 date created: 24/03/2022
 date finished: 04/04/2022
 I used both xCode and Visual Studio for coding homework3, and I encountered some differences between them. So I corrected that parts in VS way.
 As far as I know, it runs properly on VS2012. */
# include <iostream>
# include <string>
# include "Emiray_Ay_Emir_hw3_TwoDLinkedList.h"
using namespace std;

int getTotalRowNumber(node* head)
{
    node* p = head;
    int row = 1;
    if (p == NULL)
        row = 1;
    else
    {
        while (p->down != NULL)
        {
            row++;
            p = p->down;
        }
    }
    return row;
}

void veryFirstRow(node* &head, string s, int len)
// adds very first word to the linked list
{
    node* p = head;
    for (int i=0; i < len; i++)
    {
        p->data = s.at(i);
        if (i < len - 1)
        {
            p->right = new node();
            p = p->right;
        }
    }
}

void addToEnd(node* &head, string s, int len)
// if word's first char's ascii value larger than all previous words, adds it to the end
{
    node* p = head;
    while (p->down != NULL)
        p = p->down;
    
    p->down = new node();
    node* q = p->down;
    
    for (int i=0; i < len; i++)
    {
        q->data = s.at(i);
        if (i < len-1)
        {
            q->right = new node();
            p = p->right;
            p->down = q->right;
            q = q->right;
        }
    }
}

void Case1(node* akrep, node* yelkovan, int len)
// akrep at last row & yelkovan will place akrep->down(new node) and yelkovan gets akrep->data for every column
{
    akrep->down = new node();
    yelkovan = akrep->down;
    for (int i=0; i < len; i++)
    {
        yelkovan->data = akrep->data;
        if (i < len-1)
        {
            yelkovan->right = new node();
            akrep = akrep->right;
            akrep->down = yelkovan->right;
            yelkovan = yelkovan->right;
        }
    }
}

void Case2(node* akrep, node* yelkovan, int len)
// when akrep and yelkovan are both at middle rows, yelkovan gets akrep->data for every column
{
    yelkovan = akrep->down;
    for (int i=0; i < len; i++)
    {
        yelkovan->data = akrep->data;
        if (i < len-1)
        {
            akrep = akrep->right;
            yelkovan = yelkovan->right;
        }
    }
}

void Case3(node* akrep, int len, string s)
// happens at the end, akrep's row (first or first will be updated row) will be updated as "s"
{
    for (int i=0; i < len; i++)
    {
        akrep->data = s.at(i);
        if (i < len-1)
            akrep = akrep->right;
    }
}

void declareNewHead (node* &head)
{
    static bool isHeadNew = true;
    if (isHeadNew == true)
    {
        head = new node;
        head->data = '-'; // just for initializing
        isHeadNew = false;
    }
}

void TwoDLinkedList::add_row_sorted(string s)
{
    declareNewHead(head);
    int len = s.length();
    node* first = head;
    if (! ('a' <= first->data && first->data <= 'z')) // probably first row
        veryFirstRow(head, s, len);
    
    else
    {
        int row = getTotalRowNumber(head);
        bool check = false;
        int current = row-1;
        
        while (current >= 0 && check != true)
        {
            if (first->data >= s.at(0))
            {
                node* akrep = first->right;
                while (akrep != first)
                {
                    akrep = first;
                    for (int i=0; i<current; i++)
                        akrep = akrep->down;
                    
                    node* yelkovan = akrep; // just for initializing yelkovan
                    if (current == row-1)
                        Case1(akrep, yelkovan, len);
                    else
                        Case2(akrep, yelkovan, len);
                    
                    if (akrep == first)
                        Case3(akrep, len, s);
                    current--;
                }
                check = true;
            }
            if (first->down != NULL)
                first = first->down;
            current--;
            row--;
        }

        if (check == false)
            addToEnd(head, s, len);
    }
}

void TwoDLinkedList::displayFullMatrix()
{
    node* p = head;
    while (p != NULL && ('a' <= head->data && head->data <= 'z'))
        // alpha check -> to prevent big blank space (when all columns are removed)
    {
        node* q = p;
        while (q != NULL)
        {
            cout << q->data;
            q = q->right;
        }
        p = p->down;
        cout << endl;
    }
}

void TwoDLinkedList::displayFullMatrixReversed()
{
    int row = getTotalRowNumber(head);
    
    int current = row-1;
    if (head != NULL)
    {
        while (current >= 0 && ('a' <= head->data && head->data <= 'z'))
            // alpha check -> to prevent big blank space (when all columns are removed)
        {
            node* p = head;
            for (int i=0; i < current; i++)
                p = p->down;
            
            node* q = p;
            while (q != NULL)
            {
                cout << q->data;
                q = q->right;
            }
            cout << endl;
            current--;
        }
    }
}

void TwoDLinkedList::display_rows_starting_with(char c)
{
    node* p = head;
    while (p != NULL)
    {
        if (p->data == c)
        {
            node* q = p;
            while (q != NULL)
            {
                cout << q->data;
                q = q->right;
            }
            cout << endl;
        }
        p = p->down;
    }
}

void TwoDLinkedList::display_cols_starting_with(char c)
{
    node* p = head;
    while (p != NULL)
    {
        if (p->data == c)
        {
            node* q = p;
            while (q != NULL)
            {
                cout << q->data;
                q = q->down;
                cout << endl;
            }
            cout << endl;
        }
        p = p->right;
    }
}

int TwoDLinkedList::delete_rows_starting_with(char c)
{
    int n = 0;
    int cur_row = 0;
    node* p = head;
    while (p != NULL)
    {
        if (p->data == c)
        {
            n++;
            if (cur_row == 0)
            {
                head = head->down;
                node* del = p;
                p = p->down;
                while (del != NULL)
                {
                    node* q = del->right;
                    delete del;
                    del = q;
                }
            }
            else
            {
                node* pre = head;
                for (int i=0; i < cur_row-1; i++)
                    pre = pre->down; // n
                node* del = p; // n+1 (will be deleted)
                p = p->down; // n+2
                while (del != NULL)
                {
                    pre->down = del->down;
                    node* q = del->right;
                    delete del;
                    del = q;
                    pre = pre->right;
                }
            }
            cur_row--;
        }
        else
            p = p->down;
        cur_row++;
    }
    return n;
}

int TwoDLinkedList::delete_cols_starting_with(char c)
{
    int n = 0;
    int cur_col = 0;
    node* p = head;
    while (p != NULL)
    {
        if (p->data == c)
        {
            n++;
            if (cur_col == 0)
            {
                head = head->right;
                node* del = p;
                p = p->right;
                while (del != NULL)
                {
                    node* q = del->down;
                    delete del;
                    del = q;
                }
            }
            else
            {
                node* pre = head;
                for (int i=0; i<cur_col-1; i++)
                    pre = pre->right; // n
                node* del = p; // n+1 (will be deleted)
                p = p->right; // n+2
                while (del != NULL)
                {
                    pre->right = del->right;
                    node* q = del->down;
                    delete del;
                    del = q;
                    pre = pre->down;
                }
            }
            cur_col--;
        }
        else
            p = p->right;
        cur_col++;
    }
    return n;
}

void TwoDLinkedList::clear()
{
    while (head != NULL)
    {
        node* del = head;
        head = head->down;
        while (del != NULL)
        {
            node* p = del->right;
            delete del;
            del = p;
        }
    }
}
