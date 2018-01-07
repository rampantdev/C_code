int exitGame()
{
	printf("THE GAME IS OVER!!!!!!!!!!!!!!!!!!!\n");
}

int getXP()
{
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 10;

	return roll;	
}

int retrieveCharacter(sqlite3 *db, char *sqlRetreive)
{

struct Character *myChar = malloc(sizeof(Character));


	if(!myChar) {
	return 1;
}

    sqlite3_stmt *stmt;
	int rc = sqlite3_prepare_v2(db, sqlRetreive, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
    	printf("error: ", sqlite3_errmsg(db));
    	return;
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    		
    	char *tmp;
    	int temp;
        temp= sqlite3_column_int (stmt, 0);
 		myChar->id = temp;

    	tmp = sqlite3_column_text(stmt, 1);
    	strncpy(myChar->name, tmp, 6);

    	tmp = sqlite3_column_text(stmt, 2);
    	strncpy(myChar->race, tmp, 6);

    	tmp = sqlite3_column_text(stmt, 3);
    	strncpy(myChar->class, tmp, 6);

    	tmp = sqlite3_column_text(stmt, 4);
    	strncpy(myChar->owner, tmp, 6);

    	tmp = sqlite3_column_text(stmt, 5);
    	strncpy(myChar->weapon, tmp, 6);

        temp= sqlite3_column_int (stmt, 6);
 		myChar->hp = temp;

        temp= sqlite3_column_int (stmt, 7);
 		myChar->attack = temp;

        temp= sqlite3_column_int (stmt, 8);
 		myChar->magic = temp;

        temp= sqlite3_column_int (stmt, 9);
 		myChar->xp = temp;

	}

	if (rc != SQLITE_DONE) {
    	printf("error: ", sqlite3_errmsg(db));
	}
	sqlite3_finalize(stmt);

	return myChar;
}
/* new function, still broken
int updateCharacter(struct *currentCharacter)
{
	//note to self
	//lets move all the sql operations from main.c into this file
	
	//gather characters current stats and update them in the database	
	char * sql_insert[1000]; //need to reduce to the real size in the future -- this is way too big!
	char sql_tmp[] = "INSERT INTO CHARACTERS (WEAPON, HP, ATTACK, MAGIC, XP) \0";
	char sql_tmp2[500];	 

	
	sprintf(sql_tmp2, "VALUES (NULL, '%s', '%d', '%d', '%d', '%d');", currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->xp);

	strcpy(sql_insert, sql_tmp);
	strcat(sql_insert, sql_tmp2);


    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if(rc != 0)
    	printf("Character Update has failed!\n");


	//update the db with the latest character stats
}
*/
