#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Definindo a quantidade de fileiras e cadeiras
#define FILEIRAS 30
#define CADEIRAS 12
//Declarando matriz global com posições dos assentos
int assento[FILEIRAS][CADEIRAS];
//Declarando array global para guardar numeros aleatrios para tickets
int numero_do_sorteio[FILEIRAS*CADEIRAS] = {0};
//Declarando array global para saber se ticket é válido ou não
int numero_do_sorteio_aux[FILEIRAS*CADEIRAS] = {0};

//Declaração de variáveis globais
int id = 0, id_vencedor = 0, participantes = 0;



//--FUNCAO LIMPAR TELA--
void limpar_tela() {
  printf("\x1b[H\x1b[J");
}

//Set para pegar dados de Data e/ou Tempo

//Retornar dia || mes || ano atual
int get_date(char tipo) {
  struct tm *local, *gm;
  time_t t;
  t = time(NULL);
  local = localtime(&t);

  if(tipo == 'd')
    return local->tm_mday;
  else if(tipo == 'm')
    return local->tm_mon + 1;
  else if(tipo == 'y')
    return local->tm_year + 1900;
}

//Retornar horas || minutos || segundos
int get_time(char tipo) {
  struct tm *local, *gm;
  time_t t = time(0);
  t = time(NULL);
  local = localtime(&t);

  if(tipo == 'h')
    return local->tm_hour;
  else if(tipo == 'm')
    return local->tm_min;
  else if(tipo == 's')
    return local->tm_sec;
}

//Funcao que armazena numeros aleatórios em array numero_do_sorteio[cadeiras*flieiras]
void sortear() {
  int repetiu = 0;
  srand( (unsigned)time(NULL) );
  for(int i=0 ; i < 360 ; i++) {
    numero_do_sorteio[i] = 1 + ( rand() % 360 );
    do{
      repetiu = 0;
      for(int j = 0; j < i; j++) {
        if(numero_do_sorteio[i] == numero_do_sorteio[j]) {
          repetiu = 1;
          numero_do_sorteio[i] = 1 + ( rand() % 360 );
        }
      }
    }while(repetiu == 1);
  }
}

//Funcao que permite pegar numero aleatorio do sorteio
int get_numero_do_sorteio(int i) {
  return numero_do_sorteio[i];
}

//Funcao que sorteia um ticket para receber brinde
int sorteia_vencedor() {
  srand( (unsigned)time(NULL) );
  do {
    id_vencedor = rand() % id;
  }while(numero_do_sorteio_aux[id_vencedor] == 0);
  return numero_do_sorteio[id_vencedor];
}

//Funcao que permite alterar a visibilidade do cursor no terminal Linux
void set_cursor(int visible) {
  if(!visible) { // caso não seja visivel (visible == 0)
    printf("\e[?25l");
    fflush(stdout);
  }
  if(visible) { // caso seja visivel (visible >= 1)
    printf("\e[?25h");
    fflush(stdout);
  }
}

//--FUNCAO GERAR ASSENTOS--
//Atribuindo todos os assentos para disponíveis (1)
void gerar_assentos() {
    for(int i = 0; i < FILEIRAS; i++) {
      for(int j = 0; j < CADEIRAS; j++) {
        assento[i][j] = 1;
      }
    }
}

//Função que altera a disponibildidade do assento (1 -> disponivel; 0 -> ocupado)
int ocupar_assento(int fileira, int cadeira) {
  assento[fileira-1][cadeira-1] = 0;
}

void mostrar_welcome_screen() {
  limpar_tela();
  printf("Iniciando o sistema...");
  set_cursor(0);
  sleep(2);
  set_cursor(1);
  limpar_tela();
}

void mostrar_assentos_normais() {
  printf("Retornar á tela principal: 0 \n\n");
  char disponivel = ' ';
  printf("      ");
  for(int i = 0; i < CADEIRAS; i++) {
    if(i < 9)
      printf("-%d-  ", i+1);
    else {
      printf("-%d- ", i+1);
    }
  }
  printf("\n");
  for(int i = 4; i < FILEIRAS; i++) {
    for(int j = 0; j < CADEIRAS; j++) {
      disponivel = ' ';
      if(!assento[i][j])
        disponivel = 'x';
        if(j == 0) {
          if(i < 9)
            printf("%d->   [%c]  ", i+1, disponivel);
          else
            printf("%d->  [%c]  ", i+1, disponivel);
        }
        else
          printf("[%c]  ", disponivel);
    }
    printf("\n");
  }
}

void mostrar_assentos_convidados() {
  printf("Retornar á tela principal: 0 \n\n");  char disponivel = ' ';
  printf("      ");
  for(int i = 0; i < CADEIRAS; i++) {
    if(i < 9)
      printf("-%d-  ", i+1);
    else {
      printf("-%d- ", i+1);
    }
  }
  printf("\n");
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < CADEIRAS; j++) {
      disponivel = ' ';
      if(!assento[i][j])
        disponivel = 'x';
        if(j == 0) {
          if(i < 9)
            printf("%d->   [%c]  ", i+1, disponivel);
          else
            printf("%d->  [%c]  ", i+1, disponivel);
        }
        else
          printf("[%c]  ", disponivel);
    }
    printf("\n");
  }
}


void mostrar_assentos_pne() {
  printf("Retornar á tela principal: 0 \n\n");
  char disponivel = ' ';
  printf("      ");
  for(int i = 0; i < CADEIRAS; i++) {
    if(i < 9)
      printf("-%d-  ", i+1);
    else {
      printf("-%d- ", i+1);
    }
  }
  printf("\n");
  for(int i = 2; i < 4; i++) {
    for(int j = 0; j < CADEIRAS; j++) {
      disponivel = ' ';
      if(!assento[i][j])
        disponivel = 'x';
        if(j == 0) {
          if(i < 9)
            printf("%d->   [%c]  ", i+1, disponivel);
          else
            printf("%d->  [%c]  ", i+1, disponivel);
        }
        else
          printf("[%c]  ", disponivel);
    }
    printf("\n");
  }
}

//Funcao que permite escolher qual tela de assentos mostrar
void escolher_tela(int tipo_de_ticket) {
  switch (tipo_de_ticket) {
    case 1:
      mostrar_assentos_normais();
      break;
    case 2:
      mostrar_assentos_convidados();
      break;
    case 3:
      mostrar_assentos_convidados();
      break;
    case 4:
      mostrar_assentos_pne();
      break;
    default:
      printf("Tipo de ticket invalido(em: função 'escolher_tela()')\n");
  }
}

//Funcao que gera e guarda informações de novo ticket
struct Ticket {
    int ticket_number, ticket_sorteio, ticket_fileira, ticket_cadeira, ticket_tipo;
    int ticket_dia, ticket_mes, ticket_ano;
    int ticket_horas, ticket_minutos, ticket_segundos;
    char ticket_isset; //y para verdadeiro
} ticket[360];
void gerar_ticket(int fileira, int cadeira, int tipo_de_ticket) {
  ticket[id].ticket_number = id+1;
  ticket[id].ticket_tipo = tipo_de_ticket;
  ticket[id].ticket_fileira = fileira;
  ticket[id].ticket_cadeira = cadeira;
  ticket[id].ticket_isset = 'y';
  ticket[id].ticket_dia = get_date('d');
  ticket[id].ticket_mes = get_date('m');
  ticket[id].ticket_ano = get_date('y');
  ticket[id].ticket_horas = get_time('h');
  ticket[id].ticket_minutos = get_time('m');
  ticket[id].ticket_segundos = get_time('s');
  if(tipo_de_ticket != 2) {
    ticket[id].ticket_sorteio = get_numero_do_sorteio(participantes);
    numero_do_sorteio_aux[participantes] = 1;
    participantes++;
  }
  id++;
}

//Funcao que gera/mostra ticket -> (assento, horário e número de sorteio)
void mostrar_ticket(int id) {
  limpar_tela();
  printf("\nTICKET Nº %d\n\n", ticket[id-1].ticket_number);
  printf("Ticket gerado em: %d/%d/%d\n", ticket[id-1].ticket_dia, ticket[id-1].ticket_mes, ticket[id-1].ticket_ano);
  printf("Horário: %d:%02d:%02d\n\n", ticket[id-1].ticket_horas, ticket[id-1].ticket_minutos, ticket[id-1].ticket_segundos);
  printf("Fileira: %d   Cadeira: %d\n", ticket[id-1].ticket_fileira, ticket[id-1].ticket_cadeira);
  if(ticket[id-1].ticket_tipo != 2) {
    printf("-------------------\n");
    printf("NÚMERO DO SORTEIO: %d\n", ticket[id-1].ticket_sorteio);
  }
  while(1) {
    printf("\n\nDigite 'Ok' para continuar...\n");
    char continuar[20];
    scanf("%s", continuar);
    for(int i = 0; i < strlen(continuar); i++) {
      continuar[i] = toupper(continuar[i]);
    }
    if(strcmp(continuar, "OK") == 0)
      return;
  }
}

void mostrar_tela_sorteio() {
  int conta_brinde = 1, num_vencedor = 0, end = 0, resposta = 0;
  char confirma = 'n';
  do {
    limpar_tela();
    printf("Vencedor do Brinde!!!\n\n");
    num_vencedor = sorteia_vencedor();
    printf("Ticket com número de sorteio igual a: %d\n", num_vencedor);
    printf("-------------------------------------\n");
    printf("Encerrar programa (9)\n\n");
    scanf("%d", &resposta);
    if(resposta == 9) {
        end = 1;
        return;
    }
  else {
    printf("Opção Inválida!\n");
    set_cursor(0);
    sleep(2);
    set_cursor(1);
  }
  conta_brinde++;
  }while(end == 0);
}


// FUNCAO PARA DIALOGO DE ESCOLHER ASSENTO
void escolher_assento(int tipo_de_ticket) {
  int minimo_fileira = 0, max_fileira = 0, fileira_escolhida = 0, cadeira_escolhida = 0, disponivel = 0;
  switch (tipo_de_ticket) {
    case 1:
      minimo_fileira = 5;
      max_fileira = 30;
      break;
    case 2:
      minimo_fileira = 1;
      max_fileira = 2;
      break;
    case 3:
      minimo_fileira = 1;
      max_fileira = 2;
      break;
    case 4:
      minimo_fileira = 3;
      max_fileira = 4;
      break;
  }
  do {
    do {
      printf("\nFileira Desejada: ");
      scanf("%d", &fileira_escolhida);
      if(fileira_escolhida == 0)
        return;
      if(fileira_escolhida < minimo_fileira || fileira_escolhida > max_fileira) {
        printf("\nAVISO: A fileira escolhida não existe ou não é permitida para este tipo de ticket.\nPor favor, tente novamente!\n");
        set_cursor(0);
        sleep(3);
        set_cursor(1);
        limpar_tela();
        escolher_tela(tipo_de_ticket);
      }
    } while(fileira_escolhida < minimo_fileira || fileira_escolhida > max_fileira);
    do {
      printf("Cadeira Desejada: ");
      scanf("%d", &cadeira_escolhida);
      if(cadeira_escolhida == 0)
        return;
      if(cadeira_escolhida < 1 || cadeira_escolhida > 12) {
        printf("AVISO: A cadeira escolhida não existe.\nPor favor, tente novamente!\n");
        set_cursor(0);
        sleep(3);
        set_cursor(1);
        limpar_tela();
        escolher_tela(tipo_de_ticket);
      }
    } while(cadeira_escolhida < 1 || cadeira_escolhida > 12);
    disponivel = assento[fileira_escolhida-1][cadeira_escolhida-1];
    //Assento está ocupado?
    if(disponivel == 0 ) {
      printf("AVISO: Este assento não está disponível! Por favor, tente outro!\n" );
      set_cursor(0);
      sleep(3);
      set_cursor(1);
      limpar_tela();
      escolher_tela(tipo_de_ticket);
    }
    //Assento está disponível?
    else if( disponivel == 1) {
      ocupar_assento(fileira_escolhida, cadeira_escolhida);
      printf("Gerando Ticket...\n");
      sleep(3);
      gerar_ticket(fileira_escolhida, cadeira_escolhida, tipo_de_ticket);
      mostrar_ticket(id);
    }
  } while(disponivel == 0);
}

//--FUNCAO CADASTRAR USUARIO--
int cadastrar_usuario() {
  //Declaração de variáveis
  int tipo_de_ticket = 0, fileira=0, cadeira=0, disponivel=0;
  char sair='n', resposta;
  //Tela de Inicio
  mostrar_welcome_screen();
  sortear();
  //Perguntado tipo de ticket enquanto ele for diferente de 9
  do {
    limpar_tela();
    if(id > 359 ) {
      printf("Não há mais cadeiras disponíveis!\nIniciando sorteio de brindes...\n");
      set_cursor(0);
      sleep(3);
      set_cursor(1);
      sair = 's';
      return 0;
    }
    printf("\nNOVO TICKET\n\n");
    printf("Selecione o Tipo de Assento:\n\n");
    printf("1 - Assento Comum :\n");
    printf("2 - Assento p/ Convidado:\n");
    printf("3 - Assento p/ Professor:\n");
    printf("4 - Assento P.N.E:\n");
    printf("--------------------\n");
    printf("9 - Fazer Sorteio:\n\n");
    scanf("%d", &tipo_de_ticket);

    //Ticket é do tipo 9?
    if (tipo_de_ticket == 9) {
      if(id < 2) {
        printf("AVISO: Para sortear o brinde é necessário ter mais de um participante!\n");
        set_cursor(0);
        sleep(3);
        set_cursor(1);
      }
      else if(participantes < 2) {
        printf("AVISO: Para sortear o brinde é necessário ter mais de um participante!(Convidados do palestrante não são participantes)\n");
        set_cursor(0);
        sleep(3);
        set_cursor(1);
      }
      else {
        printf("Após sortear o brinde o programa será encerrado, deseja mesmo interromper o cadastro de clientes agora? ('s' | 'n') \n");
        scanf(" %c", &resposta);
        if(resposta == 's' || resposta == 'S') {
            sair = 's';
        }
      }
    }
    //Ticket é maior que 4 ou menor do que 1 ?
    else if(tipo_de_ticket > 4 || tipo_de_ticket < 1) {
      printf("AVISO: Digite um tipo de ticket válido!\n");
      set_cursor(0);
      sleep(2);
      set_cursor(1);
    }
    //Ticket é de um tipo conhecido?
    if(tipo_de_ticket < 5 && tipo_de_ticket > 0) {
      if(tipo_de_ticket == 1) {
        limpar_tela();
        mostrar_assentos_normais();
      }
      else if(tipo_de_ticket == 2 || tipo_de_ticket == 3) {
        limpar_tela();
        mostrar_assentos_convidados();
      }
      else {
        limpar_tela();
        mostrar_assentos_pne();
      }
      escolher_assento(tipo_de_ticket);
    }
  } while(sair != 's');
  mostrar_tela_sorteio();
}
