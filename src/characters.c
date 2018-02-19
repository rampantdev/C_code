struct Character {
	int id;
	char name[20];
	char race[6];
	char class[8];
	char owner[20];
	char weapon[20];
	int hp;
	int attack;
	int magic;
	int xp;
	int level;
	
} Character;


int newchar()
{
struct Character *myChar = malloc(sizeof(Character));


//printf("Size of the struct we malloc'd: %d\n", sizeof(Character));

if(!myChar) {
	return 1;
}


myChar->attack = deriveAttackPower();
printf("The Random Number Generator determined your attack power is: %d\n", myChar->attack);

myChar->hp = deriveHP();
printf("The Random Number Generator determined your defense is: %d\n", myChar->hp);


printf("Which race is your character?\n");
printf("1 - Orc\n");
printf("2 - Elf\n");
printf("3 - Human\n");
printf("4 - Gnome\n");
printf("5 - Dwarf\n");

int tmp;

scanf("%d", &tmp);
printf("tmp %d\n", tmp);

switch(tmp) {
	case 1:
		myChar->hp += 2;
		strncpy(myChar->race, "Orc\0", 6);
		break;

	case 2:
		myChar->magic +=2;
		strncpy(myChar->race, "Elf\0", 6);
		break;

	case 3:
		strncpy(myChar->race, "Human\0", 6);
		break;

	case 4:
		strncpy(myChar->race, "Gnome\0", 6);
		break;

	case 5:
		strncpy(myChar->race, "Dwarf\0", 6);
		break;
}
printf("Which class is your character?\n");
printf("1 - Wizard\n");
printf("2 - Priest\n");
printf("3 - Warrior\n");
printf("4 - Archer\n");
printf("5 - Rogue\n");

int tmp_class;
scanf("%d", &tmp_class);

myChar->hp += 2;
switch(tmp_class) {
	case 1:
		strncpy(myChar->class, "Wizard\0", 8);
		myChar->magic +=2;
		break;

	case 2:
		strncpy(myChar->class, "Priest\0", 8);
		myChar->magic +=2;
		break;

	case 3:
		strncpy(myChar->class, "Warrior\0", 8);
		myChar->hp +=2;
		break;

	case 4:
		strncpy(myChar->class, "Archer\0", 8);
		myChar->attack +=2;
		break;

	case 5:
		strncpy(myChar->class, "Rogue\0", 8);
		myChar->attack +=2;
		break;
}

printf("Enter the name of your char\n");
scanf("%s", myChar->name);


printf("What is your username?\n");
scanf("%s", myChar->owner);

printf("What weapon are you using?\n");
scanf("%s", myChar->weapon);

myChar->xp = 0;
myChar->level = 1; 

printf("New Character Created: \n");

return myChar;
}
