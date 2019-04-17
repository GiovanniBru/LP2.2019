#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_barrier_t barr;
long int bytes = 0;
int lock; //__sync_lock_test_and_set(&lock,1)
//int chdir(const char *pathname);

void *func(void *p){
	char reqs[100];
	char answ[100];
	FILE *arquivoREQ;//ponteiro para o arquivo de requisição(entrada)
	FILE *arquivoANSW;//ponteiro para o arquivo de resposta(saida)
	long int tamanho; //tamanho em bytes do arquivo
	int j = (int)p;//parametro 

	printf("[Thread #%d] - Executando.\n",j);

	//abrindo o req

	//CHDIR = change working directory 
	//chdir("/reqs");
	char *directory = "reqs";
	int ret;
	ret = chdir(directory);

	//req = fopen("req1.req", "r");//r = leitura
	if ((arquivoREQ = fopen("req1.req", "r")) == NULL){
		printf("ERRO! O arquivo não foi aberto!\n");
		exit(1);
	}

	//lendo o req

	while (!feof("req1.req")){ //NAO ESTA FUNCIONANDO	
  		fscanf("req1.req","%c",answ);
  		printf("%c",answ);
  	} 
	
	tamanho = calcularTamanhoArquivo(arquivoREQ);

	//FILES
	//FAZER MUDANÇA DE DIRETORIO PRO FILES
	

	//CRIAR O ANSW
	//MUDAR DIRETORIO PRO ANSW
	/*
	//arquivoANSW = fopen(answ, "a");// a = escrita
	if ((arquivoANSW = fopen("answ", "a")) == NULL){
		printf("ERRO! O arquivo não foi aberto!\n");
	} */

	//COPIAR ARQUIVOS PRO ANSW
	//fechando os arquivos
	fclose(reqs);
	//fclose(answ);
}

int calcularTamanhoArquivo(FILE *arquivo) {
 
    // guarda o estado ante de chamar a função fseek
    long posicaoAtual = ftell(arquivo);
 
    // guarda tamanho do arquivo
    long int tamanho;
 
    // calcula o tamanho
    fseek(arquivo, 0, SEEK_END);//fseek – movimenta a posição corrente de escrita ou leitura no arquivo para um local específico
    tamanho = ftell(arquivo);//ftell – retorna a posição corrente de leitura ou escrita no arquivo (em bytes)
 
    // recupera o estado antigo do arquivo
    fseek(arquivo, posicaoAtual, SEEK_SET);
 
    return tamanho;
}

int main(){
	char q[256];//quantidade de reqs
	char *directory = "reqs";
	int ret;
	ret = chdir(directory);//mudando diretorio para reqs

	//CALCULAR QUANTIDADE DE REQS PRA SUBSTITUIR NO NUMERO DE THREADS
	//int nthreads = atoi(q);
	int nthreads = 2; //usei para testar o func antes de calcular os reqs 

	printf("Serao criadas %d threads \n", nthreads);

	pthread_t threads[nthreads]; 
	for (int i = 1; i < nthreads; i++){
       		pthread_create(&threads[i], NULL, func, i);
        	pthread_join(threads[i], NULL);
	}
}
