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