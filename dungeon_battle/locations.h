int location()
{

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 9;
	char location[20];

	switch(roll)
	{
		case 1:
			*location = "Dwarven Outskirts\0";
		case 2:
			*location = "Roaming Wilderness\0";
		case 3:
			*location = "Human City\0";
		case 4:
			*location = "A Dark Cave\0";
		case 5:
			*location = "Hidden Forest\0";
		case 6:
			*location = "Smauldering Volcano\0";
		case 7:
			*location = "Underneath a Bridge\0";
		case 8:
			*location = "Foggy Swamp\0";
	}
}
