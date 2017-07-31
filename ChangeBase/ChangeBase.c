/**
 * @file ChangeBase.c
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 09 Aug 2016
 *
 * @brief A program that convert a given number from one base representation to another.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A program that convert a given number from one base representation to another.
 * Input:       One input that holds the given number, it's current base representation and the
 *              new base we want to convert to. The input comes from the user in the format of -
 *              <original base>^<new base>^<the number in original base>^
 * Process:     The program analyze if the input is valid, an invalid state is where the given
 *              number cannot be represented with the given original base.
 *              After validating the input, the program convert the number to the new base
 *              representation and prints it out to the screen.
 * Output:      The converted number is printed to the screen if the input was valid.
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
 * @def STANDARD_BASE 10
 * @brief A Macro that sets the standard base which we usually use.
 */
#define STANDARD_BASE 10

/**
 * @def TRUE 1
 * @brief A Flag for true statement.
 */
#define TRUE 1

/**
 * @def FALSE 0
 * @brief A Flag for false statement.
 */
#define FALSE 0

/**
 * @def MAX_RESULT_SIZE 20
 * @brief A Macro that sets the maximum number of digits for the result number after conversion.
 */
#define MAX_RESULT_SIZE 20

/**
 * @def INVALID_INPUT_MESSAGE "invalid!!\n"
 * @brief A Macro that sets the output message for invalid user input.
 */
#define INVALID_INPUT_MESSAGE "invalid!!\n"


/*----=  Forward Declarations  =-----*/


/**
 * @brief Performs the base conversion from a given bases for the desired given number to convert.
 *        The function first convert the number to be represented in base 10, and then convert
 *        from base 10 to the desired new base.
 *        Explanation of the Algorithm: In the description of this function's definition.
 * @param originalBase The base in which the given number is currently represented.
 * @param newBase The base to convert the given number representation to.
 * @param number The given number, represented in the original base, that should be converted.
 * @param result The path to store the conversion result in.
 * @return char array holding the converted number.
 */
char * baseConverter(int const originalBase, int const newBase, int number, char * result);

/**
 * @brief An Helper function for the Base Converter function.
 *        This function perform the actual base conversion from the given number to decimal,
 *        i.e. represented in base 10.
 * @param originalBase The base in which the given number is currently represented.
 * @param number The given number, represented in the original base, that should be converted.
 * @return The number represented in base 10 as decimal.
 */
int decimalConverter(int const originalBase, int number);

/**
 * @brief An Helper function for the Base Converter function.
 *        This function perform the actual base conversion, assuming the original base is 10,
 *        and convert the given number to the new base.
 *        The function updates the given result array with the converted number.
 * @param newBase The base to convert the given number representation to.
 * @param number The given number, represented in the original base, that should be converted.
 * @param result The path to store the conversion result in.
 */
void baseConverterHelper(int const newBase, int number, char * result);

/**
 * @brief A Power operator. Raises the base in the power of degree.
 * @param base The base of the power.
 * @param degree The degree of the power.
 * @return The result of the base raised to the degree.
 */
int power(int const base, int const degree);

/**
 * @brief Verify that the given number in the user input can be represented in the
 *        given original base.
 * @param originalBase The given original base in the user input.
 * @param number The given number in the user input.
 * @return 0 if the input is invalid, 1 otherwise.
 */
int checkInput(int const originalBase, int number);

/**
 * @brief Prints the given conversion result to the standard output.
 *        During the conversion, the result is stored backwards, so this function determines which
 *        index is the last index in the result array that contains data, and from this points it
 *        prints the data all the way back.
 * @param The result of the converted number.
 */
void printResult(char * result);


/*----=  Main  =-----*/


/**
 * @brief The main function that runs the program. The function receive input from the user
 *        and perform the base conversion using the base conversion functions.
 *        The function determines if the input is valid, and if so it prints the result of the
 *        base conversion. If the input is invalid, the function will print an error message.
 * @return 0 when the program ran successfully, 1 otherwise.
 */
int main()
{
    // Initialize variables.
    int originalBase = 0;
    int newBase = 0;
    int number = 0;
    char result[MAX_RESULT_SIZE + 1] = {};

    // Receive input from user parse it to the relevant variables.
    scanf("%d^%d^%d^", &originalBase, &newBase, &number);

    // If the given number is 0, it does not matter what are the bases, the result will be 0.
    if (number == 0)
    {
        printf("%d\n", number);
    }
    else
    {
        // Verify input, Convert the number and print the result.
        if (checkInput(originalBase, number))
        {
            printResult(baseConverter(originalBase, newBase, number, result));
        }
        else
        {
            fprintf(stderr, INVALID_INPUT_MESSAGE);
            return INVALID_STATE;
        }
    }

    return VALID_STATE;
}


/*----=  Base Conversion  =-----*/


/**
 * @brief Performs the base conversion from a given bases for the desired given number to convert.
 *        The function first convert the number to be represented in base 10, and then convert
 *        from base 10 to the desired new base.
 *        Explanation of the Algorithm:
 *        The algorithm used in order to convert the number is as follow:
 *        We take each digit in the given number, starting from the lowest one, and
 *        perform Euclidean Division of this digit with the new base we want to convert to.
 *        Then, we take the remainder and multiply it with the original base raised to the power
 *        of the digit index.
 *        We take the quotient from the Euclidean Division and perform the same actions on this
 *        number. We keep doing so until the quotient is equals to 0.
 *        We sum up all of our calculations of the remainders multiplied by the original base
 *        powers, and this is the result for the converted number.
 *        The running time complexity of this algorithm is O(n) where n is the number of digits
 *        in the given number to convert.
 *        In the main call for this algorithm, we perform a conversion to base 10 first, and then
 *        convert from base 10 to the new base. So we call this function twice, so the
 *        running time complexity is O(n) + O(n), i.e. O(n).
 *        This algorithm was taught during Linear Algebra class, in order to represent one
 *        polynomial another polynomial's degrees.
 * @param originalBase The base in which the given number is currently represented.
 * @param newBase The base to convert the given number representation to.
 * @param number The given number, represented in the original base, that should be converted.
 * @param result The path to store the conversion result in.
 * @return char array holding the converted number.
 */
char * baseConverter(int const originalBase, int const newBase, int number, char * result)
{
    int baseTenNumber = decimalConverter(originalBase, number);  // Convert to Decimal.
    baseConverterHelper(newBase, baseTenNumber, result);
    return result;
}

/**
 * @brief An Helper function for the Base Converter function.
 *        This function perform the actual base conversion from the given number to decimal,
 *        i.e. represented in base 10.
 * @param originalBase The base in which the given number is currently represented.
 * @param number The given number, represented in the original base, that should be converted.
 * @return The number represented in base 10 as decimal.
 */
int decimalConverter(int const originalBase, int number)
{
    int result = 0;

    int index = 0;
    while (number != 0)
    {
        int currentDigit = number % STANDARD_BASE;
        result += (currentDigit * (power(originalBase, index)));
        number /= STANDARD_BASE;
        index++;
    }

    return result;
}

/**
 * @brief An Helper function for the Base Converter function.
 *        This function perform the actual base conversion, assuming the original base is 10,
 *        and convert the given number to the new base.
 *        The function updates the given result array with the converted number.
 * @param newBase The base to convert the given number representation to.
 * @param number The given number, represented in the original base, that should be converted.
 * @param result The path to store the conversion result in.
 */
void baseConverterHelper(int const newBase, int number, char * result)
{
    int index = 0;
    while (number != 0)
    {
        int currentDigit = number % newBase;
        result[index] = (char)(currentDigit + '0');
        number /= newBase;
        index++;
    }
}

/**
 * @brief A Power operator. Raises the base in the power of degree.
 * @param base The base of the power.
 * @param degree The degree of the power.
 * @return The result of the base raised to the degree.
 */
int power(int const base, int const degree)
{
    if (degree == 0)
    {
        return 1;
    }
    else
    {
        return (power(base, degree - 1)) * base;
    }
}


/*----=  Input Handling  =-----*/


/**
 * @brief Verify that the given number in the user input can be represented in the
 *        given original base.
 * @param originalBase The given original base in the user input.
 * @param number The given number in the user input.
 * @return 0 if the input is invalid, 1 otherwise.
 */
int checkInput(int const originalBase, int number)
{
    while (number != 0)
    {
        int currentDigit = number % STANDARD_BASE;
        if (currentDigit >= originalBase)
        {
            return FALSE;
        }
        number /= STANDARD_BASE;
    }
    return TRUE;
}


/*----=  Output Handling  =-----*/


/**
 * @brief Prints the given conversion result to the standard output.
 *        During the conversion, the result is stored backwards, so this function determines which
 *        index is the last index in the result array that contains data, and from this points it
 *        prints the data all the way back.
 * @param The result of the converted number.
 */
void printResult(char * result)
{
    // Determine the indices of result that contain data.
    int i = 0;
    while (result[i] != 0)
    {
        i++;
    }

    // Prints the converted number in the required order.
    i--;  // index 'i' is currently at the '\0' character, we need to take 1 step backwards.
    for ( ; i >= 0; --i)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
