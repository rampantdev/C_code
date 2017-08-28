#include "locations.h"

struct Monster {
	char name[50];
	int armour;
	int attack;
	int magic;
	int defense;
	char type[15];

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

	printf("Dice Roll for type-gen: %d\n", roll);
	printf("Type in type generator: %s\n", type);
	return type;
}

int newMonster()
{
	struct Monster *newMonster = malloc(sizeof(Monster));
	

	if(!newMonster)
	{
		printf("New Monster allocation has failed\n");
	}	

	char *type = monsterTypes();

	//*newMonster->type = tmp;
	printf("TYPE: %s\n", type);
	
	
	strcpy(newMonster->type, type);
	printf("Monster type: %s\n", newMonster->type);
	
	char tmp[50];
	
/*
	this block of code doesn't work. I don't know why it doesn't give us a location value. 
	Note that locations.h doesn't return a value.. however when we pass location() directly into strcat it works fine
	I don't know why this is -> investigate as time allows

	*tmp = location();
	printf("Location: %s\n", tmp);

*/
	strcpy(newMonster->name, type);
	
	strcat(newMonster->name, " of ");
	strcat(newMonster->name, location());

	//*newMonster->name = tmp;
	printf("Monster name: %s\n", newMonster->name);
	//*newMonster->name = ("%s of %s", type, location()); 

}