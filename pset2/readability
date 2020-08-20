#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int count_letters(string m);
int count_words(string n);
int count_sentences(string o);

int main()
{
    string text;
    text = get_string("Text: ");
    int letters, words, sentences, grade;
    double index;
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    
    double L = ((float)letters / words) * 100;// L= average no of letter per 100 words.
    double S = ((float)sentences / words) * 100;// S= average no. of sentences per 100 words.
    index = 0.0588 * L - 0.296 * S - 15.8;// Formula to create grade.
    grade = round(index);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    
    
}


int count_letters(string m) //Function to count no. of letters.
{
    int count = 0;
    int length = strlen(m);
    for (int i = 0; i < length; i++)
    {
        
        if (m[i] >= 'a' && m[i] <= 'z')
        {
            count++;
        } 
        if (m[i] >= 'A' && m[i] <= 'Z')
        {
            count++;
        }
    }
    return count;
    
}

int count_words(string n) //Function to count no. of words.
{
    int count = 0;
    int length = strlen(n);
    for (int i = 0 ; i < length + 1 ; i++) //Here used length +1 to count the last word when sentence ends.
    {
        if (n[i] == ' ' || n[i] == '\t' || n[i] == '\0')
        {
            count++;
        }
    }
    return count;
    
}

int count_sentences(string o) // Function to count the no. of sentences.
{
    int count = 0;
    int length = strlen(o);
    for (int i = 0; i < length ; i++)
    {
        if (o[i] == '.' || o[i] == '?' || o[i] == '!')
        {
            count++;
        }
    }
    return count;
}
