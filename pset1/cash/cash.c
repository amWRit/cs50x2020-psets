#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions
#include <math.h>

int get_change(float); // function declaration

int main(void)
{
	float dollars;
	int cents;
	do
	{
		dollars = get_float("Change Owed: \n"); // ask for the height and store in height variable
	}
	while (dollars < 0);  // prompt until height input is freater than 0

	printf("%i\n", get_change(dollars));
}

// takes in dollars value and returns number of coins required in change
// assuming 4 different coins
//  quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
int get_change(float dollars)
{
	int cents = (int)round(dollars * 100);
	int num_coins = 0;
	int factor;
	while (cents != 0)
	{
		//printf("Cents: %i\n", cents);
		// get number of quarters (25¢) if required
		if (cents / 25 > 0)
		{
			factor = cents / 25;
			num_coins += factor;
			cents = cents - 25 * factor;
			//printf("Factor: %i, Coins: %i\n", factor, num_coins);
		}
		// get number of dimes (10¢) if required
		else if (cents / 10 > 0)
		{
			factor = cents / 10;
			num_coins += factor;
			cents = cents - 10 * factor;
			//printf("Factor: %i, Coins: %i\n", factor, num_coins);
		}
		// get number of nickels (5¢) if required
		else if (cents / 5 > 0)
		{
			factor = cents / 5;
			num_coins += factor;
			cents = cents - 5 * factor;
			//printf("Factor: %i, Coins: %i\n", factor, num_coins);
		}
		// get remaining change in pennies (1¢)
		else // 1 cent
		{

			num_coins += cents;
			cents = 0;
			printf("Coins: %i\n", num_coins);
		}
	}
	return num_coins;
}