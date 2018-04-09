void modoExperimento(FILE *salida, int iteraciones){
	// Datos de entrada del problema
	FILE *archivoEjecucion;
	FILE *archivoResultados;
	FILE *archivoEstadistico;

	// Guarda el tiempo de ejecución de los algoritmos y el total de ejecución
	double tiempoGreedy        [10];
	double tiempoDinamico      [10];
	double tiempoFinalDinamico [10];     
	double tiempoFinalGreedy   [10];       
	llenarDobles(tiempoFinalDinamico);  
	llenarDobles(tiempoFinalGreedy);    
	llenarDobles(tiempoGreedy);
	llenarDobles(tiempoDinamico);

	// Guarda las estadisticas de los algoritmos
	float estadisticaTotalGreedy   [10];
	float estadisticaTotalDinamica [10];
	llenarFlotantes(estadisticaTotalGreedy);
	llenarFlotantes(estadisticaTotalDinamica);

	double tiempoEjecucion = 0;
	double tiempoTotalEjecucion = 0;

	// Abren los archivos.
	archivoEjecucion   = fopen(execFileName, "w");
	archivoResultados  = fopen(respFileName, "w");
	archivoEstadistico = fopen(stadFileName, "w");
	salida = fopen(archivoLatex, "w");

	for(int i = 1; i <= iteraciones; i++)
	{
		// Variables de configuración...
		int ciclos = 10;
		float totalGreedy, totalDinamico = 0;

		// Guardan los resultados de los algoritmos.
		float resultadosGreedy[ciclos];
		float resultadosDinamico[ciclos];
		int   estadisticaGreedy[ciclos];
		int   estadisticaDinamica[ciclos];

		llenarEnteros(estadisticaGreedy);
		llenarEnteros(estadisticaDinamica);

		// Guarda el inicio del reloj
		clock_t beginExecutiontime;

		for(int j = 1; j <= ciclos; j++){

			// Se genera el problema.
			int objetos = j * 10;
			int largoTabla = objetos + 1;

			/* Inicializan las estructuras. */
			struct elemento matriz[objetos];    // Tabla de objetos.
			float  A[objetos + 1][objetos + 1]; // Tabla A, que posee los porcentajes.
			int    R[objetos + 1][objetos + 1]; // Tabla R, que posee la ubicación del árbol.

			// Crea el problema (faltan detalles)
			crearProblema(matriz, objetos);

			// ######################################################
			// Ejecuta el algoritmo de árbol dinámico.
			// ######################################################
			ceroLlenado(largoTabla, A, R); 
			beginExecutiontime = clock();
			primerLlenado(largoTabla, A, R, matriz, objetos); 
			totalDinamico = llenado(largoTabla, A, R, matriz); 
			tiempoEjecucion = getTime(beginExecutiontime);
			resultadosDinamico[j - 1] = totalDinamico;
			tiempoDinamico[j - 1] = tiempoEjecucion;
			tiempoTotalEjecucion += tiempoEjecucion;
			// ######################################################


			// ######################################################
			// Ejecuta el algoritmo de árbol Greedy.
			// ######################################################
			int GreedyR[objetos + 1][objetos + 1];
			float bonusTable[largoTabla][largoTabla];

			ceroLlenado(largoTabla, bonusTable, GreedyR);
			beginExecutiontime = clock();
			primerLlenado(largoTabla, bonusTable, GreedyR, matriz, objetos);
			greedy(matriz, largoTabla, GreedyR, 1, 6);
			printR(largoTabla, GreedyR);
			tiempoEjecucion = getTime(beginExecutiontime);
			tiempoGreedy[j - 1] = tiempoEjecucion;
			// ######################################################
		}

		/* Escriba en el archivo resultado los datos. */ 
		if (i <= 1)
		{
			writeCase(archivoResultados, i);
		}
		generateResultsTable(archivoResultados, resultadosDinamico, "Resultados Dinámicos");


		if (i <= 1)
		{
			writeExecCase(archivoEjecucion);
		}
		
		// Saca la suma del tiempo de las n ejecuciones dinamico
		for (int k = 0; k < 10; k++)
		{
			tiempoFinalDinamico[k] += tiempoDinamico[k];
		}

		// Saca la suma de el tiempo de las n ejecuciones greddy
		for (int k = 0; k < 10; k++)
		{
			tiempoFinalGreedy[k] += tiempoGreedy[k];
		}
	}

	////////////////////////////////////////////////////////
	// Imprime la tabla de tiempo promedio final dinamico //
	for (int k = 0; k < 10; k++)
	{
		tiempoFinalDinamico[k] = tiempoFinalDinamico[k] / iteraciones;
	}
	generateExecutionTable(archivoEjecucion, tiempoFinalDinamico, "Tiempos Promedio A.B.B Dinámicos");
	////////////////////////////////////////////////////////
	

	////////////////////////////////////////////////////////
	// Imprime la tabla de tiempo promedio final Greedy   //
	for (int k = 0; k < 10; k++)
	{
		tiempoFinalGreedy[k] = tiempoFinalGreedy[k] / iteraciones;
	}
	generateExecutionTable(archivoEjecucion, tiempoFinalGreedy, "Tiempos Promedio A.B.B Greedy");
	////////////////////////////////////////////////////////

	// Cerrar los archivos.
	closeFiles(archivoEjecucion, archivoResultados, archivoEstadistico);

	// Genera el latex
	generateExpLatex(salida, archivoEjecucion, archivoResultados, archivoEstadistico, iteraciones);
	deleteFiles();
}