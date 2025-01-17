/*
Assignment name  : infin_mult
Expected files   : *.c, *.h
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------
Write a program that takes as a parameter two strings that represent two
numbers potentially infinit, and displays on stdout the result of the
multiplication of these two numbers, followed by a '\n'.
A negative number will always be prefixed by one and only one -. The only
characters that can be part of the strings are digits and the sign -.
Both parameters will always be well formated, and you will always have exactly
two parameters, no tricks.
Example:
$> ./infin_mult "879879087" "67548976597" | cat -e
59434931855952726939$
$> ./infin_mult "-876435" "987143265" | cat -e
-865166907460275$
$> ./infin_mult "-807965" "-34532" | cat -e
27900647380$
$> ./infin_mult "-807965" "0"
0
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

void multiply_strings(char *s1, char *s2)
{
    // 1. strlen of s1 and s2
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    // 2. check for negative signs
    int negative = false;
    if (s1[0] == '-') {
        negative ^= true;
        s1++;
        len1--;
    }
    if (s2[0] == '-') {
        negative ^= true;
        s2++;
        len2--;
    }

    // 3. handle zero
    if ((len1 == 1 && s1[0] == '0') || (len2 == 1 && s2[0] == '0')) {
        write(1, "0", 2);
        return;
    }

    // 4. allocate space for result
    int result_len = len1 + len2;
    char *result = malloc(result_len + 1);
    if (!result)
        return ;

    // 5. initialize result array with zeros
    for (int i = 0; i < result_len; i++)
        result[i] = '0';
    result[result_len] = '\0';

    // 6. perform multiplication
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (s1[i] - '0') * (s2[j] - '0');
            int pos1 = i + j;
            int pos2 = i + j + 1;
            int sum = (result[pos2] - '0') + mul;

            result[pos2] = (sum % 10) + '0';
            result[pos1] += sum / 10;
        }
    }

    // 7. handle negative sign
    if (negative == true)
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
    
    multiply_strings(argv[1], argv[2]);
    write(1, "\n", 1);
    return 0;
}