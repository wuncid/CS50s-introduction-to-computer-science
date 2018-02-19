#include <stdio.h>
#include <cs50.h>
#include <math.h>

// calculates the minimum number of coins to give user a change
int main(void)
{
    // initializes the counter of coins to 0
    int totalNrOfCoins = 0;
    // declares the current amount of change owed
    int changeStillOwed;

    float change;
    // keeps asking the user for a poisitive number, the amount of change
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // converts the change to cents
    changeStillOwed = (int) round(change * 100);

    // adds the number of quarters to the counter and sets the change still owed to the leftover
    totalNrOfCoins += changeStillOwed / 25;
    changeStillOwed = changeStillOwed % 25;

    // adds the number of dimes to the counter and sets the change still owed to the leftover
    totalNrOfCoins += changeStillOwed / 10;
    changeStillOwed = changeStillOwed % 10;

    // adds the number of nickels to the counter and sets the change still owed to the leftover
    totalNrOfCoins += changeStillOwed / 5;
    changeStillOwed = changeStillOwed % 5;

    // adds the number of pennies to the counter and sets the change still owed to the leftover
    totalNrOfCoins += changeStillOwed / 1;
    changeStillOwed = changeStillOwed % 1;

    // prints out the final number of coins
    printf("%i\n", totalNrOfCoins);
}