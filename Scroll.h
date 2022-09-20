
#include <iostream>
#include <string>
using namespace std;


class Scroll
{
    private:
    string name;
    int value;

    public:
    Scroll();
    Scroll(string name, int value);

    string getName();
    int getValue();

    void setName(string);
    void setValue(int);

    
};

