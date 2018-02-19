#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include "characters.c"
#include "commonFunctions.c"
#include "xp_levels.c"
#include "battle.c"
#include "cities.c"
#include "setup.c"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
//used to insert newly created characters into the db
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


static int callback_insert(void *data, int argc, char **argv, char **azColName){
//used for initial character creation and also used to retrive char list of stored characters so that a user can choose which char
//to resume playing when logging back in
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

	
	printf("1: Create Character\n2: Retrieve Existing Character");

	//printf("Choose Character\n");
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
         "MAGIC        INT(50)," \
		 "XP        INT(50));";

		 rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		 printf("Did the table creation work? %d\n", rc);

	//performs initializtion to ensure we have 
	//createCities(db);

	//change this back to menu == 1, this was changed for debugging
	if(menu == 1)
	{ 
	currentCharacter = newchar();	
	
	char * sql_insert[1000];
	char sql_tmp[] = "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER,WEAPON,HP,ATTACK,MAGIC,XP) \0";
	char sql_tmp2[500];	 

	
sprintf(sql_tmp2, "VALUES (NULL, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->xp);

	strcpy(sql_insert, sql_tmp);
	strcat(sql_insert, sql_tmp2);

	//printf("TESTING : %s\n", sql_insert);

    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    
    if(rc != 0)
    	printf("Character creation has failed!\n");
	
			//need to pull out the last number we used as a character ID so that we can assign the nex sequential number
		//isn't this built into sql?
	
	

		char *sql_id = "SELECT MAX(ID) FROM CHARACTERS;";

		sqlite3_stmt *stmt;
		rc = sqlite3_prepare_v2(db, sql_id, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
    		printf("error: ", sqlite3_errmsg(db));
    		return;
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    		
    		int temp;
        	temp= sqlite3_column_int (stmt, 0);
 			
 			currentCharacter->id = temp;

 		/* although the sql prepare returns the proper ID; it still gives a return value indiciating it failed
 		//need to fix in the future
		if (rc != SQLITE_DONE) {
    			printf("error: %s\n", sqlite3_errmsg(db));
			}
	//	sqlite3_finalize(stmt); //this doesn' work in this context - not sure why
	
	*/
		}
	
	}

		
	else 
		//user has chosen to resume playing an already created character
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

    	sprintf(sqlRetreive, "SELECT ID, NAME, RACE, CLASS, OWNER, WEAPON, HP, ATTACK, MAGIC, XP FROM CHARACTERS WHERE ID = %d", id);\

    	currentCharacter = retrieveCharacter(db, sqlRetreive);	
}	
	
	
	print_character(currentCharacter);
	printf("Welcome to %s's Realm\n", currentCharacter->name);


	int go = 1;
	while(go) {
	
	//triggers progression in the game; either continue walking, battle, or visit a city
	nextEvent(currentCharacter, db);

	printf("Continue Adventure? \n 1 - Yes \t 0 - No\n");
	scanf("%d", &go);
	//need to verify either 1 or 0 was entered and prevent bad input
	}

	return 0;
}


