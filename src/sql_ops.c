//this functin is used when a character is first created, and inserts the detail into the sql db
char *buildNewCharString(struct Character *currentCharacter)
{
	char * sql_insert[1000];
	char sql_tmp[] = "INSERT INTO CHARACTERS (ID,NAME,RACE,CLASS,OWNER,WEAPON,HP,ATTACK,MAGIC,XP) \0";
	char sql_tmp2[500];	 

	
sprintf(sql_tmp2, "VALUES (NULL, '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d');", currentCharacter->name, currentCharacter->race,
          currentCharacter->class, currentCharacter->owner, currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->xp);

	strcpy(sql_insert, sql_tmp);
	strcat(sql_insert, sql_tmp2);

	//printf("TESTING : %s\n", sql_insert);

	return sql_insert;
    
}

int getMaxID(sqlite3 *db)
{

		char *sql_id = "SELECT MAX(ID) FROM CHARACTERS;";

		sqlite3_stmt *stmt;
		int rc = sqlite3_prepare_v2(db, sql_id, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
    		printf("error: ", sqlite3_errmsg(db));
    		return 1;
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    		
    		int temp;
        	temp= sqlite3_column_int (stmt, 0);
 			
 			return temp;
		}
}
 		/* although the sql prepare returns the proper ID; it still gives a return value indiciating it failed
 		//need to fix in the future
		if (rc != SQLITE_DONE) {
    			printf("error: %s\n", sqlite3_errmsg(db));
			}
	//	sqlite3_finalize(stmt); //this doesn' work in this context - not sure why
	
	*/
