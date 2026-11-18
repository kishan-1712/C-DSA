#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Student {
    char name[50];
    char usn[15];
    int sem;
    float cgpa;
    struct Student *prev;
    struct Student *next;
} Student;
Student *head = NULL;
Student *tail = NULL;
int count = 0;
void to_upper(char *s) {
    for (; *s; s++) *s = (char)toupper((unsigned char)*s);
}
void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
Student *find_by_usn(const char *usn) {
    for (Student *p = head; p; p = p->next)
        if (strcmp(p->usn, usn) == 0) return p;
    return NULL;
}
Student *read_student(void) {
    Student *s = (Student *)malloc(sizeof(Student));
    if (!s) { printf("Memory allocation failed!\n"); return NULL; }
    printf("Enter Name : ");
    scanf(" %49[^\n]", s->name);
    printf("Enter USN  : ");
    scanf(" %14s", s->usn);
    to_upper(s->usn);
    if (find_by_usn(s->usn)) {
        printf("A student with USN %s already exists. Not added.\n", s->usn);
        free(s);
        return NULL;
    }
    do {
        printf("Enter Sem (1-8)  : ");
        if (scanf("%d", &s->sem) != 1) { clear_input(); s->sem = 0; }
    } while (s->sem < 1 || s->sem > 8);
    do {
        printf("Enter CGPA (0-10): ");
        if (scanf("%f", &s->cgpa) != 1) { clear_input(); s->cgpa = -1; }
    } while (s->cgpa < 0 || s->cgpa > 10);
    s->prev = s->next = NULL;
    return s;
}
void display_forward(void) {
    printf("\n--- LIST STATUS (Head -> Tail) | Total students: %d ---\n", count);
    if (!head) { printf("List is EMPTY.\n"); return; }
    printf("%-4s %-22s %-12s %-5s %-5s\n", "No.", "Name", "USN", "Sem", "CGPA");
    printf("--------------------------------------------------------\n");
    int i = 1;
    for (Student *p = head; p; p = p->next, i++)
        printf("%-4d %-22s %-12s %-5d %-5.2f\n", i, p->name, p->usn, p->sem, p->cgpa);
}
void display_backward(void) {
    printf("\n--- LIST STATUS (Tail -> Head) | Total students: %d ---\n", count);
    if (!tail) { printf("List is EMPTY.\n"); return; }
    printf("%-4s %-22s %-12s %-5s %-5s\n", "No.", "Name", "USN", "Sem", "CGPA");
    printf("--------------------------------------------------------\n");
    int i = count;
    for (Student *p = tail; p; p = p->prev, i--)
        printf("%-4d %-22s %-12s %-5d %-5.2f\n", i, p->name, p->usn, p->sem, p->cgpa);
}
void insert_front(void) {
    Student *s = read_student();
    if (!s) return;
    s->next = head;
    if (head) head->prev = s; else tail = s;
    head = s;
    count++;
    printf("Inserted %s at the FRONT.\n", s->usn);
}
void insert_end(void) {
    Student *s = read_student();
    if (!s) return;
    s->prev = tail;
    if (tail) tail->next = s; else head = s;
    tail = s;
    count++;
    printf("Inserted %s at the END.\n", s->usn);
}
void insert_at_position(void) {
    int pos;
    printf("Enter position (1 to %d): ", count + 1);
    if (scanf("%d", &pos) != 1) { clear_input(); printf("Invalid input.\n"); return; }
    if (pos < 1 || pos > count + 1) { printf("Invalid position!\n"); return; }
    Student *s = read_student();
    if (!s) return;
    if (pos == 1) {
        s->next = head;
        if (head) head->prev = s; else tail = s;
        head = s;
    } else if (pos == count + 1) {
        s->prev = tail;
        tail->next = s;
        tail = s;
    } else {
        Student *p = head;
        for (int i = 1; i < pos - 1; i++) p = p->next;   /* node before pos */
        s->next = p->next;
        s->prev = p;
        p->next->prev = s;
        p->next = s;
    }
    count++;
    printf("Inserted %s at position %d.\n", s->usn, pos);
}
void unlink_and_free(Student *p) {
    if (p->prev) p->prev->next = p->next; else head = p->next;
    if (p->next) p->next->prev = p->prev; else tail = p->prev;
    printf("Deleted: %s (%s)\n", p->name, p->usn);
    free(p);
    count--;
}
void delete_front(void) {
    if (!head) { printf("List is empty. Nothing to delete.\n"); return; }
    unlink_and_free(head);
}
void delete_end(void) {
    if (!tail) { printf("List is empty. Nothing to delete.\n"); return; }
    unlink_and_free(tail);
}
void delete_by_usn(void) {
    char usn[15];
    if (!head) { printf("List is empty. Nothing to delete.\n"); return; }
    printf("Enter USN to delete: ");
    scanf(" %14s", usn);
    to_upper(usn);
    Student *p = find_by_usn(usn);
    if (!p) { printf("USN %s not found.\n", usn); return; }
    unlink_and_free(p);
}
void delete_at_position(void) {
    int pos;
    if (!head) { printf("List is empty. Nothing to delete.\n"); return; }
    printf("Enter position (1 to %d): ", count);
    if (scanf("%d", &pos) != 1) { clear_input(); printf("Invalid input.\n"); return; }
    if (pos < 1 || pos > count) { printf("Invalid position!\n"); return; }
    Student *p = head;
    for (int i = 1; i < pos; i++) p = p->next;
    unlink_and_free(p);
}
void search_by_usn(void) {
    char usn[15];
    printf("Enter USN to search: ");
    scanf(" %14s", usn);
    to_upper(usn);
    int pos = 1;
    for (Student *p = head; p; p = p->next, pos++) {
        if (strcmp(p->usn, usn) == 0) {
            printf("FOUND at position %d -> Name: %s | USN: %s | Sem: %d | CGPA: %.2f\n",
                   pos, p->name, p->usn, p->sem, p->cgpa);
            return;
        }
    }
    printf("USN %s not found.\n", usn);
}
void update_student(void) {
    char usn[15];
    printf("Enter USN of the student to update: ");
    scanf(" %14s", usn);
    to_upper(usn);
    Student *p = find_by_usn(usn);
    if (!p) { printf("USN %s not found.\n", usn); return; }
    int sem; float cgpa;
    do {
        printf("Enter new Sem (1-8)  : ");
        if (scanf("%d", &sem) != 1) { clear_input(); sem = 0; }
    } while (sem < 1 || sem > 8);
    do {
        printf("Enter new CGPA (0-10): ");
        if (scanf("%f", &cgpa) != 1) { clear_input(); cgpa = -1; }
    } while (cgpa < 0 || cgpa > 10);
    p->sem = sem;
    p->cgpa = cgpa;
    printf("Record of %s updated.\n", p->usn);
}
void swap_data(Student *a, Student *b) {
    Student t;
    strcpy(t.name, a->name);  strcpy(a->name, b->name);  strcpy(b->name, t.name);
    strcpy(t.usn, a->usn);    strcpy(a->usn, b->usn);    strcpy(b->usn, t.usn);
    t.sem = a->sem;           a->sem = b->sem;           b->sem = t.sem;
    t.cgpa = a->cgpa;         a->cgpa = b->cgpa;         b->cgpa = t.cgpa;
}
void sort_by_cgpa(void) {
    if (count < 2) { printf("Not enough records to sort.\n"); return; }
    int swapped;
    do {
        swapped = 0;
        for (Student *p = head; p->next; p = p->next) {
            if (p->cgpa < p->next->cgpa) {      
                swap_data(p, p->next);
                swapped = 1;
            }
        }
    } while (swapped);
    printf("List sorted by CGPA (highest first).\n");
}
void reverse_list(void) {
    if (count < 2) { printf("Not enough records to reverse.\n"); return; }
    Student *p = head, *tmp;
    while (p) {
        tmp = p->prev;
        p->prev = p->next;
        p->next = tmp;
        p = p->prev;           
    }
    tmp = head; head = tail; tail = tmp;
    printf("List reversed.\n");
}
void free_list(void) {
    Student *p = head, *n;
    while (p) { n = p->next; free(p); p = n; }
    head = tail = NULL;
    count = 0;
}
int main(void) {
    int choice;
    printf("=========== STUDENT DOUBLY LINKED LIST ===========\n");
    display_forward();
    while (1) {
        printf("\n================== MENU ==================\n");
        printf(" 1. Insert at front\n");
        printf(" 2. Insert at end\n");
        printf(" 3. Insert at a position\n");
        printf(" 4. Delete from front\n");
        printf(" 5. Delete from end\n");
        printf(" 6. Delete by USN\n");
        printf(" 7. Delete at a position\n");
        printf(" 8. Search by USN\n");
        printf(" 9. Update Sem / CGPA\n");
        printf("10. Sort by CGPA (descending)\n");
        printf("11. Reverse the list\n");
        printf("12. Display in reverse (Tail -> Head)\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_input();
            printf("Invalid input! Enter a number.\n");
            continue;
        }
        switch (choice) {
            case 1:  insert_front();        break;
            case 2:  insert_end();          break;
            case 3:  insert_at_position();  break;
            case 4:  delete_front();        break;
            case 5:  delete_end();          break;
            case 6:  delete_by_usn();       break;
            case 7:  delete_at_position();  break;
            case 8:  search_by_usn();       break;
            case 9:  update_student();      break;
            case 10: sort_by_cgpa();        break;
            case 11: reverse_list();        break;
            case 12: display_backward();    continue;
            case 13:
                free_list();1
                printf("Memory freed. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
        display_forward();   /* status after every operation */
    }
}