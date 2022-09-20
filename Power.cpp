#include <iostream>
#include "Power.h"

using namespace std;

Power::Power()
{
    pwrlvl = 0;
    training = 0; 
}
Power::Power(int power, int train)
{
    pwrlvl = power;
    training = train;
}
void Power :: setTraining(int train)
{
    training = train;
    return;
}
void Power :: setPowerLevel(int train)
{
    pwrlvl = pwrlvl + train;
    return;
}
int Power :: getPowerLevel()
{
    return pwrlvl;
}