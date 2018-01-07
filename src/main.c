#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include "characters.c"
#include "commonFunctions.c"
#include "xp_levels.c"
#include "battle.c"

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

static int callback_retrieve(void *data, int argc, char **argv, char **azColName){
//used to assign sleected character data to a character struct, so that a user can continue with a 
//previously started character

  	int i;
   
   fprintf(stderr, "%s: ", (const char*)data);
   
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   
   		struct Character *tempChar = malloc(sizeof(Character));

     	char temp[50];

		strcpy(temp, argv[1]);
   	 	*tempChar->name = temp;

   	 	strcpy(temp, argv[2]);
   	 	*tempChar->race = temp;

   	 	strcpy(temp, argv[3]);
   	 	*tempChar->class = temp;

   	 	strcpy(temp, argv[4]);
   	 	*tempChar->owner = temp;
   	  
		strcpy(temp, argv[5]);
   	 	*tempChar->weapon = temp;

		tempChar->hp = argv[6];
		tempChar->attack = argv[7];
		tempChar->magic = argv[8];
		tempChar->xp = argv[9];

		printf("assignments all good?\n");


   		printf("\n");
		return tempChar;
/*

   	 	int tmp_int;
		
		tmp_int = atoi(argv[6]);
		
		currentCharacter.hp = tmp_int;
		printf("CURRENT HP %d\n", currentCharacter.hp);

		printf("arg 7: %d\n", atoi(argv[7]));


		tmp_int = atoi(argv[7]);

		//line below caises segfault;
		currentCharacter.attack = tmp_int;

		//printf("CURRENT ATTACK %d\n", currentCharacter.attack);

		tmp_int = atoi(argv[8]);
		currentCharacter.attack = tmp_int;
		printf("CURRENT MAGIC %d\n", currentCharacter.magic);

*/   
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
         "MAGIC        INT(50)," \
		 "XP        INT(50));";

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
	printf("XP: %d\n", currentCharacter->xp);

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

    	sprintf(sqlRetreive, "SELECT ID, NAME, RACE, CLASS, OWNER, WEAPON, HP, ATTACK, MAGIC, XP FROM CHARACTERS WHERE ID = %d", id);\
		//printf("SQL Retrive: %s\n", sqlRetreive);   

    	//pull the char record
    	rc = sqlite3_exec(db, sqlRetreive, callback_retrieve, (void*)data, &zErrMsg);

    	if(rc != 0)
    		printf("SQL Retrieval has failed!\n");
 	   	//printf("DID I RETURN?\n");
		printf("Nmae of xdwqd:;:: %s\n", currentCharacter->name);
	}


	printf("Welcome to %s's Realm\n", currentCharacter->name);


	//battle(currentCharacter);

	return 0;
}