#include "monsters.c"

int attack()
{
	//derive attack dmg
	time_t t;
	srand((unsigned) time(&t));
	int dmg = rand() % 5;
	
	return dmg;
}

//file to capture a battle scenario


int battle(struct Character* currentChar)
{
	
	struct Monster *currentMonster;
	currentMonster = newMonster();
	//struct Monster *currentMonster = malloc(sizeof(Monster));

	int gained_xp;
	int current_dmg;
	int characterCurrentLife = currentChar->hp;
	int monsterCurrentLife = currentMonster->hp;

	//determine who strikes first
	time_t t;
	srand((unsigned) time(&t));
	int first_strike = rand() % 2;

	//need to go into monsters and define functions to create monster attack values
	current_dmg = attack;

	if(first_strike == 0){
		printf("%s has first strike advantage!\n", currentChar->name);
		monsterCurrentLife -= current_dmg;
	}

	if(first_strike == 1){
		printf("%s has caught %s offguard!\n", currentMonster->name, currentChar->name);
		characterCurrentLife -= current_dmg;
	}
	
	if(characterCurrentLife < currentChar->hp){
		printf("You've died, game over!\n");
		exitGame();
	}
	
	if(monsterCurrentLife < currentMonster->hp){
		printf("Monster defeated!\n");
		gained_xp = getXP();
		currentChar->xp += gained_xp;	
		currentChar->level = getLevel(currentChar->xp);
	}

}

