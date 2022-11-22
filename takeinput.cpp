#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;

string getdata(string &Line, string &stuff){
    int newline_count = 0;
    char ch;
    while (newline_count < 5){
        if (cin.peek() == '\n'){
            newline_count++;
            cin.ignore(-1, '\n');
        } else {
            stuff.push_back(ch);
        }
    }
    cout << "stuff: " << stuff << endl;
    return stuff;
}
int main(){
    string num_its;
    int count = 0;
    string post;

    getline(std::cin, num_its);
    cin.ignore();
    cout << num_its << endl;
    cout << cin.peek() << endl;
    while (cin.peek() != 10){
        string line;
        getline(std::cin, line);
        cin.ignore(-1, '\n');
        char ch = line[0];
        cout << "ch-->" << ch << endl;
        post.push_back(ch);
    }

    cout << post << endl;

    return 0;
}