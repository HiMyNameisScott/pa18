#include "ForwardList.hpp"



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

int precedence(char ch);

int main() {

    char add_to_postfix;
    std::string postfix_exp;
    Stack<char> post_operators;
    auto text = std::string {};

    text = std::cin.get();                  // set text to the cin.get in a string array
        for (char ch : text){               // evaluate each ch in text array
            if (ch >= 48 && ch <= 56){      // if the char is between 0-9
                postfix_exp.push_back(ch);  // add directly to expression
            } else if (ch == '(') {         // if open parans we can push this to operator stack
                post_operators.push(ch);
            } else if (ch == ')'){          // This is a closing of an expression so we know that everything up to this point can
                                            // be pushed to the postfix expression.
                while (!post_operators.empty()){    // While the stack is not empty, we can push to expression
                    char ch = post_operators.top();        // ch = the top of the stack
                    postfix_exp.push_back(ch);             // push to expression
                    post_operators.pop();                // pop the top of the stack, repeat until empty
                }
            } else { 
                while ( post_operators.empty() != true &&   // loop while stack is not empty
                        precedence(ch) <= precedence(post_operators.top()) ){ // if the precedence of the operator is < ****
                            char ch = post_operators.top(); // set char to push
                            postfix_exp.push_back(ch);      // push the char to expression
                            post_operators.pop();            // pop char from the stack
                }
            }

            while (!post_operators.empty()){    // Since no other test cases are met , we will add to expression
                char ch = post_operators.top();
                postfix_exp.push_back(ch);
                post_operators.pop();
            }

            std::cout << postfix_exp;           // print out the expression
        }
    return 0;
}

/// @brief This will return the precedence of the char operand
/// @param ch taken in to check for precedence
/// @return the precedence of the operand
int precedence(char ch) {
     switch(ch){
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
     }
}