// Helper functions
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = atoi(strtok(fraction, "/"));
    int denominator = atoi(strtok(NULL, "/"));
    return 8 * numerator / denominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Notes in an octave
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    const int BASEOCTAVE = 4;
    int basefrequency = 440;

    string shortnote;
    int noteindex;
    int octave;

    // allocates the memory for the short note string (note without the octave number)
    shortnote = malloc(strlen(note)  * sizeof(char));

    // checks the lenght of the note string and extracts values accordingly
    if (strlen(note) == 3)
    {
        shortnote[0] = note[0];
        shortnote[1] = note[1];
        shortnote[2] = '\0';

        if (shortnote[1] == '#')
        {
            shortnote[0] = note[0];
            shortnote[1] = note[1];
            shortnote[2] = '\0';
            octave = note[2] - '0';
        }
        else if (shortnote[0] == 'A' && shortnote[1] == 'b')
        {
            shortnote[0] = 'G';
            shortnote[1] = '#';
            shortnote[2] = '\0';
            octave = note[2] - '0';
        }
        else
        {
            shortnote[0] = shortnote[0] - 1;
            shortnote[1] = '#';
            shortnote[2] = '\0';
            octave = note[2] - '0';
        }
    }
    else
    {
        shortnote[0] = note[0];
        shortnote[1] = '\0';
        octave = note[1] - '0';
    }

    // modifies the base frequency to the frequency of the A note of current octave
    if (octave > BASEOCTAVE)
    {
        basefrequency = (octave - BASEOCTAVE) * 2 * basefrequency;
    }
    else if (octave < BASEOCTAVE)
    {
        basefrequency = basefrequency / ((BASEOCTAVE - octave) * 2);
    }

    // finds the note in the note array and returns the corresponding index
    bool found = false;
    int i = 0;
    while (!found && i < sizeof(NOTES))
    {
        if (strcmp(NOTES[i], shortnote) == 0)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }

    // calculates the n for the frequency formula
    noteindex = i - 9;

    // returns the frequency as an int
    int frequency = round(pow(2, noteindex / 12.0) * basefrequency);
    free(shortnote);
    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (strcmp("", s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
