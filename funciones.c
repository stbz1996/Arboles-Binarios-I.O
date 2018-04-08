//#############################################################
//  Se encarga de concatenar un caracter a un string
//#############################################################
char *concatenar(char *destino, char caracter){
    char *cad;
	int i;
	cad = realloc(destino, strlen(destino) + 2);
	for (i = 0; cad[i] != '\0'; i++);           /* Encontrar el fin de destino */
		cad[i++] = caracter;                        /* Añadimos el caracter */
	cad[i] = '\0';                              /* Añadimos el caracter de fin de destino */
    return destino;
}


//#############################################################
//  Recibe el tiempo y retorna cuando ha pasado desde ese 
//  instante en segundos
//#############################################################
double getTime(double begin){
	return ((double)(clock()-begin)/CLOCKS_PER_SEC)*1000;
}


///#############################################################
//  Nos permite obtener un número totalmente random.
//#############################################################
int getRandom(int limit){
	return rand() % limit + 1;
}

void printTable(struct elemento matriz[], int numPos){
	printf("\n Imprimir tabla: \n");
	for(int i=0; i < numPos; i++){
		printf("%c | %d | %f \n", matriz[i].letra, matriz[i].peso, matriz[i].prob);
	}
}


//#############################################################
//  Se encarga de generar la tabla, e inicializarla con pesos y probabilidades.
//#############################################################
void crearProblema(struct elemento matriz[], int numPos){
	int total = 0;
	int caracter, randNum;
	for(int i=0; i < numPos; i++){
		caracter = 65 +  i;
		randNum = getRandom(1000);
		matriz[i].letra = caracter;
		matriz[i].peso = randNum;
		total += randNum;
	}

	for(int i=0; i < numPos; i++){
		matriz[i].prob = (float) matriz[i].peso / total;
	}
	//SelectionSort(matriz, numPos);
}

//#############################################################
//  Llena una matriz de doubles de 0's
//#############################################################
void llenarFlotantes(float mat[10]){
	for (int i = 0; i < 10; i++){
		mat[i] = 0.0;
	}
}


//#############################################################
//  Llena una matriz de doubles de 0's
//#############################################################
void llenarDobles(double mat[10]){
	for (int i = 0; i < 10; i++){
		mat[i] = 0;
	}
}

//#############################################################
//  Llena una matriz de enteros de 0's
//#############################################################
void llenarEnteros(int mat[10]){
	for (int i = 0; i < 10; i++){
		mat[i] = 0;
	}
}

//#############################################################
//  Retorna la posicion del número con mayor probabilidad.
//#############################################################
int buscaMaxProb(struct elemento matriz[], int min, int max){
	float num = matriz[min].prob;
	int pos = min + 1;
	for(int i=min; i < max; i++){
		if (num < matriz[i].prob){
			num = matriz[i].prob;
			pos = i + 1;
		}
	}
	return pos;
}

//#############################################################
//  FUn
//#############################################################
void greedy(struct elemento matriz[], int largo, int R[][largo], int min, int max){
	int num = buscaMaxProb(matriz, min-1, max);
	R[min-1][max] = num;
	printf("Num %d - Min %d - Max %d \n", num, min, max);

	if (num > min){
		greedy(matriz, largo, R, min, num-1);
	}

	if (num < max){
		greedy(matriz, largo, R, num+1, max);
	}
}

//#############################################################
// Cierra los archivos
//#############################################################
void closeFiles(FILE *file1, FILE *file2, FILE *file3){
	fclose(file1);
	fclose(file2);
	fclose(file3);
}

void deleteFiles(){
	remove(execFileName);
	remove(stadFileName);
	remove(respFileName);
}
