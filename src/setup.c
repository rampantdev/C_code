
int createCharTable(sqlite3 *db)
{
//code is duplicated in main right now while we figure out how to make this work
	sqlite3_stmt *statement;
	char *zErrMsg = 0;
	char *sql_insert = "CREATE TABLE IF NOT EXISTS CHARACTERS ("  \
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
	int rc = sqlite3_prepare_v2(db, sql_insert, -1, &statement, NULL);
    rc = sqlite3_step(statement);
    sqlite3_finalize(statement);
}

int createCities(sqlite3 *db)
{

	//this function is called once ever, when a player first plays the game
	//this function sets up ten different cities that a player can journey to and from
	//assumption is made that cities exist in a linear line (ex: you must travel through city 5 6 7 in order to reach city 8)

	//a master list of 100 cities is located in cities.txt
	//take 10 random cities from the list
	//list taken from http://www.dungeoneering.net/d100-list-fantasy-town-names/

	char buf[100];
	int x = 0;
	char ch;
	sqlite3_stmt *statement;

	//need to do one create table call, create a table for cities

	char *sql_insert = "CREATE TABLE IF NOT EXISTS CITIES ("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "NAME           CHAR(50)    NOT NULL," \
         "HOMERACE            CHAR(50)    NOT NULL," \
         "KING        CHAR(50)," \
         "AFFINITY	  CHAR(50)," \
         "PROSPERITY  INT(3)," \
         "REGION        CHAR(50));";

         //code is failing on the line below
	int rc = sqlite3_prepare_v2(db, sql_insert, -1, &statement, NULL);
    	 //executes the sql statement

    rc = sqlite3_step(statement);

    	 //cleans up memory
    sqlite3_finalize(statement);


    //code below is broken

	FILE *fp = fopen("cities.txt", "r");
	if(fp == NULL) {
		printf("ERROR ON FILE OPEN\n");
		return 1;
	}
	
	char * sql_insert[1000];
	char sql_tmp2[500];	 
	char sql_tmp[] = "INSERT INTO CITIES (ID,NAME,HOMERACE,KING,AFFINITY,PROSPERITY, REGION) \0";
		
	while((ch = fgetc(fp)) != EOF)
	{
		printf("x: %d\t %c\n", x, ch);
		
		
		if(ch == '\n' || ch == '\r') { //use '' for character and "" for a string
 			x++;
			buf[x] = '\0';
			//need to add a call to sqlite to write an entry into our cities table for our 10 cities

		
	
		sprintf(sql_tmp2, "VALUES (NULL, '%s', '%s', '%s', '%s', '%s', '%s');", currentCharacter->name, 
			currentCharacter->race,
        	currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->hp,
         	currentCharacter->attack, currentCharacter->magic, currentCharacter->xp);

		strcpy(sql_insert, sql_tmp);
		strcat(sql_insert, sql_tmp2);

	//printf("TESTING : %s\n", sql_insert);


			printf("Our new city is: %s\n", buf);

			x = 0;
			continue;
		}

		
		buf[x] = ch;
		x++;
	}

    fclose(fp);
	return 0;
}





