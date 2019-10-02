// Walk in the Woods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <vector>

class Answers //possible tags that don't directly relate to a move between menu screens
{
public:
	std::string mainAnw;
public:
	std::string posAnws[10];
public:
	int posLength;

public:
	void posSetUp(int length, std::string posText[]) //sets up all possible variations
	{
		posLength = length;
		posAnws->resize(length);
		for (int i = 0; i < length; i++)
		{
			posAnws[i] = posText[i];
		}
	}
};

class Menus //all the possible menus pre-game
{
public: //which menu this is
	int thisRef;
public: //what kind of menu this is
	int type; //0 - menu, 1 - play, 2 - change name, 3 - change pronouns, 4 - exit
public: //what the player types to bring up this menu
	std::string tags[10];
public: //how long the tags array is
	int tagsLength;
public: //the title of this menu, displayed at the top of the screen
	std::string title;
public: //the opts this menu has - ie. 1. Play, 2. Options, etc.
	std::string opt[10];
public: //how many options this menu has
	int optLength;
public: //the text that appears for this menu 
	std::string desc[10];
public: //the length of the above array
	int descLength;
public: //which other menus can be reached from this menu
	Menus *tagged[10];
public: //the length of the above array
	int taggedLength;
public:
	void descSetUp(int length, std::string descText[])  //sets up the descption text of the menus 
	{
		desc->resize(length);
		descLength = length;
		for (int i = 0; i < length; i++) 
		{
			desc[i] = descText[i];
		}
	}

public:
	void optSetUp(int length, std::string optText[])  //sets up which options the menu has
	{
		opt->resize(length);
		optLength = length;
		for (int i = 0; i < length; i++)
		{
			opt[i] = optText[i];
		}
	}


public:
	void tagSetup(int length, std::string tagText[]) //sets up the tags of the menu
	{
		tagsLength = length;
		tags->resize(length);
		for (int i = 0; i < length; i++) 
		{
			tags[i] = tagText[i];
		}
	}

public:
	void taggedSetup(int length, Menus *menus[]) //sets up which menus are tagged and how to reach them
	{
		int x = 0; //current working number of tagged
		//std::list<Menus*> menusList;
		
		for (int i = 0; i < optLength; i++) //the options
		{
			for (int j = 0; j < length; j++) //the menus
			{
				for (int k = 0; k < menus[j]->tagsLength; k++) //the tags
				{
					if (opt[i] == menus[j]->tags[k]) //if the tags match
					{
						tagged[x] = menus[j];
						taggedLength++;
						x++;
						i++;
					}
				}
			}
		}
	}
};

//main game vars
std::string gameTitle = "A Walk In the Woods";

//player vars
std::string playerInput;

//main menus
int prevMenu;
int menuRef;
Menus mainMenu;
Menus optsMenu;
Menus helpMenu;
Menus playMenu; 
Menus nameMenu;
Menus proMenu;
Menus exitMenu;
Menus *allMenus[7]; //must be manually set

//responses
Answers yesAnw;
Answers noAnw;
Answers* allAnw[2];

//flow variables
bool found = false;
bool nameSet = false;
bool genderSet = false;

//player vertiables
std::string playerName;
int playerPro;


//SET UP VOIDS
void MenuSetUp() 
{
	//ANSWERS SETUP
	//answers points
	allAnw[0] = &yesAnw;
	allAnw[1] = &noAnw;

	//yes setup
	allAnw[0]->mainAnw = "yes";
	std::string yesPos[] = { "yes", "go", "start", "begin", "accept", "yep", "yeah" };
	allAnw[0]->posSetUp(7, yesPos);
	//no setup
	allAnw[1]->mainAnw = "no";
	std::string noPos[] = { "no", "nope", "stop", "back", "nop" };
	allAnw[1]->posSetUp(5, noPos);


	//MENU SETUP
	//menu pointers
	allMenus[0] = &mainMenu;
	allMenus[1] = &optsMenu;
	allMenus[2] = &helpMenu;
	allMenus[3] = &playMenu;
	allMenus[4] = &nameMenu;
	allMenus[5] = &proMenu;
	allMenus[6] = &exitMenu;

	//menu titles and desc
	allMenus[0]->title = "Main Menu";
	allMenus[1]->title = "Options";
	allMenus[2]->title = "Help";
	allMenus[3]->title = "";
	allMenus[4]->title = "Change Name";
	allMenus[5]->title = "Change Pronouns";
	allMenus[6]->title = "Exit";

	//main set details
	allMenus[0]->type = 0;
	std::string mainDesc[] = { "1.Play", "2.Options", "3.Help", "4.Exit" };
	allMenus[0]->descSetUp(4, mainDesc);
	std::string mainOpt[] = { "play", "load", "opt", "help", "exit" };
	allMenus[0]->optSetUp(5, mainOpt);
	std::string mainTags[] = { "main menu", "main", "restart", "menu" };
	allMenus[0]->tagSetup(4, mainTags);
	allMenus[0]->thisRef = 0;

	//options set details
	allMenus[1]->type = 0;
	std::string optDesc[] = { "1.Change Name", "2.Change Pronouns" };
	allMenus[1]->descSetUp(2, optDesc);
	std::string optOpt[] = { "name", "pronouns", "clear", "back" };
	allMenus[1]->optSetUp(4, optOpt);
	std::string optTags[] = { "options", "settings", "opt", "2" };
	allMenus[1]->tagSetup(4, optTags);
	allMenus[1]->thisRef = 1;

	//help set details
	allMenus[2]->type = 0;
	std::string helpDesc[] = { "A Walk In the Woods is a text-based game.  Your characters actions and", "movements are determined by what you type into the command prompt.  For", "example, if you type 'forward' or 'walk forward' you will walk forward.  If", "you're ever unsure what to write, typing 'help' will prompt some hints.", "Some commands require a word before the object to work, such as 'inspect", "flower'.",  "Commonly used words are: inspect, take, use" };
	allMenus[2]->descSetUp(7, helpDesc);
	std::string helpOpt[] = { "back" };
	allMenus[2]->optSetUp(1, optOpt);
	std::string helpTags[] = { "help", "3" };
	allMenus[2]->tagSetup(2, helpTags);
	allMenus[2]->thisRef = 2;

	//play set details
	allMenus[3]->type = 1;
	std::string playDesc[] = { "Start New Game?" };
	allMenus[3]->descSetUp(1, playDesc);
	std::string playTags[] = { "1", "play", "start", "start game", "begin" };
	allMenus[3]->tagSetup(5, playTags);
	allMenus[3]->thisRef = 3;

	//change name set details
	allMenus[4]->type = 2;
	allMenus[4]->descLength = 0;
	std::string nameTags[] = { "change name", "name", "1" };
	allMenus[4]->tagSetup(3, nameTags);
	allMenus[4]->thisRef = 4;

	//change pronouns set details
	allMenus[5]->type = 3;
	allMenus[5]->descLength = 0;
	std::string proTags[] = { "change pronouns", "change pronoun", "pronoun", "pronouns", "2" };
	allMenus[5]->tagSetup(5, proTags);
	allMenus[5]->thisRef = 5;

	//exit set details
	allMenus[6]->type = 4;
	std::string exitDesc[] = { "Exit?" };
	allMenus[6]->descSetUp(1, exitDesc);
	std::string exitTags[] = { "4", "exit", "leave", "end", "close" };
	allMenus[6]->tagSetup(5, exitTags);
	allMenus[6]->thisRef = 6;

	//set the tagged, has to be done after everything else is set
	for (int i = 0; i < 7; i++) 
	{
		if ( i < 3) 
		{
			//these three connect to other menus
			allMenus[i]->taggedSetup(7, allMenus);
		}
	}

	//set current menu
	menuRef = 0;
}

std::string AnwsChecker(std::string inputCheck) 
{
	std::string checkedAnswer; //0 - no, 1 - yes

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < allAnw[i]->posLength; j++) 
		{
			size_t tempChecked = allAnw[i]->posAnws[j].find(inputCheck);
			if (tempChecked != std::string::npos)
			{
				checkedAnswer = allAnw[i]->mainAnw;
			}
		}
	}

	return checkedAnswer;
}

void StartPlay() 
{
	if (!nameSet)
	{
		std::cout << "What is your name?" << std::endl << "Command: ";
		std::cin >> playerName;
		nameSet = true;
	}
	if (!genderSet)
	{
		std::cout << "What pronouns do you use?" << std::endl << "1. They/Them" << std::endl << "2. He/Him" << std::endl << "3. She/Her" << std::endl << "Command: ";
		std::cin >> playerInput;
	pronounAgain:
		if (playerInput == "1")
		{
			playerPro = 0;
			genderSet = true;
			goto playEnd;
		}
		if (playerInput == "2")
		{
			playerPro = 1;
			genderSet = true;
			goto playEnd;
		}
		if (playerInput == "3")
		{
			playerPro = 2;
			genderSet = true;
			goto playEnd;
		}
		else
		{
			std::cout << std::endl << "Please enter a number between 1 and 3." << std::endl << "Command: ";
			std::cin >> playerInput;
			goto pronounAgain;
		}
	}

playEnd:
	std::cout << playerName << ", you have reached the end of the menu test.  Type anything to continue." << std::endl << "Command: ";
	std::cin >> playerInput;
}

//GAMEPLAY VOIDS
void RunMenu()
{
menuStart:
	//game title is at the top of all menus
	std::cout << gameTitle << std::endl;
	std::cout << "---------------" << std::endl;
	//read current menu 
	std::cout << allMenus[menuRef]->title << std::endl;

	for (int x = 0; x < allMenus[menuRef]->descLength; x++)
	{
		std::cout << allMenus[menuRef]->desc[x] << std::endl;
	}

	//the following screens are a bit more complicated, so they get their own details
	if (allMenus[menuRef]->thisRef == 4)
	{
		//change name screen
		if (!nameSet)
		{
			std::cout << "You have not yet entered your name." << std::endl;
			std::cout << "What is your name?" << std::endl;
		}
		else
		{
			std::cout << "Your name is set as " << playerName << std::endl;
			std::cout << "Change it?" << std::endl;
		}
	}
	if (allMenus[menuRef]->thisRef == 5)
	{
		//change pronouns screen
		if (!genderSet)
		{
			std::cout << "You have not yet choosen your pronouns." << std::endl;
			std::cout << "Please type in a number: " << std::endl;
			std::cout << "1. They/Them" << std::endl << "2. He/Him" << std::endl << "3. She/Her" << std::endl;
		}
		else
		{
			std::string tempPro;
			switch (playerPro)
			{
			case 0:
				tempPro = "They/Them";
				break;
			case 1:
				tempPro = "He/Him";
				break;
			case 2:
				tempPro = "She/Her";
				break;
			}

			std::cout << "Your pronouns are set as " << tempPro << std::endl;
			std::cout << "Change them?" << std::endl;
		}
	}

	//enter number, this changes the menu
tryAgain:
	std::cout << "Command: ";
	std::cin >> playerInput;
	std::cout << "checking..." << std::endl;

	found = false;
goBack:
	if (playerInput == "back")
	{
		int tempRef;
		tempRef = menuRef;
		menuRef = prevMenu;
		if ((tempRef == 4) || (tempRef == 5)) 
		{
			prevMenu = 0;
		}
		found = true;
		std::cout << std::endl << std::endl << std::endl;
	}
	else {
		int temp = menuRef;
		std::string playerResponse;
		switch (allMenus[temp]->type)
		{
		case 0: //normal menu

			for (int i = 0; i < allMenus[temp]->taggedLength; i++) //all tagged menus
			{
				for (int j = 0; j < allMenus[temp]->tagged[i]->tagsLength; j++) //all tags on menu
				{
					if (!found) //if its already found, ignore this forloop
					{
						std::size_t tempSize = playerInput.find(allMenus[temp]->tagged[i]->tags[j]); //see if the playerInput matches the tag
						if (tempSize != std::string::npos)
						{
							//if yes woohoo, you can move on
							found = true;
							prevMenu = menuRef;
							menuRef = allMenus[prevMenu]->tagged[i]->thisRef;
							std::cout << std::endl << std::endl << std::endl;
						}

					}
				}
			}
			break;
		case 1: //play
			playerResponse = AnwsChecker(playerInput);
			if (playerResponse == "yes")
			{
				goto startPlay;
			}
			if (playerResponse == "no")
			{
				playerInput = "back";
				goto goBack;
			}
			break;
		case 2: //change name
			if (!nameSet)
			{
				playerName = playerInput;
				nameSet = true;
				std::cout << std::endl << std::endl;
				goto menuStart;
			}
			else
			{
				playerResponse = AnwsChecker(playerInput);
				if (playerResponse == "yes")
				{
					std::cout << "What is your name?" << std::endl;
					std::cout << "Command:";
					std::cin >> playerInput;
					playerName = playerInput;
					std::cout << std::endl << std::endl;
					goto menuStart;
				}
				if (playerResponse == "no")
				{
					playerInput = "back";
					goto goBack;
				}
			}
			break;
		case 3: //change pronouns
			if (!genderSet)
			{
				goto pronounCheck;
			}
			else
			{
				playerResponse = AnwsChecker(playerInput);
				if (playerResponse == "yes")
				{
					std::cout << "Please type in a number: " << std::endl;
					std::cout << "1. They/Them" << std::endl << "2. He/Him" << std::endl << "3. She/Her" << std::endl;
					std::cout << "Command:";
					std::cin >> playerInput;
					goto pronounCheck;
				}
				if (playerResponse == "no")
				{
					playerInput = "back";
					goto goBack;
				}
			}

		pronounCheck:
			if (playerInput == "1")
			{
				playerPro = 0;
				genderSet = true;
				std::cout << std::endl << std::endl;
				goto menuStart;
			}
			if (playerInput == "2")
			{
				playerPro = 1;
				genderSet = true;
				std::cout << std::endl << std::endl;
				goto menuStart;
			}
			if (playerInput == "3")
			{
				playerPro = 2;
				genderSet = true;
				std::cout << std::endl << std::endl;
				goto menuStart;
			}
			else
			{
				std::cout << std::endl << "Please enter a number between 1 and 3." << std::endl << "Command: ";
				std::cin >> playerInput;
				goto pronounCheck;
			}
			break;
		case 4: //exit
			playerResponse = AnwsChecker(playerInput);
			if (playerResponse == "yes")
			{
				goto gameExit;
			}
			if (playerResponse == "no")
			{
				playerInput = "back";
				goto goBack;
			}
			break;
		}
	}

	if (found)
	{
		goto menuStart;
	}
	else
	{
		std::cout << "Command not recongized." << std::endl;
		std::cout << std::endl << std::endl;
		goto tryAgain;
	}

startPlay:
	StartPlay();
	//Note: always returns to here.

gameExit:
	//always at the end of the void
	std::cout << "Thanks for playing!";

}

//MENU START
int main()
{
	//set up
	MenuSetUp();

	//game start
	RunMenu();

}
