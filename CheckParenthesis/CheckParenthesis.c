/**
 * @file CheckParenthesis.c
 * @author Itai Tagar <itagar>
 * @version 1.2
 * @date 09 Aug 2016
 *
 * @brief A program that verify text files that satisfies a desired parenthesis structure.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A program that verify text files that satisfies a desired parenthesis structure.
 * Input:       A name or a path to a text file.
 * Process:     Validates input, if the input is valid the program starts to analyze the text file
 *              for determine if the structure of parenthesis is valid or invalid.
 *              If the file is invalid the program ends with an error message.
 * Output:      A message that states the file analysis results, if the input was valid.
 *              An error message in case of bad input.
 */


/*----=  Includes  =-----*/


#include <stdio.h>


/*----=  Definitions  =-----*/


/**
 * @def VALID_STATE 0
 * @brief A Flag for valid state during the program run.
 */
#define VALID_STATE 0

/**
 * @def INVALID_STATE 1
 * @brief A Flag for invalid state during the program run.
 */
#define INVALID_STATE 1

/**
 * @def VALID_ARGUMENTS_NUMBER 2
 * @brief A Macro that sets the valid number of arguments for this program.
 */
#define VALID_ARGUMENTS_NUMBER 2

/**
 * @def INVALID_ARGUMENTS_MESSAGE "Please supply a file!\nusage: CheckParenthesis <filename>\n"
 * @brief A Macro that sets the output message for invalid arguments.
 */
#define INVALID_ARGUMENTS_MESSAGE "Please supply a file!\nusage: CheckParenthesis <filename>\n"

/**
 * @def FILE_NAME_INDEX 1
 * @brief A Macro that sets the index of the File name in the arguments array.
 */
#define FILE_NAME_INDEX 1

/**
 * @def INVALID_FILE_ARGUMENTS_MESSAGE "Error! trying to open the file %s\n"
 * @brief A Macro that sets the output message for an invalid File argument.
 */
#define INVALID_FILE_ARGUMENTS_MESSAGE "Error! trying to open the file %s\n"

/**
 * @def VALID_FILE "ok\n"
 * @brief A Macro that sets the output message for a valid File.
 */
#define VALID_FILE "ok\n"

/**
 * @def INVALID_FILE "bad structure\n"
 * @brief A Macro that sets the output message for a invalid File.
 */
#define INVALID_FILE "bad structure\n"

/**
 * @def INITIAL_SCOPE_NUMBER 0
 * @brief A Macro that sets the initial scope number in a given File.
 */
#define INITIAL_SCOPE_NUMBER 0

/**
 * @def OPEN_ROUND '('
 * @brief A Flag for the Round Opening-Parenthesis character.
 */
#define OPEN_ROUND '('

/**
 * @def CLOSE_ROUND ')'
 * @brief A Flag for the Round Closing-Parenthesis character.
 */
#define CLOSE_ROUND ')'

/**
 * @def OPEN_SQUARE '['
 * @brief A Flag for the Square Opening-Parenthesis character.
 */
#define OPEN_SQUARE '['

/**
 * @def CLOSE_SQUARE ']'
 * @brief A Flag for the Square Closing-Parenthesis character.
 */
#define CLOSE_SQUARE ']'

/**
 * @def OPEN_TRIANGLE '<'
 * @brief A Flag for the Triangle Opening-Parenthesis character.
 */
#define OPEN_TRIANGLE '<'

/**
 * @def CLOSE_TRIANGLE '>'
 * @brief A Flag for the Triangle Closing-Parenthesis character.
 */
#define CLOSE_TRIANGLE '>'

/**
 * @def OPEN_CURLY '{'
 * @brief A Flag for the Curly Opening-Parenthesis character.
 */
#define OPEN_CURLY '{'

/**
 * @def CLOSE_CURLY '}'
 * @brief A Flag for the Curly Closing-Parenthesis character.
 */
#define CLOSE_CURLY '}'


/*----=  Forward Declarations  =-----*/


/**
 * @brief Analyze the results of the 'checkFile' functions, and perform the
 *        required actions for each scenario.
 * @param checkFileResult The given result of the 'checkFile' functions.
 */
void analyzeResults(int const checkFileResult);

/**
 * @brief Checks the given File for valid parenthesis structure.
 * @param pFile The given File to check.
 * @return 0 if the given File satisfies the required parenthesis structure, 1 otherwise.
 */
int checkFile(FILE * const pFile);

/**
 * @brief Checks the given File for valid parenthesis structure.
 *        This function perform recursive calls each time a new parenthesis is opened.
 * @param currentType The current type of Opening-Parenthesis in this call of the function.
 * @param pFile The given File to check.
 * @return 0 if the given File satisfies the required parenthesis structure, 1 otherwise.
 */
int checkFileHelper(char const currentType, FILE * const pFile);

/**
 * @brief Checks if a given 2 parenthesis are matching each other (i.e. one closes the other).
 * @param close The Closing-Parenthesis character.
 * @param open The Opening-Parenthesis character.
 * @return 0 if the given 2 parenthesis are matching each other, 1 otherwise.
 */
int checkMatchingParenthesis(char const close, char const open);


/*----=  Main  =-----*/


/**
 * @brief The main function that runs the program.
 *        It receives arguments from the user and if the arguments are valid, it runs the File
 *        Analysis.
 * @param argc The number of given arguments.
 * @param argv[] The arguments from the user.
 * @return 0 if the given File is a text file which satisfies the required
 *         parenthesis structure, 1 otherwise.
 */
int main(int argc, char * argv[])
{

    // Check valid arguments.
    if (argc != VALID_ARGUMENTS_NUMBER)
    {
        fprintf(stderr, INVALID_ARGUMENTS_MESSAGE);
        return INVALID_STATE;
    }
    else
    {
        // Receive the File to check.
        FILE * pFile;
        pFile = fopen(argv[FILE_NAME_INDEX], "r");

        // In case of a bad File.
        if (pFile == 0)
        {
            fprintf(stderr, INVALID_FILE_ARGUMENTS_MESSAGE, argv[FILE_NAME_INDEX]);
            fclose(pFile);
            return INVALID_STATE;
        }

        // Analyze the File and close its Stream.
        int checkFileResult = checkFile(pFile);
        fclose(pFile);

        // Analyze the results.
        analyzeResults(checkFileResult);
        return VALID_STATE;
    }
}


/*----=  Analyze File  =-----*/


/**
 * @brief Analyze the results of the 'checkFile' functions, and perform the
 *        required actions for each scenario.
 * @param checkFileResult The given result of the 'checkFile' functions.
 */
void analyzeResults(int const checkFileResult)
{
    if (!(checkFileResult))  // If the File is valid, 'checkFileResult' will be equal to 0.
    {
        printf(VALID_FILE);
    }
    else
    {
        printf(INVALID_FILE);
    }
}

/**
 * @brief Checks the given File for valid parenthesis structure.
 * @param pFile The given File to check.
 * @return 0 if the given File satisfies the required parenthesis structure, 1 otherwise.
 */
int checkFile(FILE * const pFile)
{
    return checkFileHelper(EOF, pFile);
}

/**
 * @brief Checks the given File for valid parenthesis structure.
 *        This function perform recursive calls each time a new parenthesis is opened.
 * @param currentType The current type of Opening-Parenthesis in this call of the function.
 * @param pFile The given File to check.
 * @return 0 if the given File satisfies the required parenthesis structure, 1 otherwise.
 */
int checkFileHelper(char const currentType, FILE * const pFile)
{
    static int scopeCounter = INITIAL_SCOPE_NUMBER;

    int currentChar;  // The current character in the given File.

    while ((currentChar = fgetc(pFile)) != EOF)
    {
        // In case we reached any kind of Opening-Parenthesis, we enter a recursive call
        // and increase the 'scopeCounter' by 1.
        if (currentChar == OPEN_ROUND)
        {
            scopeCounter++;
            checkFileHelper(OPEN_ROUND, pFile);
        }
        else if (currentChar == OPEN_SQUARE)
        {
            scopeCounter++;
            checkFileHelper(OPEN_SQUARE, pFile);
        }
        else if (currentChar == OPEN_TRIANGLE)
        {
            scopeCounter++;
            checkFileHelper(OPEN_TRIANGLE, pFile);
        }
        else if (currentChar == OPEN_CURLY)
        {
            scopeCounter++;
            checkFileHelper(OPEN_CURLY, pFile);
        }

        // In case we reached any kind of Closing-Parenthesis, we determine if it is valid.
        // If it is valid we exit the current recursive call and decrease the 'scopeCounter' by 1.
        // If it is invalid, we exit the recursive call with the value 1.
        if (currentChar == CLOSE_ROUND || currentChar == CLOSE_SQUARE ||
            currentChar == CLOSE_TRIANGLE || currentChar == CLOSE_CURLY)
        {
            if (!(checkMatchingParenthesis((char) currentChar, currentType)))
            {
                scopeCounter--;
                return VALID_STATE;
            }
            else
            {
                return INVALID_STATE;
            }
        }
    }

    // In case we reached the end of the File, we check that there are no Opening-Parenthesis
    // left unclosed, using the 'scopeCounter'.
    if (scopeCounter == INITIAL_SCOPE_NUMBER)
    {
        return VALID_STATE;
    }
    else
    {
        return INVALID_STATE;
    }
}

/**
 * @brief Checks if a given 2 parenthesis are matching each other (i.e. one closes the other).
 * @param close The Closing-Parenthesis character.
 * @param open The Opening-Parenthesis character.
 * @return 0 if the given 2 parenthesis are matching each other, 1 otherwise.
 */
int checkMatchingParenthesis(char const close, char const open)
{
    switch (close)
    {
        case (CLOSE_ROUND):
            if (open != OPEN_ROUND)
            {
                return INVALID_STATE;
            }
            else
            {
                return VALID_STATE;
            }

        case (CLOSE_SQUARE):
            if (open != OPEN_SQUARE)
            {
                return INVALID_STATE;
            }
            else
            {
                return VALID_STATE;
            }

        case (CLOSE_TRIANGLE):
            if (open != OPEN_TRIANGLE)
            {
                return INVALID_STATE;
            }
            else
            {
                return VALID_STATE;
            }

        case (CLOSE_CURLY):
            if (open != OPEN_CURLY)
            {
                return INVALID_STATE;
            }
            else
            {
                return VALID_STATE;
            }

        default:
            return INVALID_STATE;
    }
}
