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

int updateCharacter(struct *currentCharacter)
{
	//note to self
	//lets move all the sql operations from main.c into this file
	
	//gather characters current stats and update them in the database	
	char * sql_insert[1000]; //need to reduce to the real size in the future -- this is way too big!
	char sql_tmp[] = "INSERT INTO CHARACTERS (WEAPON, HP, ATTACK, MAGIC, XP) \0";
	char sql_tmp2[500];	 

	
	sprintf(sql_tmp2, "VALUES (NULL, '%s', '%d', '%d', '%d', '%d');", currentCharacter->weapon, currentCharacter->hp,
          currentCharacter->attack, currentCharacter->magic, currentCharacter->XP);

	strcpy(sql_insert, sql_tmp);
	strcat(sql_insert, sql_tmp2);


    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if(rc != 0)
    	printf("Character Update has failed!\n");


	//update the db with the latest character stats
}