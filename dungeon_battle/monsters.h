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
	int roll = rand() % 11;
	char type[15];

	switch(roll)
	{
		case 1:
			//*type = "Dragon\0";
			strncpy(type, "Dragon\0", 15);
		case 2:
			strncpy(type, "Bear\0", 15);
		case 3:
			strncpy(type, "Zombie\0", 15);
		case 4:
			strncpy(type, "Dark Wizard\0", 15);
		case 5:
			strncpy(type, "Ent\0", 15);
		case 6:
			strncpy(type, "Giant\0", 15);
		case 7:
			strncpy(type, "Troll\0", 15);
		case 8:
			strncpy(type, "Ghost\0", 15);
		case 9:
			strncpy(type, "Werewolf\0", 15);
		case 10:
			strncpy(type, "Vampire\0", 15);
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

	
	*newMonster->type = monsterTypes();
	printf("%s", newMonster->type);
	
	char tmp[50];
	sprintf(tmp, "%s of %s", *newMonster->type, location());


	*newMonster->name = tmp;
	printf("Monster name: %s\n", tmp);
	//*newMonster->name = ("%s of %s", type, location()); 

}