#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 100000
#define WORKERS 2

typedef struct {
  int *a;
  int left;
  int right;
} thread_args;

int vet[MAX];

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    if ((left + right)%2 != 0) {
    	x = a[(left + right + 1)/2];
	}
    else 
		x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

void *worker(void *arg) {
  thread_args *info = (thread_args *) arg;
  quick_sort(info->a, info->left, info->right);
  //printf("Thread está funcionando");
  return NULL;
}


int main () {
 pthread_t workers[WORKERS];
 thread_args *send_args[WORKERS];

char c;
int tam = 0;
  do {
    scanf("%d", &vet[tam]);
    tam++;
  }
  while((c = getchar()) != '\n');
  /*printf("Valores desordenados\n");
 for(int i = 0; i < tam; i++)
 {
  printf("%d ", vet[i]);
 }
 printf("tamanho %d\n", tam);*/

  if (tam%2 != 0) {
  	for (int i = 0; i < WORKERS; i++) {
    (send_args[i]) = (thread_args*) malloc(sizeof(thread_args));
    (send_args[i])->a = vet;
    (send_args[i])->left = (tam+1/2)*i;
    (send_args[i])->right = (tam+1/2)*(i+1) - 1;
  }
  	(send_args[WORKERS-1])->right = tam - 1;
  }
  else {
  	for (int i = 0; i < WORKERS; i++) {
    (send_args[i]) = (thread_args*) malloc(sizeof(thread_args));
    (send_args[i])->a = vet;
    (send_args[i])->left = (tam/2)*i;
    (send_args[i])->right = ((tam/2)*(i+1))-1;
  }
  }
  
  for (int i = 0; i < WORKERS; i++)
    pthread_create(&(workers[i]), NULL, worker, (void *) send_args[i]);
  
  for (int i = 0; i < WORKERS; i++)
    pthread_join(workers[i], NULL);
    
  for (int i = 0; i < WORKERS; i++)
  {
    quick_sort(vet, (send_args[0])->left, (send_args[i])->right);
  }
    
	for (int i = 0; i < WORKERS; i++)
    	free(send_args[i]);

 //printf("Valores ordenados\n");
 for(int i = 0; i < tam - 1; i++)
 {
  printf("%d ", vet[i]);
 }
 printf("%d\n", vet[tam - 1]);
 
 return 0;
}
 


