#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 4

volatile int lock = 0;
volatile int global_var = 0;

void __unlock() {
	__sync_synchronize();
	lock = 0;
}

void* secao_critica(void* args) {
	int count = 0;
  int x = 0;
	int thread_index = (int)args;

	// Função loopando 20x
	while(count++ < 20) {
		printf("%d - executando funcao secao_critica.\n", thread_index);

		// Protocolo de Entrada - INÍCIO

		/* Funcionamento do Test and Set:
		__sync_lock_test_and_set(param1, param2) {
			valor_inicial = param1;
			param1 = param2;
			return inicial;
		}	*/
		while(__sync_lock_test_and_set(&lock, 1)) {
			printf("%d - Estou travada no test and set!\n", thread_index);
		}

		// while (x < 100000) {
		// 	x++;
		// }

		printf("%d - Acessando a função secao_critica()\n", thread_index);

		// Seção Crítica - INÍCIO
		printf("%d valor de myvar = %d\n", thread_index, ++global_var);
		printf("%d - Estou saindo da seção crítica...\n", thread_index);
		// Seção Crítica - FINAL

		// Protocolo de saída - apenas setando lock pra 0 de forma ATÔMICA.
		__unlock();

		printf("%d - Estou fora da seção crítica...\n", thread_index);
	}

  return (void*) thread_index;
}

int main (int argc, char **argv) {

	printf("Iniciando o programa...\n");
	int i;

	// Inicializa um array de variáveis do tipo pthread
	pthread_t threads[NUM_THREADS];

	// Cria as threads
	for (i = 1; i < NUM_THREADS+1; i++) {
		pthread_create(&threads[i], NULL, secao_critica, (void *)i);
		printf("%d - Fui criada\n", i);
	}

	/* Da join nas threads.
	Essa função pode não ser executada, isso ocorre quando a Thread main termina antes dela */
	for (i = 1; i < NUM_THREADS+1; i++) {
		pthread_join(threads[i], NULL);
		printf("%d - (JOIN) Agora que já fiz meu trabalho, vou embora, tchau!\n", i);
	}

	return 0;
}
