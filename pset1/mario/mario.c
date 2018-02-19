#include <stdio.h>
#include <cs50.h>

// prints out a half-pyramid of specified height
int main(void)
{
    int height;
    bool correct = false;

    // prompts the user for an int value between 0 and 23, the height of the half-pyramid
    while (!correct)
    {
        height = get_int("Height: ");
        if (height >= 0 && height < 24)
        {
            correct = true;
        }
        // Give detailed instructions what kind of input is required
        else
        {
            printf("%s", "Please enter an integer between 0 and 23.\n");
        }
    }

    // keeps track of the current line
    for (int line = 0; line < height; line++)
    {
        // prints the spaces for that line
        for (int spaces = 0; spaces < height - line - 1; spaces++)
        {
            printf("%s", " ");
        }
        // prints the hashes for that line
        for (int hashes = 0; hashes < line + 2; hashes++)
        {
            printf("%s", "#");
        }
        // prints a new line
        printf("%s", "\n");
    }
}