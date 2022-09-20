#include <iostream>

using namespace std;

class Power
{
    private:
    int pwrlvl;
    int training;
    
    public:
    Power();
    Power(int pwrlvl , int training);
    void setTraining(int training);
    void setPowerLevel(int training);
    int getPowerLevel();
};