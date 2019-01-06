typedef struct sescalonador {
	int disc_a[10], caixas, delta_t;
	Fila_FIFO *f[5];
	
} Escalonador;

//Inicializa o escalonador, alocando e inicializando as 5 filas, que serão atendidas por “caixas” caixas, onde cada  operação é tratada em “delta_t” minutos por um caixa, e o escalonamento utiliza a Disciplina de Atendimento  representada por {n_1; n_2; n_2; n_4; n_5}, nos termos do que foi definido na página 1 deste enunciado.
void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5); 

//Insere na fila “classe” o cliente de número “num_conta”, que pretende realizar “qtde_operacoes” operações bancárias.
int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes);

//Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, retirando-o da sua respectiva fila.
int e_obter_prox_num_conta(Escalonador *e);

//Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, sem retirá-lo da sua respectiva fila.
int e_consultar_prox_num_conta (Escalonador *e);

//Retorna a quantidade de operações bancárias que o próximo cliente das filas pretende realizar com o caixa, sem retirá-lo da sua respectiva fila.
int e_consultar_prox_qtde_oper (Escalonador *e);

//Retorna a próxima fila que será atendida de acordo com a Disciplina de Atendimento.
int e_consultar_prox_fila (Escalonador *e);

//Retorna a quantidade total (soma) de clientes esperando atendimento em todas as filas.
int e_consultar_qtde_clientes (Escalonador *e);

//Retorna o tempo necessário para que o próximo cliente a ser atendido realize todas as operações financeiras que deseja, sem retirá-lo da sua respectiva fila. Retornar -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_tempo_prox_cliente (Escalonador *e);

//Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome “nome_arq_conf”, retornando 1 em caso de sucesso e 0 caso contrário.
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);

//Executar a simulação do atendimento, lendo o arquivo de configuração de nome “nome_arq_in” e escrevendo o resultado do processamento para arquivo de nome “nome_arq_out”.
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);