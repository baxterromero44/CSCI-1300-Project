#include <iostream>
#include <string>
#include "Scroll.h"
using namespace std;

Scroll::Scroll() : name(""), value(0)
{
}
Scroll::Scroll(string name, int value) : name(name), value(value)
{
}
void Scroll::setName(string n){
    name = n;
}
void Scroll::setValue(int v){
    value = v;
}
string Scroll::getName(){
    return name;
}
int Scroll::getValue(){
    return value;
}
