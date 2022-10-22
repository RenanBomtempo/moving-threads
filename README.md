## Introdução

Neste trabalho vamos implementar um sistema de sincronização entre threads que se assemelha a um sistema de controle de movimentação para um jogo digital, ou para o controle de robôs.

## Objetivo

Seu objetivo será criar um programa em C, com Pthreads, que deve criar um certo número de threads que seguirão, cada uma, um trajeto definido dentro de uma grade (como um tabuleiro representado por uma matriz NxN). Cada thread visitará um certo número de posições e deverá seguir certas regras no seu movimento.

## O princípio de operação

A especificação do tabuleiro, do número de threads e dos seus trajetos será fornecida através da entrada padrão, como linhas de texto. Cada thread representará uma entidade se movendo em um tabuleiro NxN, com certas restrições sobre o movimento. Ao entrar em uma posição da grade, cada thread deve passar um certo tempo ali (definido na especificação) antes de se mover para a próxima posição. Depois de ficar o tempo determinado na última posição do seu trajeto, cada thread deve terminar.

O tempo mínimo a ser gasto em cada posição será fornecido em décimos de segundo; ao se estabelecer em uma certa posição, a threade deve executar a função passa_tempo() que deve ser definida exatamente como a seguir:

```c
#include <time.h>

void passa_tempo(int tid, int decimos)
{
    struct timespec zzz;

    zzz.tv_sec  = decimos/10;
    zzz.tv_nsec = (decimos%10) * 100L * 1000000L;

    printf("PTa(%d,%d)\n",tid,decimos);
    nanosleep(&zzz,NULL);
    printf("PTb(%d,%d)\n",tid,decimos);
}
```

O código apresentado para a função passa_tempo fará com que a thread seja suspensa pelo tempo indicado. Para todos os efeitos de sincronização, seria o mesmo que se ela estivesse executando qualquer tipo de operação computacionamente intensiva, porém sem ocupar a CPU durante esse período.

## Especificação do problema

O arquivo de entrada seguirá o seguinte formato

- dois inteiros, representando a dimensão do tabuleiro, N, e o número de threads (n_threads);
- para cada thread:
    - um inteiro com o identificador da thread;
    - um inteiro com o número do grupo da thread;
    - um inteiro com o número de posições que devem ser visitadas pela thread em seu trajeto;
    - para cada posição:
        - dois inteiros com as coordenadas da grade, x e y;
        - um inteiro com o tempo mínimo, em décimos de segundo, a permanecer naquela posição.

Sobre o formato da entrada, valem as seguintes regras:

- o espaçamento entre valores pode ser qualquer: podem haver vários valores em uma linha, um por linha, etc.;
- o número de espaços entre valores também pode variar;
- o valor máximo de N será 20 e o valor máximo de n_threads será N;
- o comprimento máximo de um trajeto será 2 x N;
- os valores de x e y estarão dentro do intervalo [0..N-1];
- o tempo de permanência estará sempre no intervalo [1..100]

O formato da entrada será garantido sem erros (não é preciso incluir código para verificar se os valores seguem a especificação). Inclusive, não há nenhuma restrição quanto à relação entre uma posição e a próxima no trajeto: cada posição no trajeto pode ser qualquer.

Um exemplo de arquivo de entrada será apresentado ao final desta página.

## Movimento pelo trajeto

Cada thread, ao ser criada, deve recever seu identificador, o identificador do seu grupo e o trajeto a ser seguido. Ela deve então se mover pelo trajeto, pelas posições (x,y) indicadas. Além da garantia já fornecida de que todos os movimentos na descrição do trajeto são válidos, a única regra a ser observada é:

*Estando em uma posição P1 e devendo se mover para a posição P2, uma thread só pode realmente se mover quando a posição P2 estiver vazia, ou ocupada apenas por threads do mesmo grupo da thread que deseja se mover.* Em outras palavras, se houver uma thread de outro grupo na posição P2, a thread que deseja se mover deve permanecer em P1 até que o movimento seja possível.

Se várias threads estiverem bloqueadas tentando se mover para uma certa posição já ocupada, não há uma ordem garantida em que as threads devem poder se mover, exceto pela restrição de mesmo.

Para simplificar, se isso for importante na sua implementação, pode-se assumir que cada thread iniciará seu trajeto de uma posição diferente.

Cada thread do pool, ao ser criada, deve receber como parâmetro um identificador (inteiro, iniciando em 1 e incrementado a cada nova thread criada) e executar a seguinte sequência de operações (expressa em C-pseudo-código):

## Detalhamento da sincronização

Em síntese, o objetivo principal deste exercício, do ponto de vista da disciplina, é a criação e controle de um grupo de threads, que deverão acessar cada posição da grade disponível de forma sincronizada, segundo a regra de movimentação apresentada. Essa sincronização deve ser implementada usando variáveis de exclusão mútua e de condição (uma solução com semáforos nesse caso seria mais complexa).

Uma possível solução poderia usar operações denominadas entra/sai que receberiam como parâmetros as coordenadas de uma posição. No seu movimento de P1 para P2, bastaria a uma thread executar a sequência **entra(P2.x,P2.y); sai(P1.x,p1.y);** sendo que as primitivas de sincronização estariam dento das funções **entra()** e **sai()**.

## Sobre a execução do programa:

Seu programa deve ler da entrada padrão e escrever na saída padrão. Ele não deve receber parâmetros de linha de comando. Não é preciso testar por erros na entrada, mas seu programa deve funcionar com qualquer combinação válida.

A única saída esperada para seu programa será gerada pelos comandos printf dentro da função passa_tempo. Caso você inclua mensagens de depuração ou outras informações que sejam exibidas durante a execução, certifique-se de removê-las da saída na execução da versão final.

O código deve usar apenas C padrão, sem bibliotecas além das consideradas padrão. O paralelismo de threads deve ser implementado usando POSIX threads (Pthreads) apenas.

O material desenvolvido por você deve executar sem erros nas [máquinas linux do laboratório de graduação](https://www.crc.dcc.ufmg.br/infraestrutura/laboratorios/linux). A correção será feita naquelas máquinas e programas que não compilarem, não seguirem as determinações quanto ao formato da entrada e da saída, ou apresentarem erros durante a execução, serão desconsiderados.

## O que deve ser entregue:

Você deve entregar um arquivo .zip contendo os seguintes elementos:

- código fonte do programa final produzido em C, devidamente comentado para destacar as decisões de implementação;
- makefile com as seguintes regras: clean (remove todos os executáveis, .o e outros temporários) e build (compila e gera o executável com nome **ex1**) - o comportamento default deve ser build;
- relatório em PDF.

Novamente, o material desenvolvido por você deve executar sem erros nas [máquinas linux do laboratório de graduação](https://www.crc.dcc.ufmg.br/infraestrutura/laboratorios/linux). A correção será feita naquelas máquinas e programas que não compilarem, não seguirem as determinações quanto a nomes, parâmetros de entrada e formato da saída, ou apresentarem erros durante a execução, serão penalizados.

O relatório não precisa ser longo, mas deve documentar as principais decisões de projeto consideradas - em particular, como foi implementada a sincronização entre as threads.

Preste atenção nos prazos: entregas com atraso serão aceitas por um ou dois dias, mas serão penalizadas.

### Sugestões de depuração

Faz parte do exercício desenvolver os casos de teste para o mesmo. Não serão fornecidos arquivos de teste além da entrada descrita a seguir. Vocês devem criar os seus próprios arquivos e podem compartilhá-los no fórum do exercício. Por outro lado, obviamente não é permitido discutir o princípio de sincronização da solução.

### Dúvidas?

Usem o fórum criado especialmente para esse exercício de programação para enviar suas dúvidas. **Não é permitido publicar código no fórum**! Se você tem uma dúvida que envolve explicitamente um trecho de código, envie mensagem por e-mail diretamente para o professor.

### Exemplo de entrada:

Segundo o formato descrito, as linhas a seguir definiriam uma grade 4x4, com três threads, de dois grupos, sendo que uma thread se move na horizontal e as outras duas, na vertical, e o trajeto vertical tem uma posição em comum com cada trajeto horizontal. A thread vertical se encontra primeiro com a thread do outro grupo (e tem que esperar) e depois com a do mesmo grupo (e aí as duas ocupam a mesma posição por algum tempo).

```
4 3
11 99 4
    0 0 50
    1 0 60
    2 0 90
    3 0 60
12 98 4
    0 2 10
    1 2 20
    2 2 60
    3 2 180
13 99 4
    2 3 40
    2 2 60
    2 1 10
    2 0 120
```

Não executei o programa ainda, mas a saída para essa entrada, em uma máquina com utillização baixa, deve ser algo mais ou menos como a lista a seguir. As linhas marcadas com um mesmo símbolo (*,+) podem aparecer em ordens diferentes. O tempo total de execução deveria ser da casa de 28 segundos. Mudanças nesse tempo total podem indicar erros na sincronização (mas pequenas variações são possíveis).

```
PTa(11,50) *
PTa(12,10) *
PTa(13,40) *
PTb(12,10)
PTa(12,20)
PTb(12,20)
PTa(12,30)
PTb(13,40)
PTb(11,50)
PTa(11,60)
PTb(12,30)
PTa(12,40) +
PTa(13,60) +
PTb(11,60)
PTa(11,90)
PTb(13,60)
PTa(13,10)
PTb(13,10)
PTa(13,120)
PTb(11,90)
PTa(11,60)
PTb(11,60)
PTb(12,180)
PTb(13,120)
```
