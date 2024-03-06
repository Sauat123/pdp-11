#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef int register_type;
const int NUM_OF_REGISTERS = 4;
register_type registers[NUM_OF_REGISTERS] = {};

enum LEGAL_COMMANDS{HLT = 0,
                    ADD, SUB, MOV,
                    IR, reg_A, reg_B, reg_C, reg_D};

int scan_commands(int * current_command);

register_type register_add(int reg1, int reg2); //parameters: register number in memory
register_type register_sub(int reg1, int reg2); //parameters: register number in memory

register_type register_mov(int source_register, register_type value);

void print_registers();

void evaluate(int current_command);

void scan_arguments_for_eval(int * reg1, int * reg2); //scanning arguments for register_add or register_sub

int main()
{
    int current_command = 1; //random number excluding 0

    while(scan_commands(&current_command))
    {
        evaluate(current_command);
    }
    return 0;
}

void evaluate(int current_command)
{
    int reg1 = 0;
    int reg2 = 0;

    switch (current_command) {
    
        case HLT: {
            fprintf(stderr, "Current command can't be equal 0\nCheck scan_commands() returning value");
            break;
        }

        case IR: {
            print_registers();
            break;
        }

        case ADD: {
            scan_arguments_for_eval(&reg1, &reg2);
            register_add(reg1, reg2);
            break;
        }

        case SUB: {
            scan_arguments_for_eval(&reg1, &reg2);
            register_sub(reg1, reg2);
            break;
        }

        case MOV: {
            register_type value = 0;
            if(scan_commands(&reg1))
            {
                scanf("%d", &value);
                register_mov(reg1, value);
            }
            break;
        }

        default: {
            fprintf(stderr, "Error in evaluate switch case\n");
        }

    }
}

void scan_arguments_for_eval(int * reg1, int * reg2)
{
    if(scan_commands(reg1))
            if(scan_commands(reg2) == 0)
                exit(0);
}

void print_registers()
{
    for(int i = 0; i < NUM_OF_REGISTERS; i++)
    {
        printf("%d ", registers[i]);
    }
    printf("\n");
}

register_type register_add(int reg1, int reg2)
{
    registers[reg1-5] = registers[reg1-5] + registers[reg2-5];
    
    return registers[reg1-5];
}

register_type register_sub(int reg1, int reg2)
{
    registers[reg1-5] = registers[reg1-5] - registers[reg2-5];  

    return registers[reg1-5];
}

register_type register_mov(int reg1, register_type value)
{
    registers[reg1-5] = value;
    return registers[reg1-5];
}

int scan_commands(int * current_command)
{
    scanf("%d", current_command);

    if(*current_command == 0) return 0;
    else return 1;
}