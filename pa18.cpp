#include "ForwardList.hpp"


template <class T>
class Stack : protected ForwardList<T> {
public:
    // member types
    using value_type = T;
    using reference  = T&;

    reference top( return ForwardList<T>::*begin() );
    bool empty( return ForwardList<T>::empty() );
    void push(const value_type& value) { ForwardList<T>::insert(begin(), value); };
    void pop(erase.begin());
};

int main() {

    char add_to_postfix;
    std::string postfix_exp;
    Stack<char> post_operators;

    const std::array<char, 4> MATH_OPERANDS =  {'+','-', '*', '/'};


    while (std::cin.get() && !EOF){
        if (std::cin.get() >= 48 && std::cin.get() <= 57){
            postfix_exp.push_back(std::cin.get());
        } else if (std::cin.get() == '(' ){
            post_operators.push(std::cin.get());
        }
    }


    return 0;
}
