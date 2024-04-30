#include <iostream>
#include <omp.h>
using namespace std;

long long num_passos = 10000000000;
double passo;

int main(){
   long long i;
   double x, pi, soma=0.0, time_inicio, time_fim;
   time_inicio = omp_get_wtime();
   passo = 1.0/(double)num_passos;
	
   #pragma omp parallel for private(i,x) num_threads(4) reduction(+:soma)
   for(i=0; i < num_passos; i++){
      x = (i + 0.5)*passo;
      soma = soma + 4.0/(1.0 + x*x);
   }

   pi = soma*passo;
   time_fim = omp_get_wtime();
   cout << "Tempo:" << time_fim - time_inicio << endl;
   cout << "O valor de PI é: " << pi << endl;
   return 0;
}
