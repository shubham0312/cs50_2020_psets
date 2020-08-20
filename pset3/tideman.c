#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool loop_checker(int pair, bool visited[]);
bool cycle_present(int pair);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i],name) == 0) // Checking the name of the voters if they are correct then give them ranking accordingly and return true.
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_number_1 = ranks[i]; // Here candidate_number stores the  candidate number which is prefered over the other candidates in an array.
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidate_number_2 = ranks[j]; // storing the next candidates number and then increasing the votes for one on one election winner.
            preferences[candidate_number_1][candidate_number_2] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == 0)
        {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j) // if the value is same then preference array stores the same candidate name in it ,so continue.
            {
                continue;
            }
            else if (preferences[i][j] > preferences[j][i]) // if preference[i][j] greater than preference[j][i] then increase pair count and also stores the winner and the loser in the pair struct.
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])// if preference[i][j] smaller than preference[j][i] then increase pair count and also stores the winner and the loser in the pair struct.
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
            else // if preference[i][j] is equal to  preference[j][i] then continue.
            {
                continue; // tied condition should not be considered
            }

        }
        }
        else
        {
            for (int j = i + 1; j < candidate_count; j++)
        {
            if (i == j) // if the value is same then preference array stores the same candidate name in it ,so continue.
            {
                continue;
            }
            else if (preferences[i][j] > preferences[j][i]) // if preference[i][j] greater than preference[j][i] then increase pair count and also stores the winner and the loser in the pair struct.
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])// if preference[i][j] smaller than preference[j][i] then increase pair count and also stores the winner and the loser in the pair struct.
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
            else // if preference[i][j] is equal to  preference[j][i] then continue.
            {
                continue; // tied condition should not be considered
            }

        }
        }


    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max_votes[pair_count];
    for (int i = 0; i < pair_count; i++)  // Firstly we are storing the preferences of the voter which consists of votes of winner in a one on  one competition
    {
        max_votes[i] = preferences[pairs[i].winner][pairs[i].loser]; // We are doing this so that we can easily sort the winners votes in descending order of their victory.
    }
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (max_votes[i] >= max_votes[j]) // if the first pair votes is greater than the second pair then continue.
            {
                continue;
            }
            else // if the first pair votes are less than the next pair votes then swap their places in pairs structure.
            {
                int temp1 = pairs[i].winner; // declared two temporary variable to swap the struct pairs. We are doing the operations of sorting in the array called max_votes and then storing the sorted elements.
                int temp2 = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp1;
                pairs[j].loser = temp2;
                int temp3 = max_votes[i];
                max_votes[i] = max_votes[j];
                max_votes[j] = temp3;

            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;  // make all the pairs to be locked initially
        if(cycle_present(i) == true)  // now checking if it have a cycle present or not .
        {
            locked[pairs[i].winner][pairs[i].loser] = false; // if the cycle is present then make the pair equal to false in the locked matrix.
        }
    }
    return;
}

bool cycle_present(int pair) 
{
    bool visited[candidate_count]; // boolean varirable created to check the visited and unvisited nodes.
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;   // initially loading the array with false which means no node is visited initially.
    }
    return loop_checker(pair, visited); // if it returns true then cycle is present and vice versa.
    
}

bool loop_checker(int pair, bool visited[]) // recursive fucntion to check the loop.
{
    if(visited[pair]) // if the node is visited then return true 
    {
        return true;
    }
    visited[pair] = true; // make the node visited by storing true for that node
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[pair][i] == true) 
        {
            if (loop_checker(i, visited) == true) //calling the recursive function to check if the loop is present or not
            {
                return true;
            }
        }
    }
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j) // if the value of i == j then continue as we have already made it false. This matrix is given in the question for the locked matrix of alice , charlie, bob. 
            {                         //       Alice   Bob  Charlie
                continue;            // Alice [false, true, false]
            }                        //  Bob  [false, false, false]  // if we want to find the source then we will check for that column
                                     //Charlie[true, false, false]      which has all the falses in the that column.
            if (locked[j][i] == true)
            {
                break;
            }
            else
            {
                if(j == candidate_count - 1)  // when the value of (j == total candidate - 1) Which means that all the column elements of locked[i] is false and when it reaches the last element then print the name of the winner.
                {
                    printf("%s\n",candidates[i]);
                }
            }
        }
    }
    return;
}
