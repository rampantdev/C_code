
int attack()
{
	
	time_t t;
	srand((unsigned) time(&t));
	int dmg = rand() % 5;
	
	return dmg;

}

//file to capture a battle scenario

int battle(struct Character* currentChar)
{

int current_dmg;
int characterCurrentLife = currentChar->
int monsterCurrentLife;

	time_t t;
	srand((unsigned) time(&t));
	int first_strike = rand() % 1;
	

int currentMonster = newMonster();

current_dmg = attack;

if(first_strike == 0)
	printf("%s has first strike advantage!", currentChar->name);
			
if(first_strike == 1)
	printf("%s has caught %s offguard!\n", currentMonster->name, currentChar->names);



}

