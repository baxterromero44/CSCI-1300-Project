#include <iostream>
#include "Character.h"

using namespace std;

Character::Character() 
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
Character::Character(int h, int o, int s, Power p, Scroll n, Jutsu j, int ssize, int jsize)
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
int Character::getHealth()
{
    return health;
}
int Character::getOppHealth()
{
    return oppHealth;
}
int Character::getStamina()
{
    return stamina;
}
Power Character::getPower()
{
    
    return powerLvl;
}
Scroll Character::getScroll(int index)
{
    return scrolls;
}
Jutsu Character :: getJutsu(int index)
{
    return jutsu;
}
void Character :: setHealth(int h, int dam)
{
    health = h - dam;
}
void Character :: setOppHealth(int o, int damge)
{
    oppHealth = o-damge;
}
void Character :: setStamina(int s)
{
    stamina = s;
}
void Character :: setPower(Power p)
{
    powerLvl = p;
}
void Character :: setScroll(Scroll s, int index)
{
    scrolls = s;
}
void Character :: setJutsu(Jutsu j, int index)
{
    jutsu = j;
}