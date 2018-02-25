
//location() grabs a rndom suffix to assign to our monsters in order to make them unique
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


char *getCityHomeRace()
{
	char *homerace;
	

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 8;
	
	switch(roll) {
	
	case 0:
		strncpy(homerace, "Dwarf\0", 6);
		break;

	case 1:
		strncpy(homerace, "Orc\0", 6);
		break;

	case 2:
		strncpy(homerace, "Elf\0", 6);
		break;

	case 3:
		strncpy(homerace, "Human\0", 6);
		break;

	case 4:
		strncpy(homerace, "Gnome\0", 6);
		break;
	}
	
	return homerace;
}

char *getCityRuler()
{
	char *ruler;

	return ruler;
}

char *getCityAffinity()
{
	char *affinity;

	return affinity;
}

char *getCityProsperity()
{
	char *prosperity;

	return prosperity;
}

char *getCityRegion()
{
	char *region;

	return region;
}

