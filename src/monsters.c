#include "locations.c"

struct Monster {
	char name[50];
	int hp;
	int attack;
	int magic;
	char type[15];
	char location[15];

} Monster;


char* monsterTypes()
{

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 10;
	char* type = malloc(15);

	switch(roll)
	{
		case 1:
			//*type = "Dragon\0";
			strncpy(type, "Dragon\0", 15);
			break;
		case 2:
			strncpy(type, "Bear\0", 15);
			break;
		case 3:
			strncpy(type, "Zombie\0", 15);
			break;
		case 4:
			strncpy(type, "Dark Wizard\0", 15);
			break;
		case 5:
			strncpy(type, "Ent\0", 15);
			break;
		case 6:
			strncpy(type, "Giant\0", 15);
			break;
		case 7:
			strncpy(type, "Troll\0", 15);
			break;
		case 8:
			strncpy(type, "Ghost\0", 15);
			break;
		case 9:
			strncpy(type, "Werewolf\0", 15);
			break;
		case 10:
			strncpy(type, "Vampire\0", 15);
			break;
		default:
			printf("ERROR MONSTER TYPE FAIL\n");
	}

	return type;
}

struct Monster *newMonster()
{
	struct Monster *newMonster = malloc(sizeof(Monster));
	

	if(!newMonster) {
		printf("New Monster allocation has failed\n");
	}	

	char *type = monsterTypes();	
	strcpy(newMonster->type, type);
	
	char *tmp = location();
	*newMonster->location = tmp;

	//concatenate our monster and location to make it unique
	strcpy(newMonster->name, type);	
	strcat(newMonster->name, " of ");
	strcat(newMonster->name, tmp);

	newMonster->attack = deriveAttackPower();
	newMonster->hp = deriveHP();
	printf("monsta attack: \n", newMonster->attack);
	return newMonster;
}