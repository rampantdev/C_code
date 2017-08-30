//build tiers to derive level from xp

int getLevel(int xp)
{
	int level = 1;

	if(xp > 30)
		level = 1;
	if(xp > 70)
		level = 2;
	if(xp > 100)
		level = 3;
	if(xp > 130)
		level = 4;
	if(xp > 170)
		level = 5;
	if(xp > 230)
		level = 6;
	if(xp > 300)
		level = 7;
	if(xp > 350)
		level = 8;
	if(xp > 450)
		level = 9;
	if(xp > 500)
		level = 10;

	return level;
}