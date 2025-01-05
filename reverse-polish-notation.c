#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate(char operator, int a, int b){
  switch (operator)
  {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    return 0;
  }
}

int main() {
  char expr[] = "50 3 4 + 5 * -";
  int stack[100], top = 0;

  for(char* token = strtok(expr, " "); token != NULL; token = strtok(NULL, " ")){
    char op = strlen(token) == 1 ? token[0] : '\0';
    if (op == '+' || op == '-' || op == '*' || op == '/'){
      int result = calculate(op, stack[--top], stack[--top]);
      stack[top++] = result;
    } else {
      stack[top++] = atoi(token);
    }
  }

  if(top != 1){
    printf("incorrect expression!\n");
  } else {
    int res = stack[0];
    printf("%d\n", res);
  }
  
  return 0;
}