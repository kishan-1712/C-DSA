#include <stdio.h>
#include <string.h>

int match(char *t, char *p) {
    for (int i = 0; t[i]; i++) {
        int j = 0;
        while (p[j] && t[i + j] == p[j]) j++;
        if (!p[j]) return i;
    }
    return -1;
}

int main() {
    char t[100], p[100];
    
    // Separate user inputs
    printf("Enter the main string: ");
    scanf("%s", t);
    
    printf("Enter the pattern to find: ");
    scanf("%s", p);

    // Results
    printf("Without built-in: %d\n", match(t, p));
    
    char *res = strstr(t, p);
    printf("With built-in: %d\n", res ? (int)(res - t) : -1);

    return 0;
}