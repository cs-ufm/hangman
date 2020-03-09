#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
 
#define TRUE 1
#define FALSE 0

void mostrar(int cambiar, char *erroneo,char *llamar);
int menu(void);
int encontrarla(char letra);
int esta_la_palabra(char letra);

int menu(void){    
	int opcion;
	
    printf("\n\n\tJuego de Ahorcado\n\n\n\t\\
	\n\t1. Empezar a jugar\n\\
	\n\t2. Salir del juego\n\\
	\n\t Escoja una opcion: ");
    scanf("%d", &opcion);
    return(opcion);
}

char *adivinar(void)
{
	char *diccionario[]={"CASA","CARRO","TELEFONO","CIUDAD","AMIGO",
			     "COMPUTADORA","MESA","PERRO","FUTBOL","PELOTA","GATO",
			     "VASO","TENEDOR","LAPIZ","CUADERNO","ODIO","AMOR",
			     "LAGRIMA","SONRISA","DEDO","CANCION","MUSICA","LETRAS",
			     "MARCOS","MUNDO","PROGRAM","VICTOR","CIEN",
			     "AGUA","HIELO","FRIO","TRAFICO","DANIEL",
			     "ZAPATO","CABELLO","MOCHILA","TALVEZ","SUELO",
			     "LECHE","CEREAL","AZUCAR","ROBO","DEDOS",
			     "INTERNET","ARBOL","FLOR","ARCHIVO","LENTES","COMIDA",
			     "NUMERO","SUETER","PACHON","APRENDER"};
	int numero;
	srand((unsigned)time(NULL));
	numero=rand()%50;
	return(diccionario[numero]);
}

char *secuencia, palabra[10], letras_error[10];

int encontrarla(char letra){
	int correctas = FALSE, i;
	letra = toupper(letra);
	
	for(i=0; i<strlen(secuencia); i++){
		if(letra == secuencia[i]){
			palabra[i] = letra;
			correctas = TRUE;
		}
	}
	return(correctas);
}

main(){
	int i, contar = 0, perder = FALSE, oportunidades, correctas = FALSE, existe;
	int opciones = 0;
	char letra;
	
	system("cls");
	opciones = menu();
	
	do{
		system("cls");
		
		switch(opciones){
			case 1:
				secuencia = adivinar();
				strcpy(palabra, secuencia);
				oportunidades = 6;
				for(i = 0; i<strlen(secuencia); i++) 
				palabra[i]='_';
				for(i = contar; i >= 0; i--) 
				letras_error[i] ='\0';
				contar = 0;
				
				do{
					do{
						fflush(stdin);
						system("cls");
						existe = correctas = FALSE;
						mostrar(oportunidades, letras_error,palabra);
						printf("\n\n\t Letra?: ");
						scanf("%c",&letra);
						existe = esta_la_palabra(letra);	
					}
					
					while(existe);
						correctas = encontrarla(letra);
						
						if(correctas){
							if(strcmp(palabra, secuencia) != 0){
								perder = FALSE; 
								continue;
							}
							else perder = TRUE;
						}
						
						else {
							letras_error[contar++] = letra; --oportunidades;
						}		
				}
				
				while(oportunidades > 0&& perder == FALSE);
				system("cls");
				
				if(perder && oportunidades > 4){
					mostrar(oportunidades, letras_error, palabra);
					printf("\n\t ¡NO TE EQUIVOCASTE!");
				}
				
				else if(perder && oportunidades > 2){
					mostrar(oportunidades, letras_error, palabra);
					printf("\n\t¡BUENOS INTENTOS!");
				}
				
				else if(perder){
					mostrar(oportunidades, letras_error, palabra);
					printf("\n\t¡GANASTE!!");
				}
				
				else {  
					printf("\n\tPERDISTE :(\n\n\t");
					printf("\La palabra correcta era...\n\n\t");
					for(i = 0; i < strlen(secuencia); i++) 
					printf(" %c", secuencia[i]);
				}
				
				perder = FALSE;
				break;
				
			case 2: 
				exit(0);
				break;
		}
		
		fflush(stdin);
		opciones = menu();
	}
	
	while(opciones == 1);
}

int esta_la_palabra(char letra){
	int existe = FALSE, i;
	
	for(i=0; i<strlen(letras_error) ;i++){
		if(letra == letras_error[i]){
			printf("\nEsa palabra ya la habias escrito\n");
			existe = TRUE;
			system("pause");
		}
	}
	return(existe);
}

void mostrar(int cambiar, char *erroneo, char *llamar){
	int i;
	printf("\n\n\tJuego de Ahorcado\n\n\n\t");
	
	if(cambiar<6){
		printf("\n\n\tLetras incorrectas: ");
	
		for(i=0; i<strlen(erroneo); i++) 
		printf(" %c", erroneo[i]);
	}
	
	printf("\n\n\t");
	for(i=0; i<strlen(secuencia); i++) 
	printf(" %c",llamar[i]);
	printf("\n\n\tNumero de oportunidades: %d\n",cambiar);
}



