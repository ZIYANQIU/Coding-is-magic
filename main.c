#include <stdio.h>

#include <stdio.h>

#include <stdlib.h>

int main()

{
    int num;
    printf("Enter a num between 1 to 7: ");
    scanf("%d", &num);

    int arr[2] = {2,5};
    for(int i = 0; i <sizeof(arr)/sizeof(arr[0]);i++){
        printf("%d\n",arr[i]);
    }

    
};
