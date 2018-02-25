
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
	int roll = rand() % 4;
	
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
	
	default:
		printf("Homrace selection has failed!\n");
		break;
	}
	return homerace;
}

char *getCityRuler()
{
	
	char *ruler;

	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 7;
	
	
	switch(roll) {
	
	case 0:
		strncpy(ruler, "King\0", 5);
		break;

	case 1:
		strncpy(ruler, "Queen\0", 6);
		break;

	case 2:
		strncpy(ruler, "Princess\0", 9);
		break;

	case 3:
		strncpy(ruler, "Overlord\0", 9);
		break;

	case 4:
		strncpy(ruler, "Warlord\0", 8);
		break;

	case 5:
		strncpy(ruler, "Tyrant\0", 7);
		break;
	
	case 6:
		strncpy(ruler, "None\0", 5);
		break;
	
	default:
		printf("Ruler Selection Has Failed\n");
		break;
	}
	return ruler;
}

char *getCityAffinity()
{
	char *affinity;
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 4;
	
	
	switch(roll) {
	
	case 0:
		strncpy(affinity, "Friendly\0", 9);
		break;

	case 1:
		strncpy(affinity, "Hostile\0", 8);
		break;

	case 2:
		strncpy(affinity, "Neutral\0", 8);
		break;

	case 3:
		strncpy(affinity, "Divine\0", 7);
		break;

	case 4:
		strncpy(affinity, "Merchant\0", 8);
		break;
	
	default:
		printf("Affinity Selection Has Failed\n");
		break;
	}

	return affinity;
}

char *getCityProsperity()
{
	char *prosperity;
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 3;
	
	
	switch(roll) {
	
	case 0:
		strncpy(prosperity, "Wealthy\0", 8);
		break;

	case 1:
		strncpy(prosperity, "Poor\0", 5);
		break;

	case 2:
		strncpy(prosperity, "Neutral\0", 8);
		break;

	case 3:
		strncpy(prosperity, "Impoverished\0", 7);
		break;

	default:
		printf("Prosperity Selection Has Failed\n");
		break;
	}

	return prosperity;
}

char *getCityRegion()
{
	char *region;
	time_t t;
	srand((unsigned) time(&t));
	int roll = rand() % 3;
	
	
	switch(roll) {
	
	case 0:
		strncpy(region, "North\0", 6);
		break;

	case 1:
		strncpy(region, "South\0", 6);
		break;

	case 2:
		strncpy(region, "West\0", 5);
		break;

	case 3:
		strncpy(region, "East\0", 5);
		break;

	default:
		printf("Region Selection Has Failed\n");
		break;
	}

	return region;
}

