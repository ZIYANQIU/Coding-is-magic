// Xinze Du  2092629
// Ziyan Qiu 2089937
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Question:
 * String Formatting and Justification
 * For this assignment, you will write a function that formats and justifies a string into
 * lines of a specified length. This function will ensure that spaces between words are
 * balanced so that each line reaches the desired length.
 */

/**
 * Ideas for solving the problem:
 * Using the divide and conquer, we can divide this problem into six steps.
 * 1. Read the file and get the paragraph and lineLength.
 * 2. Put the pointer paragraph into the words array, separated by spaces, and count the wordCount.
 * 3. Define two pivot start and end, start does not move, move the end, and calculate the currentLength, the next word added to the currentLength and lineLength comparison, to determine the number of words in each line.
 * 4. Calculate how many space slots, such as 4 words, there are 3 slots, one between each two words, when there are extra spaces will be filled from front to back to the slot.
 * 5. Fill words and spaces into output.First fill the word, then fill the spaceWidth, if there are remaining spaces extraSpaces, fill a remaining space, and then continue to fill the next word, until the end, and finally add a '\n'.
 * 6. Write the output file
 */

// Define maximum lengths for words, paragraph, and output
#define MAX_WORD_LENGTH 100
#define MAX_PARAGRAPH_LENGTH 1000
#define MAX_OUTPUT_LENGTH 10000

// Function to read the file and extract the paragraph and line length
int readFile(const char *input, int *lineLength, char *paragraph)
{
    // Error message for reading files
    FILE *file = fopen(input, "r");
    if (file == NULL)
    {
        printf("Failed to open the file: %s\n", input);
        return -1;
    }
    // Error message for getting the lineLength
    if (fscanf(file, "%d\n", lineLength) != 1)
    {
        printf("Failed to read the lineLength from file: %s\n", input);
        fclose(file);
        return -1;
    }
    // Initialize the paragraph to an empty string
    paragraph[0] = '\0';
    char buffer[MAX_PARAGRAPH_LENGTH];
    while (fgets(buffer, sizeof(buffer), file))
    {
        if (buffer[0] == 'E')
        {
            break;
        }
        // Concatenate the buffer content to the paragraph
        strcat(paragraph, buffer);
    }
    fclose(file);
    return 0;
}

// Function to format and print the paragraph with justified lines
void formatAndPrintParagraph(char *paragraph, int lineLength, char *output)
{
    // Split the paragraph into words
    char *words[MAX_WORD_LENGTH];
    int wordCount = 0;
    char *word = strtok(paragraph, " ");
    // Store words and count them
    while (word != NULL)
    {
        words[wordCount++] = word;
        // Move to the next word
        word = strtok(NULL, " ");
    }

    int currentLength = 0;
    int start = 0;
    output[0] = '\0';  // Initialize output to an empty string

    // Process each line
    while (start < wordCount)
    {
        int end = start;
        currentLength = strlen(words[start]);
        // Find the maximum number of words that fit in the current line
        while (end + 1 < wordCount)
        {
            int nextWordLength = strlen(words[end + 1]);
            if (currentLength + nextWordLength + 1 <= lineLength)
            {
                currentLength += nextWordLength + 1;
                end++;
            }
            else
            {
                break;
            }
        }
        // Calculate space distribution
        int spaceSlots = end - start;
        int totalSpaces = lineLength - currentLength + spaceSlots;
        int spaceWidth = spaceSlots > 0 ? (totalSpaces / spaceSlots) : 0;
        int extraSpaces = spaceSlots > 0 ? (totalSpaces % spaceSlots) : 0;
        // Print the current line
        for (int i = start; i <= end; i++)
        {
            if (i > start)
            {
                // Add the calculated spaces between words
                for (int j = 0; j < spaceWidth; j++)
                    strcat(output, " ");
                if (extraSpaces > 0)
                {
                    strcat(output, " ");
                    extraSpaces--;
                }
            }
            strcat(output, words[i]);
        }
        start = end + 1;
        if (start < wordCount)
        {
            strcat(output, "\n");
        }
    }
}

// Function to write the formatted paragraph to a file
int writeFile(const char *filename, char *output)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open the file: %s\n", filename);
        return -1;
    }
    // Write the output to the file
    fprintf(file, "%s", output);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 3)
    {
        printf("Usage: %s input.txt output.txt\n", argv[0]);
        return -1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    int lineLength;
    char paragraph[MAX_PARAGRAPH_LENGTH];
    char output[MAX_OUTPUT_LENGTH];

    // Read the input file
    if (readFile(input_filename, &lineLength, paragraph) != 0)
    {
        return -1;
    }
    // Format and print the paragraph
    formatAndPrintParagraph(paragraph, lineLength, output);

    // Write the output file
    if (writeFile(output_filename, output) != 0)
    {
        return -1;
    }

    return 0;
}
