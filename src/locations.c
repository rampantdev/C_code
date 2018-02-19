int location()
{

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 8;
	char location[20];
	printf("location roll: %d\n", roll);
	switch(roll)
	{
		case 0:
			*location = "Foggy Swamp\0";
			break;
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
		default:
			printf("LOCATION FAIL\n");
	}

}
