// In this project, we focus on fully parenthesized infix expressions, such as: (((3+4)*8)-6)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Define the structure of an operand stack StackOpd for Operands
typedef struct StackOpd{
    int *operands; //dynamic allocation of array of operands
    int top;
    int size;
}StackOpd;

//Define the structure of an operand stack StackOpr for Operators
typedef struct StackOpr{
    char *operators;
    int top;
    int size;
}StackOpr;



//Function Declarations for Operand Stack
void initStackOpd(StackOpd *stack, int stack_size); //to initialize an empty operand stack at address adrP.
void empilerOpd(StackOpd *stack, int x); //to add an element x to the stack at address adrP
int depilerOpd(StackOpd *stack); //to remove and return the top of the stack.

//Function Declarations for Operator Stack
void initStackOpr(StackOpr *stack, int stack_size);
void empilerOpr(StackOpr *stack, char x);
char depilerOpr(StackOpr *stack);

//Convert Infix to Postfix
char *convertirInf2Post(char *expInf); //takes an infix notation expression as a parameter and returns its conversion to postfix notation.

//Evaluate the Postfix expression
int calculate(int x, int y, char op); // takes two operands x and y and an operator op as parameters to compute the expression x op y.
int evaluer(char *exp);



//Function Definitions for Operand Stack
void initStackOpd(StackOpd* stack, int size){
    stack -> operands = malloc(sizeof(int)*size);
    stack -> top = -1;
    stack-> size = size;}

void empilerOpd(StackOpd *stack, int new_elem){
    stack->operands[++(stack->top)] = new_elem;}


int depilerOpd(StackOpd *stack){
    if(stack->top>=0) //non empty
    {
        return stack->operands[(stack->top)--];
    }
    return -1;}


//Function Definitions for Operator Stack
void initStackOpr(StackOpr *stack, int size){
    stack->operators = malloc(sizeof(char)* size);
    stack->top = -1;
    stack->size = size;}


void empilerOpr(StackOpr *stack, char new_elem){
    stack->operators[++(stack->top)] = new_elem;
    
}


char depilerOpr(StackOpr *stack){
    if(stack->top >= 0){
        return stack->operators[(stack->top)--];
    }
    return '\0';
    
}

char *convertirInf2Post(char *expInf){
    
    StackOpr stack_operator;
    initStackOpr(&stack_operator, 100);
    char *expPost = malloc(strlen(expInf) + 1);
    
    int i,j=0;
    
    for(i=0;expInf[i] != '\0';i++){
        if (expInf[i] == '('){
            continue;
        }
        else if (isdigit(expInf[i])) //add operand to postfix expression
        {
            expPost[j++]=expInf[i];
            
        }
        else if (expInf[i] == ')'){
            expPost[j++] = depilerOpr(&stack_operator);
        }
        else if (strchr("+-*/", expInf[i])){ //it is an operator -> push to stack of operators
            expPost[j++] = ' ';
            empilerOpr(&stack_operator,expInf[i]);
        }
    }
        expPost[j] = '\0';
        return expPost;
}

int calculate(int x, int y, char op){
    //will only use the operators +, -, *, and /.
    switch(op){
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '*':
            return x*y;
        case '/':
            return y!=0 ? x/y : 0; //if divided by 0 returns 0
        default:
            return 0;
    }
}

int evaluer(char *exp) {
    char *expPost;
    StackOpd stack_operand;
    initStackOpd(&stack_operand, 100);
    int i;
    int x, y;
    int result = 0;
    
    expPost = convertirInf2Post(exp);
    
    for (i = 0; expPost[i] != '\0'; i++) {
        if (isdigit(expPost[i])) { // push to stack
            empilerOpd(&stack_operand, expPost[i] - '0'); // Convert char to int before pushing
        }
        else if (strchr("+-*/", expPost[i])) {
            y = depilerOpd(&stack_operand);
            x = depilerOpd(&stack_operand);
            result = calculate(x, y, expPost[i]);
            empilerOpd(&stack_operand, result);
        }
    }
    
    result = depilerOpd(&stack_operand); // Get final result from stack
    
    free(expPost);
    return result;
}

int main(void){
    
    char expInf[100];
    char expPost[100];
    int result;
    
    printf("Please Enter a Fully Parenthesized Infix Expression:\n");

    fgets(expInf,100, stdin);
    printf("The Infix Expression is: %s \n",expInf);
    strcpy(expPost, convertirInf2Post(expInf));
    printf("The Equivalent Postfix Expression is: %s ",expPost);
    result = evaluer(expInf);
    printf("The Result of Evaluating %s is: %d \n",expPost,result);

    return 0;
}










