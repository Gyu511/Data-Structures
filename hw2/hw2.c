#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )

char input1[128];
char input2[128];
int arr[20];
int cnt = 0;

int partition(int list[], int left, int right) {
   int pivot, temp;
   int low, high;

   low = left;
   high = right + 1;
   pivot = list[left]; 

   do {      
      do {
         low++; 
      } while (low <= right && list[low] < pivot);
      
      do {
         high--; 
      } while (high >= left && list[high] > pivot);
   
      if (low < high) {
         SWAP(list[low], list[high], temp);
      }
   } while (low < high);

   SWAP(list[left], list[high], temp);

   return high;
}

void quick_sort(int list[], int left, int right) {
   if (left < right) {   
      int q = partition(list, left, right); 
      quick_sort(list, left, q - 1); 
      quick_sort(list, q + 1, right); 
   }
}

short check(int num) {
   for (int i = 0; i < cnt; i++) {
      if (arr[i] == num)
         return 1;
   }
   return 0;

}

int main() {
   FILE* fp = fopen("input.txt", "r");
   

   printf("Input :\n");
   fgets(input1,sizeof(input1),fp);
   fgets(input2, sizeof(input2), fp);

   //gets(input1);
   //gets(input2);

   char* ptr1 = strtok(input1, ",");
   while (ptr1 != NULL) {
      int tmp = atoi(ptr1);
      if(!check(tmp)) //if there's not same number
         arr[cnt++] = tmp;
      ptr1 = strtok(NULL, ",");            
   }

   char* ptr2 = strtok(input2, ",");
   
   while (ptr2 != NULL) {
      int tmp = atoi(ptr2);
      if (!check(tmp)) //if there's not same number
         arr[cnt++] = tmp;
      ptr2= strtok(NULL, ",");         
   }

   quick_sort(arr, 0, cnt-1);
   printf("Output:\n");
   for (int i = 0; i < cnt-1; i++) {
      printf("%d, ", arr[i]);
   }printf("%d", arr[cnt-1]);
}