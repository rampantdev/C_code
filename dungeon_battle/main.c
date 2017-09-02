#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include "characters.h"
#include "commonFunctions.h"
#include "xp_levels.h"
#include "battle.h"

//this function used for the sqlite calls, TBH have no idea what it does
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


static int callback_insert(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}


int main() 
{
	int menu;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
		

	struct Character *currentCharacter;

	printf("Choose Character\n");
	//need to retrieve list of character names from sqlitedb

	//re-enable the below scanf for prod
	scanf("%d", &menu); 

		
	rc = sqlite3_open("dungeons.db", &db);

	if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   } else {
      fprintf(stdout, "Opened database successfully\n");
   	}


		sql = "CREATE TABLE IF NOT EXISTS CHARACTERS ("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "NAME           CHAR(50)    NOT NULL," \
         "RACE            CHAR(50)    NOT NULL," \
         "CLASS        CHAR(50)," \
         "OWNER        CHAR(50)," \
         "WEAPON        CHAR(50)," \
         "HP        INT(50)," \
         "ATTACK        INT(50)," \
         "MAGIC        INT(50));";
		
		 rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		 printf("Did the table creation work? %d\n", rc);

	//change this back to menu == 1, this was changed for debugging
	if(menu == 1)
	{ 
	currentCharacter = newchar();	
			//need to pull out the last number we used as a character ID so that we can assign the nex sequential number
		//isn't this built into sql?
	
	printf("Name %s\n", currentCharacter->name);
	printf("Race: %s\n", currentCharacter->race);
	printf("Class: %s\n", currentCharacter->class);
	printf("Owner: %s\n", currentCharacter->owner);
	printf("Weapon: %s\n", currentCharacter->weapon);
	printf("HP: %d\n", currentCharacter->hp);
	printf("Attack: %d\n", currentCharacter->attack);
	printf("Magic: %d\n", currentCharacter->magic);
	

	char * sql_insert[1000];
	char sql_tmp[] = "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER, WEAPON, HP, ATTACK, MAGIC) \0";
	char sql_tmp2[500];	 

	
	sprintf(sql_tmp2, "VALUES (NULL, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic);

	strcpy(sql_insert, sql_tmp);
	strcat(sql_insert, sql_tmp2);


    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    printf("Did the character insert work? %d\n", rc);
//	printf("Did the character insert work?: %d\n", rc);	
	
	}
	
	else 
	{	
		const char* data = "Callback function called";
		//retrieve sqlite record 
		sql = "SELECT ID, NAME, RACE, CLASS, OWNER FROM CHARACTERS";

        rc = sqlite3_exec(db, sql, callback_insert, (void*)data, &zErrMsg);
    	printf("%d\n", rc);

	}
	//else need to pull their character data from sqlite


	printf("Welcome to %s's Realm\n", currentCharacter->name);


	//battle(currentCharacter);

	return 0;
}