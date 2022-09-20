#include <iostream>
#include "Light.h"

using namespace std;

Light::Light() 
{
    health = 0;
    oppHealth = 0;
    stamina = 0;
    scrollsSize = 0;
    jutsuSize = 0;
    powerLvl.setPowerLevel(0);
    powerLvl.setTraining(0);
    scrolls.setValue(0);
    scrolls.setName("");
    jutsu.setJutsuName("");
    jutsu.setJutsuDamage(0);
}
Light::Light(int h, int o, int s, Power p, Scroll n, Jutsu j, int ssize, int jsize)
{
    health = h;
    oppHealth = o;
    stamina = s;
    powerLvl = p;
    scrollsSize = ssize;
    jutsuSize = jsize;
    scrolls = n;
    jutsu = j;
}
int Light::getHealth()
{
    return health;
}
int Light::getOppHealth()
{
    return oppHealth;
}
int Light::getStamina()
{
    return stamina;
}
Power Light::getPower()
{
    
    return powerLvl;
}
Scroll Light::getScroll(int index) //we probably need an int index parameter for when we a character has multiple jutsus/scrolls
{
    return scrolls;
}
Jutsu Light :: getJutsu(int index) 
{
    return jutsu;
}
void Light :: setHealth(int h, int dam)
{
    health = h - dam;
}
void Light :: setStamina(int s)
{
    stamina = s;
}
void Light:: setOppHealth(int o, int damge)
{
    oppHealth = o - damge;
}
void Light :: setPower(Power p)
{
    powerLvl = p;
}
void Light :: setScroll(Scroll s, int index)
{
    scrolls = s;
}
void Light :: setJutsu(Jutsu j, int index)
{
    jutsu = j;
}
