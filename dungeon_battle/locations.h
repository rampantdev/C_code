int location()
{

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 9;
	char location[20];

	printf("ROLL in locations %d\n", roll);

	switch(roll)
	{
		case 1:
			*location = "Dwarven Outskirts\0";
			break;
		case 2:
			*location = "Roaming Wilderness\0";
			break;
		case 3:
			*location = "Human City\0";
			break;
		case 4:
			*location = "A Dark Cave\0";
			break;
		case 5:
			*location = "Hidden Forest\0";
			break;
		case 6:
			*location = "Smauldering Volcano\0";
			break;
		case 7:
			*location = "Underneath a Bridge\0";
			break;
		case 8:
			*location = "Foggy Swamp\0";
			break;
		default:
			printf("LOCATION FAIL\n");
	}

}
