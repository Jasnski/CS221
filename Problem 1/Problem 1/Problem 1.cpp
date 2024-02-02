//Jason Siecienski
// cs 221 Homework 2


#include <iostream>
#include <cctype>
#include <string>
#include <map>

using namespace std;

int term_value(map<string, double>& factorVarVals);
int factor_value(map<string, double>& factorVarVals);

/**
   Evaluates the next expression found in cin.
   @return the value of the expression.
*/
int expression_value(map<string, double>& factorVarVals)
{
    int result = term_value(factorVarVals);
    bool more = true;
    while (more)
    {
        char op = cin.peek();
        if (op == '+' || op == '-')
        {
            cin.get();
            int value = term_value(factorVarVals);
            if (op == '+') result = result + value;
            else result = result - value;
        }
        else more = false;
    }
    return result;
}

/**
   Evaluates the next term found in cin.
   @return the value of the term.
*/
int term_value(map<string, double>& factorVarVals)
{
    int result = factor_value(factorVarVals);
    bool more = true;
    while (more)
    {
        char op = cin.peek();
        if (op == '*' || op == '/')
        {
            cin.get();
            int value = factor_value(factorVarVals);
            if (op == '*') result = result * value;
            else result = result / value;
        }
        else more = false;
    }
    return result;
}

/**
   Evaluates the next factor found in cin.
   @return the value of the factor.
*/
int factor_value(map<string, double>& factorVarVals)
{
    int result = 0;
    char c = cin.peek();
    if (c == '(')
    {
        cin.get();
        result = expression_value(factorVarVals);
        cin.get(); // read ")"
    }
    else // Assemble number value from digits
    {
        string factorVar = "";
        while (isalpha(c))
        {
            //cout << "Not a digit" << endl;
            factorVar += c;
            cin.get();
            c = cin.peek();
        }

        //cout << "factorVar: " << factorVar << endl;
        if (factorVarVals.find(factorVar) != factorVarVals.end())
        {
            return factorVarVals[factorVar];
        }
        else if ((factorVar != "") && (factorVarVals.find(factorVar) == factorVarVals.end()))  //If factorVar is not in the factorVarVals map...
        {
            cout << "[Please enter value of " << factorVar << " and close bracket when done: ";
            int factorVal = 0;
            char term = cin.get();
            char c2 = cin.peek();
            while (c2 != ']')
            {
                if (isdigit(c2))
                {
                    factorVal = 10 * factorVal + c2 - '0';
                    cin.get();
                    c2 = cin.peek();
                }
            }
            cin.get();  //pops off the closing bracket
            cin.putback(term);  //pushes the term back onto the cin stack

            factorVarVals.insert({ factorVar, factorVal });

            return factorVal;
        }

        while (isdigit(c))
        {
            result = 10 * result + c - '0';
            cin.get();
            c = cin.peek();
        }
    }
    return result;
}

int main()
{
    cout << "Simple C++ Calculator\n";
    cout << "Enter an arithmetic expression, and the program will evaluate it.\n";
    cout << "Supported operations: +, -, *, /, and parentheses. You can also use variables.\n";
    cout << "Example: 2 * (3 + x) - y\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    map<string, double> factorVarVals;
    cout << "Enter an expression: ";
    cout << expression_value(factorVarVals) << "\n";
    return 0;
}