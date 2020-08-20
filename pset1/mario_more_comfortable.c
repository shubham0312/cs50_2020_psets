#include <cs50.h>
#include <stdio.h>

//Function prototype
void print(char c, int n);

int main(void)
{
    int height;
    do
    {
        //Getting the height from the user
       height = get_int("Height: ");
    } //Condition for not accepting the height given by the user
    while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        print(' ', height - i - 1);
        print('#', i + 1);
        print(' ', 2);
        print('#', i + 1);
        printf("\n");
    }

}

// funtion to print the pyramid
void print(char c, int n)
{
    // loop to print the number of times the given character
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}
