#include<stdio.h>
#include<ctype.h>
int priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
void infixToPostfix(char infix[], char postfix[]) {
    char stack[100];
    int top = -1, i = 0, j = 0;
    char c;

    while ((c = infix[i++]) != '\0' && c != '\n') {
        if (isalnum(c)) {
            postfix[j++] = c;
        } 
        else if (c == '(') {
            stack[++top] = c;
        } 
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') postfix[j++] = stack[top--];
            if (top != -1) top--; // Pop '('
        } 
        else {
            while (top != -1 && priority(stack[top]) >= priority(c) && !(c == '^' && stack[top] == '^')) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) postfix[j++] = stack[top--];
    postfix[j] = '\0';
}
int main() {
    char infix[100], postfix[100];
    printf("Enter infix: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    
    return 0;
}