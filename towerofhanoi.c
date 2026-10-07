#include<stdio.h>
void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod){
    if(n==1){
        printf("move disk 1 from rod %c to rod %c\n", from_rod, to_rod);
        return;
    }
    tower_of_hanoi(n-1, from_rod, aux_rod, to_rod);
    printf("move disk %d from rod %c to rod %c\n",n , from_rod, to_rod);
    tower_of_hanoi(n-1, aux_rod, to_rod, from_rod);
}
int main(){
    int n;
    printf("nter the number of disks:");
    scanf("%d",&n);
    printf("\nsequence of disks:\n");
    tower_of_hanoi(n, 'A', 'C', 'B');
    return 0;
}