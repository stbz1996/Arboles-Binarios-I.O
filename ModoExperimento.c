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
	float estadisticaCoincidencias     [10];
	float estadisticaPorcCoincidencias [10];
	llenarFlotantes(estadisticaCoincidencias);
	llenarFlotantes(estadisticaPorcCoincidencias);

	float numeroIgualdades = 0;
	float totalIgualdades = 0;

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
		float tablaCoincidencias[ciclos];
		float totalCoincidencias[ciclos];

		// Guarda el inicio del reloj
		clock_t beginExecutiontime;

		for(int j = 1; j <= ciclos; j++){

			// Se genera el problema.
			int objetos = j * 10;
			int largoTabla = objetos + 1;
			float coincidencias, porcCoincidencias, esIgual;

			/* Inicializan las estructuras. */
			struct elemento matriz[objetos];    // Tabla de objetos.
			float  A[largoTabla][largoTabla]; // Tabla A, que posee los porcentajes.
			int    R[largoTabla][largoTabla]; // Tabla R, que posee la ubicación del árbol.

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
			int GreedyR[largoTabla][largoTabla];
			float bonusTable[largoTabla][largoTabla];

			ceroLlenado(largoTabla, bonusTable, GreedyR);
			beginExecutiontime = clock();
			primerLlenado(largoTabla, bonusTable, GreedyR, matriz, objetos);
			//greedy(matriz, largoTabla, GreedyR, 1, objetos);
			llenadoGreedy(largoTabla, GreedyR, matriz);

			tiempoEjecucion = getTime(beginExecutiontime);
			tiempoGreedy[j - 1] = tiempoEjecucion;

			coincidencias = buscarIgualdad(matriz, largoTabla, R, GreedyR, 1, objetos);
			porcCoincidencias = coincidencias / objetos;
			esIgual = (int) porcCoincidencias;

			tablaCoincidencias[j - 1] = esIgual;
			totalCoincidencias[j - 1] = porcCoincidencias;
		}

		if (i <= 1)
		{
			writeExecCase(archivoEjecucion);
		}

		if (i <= 1){
			writeStadCase(archivoEstadistico);
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

		// Saca la suma de las veces que tuvieron la misma estructura.
		for (int k = 0; k < 10; k++)
		{
			estadisticaCoincidencias[k] += tablaCoincidencias[k];
		}

		// Saca la suma de las veces que un nodo encajo en la estructura.
		for (int k = 0; k < 10; k++)
		{
			estadisticaPorcCoincidencias[k] += totalCoincidencias[k];
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

	////////////////////////////////////////////////////////
	// Imprime la tabla de coincidencias de los algoritmos  //
	for (int k = 0; k < 10; k++)
	{
		estadisticaCoincidencias[k] = 100 * (estadisticaCoincidencias[k] / iteraciones);
	}
	generateStadisticTable(archivoEstadistico, estadisticaCoincidencias, "Porcentaje de veces que el algoritmo greedy encuentra la opción óptima");
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	// Imprime la tabla de tiempo promedio final Greedy   //
	for (int k = 0; k < 10; k++)
	{
		estadisticaPorcCoincidencias[k] = 100 * (estadisticaPorcCoincidencias[k] / iteraciones);
	}
	generateStadisticTable(archivoEstadistico, estadisticaPorcCoincidencias, "Porcentaje de coincidencias de estructura de los árboles");
	////////////////////////////////////////////////////////

	// Cerrar los archivos.
	closeFiles(archivoEjecucion, archivoResultados, archivoEstadistico);

	// Genera el latex
	generateExpLatex(salida, archivoEjecucion, archivoResultados, archivoEstadistico, iteraciones);
	deleteFiles();
}