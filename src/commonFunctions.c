
int nextEvent(currentCharacter, db)
{
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 2;

	if (roll == 0)
		battle(currentCharacter, db);

	if (roll == 1)
		//visit a city
		visitCity(db);
	if (roll == 2)
		//just walk and get some XP or something 
		walk();
}

int walk() 
{
	return 0;
}

void exitGame()
{
	printf("THE GAME IS OVER!!!!!!!!!!!!!!!!!!!\n");
	return exit(0);
}

int getXP()
{
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 10;

	return roll;	
}



int deriveAttackPower()
{
	time_t t;
	srand((unsigned) time(&t));
	int attack = (rand() % 7) +1;
	
	return attack;
}


int deriveHP()
{
	time_t t;
	srand((unsigned) time(&t));
	int hp = (rand() % 10) +1;
	//printf("THIS IS MY HP AFTER RAND: %d\n", hp);
	return hp;
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

void print_character(struct Character *currentCharacter) 
{
	//function to print all of the stats relating to the currently selected character
	printf("ID %d\n", currentCharacter->id);
	printf("Name %s\n", currentCharacter->name);
	printf("Race: %s\n", currentCharacter->race);
	printf("Class: %s\n", currentCharacter->class);
    printf("Owner: %s\n", currentCharacter->owner);
	printf("Weapon: %s\n", currentCharacter->weapon);
	printf("HP: %d\n", currentCharacter->hp);
	printf("Attack: %d\n", currentCharacter->attack);
	printf("Magic: %d\n", currentCharacter->magic);
	printf("XP: %d\n", currentCharacter->xp);
}

static int callback_tmp(void *NotUsed, int argc, char **argv, char **azColName) {
//put this function here temporarily as the prog wasnt compiling need to refactor this out and use 1 common callback for sqlite in the future

   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


// new function, still broken
int updateCharacter(struct Character *currentCharacter, sqlite3 *db)
{
	printf("did we make it?\n");
	//create a string with all of our current stats
	char * sql_insert[1000]; //need to reduce to the real size in the future -- this is way too big!
	sprintf(sql_insert, "UPDATE CHARACTERS SET WEAPON = '%s', HP = %d, ATTACK = %d, MAGIC = %d, XP = %d where ID = %d\0",
	currentCharacter->weapon, currentCharacter->hp, currentCharacter->attack, currentCharacter->magic, currentCharacter->xp,
	  currentCharacter->id);
	

	sqlite3_stmt *statement;
	//turns our sql statement into byte code
    int retStatus = sqlite3_prepare_v2(db, sql_insert, -1, &statement, NULL);
    
    //executes the sql statement
    int rc = sqlite3_step(statement);

    //cleans up memory
    sqlite3_finalize(statement);
	
}

