#include "ForwardList.hpp"
#include <vector>
#include <iostream>


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
void obtain_data(std::vector<char> &text){
    char ch;
    
    while(ch != '\n'){
        text.push_back(ch);
        std::cout << ch << std::endl;
        std::cin.get(ch);
        std::cin.ignore(1000, '\n');
    }
};
void process_in(Stack<char> &post_operators, std::vector<char> &text);
int main() {

    char add_to_postfix;        //add to postfix expression                                                                                                                                                                                                                                                                                                                                                                                                                                         
    std::string postfix_exp;    //stores postfix expression
    Stack<char> post_operators; //stack to store operands
    std::vector<char> text;     //vector to store initial input.
    int count = 0;              //tracks the number of times to iterate loop

    char number_of_its = std::cin.get();
    std::cin.ignore(1000, '\n');

    
    std::cout << "before loop" << std::endl;

    std::cout << number_of_its << std::endl;

    while (count < (number_of_its - 48)){
        obtain_data(text);
        for (auto i : text){
            std::cout << i << std::endl;
        }
        std::cout << postfix_exp << std::endl;
        count ++;
        }
    std::cout << number_of_its << std::endl;
    std::cout << "count " << count << std::endl;
return 0;
}


/// @brief 
/// @param postfix_exp 
/// @param post_operators 
/// @param text 
void process_in(std::string &postfix_exp, Stack<char> &post_operators, std::vector<char> &text){
    for (char ch : text){               // evaluate each ch in text array
        if (ch >= 48 && ch <= 56){      // if the char is between 0-9
            postfix_exp.push_back(ch);  // add directly to expression
        } else if (ch == '(') {         // if open parans we can push this to operator stack
            post_operators.push(ch);
        } else if (ch == ')'){          //
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
        while (!post_operators.empty()){    // No other test cases, add rest
            char ch = post_operators.top();
            postfix_exp.push_back(ch);
            post_operators.pop();
    }

        std::cout << postfix_exp;           // print out the expression
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
