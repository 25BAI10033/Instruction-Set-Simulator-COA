#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <string>
using namespace std;

// Function to check operator precedence
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to check if character is an operator
bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to validate the expression
bool isValidExpression(string exp)
{
    stack<char> st;

    for (char ch : exp)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            continue;
        }
        else if (isOperator(ch))
        {
            continue;
        }
        else if (ch == '(')
        {
            st.push(ch);
        }
        else if (ch == ')')
        {
            if (st.empty())
                return false;

            st.pop();
        }
        else
        {
            return false;
        }
    }

    return st.empty();
}

// Function to convert infix to postfix
string infixToPostfix(string exp)
{
    stack<char> st;
    string postfix = "";

    for (char ch : exp)
    {
        // Operand
        if (ch >= 'A' && ch <= 'Z')
        {
            postfix += ch;
        }

        // Opening bracket
        else if (ch == '(')
        {
            st.push(ch);
        }

        // Closing bracket
        else if (ch == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }

            if (!st.empty())
                st.pop();
        }

        // Operator
        else
        {
            while (!st.empty() &&
                   precedence(st.top()) >= precedence(ch))
            {
                postfix += st.top();
                st.pop();
            }

            st.push(ch);
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Function to perform operation
int calculate(int a, int b, char op)
{
    switch(op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}


void generateThreeAddress(string postfix, map<char,int> value)
{
    
    stack<string> st;

    int tempNo = 1;

    map<string,int> tempValue;

    cout<<"\n=====================================\n";
    cout<<"3 ADDRESS CODE\n";
    cout<<"=====================================\n\n";

    for(char ch : postfix)
    {
        if(ch>='A' && ch<='Z')
        {
            string s="";
            s+=ch;
            st.push(s);
        }

        else
        {
            string op2=st.top();
            st.pop();

            string op1=st.top();
            st.pop();

            string temp="T"+to_string(tempNo);

            cout<<temp<<" = "<<op1<<" "<<ch<<" "<<op2<<endl;

            int val1,val2;

            if(op1[0]=='T')
                val1=tempValue[op1];
            else
                val1=value[op1[0]];

            if(op2[0]=='T')
                val2=tempValue[op2];
            else
                val2=value[op2[0]];

            tempValue[temp]=calculate(val1,val2,ch);

            st.push(temp);

            tempNo++;
        }
    }

    cout<<"\nExecution\n";
    cout<<"-----------\n";

    for(int i=1;i<tempNo;i++)
    {
        string t="T"+to_string(i);

        cout<<t<<" = "<<tempValue[t]<<endl;
    }

    cout<<"\nFinal Result = "<<tempValue[st.top()]<<endl;

    cout<<"Instruction Count = "<<tempNo-1<<endl;
}

void generateTwoAddress(string postfix)
{
    stack<string> st;

    int tempNo = 1;

    cout << "\n=====================================\n";
    cout << "2 ADDRESS CODE\n";
    cout << "=====================================\n\n";

    for(char ch : postfix)
    {
        if(ch >= 'A' && ch <= 'Z')
        {
            string s = "";
            s += ch;
            st.push(s);
        }
        else
        {
            string op2 = st.top();
            st.pop();

            string op1 = st.top();
            st.pop();

            string temp = "T" + to_string(tempNo);

            cout << "MOV " << temp << ", " << op1 << endl;

            if(ch == '+')
                cout << "ADD " << temp << ", " << op2 << endl;

            else if(ch == '-')
                cout << "SUB " << temp << ", " << op2 << endl;

            else if(ch == '*')
                cout << "MUL " << temp << ", " << op2 << endl;

            else if(ch == '/')
                cout << "DIV " << temp << ", " << op2 << endl;

            st.push(temp);

            tempNo++;
        }
    }

    cout << "\nInstruction Count = "
         << (tempNo-1)*2
         << endl;
}

void generateOneAddress(string postfix)
{
    stack<string> st;

    int tempNo = 1;

    cout << "\n=====================================\n";
    cout << "1 ADDRESS CODE\n";
    cout << "=====================================\n\n";


    for(char ch : postfix)
    {
        // Operand
        if(ch >= 'A' && ch <= 'Z')
        {
            string s = "";
            s += ch;
            st.push(s);
        }

        // Operator
        else
        {
            string op2 = st.top();
            st.pop();

            string op1 = st.top();
            st.pop();


            // Load first operand into accumulator
            cout << "LOAD " << op1 << endl;


            // Perform operation with second operand
            if(ch == '+')
                cout << "ADD " << op2 << endl;

            else if(ch == '-')
                cout << "SUB " << op2 << endl;

            else if(ch == '*')
                cout << "MUL " << op2 << endl;

            else if(ch == '/')
                cout << "DIV " << op2 << endl;


            // Store intermediate result
            string temp = "T" + to_string(tempNo);

            cout << "STORE " << temp << endl;


            // Push temporary result back
            st.push(temp);

            tempNo++;
        }
    }


    cout << "\nFinal Result stored in ACC\n";

    cout << "Instruction Count = "
         << (tempNo-1)*3
         << endl;
}

void generateZeroAddress(string postfix)
{
    stack<string> st;

    cout << "\n=====================================\n";
    cout << "0 ADDRESS CODE\n";
    cout << "=====================================\n\n";


    int instructionCount = 0;


    for(char ch : postfix)
    {
        // Operand
        if(ch >= 'A' && ch <= 'Z')
        {
            cout << "PUSH " << ch << endl;

            string s = "";
            s += ch;
            st.push(s);

            instructionCount++;
        }


        // Operator
        else
        {
            string op2 = st.top();
            st.pop();

            string op1 = st.top();
            st.pop();


            if(ch == '+')
                cout << "ADD" << endl;

            else if(ch == '-')
                cout << "SUB" << endl;

            else if(ch == '*')
                cout << "MUL" << endl;

            else if(ch == '/')
                cout << "DIV" << endl;


            // Temporary result
            string temp = "T";

            st.push(temp);

            instructionCount++;
        }
    }


    cout << "\nFinal Result is on Stack Top\n";

    cout << "Instruction Count = "
         << instructionCount
         << endl;
}

void comparisonGraph()
{
    int three = 3;
    int two = 6;
    int one = 8;
    int zero = 7;


    cout << "\n=====================================\n";
    cout << "INSTRUCTION FORMAT COMPARISON\n";
    cout << "=====================================\n\n";


    cout << "3 Address : " << three << " instructions\n";
    cout << "2 Address : " << two << " instructions\n";
    cout << "1 Address : " << one << " instructions\n";
    cout << "0 Address : " << zero << " instructions\n";


    cout << "\n\nGRAPH\n";
    cout << "-------------------------------------\n";


    cout << "3 Address : ";
    for(int i=0;i<three;i++)
        cout << "*";
    cout << endl;


    cout << "2 Address : ";
    for(int i=0;i<two;i++)
        cout << "*";
    cout << endl;


    cout << "1 Address : ";
    for(int i=0;i<one;i++)
        cout << "*";
    cout << endl;


    cout << "0 Address : ";
    for(int i=0;i<zero;i++)
        cout << "*";
    cout << endl;


    cout << "-------------------------------------\n";
}



int main()
{
    string expression;

    cout << "=====================================\n";
    cout << " Instruction Set Simulator (Part 1)\n";
    cout << "=====================================\n\n";

    cout << "Enter Infix Expression : ";
    cin >> expression;

    // Validate expression
    if (!isValidExpression(expression))
    {
        cout << "\nInvalid Expression!\n";
        return 0;
    }

    // Convert to postfix
    string postfix = infixToPostfix(expression);

    cout << "\nPostfix Expression : " << postfix << endl;

    // Store operands
    set<char> operands;
    map<char, int> value;

    for (char ch : expression)
    {
        if (ch >= 'A' && ch <= 'Z')
            operands.insert(ch);
    }

    cout << "\nEnter values of operands:\n";

    for (char op : operands)
    {
        cout << op << " = ";
        cin >> value[op];
    }

    cout << "\nOperand Values\n";

    for (auto x : value)
    {
        cout << x.first << " = " << x.second << endl;
    }
   
    generateThreeAddress(postfix, value);
    generateTwoAddress(postfix);
    generateOneAddress(postfix);
    generateZeroAddress(postfix);
    comparisonGraph();
    return 0;
}
//HELLO
//HELLO
//HELLO
