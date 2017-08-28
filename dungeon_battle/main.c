#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include "monsters.h"
#include "characters.h"

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
		char *sql[1000];
		
		rc = sqlite3_open("dungeons.db", &db);

		if(rc) {
			fprintf(stderr, "%s Can't open database: %s\n", sqlite3_errmsg(db));
			return 0;
		} else {
		fprintf(stdout, "Opened db successfully\n");
		}

	
		*sql = ("CREATE TABLE IF NOT EXISTS CHARACTERS ("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "NAME           CHAR(50)    NOT NULL," \
         "RACE            CHAR(50)    NOT NULL," \
         "CLASS        CHAR(50)," \
         "OWNER        CHAR(50)," \
         "WEAPON        CHAR(50)," \
         "HP        INT(50)," \
         "ATTACK        INT(50)," \
         "MAGIC        INT(50);");

		 rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		 printf("Did the table creation work? %d\n", rc);

	//change this back to menu == 1, this was changed for debugging
	if(menu = 1)
	{ 
	currentCharacter = newchar();	
			//need to pull out the last number we used as a character ID so that we can assign the nex sequential number
		//isn't this built into sql?
	
	/*
	snprintf(sql, 1000, "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, ARMOUR, ATTACK, MAGIC) "  \
          "VALUES (1, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->armour,
          currentCharacter->attack, currentCharacter->magic);
	*/

	printf("Name %s\n", currentCharacter->name);
	printf("Race: %s\n", currentCharacter->race);
	printf("Class: %s\n", currentCharacter->class);
	printf("Owner: %s\n", currentCharacter->owner);
	printf("Weapon: %s\n", currentCharacter->weapon);
	printf("HP: %d\n", currentCharacter->hp);
	printf("Attack: %d\n", currentCharacter->attack);
	printf("Magic: %d\n", currentCharacter->magic);
	


	char sql_tmp[] = "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, HP, ATTACK, MAGIC) \0";
	char sql_tmp2[500];	 

	
	sprintf(sql_tmp2, "VALUES (NULL, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic);

	strcpy(sql, sql_tmp);
	strcat(sql, sql_tmp2);


    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

//	printf("Did the character insert work?: %d\n", rc);	
	
	}
	
	else 
	{	

		//retrieve sqlite record 
		*sql = "SELECT FROM CHARACTERS (ID,NAME,RACE,CLASS,OWNER) "  \
          "VALUES (1, '%s', '%s', '%s', '%s');";

	}
	//else need to pull their character data from sqlite

	int noink = newMonster();

	printf("Welcome to %s's Realm\n", currentCharacter->name);

	return 0;
}


