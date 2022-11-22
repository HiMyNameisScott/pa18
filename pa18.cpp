#include "ForwardList.hpp"
#include <vector>
#include <iostream>

///============================================================================
/// Stack Template=============================================================
///============================================================================

template <class T>
class Stack : protected ForwardList<T> {
public:
    // member types
    using value_type = T;
    using reference  = T&;

    reference top(){ return *ForwardList<T>::begin(); };
    bool empty(){ return ForwardList<T>::empty(); };
    void push(const value_type& value) 
        { ForwardList<T>::insert(ForwardList<T>::begin(), value); };
    void pop(){ ForwardList<T>::erase(ForwardList<T>::begin()); };
};


///============================================================================
/// Fucntion Stubs for pa18====================================================
///============================================================================
int precedence(char ch);
void obtain_data(std::string &infix);
void process_infix(std::string& final, 
                   Stack<char>& stack, 
                   std::string& evaluate);

///============================================================================
/// MAIN=======================================================================
///============================================================================

int main() {

    char add_to_postfix;        //add to postfix expression                                                                                                                                                                                                                                                                                                                                                                                                                                         
    std::string postfix_exp;    //stores postfix expression
    Stack<char> post_operators; //stack to store operands
    std::string infix;          //stores characters from input
    int count = 0;              //tracks the number of times to iterate loop

    std::string number_of_its;
    std::getline(std::cin, number_of_its);
    std::cin.ignore();

    while (count < stoi(number_of_its)){
        obtain_data(infix);
        process_infix(postfix_exp, post_operators, infix);

        count ++;
        }
    std::cout << "infix" << infix << std::endl;
return 0;
}

///============================================================================
/// Function Definitions for pa18==============================================
///============================================================================

/// @brief 
/// @param postfix_exp 
/// @param post_operators 
/// @param text 
void process_infix(std::string& final, 
                Stack<char>& stack, 
                std::string& evaluate){
    for (char ch : evaluate){               // evaluate each ch in text array
        if (ch >= 48 && ch <= 56){      // if the char is between 0-9
            final.push_back(ch);  // add directly to expression
        } else if (ch == '(') {         // if open parans we can push this to operator stack
            stack.push(ch);
        } else if (ch == ')'){          //
            while (!stack.empty()){    // While the stack is not empty, we can push to expression
                char ch = stack.top();        // ch = the top of the stack
                final.push_back(ch);             // push to expression
                stack.pop();                // pop the top of the stack, repeat until empty
            }
        } else { 
            while ( stack.empty() != true &&   // loop while stack is not empty
                    precedence(ch) <= precedence(stack.top()) ){ // if the precedence of the operator is < ****
                        char ch = stack.top(); // set char to push
                        final.push_back(ch);      // push the char to expression
                        stack.pop();            // pop char from the stack
            }
        }
        while (!stack.empty()){    // No other test cases, add rest
            char ch = stack.top();
            final.push_back(ch);
            stack.pop();
    }

        std::cout << final ;           // print out the expression
    }
};

/// @brief This will return the precedence of the char operand
/// @param ch taken in to check for precedence
/// @return the precedence of the operand
int precedence(char ch) {
     switch(ch){
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 2; break;
        default: return 0; break;
     } 
}


/// @brief 
/// @param infix 
void obtain_data(std::string &infix){
    
    while(std::cin.peek() != 10){
        std::string line;
        getline(std::cin, line);
        std::cin.ignore(-1, '\n');
        char ch = line[0];
        infix.push_back(ch);
    }
};