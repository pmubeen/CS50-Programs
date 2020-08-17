/*
    Name: plurality.c
    Description: Takes in command line arguments as candidate names. Then takes in number of votes and takes in the candidate
    name for each vote. Tallies each candidates votes, compares and prints out the candidate/s with the maximum vote.
    Author: CS50 staff
    Co-Author: Mubeen Padaniya
    Date: 5/5/2020
    Version: 2 (completed the print_winner and vote functions)
*/
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
    // goes through candidate list
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name,name) == 0) { //if the input name matches candidate name
            candidates[i].votes++; //append the candidates' vote count
            return true; //exit bool and return value true
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int max_votes = 0; //placeholder for the maximum votes
    for (int i = 0; i < candidate_count; i++) { //checks for the maximum vote value
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++) { //checks if candidates have maximum vote value and prints their name if true.
        if (candidates[i].votes == max_votes) {
            printf("%s\n",candidates[i].name);
        }
    }
    return;
}
