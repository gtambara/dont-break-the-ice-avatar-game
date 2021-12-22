/*  @file/matricula: 180017021.c
 *          @author: Gabriel Tambara Rabelo
 *      @disciplina: Algoritmos e Programacão de Computadores
 *        @Programa: Don't break the ice pirata
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/*
Nome:		flush_in
Descrição:	Limpeza de buffer, facilitando a validaçao de entrada.
Argumentos:	nill
Retorno:	nill
Fonte:		https://pt.stackoverflow.com/questions/9427/limpeza-do-buffer-do-teclado-ap%C3%B3s-scanf */
void flush_in(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

/*
Nome:		espera
Descricao:	controle de fluxo no terminal para leitura de dados na tela antes da atualizaçao 
Argumentos: 	nill
Retorno: 	nill
*/
void espera(){
	printf("Digite algo para continuar:\n");
	scanf("%*c");
	flush_in();
	printf("\n");
}
							
/*
Nome:		nomeia
Descrição:	Nomeia os personagens atraves de vetores especificos 
Argumentos:	'nome'(referencia ao nome do personagem); 'x'(indice do jogador)
Retorno:
*/
void nomeia(char *nome, int x){
	int i;
	printf("Jogador %d, digite seu nome de guerra. Maximo de 25 caracteres\n", x);
	scanf("%[^\n]24s",nome);
}

/*
Nome:		mostra
Descrição: 	Imprime os vetores inteiros na tela e a interface de ajuda
Argumentos:	'tela'(matrix do campo)
Retorno:	nill
*/
void mostra(char tela[10][20]){
	int y, x;
	printf("\033[1;31m");
	printf("-1234567890\033[1;33m1234567890-\n");
	printf("\033[0;37m");
	printf("----------------------	\n");
	for(y=0; y<10; y++){
		for(x=0; x<20; x++){
			if(x==0){
				printf("!");
			}
			printf("\033[0;34m");
			if(tela[y][x] == '#' ){
				printf("\033[0;34m");
			}
			else if(tela[y][x] == 'U' ){
				printf("\033[1;37m");
			}
			else if(tela[y][x] == '_' ){
				printf("\033[0;35m");
			}
			printf("%1c", tela[y][x]);
			printf("\033[0;37m");
			if(x==19){
				printf("!");
				printf("\033[0;31m");
				printf("%d", 1+y);
				printf("\033[0;37m");
			}
		}
	printf("\n");
	}
	printf("----------------------\n");
}
/*
Nome:		cria_matriz
Descrição:	Inicializa mapa de jogo inicial
Argumentos:	'tela'(mapa de jogo)
Retorno:	nill
*/
void cria_matriz(char tela[10][20]){
	int y,x;
	for(y=0; y<10; y++){
		for(x=0; x<20; x++){
			tela[y][x] = '#';
		}
	}
}

/*
Nome:		gelao
Descrição:	Define em quais posicoes dos vetores o aang ficara atraves de caracteres especificos.
Argumentos:	'tela'(tela do jogo); 'xu'(posicao no eixo x do usuario); 'yu'(posicao no eixo y do usuario)
Retorno:	nill
*/
void gelao(char tela[10][20], int* xu, int* yu){
	int y, x;
	srand((unsigned)time(NULL));
	*yu = y = rand()%5;
	*xu = x = rand()%15;
	tela[y+2][x+2] = 'U';
	tela[y+2][x+3] = 'U';
	tela[y+3][x+2] = 'U';
	tela[y+3][x+3] = 'U';
}

/*
Nome:		testa_cord
Descrição:	Verifica se as coordenadas são válidas dentro do campo de jogo
Argumentos:	'y'(tamanho no eixo y do mapa); 'x'(tamanho no eixo x do mapa)
Retorno:	1(coordenadas validas); 0(coordenadas invalidas)
*/
int testa_cord(int y, int x){
	if(y>10 || y<0 || x>20 || x<0){
		return 0;
	}
	return 1;
}

/*
Nome:		quebra
Descrição:	Define 'blocos quebrados' ao atribuir caractere especifico na matriz guiado por coordenadas digitadas
Argumentos:	'tela'(mapa do jogo)
Retorno:	ponto(pontuacao obtida pela quantidade de blocos quebrados)
*/
int quebra(char tela[10][20]){
	int teste, chance, lado, scolha, y=0, x=0, ponto=0;
	char xr[2], yr[2];
	srand((unsigned)time(NULL));
	chance = rand()%4;
	lado = rand()%4;
	do{
		printf("Quebrar um ou dois blocos?\n1-(1 bloco)\n2-(2 blocos)\n");
		do{
			scanf("%d",&scolha);
			if(scolha != 1 && scolha != 2){printf("Entrada invalida\n"); flush_in();}
		}while(scolha != 1 && scolha != 2);
		printf("Digite a coordenada X:\n");
		do{
			teste = 0;
			x = -1;
			flush_in();
			scanf("%s", xr);
			if (!(isdigit(xr[0]))){teste = 1;}
			if(teste == 0){x = atoi(xr);}
			if(x<0 || x>20){printf("Entrada invalida\n"); teste = 1;}
		}while(teste == 1);
		printf("Digite a coordenada Y:\n");
		do{
			teste = 0;
			y = -1;
			flush_in();
			scanf("%s", yr);
			if (!(isdigit(yr[0]))){teste = 1;}
			if(teste == 0){y = atoi(yr);}
			if(y<0 || y>20){printf("Entrada invalida\n"); teste = 1;}
		}while(teste == 1);
		y--;
		if(!testa_cord(y, x)){
			printf("Entrada de coordenada invalida!!!\n");
		}
	}while(!testa_cord(y, x));
		if(tela[y][x-1] == 'U' || tela[y][x-1] == '_'){
			printf("Impossivel quebrar objeto\n\n");
		}else{
	if(scolha == 1){ /* Define 1/4 de chance de quebrar um bloco adjacente 'aleatorio' e checa se eh valido quebra-lo*/
		chance = rand()%4;
		lado = rand()%4;
		if(chance == 0){
			if(lado == 1){
				if(testa_cord(y+1, x+1)){
					if(!(tela[y+1][x-1] == 'U' || tela[y+1][x-1] == '_')){
						tela[y+1][x-1] = '_';
						ponto += 1;
					}
				}
			}
			else if(lado == 2){
				if(testa_cord(y-1,x)){
					if(!(tela[y-1][x-1] == 'U' || tela[y-1][x-1] == '_')){
						tela[y-1][x-1] = '_';
						ponto += 1;
					}
				}
			}
			else if(lado == 3){
				if(testa_cord(y, x+1)){
					if(!(tela[y][x] == 'U' || tela[y][x] == '_')){
						tela[y][x] = '_';
						ponto += 1;
					}
				}
			}
			else if(lado == 0){
				if(testa_cord(y, x-1)){
					if(!(tela[y][x-2] == 'U' || tela[y][x-2] == '_')){
						tela[y][x-2] = '_';
						ponto += 1;
					}
				}
			}
				tela[y][x] = '_';
				ponto += 1;
			}	
		}else{ /* Define 3/4 de chance de quebrar um bloco adjacente 'aleatorio' e checa se eh valido quebra-lo*/
			chance = rand()%4;
			lado = rand()%4;
			if(chance == 0 || chance == 1 || chance == 2){
				if(lado == 1){
					if(testa_cord(y+1, x)){
						if(!(tela[y+1][x-1] == 'U' || tela[y+1][x-1] == '_')){
							tela[y+1][x-1] = '_';
							ponto += 1;
						}
					}
				}
				if(lado == 2){
					if(testa_cord(y-1, x)){
						if(!(tela[y-1][x-1] == 'U' || tela[y-1][x-1] == '_')){
							tela[y-1][x-1] = '_';
							ponto += 1;
						}
					}
				}
				else if(lado == 3){
					if(testa_cord(y, x+1)){
						if(!(tela[y][x] == 'U' || tela[y][x] == '_')){
							tela[y][x] = '_';
							ponto += 1;
						}
					}
				}
				else if(lado == 0){
					if(testa_cord(y, x-1)){
						if(!(tela[y][x-2] == 'U' || tela[y][x-2] == '_')){
							tela[y][x-2] = '_';
							ponto += 1;
						}
					}
				}	
			}
		}
		tela[y][x-1] = '_';
		ponto += 1;
	}
	espera();
	return ponto;
}

/*
Nome:		limpa_matriz
Descrição:	Reseta efeitos da "checagem por flooding" na matriz
Argumentos:	'tela'(mapa do jogo)
Retorno:	nill
*/
void limpa_matriz(char tela[10][20]){
	int x, y;
	for(x=0; x<20; x++){
		for(y=0; y<10; y++){
			if(tela[y][x]=='X'){tela[y][x]='#';}
		}
	}
}

/* 
Nome:		checar_norte
Descrição:	Checa todos os blocos diretamente conectados à superficie norte e se há algum destes adjacente ao aang ao comparar as redondezas, um por um.
		O mesmo eh feito para a superifice sul, leste e oeste. O algoritmo é o de deteccao por 'flooding'
Argumentos:	'tela'(mapa do jogo)
Retorno:	1(aang conectado pelo norte); 0(aang nao detectado)
*/
int checar_norte(char tela[10][20]){
	int x, y, i=0;
	for(x=0; x<20; x++){
		if(tela[0][x] == '#'){ tela[0][x] = 'X';}
	}
	for(;i<=200;i++){
		for(y=1; y<10; y++){
			for(x=0; x<20; x++){
				if((tela[y-1][x]=='X' || tela[y+1][x]=='X' || tela[y][x+1]=='X' || tela[y][x-1]=='X') && tela[y][x] == '#'){tela[y][x] = 'X';}
				if(tela[y][x]=='X' && (tela[y+1][x]=='U' || tela[y-1][x]=='U' || tela[y][x+1]=='U' || tela[y][x-1]=='U')){
					limpa_matriz(tela);
					return 0;
				}
			}
		}
	}
	limpa_matriz(tela);
	return 1;
}

/* 
Nome:		checar_sul
Descrição:	Checa todos os blocos diretamente conectados à superficie sul e se há algum destes adjacente ao aang ao comparar as redondezas, um por um.
		O mesmo eh feito para a superifice sul, leste e oeste. O algoritmo é o de deteccao por 'flooding'
Argumentos:	'tela'(mapa do jogo)
Retorno:	1(aang conectado pelo norte); 0(aang nao detectado)
*/
int checar_sul(char tela[10][20]){
	int x, y, i=0;
	for(x=0; x<20; x++){
		if(tela[9][x] == '#'){ tela[9][x] = 'X';}
	}
	for(;i<=200; i++){
		for(y=9; y>0; y--){
			for(x=0; x<20; x++){
				if((tela[y-1][x]=='X' || tela[y+1][x]=='X' || tela[y][x+1]=='X' || tela[y][x-1]=='X') && tela[y][x] == '#'){tela[y][x] = 'X';}
				if(tela[y][x]=='X' && (tela[y+1][x]=='U' || tela[y-1][x]=='U' || tela[y][x+1]=='U' || tela[y][x-1]=='U')){
					limpa_matriz(tela);
					return 0;
				}
			}
		}
	}
	limpa_matriz(tela);
	return 1;
}

/* 
Nome:		checar_oeste
Descrição:	Checa todos os blocos diretamente conectados à superficie oeste e se há algum destes adjacente ao aang ao comparar as redondezas, um por um.
		O mesmo eh feito para a superifice sul, leste e oeste. O algoritmo é o de deteccao por 'flooding'
Argumentos:	'tela'(mapa do jogo)
Retorno:	1(aang conectado pelo norte); 0(aang nao detectado)
*/
int checar_oeste(char tela[10][20]){
	int x, y, i=0;
	for(y=0; y<10; y++){
		if(tela[y][0] == '#'){ tela[y][0] = 'X';}
	}
	for(; i<=200; i++){
		for(x=1; x<20; x++){
			for(y=0;y<10;y++){
				if((tela[y-1][x]=='X' || tela[y+1][x]=='X' || tela[y][x+1]=='X' || tela[y][x-1]=='X') && tela[y][x] == '#'){tela[y][x] = 'X';}
				if(tela[y][x]=='X' && (tela[y+1][x]=='U' || tela[y-1][x]=='U' || tela[y][x+1]=='U' || tela[y][x-1]=='U')){
					limpa_matriz(tela);
					return 0;
				}
			}
		}
	}
	limpa_matriz(tela);
	return 1;
}

/* 
Nome:		checar_leste
Descrição:	Checa todos os blocos diretamente conectados à superficie leste e se há algum destes adjacente ao aang ao comparar as redondezas, um por um.
		O mesmo eh feito para a superifice sul, leste e oeste. O algoritmo é o de deteccao por 'flooding'
Argumentos:	'tela'(mapa do jogo)
Retorno:	1(aang conectado pelo norte); 0(aang nao detectado)
*/
int checar_leste(char tela[10][20]){
	int x, y, i=0;
	for(y=0; y<10; y++){
		if(tela[y][19] == '#'){ tela[y][19] = 'X';}
	}
	for(; i<=200; i++){
		for(x=18; x>=0; x--){
			for(y=0; y<10; y++){
				if((tela[y-1][x]=='X' || tela[y+1][x]=='X' || tela[y][x+1]=='X' || tela[y][x-1]=='X') && tela[y][x] == '#'){tela[y][x] = 'X';}
				if(tela[y][x]=='X' && (tela[y+1][x]=='U' || tela[y-1][x]=='U' || tela[y][x+1]=='U' || tela[y][x-1]=='U')){
					limpa_matriz(tela);
					return 0;
				}
			}
		}
	}
	limpa_matriz(tela);
	return 1;
}

/*
Nome:		checa_tudo
Descrição:	Retorna resultado da checagem de multiplos lados ao compara-los com as regras de jogo
Argumentos:	'tela'(mapa do jogo)
Retorno:	1(aang nao conectado); 0(aang conectado)
*/
 int checa_tudo(char tela[10][20]){
/*	Para fins de teste, habilitar isto para checagem.
	if(!checar_norte(tela)){printf("conectado no norte\n");}
	if(!checar_norte(tela)){printf("conectado no sul\n");}
	if(!checar_norte(tela)){printf("conectado no leste\n");}
	if(!checar_norte(tela)){printf("conectado no oeste\n");} */
	printf("\n");
	if((checar_norte(tela) && checar_sul(tela)) || (checar_leste(tela) && checar_oeste(tela))){
		printf("O AANG FOI SOLTO DO CONTINENTE!!!\n");
		return 1;
	}
	return 0;
}

/*
Nome:		evento
Descrição:	Define chance aleatória de uma nevasaca aparecer e congelar/reestituir todos os blocos quebrados novamente
Argumentos:	'tela'(mapa do jogo)
Retorno:	nill
*/
void evento(char tela[10][20]){
	int chance, x, y;
	srand((unsigned)time(NULL));
	chance = rand()%1000;
	if(chance == 0){
		printf("Uma nevasca apareceu, os blocos quebrados voltaram a se congelar!\n");
		for(x=0; x<20; x++){
			for(y=0; y<10; y++){
				if(tela[y][x]!='U'){
					tela[y][x]='#';
				}
			}
		}
	}
}

/*
Nome:		desconta
Descrição:	conta quantos pontos descontar do perdedor ao checar toda a matriz
Argumentos:	'tela'(mapa do jogo)
Retorno:	restam(quantida de pontos a ser descontada)
*/
int desconta(char tela[10][20]){
	int x,y,restam=0;
	for(x=0; x<20; x++){
		for(y=0; y<10; y++){
			if(tela[y][x]=='#'){restam++;}
		}
	}
	return restam;
}

/*
Nome:		limpa_tela
Descrição:	detecta o sistema operacional para limpar a tela do terminal
Argumentos:	nill
Retorno:	0(significa "deu certo")
*/
int limpa_tela(){
	#ifdef _WIN32 
		system("cls");
	#elif __linux__
		system("clear");
	#endif
return 0;
}

/*
Nome:		main
Descrição:	Rotina principal do programa
Argumentos:	nill
Retorno:	0(significa "deu certo")
*/
int main(){ 
	char comeco;
	limpa_tela();
	printf("Bem vindo ao\033[0;36m Don't Break The Ice\033[0;37m\n\n");
	do{
		printf("Digite para selecionar uma das opcoes:\n\nA-Jogar\nB-Instrucoes\nC-Sair\n");
		scanf("%1c",&comeco);
		flush_in();
		if(comeco != 'A' && comeco != 'a' && comeco != 'B' && comeco != 'b' && comeco != 'C' && comeco != 'c'){printf("Entrada invalida\n"); flush_in();}
		if(comeco == 'B' || comeco == 'b'){
			limpa_tela();
			printf("Ha dois jogadores, o objetivo eh acumular pontos ao quebrar mais blocos de gelo sem desprender o bloco de gelo 'U' das bordas.\n");
			printf("O ultimo jogador a jogar antes do bloco de gelo se desprender, faz com que seu\noponente tenha a quantidade de blocos sobrando na arena ser descontada da sua\npontuacao.\n");
			espera();
			limpa_tela();
		}
		if(comeco == 'C' || comeco == 'c'){
			system("exit");
			return 0;
		}
	}while(comeco != 'A' && comeco != 'a');
		limpa_tela();
	int jogador=1, fim=0, pontos1=0, pontos2=0, xu, yu;
	char nome1[25], nome2[25];
	nomeia(nome1, 1);
	flush_in();
	nomeia(nome2, 2);
	espera();
	char tela[10][20];
	cria_matriz(tela);
	gelao(tela, &xu, &yu);
	limpa_tela();
	do{
		mostra(tela);
		printf("%s: %d\n%s: %d\n", nome1, pontos1, nome2, pontos2);
		if(jogador==1){	printf("\nVez de\033[0;36m %s \033[0;37m\n", nome1);}
		else{ printf("\nVez de\033[0;36m %s \033[0;37m \n", nome2);}
		if(jogador==1){pontos1 += quebra(tela);}
		else{pontos2 += quebra(tela);}
		limpa_tela();
		if(jogador == 1){jogador = 2;}
		else{jogador =1;}
		if(checa_tudo(tela)){
			fim = 1;
		}
		if(fim==0){
			evento(tela);	
		}
	}while(fim == 0);
	if(jogador == 1){
		pontos1 = pontos1 - desconta(tela);	
	}else{
		pontos2 = pontos2 - desconta(tela);	
	}
	if(pontos1>pontos2){printf("Parabens\033[0;36m %s\033[0;37m, voce venceu!!!\n", nome1);}
	if(pontos2>pontos1){printf("Parabens\033[0;36m %s\033[0;37m, voce venceu!!!\n", nome2);}
	if(pontos1==pontos2){printf("O jogo\033[0;31m empatou\033[0;37m!!! Ao menos foi bem disputado...\n");}
return 0;
}
