/*
Assignment name  : infin_add
Expected files   : *.c, *.h
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------
Write a program that takes as a parameter two strings that represent two
numbers potentially infinit, and displays on stdout the result of the addition
of these two numbers, followed by a '\n'.
A negative number will always be prefixed by one and only one -. The only
characters that can be part of the strings are digits and the sign -.
Both parameters will always be well formated, and you will always have
exactly two parameters, no tricks.
Example:
$> ./infin_add "879879087" "67548976597" | cat -e
68428855684$
$> ./infin_add "-876435" "987143265" | cat -e
986266830$
$> ./infin_add "-807965" "-34532"
-842497
$>
*/

#include <stdio.h> // for printf -> TESTING ONLY

#include <unistd.h> // For write and size_t
#include <stdlib.h> // For malloc and free
#include <stdbool.h>

size_t ft_strlen(char *s)
{
    size_t len = 0;
    while(s[len])
        len++;
    return(len);
}

void add_strings(char *s1, char *s2)
{
    // 1. strlen of s1 and s2
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    // 2. check for negative signs
    int negative1 = false;
    int negative2 = false;
    if (s1[0] == '-') {
        negative1 = true;
        s1++;
        len1--;
    }
    if (s2[0] == '-') {
        negative2 = true;
        s2++;
        len2--;
    }

    // 3. determine result sign for subtraction cases
    int result_is_negative = 0;

    // 4. allocate space for result
    size_t max_len = (len1 > len2 ? len1 : len2) + 1;
    char *result = malloc(max_len + 1);
    if (!result)
        return ;

    // 5. initialize result array with zeros
    for (size_t i = 0; i < max_len; i++)
        result[i] = '0';
    result[max_len] = '\0';

    // 6. perform addition or subtraction based on signs
    if (negative1 == negative2) // same sign -> perform addition
    {
        int carry = 0;
        size_t k = max_len - 1;
        for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; i--, j--, k--) {
            int digit1 = (i >= 0 ? s1[i] - '0' : 0);
            int digit2 = (j >= 0 ? s2[j] - '0' : 0);
            int sum = digit1 + digit2 + carry;
            result[k] = (sum % 10) + '0';
            carry = sum / 10;
        }
        result_is_negative = negative1;
    }
    else // different signs -> perform subtraction
    {
        int borrow = 0;
        size_t k = max_len - 1;

        // determine larger absolute value
        char *larger = len1 > len2 || (len1 == len2 && ft_strlen(s1) > ft_strlen(s2)) ? s1 : s2;
        char *smaller = larger == s1 ? s2 : s1;
        size_t larger_len = larger == s1 ? len1 : len2;
        size_t smaller_len = larger == s1 ? len2 : len1;
        result_is_negative = (larger == s2 ? negative2 : negative1);

        for (int i = larger_len - 1, j = smaller_len - 1; i >= 0 || borrow; i--, j--, k--) {
            int digit1 = (i >= 0 ? larger[i] - '0' : 0);
            int digit2 = (j >= 0 ? smaller[j] - '0' : 0);
            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result[k] = diff + '0';
        }
    }

    // 7 write negative sign if necessary
    if (result_is_negative)
        write(1, "-", 1);

    // 8. skip over leading zero digits
    int i = 0;
    while (result[i] == '0')
        i++;

    // 9. write the result to STDOUT
    while (result[i]) {
        write(1, &result[i], 1);
        i++;
    }

    // 10. free allocated memory for result
    free(result);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    
    add_strings(argv[1], argv[2]);
    write(1, "\n", 1);
    return 0;
}