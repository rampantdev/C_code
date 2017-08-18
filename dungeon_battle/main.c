#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>


struct Character {
	char name[50];
	char race[50];
	char class[50];
	char owner[50];
	char weapon[50];
	int armour;
	int attack;
	int magic;
	int defense;

} Character;


int newmonster()
{
	//need to dynamically generate a new monster 
}

int newlevel()
{
	//dynamically create a new level
	//to do this, we should pull from a database of levels, but only use a level that this character hasn't
	//encountered before
}

int newchar()
{
struct Character *myChar = malloc(sizeof(Character));

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
	//*myChar->race = "Orc";
	char orc[5] = "Orc";

	strcpy(*myChar->race, orc);
	printf("Race: %s\n", orc);
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
		*myChar->race = "Wizard";
		myChar->magic +=2;
	case 2:
		*myChar->race = "Priest";
		myChar->magic +=2;
	case 3:
		*myChar->race = "Warrior";
		myChar->armour +=2;
	case 4:
		*myChar->race = "Archer";
		myChar->attack +=2;
	case 5:
		*myChar->race = "Rogue";
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
printf("The Random Number Generator determined your defense is: %d\n", myChar->attack);

printf("New Character Created: \n");
//printf(*myChar->name);

return myChar;
}



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

//this function used for the sqlite calls, TBH have no idea what it does
static int callback(void *Notused, int argc, char **argv, char **azColName)
	{
		int i;
		for(i=0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}	
		printf("\n");
		return 0;
	}

int main() 
{
	int menu;

	struct Character *currentCharacter;

	printf("Choose Character\n");
	//need to retrieve list of character names from sqlitedb

	//re-enable the below scanf for prod
	//scanf("%d", &menu); 

		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char *sql;
		
		rc = sqlite3_open("dungeons.db", &db);

		if(rc) {
			fprintf(stderr, "%s Can't open database: %s\n", sqlite3_errmsg(db));
			return 0;
		} else {
		fprintf(stdout, "Opened db successfully\n");
		}

	
		sql = ("CREATE TABLE IF NOT EXISTS CHARACTERS ("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "NAME           CHAR(50)    NOT NULL," \
         "RACE            CHAR(50)    NOT NULL," \
         "CLASS        CHAR(50)," \
         "OWNER        CHAR(50)," \
         "WEAPON        CHAR(50)," \
         "ARMOUR        INT(50)," \
         "ATTACK        INT(50)," \
         "MAGIC        INT(50)," \
         "DEFENSE         INT(50) );");

		 rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		 printf("Did the table creation work? %d\n", rc);

	//change this back to menu == 1, this was changed for debugging
	if(menu = 1)
	{ 
	currentCharacter = newchar();	
			//need to pull out the last number we used as a character ID so that we can assign the nex sequential number
		//isn't this built into sql?
	
	/*
	snprintf(sql, 1000, "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, ARMOUR, ATTACK, MAGIC, DEFENSE) "  \
          "VALUES (1, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->armour,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->defense);
	*/

	printf("Name %s\n", currentCharacter->name);
	printf("Race: %ld\n", currentCharacter->race);
	printf("Class: %s\n", currentCharacter->class);
	printf("Owner: %s\n", currentCharacter->owner);
	printf("Weapon: %s\n", currentCharacter->weapon);
	printf("Armour: %s\n", currentCharacter->armour);
	printf("Attack: %s\n", currentCharacter->attack);
	printf("Magic: %s\n", currentCharacter->magic);
	printf("Defense: %s\n", currentCharacter->defense);

/*
		"INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, ARMOUR, ATTACK, MAGIC, DEFENSE) "  \
          "VALUES (1, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->armour,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->defense);
*/

	/*
	sql = ("INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, ARMOUR, ATTACK, MAGIC, DEFENSE) "  \
          "VALUES (1, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", *currentCharacter->name, *currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->armour,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->defense);
	*/

	//printf("SQL INSERT data: %s\n", sql);
	
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	printf("Did the character insert work?: %d\n", rc);	
	
	}
	
	else 
	{	

		//retrieve sqlite record 
		sql = "SELECT FROM CHARACTERS (ID,NAME,RACE,CLASS,OWNER) "  \
          "VALUES (1, '%s', '%s', '%s', '%s');";

	}
	//else need to pull their character data from sqlite

	printf("Welcome to %s's Realm", currentCharacter->name);

	return 0;
}



/*



*/