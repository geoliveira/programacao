#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"
#include "logtree.h"
#include "escalonador.h"

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5) {
	int j=5;
	//Inicialização dos valores dinâmicos, que estão nos indices 0 a 4, e estáticos, que estão nos índices 5 a 9.
	(*e).disc_a[0+j] = (*e).disc_a[0] = n_1;
	(*e).disc_a[1+j] = (*e).disc_a[1] = n_2;
	(*e).disc_a[2+j] = (*e).disc_a[2] = n_3;
	(*e).disc_a[3+j] = (*e).disc_a[3] = n_4;
	(*e).disc_a[4+j] = (*e).disc_a[4] = n_5;
	
	//Inicialização das 5 filas e da quantidade de caixa e do delta T
	for (int i=0; i<5; i++) f_inicializar(&(*e).f[i]);
	(*e).caixas = caixas;
	(*e).delta_t = delta_t;
}

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
	//Caso o inteiro classe não esteja nos valores entre 1 e 5, função é interrompida
	if (!(classe >= 1 && classe <= 5)) return -1;

	//Inserção dos valores, passados como parâmetros, na fila.
	int indice;
	indice = classe-1;
	f_inserir(&(*e).f[indice], num_conta, qtde_operacoes*(*e).delta_t); //Observação: o valor da fila condiz com o tempo individual do cliente
	
	return 1;
}

//Abaixo as funções são semelhantes. Seguem o padrão do vetor disc_a.
int e_obter_prox_num_conta(Escalonador *e) {
	int num_conta;
	int i;

	for (i=0; i<5; i++) //Percorre os indices de 0 a 4, cujo tem valores dinâmicos. A variação ocorre por conta do andamento dos clientes em relação a Disciplina de Atendimento. 
		if ((*e).disc_a[i] >= 1 && (*e).f[i] != NULL) { //Caso (*e).disc_a[i] == 0, então nessa rodada não há mais clientes da respectiva classe a ser chamado
			num_conta = f_obter_proxima_chave(&(*e).f[i]);
			(*e).disc_a[i] -= 1;

			return num_conta;
		}
	
	//Aqui tratamos quando a rodada acaba, que significa que os valores dos indíces 0 a 4 estão zerados, ou não há mais clientes a serem chamados
	for (i=0; i<5; i++)
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) //Caso ainda tenha cliente na respectiva fila e seu atendimento obedeça a Disciplina de Atendimento, os valores de 0 a 4 recebem os valores originais da Disciplina de Atendimento
			(*e).disc_a[i] = (*e).disc_a[i+5];

	for (i=0; i<5; i++) 
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) //Se houver cliente na respectiva fila, acontece a chamada recursiva para que ele seja chamado
			return e_obter_prox_num_conta(e);

	//Não há mais clientes para ser chamado
	return -1;
}

//Segue a mesma lógica da função int e_obter_prox_num_conta(Escalonador *e)
int e_consultar_prox_num_conta (Escalonador *e) {
	int num_conta;
	int i;

	for (i=0; i<5; i++) 
		if ((*e).disc_a[i] >= 1 && (*e).f[i] != NULL) {
			num_conta = f_consultar_proxima_chave(&(*e).f[i]);

			return num_conta;
		}
	
	for (i=0; i<5; i++)
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			(*e).disc_a[i] = (*e).disc_a[i+5];
	
	for (i=0; i<5; i++) 
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			return e_consultar_prox_num_conta(e);

	return 0;
}

//Segue a mesma lógica da função int e_obter_prox_num_conta(Escalonador *e)
int e_consultar_prox_qtde_oper (Escalonador *e) {
	int qtd_op;
	int i;

	for (i=0; i<5; i++) 
		if ((*e).disc_a[i] >= 1 && (*e).f[i] != NULL) {
			qtd_op = f_consultar_proximo_valor(&(*e).f[i])/(*e).delta_t;
			
			return qtd_op;
		}
	
	for (i=0; i<5; i++)
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			(*e).disc_a[i] = (*e).disc_a[i+5];

	for (i=0; i<5; i++) 
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			return e_consultar_prox_qtde_oper(e);

	return -1;
}

//Segue a mesma lógica da função int e_obter_prox_num_conta(Escalonador *e)
int e_consultar_prox_fila (Escalonador *e) {
	int i;
	
	for (i=0; i<5; i++) 
		if ((*e).disc_a[i] >= 1 && (*e).f[i] != NULL)
			return i+1; //O retorno da função varia entre 1 e 5, os valores referentes as classes dos clientes
	
	for (i=0; i<5; i++)
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			(*e).disc_a[i] = (*e).disc_a[i+5];

	for (i=0; i<5; i++) 
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			return e_consultar_prox_fila(e);

	return -1;
}

int e_consultar_qtde_clientes (Escalonador *e) {
	int somatorio = 0;

	for (int i=0; i<5; i++)
		somatorio += f_num_elementos(&(*e).f[i]); //Somatório da quantidade de clientes em cada classe
	
	return somatorio;
}

//Segue a mesma lógica da função int e_obter_prox_num_conta(Escalonador *e)
int e_consultar_tempo_prox_cliente (Escalonador *e) {
	int tempo;
	int i;

	for (i=0; i<5; i++) 
		if ((*e).disc_a[i] >= 1 && (*e).f[i] != NULL) {
			tempo = f_consultar_proximo_valor(&(*e).f[i]);
			
			return tempo;
		}
	
	for (i=0; i<5; i++)
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			(*e).disc_a[i] = (*e).disc_a[i+5];

	for (i=0; i<5; i++) 
		if (f_num_elementos(&(*e).f[i]) != 0 && (*e).disc_a[i+5] >= 1) 
			return e_consultar_tempo_prox_cliente(e);

	return -1;
}

//Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome “nome_arq_conf”, retornando 1 em caso de sucesso e 0 caso contrário.
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf) {
	int caixas, delta, n1, n2, n3, n4, n5, conta, operacao, i;
    char classe[7];

	FILE *arq = fopen(nome_arq_conf, "r");

	//Pelo nome do arquivo entrado, é lido a configuração do programa. É necessário que este arquivo esteja no diretório filasim_cases. Caso contrário retornará erro.
	if (arq == NULL) {
		printf("Arquivo entrado não existe no diretório filasim_cases\n");
		return 0;
	}
	
	//As 3 primeiras linhas do arquivo de configuração são lidas, e em seguida é inicializado o Escalonador
    fscanf(arq,"qtde de caixas = %d\n", &caixas);
    fscanf(arq,"delta t = %d\n", &delta);
    fscanf(arq,"disciplina de escalonamento = {%d,%d,%d,%d,%d}\n", &n1, &n2, &n3, &n4, &n5);

    e_inicializar(e, caixas, delta, n1, n2, n3, n4, n5);

    //A partir da inicialização, os clientes são inseridos nas suas respectivas filas
    while (fscanf(arq,"%s - conta %d - %d operacao(oes)\n", classe, &conta, &operacao) != EOF) {
        if (strcmp(classe, "Premium") == 0) e_inserir_por_fila(e , 1, conta, operacao);
        if (strcmp(classe, "Ouro") == 0) e_inserir_por_fila(e , 2, conta, operacao);
        if (strcmp(classe, "Prata") == 0) e_inserir_por_fila(e , 3, conta, operacao);
        if (strcmp(classe, "Bronze") == 0) e_inserir_por_fila(e , 4, conta, operacao);
        if (strcmp(classe, "Comum") == 0) e_inserir_por_fila(e , 5, conta, operacao);
    }

    fclose(arq); //Fechamento do arquivo de configuração

    return 1;
}

//Aqui os nomes dos arquivos já obedecem o padrão entrada-X.txt e saida-X.txt. O arquivo de saida é salvo na mesma pasta onde está as APIs
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
    //Inicialização do Registrador L e das variavéis que serão usadas na impressão dos valores do programa e abertura do arquivo saida-X.txt
    Log *l;

    log_inicializar(&l);
    e_conf_por_arquivo(e, nome_arq_in);

    FILE *arq;
    arq = fopen(nome_arq_out, "w");

    int cliente_por_caixa[(*e).caixas], caixas[(*e).caixas], mintempo, mincaixa, clock, tempoatd, conta, op, fila, i,j;
    char *classe[5] = {"Premium","Ouro","Prata","Bronze","Comum"};
    float ops_cliente[5], t_cliente_por_classe;

    for (j=0; j<5; j++) ops_cliente[j] = 0;

    for (j=0; j<(*e).caixas; j++) caixas[j] = 0;
    
    for (j=0; j<(*e).caixas; j++) cliente_por_caixa[j] = 0;

    tempoatd = 0; //O tempo de atendimento é inicializado com 0
	
	//Enquanto houver cliente a ser chamado, os seus respectivos valores seram impressos no arquivo saida-X.txt
    while (e_consultar_prox_num_conta(e)) { 
        //Como o próximo cliente será atendido pelo caixa de menor número com menor tempo disponível, nos basearemos pelos valores crescentes iniciais
        mintempo = caixas[0];
        clock = mintempo; //O tempo 'atual' é sempre o tempo do caixa de maior tempo de atendimento, mas para isso nos pegamos um valor referência
        mincaixa = 0;

        //Pegando valor do caixa que virá a atender o próximo cliente
        for (i=0; i<(*e).caixas; i++)
            if (caixas[i] < mintempo) {
                mintempo = caixas[i]; 
                mincaixa = i;
            }

        if (caixas[mincaixa] != 0) tempoatd = caixas[mincaixa]; //Observação: Caso contrário, tempoatd = 0, o que significa que está começando a 1ª rodada de atendimento
        
        fila = e_consultar_prox_fila(e); //Valor da fila do cliente que que são de 1 a 5
        classe[fila-1]; // Vetor de string com o nome das classes
        cliente_por_caixa[mincaixa] += 1; //Somatório da quantidade de clientes atendidos por determinado caixa
        caixas[mincaixa] += e_consultar_tempo_prox_cliente(e); //Observação: o caixa guarda o tempo individual de cada cliente atendido
        conta = e_consultar_prox_num_conta(e); //Número da conta do próximo cliente
        op = e_consultar_prox_qtde_oper(e); //Quantidade de operação do mesmo
        ops_cliente[fila-1] += op; //Somatório das operações dos clientes por classe

        //Impressão no arquivo saida-X.txt dos valores do cliente e em seguida registramos atendimento do mesmo
        fprintf(arq, "T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n", tempoatd, mincaixa+1, classe[fila-1], conta, op);

        log_registrar(&l, conta, fila, tempoatd, mincaixa+1);

        e_obter_prox_num_conta(e); // Chamamos o próximo
        
        for (i=0; i<(*e).caixas; i++)
            if (caixas[i] > clock) clock = caixas[i]; // O tempo é atualizado
    }
    
    //Impressão dos valores estatísticos do atentimento do banco

    fprintf(arq, "Tempo total de atendimento: %d minutos.\n", clock);
    
    for (j=1; j<5; j++) {
    	fprintf(arq, "Tempo medio de espera dos %d clientes %s: %.2f\n", log_obter_contagem_por_classe(&l, j), classe[j-1], log_media_por_classe(&l, j));
    }
        
	fprintf(arq, "Tempo medio de espera dos %d clientes %s: %.2f\n", log_obter_contagem_por_classe(&l, 5), "Comuns", log_media_por_classe(&l, 5));

    for (j=1; j<=5; j++) {
    	t_cliente_por_classe = log_obter_contagem_por_classe(&l, j); //Observação: variavel t_cliente_por_classe do tipo float recebe o retorno inteiro da função. A "transformação" é feita para garantir o dado.
    	fprintf(arq, "Quantidade media de operacoes por cliente %s = %.2f\n", classe[j-1], ops_cliente[j-1]/t_cliente_por_classe);
    }
    
    for (j=0; j<(*e).caixas; j++) fprintf(arq, "O caixa de número %d atendeu %d clientes.\n", j+1, cliente_por_caixa[j]);
        
    fclose(arq); // Feito a impressão dos dados estatísticos e de todos os clientes e seus repectivos valores, o arquivo saida-X.txt é gerado.
}