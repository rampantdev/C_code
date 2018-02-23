
int createCharTable(sqlite3 *db)
{
//code is duplicated in main right now while we figure out how to make this work
		sqlite3_stmt *statement;
		char *zErrMsg = 0;
		char sql_insert = "CREATE TABLE IF NOT EXISTS CHARACTERS ("  \
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
		int retStatus = sqlite3_prepare_v2(db, sql_insert, -1, &statement, NULL);
    	 //executes the sql statement
    	int rc = sqlite3_step(statement);

    	 //cleans up memory
    	sqlite3_finalize(statement);

		printf("Did the table creation work? %d\n", rc);

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
	FILE *fp;
	char ch;
	sqlite3_stmt *statement;

	//need to do one create table call, create a table for cities

	char sql_insert = "CREATE TABLE IF NOT EXISTS CITIES ("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "NAME           CHAR(50)    NOT NULL," \
         "HOMERACE            CHAR(50)    NOT NULL," \
         "KING        CHAR(50)," \
         "AFFINITY	  CHAR(50)," \
         "PROSPERITY  INT(3)," \
         "XP        INT(50));";

         //code is failing on the line below
	int retStatus = sqlite3_prepare_v2(db, sql_insert, -1, &statement, NULL);
    	 //executes the sql statement

    int rc = sqlite3_step(statement);

    	 //cleans up memory
    sqlite3_finalize(statement);

	printf("Did the table creation work? %d\n", rc);
	

	fp = open("cities.txt", "r");
	if(fp == NULL) {
		printf("ERROR ON FILE OPEN\n");
		return 1;
	}

	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == "\n") {
			x++;
			buf[x + 1] = '\0';
			//need to add a call to sqlite to write an entry into our cities table for our 10 cities
			continue;
		}

		buf[x] = ch;
	}


	return 0;
}