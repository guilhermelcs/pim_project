#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// int main()
// {
//     int i, x[365] = {0}, repetiu = 0;
//     srand( (unsigned)time(NULL) );
//
//     for(i=0 ; i < 365 ; i++) {
//       x[i] = 1 + ( rand() % 365 );
//         do{
//           repetiu = 0;
//           for(int j = 0; j < i; j++) {
//               if(x[i] == x[j]) {
//                 repetiu = 1;
//                 x[i] = 1 + ( rand() % 365 );
//               }
//             }
//         }while(repetiu == 1);
//         printf("Numero %d:    %d\n",i, x[i]);
//     }
//
//     printf("\n\n------------------------------------\n");
//     for(i = 0; i < 365; i++) {
//       for(int j = i; j < 365; j++) {
//         if(x[j] < x[i]) {
//           int aux = x[i];
//           x[i] = x[j];
//           x[j] = aux;
//         }
//       }
//       printf("Numero %d:    %d\n",i, x[i]);
//     }
//   return 0;
// }

int i, x[10] = {0}, repetiu = 0;

void sortear() {
  srand( (unsigned)time(NULL) );
  for(i=0 ; i < 10 ; i++) {
    x[i] = 1 + ( rand() % 10 );
    do{
      repetiu = 0;
      for(int j = 0; j < i; j++) {
        if(x[i] == x[j]) {
          repetiu = 1;
          x[i] = 1 + ( rand() % 10 );
        }
      }
    }while(repetiu == 1);
  }
}

int get_sorteio(int i) {
  return x[i];
}


int main() {
  int i = 0;
  while (i!=10) {
    sortear();
    int y = sortear(i);
    printf("%d\n", y);
    i++;
  }
  return 0;
}
