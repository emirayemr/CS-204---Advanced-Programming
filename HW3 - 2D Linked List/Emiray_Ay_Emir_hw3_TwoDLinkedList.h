#ifndef Emiray_Ay_Emir_hw3_TwoDLinkedList_h
#define Emiray_Ay_Emir_hw3_TwoDLinkedList_h

#include <string>
using namespace std;

struct node
{
    char data;
    node* right;
    node* down;
    
    // constructor
    node ()
        :data(), right(NULL), down(NULL)
    {}
};

class TwoDLinkedList
{
    private:
        node* head;
    
    public:
        void add_row_sorted(string s);
        void displayFullMatrix();
        void displayFullMatrixReversed();
        void display_rows_starting_with(char c);
        void display_cols_starting_with(char c);
        int delete_rows_starting_with(char c);
        int delete_cols_starting_with(char c);
        void clear();
};

#endif
