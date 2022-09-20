#include <iostream>

using namespace std;

class Jutsu
{
    private:
    string jname;
    string oppname;
    int damage;
    double multiplier;
    bool shadowclone;
    int oppDamage;

    public:
    Jutsu();
    Jutsu(string jname, int damage, double multiplier, string opp, int oppDamage);
    void setJutsuName(string jname);
    void setOppJutsuName(string jname);
    string getJutsuName();
    string getOppJutsuName();
    void setJutsuDamage(int damage);
    int getJutsuDamage();
    void setOppJutsuDamage(int damage);
    int getOppJutsuDamage();


};