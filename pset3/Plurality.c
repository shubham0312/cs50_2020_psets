#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int i, val = 0;
    for (i = 0; i < candidate_count; i++)
    {
        int len1 = strlen(candidates[i].name);
        int len2 = strlen(name);
        string name_candidate = candidates[i].name;
        if (len1 == len2)
        {
        for (int j = 0; j < len1; j++)
        {
            if (name[j] == name_candidate[j])
            {
                val = i;
                if (j == (len1 - 1))
                {
                    candidates[val].votes += 1;
                    return true;
                }

            }
            else
            {
                break;
            }

        }

        }
        else
        {
            continue;
        }


    }
    return false;


}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int i = 0, val, temp;
    for (int j = 1; j < candidate_count; j++)
    {
        if (candidates[i].votes > candidates[j].votes)
        {
            val = i;
        }
        else
        {
            val = j;
            i = i + 1;
        }
    }
    for (int m = 0; m < candidate_count; m++)
    {

        if (val != m)
        {
            if (candidates[val].votes == candidates[m].votes)
            {
                temp = m;
                printf("%s\n", candidates[temp].name);
            }
        }
        else
        {
            continue;
        }

    }
    printf("%s\n", candidates[val].name);
}
