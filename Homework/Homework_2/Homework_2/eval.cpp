////
////  eval.cpp
////  Homework_2
////
////  Created by Aashman Rastogi on 5/1/23.
////
//

#include <string>
#include <stack>
#include <array>
#include <iostream>
#include <cassert>
using namespace std;

bool isValid(string infix);
void convertToPostfix(string infix, string& postfix);
int precedence(char c);

int evaluate(string infix, string& postfix, bool& result)
{
    if (!isValid(infix))
        return 1;
    convertToPostfix(infix, postfix);
    stack<char> OperandStack;
    char Op1;
    char operand2;
    for (int i = 0 ; i < postfix.size() ; i++)
    {
        char c = postfix.at(i);
        switch (c) {
            case 'T':
            case 'F':
                OperandStack.push(c);
                break;
            case '!':
                operand2 = OperandStack.top();
                OperandStack.pop();
                if (operand2 == 'T')
                {
                    OperandStack.push('F');
                }
                else
                {
                    OperandStack.push('T');
                }
                break;
            case '^':
            case '&':
                operand2 = OperandStack.top();
                OperandStack.pop();
                Op1 = OperandStack.top();
                OperandStack.pop();
                switch (c) {
                    case '^':
                        if ((Op1 == 'T' && operand2 == 'T') || (Op1 == 'F' && operand2 == 'F'))
                        {
                            OperandStack.push('F');
                        }
                        else if ((Op1 == 'F' && operand2 == 'T') || (Op1 == 'T' && operand2 == 'F'))
                        {
                            OperandStack.push('T');
                        }
                        break;
                    case '&':
                        if ((Op1 == 'F' && operand2 == 'T') || (Op1 == 'T' && operand2 == 'F') || (Op1 == 'F' && operand2 == 'F'))
                        {
                            OperandStack.push('F');
                        }
                        else if (Op1 == 'T' && operand2 == 'T')
                        {
                            OperandStack.push('T');
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    if (OperandStack.top() == 'T')
        result = true;
    else
        result = false;
    return 0;
}




bool isValid(string infix)
{
    int OpenBracket = 0;
    int CloseBracket = 0;
    string simpleInfix = "";
    for (int i = 0 ; i < infix.size() ; i++)
    {
        if (infix.at(i) != ' ')
        {
            simpleInfix += infix.at(i);
        }
    }
    if (simpleInfix == "")
        return false;
    
    switch (simpleInfix.at(0))
    {
        case '^':
        case '&':
            return false;
        default:
            break;
    }
    switch (simpleInfix.at(simpleInfix.size() - 1))
    {
        case '^':
        case '&':
        case '!':
        case '(':
            return false;
        default:
            break;
    }
    for (int i = 0; i < simpleInfix.size(); i++)
    {
        char c = simpleInfix.at(i);
        if (c == 'T' || c == 'F')
        {
            if (i + 1 < simpleInfix.size())
            {
                switch (simpleInfix.at(i + 1))
                {
                    case 'T':
                    case 'F':
                    case '(':
                    case '!':
                        return false;
                    default:
                        break;
                }
            }
        }
        else if (c == '(' || c == '!')
        {
            if (c == '(')
                OpenBracket++;
            if(i+1<simpleInfix.size())
            {
                switch (simpleInfix.at(i+1))
                {
                    case '^':
                    case '&':
                    case ')':
                        return false;
                    default:
                        break;
                        
                }
            }
        }
        else if (c == ')')
        {
            CloseBracket++;
            if(i+1<simpleInfix.size())
            {
                switch (simpleInfix.at(i+1))
                {
                    case '(':
                    case 'T':
                    case 'F':
                        return false;
                    default:
                        break;
                        
                }
            }
        }
        else if (c == '&' || c == '^')
        {
            if(i+1<simpleInfix.size())
            {
                switch (simpleInfix.at(i+1))
                {
                    case '&':
                    case '^':
                    case ')':
                        return false;
                    default:
                        break;
                        
                }
            }
            
        }
        else if (c == ' ')
        {
            break;
        }
        else
        {
            return false;
        }
    }
    if (OpenBracket != CloseBracket)
        return false;
    return true;
}

void convertToPostfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> operatorStack;
    char c;
    for (int i = 0 ; i < infix.size() ; i++)
    {
        c = infix.at(i);
        switch (c) {
            case 'T':
            case 'F':
                postfix+=c;
                break;
            case '(':
            case '!':
                operatorStack.push(c);
                break;
            case ')':
                while (operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '&':
            case '^':
                while (!operatorStack.empty() &&
                       operatorStack.top() != '(' &&
                       precedence(c) <= precedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(c);
                break;
        }
    }
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
}

int precedence(char c)
{
    switch (c)
    {
        case '^':
            return 1;
        case '&':
            return 2;
        case '!':
            return 3;
        default:
            return -1;
    }
}


