#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"
#include "logtree.h"
#include "escalonador.h"

int main(int argc, char const *argv[]) {
    Escalonador e;
    
    //O programa recebe apenas, como parâmetro na linha de comando, um inteiro X no intervalo [1;9999]
    if (argc != 1 && atoi(argv[1])>0 && atoi(argv[1]) < 10000) {
        //inicialização das variáveis
        int tam_numero, tam_arquivo, i,j;
        char numero[4];
        char arquivo_in[] = "filasim_cases/entrada-0000.txt";
        char arquivo_out[] = "saida-0000.txt";
        
        strcpy(numero, argv[1]);
        tam_numero = strlen(numero);
        //copia o número entrado para a string que virá ser o nome do arquivo de entrada-X.txt
        tam_arquivo = strlen(arquivo_in);
        j = tam_arquivo-5;
        for (i=tam_numero-1; i>=0; i--) arquivo_in[j--] = numero[i];
        printf("Arquivo entrado: %s\n", arquivo_in);

        //copia o número entrado para a string que virá ser o nome do arquivo de saida-X.txt
        tam_arquivo = strlen(arquivo_out);
        j = tam_arquivo-5;
        for (i=tam_numero-1; i>=0; i--) arquivo_out[j--] = numero[i];
        printf("Saída do programa: %s\n", arquivo_out);

        //inicia o programa
        e_rodar(&e, arquivo_in, arquivo_out);
    }
    
    return 1;
}
