#include <cs50.h>
#include <stdio.h>
#include <math.h>
                             
int main() // Here in this program we have to tell the user that how much coins he will have to give for giving back the change.
{
    float dollars;
    int coins;
    do
    {
        dollars = get_float("Change owed: ");  // Ask the user how much change is owed
    }
    while (dollars <= 0); // Run this loop until the change owed becomes equal to 0.
    {
        int c = 0; // initially the no. of coins are set to be zero
        int cents = round(dollars * 100); //Here we are rounding off the cents by multiplying with 100 for easy calculations
        while (cents) //while cents cents does not becomes equals to zero this loop will run.
        {
            if (cents >= 25) // if cents is greater than 25 then decrease the cents by 25 and increase one 25 cents coin.
            {
                cents = cents - 25;
                c++;
            }
            else if (cents >= 10) //if cents is greater than 10 then decrease the cents by 10 and increase one 10 cents coin.
            {
                cents = cents - 10;
                c++;
            }
            else if (cents >= 5)  //if cents is greater than 5 then decrease the cents by 5 and increase one 5 cents coin.
            {
                cents = cents - 5;
                c++;
            }
            else if (cents >= 1) //if cents is greater than 1 then decrease the cents by 1 and increase one 1 cents coin.
            {
                cents = cents - 1;
                c++;
            }
            coins = c; 
        }




    }
    printf("%i \n", coins); // print the no. of coins


}
