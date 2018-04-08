void modoExperimento(FILE *salida, int iteraciones){

	// Datos de entrada del problema
	FILE *archivoEjecucion;
	FILE *archivoResultados;
	FILE *archivoEstadistico;

	// Guarda el tiempo de ejecución de los algoritmos y el total de ejecución
	double tiempoGreedy[10];
	double tiempoDinamico[10];
	float estadisticaTotalGreedy[10];
	float estadisticaTotalDinamica[10];

	double tiempoEjecucion = 0;
	double tiempoTotalEjecucion = 0;

	llenarDobles(tiempoGreedy);
	llenarDobles(tiempoDinamico);
	llenarFlotantes(estadisticaTotalGreedy);
	llenarFlotantes(estadisticaTotalDinamica);

	// Abren los archivos.
	archivoEjecucion = fopen(execFileName, "w");
	archivoResultados = fopen(respFileName, "w");
	archivoEstadistico = fopen(stadFileName, "w");
	salida = fopen(archivoLatex, "w");

	for(int i = 1; i <= iteraciones; i++){

		// Variables de configuración...
		int ciclos = 10;
		float totalGreedy, totalDinamico = 0;

		// Guardan los resultados de los algoritmos.
		float resultadosGreedy[ciclos];
		float resultadosDinamico[ciclos];
		int estadisticaGreedy[ciclos];
		int estadisticaDinamica[ciclos];

		llenarEnteros(estadisticaGreedy);
		llenarEnteros(estadisticaDinamica);

		// Guarda el inicio del reloj
		clock_t beginExecutiontime;

		for(int j = 1; j <= ciclos; j++){

			// Se genera el problema.
			int objetos = j * 10;
			int largoTabla = objetos + 1;

			/* Inicializan las estructuras. */
			struct elemento matriz[objetos]; // Tabla de objetos.
			float A[objetos + 1][objetos + 1]; // Tabla A, que posee los porcentajes.
			int R[objetos + 1][objetos + 1]; // Tabla R, que posee la ubicación del árbol.

			// Crea el problema (faltan detalles)
			crearProblema(matriz, objetos);

			// Ejecuta el algoritmo de árbol dinámico.
			ceroLlenado(largoTabla, A, R); // Se llena la tabla de -1. (A y R)
			beginExecutiontime = clock();
			primerLlenado(largoTabla, A, R, matriz, objetos); // Se llena la tabla de las diagonales iniciales.
			totalDinamico = llenado(largoTabla, A, R, matriz); // Se llena la tabla por medio del Pum Pum Pum.
			tiempoEjecucion = getTime(beginExecutiontime);

			resultadosDinamico[j - 1] = totalDinamico;
			tiempoDinamico[j - 1] = tiempoEjecucion;

			tiempoTotalEjecucion += tiempoEjecucion;

		}

		/* Escriba en el archivo resultados los datos. */ 
		if (i <= 1){
			writeCase(archivoResultados, i);
		}
		generateResultsTable(archivoResultados, resultadosDinamico, "Resultados Dinámicos");

		if (i <= 1){
			writeExecCase(archivoEjecucion);
		}
		generateExecutionTable(archivoEjecucion, tiempoDinamico, "Tiempo Dinámicos");

		/*
		for (int m = 0; m < 10; m++){
			estadisticaTotalDinamica[m] += (float) estadisticaDinamica[m];
		}
		*/

	}
	

	// Cerrar los archivos.
	closeFiles(archivoEjecucion, archivoResultados, archivoEstadistico);

	generateExpLatex(salida, archivoEjecucion, archivoResultados, archivoEstadistico, iteraciones);
	deleteFiles();
}