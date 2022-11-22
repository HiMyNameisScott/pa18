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
void process_infix(std::string& postfix_exp, 
                   Stack<char>& post_operators, 
                   std::string& infix);

///============================================================================
/// MAIN=======================================================================
///============================================================================

int main() {

    char add_to_postfix;        // add to postfix expression                                                                                                                                                                                                                                                                                                                                                                                                                                         
    std::string postfix_exp;    // stores postfix expression
    Stack<char> post_operators; // stack to store operands
    std::string infix;          // stores characters from input
    int count = 0;              // tracks the number of times to iterate loop
    std::string number_of_its;  // stores the number of times to perform process


    std::getline(std::cin, number_of_its);  // grabs number of iterations
    std::cin.ignore();                      // ignores first \n

    while (count < stoi(number_of_its)){
        obtain_data(infix);
        process_infix(postfix_exp, post_operators, infix);
        count ++;
    }

return 0;
}

///============================================================================
/// Function Definitions for pa18==============================================
///============================================================================

/// @brief performs infix to postfix conversion
/// @param postfix_exp accesses string to print postfix
/// @param post_operators access stack to store operators
/// @param text access string of input from file to process
void process_infix(std::string& postfix_exp, 
                Stack<char>& post_operators, 
                std::string& infix){
    for (char ch : infix){     // evaluate each ch in text array
        if (ch >= '0' && ch <= '9'){ // if the char is between 0-9
            postfix_exp.push_back(ch);  // add directly to expression
        } else if (ch == '(') {   // if open parans we can push this to operator stack
            post_operators.push(ch);
        } else if (ch == ')'){          
            while (!post_operators.empty()){ // While the stack is not empty, we can push to expression
                char ch = post_operators.top(); // ch = the top of the stack
                postfix_exp.push_back(ch);   // push to expression
                post_operators.pop();           // pop the top of the stack, repeat until empty
            }
        } else { 
            while ( post_operators.empty() != true && // loop while stack is not empty
                    precedence(ch) <= precedence(post_operators.top()) ){ // if the precedence of the operator is < ****
                        char ch = post_operators.top(); // set char to push
                        postfix_exp.push_back(ch); // push the char to expression
                        post_operators.pop(); // pop char from the stack
            }
        }
        while (!post_operators.empty()){ // No other test cases, add rest
            char ch = post_operators.top();
            postfix_exp.push_back(ch);
            post_operators.pop();
    }
        
    }
    std::cout << postfix_exp << std::endl; // print out the expression
};

/// @brief This will return the precedence of the char operand
/// @param ch taken in to check for precedence
/// @return the precedence of the operand
int precedence(char ch) {
    int num = 0;
     switch(ch){
        case '+': num = 1; break;
        case '-': num = 1; break;
        case '*': num = 2; break;
        case '/': num = 2; break;
        default: num = 0; break;
     } 
     return num;
}


/// @brief pushes data to a string to process for in-->post
/// @param input is a string to process
void obtain_data(std::string& infix){
    char ch_l;
    do {
        std::string line; // create new string
        std::getline(std::cin, line); // get the string
        char ch_l = line[0];  // take the first char for infix
        infix.push_back(ch_l); // push char to infix string
    } while (std::cin.peek() != -1); // loop condition :)
};