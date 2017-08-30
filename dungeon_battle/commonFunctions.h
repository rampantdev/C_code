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