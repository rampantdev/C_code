#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include "characters.h"
#include "commonFunctions.h"
#include "xp_levels.h"
#include "battle.h"

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

//used to assign sleected character data to a character struct, so that a user can continue with a 
//previously started character
static int callback_retrieve(void *data, int argc, char **argv, char **azColName, 
	struct Character currentCharacter){
  	int i;
   
 	//setup the struct to hold the data we're about to retrieve 
    //struct Character *myChar = malloc(sizeof(Character));
	
   fprintf(stderr, "%s: ", (const char*)data);
   
   //printf("\nMARKER %s\n", myChar->name);
   
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       //sprintf(sqlRetreive, "SELECT ID, NAME, RACE, CLASS, OWNER, WEAPON, HP, ATTACK, MAGIC FROM CHARACTERS WHERE ID = %d", id);\
  
     	char temp[50];

		strcpy(temp, argv[1]);
   	 	*currentCharacter.name = temp;
      
		strcpy(temp, argv[1]);
   	 	*currentCharacter.name = temp;

   	 	strcpy(temp, argv[2]);
   	 	*currentCharacter.race = temp;

   	 	strcpy(temp, argv[3]);
   	 	*currentCharacter.class = temp;

   	 	strcpy(temp, argv[4]);
   	 	*currentCharacter.owner = temp;
   	  
		strcpy(temp, argv[5]);
   	 	*currentCharacter.weapon = temp;

   	 	//segfault starts here
		static int tmp_int;
		tmp_int = atoi(argv[6]);
		
		//currentCharacter.hp = malloc(sizeof(currentCharacter.hp));
		//memcpy(currentCharacter.hp, tmp_int, sizeof(tmp_int));
/*
		strcpy(temp, argv[7]);
   	 	currentCharacter.attack = temp;

		strcpy(temp, argv[8]);
   	 	currentCharacter.magic = temp;
*/
   	 	//printf("YODAWG: %s\n", currentCharacter.name);
   
   printf("\n");
   return tmp_int;
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

    	int id;
    	scanf("%d", &id);

    	//build sql query to retrive selected character	
    	char *sqlRetreive[500];

    	sprintf(sqlRetreive, "SELECT ID, NAME, RACE, CLASS, OWNER, WEAPON, HP, ATTACK, MAGIC FROM CHARACTERS WHERE ID = %d", id);\
		//printf("SQL Retrive: %s\n", sqlRetreive);
    	


   

    	//pull the char record
    	rc = sqlite3_exec(db, sqlRetreive, callback_retrieve, (void*)data, &zErrMsg);

		printf("Nmae of xdwqd:;:: %s\n", currentCharacter->name);
	}


	printf("Welcome to %s's Realm\n", currentCharacter->name);


	//battle(currentCharacter);

	return 0;
}