#include <iostream>
#include "Jutsu.h"
#include "Power.h"

using namespace std; 

Jutsu::Jutsu()
{
    oppDamage = 0;
    jname = "";
    oppname = "";
    damage = 0;
    multiplier = 0;
    shadowclone = false;
}
Jutsu::Jutsu(string name, int strength, double value, string opp, int dam)
{
    oppDamage = dam;
    oppname = name;
    jname = name;
    damage = strength;
    multiplier = value;
}
void Jutsu:: setOppJutsuName(string name)
{
    oppname = name;
    return;
}
void Jutsu:: setJutsuName(string name)
{
    jname = name;
    return;
}
void Jutsu :: setJutsuDamage(int strength)
{
    damage = strength;   
    return;
}
void Jutsu :: setOppJutsuDamage(int strength)
{
    oppDamage = strength;   
    return;
}
string Jutsu:: getJutsuName()
{
    return jname; 
}
string Jutsu:: getOppJutsuName()
{
    return oppname; 
}
int Jutsu:: getJutsuDamage()
{
    return damage;
}
int Jutsu:: getOppJutsuDamage()
{
    return oppDamage;
}