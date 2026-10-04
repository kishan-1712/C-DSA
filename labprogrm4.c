#include<stdio.h>
int main()
{
    int n,i ;
    printf("enter the number of elements in the array: ");
    scanf("%d",&n);
    if(n<=0)
    {
        printf("array size should be greater than 0");
        return 1;
    }

int arr[n];
printf("enter %delements :\n",n);
for(i=0;i<n;i++)
{
    scanf("%d",&arr[i]);
}
int min=arr[0];
int max=arr[0];
for(i=1;i<n;i++)
{
    if(arr[i]<min)
    {
        min=arr[i];
    }
    if(arr[i]>max)
    {
        max=arr[i];
    }
}
printf("Minimum element: %d\n", min);
printf("Maximum element: %d\n", max);
return 0;
}