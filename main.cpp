/* Infix to Postfix program
Data Structure
CS214               */
#include<iostream>
#include<string>
using namespace std;


struct node {
    char data;
    struct node *next;
};

struct node *TOP = NULL;

bool isEmpty(){
    if (TOP == NULL )
        return true;
    else
        return false;
}


char peek(){
    return TOP->data;
}
// Push function inserts value in stack.

void push (char x)
{
    struct node *NewNode;
    NewNode = new (node);
    NewNode->data = x;
    NewNode->next = NULL;

    if(TOP == NULL) TOP = NewNode;
    else
    {
        NewNode->next = TOP;
        TOP=NewNode;
    }
}



// Pop function to remove an item from stack.


char pop ()
{
    struct node *T;
    char x;
    T=TOP;
    x= T->data;
    TOP = TOP->next;
    return x;
}




int priority (char alpha){
    switch (alpha){
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        case '^': return 3;

        default: return 0;
    }
}

bool IsOperand(char C)
{
    if(C >= '0' && C <= '9') return true;
    if(C >= 'a' && C <= 'z') return true;
    if(C >= 'A' && C <= 'Z') return true;
    return false;
}

string INtoPOST(string infix)
{
    int i=0;
    string postfix = "";

    while(infix[i]!='\0')
    {

// if operand add to the postfix expression
        if(IsOperand(infix[i]))
        {
            postfix += infix[i];
            i++;
        }
// if opening bracket then push the stack
        else if(infix[i]=='(')
        {
            push(infix[i]);
            i++;
        }
// if closing bracket encounted then keep popping from stack until
// closing a pair opening bracket is not encountered
        else if(infix[i]==')')
        {
            while(TOP->data!='(')
                postfix += pop();

            pop();
            i++;
        }
        else
        {

            if (infix[i] != ('+')&& infix[i] !=('-') && infix[i] !=('*')&& infix[i] != '/' && infix[i]!='%'
                && infix[i] !='^' )

               return "\n OPPS :(! you entered an invalid operator  \n";

            while (!isEmpty() && priority(infix[i]) <= priority(peek())){
                postfix += pop();
            }
            push(infix[i]);
            i++;
        }
    }
    while(!isEmpty()){
        postfix += pop();
    }

    return postfix ;
}

int main()
{
    char infix[100];
    string postfix;
    int c;
    system("Color 9F");
    do {
    cout << "\t __________________________________________________________\n\t|\t\tEnter your expression to convert\t   |  \n\t|__________________________________________________________| ";
    cout << "\n\t|\t\tPlease use the next operators: \t\t   |\n\t|__________________________________________________________|\n \t|\t^\t|  for exponents\t\t\t   |\n";
    cout << "\t| / and * and % | for division and multiplication and Mod  |\n\t|    - and +\t| for subtraction and addition\t\t   |\n\t|_______________|__________________________________________|\n";
    cout << "\t|\t    (You can use parentheses as well)\t\t   |\n\t|__________________________________________________________|\n\n";
        cin.getline(infix, 100);
           if (infix[0] == '\0') {
               cout << " There is no an expression to convert please enter your expression \n";
           }
        else
        cout << "\n Your expression after convert to Postfix : \n " << INtoPOST(infix)<<endl; //it will print postfix conversion
        cout<<"\n Do you want to try again ? PRESS 1 or 2 \n 1- YES \n 2- NO  \n ";
        cin>>c;
        cin.getline(infix, 100);
        cout << "\n  " << INtoPOST(infix); //it will print postfix conversion
    }
    while (c==1);
    return 0;
}