struct Character {
	char name[20];
	char race[6];
	char class[8];
	char owner[20];
	char weapon[20];
	int armour;
	int attack;
	int magic;
	
} Character;



int deriveAttackPower()
{
	time_t t;
	srand((unsigned) time(&t));
	int attack = rand() % 7;
	
	return attack;
}


int deriveDefensePower()
{
	time_t t;
	srand((unsigned) time(&t));
	int armour = rand() % 7;
	
	return armour;
}

int newchar()
{
struct Character *myChar = malloc(sizeof(Character));


printf("Size of the struct we malloc'd: %d\n", sizeof(Character));

if(!myChar) {
	return 1;
}

printf("Which race is your character?\n");
printf("1 - Orc\n");
printf("2 - Elf\n");
printf("3 - Human\n");
printf("4 - Gnome\n");
printf("5 - Dwarf\n");

int tmp;

scanf("%d", &tmp);
printf("tmp %d\n", tmp);

if(tmp == 1)
{
	*myChar->race = "Orc\0";

	//strcpy(*myChar->race, "Orc");
	printf("Race: %s\n", myChar->race);
} 
/*
switch(tmp) {
	case 1:
		*myChar->race = "Orc";
		myChar->armour += 2;
	case 2:
		*myChar->race = "Elf";
		myChar->magic +=2;
	case 3:
		*myChar->race = "Human";
	case 4:
		*myChar->race = "Gnome";
	case 5:
		*myChar->race = "Dwarf";
}
*/
	
printf("Which class is your character?\n");
printf("1 - Wizard\n");
printf("2 - Priest\n");
printf("3 - Warrior\n");
printf("4 - Archer\n");
printf("5 - Rogue\n");

int tmp_class;
scanf("%d", &tmp_class);

switch(tmp_class) {
	case 1:
		*myChar->race = "Wizard\0";
		myChar->magic +=2;
	case 2:
		*myChar->race = "Priest\0";
		myChar->magic +=2;
	case 3:
		*myChar->race = "Warrior\0";
		myChar->armour +=2;
	case 4:
		*myChar->race = "Archer\0";
		myChar->attack +=2;
	case 5:
		*myChar->race = "Rogue\0";
		myChar->attack +=2;
}

printf("Enter the name of your char\n");
scanf("%s", myChar->name);


printf("What is your username?\n");
scanf("%s", myChar->owner);

printf("What weapon are you using?\n");
scanf("%s", myChar->weapon);


myChar->attack += deriveAttackPower();
printf("The Random Number Generator determined your attack power is: %d\n", myChar->attack);

myChar->armour += deriveDefensePower();
printf("The Random Number Generator determined your defense is: %d\n", myChar->armour);

printf("New Character Created: \n");
//printf(*myChar->name);

return myChar;
}
