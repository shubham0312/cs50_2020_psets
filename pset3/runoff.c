#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int i;            
    for (i = 0; i < candidate_count; i++) // loop to check the name of the candidate if the name entered while voting is correct or not.
    {
        if (strcmp(candidates[i].name, name) == 0) // comparing string if they match then store the preferences of the voter and also store the value in which that name is stored in struct. 
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
    
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int candidate_number; // This integer is used to store the value of the order in which the particular name of the candidate is stored in the struct.
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            candidate_number = preferences[i][j];
            if (candidates[candidate_number].eliminated != true) // if the candidate is not eliminated then increase the candidate votes by 1.
            {
                candidates[candidate_number].votes += 1;
                break;          // as the vote is increased come out of the loop so that i increases.
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int winner, vote = voter_count;
    if (vote % 2 == 0) // if voter_count is even
    {
        vote = 1 + (vote / 2);
    }
    else // if voter count is odd.
    {
        vote = 1 + (vote - 1) / 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        
        if (candidates[i].eliminated != true)
        {
            if (candidates[i].votes >= vote)
            {
                printf("%s\n", candidates[i].name); // if the candidate have the majority votes then print the name of the winner.
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes; // lets assume the min votes is the first candidates votes
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes < min)  // condition to find the min votes. 
        {
            if (candidates[i].eliminated == false) // if they are eliminated then dont consider that candidate.
            {
                min = candidates[i].votes;
            }
            else
            {
                continue;
                
            }
        }
        else
        { 
            continue;
        }
    }
    return min;
    
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)  // loop to check if all the candidates are having same no. of votes
    {
        if (candidates[i].eliminated != true)
        {
            if (min == candidates[i].votes)
            {
                continue;
            }
            else
            {
                return false;
                break;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)     // eliminate the candidate if they have least number of votes and their votes is equal to min votes.
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated != true)
        {
            if (min == candidates[i].votes)
            {
                candidates[i].eliminated = true;
            }
        }
    }
   
    return;
}
