#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Map.h"
#include "Character.h"
#include <vector>
#include <random>

using namespace std;
/* This function takes a string splits it at every occurrence of a delimiter, and then populates an array of strings with the split pieces up to the provided maximum number of pieces
Parameters: string to be split(string), seperator(char), array(string), size(int)
Return: size
*/

/*
Steps:
Create some variable to store words
Create a variable for the amount of words
Check if an empty string
Search the entire string for the delimter
    If found store the last characters in a string
Find a way to store the last word after the delimiter
If there's only one element then return as the parameters specify
*/
int split(string enter, char sep, string arr[], int size)
{
    string sub = ""; //String used for holding the different words
    int pieces = 0; //How many times the delimiter is present
    int j = enter.length(); 
    if(j == 0) //For an empty string
    {
        return 0;
    }
    
    for (int i = 0; i < j; i++) //Searching through each character of the original string
    {
        if(enter[i] == sep) //For if the delimiter is found
        {
            if (sub.length() > 0) //Preventing error
            {
                arr[pieces++] = sub; //Word is now held in the string
            }
            sub = ""; // For the delimiter
        }
        if(enter[i] != sep) //Continues the function
        {
            sub += enter[i]; // Keeps holding the whole string
        }
    }
    arr[pieces++] = sub; //This is for the last word after the last delimiter to make sure it is stored
    if(pieces == 1) //This is if the delimiter is not used
    {
        arr[0] = enter; //Set the array to the original string
        return 1;
    }
    if(pieces > size) //Prevent the elements of the array from exceeding the size
    {
        return -1;
    }
    
    return size;
}

int main()
{
    //Initializing important variables
    srand(time(NULL));
    Map map;
    Power pwr;
    Character character;
    Scroll scroll;
    Jutsu jutsu[5];
    Jutsu darkJutsu[5];
    Jutsu oppJutsu[5];
    Jutsu oppJutsu1[5];
    int count;
    Jutsu oppJutsu2[5];
    vector<string> avail;
    character.setStamina(100);
    pwr.setPowerLevel(100);
    vector<string> inventory; 
    string playerName;
    int choice;
    int side;
    int damage;
    int playerHealth = 100;
    int oppHealth;
    int random = rand() % 10 + 1;
    double multiplier = 0;
    bool endloop = false;
    bool second = false;
    bool npc = false;
    bool fight = false;
    int sDepletion[5];
    vector<int> stamDepletion;
    int dSDepletion[5];
    vector<int> DarkstamDepletion;
    ifstream jutsuFile, npcFile, jutsuFileDark, npcFileLight;
    ofstream countmoves;
    jutsuFile.open("lightJutsu.txt");
    if(jutsuFile.is_open())
    {
        string line; 
        while(getline(jutsuFile,line))
        {
            string store[8];
            split(line, ',' , store, 8);
            for(int i = 0; i < 4; i++)
            {
                jutsu[i].setJutsuName(store[i]);
            }
            for(int i = 0; i < 4; i++)
            {
                
                jutsu[i].setJutsuDamage(stoi(store[i+4]));
                sDepletion[i] = stoi(store[i+4]);
                
            }
        }
        jutsuFile.close();
    }
    else
    {
        cout << "File failed to open...please try again.";
        return 0;
    }

    
    jutsuFileDark.open("darkJutsu.txt");
    if(jutsuFileDark.is_open())
    {
        string line; 
        while(getline(jutsuFileDark,line))
        {
            string store[8];
            split(line, ',' , store, 8);
            for(int i = 0; i < 4; i++)
            {
                darkJutsu[i].setJutsuName(store[i]);
            }
            for(int i = 0; i < 4; i++)
            {
                
                darkJutsu[i].setJutsuDamage(stoi(store[i+4]));
                dSDepletion[i] = stoi(store[i+4]);
                
            }
        }
        jutsuFileDark.close();
    }
    else
    {
        cout << "File failed to open...please try again.";
        return 0;
    }

    //Printing the menu
    do
    {
        bool endloop = false;
        cout << "Welcome to Shonen Jump!"<< endl << "Enter an input to select an option." << endl;
        cout << "1. Play Now!" << endl << "2. How to Play" << endl << "3. Exit" << endl;
        cin >> choice; 
        
        //Switch statement for selecting options
        switch (choice)
        {
        case 1:
        {  
            
            do
            {
                cout << "Enter your character name:" << endl;
                cin >> playerName; 
                cout << "Welcome " << playerName << "! Choose the light side or the dark side." << endl;
                cout << "1. Light" << endl << "2. Dark" << endl << "3. Quit" << endl << endl; 
                cin >> side;
                string move;
                int strike;
                switch (side)
                {
                /*

                Light Character




















                */
                case 1:

                    npcFileLight.open("lightEnemies.txt");
                    if(npcFileLight.is_open())
                    {
                        string line;
                        getline(npcFileLight, line);
                        string store[6];
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu[i-1].setOppJutsuName(store[i]);
                            oppJutsu[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        character.setOppHealth(stoi(store[5]),0);
                        getline(npcFileLight, line);
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu1[i-1].setOppJutsuName(store[i]);
                            oppJutsu1[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        getline(npcFileLight, line);
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu2[i-1].setOppJutsuName(store[i]);
                            oppJutsu2[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        npcFileLight.close();
                    }
                    avail.push_back(jutsu[0].getJutsuName());
                    avail.push_back(jutsu[1].getJutsuName());
                    stamDepletion.push_back(sDepletion[0]);
                    stamDepletion.push_back(sDepletion[1]);

                    cout << "You have chosen the Light. Head to the Ninja Academy to begin your ninja journey!" << endl << "Before you leave, you notice a scroll laying on the ground. You pick it up and it says The Shadow Clone Scroll. You decide it may be useful in the future and take it on your journey." << endl << endl;
                    scroll.setName("Shadow Clone");
                    inventory.push_back(scroll.getName());
                    //shows the location of the player
                    map.resetMap();
                    map.spawnBestBuy(1,1);
                   
                    do
                    {
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isBestBuyLocation())
                            {
                                cout << "Welcome to the Ninja Academy! It's time to commence your training. My name is Kakashi Hatake and to begin your training you must fight me to obtain your first jutsu!" << endl; 
                                character.setHealth(100, 0);
                                oppHealth = 50; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "3. Rest" << endl;
                                    cout << "4. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Kakashi dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Kakashi attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Kakashi dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Kakashi attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        break;
                                    case 4:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "You have won the battle and in exchange for the Shadow Clone Scroll, Kakashi has gifted you the Shadow Clone jutsu and the Rasengan Scroll. Search for Jiraiya the Toad Sage to obtain the Rasengan!" << endl << endl;
                                        avail.push_back(jutsu[2].getJutsuName());
                                        scroll.setName("Rasengan");
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Kakashi has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                npc = true;
                            }
            
                    }
                    while(!npc);
















                    //After First Battle
                    npc = false;

                    cout << "Now that you have obtained your first jutsu, you must train before being able to unlock the rest. To find Jiraiya, your power level must be at least 150!" << endl << endl << endl; 
                    character.setHealth(100,0);


                    do
                    {
                        if(map.getPlayerColPosition() == 9 || map.getPlayerRowPosition() == 4)
                        {
                            cout << "You have fallen off the map" << endl;
                            return 0;
                        }
                        if(pwr.getPowerLevel() >= 150)
                        {
                            map.spawnHacker(2,5);
                        }
                        count++;
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl << "t (Train)" << endl << "r (Rest)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << endl;
                                }
                                cout << endl;
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "t")
                            {
                                if(character.getStamina()<0)
                                {
                                    cout << "You do not have enough stamina to train please rest first!" << endl; 
                                    break;
                                }
                                cout << "You decided to stop your journey and train for a bit!" << endl;
                                int j = rand() % 6 + 1;
                                if(j == 1)
                                {
                                    cout << "During your training, you got bit my a venmous snake. You lose 10 stamina and do not gain any benefits." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                }
                                else if(j == 2)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 3)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 4)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 5)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 6)
                                {
                                    cout << "During your training, you found inner depths of power you've never discovered before! Your power level has been increased by 25 and your stamina only decreased by 5." << endl;
                                    character.setStamina(character.getStamina() - 5);
                                    pwr.setPowerLevel(25);

                                }
                            }
                            else if(move == "r")
                            {
                                cout << "You decide to rest on your journey...15 stamina has been replenished!" << endl;
                                character.setStamina(character.getStamina() + 15);
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isHackerLocation())
                            {
                                fight = false;
                                cout << "Oh so you finally came to find me huh kid. If you want to learn the Rasengan you must prove yourself worthy!" << endl; 
                                playerHealth = character.getHealth();
                                oppHealth = 100; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "4. Rest" << endl;
                                    cout << "5. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[0].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Jiraiya dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Jiraiya attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Jiraiya dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Jiraiya attacks you with " << oppJutsu1[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[2].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Jiraiya dodged! Shadow Clones only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Shadow Clone Jutsu did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Jiraiya attacks you with " << oppJutsu1[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 4:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 5:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "You have won the battle and Jiraiya has gifted you the Rasengan and the Final Scroll. Search for Sasuke and fight it out who is the strongest shinobi! Be wary, only a shinobi with a power level greater than 200 can locate Sasuke, so get training." << endl << endl;
                                        character.setHealth(100,0);
                                        avail.push_back(jutsu[3].getJutsuName());
                                        scroll.setName("The Final Scroll");
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Jiraiya has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                npc = true;
                            }
            
                    }
                    while(!npc);

















                    npc = false; 
                    
                    do
                    {
                        if(map.getPlayerColPosition() == 9 || map.getPlayerRowPosition() == 4 )
                        {
                            cout << "You have fallen off the map" << endl;
                            return 0;
                        }
                        if(pwr.getPowerLevel() >= 200)
                        {
                            map.spawnHacker2(4,8);
                        }
                        count++;
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl << "t (Train)" << endl << "r (Rest)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << " ";
                                }
                                cout << endl; 
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "t")
                            {
                                if(character.getStamina()<0)
                                {
                                    cout << "You do not have enough stamina to train please rest first!" << endl; 

                                }
                                cout << "You decided to stop your journey and train for a bit!" << endl;
                                int j = rand() % 6 + 1;
                                if(j == 1)
                                {
                                    cout << "During your training, you got bit my a venmous snake. You lose 15 stamina and do not gain any benefits." << endl;
                                    character.setStamina(character.getStamina() - 15);
                                }
                                else if(j == 2)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 3)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 4)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 5)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 6)
                                {
                                    cout << "During your training, you found inner depths of power you've never discovered before! Your power level has been increased by 25 and your stamina only decreased by 5." << endl;
                                    character.setStamina(character.getStamina() - 5);
                                    pwr.setPowerLevel(pwr.getPowerLevel() + 25);

                                }
                            }
                            else if(move == "r")
                            {
                                cout << "You decide to rest on your journey...15 stamina has been replenished!" << endl;
                                character.setStamina(character.getStamina() + 15);
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isHackerLocation2())
                            {
                                fight = false;
                                cout << endl << playerName << "... The time has finally come to prove who is the greatest. I WILL NOT LOSE!" << endl; 
                                character.setHealth(100, 0);
                                playerHealth = character.getHealth();
                                oppHealth = 150; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "5. Rest" << endl;
                                    cout << "6. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[0].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Sasuke dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Sasuke dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[2].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Sasuke dodged! Shadow Clones only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Shadow Clone Jutsu did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 4:
                                         oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[3].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Sasuke dodged! Rasengan only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Rasnegan did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;

                                    case 5:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        cout << "Sasuke attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 6:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "Congratulations! You have defeated Sasuke and proved yourself as the strongest shinobi in the Land of Fire." << endl << endl;
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Sasuke has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                    
                                npc = true;
                            }
            
                    }
                    while(!npc);
                    
                    
                              
                  
                
                    endloop = true;
                    countmoves.open("Leaderboard.txt");
                    countmoves << playerName << "," << count << endl;
                    countmoves.close();
                    cout << "You completed the game in a total of " << count << " moves" << endl;
                    int option;
                    cout << "Select whether you want to see how you compare with other runs or if you want to exit." << endl << "1.Leaderboard" << endl << "2.Quit" << endl;
                    cin >> option;
                    switch (option)
                    {
                    case 1:
                    //Sorting Algorithm
                        break;
                    case 2:
                        cout << "Goodbye! Thanks for playing." << endl;
                        return 0;
                    defualt:
                        cout << "Invalid input. Please try again." << endl;
                        break;
                    }
                    break;

                













                









                //Dark
                case 2:
                    npcFile.open("darkEnemies.txt");
                    if(npcFile.is_open())
                    {
                        string line;
                        getline(npcFile, line);
                        string store[6];
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu[i-1].setOppJutsuName(store[i]);
                            oppJutsu[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        character.setOppHealth(stoi(store[5]),0);
                        getline(npcFile, line);
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu1[i-1].setOppJutsuName(store[i]);
                            oppJutsu1[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        getline(npcFile, line);
                        split(line, ',' , store, 6);
                        for(int i = 1; i < 3; i++)
                        {
                            oppJutsu2[i-1].setOppJutsuName(store[i]);
                            oppJutsu2[i-1].setOppJutsuDamage(stoi(store[i+2]));
                        }
                        npcFile.close();
                    }
                    avail.push_back(darkJutsu[0].getJutsuName());
                    avail.push_back(darkJutsu[1].getJutsuName());
                    stamDepletion.push_back(sDepletion[0]);
                    stamDepletion.push_back(sDepletion[1]);

                    cout << "You have chosen the Dark. Head to the Ninja Academy to begin your ninja journey!" << endl << "Before you leave, you notice a scroll laying on the ground. You pick it up and it says The Chidori Scroll. You decide it may be useful in the future and take it on your journey." << endl << endl;
                    scroll.setName("Chidori Scroll");
                    inventory.push_back(scroll.getName());
                    //shows the location of the player
                    map.resetMap();
                    map.spawnBestBuy(1,1);
                   
                    do
                    {
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isBestBuyLocation())
                            {
                                cout << "Welcome to the Ninja Academy! It's time to commence your training. My name is Kakashi Hatake and to begin your training you must fight me to obtain your first jutsu!" << endl; 
                                character.setHealth(100, 0);
                                oppHealth = 50; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "3. Rest" << endl;
                                    cout << "4. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Kakashi dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Kakashi attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Kakashi dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Kakashi attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        break;
                                    case 4:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "You have won the battle and in exchange for the Fireball Scroll, Kakashi has gifted you the Fireball jutsu and the Chidori Scroll. Search for Orichimaru to obtain the Chidori!" << endl << endl;
                                        avail.push_back(darkJutsu[2].getJutsuName());
                                        scroll.setName("Chidori");
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Kakashi has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                npc = true;
                            }
            
                    }
                    while(!npc);
















                    //After First Battle
                    npc = false;

                    cout << "Now that you have obtained your first jutsu, you must train before being able to unlock the rest. To find Orichimaru, your power level must be at least 150!" << endl << endl << endl; 
                    character.setHealth(100,0);


                    do
                    {
                        if(map.getPlayerColPosition() == 9 || map.getPlayerRowPosition() == 4)
                        {
                            cout << "You have fallen off the map" << endl;
                            return 0;
                        }
                        if(pwr.getPowerLevel() >= 150)
                        {
                            map.spawnHacker(2,5);
                        }
                        count++;
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl << "t (Train)" << endl << "r (Rest)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << endl;
                                }
                                cout << endl;
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "t")
                            {
                                if(character.getStamina()<0)
                                {
                                    cout << "You do not have enough stamina to train please rest first!" << endl; 
                                    break;
                                }
                                cout << "You decided to stop your journey and train for a bit!" << endl;
                                int j = rand() % 6 + 1;
                                if(j == 1)
                                {
                                    cout << "During your training, you got bit my a venmous snake. You lose 10 stamina and do not gain any benefits." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                }
                                else if(j == 2)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 3)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 4)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 5)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 6)
                                {
                                    cout << "During your training, you found inner depths of power you've never discovered before! Your power level has been increased by 25 and your stamina only decreased by 5." << endl;
                                    character.setStamina(character.getStamina() - 5);
                                    pwr.setPowerLevel(25);

                                }
                            }
                            else if(move == "r")
                            {
                                cout << "You decide to rest on your journey...15 stamina has been replenished!" << endl;
                                character.setStamina(character.getStamina() + 15);
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isHackerLocation())
                            {
                                fight = false;
                                cout << "Welcome to my lair " << playerName << ". I've been waiting for you and your vessel!" << endl; 
                                playerHealth = character.getHealth();
                                oppHealth = 100; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "4. Rest" << endl;
                                    cout << "5. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[0].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Orochimaru dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Orochimaru attacks you with " << oppJutsu[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Orochimaru dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Orochimaru attacks you with " << oppJutsu1[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        oppDamage = oppMult * oppJutsu1[opposition].getOppJutsuDamage();
                                        damage = multiplier * darkJutsu[2].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Orochimaru dodged! Fireball only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Fireball Jutsu did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Orochimaru attacks you with " << oppJutsu1[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 4:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        cout << "Orochimaru attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 5:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "You have won the battle and Orochimaru has gifted you the Chidori and the Final Scroll. Search for Naruto and fight it out who is the strongest shinobi! Be wary, only a shinobi with a power level greater than 200 can locate Sasuke, so get training." << endl << endl;
                                        character.setHealth(100,0);
                                        avail.push_back(darkJutsu[3].getJutsuName());
                                        scroll.setName("The Final Scroll");
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Orochimaru has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                npc = true;
                            }
            
                    }
                    while(!npc);

















                    npc = false; 
                    
                    do
                    {
                        if(map.getPlayerColPosition() == 9 || map.getPlayerRowPosition() == 4)
                        {
                            cout << "You have fallen off the map" << endl;
                            return 0;
                        }
                        if(pwr.getPowerLevel() >= 200)
                        {
                            map.spawnHacker2(2,8);
                        }
                        count++;
                        cout << "Stats:" << endl << "Power Level: " << pwr.getPowerLevel() << endl << "Stamina: " << character.getStamina() << endl;
                        map.displayMap();
                        cout << "Your only moves are: " << endl;
                        map.displayMoves();
                        cout << "q (Quit)" << endl << "Please select a move." << endl << endl;
                        cout << "Other options: " << endl << "z (Check Inventory)" << endl <<  "x (See Jutsu)" << endl << "t (Train)" << endl << "r (Rest)" << endl; 
                        cin >> move;
                       
                           //Moving 
                            if(move == "q")
                            {
                                cout << "Goodbye";
                                break;
                            }
                            else if(move == "d")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() + 1);
                            }
                            else if(move == "s")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() + 1);
                            }
                            else if(move == "a")
                            {
                                map.setPlayerColPosition(map.getPlayerColPosition() - 1);
                            }
                            else if(move == "w")
                            {
                                map.setPlayerRowPosition(map.getPlayerRowPosition() - 1);
                            }
                            else if( move == "z")
                            {
                                for(int i = 0; i < inventory.size(); i++)
                                {
                                    cout << inventory[i] << " ";
                                }
                                cout << endl; 
                            }
                            else if(move == "x")
                            {
                                for(int i = 0; i < avail.size(); i++)
                                {
                                    cout << avail[i] << " ";
                                }
                                cout << endl;
                            }
                            else if(move == "t")
                            {
                                if(character.getStamina()<0)
                                {
                                    cout << "You do not have enough stamina to train please rest first!" << endl; 

                                }
                                cout << "You decided to stop your journey and train for a bit!" << endl;
                                int j = rand() % 6 + 1;
                                if(j == 1)
                                {
                                    cout << "During your training, you got bit my a venmous snake. You lose 15 stamina and do not gain any benefits." << endl;
                                    character.setStamina(character.getStamina() - 15);
                                }
                                else if(j == 2)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 3)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 4)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 5)
                                {
                                    cout << "Training went well! Stamina is decreased by 10, but your power level increased by 10." << endl;
                                    character.setStamina(character.getStamina() - 10);
                                    pwr.setPowerLevel(10);
                                }
                                else if(j == 6)
                                {
                                    cout << "During your training, you found inner depths of power you've never discovered before! Your power level has been increased by 25 and your stamina only decreased by 5." << endl;
                                    character.setStamina(character.getStamina() - 5);
                                    pwr.setPowerLevel(pwr.getPowerLevel() + 25);

                                }
                            }
                            else if(move == "r")
                            {
                                cout << "You decide to rest on your journey...15 stamina has been replenished!" << endl;
                                character.setStamina(character.getStamina() + 15);
                            }
                            else 
                            {
                                cout << "Invalid input. Please enter another value." << endl;
                            }
                            if(map.isHackerLocation2())
                            {
                                fight = false;
                                cout << endl << playerName << " ... why would you go in such an evil direction! I CANNOT LET YOU CONTINUE!" << endl; 
                                character.setHealth(100, 0);
                                playerHealth = character.getHealth();
                                oppHealth = 150; 
                                character.setOppHealth(oppHealth,0);
                                do
                                {
                                    random = rand() % 10 + 1;
                                    int opposition = rand() % 2;
                                    int oppRandom = rand() % 10 + 1;
                                    double oppMult;
                                    double oppDamage;
                                    int j = random;
                                    if(j < 3)
                                    {
                                        multiplier = 0.5;
                                    }
                                    else if(j >= 3 && j <= 7)
                                    {
                                        multiplier = 1;
                                    }
                                    else if(j > 7)
                                    {
                                        multiplier = 1.5;
                                    }
                                    if(oppRandom < 4)
                                    {
                                        oppMult = 0.5;
                                    }
                                    else if(oppRandom >= 4 && oppRandom <= 10)
                                    {
                                        oppMult = 1;
                                    }
                                    cout << "Choose an attack: " << endl ;
                                    for(int i = 0; i < avail.size(); i++)
                                    {
                                       cout << i+1 << ". " << avail[i] << endl;
                                    }
                                    
                                    cout << "5. Rest" << endl;
                                    cout << "6. End Battle and Quit" << endl;
                                    cin >> strike;
                                    switch (strike)
                                    {
                                    case 1:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[0].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[0]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Naruto dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Naruto attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 2:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[1].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Naruto dodged! Your attack only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Naruto attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 3:
                                        oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[2].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Naruto dodged! Fireball Jutsu only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Fireball Jutsu did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Naruto attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 4:
                                         oppDamage = oppMult * oppJutsu2[opposition].getOppJutsuDamage();
                                        damage = multiplier * jutsu[3].getJutsuDamage();
                                        if(character.getStamina() >= 10)
                                        {
                                            character.setStamina(character.getStamina()-stamDepletion[1]);
                                        
                                        
                                            if(multiplier < 1)
                                            {
                                            
                                                cout << "Naruto dodged! Chidori only did " << damage << " damage" << endl; 
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier == 1)
                                            {
                                                cout << "You hit him square on! Your attack did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage);
                                                oppHealth = character.getOppHealth();
                                                
                                            }
                                            if(multiplier > 1)
                                            {
                                                cout << "Critical Hit! Your Chidori did " << damage << " damage" << endl;
                                                character.setOppHealth(oppHealth, damage); 
                                                oppHealth = character.getOppHealth(); 
                                                
                                            }
                                        
                                        }
                                        else
                                        {
                                            cout << "You must rest, you do not have enough stamina to use this attack!" << endl;
                                            character.setStamina(character.getStamina() + 10);
                                        }
                                        cout << "Naruto attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;

                                    case 5:
                                        cout << "Your stamina has been rejuvenated by 10 points!" << endl;
                                        character.setStamina(character.getStamina() + 10);
                                        cout << "Naruto attacks you with " << oppJutsu2[opposition].getOppJutsuName() << "! It does " << oppDamage << " damage." << endl;
                                        character.setHealth(playerHealth, oppDamage);
                                        playerHealth = character.getHealth();
                                        break;
                                    case 6:
                                        cout << "You have escaped from the battle...Goodbye!";
                                        return 0;
                                        break;
                                    default:
                                        cout << "Invalid input. Please try again!" << endl; 
                                        break;
                                    }
                                    if(character.getHealth() <= 0)
                                    {
                                        cout << "Sorry you have been defeated. Please try again." << endl;
                                        return 0;
                                    }
                                    if(character.getOppHealth() <= 0)
                                    {
                                        cout << "Congratulations! You have defeated Naruto and proved yourself as the strongest shinobi in the Land of Fire." << endl << endl;
                                        fight = true;
                                    }
                                    else
                                    {
                                        cout << "You have " << character.getHealth() << " health left and Naruto has " << character.getOppHealth() << " health left" << endl << "You have " << character.getStamina() << " stamina left" << endl;
                                    }
                                
                                } 
                                while (!fight);
                                
                                 
                                npc = true;
                            }
            
                    }
                    while(!npc);
                   
                
                    endloop = true;
                    countmoves.open("Leaderboard.txt");
                    countmoves << playerName << "," << count << endl;
                    countmoves.close();
                    int option2; 
                    cout << "You completed the game in a total of " << count << " moves" << endl;
                    cout << "Select whether you want to see how you compare with other runs or if you want to exit." << endl << "1.Leaderboard" << endl << "2.Quit" << endl;
                    cin >> option2;
                    switch (option2)
                    {
                    case 1:
                    //Sorting Algorithm
                        break;
                    case 2:
                        cout << "Goodbye! Thanks for playing." << endl;
                        return 0;
                    }
                    break;
                case 3:
                    cout << "Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid input. Please enter another value." << endl;
                    break;
                }
            } while(!endloop);

            second = true;
        }
            break;
        case 2:
        {
            cout << endl << endl << endl;
            cout << "The goal of this game is to increase your power level and become the most powerful shinobi!" << endl << endl;
            cout << "How to obtain Jutsu: " << endl;
            cout << "Begin your training until your power level is great enough to obtain a scroll" << endl <<  "Then find NPCs to interact with/fight to learn your jutsu" << endl << endl;
            cout <<  "Beat the game by defeating the final enemy and becoming the strongest shinobi!" << endl;
            cout << endl << endl << endl;
        }
            break;
        case 3:
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        default:
            {
                cout << "Invalid input. Enter another value." << endl;
            }
            break;
        } /* code */
    } while (!second);
    
    return 0;
}
