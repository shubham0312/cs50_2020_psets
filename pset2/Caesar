#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Read the question first.

int check_lowercase(char txt); // function check lowercase. returns 1 if true and 0 if false.
int check_uppercase(char txt); // function to check uppercase.Returns 1 if true and 0 if false.


int main(int argc, string argv[])
{
    if (argc >= 3 || argv[1] == '\0') //If more than 2 argc are input then this condition will be true.If no argument is input after caesar then it will also execute this condition.
    {
        printf("./caesar key\n");
        exit(1);
    }


    string input = argv[1];
    for (int l = 0; l < strlen(input) ; l++) // loop to check if the argument string is a numerical value or any other value.
    {
        if (input[l] >= '0' && input[l] <= '9')
        {
            continue;
        }
        else
        {
            exit(1); //If it is not a numerical value then will exit by giving 1.
        }
    }
    int key;
    key = atoi(argv[1]); //atoi function(stdlib.h) used to convert string or char to an integer.

    string text;
    text = get_string("plaintext: "); // taking input
    char alphabet = 'A';
    char uppercase[26];
    for (int i = 0; i < 26 ; i++) // loop to load A to Z in uppercase array to make the value of A(0) to Z(25) .
    {

        uppercase[i] = alphabet;
        alphabet++;
    }
    alphabet = 'a';
    char lowercase[26];  // loop to load a to z in lowercase array to make the value of a(0) to z(25) .
    for (int j = 0; j < 26 ; j++)
    {

        lowercase[j] = alphabet;
        alphabet++; // incrementing alphabet value and storing it in the array.
    }
    int upper, lower;


    string ciphertext = malloc(strlen(text) * sizeof(char)); // using malloc() in stdlib.h to assign memory.


    for (int i = 0; i < strlen(text) ; i++) //loop to convert the plain text to ciphertext.
    {
        upper = check_uppercase(text[i]);  // checking uppercase
        lower = check_lowercase(text[i]); // checking lowercase
        int val = 0;
        if (upper == 1) //if uppercase true
        {
            for (int j = 0; j < 26 ; j++)
            {
                if (uppercase[j] == text[i]) // searching the value of the inputted char in the string.
                {
                    val = j; //store that value in j.
                    break;
                }

            }
            int number = (val + key) % 26; // caesars algorithm . Here we have first found the number in which the cipher text will be stored after adding the plaintext number with key and then  finding the modulo of 26.
            ciphertext[i] = uppercase[number]; //storing the uppercase in ciphertext by incrementing the the plain text with key.


        }
        if (lower == 1) //if lowercase true
        {
            for (int j = 0; j < 26 ; j++)
            {
                if (lowercase[j] == text[i]) //searching the value of inputted char in the string.
                {
                    val = j; //store that value in j.
                    break;
                }

            }
            int number = (val + key) % 26;
            ciphertext[i] = lowercase[number];// caesars algorithm . Here we have first found the number in which the cipher text will be stored after adding the plaintext number with key and then  finding the modulo of 26.
                                               //storing the uppercase in ciphertext by incrementing the the plain text with key.

        }
        if (lower == 0 && upper == 0) // if lowercase function and uppercase function is false which means input is not an alphabet.
        {
            ciphertext[i] = text[i]; //If any other character is inputted then print as it is in the ciphertext.

        }

    }

    printf("ciphertext:%s\n", ciphertext); // print cipher text


}




int check_lowercase(char txt) // checking lower case
{
    if (txt >= 'a' && txt <= 'z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_uppercase(char txt) // checking uppercase
{
    if (txt >= 'A' && txt <= 'Z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

