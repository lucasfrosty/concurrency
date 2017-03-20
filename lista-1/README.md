# Lista 1 - LP2 (Bidu)

##### 1) O que é programação concorrente? Quais são os aspectos a serem observados	quando do planejamento de sistemas que utilizam	processos concorrentes?
É um paradigma de programação onde o processo pode ser executado de forma sequencial ou paralela concorrendo pela disponibilidade do(s) processador(es) com os demais processos. Como o processador executa apenas uma instrução por vez (instruções atômicas), fica a cargo do escalonador ditar qual processo ou sub-processo (no caso de processos que tenha mais de 1 thread) terão a possibilidade de ter sua instrução executada pelo processador.
Deve se observar os seguintes aspectos (TODO):
____

##### 2) Qual o impacto do advento dos processadores multi-núcleo na implementação e execução de programas que utilizam programação concorrente?
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
____

##### 3) O que é, em programação concorrente, consistência de memória?
É a política que determina como e quando mudanças feitas por um processador são vistas pelos outros processadores do sistema. Um modelo de consistência de memória define um contrato entre o software e o sistema de memória, ou seja, se o software obedecer certas regras, o sistema de memória funcionará corretamente.
Exemplos de modelos:
- **Consistência sequencial:** Quando o resultado de qualquer uma das execuções é equivalente a uma execução entrelaçada em um único processador. A condição necessária para um sistema com acesso de memória atômico seja sequencial é que os acessos de memória sejam feitos na ordem específica do programa.
____

##### 4) O que é um processo? Quais são as informações que compreendem o contexto de um processo?
Um processo é um programa em execução, que podem acontecer _Background_, ou seja, ocorrendo sem a nossa percepção (ex: gerenciador de redes, memória, drivers, etc) ou em _Foreground_, onde temos a percepção de que ele está sendo executado (ex: browsers, editores de texto, jogos, etc). Como exemplicado, o sistema operacional é o principal responsável por gerenciar (inicializar, fechar, parar) os processos, mas os usuários também esse poder seja através de comandos no shell (como o kill), ou simplesmente inicializando um programa, que nada mais é do que é um ou mais processos.
O **contexto de um processo** pode conter as seguintes informações:
- Código do programa
- Dados armazenados na memória
- Pilha de execução
- Conteúdo dos registradores
- Descritores dos arquivos abertos
____

##### 5) Como pode ser feita	a	inicialização	e finalização de processos em C	(em sistemas POSIX)? Cite exemplos de funções utilizadas para a gerência do ciclo de processos e explique brevemente como essas funções são implementadas.
Ao criar um algoritmo (com uma simples função main) já estamos criando um processo. Porém temos comandos como o ```fork()``` que é responsável por criar um _processo filho_ ao processo principal (main) e o ```kill()``` que finaliza um determinado processo. Abaixo uma lista com várias funções utilizadas em C:
- ```fork()```: Cria um processo filho idêntico ao processo pai, porém o resultado de retorno da criação dessa função é 0 ```fork() == 0```, para que dessa forma possa-se diferenciar quem é o pai e quem é o filho.
- ```execve()```: Cria um processo filho a partir de um programa externo e um conjunto de parâmetros.
- ```exit(status)```: Termina a execução do processo que está acontecendo e retorna seu estado (parâmetro status). Usualmente é usado ```exit(0)```.
- ```kill()```: Finaliza um determinado processo.
____

##### 6) O que são threads e quais as diferenças do uso de threads para o uso de processos? Quais os estados e transições no ciclo de vida das threads?
Thread é um recurso computacional onde seu intuito é dividir o processo em outros sub-processos, onde esses sub-processos executam tarefas de forma concorrente. Seu suporte pode ser oferecido pelo próprio sistema operacional, através do _KLT_ (Kernel-Level Thread) ou implementada por uma linguagem de programação através de bibliotecas (User-Level Thread). Um programa (processo), nativamente tem pelo menos 1 thread, comumente chamada de _main thread_, porém, ao criar-se outra thread dentro daquele contexto de programa, é gerada uma thread filha que disputará com as demais threads (incluindo a main thread) pelo tempo de execução dado pelo escalonador.  
**Threads x Processo**: Threads são chamados também de _processos leves_, pois são criados e destruídos mais rapidamente do que processos. Porém, quando usa-se Threads, precisa-se haver um cuidado maior com sua implementação do que nos processos, isso porque quem escolhe qual tarefa (Thread) será executada em determinado momento é o escalonador, logo o desenvolvedor, a princípio, não tem total controle sobre a ordem de execução do programa, devido a isso é necessário utilizar-se de algumas ferramentas para se obter esse controle. Esse controle é mais comumente necessário quando múltiplas Threads acessam uma mesma área de memória (variáveis globais) e alteram a mesma, devido a falta de controle de execução das Threads fica impossível determinar o momento certo que uma Thread irá alterar o conteúdo de uma área da memória, podendo assim causar problemas indesejáveis na criação e implementação de um algoritmo. Devido a isso torna-se necessário a implementação das propriedades _Safety_ and _Liveness_.  
As Threads, assim como os processos, têm o seguinte ciclo de vida:
- **Em execução**: O momento que as tarefas designadas pela Thread são executadas pelo processador. O momento que isso irá acontecer é decidido pelo escalonador.
- **Pronto**: A Thread está pronta para ser executada, ficando em uma "fila", onde a mesma espera pelo seu momento para ir para o estado de execução (novamente, cabe ao escalonador dizer quando isso irá ocorrer).
- **Bloqueado**: A Thread depende de um determinado evento para poder estar apta a executar, geralmente isso ocorre quando a Thread depende de um determinado valor para executar sua tarefa, porém esse valor ainda não está disponível, então até que esse valor esteja disponível a Thread ficará nesse estado. Importante ressaltar que quando a Thread sai desse estado ele não é executado logo de cara, após sair do estado Bloqueado ele vai para o estado _Pronto_, onde irá esperar pelo escalonador designar seu momento de ter suas tarefas executadas no processador.

____

##### 7) Como é o controle do ciclo de vida de threads a partir da API POSIX Threads (PThreads)?
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
____

##### 8) Descreva as propriedades de Safety e Liveness e porque elas são importantes no âmbito do desenvolvimento de programas concorrentes.
a) **Safety Property**: É uma propriedade que dá ao desenvolvedor o controle sobre os estados do seu algoritmo, e que dessa forma, ele nunca entre em um estado indesejado (ex: variáveis com valores indesejados). Exemplos de técnicas que levam um algoritmo a ter a _Safety Property_:
- **Ausência de Deadlock**: Nunca ocorrerá de processos (ou parte deles) não executem, pois estão esperando a ocorrência de um evento que nunca ocorrerá. O desenvolvedor, tendo o controle de todos os eventos e estados do programa, garante que todos os eventos importantes para o algoritmo rodar, ocorram.
- **Exclusão Mútua**: No máximo um processo (ou thread) executa uma região crítica por vez.

b) **Liveness Property**: É uma propriedade que garante que o algoritmo sempre entrará um estado desejado, onde falhas levam à ausência de um comportamento desejado. Exemplos de técnicas de _Liveness Property_:
- **Terminação**: Garante que em algum momento o programa terminará.
- **Entrada eventual**: Um processo aguardando entrar em uma região crítica eventualmente terá acesso a ela.
____

##### 9)  O  que  é  o  problema  da  seção  crítica?  Dê  exemplos  de  situações  onde  tal  problema acontece.
A seção crítica são blocos de código onde, para que sua funcionalidade possa ser feita de maneira eficaz, devem satisfazer as seguintes propriedades:
- **Exclusão Mútua**: Apenas um processo (ou thread) poderá estar executando uma seção crítica por vez.
- **Ausência de Deadlock**: Se vários processos estão tentando entrar em sua seção crítica, apenas uma poderá obter esse acesso por vez.

Seu controle geralmente é feito da seguinte forma:
```c
while (true) {
    protocolo de entrada;
    seção crítica;
    protocolo de saída;
}
```
Esses protocolos, em pseudo-código, podem ser feitos através do comando <await>, onde os parênteses angulares servem para simular uma instrução atômica. Já em linguagens de alto nível como C, possuem instruções especiais para implementar essas instruções atômicas como a de _Test and Set_, geralmente implementada em _Spin Locks_.

Exemplos (TODO):
____

##### 10) Explique o que são locks (travas) e dê um exemplo de código (código em C/C++) do uso de locks para solução do problema da seção	crítica.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
