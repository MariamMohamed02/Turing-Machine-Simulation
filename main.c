 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function declaration
void inputString(char ***parsed_array);
int inputNumber();
void getTape(char **tape);
void generateTransitions(int num_states, int num_transitions, char transition[][5],char **machine_symbols);
void parseString(char *input, char parsed[][20], int *num_parts);
void turingMachine(int num_states, int num_transitions, char transition[][5],char **machine_symbols, int head_position, char **tape,int initial_state);
void encodeTM(int num_states, int num_transitions, char transition[][5],char **machine_symbols,int initial_state);

int main() {
    char **machine_symbols = NULL;  // Pointer to an array of strings (char pointers)
    char *tape = NULL;  // Pointer to an array of characters (string)
    int initial_state;
    int num_states;
    int head_position;
    int num_transitions;
    int num_symbols=0;
    char actions[4] = {'l', 'r', 'y', 'n'};


    printf("Universal Turing Machine Simulation\n");
    printf("----------------------------------------\n");
    printf("Assumptions made: \n");
    printf("1- The tape is zero indexed, ie: Index 0 has the first input symbol you entered\n");
    printf("2- Do not enter the '<' mark as it is already added in the code\n");
    printf("The states are numbered as: 0, 1, 2,etc.. state 0 being the first state\n");


    printf("----------------------------------------\n");
    printf("Enter the Number of States: ");
    num_states = inputNumber();

    printf("----------------------------------------\n");
    // Call the inputMachineSymbols function
    inputMachineSymbols(&machine_symbols);
    for (int i = 0; machine_symbols[i] != NULL; i++) {
            num_symbols++;
    }

    printf("Enter the Initial State: ");
    initial_state = inputNumber();

    printf("----------------------------------------\n");

    printf("Enter the Head Position:");
    head_position = inputNumber();

    printf("----------------------------------------\n");

    //Calculate Number of Transitions
    num_transitions= num_symbols*num_states;
    char transition[num_transitions][5];

    // Call the getTape function
    getTape(&tape);

    printf("----------------------------------------\n");
    //Call the getTransition Function
    generateTransitions(num_states, num_transitions, transition, machine_symbols);

    //Apply Turing Machine Function to the tape.
    printf("----------------------------------------\n");
    turingMachine(num_states, num_transitions, transition, machine_symbols,head_position,&tape,initial_state);

    printf("----------------------------------------\n");
    encodeTM(num_states, num_transitions, transition, machine_symbols,initial_state);



    // FREE MEMORY
    for (int i = 0; machine_symbols[i] != NULL; i++) {
        free(machine_symbols[i]);  // Free each symbol's allocated memory
    }
    free(machine_symbols);  // Free the array of pointers
    free(tape); // Free the memory allocated for the tape


    return 0;
}

// inputNumber Function Definition
int inputNumber() {
    int num;
    num=getchar();
    getchar();
    num=atoi((char *)&num);
    return num;
}



// inputMachineSymbol Function definition
void inputMachineSymbols(char ***parsed_array) {
    char input[1024];  // Buffer to hold the user input
    int count = 0;  // Number of parsed parts

    printf("Enter the machine symbols, separating the symbols with a comma: \n");
    printf("Example: a,b,c,# \n");
    printf("Machine Symbols: ");
    if (fgets(input, sizeof(input), stdin)) {
        // Remove the newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Parse the input
        char *token = strtok(input, ",");
        while (token != NULL) {
            // Dynamically allocate or resize the parsed_array
            char **temp = realloc(*parsed_array, (count + 2) * sizeof(char *));
            if (temp == NULL) {
                perror("Failed to realloc memory");
                // Free memory allocated so far
                for (int i = 0; i < count; i++) {
                    free((*parsed_array)[i]);
                }
                free(*parsed_array);
                exit(EXIT_FAILURE);
            }
            *parsed_array = temp;

            // Allocate memory for the current token and add it to the array
            (*parsed_array)[count] = malloc(strlen(token) + 1);
            if ((*parsed_array)[count] == NULL) {
                perror("Failed to allocate memory for token");
                // Free memory allocated so far
                for (int i = 0; i < count; i++) {
                    free((*parsed_array)[i]);
                }
                free(*parsed_array);
                exit(EXIT_FAILURE);
            }

            strcpy((*parsed_array)[count], token);
            count++;

            // Get next token
            token = strtok(NULL, ",");
        }
        // Set the last element of the array to NULL as a sentinel value
        (*parsed_array)[count] = NULL;
    }


}

// Function definition to get the tape from the user
void getTape(char **tape) {
    char input[1024];  // Buffer to hold the user input

    // Prompt the user to enter the tape
    printf("Enter the tape: ");
    if (fgets(input, sizeof(input), stdin)) {
        // Remove the newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Allocate memory for the tape array
        *tape = malloc(strlen(input) + 1);
        if (*tape == NULL) {
            perror("Failed to allocate memory for tape");
            exit(EXIT_FAILURE);
        }

        // Copy each character of the input string to the tape array
        for (int i = 0; input[i] != '\0'; i++) {
            (*tape)[i] = input[i];
        }
        (*tape)[strlen(input)] = '\0';  // Null-terminate the tape array
    }
}

void generateTransitions(int num_states, int num_transitions, char transition[][5], char **machine_symbols) {
     int state = 0;
    int symbol = 0;
    int counter = 0;

    // FILL THE FIRST AND SECOND COLUMNS
    for (int i = 0; i < num_transitions; i++) {
        transition[i][0] = state;
        counter++;
        transition[i][1] = machine_symbols[symbol][0]; // Assign the first character of machine symbol
        symbol++;

        if (counter % (num_transitions / num_states) == 0) {
            counter= 0;
            state++;
            symbol = 0;
        }



}

    char input[100];       // Assuming the input string will not exceed 100 characters
    char parsed[3][20];    // Assuming each transition string will have 3 parts, each with a maximum length of 20 characters
    int num_parts;         // Number of parts in the parsed string
    // Loop to get transitions from the user
    printf("For each (current state,current symbol) displayed, type the (new state, new symbol, action)\n");
    printf("For example: 1,a,r\n");
    printf("Enter the Transition Function Below: \n");
    for (int i = 0; i < num_transitions; i++) {
        // Input a string from the user
        printf("(%d %c)->" , transition[i][0],transition[i][1]);
        fgets(input, sizeof(input), stdin);
        // Call the parseString function to parse the input string
        parseString(input, parsed, &num_parts);
        // Store the parsed parts in the transition array
        transition[i][2] = parsed[0][0];  // First part
        transition[i][3] = parsed[1][0];  // Second part
        transition[i][4] = parsed[2][0];  // Third part
}
}

void parseString(char *input, char parsed[][20], int *num_parts) {
    int i = 0;  // Index for the input string
    int j = 0;  // Index for the parsed string
    int k = 0;  // Index for the current part of the parsed string

    // Loop through each character of the input string
    while (input[i] != '\0') {
        // If the current character is not a comma and not the end of the line, add it to the current part
        if (input[i] != ',' && input[i] != '\n') {
            parsed[j][k] = input[i];
            k++;
        } else {
            // If a comma or end of the line is encountered, terminate the current part with a null character
            parsed[j][k] = '\0';
            j++;  // Move to the next part in the parsed string
            k = 0;  // Reset the index for the current part
        }
        i++;  // Move to the next character in the input string
    }

    // Update the number of parts
    *num_parts = j;
}

void turingMachine(int num_states, int num_transitions, char transition[][5], char **machine_symbols, int head, char **tape, int initial_state) {
    int current_state = initial_state;
    char current_symbol=(*tape)[0];
    int tape_size = strlen(*tape);
    char new_tape[100]; // Assuming the maximum size of the tape is 100
    char action='y';
    int new_state;
    char new_symbol;

    for (int i = 0; i < 100; i++) {
    new_tape[i] = '#';
}

    //Fill New Array
    new_tape[0] = '<';
    // Copy the content of the tape to the new tape
    for (int i = 1; i <= tape_size; i++) {
        new_tape[i] = (*tape)[i - 1];
    }

    head++; // head on first input symbol since now array starts with <
    printf("Initial: (%d, %s), Head On index: %d\n",current_state,(*tape),head );

    do{



        //Find Corresponding Transition
        for(int i=0; i<num_transitions;i++){
                if (transition[i][0]==current_state && transition[i][1]==current_symbol){

                    new_state=transition[i][2];
                    new_symbol=transition[i][3];
                    action=transition[i][4];

                    printf("Apply: (%d %c)-->(%c %c %c)\n",transition[i][0],transition[i][1],transition[i][2],transition[i][3],transition[i][4]);
                    break;
                }

        }


        new_tape[head]=new_symbol;
        current_state=new_state - 48;
        if(action=='l')
            {head--;
            current_symbol=new_tape[head];}
        else if(action=='r')
            {head++;
            current_symbol=new_tape[head];}
        else if(action=='y'){
            printf("Input Tape Accepted\n");
            printf("For Input Tape: %s, Output is: %s\n",tape, new_tape);
            break;
        }
        else if (action=='n')
            {
                printf("Input Tape Rejected or Error Occured\n");

                break;
            }

         printf("Current: (%d, %s)\n",current_state,new_tape);
         printf("Head On index: %d\n",head );

    }
    while(action=='r' || action=='l');

}

void encodeTM(int num_states, int num_transitions, char transition[][5], char **machine_symbols ,int initial_state) {
    printf("\nEncoded Turing Machine:\n");

    int blank=0;
    printf("States:\n");
    for (int i = 0; i < num_states; i++) {
        printf("State %d -> ", i);

        for (int j = 0; j <= i; j++) {
            printf("1");
        }
        printf(" , ");
    }

    printf("\nInput Symbols:\n");
    for (int i = 0; machine_symbols[i] != NULL; i++) {
    blank++;
        printf("%s -> ", machine_symbols[i]);
        for (int j = 0; j <= i; j++) {
            printf("1");

        }
        printf(" , ");
    }

    printf("\nMachine Symbols:\n");
    for (int i = 0; machine_symbols[i] != NULL; i++) {
            if (strcmp(machine_symbols[i], "#") == 0)
            {
                //printf("here");
                 continue;
            }

        printf("%s -> ", machine_symbols[i]);
        for (int j = 0; j <= i; j++) {
            printf("1");
        }
        printf(" , ");
    }

    printf("\n Initial State:\n");
    //printf("\nStates:\n");
    for (int i = 0; i <= initial_state; i++) {
            printf("1");
    }



    // Encode transitions
    printf("\nTransitions:\n");
    for (int i = 0; i < num_transitions; i++) {
        printf("(%d, %c) -> (%c, %c, %c) -> ", transition[i][0], transition[i][1], transition[i][2], transition[i][3], transition[i][4]);

        // Encode current state
        for (int j = 0; j <=transition[i][0]; j++) {
            printf("1");
        }
        printf(" 0 ");

        // Encode current symbol

        if (transition[i][1] == '#') {
                for(int i=0; i<blank; i++)
                printf("1");
            //printf("0");
        } else {
            for (int j = 0; j <= (transition[i][1] - 'a'); j++) {
                printf("1");
            }
        }
         printf(" 0 ");


        // Encode new state
        for (int j = 0; j <=(transition[i][2] - '0'); j++) {
            printf("1");
        }
        printf(" 0 ");

        // Encode new symbol
        if (transition[i][3] == '#') {
                for(int i=0; i<blank; i++)
                printf("1");

        } else {
            for (int j = 0; j <= (transition[i][3] - 'a'); j++) {
                printf("1");
            }
        }
        printf(" 0 ");

        // Encode action
        if (transition[i][4] == 'l') {
            printf("1");
        } else if (transition[i][4] == 'r') {
            printf("11");
        } else if (transition[i][4] == 'y') {
            printf("111");
        } else if (transition[i][4] == 'n') {
            printf("1111");
        }
        printf("\n");
    }
}

