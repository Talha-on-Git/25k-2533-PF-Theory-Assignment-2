#include <stdio.h>
#include <string.h>

void reverseString(char message[], int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        char temp = message[i];
        message[i] = message[length - i - 1];
        message[length - i - 1] = temp;
    }
}

void encodeMessage(char message[], char encodedMessage[], int length)
{

    reverseString(message, length);
    printf("\nReversed string: %s", message);

    for (int i = 0; i < length; i++)
    {
        unsigned char val = message[i];
        val = val ^ ((1 << 1) | (1 << 4));
        encodedMessage[i] = (char)val;
    }

    encodedMessage[length] = '\0';

    printf("\nEncoded message: %s\n", encodedMessage);
}

void decodeMessage(char message[], char encodedMessage[], int length)
{
    for (int i = 0; i < length; i++)
    {
        unsigned char val = encodedMessage[i];
        val = val ^ ((1 << 1) | (1 << 4));
        message[i] = (char)val;
    }
    message[length] = '\0';
    printf("\nDecoded message (after re toggling bits): %s", message);

    reverseString(message, length);

    // for (int i = length/2; i > 0; i--)
    // {
    //     char temp = message[i-1];
    //     message[i-1] = message[length - i];
    //     message[length - i] = temp;
    // }
    printf("\nfinal decoded message: %s", message);
}

int main()
{
    char message[50];
    char encodedMessage[50];
    int counter = 0, choice, length = 0, isEncoded = 0;
    char ch;
    printf("\n=========== Welcome to TCS Dispatch Management System ==========\n");

    do
    {
        printf("\n1. Encode message");
        printf("\n2. Decode message");
        printf("\n3. Decode a Custom Encoded Message");
        printf("\n4. Exit\n");
        printf("\nWhich operation do you want to perform?: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            counter = 0;
            printf("Enter your message to encode: ");

            while (counter < 50)
            {
                ch = getchar();
                if (ch == '\n')
                {
                    break;
                }
                else
                {
                    message[counter] = ch;
                    counter++;
                }
            }
            message[counter] = '\0';
            printf("Your message is: %s\n", message);

            length = counter;
            encodeMessage(message, encodedMessage, length);
            isEncoded = 1;
            break;
        case 2:
            if (!isEncoded)
            {
                printf("\nPlease encode the message before decoding!\n");
            }
            else
            {
                decodeMessage(message, encodedMessage, length);
            }
            break;
        case 3:
            printf("Enter encoded message to decode: ");
            fgets(encodedMessage, 50, stdin);
            encodedMessage[strcspn(encodedMessage, "\n")] = '\0';
            length = strlen(encodedMessage);
            decodeMessage(message, encodedMessage, length);
            break;
        case 4:
            printf("\nGoodbye!");
            return 0;
            break;
        default:
            printf("\nInvalid choice!");
            break;
        }
    } while (choice != 4);
}