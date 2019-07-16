// Test123.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>		//included for cout, cin, endl
#include <algorithm>	//included for the std::max() and std::min functions
#include <time.h>		//included for the time() function
#include <iomanip>      // std::setw

#include "windows.h."	//Included for the Sleep() function
#undef min  //there is a min and max defined in windows.h and we dont want to use those
#undef max


enum Color : unsigned
{
  TextBlack = 30,
  TextRed = 31,
  TextGreen = 32,
  TextYellow = 33,
  TextBlue = 34,
  Textmagenta = 35,
  TextCyan = 36,
  TextWhite = 37,
  BackgroundBlack = 40,
  BackgroundRed = 41,
  BackgroundGreen = 42,
  BackgroundYellow = 43,
  BackgroundBlue = 44,
  BackgroundMagenta = 45,
  BackgroundCyan = 46,
  BackgroundWhite = 47
};

enum Setting : unsigned
{
  reset = 0,  //(everything back to normal)
  boldAndBright = 1,  //(often a brighter shade of the same colour)
  underline = 4,
  inverse = 7,  //(swap foregroundand background colours)
  boldBrightOff = 21,
  underlineOff = 24,
  inverseOff = 27
};


struct Enemy
{
	int health = 10;  //(rand() % 10) + 1; // +1 for range 1-10
	int damage = 1;
	bool IsDead = false;
	std::string name;
};
//test
void ResetText()
{
  std::cout << "\033[0m";
}

//uses ANSI values to change the color of the text
void SetColoredText(Color color, Setting setting = Setting::reset)
{
  char buffer[10];
  std::string colorStr = "\033[";

  _itoa_s(color, buffer, 10, 10);
  colorStr += buffer;
  colorStr += ";";
  _itoa_s(setting, buffer, 10, 10);
  colorStr += buffer;
  colorStr += "m";
  std::cout << colorStr;
}

int main()
{
	bool SuperUsed = false;
	//seed rand with the current time
  srand(time(nullptr));

  //set some constant variables for the size of the arrays
	const int maxPlayers = 50;
	const int maxNames = 111;
	
  //we have an array of booleans of if the name was used so that we do not have duplicate names
	bool usedName[maxNames]{ false };	//sets all the used name booleans to false
	

	//our names in addition to the 100 most popular names in 2014 = 112 names to choose from
  std::string enemyNames[] = 
	{
		"Joe","Shmoe","Floe", "Toe", "Poe", "Moe", "Koe", "Roe", "Boe", "Frank", "Billy Bob JR.", "Billy Bob SR.", "Michael",
		"James","John","Robert","David","William","Mary","Christopher","Richard","Joseph","Daniel","Thomas","Matthew","Jennifer",
		"Charles","Anthony","Patricia","Linda","Mark","Elizabeth","Joshua","Steven","Andrew","Kevin","Brian","Barbara","Jessica",
		"Jason","Susan","Timothy","Paul","Kenneth","Lisa","Ryan","Sarah","Karen","Jeffrey","Donald","Ashley","Eric","Jacob",
		"Nicholas","Jonathan","Ronald","Michelle","Kimberly","Nancy","Justin","Sandra","Amanda","Brandon","Stephanie","Emily",
		"Melissa","Gary","Edward","Stephen","Scott","George","Donna","Jose","Rebecca","Deborah","Laura","Cynthia","Carol",
		"Amy","Margaret","Gregory","Sharon","Larry","Angela","Maria","Alexander","Benjamin","Nicole","Kathleen","Patrick",
		"Samantha","Tyler","Samuel","Betty","Brenda","Pamela","Aaron","Kelly","Heather","Rachel","Adam","Christine","Zachary",
		"Debra","Katherine","Dennis","Nathan","Christina","Julie","Jordan","Kyle","Anna"
	};

	Enemy enemies[maxPlayers];

  SetColoredText(Color::TextRed, Setting::boldAndBright);
  SetColoredText(Color::BackgroundWhite, Setting::boldAndBright);
  std::cout << std::endl <<
    "_________                                                .___  __________                        \n"
    "\\_   ___ \\   ____    _____    _____  _____     ____    __| _/  \\____    /  ____    ____    ____  \n"
    "/    \\  \\/  /  _ \\  /     \\  /     \\ \\__  \\   /    \\  / __ |     /     /  /  _ \\  /    \\ _/ __ \\ \n"
    "\\     \\____(  <_> )|  Y Y  \\|  Y Y  \\ / __ \\_|   |  \\/ /_/ |    /     /_ (  <_> )|   |  \\\\  ___/ \n"
    " \\______  / \\____/ |__|_|  /|__|_|  /(____  /|___|  /\\____ |   /_______ \\ \\____/ |___|  / \\___  >\n"
    "        \\/               \\/       \\/      \\/      \\/      \\/           \\/             \\/      \\/ \n"
    << std::endl;
  ResetText();


	int contestantMax = 0;
  SetColoredText(Color::TextRed, Setting::boldAndBright);
	std::cout << "How Many Contestants do you want to Battle? (50 Max)" << std::endl;
  ResetText();
	std::cin >> contestantMax;

	//stops contestant max from being larger than 100
	contestantMax = std::min(contestantMax, maxPlayers);

	for (unsigned i = 0; i < contestantMax; ++i)
	{
		//sets the name to a random value between 0 and maxNames - 1 
		unsigned name = rand() % maxNames;
		//while the name we want to use is used
    while (usedName[name] == true)
    {
      //find a new name to use
      name = rand() % maxNames;
    }

    //usedName[name] == false down here      
		enemies[i].name = enemyNames[name];
		usedName[name] = true;

	}


  


  for (unsigned i = 0; i < 5; ++i)
  {
    Sleep(200);
    std::cout << ".";
  }
  std::cout << std::endl;
  system("cls");
	//if there are no contestants total then there is no battle
	if (contestantMax == 0)
	{
		//return and dont fight if there is no one to fight
		std::cout << "There no contestants, No Contest" << std::endl;
		return 0;
	}
	//contestant max is not betweel 1 and 50
	int alive = contestantMax;
	std::cout << "There are " << contestantMax << " Contestants Total" << std::endl;
	

  //std::cout << "\033[0;31m red text\033[0m\n";

	if (!SuperUsed)
	{
		int roundNum = 0;
		while (alive > 1)
		{
			//increments round number after printing out the round number
			int defender = rand() % contestantMax; //gets random attacker and defender within the array between 0 -> contestantMax
			int attacker = rand() % contestantMax;

			if (defender != attacker && !enemies[attacker].IsDead && !enemies[defender].IsDead) //if defender is not the attacker and the enemies
			{
        //print out round number and format the header
        //setw sets the width so setw(3) cout << 5; becomes "  5"

				std::cout << "########Round " << std::setw(3) << std::setfill('0') <<roundNum++ << "########" << std::endl;

        //reset the fill characters and width
        std::cout << std::setw(0) << std::setfill(' ');
        //calculate extra damage done in range 1-9
				int extraDamage = rand() % 10;

        //print out attack
				std::cout << enemies[attacker].name << " attacked " << enemies[defender].name << "!" << std::endl;

        //decrement defenders health by attackers damage + extra damage
				enemies[defender].health -= enemies[attacker].damage + extraDamage; 				//decrement defender health by attacker damage

        //print out how much damage was done
        std::cout << enemies[attacker].name << " Did ";

        SetColoredText(Color::TextRed, Setting::boldAndBright);
        std::cout << enemies[attacker].damage + extraDamage;
        ResetText();

        std::cout << " Damage To " << enemies[defender].name << std::endl;
        std::cout << enemies[defender].name << " Has ";
        SetColoredText(Color::TextGreen, Setting::boldAndBright);

        std::cout << std::max(enemies[defender].health, 0);
        ResetText();

        std::cout << " Health left" << std::endl;
				//sets the output health to the max of the health of the defender and 0 so the output looks good
				if (enemies[defender].health <= 0) //if defender health less than or equal to 0
				{
          --alive;
					enemies[defender].IsDead = true; //set defender to dead
				}


			  std::cout << "Contestants Left: " << alive << std::endl; //lower number of alive players
			  //wait at the end of the round if the round is successfull
        std::cout << "#########################" << std::endl << std::endl;
			  Sleep(1000);
			}
		}
		for (unsigned i = 0; i < contestantMax; ++i)
		{
			if (enemies[i].IsDead == false)
				std::cout << std::endl << "The VICTOR IS " << enemies[i].name << std::endl;
		}
	}
}

