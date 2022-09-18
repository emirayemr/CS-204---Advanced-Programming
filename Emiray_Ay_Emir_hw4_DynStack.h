#ifndef Emiray_Ay_Emir_Hw4_DynStack_h
#define Emiray_Ay_Emir_Hw4_DynStack_h

struct StackNode
{
    char symbol;
    int line_number;
    StackNode *next;
    StackNode() : next(nullptr){}
};

class DynStack
{
private:
    StackNode *top;
    void clear();
    StackNode* clone() const;

public:
    DynStack(void);
    DynStack(const DynStack&);
    const DynStack& operator=(const DynStack&);
    void push(char, int);
    void pop(char &, int &);
    bool isEmpty(void);
    ~DynStack();
};

#endif
