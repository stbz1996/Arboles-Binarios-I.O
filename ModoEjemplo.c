// 0 Spanglish. Todo en español.

void modoEjemplo(FILE *salida){

	// Datos de entrada del problema.
	int objetos = MAX_EJEMPLO_OBJ;
	int largoTabla = objetos + 1;
	double dynamicTime = 0, greedyTime = 0;
	clock_t newBegin;

	/* Abrir los archivos */
	salida = fopen(archivoLatex, "w");

	/* Inicializan las estructuras. */
	struct elemento matriz[objetos]; // Tabla de objetos.
	float A[objetos + 1][objetos + 1]; // Tabla A, que posee los porcentajes.
	int R[objetos + 1][objetos + 1]; // Tabla R, que posee la ubicación del árbol.
	int GreedyR[objetos + 1][objetos + 1];
	int GreedyRDoble[largoTabla][largoTabla];
	float bonusTable[largoTabla][largoTabla];

	// Crea el problema (faltan detalles)
	crearProblema(matriz, objetos);

	// Ejecuta el algoritmo de árbol dinámico.
	ceroLlenado(largoTabla, A, R); // Se llena la tabla de -1. (A y R)
	newBegin = clock();
	primerLlenado(largoTabla, A, R, matriz, objetos); // Se llena la tabla de las diagonales iniciales.
	llenado(largoTabla, A, R, matriz); // Se llena la tabla por medio del Pum Pum Pum.
	dynamicTime = getTime(newBegin);

	// Ejecuto el algoritmo de árbol greedy.
	ceroLlenado(largoTabla, bonusTable, GreedyR);
	ceroLlenado(largoTabla, bonusTable, GreedyRDoble);
	newBegin = clock();
	primerLlenado(largoTabla, bonusTable, GreedyR, matriz, objetos);
	greedy(matriz, largoTabla, GreedyR, 1, 6);
	greedyTime = getTime(newBegin);
	primerLlenado(largoTabla, bonusTable, GreedyRDoble, matriz, objetos);
	llenadoGreedy(largoTabla, GreedyRDoble, matriz);

	/* Genera el latex */
    createLatex(salida);
    cover(salida);
    informationExample(salida);
    createObjectTable(salida, objetos, matriz);

    // Latex del AAB
    introductionDynamicExample(salida, objetos, matriz);
    createExampleTableA(salida, largoTabla, A);
    createExampleTableR(salida, largoTabla, R);
    executionTime(salida, dynamicTime);
    creadorArboles(salida, matriz, largoTabla, R, 1, 6);
    // Latex del greedy.
    introductionGreedyExample(salida, objetos, matriz);
    createExampleTableR(salida, largoTabla, GreedyR);
    ejemploCompleta(salida);
    createExampleTableR(salida, largoTabla, GreedyRDoble);
    executionTime(salida, greedyTime);
    creadorArboles(salida, matriz, largoTabla, GreedyR, 1, 6);
    closeLatex(salida);

	fclose(salida);
}