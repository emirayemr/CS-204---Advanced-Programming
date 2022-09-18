/* Emir Ay
date created: 02/03/2022
date finished: 14/03/2022
I used both xCode and Visual Studio for coding homework1.
As far as I know, it runs properly on VS2012. */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct cell
{
    char letter;
    char color;
};

string getWord(int& attempt)
/* asks the file name to user and tests if it exists,
returns the "WORD" if user entry is correct */
{
    ifstream input; /* to read the file one-by-one */
    string word; /* the return value */
    do
    {
        string fileName;
        cout << "Please enter the file name: ";
        cin >> fileName; /* get file name */
        
        input.open(fileName.c_str());
        
        if (input.fail()) // error message
            cout << "Couldn't find the file!" << endl;
        else
        {
            /* (if does not fail)
             assign attempt and word respectively */
            input >> attempt >> word;
        }
        
    } while(input.fail()); // if fail do it again
    
    return word; // get the WORD
}

bool isAllLow(string s)
/* Checks if the user entry is made only by low letters */
{
    bool check = true; // return value
    for (int i=0; i < s.length(); i++)
    {
        if (! ('a' <= s.at(i) && s.at(i) <= 'z'))
            check = false;
    }
    
    if (check == false)
        cout << "Your input has illegal letters!" << endl;
    return check;
}

bool isLengthSame (string s, string word)
/* checks the numb of letters */
{
    bool check = true; // return value
    int len = word.length();
    
    if (len > s.length())
    {
        check = false;
        cout << "The word is too short!" << endl;
    }
    else if (len < s.length())
    {
        check = false;
        cout << "The word is too long!" << endl;
    }
    return check;
}

bool isLetterDuplicated(string s)
/* Tests if a letter is repeated in the string */
{
    bool check = true; // return value
    for (int i=0; i < s.length(); i++)
        /* from 0 to the end of the string */
    {
        char test = s.at(i);
        for (int j=0; j < i; j++)
            /* repeats for every i value
               from the beginning */
        {
            char prev = s.at(j);
            if (prev == test)
                check = false;
        }
    }
    
    if (check == false)
        cout << "Your input has a duplicate letter!" << endl;
    return check;
}

bool isFirstGuessValid(string s, string word)
{
    bool check = true; // return value
    if (! isLengthSame(s, word))
        check = false;
    if (check == true && !isAllLow(s))
        check = false;
    if (check == true && !isLetterDuplicated(s))
        check = false;
    return check;
}

string getFirstGuess(string word, vector<vector<char>>& Matrix, cell g)
{
    string guess;
    do
    {
        cout << "What's your guess? ";
        cin >> guess;
    } while (! isFirstGuessValid(guess, word));
    
    for (int i=0; i < word.length(); i++)
    {
        g.letter = guess.at(i);
        Matrix[0][i*2] = g.letter;
    }
    return guess;
}

bool isGuessSame(vector<vector<char>>& Matrix, string guess, int soFar) // soFar = column size
/* Checks if a guess was already typed */
{
    bool check = true; // return value
    int count = 0;
    for (int i=0; i < soFar && count < guess.length(); i++)
        // i = column variable (top to bottom)
    {
        count = 0; // if guess is not same previous test -> turn it into 0
        for (int j=0; j < guess.length(); j++) // j = row variable (left to right)
        {
            char test = Matrix[i][j*2]; // j*2 -> there are color variables on odd numbers
            // here j also suits for guess' letters
            if (guess.at(j) == test)
            {
                count ++;
            }
        }
    }
    if (count == guess.length())
    {
        cout << "You've already tried this word!" << endl;
        check = false;
    }
    return check;
}

bool isGreenUsed(string guess, vector<vector<char>> Matrix, int soFar)
{
    bool check = true; // return value
    int rowSize = guess.length();
    for (int i=0; i < soFar ; i++) // top to bottom
    {
        for (int j=0; j < rowSize; j++) // left to right (also stands for guess position)
            /* Matrix[i][j] */
        {
            if (Matrix[i][j*2+1] == 'G')
                // j=0 -> 1 , j=1 -> 3 , j=2 -> 5, j=5 -> 11
                // green letter must be on the same pos, so at "j"
            {
                if (Matrix[i][j*2] != guess.at(j)) // j*2 -> one step before "G"
                    check = false;
            }
        }
    }
    
    if (check == false)
        cout << "You did not use the green letter in your word!\n";
    
    return check;
}

bool isOtherGuessValid(string s, string w, vector<vector<char>> Matrix, int soFar)
{
    bool check = true; // return value
    if (! isFirstGuessValid(s, w)) // same parameters
        check = false;
    if (check == true && !isGuessSame(Matrix, s, soFar))
        check = false;
    if (check == true && !isGreenUsed(s, Matrix, soFar))
        check = false;
    return check;
}

string getOtherGuess(string word, cell g, vector<vector<char>>& Matrix, int& soFar)
{
    string guess;
    do
    {
        cout << "What's your guess? ";
        cin >> guess;
    } while (! isOtherGuessValid(guess, word, Matrix, soFar));
    
    soFar++; // number of guesses so far is updated
    for (int i=0; i < word.length(); i++)
    {
        g.letter = guess.at(i);
        Matrix[soFar-1][i*2] = g.letter; // soFar-1 -> i.e. there are 2 words but pos is "1" for the last one
    }
    return guess;
}

void updateColorAndLists(cell& g, int i, int j, string word, vector<vector<char>> Matrix)
/* Updates color as G or Y or B */
{
    int count = 0;
    for (int k=0; k < word.length(); k++)
    {
        char let = Matrix[i][j-1];
        if (let == word.at(k))
        {
            if (j/2 == k)
            {
                g.color = 'G';
            }
            else
                g.color = 'Y';
            count++;
        }

        if (count == 0)
            g.color = 'B';
    }
}

void printEmptyRows(int attempt, int let_num, int soFar, cell g);

void printMatrix(cell g, string word, vector<vector<char>>& Matrix, int attempt, int let_num, int soFar)
/* prints out the table for user
   also, updtes the Matrix */
{
    string guess;
    for (int i=0; i < soFar; i++)
    {
        for (int j=0; j < let_num*2; j++)
        {
            if (j == 0)
            {
                cout << "|| " << Matrix[i][j] << " , ";
            }
            else if (j % 2 == 0)
            {
                cout << " " << Matrix[i][j] << " , ";
            }
                
            else
            {
                updateColorAndLists(g, i, j, word, Matrix);
                Matrix[i][j] = g.color;
                cout << Matrix[i][j] << " ||";
            }
            
        }
        cout << endl;
    }
    
    g.color = '-';
    g.letter = '-';
    printEmptyRows(attempt, let_num, soFar, g);
}

void printEmptyRows(int attempt, int let_num, int soFar, cell g)
{
    int emptyRows = attempt - soFar;
    for (int j=0; j < emptyRows; j++)
    {
        for (int k=0; k < let_num; k++)
        {
            cout << "|| " << g.letter << " , " << g.color << " ";
        }
        cout << "||" << endl;
    }
}

void getResult(string word, string guess)
/* Finally gives output if user win or lose */
{
    if (guess == word)
        cout << "You win!\n";
    
    else
        cout << "You lose!\n";
}

int main()
{
    cout << "Welcome to SWordle!" << endl;
    
    int attempt = 0; // max number of attempts
    
    string word = getWord(attempt); // word will be guessed
                    /* get the word and
                    update attempt value */
    
    int let_num = word.length(); // numb of letters in WORD
    
    cout << "The word that you will guess has " << let_num << " letters and you have " << attempt << " attempts." << endl;
    
    string guess;
    int soFar = 1; // to know how many guesses are already there, 1 is for very first guess
    
    vector<vector<char>> Matrix(attempt,vector<char>(let_num*2));
    /* letters will be stored with their colors
     if attempt = 3, length = 5
       0   1    2   3    4   5    6   7    8   9
       =   =    =   =    =   =    =   =    =   =
    || L , C || L , C || L , C || L , C || L , C ||
    || - , - || - , - || - , - || - , - || - , - ||
    || - , - || - , - || - , - || - , - || - , - ||
     */
    
    cell g;
    g.letter = '-';
    g.color = '-';
    /* g.letter -> every char in "guess"
       g.color -> 'G' 'Y' 'B' */

    for (int i=0; i < attempt; i++)
    {
        if (i == 0)
            guess = getFirstGuess(word, Matrix, g);
        else
            guess = getOtherGuess(word, g, Matrix, soFar);
        
        printMatrix(g, word, Matrix, attempt, let_num, soFar);
        
        if (guess == word)
        {
            i = attempt; /* so that loop will never be executed,
                          and guess value will stay as "WORD",
                          in this case user will win */
        }
    }
    
    getResult(word, guess);
    return 0;
}
