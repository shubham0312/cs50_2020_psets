#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Read the question first. To understand more clearly use debugger.

int check_lowercase(char txt); // function check lowercase. returns 1 if true and 0 if false.
int check_uppercase(char txt); // function to check uppercase.Returns 1 if true and 0 if false.


int main(int argc, string argv[])
{
    if (argc >= 3 || argv[1] == '\0')
    //If more than 2 argc are input then this condition will be true.If no argument is input after caesar then it will also execute this condition.
    {
        printf("./substitution key\n");
        exit(1);
    }

    string input = argv[1];
    char uppercase[26];
    char lowercase[26];
    int upper, lower;
    int len = strlen(input);
    if (len == 26) // checking if length of the key is 26 or not.
    {
        for (int i = 0 ; i < len ; i++) //loop to check if the key is uppercase or lowercase and loading it to particular array.
        {

            upper = check_uppercase(input[i]);
            lower = check_lowercase(input[i]);
            if (upper == 1) // if true then load upper case with that character.
            {
                uppercase[i] = argv[1][i];
                lowercase[i] = argv[1][i] + 32 ; // adding 32 to convert uppercase to lowercase.
            }
            else if (lower == 1)
            {
                lowercase[i] = argv[1][i];
                uppercase[i] = argv[1][i] - 32 ; // subtracting 32 to convert lowercase to uppercase.
            }
            else
            {
                exit(1); // if not an alphabet then exit.
            }

        }
        for (int i = 0 ; i < 25 ; i++) // loop to check the key if their is no multiple alphabet present in the key.
        {
            for (int j = i + 1 ; j < 26 ; j++)
            {
                if (uppercase[i] == uppercase[j])
                {
                    exit(1);
                }
            }
        }
        string text;
        text = get_string("plaintext: "); // taking input
        string ciphertext = malloc(strlen(text) * sizeof(char)); // using malloc() in stdlib.h to assign memory.
        char alphabet = 'A';
        char alphabet_upper[26], alphabet_lower[26];
        for (int k = 0 ; k < 26 ; k++) //loop to load an array with alphabets from A to Z.
        {
            alphabet_upper[k] = alphabet;
            alphabet++;
        }
        alphabet = 'a';
        for (int k = 0 ; k < 26 ; k++) // Loading an array with a to z.
        {
            alphabet_lower[k] = alphabet;
            alphabet++;
        }
        for (int i = 0; i < strlen(text) ; i++) //loop to convert the plain text to ciphertext.
        {
            upper = check_uppercase(text[i]);  // checking uppercase
            lower = check_lowercase(text[i]); // checking lowercase
            int val = 0;
            if (upper == 1) //if uppercase true
            {
                for (int j = 0; j < 26 ; j++) // loop to search the uppercase character value number present in the key.By equating it with the normal alphabetical series.
                {
                    if (alphabet_upper[j] == text[i]) // searching the value of the inputted char in the string.
                    {
                        val = j; //store that value in j.
                        break;
                    }

                }
                ciphertext[i] = uppercase[val]; // loading plain text converted value to ciphertext.

            }
            if (lower == 1) //if lowercase true
            {
                for (int j = 0; j < 26 ; j++)// loop to search the lowercase character value number present in the key.By equating it with the normal alphabetical series.
                {
                    if (alphabet_lower[j] == text[i]) //searching the value of inputted char in the string.
                    {
                        val = j; //store that value in j.
                        break;

                    }

                }
                ciphertext[i] = lowercase[val];
            }
            if (lower == 0 && upper == 0) // if lowercase function and uppercase function is false which means input is not an alphabet.
            {
                ciphertext[i] = text[i]; //If any other character is inputted then print as it is in the ciphertext.
            }
        }
        printf("ciphertext:%s\n", ciphertext); // print cipher text
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        exit(1);

    }

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

