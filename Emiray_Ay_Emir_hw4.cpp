/* Emir Ay
   Date created: 06/04/2022
   Date finished: 11/04/2022
   I used both xCode and Visual Studio for coding homework4.
   As far as I know, it runs properly on VS2012. */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Emiray_Ay_Emir_hw4_DynStack.h"
using namespace std;

void getInput(ifstream &input)
{
    do
    {
        string fileName;
        cout << "Please enter the file name: ";
        cin >> fileName; /* get file name */
        input.open(fileName.c_str());
        if (input.fail())
            cout << "File not found." << endl;
    } while(input.fail()); // if fail do it again
}

void giveOutput (char c, int line_num, DynStack &Stack, bool &check)
{
    if (c == '{' || c == '[' || c == '(' )
    {
        Stack.push(c, line_num);
        cout << "Found the opening symbol " << c << " at line " <<  line_num << endl;
    }
    else if (c == '}' || c == ']' || c == ')')
    {
        if (! Stack.isEmpty())
        {
            char pre_char;
            int pre_line;
            Stack.pop(pre_char, pre_line);
            if (c == ')')
            {
                if (pre_char == '(')
                    cout << "Found the closing symbol " << c << " at line " << line_num << " which closes the opening symbol " << pre_char << " at line " << pre_line << endl;
                else
                {
                    check = false;
                    cout << "ERROR!!! Found the closing symbol " << c << " at line " << line_num << " but the last unclosed opening symbol is " << pre_char << " at line " << pre_line << endl;
                }
            }
            else
            {
                if (pre_char == c-2)
                    cout << "Found the closing symbol " << c << " at line " << line_num << " which closes the opening symbol " << pre_char << " at line " << pre_line << endl;
                else
                {
                    check = false;
                    cout << "ERROR!!! Found the closing symbol " << c << " at line " << line_num << " but the last unclosed opening symbol is " << pre_char << " at line " << pre_line << endl;
                }
            }
        }
        else
        {
            check = false;
            cout << "ERROR!!! Found the closing symbol " << c << " but there are no unclosed opening symbols!" << endl;
        }
    }
}

void giveFullOutput (char c, string line, DynStack &Stack, bool &check)
{
    static int line_num = 1;
    for (int i=0; i<line.length(); i++)
    {
        c = line.at(i);
        giveOutput(c, line_num, Stack, check);
        
    }
    line_num++;
}

int main()
{
    DynStack Stack;
    ifstream input;
    getInput(input);
    
    string line;
    char c = ' '; // just for initializing
    bool isSuccessful = true; // checks if closing signs ") ] }" closes some opening signs
    while (getline(input, line) && isSuccessful)
    {
        giveFullOutput(c, line, Stack, isSuccessful);
    }
    
    if (isSuccessful) // is there any error until now (about not-closing closing signs)
    {
        if (Stack.isEmpty())
            cout << "File processed successfully. No errors were found." << endl;
        else // means that there are some unclosed opening signs "( [ {"
        {
            cout << "ERROR!!! The following opening symbols were not closed:" << endl;
            while (! Stack.isEmpty())
            {
                int n;
                Stack.pop(c, n);
                cout << "  Symbol " << c << " at line " << n << endl;
            }
        }
    }
    return 0;
}
