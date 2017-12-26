// Delbert Harrison
// Program 4
// Sec 001
// Purpose: To build expressions based upon user input
// that are defined by postfix, prefix, and infix

#include <cstdlib>
#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;

bool isValidInfix(string s) // Boolean algebra based up on finding out if the expression is invalid
{
    bool expectnum = true;
    int par = 0;

    vector<string> v;
    while(s.find(' ') != string::npos)//while this is not the last element
    {
        v.push_back(s.substr(0, s.find(' ')));
        s = s.substr(s.find(' ') + 1, s.length());
    }
    v.push_back(s);//add last element

    for(unsigned int i = 0; i < v.size(); i++) // for all elements in the vector less than 2
    {
        if(v[i].length() > 1)
        {
            if(expectnum == false)
            {
                return false;
            }
            for(unsigned int j = 0; j < v[i].length(); j++)
            {
                string temp;
                temp += v[i][j];
                if(strtol(temp.c_str(), NULL, 10) == 0L)
                    return false;


            }

        }
        if(v[i] == "(")
        {
            par++;
            continue;
        }
        else if(v[i] == ")")
        {
            par--;
            if(par < 0)
                return false;
            continue;
        }
        else if(strtol(v[i].c_str(), NULL, 10) != 0L && expectnum == false) // Cases for invalid expressions
            return false;
        else if(strtol(v[i].c_str(), NULL, 10) == 0L && expectnum == true)
            return false;
        else if(v[i] != "+"  && v[i] != "-" && v[i] != "*" && v[i] != "/" && expectnum == false)
            return false;
        expectnum = !expectnum;
    }
        if(par != 0 || expectnum == true)
            return false;

    return true;
}



int main()
{
    string menu ="\n"; // Menu for the user with options
    menu+="***********************************************************\n";
    menu+="SELECTIONS:\n";
    menu+="1. Read an expression\n";
    menu+="2. Display the prefix expression\n";
    menu+="3. Display the infix expression\n";
    menu+="4. Display the postfix expression\n";
    menu+="5. Evaluate the expression using postfix notation\n";
    menu+="6. Exit\n";
    menu+="***********************************************************\n";
    menu+="Select: ";
    cout << menu;
    Tree tree;
    string users_input;
    string expression;
    cin >> users_input;
    bool quit = false; // Gather users input based while repeating the menu
    while(!quit)
    {
        if(users_input == "1") // Gain the expression from the user
        {
            cin.ignore();
            string temp;
            getline(cin, temp);
            if(isValidInfix(temp))
            {
                expression = temp;
                tree.buildTree(expression);
            }
            else
            {
                cout << "Invalid expression!" << endl;
            }
        }
        else if(users_input == "2") // Prefix notation
        {
            if(expression == "") // In case we have no expression
            {
                cout<< "Expression from user input is empty!"<<endl;
            }
            else
            {
                cout<< "Expression from user input: " << expression <<endl;
                cout<< "PREFIX Expression: ";
                tree.prefix();
            }
        }
        else if(users_input == "3") // Infix notation
        {
            if(expression == "")
            {
                cout<< "Expression from user input is empty!"<<endl;
            }
            else
            {
                cout<< "Expression from user input: " << expression <<endl;
                cout<< "INFIX Expression: ";
                tree.infix();
            }
        }
        else if(users_input == "4") // Postfix Notation
        {
            if(expression == "")
            {
                cout<< "Expression from user input is empty!"<<endl;
            }
            else
            {
                cout<< "Expression from user input: " << expression << endl;
                cout<< "POSTFIX Expression: ";
                cout<< tree.postfix();
            }
        }
        else if(users_input == "5") // Sum of the expression using postfix notation
        {
            if(expression == "")
            {
                cout<< "Expression from user input is empty!"<<endl;
            }
            else
            {
                cout<< "Expression from user input: " << expression <<endl;
                cout<< "Evaluated Expression: " << tree.evaluateByPostfix();


            }

        }
        else if (users_input == "6") // Quit the program
        {
            quit = true;
            cout<< "Thank you for using my program! "<<endl;
        }
        else
        {
            cout<< "Please enter a number between 1-6"<<endl;
        }
        if(quit == false)
        {
            cout<< menu;
            cin>> users_input;
        }
    }
    return 0;
}
