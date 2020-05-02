#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*The program operates by the user choosing one of the four main tasks:
                     1. Classical rail fence cipher
                     2. 2-Level rail fence cipher encryption
                     3. 2-Level rail fence cipher decryption
                     4. Substitution cipher decryption.
These correspond to options 1, 2, 3 and 4 respectively. */

/*****************************************************************************************************************************************
USER INTERFACE NOTES: The program uses FILE I/O to operate the task selection, the user inputs either 1, 2, 3 or 4 into
the "TaskSelection.txt" file. The user then needs to put in the text to encrypt or decrypt into the file called
"InputDataAssignment.txt". After this, an integer rail key number is required for both primary and secondary rails
into the files "EnterTheKeyPrimaryRails" AND "EnterTheKeySecondaryRails" respectively.
*****************************************************************************************************************************************/

/*The terminal provides a friendly menu system which states the four possible tasks which can be chosen. The program accepts and validates the user's
input, reads this choice and displays it on the terminal and corresponds this number to a switch statement 'case' where the code to perform
the task is executed. Once the switch case is chosen, the program reads the message and the number of characters,
performing either encryption or decryption by calling the respective function.
Once the program has completed the encryption/decryption algorithm, it outputs the cipher text to a file called
"OutputDataAssignment.txt". This text is also displayed in the terminal and a visual representation of the
rail fence cipher is also displayed to reinforce that the correct algorithm is used.*/

/*****************************************************************************************************************************************
PROGRAM FLOW CONTROL: User inputs the task they want to execute into a file, choosing either 1, 2, 3 or 4. The number of primary &
secondary rails is inputted by the user into "EnterTheKeyPrimaryRails" AND "EnterTheKeySecondaryRails" respectively. Finally, the user
inputs the text they want to encrypt/decrypt into another file "InputDataAssignment.txt". The user then runs the program.
If:
Option 1 is chosen: 'railFence' function is called
Option 2 is chosen: 'railFence2' function is called
Option 3 is chosen: 'railFence2' function is called
Option 4 is chosen: 'Words' function is called
After the algorithm is complete, it outputs the final encrypted/decrypted message into an output file called "OutputDataAssignment.txt".
This message is also outputted to the terminal.
*****************************************************************************************************************************************/


void railFence(char *message, char *cipherText, int length, int A);
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir);
void Words(char *message, char cipherText, int length);
void PutFrequentLetters(int column, int length, char *columnLetter, char *message, char *FrequentLettersUsed);
int stringLength(char *Inputstr);

int main()
{
    int x = 0;                   //'x' is an integer to store the user's input of number 1, 2, 3 or 4
    int dir = 0;                //When 'dir' is 0, double rail encryption is performed, when 'dir' is 1, double rail decryption is performed

    printf("\n\n\n\n\n\n\n\n");
    printf("                            Welcome to Encryption, Decryption and Substitution ciphering\n");               //Creates the 'User-friendly' menu system
    printf("                            Which program would you like to do? Please enter a number, 1, 2, 3 or 4:\n\n");     //Each task corresponds to a specific number
    printf("                                            1. Classical Rail Fence Encryption\n\n");
    printf("                                            2. 2-Level Rail Fence Cipher Encryption\n\n");
    printf("                                            3. 2-Level Rail Fence Cipher Decryption\n\n");
    printf("                                            4. Substitution Cipher Decryption\n\n\n");
    printf("Please enter your selection: ");
    printf("\n");


    FILE *TaskSelect;           //Pointer to a file "TaskSelection.txt" where the user selects a task given by number 1, 2, 3 or 4

    TaskSelect = fopen("C:/Users/George/Downloads/TaskSelection.txt", "r");         //Opens the file and reads the task number that the user has inputted into the designated file

    if(TaskSelect == NULL)      //If the file does not exist, program prints out a message which says the directory does not exist
    {
        perror("fopen()");
        return 0;
    }

    fscanf(TaskSelect, "%d", &x);     //Scans the designated file and reads the first integer in the file
    printf("%d\n", x);              //Prints to the console what the integer in the file was

    while(x < 1 || x > 4)              //If the user input is not a number between 1 & 4, the program terminates and asks to restart to enter a valid number 1, 2, 3 or 4
    {
        printf("\nInvalid number, please enter again a number between 1 & 4 in the file. Kill the program to restart\n");
        return 0;
    }

    if(x == 2)             //When option 2 is selected (2-Level Rail fence cipher encryption)
    {
        dir = 0;            //Establishing the dir variable as a number to execute the 2-Level Rail fence cipher encryption
    }

    if (x == 3)            //When option 3 is selected (2-Level Rail fence cipher decryption)
    {
        dir = 1;            //Establishing the dir variable as a number to execute the 2-Level Rail fence cipher decryption
    }


    switch(x)                  //Contains 4 cases which correspond to the 4 possible choices the user can input, number 1, 2, 3 or 4
    {
        case 1:                     //Case when option 1 is chosen (Classical Rail Fence Cipher Encryption)
        {
            int railRows;           //Variable to take in user's input for the amount of rails used in the encryption
            int i = 0;              //Variable used as a counter when counting how many characters are in the designated file
            int x = 0;              //Variable to store the amount of rails used in the encryption
            char c;                             //Is a variable to temporarily store each individual character in the message


            FILE *input;                    //Pointer to a file called "InputDataAssignment.txt" where the user has inputed the text they want to encrypt

            input = fopen("C:/Users/George/Downloads/InputDataAssignment.txt", "r");        //The pointer 'input' opens the file and is set to read the message

            if(input == NULL)      //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }
                                                //We determine the size of the file and set the size of array before declaring it
            fseek(input, 0, SEEK_END);          //Denotes the end of the message and sets the position indicator
            int size = ftell(input);            //Returns the size of the message based on the two position indicators
            fseek(input, 0, SEEK_SET);          //Denotes the start of the message and sets the starting position indicator

            char message[size];      //The array 'message[]' stores the input characters from the designated file with array size 'size'
            char cipherText[size];           //The array stores the encrypted characters once the function 'railFence' has completed its algorithm

            printf("\nThe string was of length: %d\n\n", size);
            printf("Please enter message to encrypt:\n");

            fscanf(input, "%c", &c);                //Scans the input file and reads the first character in the file

            while(!feof(input))                     //Whilst there is still a character present (Including spaces and newlines), keep storing characters in the array
            {
                message[i] = c;                 //Puts the first character of the file into the array strting at index '0'
                i++;                           //Increments the array index by 1
                fscanf(input, "%c", &c);      //Scans the input file again and reads the next character in the file
            }

            message[i] = 0;             //Terminate the last scanned character in the array so the 'space' character is not included
            printf("%s\n", message);            //Displays the input message from the file

            int len = stringLength(message);              //Function 'stringLength' is called to return the length of the inputed 'message', storing it as an integer


            FILE *PrimaryRailKey;               //Pointer to a file "EnterTheKeyPrimaryRails" where the user puts in the number of primary rails they want for the encryption

            PrimaryRailKey = fopen("C:/Users/George/Downloads/EnterTheKeyPrimaryRails", "r");       //Opens the file and reads the number of rails the user has inputted

            if(PrimaryRailKey == NULL)             //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }

            fscanf(PrimaryRailKey, "%d", &x);               //Scans the integer number of rails and puts the number into a variable called 'x'

            while(x < 1)                               //If the number of rails is less than 1, the program terminates
            {
                printf("\nInvalid number, please enter again. Kill the program to restart\n");
                return 0;
            }

            railRows = x;                       //Rail number is given to a variable 'railRows' so it is easier to remember what the variable stores
            printf("\nEnter the number of primary rails:\n%d\n\n", railRows);

            int j = 0;
            railFence(message, cipherText, len, railRows);         //The function 'railFence' is called to perform the encryption algorithm for the classical rail fence cipher
            printf("\n");

            FILE *output;                   //Pointer to a file called "OutputDataAssignment.txt" where the program outputs the encrypted text
            output = fopen("C:/Users/George/Downloads/OutputDataAssignment.txt", "w");          //The pointer 'output' opens the file and writes the encrypted message in

            if(output == NULL)        //If there is no file present, produce an error statement
            {
                perror("fopen()");
            }

            printf("The encrypted message is:\n");


            for(j = 0; j < len; j++)            //Loop until the end of the encrypted message is reached
            {
                printf("%c", cipherText[j]);                    //Encrypted message is printed to the terminal
                fprintf(output, "%c", cipherText[j]);           //The encrypted message is also printed to the file
            }
            printf("\n\n");
            break;          //Allows the process to end after the encryption by getting out of the switch loop
        }





        case 2:                                //Case when option 2 is chosen (2-Level Rail fence cipher Encryption)
        {
            int railRowsPrimary;                 //Variable to take user's input for the number of primary rails
            int railRowsSecondary;               //Variable to take user's input for the number of secondary rails
            int dir = 0;                         //Variable initialised to tell the function to perform Encryption
            int i = 0;                           //Variable used as a counter when counting how many characters are in the designated file
            int x = 0;                           //Variable to store the amount of primary rails used in the encryption
            int x2 = 0;                          //Variable to store the amount of secondary rails used in the encryption
            char c;                              //Is a variable to temporarily store each individual character in the message

            FILE *input;                //Pointer to a file called "InputDataAssignment.txt" where the user has inputed the text they want to encrypt

            input = fopen("C:/Users/George/Downloads/InputDataAssignment.txt", "r");       //The pointer 'input' opens the file and is set to read the message

            if(input == NULL)      //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }
                                                //We determine the size of the file and set the size of array before declaring it
            fseek(input, 0, SEEK_END);          //Denotes the end of the message and sets the position indicator
            int size = ftell(input);            //Returns the size of the message based on the two position indicators
            fseek(input, 0, SEEK_SET);          //Denotes the start of the message and sets the starting position indicator

            char message[size];      //The array 'message[]' stores the input characters from the designated file with array size 'size'
            char cipherText[size];           //The array stores the encrypted characters once the function 'railFence' has completed its algorithm

            printf("\nThe string was of length: %d\n\n", size);
            printf("Please enter message to encrypt:\n");

            fscanf(input, "%c", &c);              //Scans the input file and reads the first character in the file

            while(!feof(input))                    //Whilst there is still a character present (Including spaces and newlines), keep reading
            {
                message[i] = c;                 //Puts the first character of the file into the array strting at index '0'
                i++;                            //Increments the array index by 1
                fscanf(input, "%c", &c);        //Scans the input file again and reads the next character in the file
            }

            message[i] = 0;                     //Terminate the last scanned character in the array so the 'space' character is not included
            printf("%s\n", message);

            int len = stringLength(message);               //Function 'stringLength' is called to return the length of the inputed 'message', storing it as an integer


            FILE *PrimaryRailKey;                           //Pointer to a file "EnterTheKeyPrimaryRails" where the user puts in the number of primary rails they want for the encryption

            PrimaryRailKey = fopen("C:/Users/George/Downloads/EnterTheKeyPrimaryRails", "r");       //Opens the file and reads the number of rails the user has inputted

            if(PrimaryRailKey == NULL)              //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }

            fscanf(PrimaryRailKey, "%d", &x);       //Scans the integer number of rails and puts the number into a variable called 'x'

            while(x < 1)                               //If the number of rails is less than 1, the program terminates
            {
                printf("\nInvalid number, please enter again. Kill the program to restart\n");
                return 0;
            }

            railRowsPrimary = x;                      //Rail number is given to a variable 'railRowsPrimary' so it is easier to remember what the variable stores
            printf("\nEnter the number of primary rails:\n%d\n\n", railRowsPrimary);


            FILE *SecondaryRailKey;                 //Pointer to a file called "EnterTheKeySecondaryRails" where the user puts the number of secondary rails they want for the encryption

            SecondaryRailKey = fopen("C:/Users/George/Downloads/EnterTheKeySecondaryRails", "r");           //Opens the file and reads the number of secondary rails the user has inputted

            if(SecondaryRailKey == NULL)               //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }

            fscanf(SecondaryRailKey, "%d", &x2);        //Scans the integer number of secondary rails and puts the number into a variable called 'x2'


            railRowsSecondary = x2;                     //Rail number is given to a variable 'railRowsSecondary' so it is easier to remember what the variable stores
            printf("\nEnter the number of secondary rails:\n%d\n\n", railRowsSecondary);

            while(x2 <= 1)                 //The number of secondary rails must be greater than 1 as it has to be greater than the number of primary rails
            {
                printf("\nError: Secondary rails must be greater than 1, please enter again. Kill the program to restart\n");
                return 0;
            }

            while(railRowsSecondary >= railRowsPrimary)             //The number of secondary rails MUST be greater than the number of primary rails, otherwise it will ruin the encryption algorithm
            {
                printf("Error: Secondary rail must be less than primary. Please enter again. Kill the program to restart\n");
                return 0;
            }

            railFence2(message, cipherText, len, railRowsPrimary, railRowsSecondary, dir);          //The function 'railFence2' is called to perform the encryption algorithm for the 2-Level rail fence cipher


             FILE *output;           //Pointer to a file called "OutputDataAssignment.txt" where the program outputs the encrypted text
            output = fopen("C:/Users/George/Downloads/OutputDataAssignment.txt", "w");          //The pointer 'output' opens the file and writes the encrypted message in

            if(output == NULL)        //If there is no file present, produce an error statement
            {
                perror("fopen()");
            }


            int j = 0;
            printf("The encrypted message is:\n");
            for(j = 0; j < len; j++)                                //Loop until the end of the encrypted message is reached
            {
                    printf("%c", cipherText[j]);                    //Encrypted message is printed to the terminal
                    fprintf(output, "%c", cipherText[j]);           //The encrypted message is also printed to the file
            }
            printf("\n\n");

            break;                  //Allows the process to end after the encryption by getting out of the switch loop
        }





        case 3:                          //Case when option 3 is chosen (2-Level Rail fence cipher Decryption)
        {
            int railRowsPrimary;            //Variable to take user's input for the number of primary rails
            int railRowsSecondary;               //Variable to take user's input for the number of secondary rails
            int dir = 1;                         //Variable initialised to tell the function to perform Decryption
            int i = 0;                           //Variable used as a counter when counting how many characters are in the designated file
            int x = 0;                           //Variable to store the amount of primary rails used in the Decryption
            int x2 = 0;                          //Variable to store the amount of secondary rails used in the Decryption
            char c;                              //Is a variable to temporarily store each individual character in the message

            FILE *input;                //Pointer to a file called "InputDataAssignment.txt" where the user has inputed the text they want to decrypt

            input = fopen("C:/Users/George/Downloads/InputDataAssignment.txt", "r");       //The pointer 'input' opens the file and is set to read the message

            if(input == NULL)      //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }
                                                //We determine the size of the file and set the size of array before declaring it
            fseek(input, 0, SEEK_END);          //Denotes the end of the message and sets the position indicator
            int size = ftell(input);            //Returns the size of the message based on the two position indicators
            fseek(input, 0, SEEK_SET);          //Denotes the start of the message and sets the starting position indicator

            char message[size];      //The array 'message[]' stores the input characters from the designated file with array size 'size'
            char cipherText[size];           //The array stores the encrypted characters once the function 'railFence' has completed its algorithm

            printf("\nThe string was of length: %d\n\n", size);
            printf("Please enter message to decrypt:\n");

            fscanf(input, "%c", &c);              //Scans the input file and reads the first character in the file
            while(!feof(input))                //Whilst there is still a character present (Including spaces and newlines), keep reading
            {
                cipherText[i] = c;                 //Puts the first character of the file into the array strting at index '0'
                i++;                            //Increments the array index by 1
                fscanf(input, "%c", &c);        //Scans the input file again and reads the next character in the file
            }

            cipherText[i] = 0;                     //Terminate the last scanned character in the array so the 'space' character is not included
            printf("%s\n", cipherText);

            int len = stringLength(cipherText);             //Function 'stringLength' is called to return the length of the inputed 'message', storing it as an integer


            FILE *PrimaryRailKey;                           //Pointer to a file "EnterTheKeyPrimaryRails" where the user puts in the number of primary rails they want for the decryption

            PrimaryRailKey = fopen("C:/Users/George/Downloads/EnterTheKeyPrimaryRails", "r");       //Opens the file and reads the number of rails the user has inputted

            if(PrimaryRailKey == NULL)              //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }

            fscanf(PrimaryRailKey, "%d", &x);       //Scans the integer number of rails and puts the number into a variable called 'x'

            while(x < 1)                              //If the number of rails is less than 1, the program terminates
            {
                printf("\nInvalid number, please enter again. Kill the program to restart\n");
                return 0;
            }

            railRowsPrimary = x;                      //Rail number is given to a variable 'railRowsPrimary' so it is easier to remember what the variable stores
            printf("\nEnter the number of primary rails:\n%d\n\n", railRowsPrimary);



            FILE *SecondaryRailKey;                 //Pointer to a file called "EnterTheKeySecondaryRails" where the user puts the number of secondary rails they want for the decryption

            SecondaryRailKey = fopen("C:/Users/George/Downloads/EnterTheKeySecondaryRails", "r");           //Opens the file and reads the number of secondary rails the user has inputted

            if(SecondaryRailKey == NULL)               //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }

            fscanf(SecondaryRailKey, "%d", &x2);        //Scans the integer number of secondary rails and puts the number into a variable called 'x2'


            railRowsSecondary = x2;                     //Rail number is given to a variable 'railRowsSecondary' so it is easier to remember what the variable stores
            printf("\nEnter the number of secondary rails:\n%d\n\n", railRowsSecondary);

            while(x2 <= 1)                //The number of secondary rails must be greater than 1 as it has to be greater than the number of primary rails
            {
                printf("\nError: Secondary rails must be greater than 1, please enter again. Kill the program to restart\n");
                return 0;
            }

            while(railRowsSecondary >= railRowsPrimary)             //The number of secondary rails MUST be greater than the number of primary rails, otherwise it will ruin the decryption algorithm
            {
                printf("Error: Secondary rail must be less than primary. Please enter again. Kill the program to restart\n");
                return 0;
            }

            railFence2(message, cipherText, len, railRowsPrimary, railRowsSecondary, dir);          //The function 'railFence2' is called to perform the decryption algorithm for the 2-Level rail fence cipher



            FILE *output;           //Pointer to a file called "OutputDataAssignment.txt" where the program outputs the decrypted text
            output = fopen("C:/Users/George/Downloads/OutputDataAssignment.txt", "w");          //The pointer 'output' opens the file and writes the edecrypted message in

            if(output == NULL)        //If there is no file present, produce an error statement
            {
                perror("fopen()");
            }


            printf("\n\nThe decrypted message is:\n");
            int j = 0;

            for(j = 0; j < len; j++)                        //Loop until end of decrypted message is reached
            {
                printf("%c", message[j]);                   //Decrypted message is printed to the terminal
                fprintf(output, "%c", message[j]);          //The encrypted message is also printed to the file
            }
            printf("\n");
            break;                  //Allows the process to end after the encryption by getting out of the switch loop
        }





        case 4:
        {
            int i = 0;              //Variable used as a counter when counting how many characters are in the designated file
            char c;                              //Is a variable to temporarily store each individual character in the message

            FILE *input;                //Pointer to a file called "InputDataAssignment.txt" where the user has inputed the text they want to decrypt

            input = fopen("C:/Users/George/Downloads/InputDataAssignment.txt", "r");       //The pointer 'input' opens the file and is set to read the message

            if(input == NULL)      //If the file does not exist, print out a message which says it does not exist
            {
                perror("fopen()");
                return 0;
            }
                                                //We determine the size of the file and set the size of array before declaring it
            fseek(input, 0, SEEK_END);          //Denotes the end of the message and sets the position indicator
            int size = ftell(input);            //Returns the size of the message based on the two position indicators
            fseek(input, 0, SEEK_SET);          //Denotes the start of the message and sets the starting position indicator

            char message[size];               //The array 'message[]' stores the input characters from the designated file with array size 'size'
            char cipherText[size];           //The array stores the encrypted characters once the function 'railFence' has completed its algorithm

            printf("The string was of length: %d\n\n", size);
            printf("Please enter substitution cipher to decrypt:\n");

            fscanf(input, "%c", &c);              //Scans the input file and reads the first character in the file
            while(!feof(input))                //Whilst there is still a character present (Including spaces and newlines), keep reading
            {
                message[i] = c;                 //Puts the first character of the file into the array strting at index '0'
                i++;                            //Increments the array index by 1
                fscanf(input, "%c", &c);        //Scans the input file again and reads the next character in the file
            }

            message[i] = 0;                     //Terminate the last scanned character in the array so the 'space' character is not included
            printf("%s\n", message);


            int len = stringLength(message);               //Function 'stringLength' is called to return the length of the inputed 'message', storing it as an integer
            Words(message, cipherText, len);                   //The function 'Words' is called to perform the decryption algorithm for the substitution cipher
            break;                              //Allows the process to end after the encryption by getting out of the switch loop
        }

    }
}





int stringLength(char *message)         //Function determines the length of the message
{
    int column = 0;                   //Initialise integer variable to keep track of the array index number starting at 0
    while(message[column] != 0)       //Whilst there is still a character present (Including spaces), increment the amount of columns by 1
    {
        column++;                     //Incrementing the index number in the array by 1
    }
    return column;                  //Returns the number of characters / length of the message
}



/***********************************************************************************************************************
BLOCK COMMENT FOR FUNCTION DEFINITION: railFence
FUNCTION PERFORMS: Classical rail fence cipher Encryption

The inputs for the function "railFence" are the message to be encrypted and the number of primary rails. These are
entered into files by the user before the program is executed. The return value is the encrypted message which is
printed to the output file and to the terminal. The function performs the classical rail fence cipher encryption and
outputs both the written encrypted text and the visual encrypted text with the rails. The function can accept multiple
lines of text and treats the 'newline' character (Line feed) as a NULL character, so the string can continue to read
the message. The string must be less than 1000000 char characters and can take letters both lower case and
upper case, punctuation, spaces, numbers and other special characters.
***********************************************************************************************************************/


void railFence(char *message, char *cipherText, int length, int A)          //Function performs classical rail fence encryption
{
    int row = 0, column = 0;        //Row and column number creates a 2D array initialised at index (0,0)
    char grid[length][A];           //A working grid is created consisting of a fixed number of rows 'A' and a set number of columns 'length'
                                    //The variable 'length' signifies the length of the message and variable 'A' signifies the number of rail rows specified by the user
    for(row = 0; row < A; row++)
    {
        for(column = 0; column < length; column++)
        {
            grid[column][row] = 0;              //The two loops with 'row' and 'column' zero all the elements in the array
        }
    }

    column = 0, row = 0;                         //Re-initalise column & row number to the first array element (0,0)
    int counter = 0;                            //Variable is used to switch the direction of the rails from top-to-bottom, bottom-to-top, top-to-bottom and so on

    while(column < length)                         //Whilst there is still a character present in the array, continue the encryption algorithm
    {
        if(counter%2 == 0)                         //When counter number is even or 0, the grid moves down from top left to bottom right
        {
            for(row = 0; row < A; row++)               //The number of rows is incremented for each column until the max number of rows is reached (Reached the bottom of the array)
            {
               if(column == length)                    //So the program does not access an element outside the array
                {
                    break;
                }

                grid[column][row] = message[column];                 //For each column number corresponding to a row number, a letter is being filled in the array diagonally from top left to bottom right
                column++;                                       //Column number increments so array is filled from left to right
            }
        }

        else                                                     //When counter number is odd, the grid moves upward from bottom left to top right
        {
            for(row = A-1-1; row > 0; row--)        //The number of rows is decremented for each column until the 1st row is reached
            {
                                                    //We minus 1 because we move 1 row up and minus 1 again as the array starts at (0,0) instead of (1,1)
                if(column == length)              //So the program does not access an element outside the array
                {
                    break;
                }

                grid[column][row] = message[column];           //For each column number corresponding to a row number, a letter is being filled in the array diagonally from bottom left to top right
                column++;                                     //Column number increments so array is filled from left to right
            }
        }

        counter++;                               //We increment the count number by 1, to change the diagonal direction of where the numbers are placed in the array
    }



    int j = 0;
    for(row = 0; row < A; row++)            //For each row, column number is incremented to fill in the array with letters for when the index number does not have a 0
    {
        for(column = 0; column < length; column++)
        {
            if(grid[column][row] != 0)         //Allows the letters to be placed in a diagonal order, from top left to bottom right, then bottom left to top right and so on
            {
                cipherText[j] = grid[column][row];          //Fills the cipherText array with the correct encrypted message

                if(grid[column][row] == 10)                //When the grid encounters a new line character (Line feed)
                {
                    grid[column][row] = NULL;       //Leaves the 'newline' character in place so the same amount of lines of message are printed to the file and the terminal
                }
                j++;
            }
        }
    }


    printf("\n\n");
                                            //We now print out the encryption in visual format to the terminal as a comparison to the written encrypted text
    for(row = 0; row < A; row++)            //For each row, column number is incremented to fill in the array with letters for when the index number grid is not 'zeroed'
    {
        for(column = 0; column < length; column++)
        {
            if(grid[column][row] != 0)
            {
              printf("%c", grid[column][row]);   //We print out all the numbers that are not zeroed, I.e the numbers which only go in a zig-zag pattern starting from top left to bottom right
            }

            if(grid[column][row] == 0)          //Places dots in places where there is a zero in the array
            {
                printf(".");
            }
        }
        printf("\n");
    }
}




/**********************************************************************************************************************
BLOCK COMMENT FOR FUNCTION DEFINITION: railFence2
FUNCTION PERFORMS: 2-Level Rail Fence cipher Encryption or Decryption

It is noted that the function "railFence2" contains both the encryption and decryption for the 2-Level Rail Fence cipher.
To decide on which one it executes when option 2 or 3 is chosen, a variable 'dir' is used. When option 2 is chosen,
dir = 0 and when option 3 is chosen, dir = 1. This allows 'if' statements to be used to control if encryption or
decryption is executed.

When dir = 0, the 2-Level rail fence cipher encryption is executed. The inputs for the function are the message to be
encrypted, the number of primary rails and the number of secondary rails. These are entered into files by the user
before the program is executed. The return value is the encrypted message which is printed to the output file and to the
terminal. The visual encrypted text with the rails is also outputted to the terminal. THe function can accept multiple
lines of text and treats the 'newline' character (Line feed) as a NULL character, so the string can continue to read
the message. The string must be less than 1000000 char characters and can take letters both lower case and upper case,
punctuation, spaces, numbers and other special characters.

When dir = 1, the 2-Level rail fence cipher decryption is executed. The inputs for the function are the message to be
decrypted, the number of primary rails and the number of secondary rails. These are entered into files by the user
before the program is executed. This is one of the limitations as the key for both primary rails and secondary rails
needs to be known, otherwise the program cannot decrypted properly. The return value is the decrypted message which is
printed to the output file and to the terminal. The visual decrypted text with the rails is also outputted to the
terminal. The function can accept multiple lines of text and treats the 'newline' character (Line feed) as a NULL
character, so the string can continue to read the message. The string must be less than 1000000 char characters and can
take letters both lower case and upper case, punctuation, spaces, numbers and other special characters.
***********************************************************************************************************************/


void railFence2(char *message, char *cipherText, int length, int A, int B, int dir)         //Function either performs the 2-Level rail fence Encryption or the 2-Level rail fence Decryption, which is dependent on the 'dir' variable as chosen by the user
{
    if(dir == 0)            //Perform encryption of double rail cipher
    {
        int row = 0, column = 0;        //Row and column number creates a 2D array initialised at index (0,0)
        char grid[length][A];           //A working grid is created consisting of a fixed number of rows 'A' and a set number of columns 'length'
                                    //The variable 'length' signifies the length of the message and variable 'A' signifies the number of rail rows specified by the user
        for(row = 0; row < A; row++)
        {
            for(column = 0; column < length; column++)
            {
                grid[column][row] = 0;          //The two loops with 'row' and 'column' zeroes all the elements in the array
            }
        }

        column = 0, row = 0;                         //Initalise column & row number to the first array element (0,0)
        int counter1 = 0, counter2 = 0;             //Variables act as flags to determine which direction to go and to determine if the primary rails or secondary rails has to move next


        while(column < length)             //Whilst there is still a character present in the array, continue the encryption algorithm
        {
            if(counter1 == 0 && counter2 == 0)           //This is when the primary rails go from top left to bottom right in the array grid (The BIG down)
            {
                if(column < length)                      //Whilst there is still a character present in the array, continue the encryption algorithm
                {
                    for(row = 0; row < A; row++)            //The number of rows is incremented for each column until the max number of rows is reached
                    {
                        if(column == length)                 //So the program does not access an element outside the array
                        {
                            break;
                        }

                        grid[column][row] = message[column];                 //For each column number corresponding to a row number, a letter is being filled in the array diagonally from bottom left to top right
                        column++;                                           //Column number increments so array is filled from left to right
                    }
                    counter1++;                 //The flag 'counter1' is incremented so that the secondary rails can start moving after the primary rails have finished putting their letters in
                }

                else                       //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1 == 1 && counter2 == 0)            //This is when the secondary rails go from bottom left to top right in the array grid, continuing the grid from the primary rails (The SMALL up)
            {
                if(column < length)                    //Whilst there is still a character present in the array, continue the encryption algorithm
                {
                    for(row = A - 1 - 1; row > A - B; row--)   //The number of rows is decremented for each column until the 1st row for the secondary rails is reached
                    {                                  //We minus 1 because we move 1 row up and minus 1 again as the array starts at (0,0) instead of (1,1) for the secondary rails
                        if(column == length)              //So the program does not access an element outside the array
                        {
                            break;
                        }

                        grid[column][row] = message[column];                 //For each column number corresponding to a row number, a letter is being filled in the array
                        column++;                                           //Column number increments so array is filled from left to right
                    }
                    counter1--;             //The flag 'counter1' is decremented & the flag 'counter2' is incremented so that the secondary rails can start moving downwards after it has reached the top of the row
                    counter2++;
                }

                else              //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1%2 == 0 && counter2%2 == 1)             //This is when the secondary rails go from top left to bottom right in the array grid, continuing the grid from the secondary rails (The SMALL down)
            {
                if(column < length)                        //Whilst there is still a character present in the array, continue the encryption algorithm
                {
                    for(row = A - B; row < A - 1; row++)           //The difference between the primary and secondary rows (A - B) will give the 1st row number of the secondary rails
                    {
                        if(column == length)            //So the program does not access an element outside the array
                        {
                            break;
                        }
                        grid[column][row] = message[column];                 //For each column number corresponding to a row number, a letter is being filled in the array
                        column++;                                           //Column number increments so array is filled from left to right
                    }
                    counter1++;                     //The flag 'counter1' is incremented so that the primary rails can start moving after the secondary rails have finished putting their letters in
                }
                else                    //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1 == 1 && counter2 == 1)           //This is when the primary rails go from bottom left to top right in the array grid, continuing the grid from the secondary rails (The BIG up)
            {
                if(column < length)
                {
                    for(row = A - 1; row > 0; row--)          //The row number 'A - 1' is when the primary rails start from the bottom row
                    {
                        if(column == length)               //So the program does not access an element outside the array
                        {
                            break;
                        }

                        grid[column][row] = message[column];                 //For each column number corresponding to a row number, a letter is being filled in the array
                        column++;                                           //Column number increments so array is filled from left to right
                    }

                    counter1--;                     //The flag 'counter1' & 'counter2' is decremented  so that the primary rails can start moving downwards after it has reached the top of the row
                    counter2--;
                }
                else                   //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }
        }






        int j = 0;
        for(row = 0; row < A; row++)            //For each row, column number is incremented to fill in the array with letters for when the index number does not have a 0
        {
            for(column = 0; column < length; column++)
            {
                if(grid[column][row] != 0)         //Allows the letters to be placed in a diagonal order, from top left to bottom right, then bottom left to top right and so on
                {
                    cipherText[j] = grid[column][row];      //Fills the cipherText array with the correct encrypted message


                    if(grid[column][row] == 10)                //When the grid encounters a new line character (Line feed)
                    {
                        grid[column][row] = NULL;       //Leaves the 'newline' character in place so that there are the same amount of lines which are printed to the file and the console
                    }
                    j++;
                }
            }
        }



        printf("\n\n");


                    //We now print out the encryption in visual format to the terminal as a comparison to the written encrypted text
        for(row = 0; row < A; row++)            //For each row, column number is incremented to fill in the array with letters for when the index number grid is not 'zeroed'
        {
            for(column = 0; column < length; column++)
            {
                if(grid[column][row] != 0)
                {
                printf("%c", grid[column][row]);   //We print out all the numbers that are not zeroed, I.e the numbers which only go in a zig-zag pattern starting from top left to bottom right
                }

                if(grid[column][row] == 0)          //Places dots in places where there is a zero in the array
                {
                    printf(".");
                }
            }
            printf("\n");
        }
    }






    else if(dir == 1)           //Perform decryption of double rail cipher
    {
        int row = 0, column = 0;        //Row and column number creates a 2D array initialised at index (0,0)
        char grid[length][A];           //A working grid is created consisting of a fixed number of rows 'A' and a set number of columns 'length'
                                    //The variable 'length' signifies the length of the message and variable 'A' signifies the number of rail rows specified by the user
        for(row = 0; row < A; row++)
        {
            for(column = 0; column < length; column++)
            {
            grid[column][row] = 0;          //The two loops with 'row' and 'column' zeroes all the elements in the array
            }
        }


        column = 0, row = 0;                         //Initalise column & row number to the first array element (0,0)
        int counter1 = 0, counter2 = 0;             //Variables act as flags to determine which direction to go and to determine if the primary rails or secondary rails has to move next


        while(column < length)                 //Whilst there is still a character present in the array, continue to fill the array from left to right
        {
            if(counter1 == 0 && counter2 == 0)          //This is when the primary rails go from top left to bottom right in the array grid (The BIG down)
            {
                if(column < length)                        //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = 0; row < A; row++)                                      //The number of rows is incremented for each column until the max number of rows is reached
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }
                        grid[column][row] = 1;               //For each column number corresponding to a row number, the array is filled with 1's to highlight where the letters will be placed
                        column++;                               //Column number increments so array is filled from left to right
                    }
                    counter1++;                         //The flag 'counter1' is incremented so that the secondary rails can start moving after the primary rails have finished putting their letters in
                }

                else                               //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1 == 1 && counter2 == 0)               //This is when the secondary rails go from bottom left to top right in the array grid, continuing the grid from the primary rails (The SMALL up)
            {
                if(column < length)                            //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - 1 - 1; row > A - B; row--)       //The number of rows is decremented for each column until the 1st row for the secondary rails is reached
                    {                                        //We minus 1 because we move 1 row up and minus 1 again as the array starts at (0,0) instead of (1,1) for the secondary rails
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }
                        grid[column][row] = 1;                    //For each column number corresponding to a row number, the array is filled with 1's to highlight where the letters will be placed
                        column++;                                   //Column number increments so array is filled from left to right
                    }
                    counter1--;                         //The flag 'counter1' is decremented & the flag 'counter2' is incremented so that the secondary rails can start moving downwards after it has reached the top of the row
                    counter2++;
                }
                else                       //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1%2 == 0 && counter2%2 == 1)           //This is when the secondary rails go from top left to bottom right in the array grid, continuing the grid from the secondary rails (The SMALL down)
            {
                if(column < length)                          //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - B; row < A - 1; row++)           //The difference between the primary and secondary rows (A - B) will give the 1st row number of the secondary rails
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }
                        grid[column][row] = 1;                  //For each column number corresponding to a row number, the array is filled with 1's to highlight where the letters will be placed
                        column++;                               //Column number increments so array is filled from left to right
                    }
                    counter1++;                             //The flag 'counter1' is incremented so that the primary rails can start moving after the secondary rails have finished putting their letters in
                }
                else                                //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1 == 1 && counter2 == 1)           //This is when the primary rails go from bottom left to top right in the array grid, continuing the grid from the secondary rails (The BIG up)
            {
                if(column < length)                //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - 1; row > 0; row--)               //The row number 'A - 1' is when the primary rails start from the bottom row
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }
                        grid[column][row] = 1;                  //For each column number corresponding to a row number, the array is filled with 1's to highlight where the letters will be placed
                        column++;                               //Column number increments so array is filled from left to right
                    }
                    counter1--;                 //The flag 'counter1' & 'counter2' is decremented  so that the primary rails can start moving downwards after it has reached the top of the row
                    counter2--;
                }
                else                         //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }
        }


        int k = 0, j = 0;          //We need a new integer in order put each individual letter in the encrypted message to replace the 1's in the array
        for(row = 0; row < A; row++)
        {
            for(column = 0; column < length; column++)
            {
                if(grid[column][row] != 0)                 //Places the letters in the places where there are 1's in the array
                {
                    grid[column][row] = cipherText[k];     //'k' is used instead of 'column' to make sure that each character is entered in the correct spot, replacing the 1's from left to right in each row
                    k++;                                    //k is incremented to access the next character in the message
                }
            }
        }



        column = 0; row = 0;                //Reinitialise column, row, counter1 and counter2 in order to read the encrypted message from left-to-right, top-to-bottom in a diagonal direction as a 2D grid/array
        counter1 = 0; counter2 = 0;


        while(column < length)
        {
            if(counter1 == 0 && counter2 == 0)                          //This is when the primary rails go from top left to bottom right in the array grid (The BIG down)
            {
                if(column < length)                                        //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = 0; row < A; row++)                                      //The number of rows is incremented for each column until the max number of rows is reached
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }

                        message[column] = grid[column][row];

                        if(grid[column][row] == 10)            //When a newline character is detected (Line feed)
                        {
                            grid[column][row] = NULL;       //Leaves the 'newline' character in place so that there are the same amount of lines which are printed to the file and the console
                        }

                        column++;               //Column number increments so array is filled from left to right
                    }
                    counter1++;             //The flag 'counter1' is incremented so that the secondary rails can start moving after the primary rails have finished putting their letters in
                }

                else               //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }

            if(counter1 == 1 && counter2 == 0)             //This is when the secondary rails go from bottom left to top right in the array grid, continuing the grid from the primary rails (The SMALL up)
            {
                if(column < length)                    //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - 1 - 1; row > A - B; row--)       //The number of rows is decremented for each column until the 1st row for the secondary rails is reached
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }

                        message[column] = grid[column][row];

                        if(grid[column][row] == 10)            //When a newline character is detected (Line feed)
                        {
                            grid[column][row] = NULL;            //Leaves the 'newline' character in place so that there are the same amount of lines which are printed to the file and the console
                        }

                        column++;               //Column number increments so array is filled from left to right
                    }
                    counter1--;             //The flag 'counter1' is decremented & the flag 'counter2' is incremented so that the secondary rails can start moving downwards after it has reached the top of the row
                    counter2++;
                }
                else           //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }


            if(counter1%2 == 0 && counter2%2 == 1)                     //This is when the secondary rails go from top left to bottom right in the array grid, continuing the grid from the secondary rails (The SMALL down)
            {
                if(column < length)                        //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - B; row < A - 1; row++)       //The difference between the primary and secondary rows (A - B) will give the 1st row number of the secondary rails
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }

                        message[column] = grid[column][row];

                        if(grid[column][row] == 10)        //When a newline character is detected (Line feed)
                        {
                            grid[column][row] = NULL;         //Leaves the 'newline' character in place so that there are the same amount of lines which are printed to the file and the console
                        }

                        column++;                       //Column number increments so array is filled from left to right
                    }
                    counter1++;         //The flag 'counter1' is incremented so that the primary rails can start moving after the secondary rails have finished putting their letters in

                }
                else                //When the end of the array is reached, the program breaks out of the loop
                {
                break;
                }
            }


            if(counter1 == 1 && counter2 == 1)              //This is when the primary rails go from bottom left to top right in the array grid, continuing the grid from the secondary rails (The BIG up)
            {
                if(column < length)                    //Whilst there is still a character present in the array, continue the decryption algorithm
                {
                    for(row = A - 1; row > 0; row--)            //The row number 'A - 1' is when the primary rails start from the bottom row
                    {
                        if(column == length)           //So the program does not access an element outside the array
                        {
                            break;
                        }

                        message[column] = grid[column][row];

                        if(grid[column][row] == 10)            //When a newline character is detected (Line feed)
                        {
                            grid[column][row] = NULL;           //Leaves the 'newline' character in place so that there are the same amount of lines which are printed to the file and the console
                        }

                        column++;           //Column number increments so array is filled from left to right
                    }
                    counter1--;                 //The flag 'counter1' & 'counter2' is decremented  so that the primary rails can start moving downwards after it has reached the top of the row
                    counter2--;
                }

                else               //When the end of the array is reached, the program breaks out of the loop
                {
                    break;
                }
            }
        }
        printf("\n");
    }
}





/***********************************************************************************************************************
BLOCK COMMENT FOR FUNCTION DEFINITION: Words
FUNCTION PERFORMS: Substitution cipher decryption

The input for the "Words" function is the substitution text to be decrypted with no key inputted by the user. The
function works by analyzing the frequency and position of each letter in the message, keeping the punctuation, spaces
and other special characters unchanged. It then utilizes several methods to help decipher the text, using letter
frequency tables, substituting the most common letters used in the English language for the most common letters in the
encrypted text. Using the knowledge of common three letter words such as "the", two letter words such as "to" and single
letter words such as "I" and "a". Based on this complex algorithm, the program provides the best estimation for what the
letters in the encrypted message should be substituted with other letters in the alphabet. The function can accept
multiple lines in the message. There are limitations with this function however, it needs a long block of text to
get a more accurate estimation of each letter. The algorithm relies on the frequency of each occurring letter or word.
The function can only decipher lower case letters and not upper case letters.
***********************************************************************************************************************/

void Words(char *message, char cipherText, int length)                 //Function performs substitution decryption
{
    int column = 0;                 //Acts as a counter to count each letter of the alphabet a-z
    int noCharacters = 0;           //Variable to store the spaces between words
    int characters = 0;             //Variable to store the characters which are letters
    int letterCount[26];      //Array to count the frequency of each letter a to z


    for(column = 0; column < 26; column++)
    {
        letterCount[column] = 0;                //All the elements/characters in the array are zeroed so the letters can be put in for decryption later
    }


    for(column = 0; column < length; column++)         //Counts the frequency of each letter used in the array
    {
        if(message[column] != " ")                     //So any spaces are not counted in the array and are left as it is
        {
            characters = message[column] - 97;         //We minus 97 to access the range of ASCII letters a to z
            if(characters >= 0 && characters < 26)      //Prevents access to non-existent parts of the array
            {
                letterCount[characters]++;              //Increment element in array by 1 for each letter, storing the frequency of each letter used
            }

            else
            {
                noCharacters++;                 //Counts the amount of spaces between the words
            }
        }
    }

    char columnLetter[26];          //Array to store each letter in a corresponding column number

    printf("\nFrequency of each letter:\n");
    for(column = 0; column < 26; column++)              //Prints the frequency of each letter used in the encrypted message
    {
        columnLetter[column] = column + 97;             //We plus 97 to access the range of ASCII letters a to z
        printf("%c: %d\n", columnLetter[column], letterCount[column]);          //Print out the chosen letter along with the frequency of that letter in the message
    }


    int i, j, tmp, tmpLetter;       //Integers are introduced to aid in rearranging the frequency of letters in descending order

    for(i = 0; i < 26; i++)                    //Rearrange the array to highlight frequency of letters in descending order from a-z
    {
        for(j = 0; j < 26; j++)                //'i' loop represents the current letter being analysed, whilst 'j' loop represents the letters being compared to it
        {
            if(letterCount[j] < letterCount[i])        //If the count of one letter is less than the count of the  letter, rearrange the order to put the lower number count below the higher one
            {
                tmp = letterCount[i];             //We use a temporary variable to store the frequency of the most used letter
                tmpLetter = columnLetter[i];        //We use another temporary variable to store the actual letter that is most frequently used
                columnLetter[i] = columnLetter[j];      //The more frequent letter gets replaced with the 2nd most frequent letter
                letterCount[i] = letterCount[j];        //The more frequent letter gets replaced with the 2nd most frequent letter
                letterCount[j] = tmp;              //The most frequent letter then moves into array index 0, 2nd frequent letter in array index 1 and so on
                columnLetter[j] = tmpLetter;       //The most frequent letter then moves into array index 0, 2nd frequent letter in array index 1 and so on
            }
        }
    }


    char FrequentLettersUsed[26] = "etaoinsrhldcumfpgwybvkxjqz";                    //According to statistics, we store the most frequent letters used in English in descending order into an array

    printf("\n\nMost common letters in descending order:\n");
    for(i = 0; i < 26; i++)                                           //For each letter starting from the most frequent to the least frequent letter
    {
        printf("%c %d\n", columnLetter[i], letterCount[i]);            //Prints the letter with the highest frequency in descending order
    }

    printf("\n\n");


    FILE *output;                           //Pointer to a file called "OutputDataAssignment.txt" where the program outputs the decrypted text
    output = fopen("C:/Users/George/Downloads/OutputDataAssignment.txt", "w");          //The pointer 'output' opens the file and writes the decrypted message in

    if(output == NULL)        //If there is no file present, produce an error statement
    {
        perror("fopen()");
    }

    for(column = 0; column < length; column++)         //Loop enables the most frequent letter used in the encrypted message to be replaced with the most frequent letter in the english language 'e', the 2nd most frequent letter replaced by 't', 3rd most frequent letter replaced by 'a' and etc.
    {
        for(i = 0; i < 26; i++)                //Loop checks to see if the letter used in the encrypted message corresponds to the frequency of that letter, going through the alphabet a to z to check
        {
            if(columnLetter[i] == message[column])         //When the frequency of the letter in the encrypted message correpsonds to the frequency of the letter according to the English language
            {
                message[column] = FrequentLettersUsed[i];     //Once the correct letter is found, it is substituted in
                break;                      //Once the letter to replace in the encrypted message has been found and substituted, the next letter is scanned through by breaking the loop
            }
        }
    }



    for(column = 0; column < length; column++)
    {
        printf("%c", message[column]);             //Prints out all the decrypted letters in the message
        fprintf(output, "%c", message[column]);     //Prints out all the decrypted letters in the message to the specified file
    }
    printf("\n\n");

}

