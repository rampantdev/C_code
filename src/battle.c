#include "monsters.c"

//file to capture a battle scenario


int battle(struct Character* currentChar, sqlite3 *db)
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

	int startLevel = currentChar->level;
	//batte begins
	if(first_strike == 0){
		printf("%s has first strike advantage!\n", currentChar->name);
		monsterCurrentLife -= currentChar->attack;
	}

	if(first_strike == 1){
		printf("%s has caught %s offguard!\n", currentMonster->name, currentChar->name);
		characterCurrentLife -= currentMonster->attack;
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
		if(currentChar->level > startLevel) {
			currentChar->hp += deriveHP();
			currentChar->attack += deriveAttackPower();
		}
		
		updateCharacter(currentChar, db);

	}

}

