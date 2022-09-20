#include <iostream>
#include "Jutsu.h"
#include "Scroll.h"
#include "Power.h"

using namespace std;

class Light
{
public:
Light();
Light(int health, int oppHealth, int stamina, Power powerLvl, Scroll scrolls, Jutsu jutsus, int scrollsSize, int jutsuSize);

int getHealth();
int getStamina();
int getOppHealth();
Power getPower();
Scroll getScroll(int);
Jutsu getJutsu(int);

void setHealth(int, int);
void setOppHealth(int, int);
void setStamina(int);
void setPower(Power power);
void setScroll(Scroll scrolls, int);
void setJutsu(Jutsu jutsu, int);

private:
int health;
int oppHealth;
int stamina;
Power powerLvl;
int scrollsSize;
int jutsuSize;
Scroll scrolls;
Jutsu jutsu;
};