#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 1024

int stack[STACK_SIZE];
int sp = -1;

void push(int v){
    if(sp >= STACK_SIZE-1){
        printf("Error: stack overflow\n");
        exit(1);
    }
    stack[++sp] = v;
}

int pop(){
    if(sp < 0){
        printf("Error: stack underflow\n");
        exit(1);
    }
    return stack[sp--];
}

int top(){
    if(sp < 0){
        printf("Error: stack empty\n");
        exit(1);
    }
    return stack[sp];
}

int main(int argc,char **argv){

    if(argc < 2){
        printf("Usage: %s <source file>\n",argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1],"r");
    if(!f){
        printf("Error: cannot open file '%s'\n",argv[1]);
        return 1;
    }

    int c;

    while((c=fgetc(f)) != EOF){

        switch(c){

        case '!':                // increment
            stack[sp]++;
            break;

        case '@':                // decrement
            stack[sp]--;
            break;

        case '#':                // negate
            stack[sp] = -stack[sp];
            break;

        case '$':                // duplicate
            push(top());
            break;

        case '%':                // add
        {
            int a = pop();
            int b = pop();
            push(a + b);
            break;
        }

        case '^':                // print char
            putchar(top());
            break;

        case '`':                // pop
            pop();
            break;

        case '~':                // push 'A'
            push(65);
            break;

        case '(':{               // push number
            int num = 0;
            while((c=fgetc(f)) != ')'){
                if(isdigit(c))
                    num = num*10 + (c-'0');
            }
            push(num);
            break;
        }

        default:
            break;
        }
    }

    printf("\n");
    fclose(f);
}