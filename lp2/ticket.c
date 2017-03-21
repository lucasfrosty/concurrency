#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 4

/* É recomendado que todas as variáveis globais sejam declaradas com volatile
Pra saber mais: http://stackoverflow.com/questions/246127/why-is-volatile-needed-in-c */
volatile int number = 1; // variável auxiliar onde será executada a função fetch and add
volatile int next = 1; // próxima ficha a ser atendida
volatile int global_var = 0; // variável global a ser manuseada pelas threads

int turn[NUM_THREADS] = {0,0,0,0}; // array com as fichas das 4 threads

// Função da seção crítica
void* secao_critica(void* args) {
	int thread_index = (int) args; // converte o ponteiro pra void de volta para int
	printf("%d - Estou executando a função secao_critica()\n", thread_index);

	// Protocolo de Entrada - INÍCIO

	/* Funcionamento do Fetch and Add:
	__sync_fetch_and_add(param1, param2) {
		valor_inicial = param1;
		param1 = param1 + param2;
		return inicial;
	}	*/
	turn[thread_index] = __sync_fetch_and_add(&number,1);
	printf("%d - Recebi a ficha %d\n", thread_index, turn[thread_index]);

	/* As threads que ainda não foram chamadas irão esperar
	até sua vez (turn[thread_index] == next) para executar sua seção critica,
	enquanto isso não ocorrer ela ficará sempre no loop e nunca progredindo.
	Isso é a ESPERA OCUPADA */
 	while (turn[thread_index] != next) {
		printf("%d - Não é minha vez, fui bloqueada!\n", thread_index);
	}
	// Protocolo de Entrada - FINAL

	// Seção Crítica - INÍCIO
	printf("%d - Entrei na seção crítica\n", thread_index);

	/* Por ser ++global_var ela primeiramente vai incrementar o valor de global_var
	 e em seguida irá imprimí-la.
	 Se fosse global_var++ seria o contrário */
	printf("%d - valor da variável global = %d\n", thread_index, ++global_var);
	printf("%d - Estou saindo da seção crítica...\n", thread_index);
	// Seção Crítica - FINAL

	/* Protocolo de Saída - INÍCIO
	O protocolo de saída nesse caso é apenas incrementar o valor de next,
	para que assim a próxima thread saia da ESPERA OCUPADA e possa executar sua seção crítica */
	next++;
	// Protocolo de Saída - FINAL

	// Seção não crítica
	printf("%d - Não estou mais na seção crítica\n", thread_index);
	return (void*) thread_index; // returna ponteiro pra void pq a função é ponteiro pra void

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
