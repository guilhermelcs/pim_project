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
  time_t t;
  t = time(NULL);
  local = localtime(&t);

  if(tipo == 'h')
    return local->tm_hour;
  else if(tipo == 'm')
    return local->tm_min;
  else if(tipo == 's')
    return local->tm_sec;
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
  printf("Bem-vindo ao sistema de cadastro de usuários!\nPor favor, aguarde, estamos preparando o sistema...\n");
  sleep(2);
  limpar_tela();
}

void mostrar_assentos_normais() {
  printf("----------------------------------------------------------------");
  char disponivel = ' ';
  printf("      ");
  // for(int i = 0; i < CADEIRAS; i++) {
  //   if(i < 9)
  //     printf("-%d-  ", i+1);
  //   else {
  //     printf("-%d- ", i+1);
  //   }
  // }
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
  //printf("----------------------------------------------------------------\n\n");
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
  printf("----------------------------------------------------------------");
  char disponivel = ' ';
  printf("      ");
  // for(int i = 0; i < CADEIRAS; i++) {
  //   if(i < 9)
  //     printf("-%d-  ", i+1);
  //   else {
  //     printf("-%d- ", i+1);
  //   }
  // }
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
      mostrar_assentos_pne();
      break;
    default:
      printf("Tipo de ticket invalido(em: função 'escolher_tela()')\n");
  }
}

//Funcao que gera e guarda informações de novo ticket
struct Ticket {
    int ticket_number, ticket_fileira, ticket_cadeira;
    int ticket_dia, ticket_mes, ticket_ano;
    int ticket_horas, ticket_minutos, ticket_segundos;
    char ticket_isset; //y para verdadeiro
} ticket[360];
int id = 0;
void gerar_ticket(int fileira, int cadeira) {
  ticket[id].ticket_number = id+1;
  ticket[id].ticket_fileira = fileira;
  ticket[id].ticket_cadeira = cadeira;
  ticket[id].ticket_isset = 'y';
  ticket[id].ticket_dia = get_date('d');
  ticket[id].ticket_mes = get_date('m');
  ticket[id].ticket_ano = get_date('y');
  ticket[id].ticket_horas = get_time('h');
  ticket[id].ticket_minutos = get_time('m');
  ticket[id].ticket_segundos = get_time('s');
  id++;
}

// //Funcao que pega informações do ticket escolhido
// struct Ticket get_ticket(int id) {
//   if(ticket[id].ticket_isset == 'y')
//     return ticket[id];
// }

//Funcao que gera/mostra ticket -> (assento, horário e número de sorteio)
int n_cont =  0;
void mostrar_ticket(int fileira, int cadeira, int tipo_de_ticket) {
  limpar_tela();
  printf("\nTICKET Nº %d\n\n", ticket[n_cont].ticket_number);
  printf("Ticket gerado em: %d/%d/%d\n", ticket[n_cont].ticket_dia, ticket[n_cont].ticket_mes, ticket[n_cont].ticket_ano);
  printf("Horário: %d:%d:%d\n\n", ticket[n_cont].ticket_horas, ticket[n_cont].ticket_minutos, ticket[n_cont].ticket_segundos);
  printf("Fileira: %d   Cadeira: %d\n", ticket[n_cont].ticket_fileira, ticket[n_cont].ticket_cadeira);
  if(tipo_de_ticket != 2) {
    printf("-------------------\n");
    printf("NÚMERO DO SORTEIO: \n");
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
  n_cont++;
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
      minimo_fileira = 3;
      max_fileira = 4;
      break;
  }
  do {
    do {
      printf("Fileira Desejada: ");
      scanf("%d", &fileira_escolhida);
      if(fileira_escolhida == 0)
        return;
      if(fileira_escolhida < minimo_fileira || fileira_escolhida > max_fileira) {
        printf("AVISO: A fileira escolhida não existe ou não é permitida para este tipo de ticket.\nPor favor, tente novamente!\n");
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
      gerar_ticket(fileira_escolhida, cadeira_escolhida);
      mostrar_ticket(fileira_escolhida, cadeira_escolhida, tipo_de_ticket);
    }
  } while(disponivel == 0);
}

//--FUNCAO CADASTRAR USUARIO--
int cadastrar_usuario() {
  //Declaração de variáveis
  int tipo_de_ticket = 0, fileira=0, cadeira=0, disponivel=0;
  int normal=1, convidado=2, pne=3;
  //Tela de Inicio
  mostrar_welcome_screen();
  //Perguntado tipo de ticket enquanto ele for diferente de 9
  limpar_tela();
  escolher_tela(2);
  escolher_tela(3);
  escolher_tela(1);
  do {
    printf("\nNOVO TICKET\n\n");
    printf("Selecione o Tipo de Assento:\n\n");
    printf("1 - Assento Comum :\n");
    printf("2 - Assento Convidado/Professor:\n");
    printf("3 - Assento P.N.E:\n");
    printf("--------------------\n");
    printf("9 - Fazer Sorteio:\n\n");
    scanf("%d", &tipo_de_ticket);
    //Ticket é do tipo 9?
    if (tipo_de_ticket == 9) {
      return 0;
    }
    //Ticket é maior que 3 ou menor do que 1 ?
    else if(tipo_de_ticket > 3 || tipo_de_ticket < 1) {
      printf("AVISO: Digite um tipo de ticket válido!\n");
      set_cursor(0);
      sleep(2);
      set_cursor(1);
    }
    //Ticket é de um tipo conhecido?
    if(tipo_de_ticket < 4 && tipo_de_ticket > 0) {
      if(tipo_de_ticket == 1) {
        limpar_tela();
        mostrar_assentos_normais();
      }
      else if(tipo_de_ticket == 2) {
        limpar_tela();
        mostrar_assentos_convidados();
      }
      else {
        limpar_tela();
        mostrar_assentos_pne();
      }
      escolher_assento(tipo_de_ticket);
    }
  } while(tipo_de_ticket != 9);
}
