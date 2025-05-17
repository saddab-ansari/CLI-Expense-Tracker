#include <stdio.h>

int main(void)
{

    while (true)

    {

        printf(
            " -----------Welcome to the Neon Calculator!------------\n How may i help you today? \n");

        printf(" 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n 5. Exit\n");

        int i = get_int("input the number of task you want to perform : ");

        if (i == 5)
        {
            printf("See you Later!\n");
            break;
        }

        else
        {
        int a;
        printf("Enter an integer: ");
        scanf("%d", &a);

        int b;
        printf("Enter an integer: ");
        scanf("%d", &b);

        if (i == 1)
        {
            printf("The Addition of both number is : %i\n", a + b );
            printf("\n");
        }

        if (i == 2)
        {
            printf("The Substraction of second number from the first is : %i\n", a - b );
            printf("\n");
        }

        if (i == 3)
        {
            printf("The Multiplication of both number is : %i\n", a*b );
            printf("\n");
        }

        if (i == 4)
        {
            printf("The divison of first by the second number is : %i\n", a/b );
            printf("\n");
        }


        }


    }
}
