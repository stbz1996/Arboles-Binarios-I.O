

//#############################################################
// Inicializo los datos fijos que \\begin{tikzpicture}va a tener el documento.
//############################################################
void createLatex(FILE *salida){
    fprintf(salida, "%s\n", "\\documentclass[10pt,letterpaper]{article}");
    fprintf(salida, "%s\n", "\\usepackage[utf8]{inputenc}");
    fprintf(salida, "%s\n", "\\usepackage[spanish]{babel}");
    fprintf(salida, "%s\n", "\\usepackage{tikz-qtree}");
    fprintf(salida, "%s\n", "\\usepackage{multicol}");
    fprintf(salida, "%s\n", "\\usepackage{multirow}");
    fprintf(salida, "%s\n", "\\usepackage{xspace}");
    fprintf(salida, "%s\n", "\\usepackage{color, colortbl}");
    fprintf(salida, "%s\n", "\\usepackage{underscore}");
    fprintf(salida, "%s\n", "\\usepackage{tabu}");
    fprintf(salida, "%s\n", "\\usepackage{url}");
    fprintf(salida, "%s\n", "\\usepackage{ragged2e}");
    fprintf(salida, "%s\n", "\\usepackage{verbatim}");
    fprintf(salida, "%s\n", "\\usepackage{mathdots} ");
    fprintf(salida, "%s\n", "\\usepackage{amsmath, amssymb, amsbsy, amsfonts} ");
    fprintf(salida, "%s\n", "\\usepackage[left=3.5cm,right=3.5cm,top=3.5cm,bottom=3.5cm]{geometry}");
    fprintf(salida, "%s\n", "\\setlength{\\parskip}{\\baselineskip}");
}


//#############################################################
// Genero la portada.
//#############################################################
void cover(FILE *salida){
    fprintf(salida, "%s\n", "\\begin{document} \n\
    \\begin{titlepage} \n\
    \\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}} \n\
    \\center   \n\
    \\textsc{\\Huge Instituto Tecnológico de Costa Rica}\\\\[1.5cm] \n\
    \\textsc{\\normalsize PROYECTO DE INVESTIGACIÓN DE OPERACIONES}\\\\[0.5cm] \n\
    \\textsc{\\normalsize PROYECTO 2}\\\\[0.5cm] \n\
    \\HRule\\\\[0.4cm] \n\
    {\\huge\\bfseries \\vspace{1cm} Árboles Binarios}\\\\[0.4cm] \n\
    \\HRule\\\\[2cm] \n\
    \\textbf{\\Large Estudiantes}\\\\[0.5cm] \n\
        \\begin{minipage}{0.4\\textwidth} \n\
        \\begin{flushleft} \n\
            \\large \n\
            Jason Barrantes Arce \n\
            \\textsc{2015048456} \n\
        \\end{flushleft} \n\
    \\end{minipage} \n\
    ~ \n\
    \\begin{minipage}{0.4\\textwidth} \n\
        \\begin{flushright} \n\
           	\\large \n\
            Steven Bonilla Zúñiga \n\
            \\textsc{2015056296} \n\
        \\end{flushright} \n\
    \\end{minipage} \n\
   \\newline \\newline \n\
   \\newline  \n\
   \\textbf{\\Large Profesor}\\\\[0.5cm] \n\
    \\textsc{\\normalsize Francisco Torres Rojas}\\\\[0.5cm] \n\
    \\end{titlepage} \n\
    ");
}

//#############################################################
// Genero la inicialización del árbol.
//#############################################################
void startTree(FILE *salida){
    fprintf(salida, "%s\n", "El árbol de búsqueda binario queda representado de la siguiente forma: ");
    fprintf(salida, "%s\n", "\\newline \\newline ");
    fprintf(salida, "%s\n", "\\tikzset{every tree node/.style={minimum width=5em,draw,circle},");
    fprintf(salida, "%s\n", "     blank/.style={draw=none},");
    fprintf(salida, "%s\n", "     edge from parent/.style=");
    fprintf(salida, "%s\n", "     {draw,edge from parent path={(\\tikzparentnode) -- (\\tikzchildnode)}},");
    fprintf(salida, "%s\n", "     level distance=3cm}");
    fprintf(salida, "%s\n", "\\begin{tikzpicture}");
    fprintf(salida, "%s\n", "\\Tree");
}

//#############################################################
// Genero el mensaje final del árbol.
//#############################################################
void finishTree(FILE *salida){
    fprintf(salida, "%s\n", "\\end{tikzpicture}");
    fprintf(salida, "%s\n", "\\newpage");
}


//#############################################################
// Genero la nueva raiz.
//#############################################################
void nuevaRaiz(FILE *salida, struct elemento matriz[], int largo, int R[][largo], int min, int max){
    int num = R[min-1][max];
    char letra = matriz[num-1].letra;
    fprintf(salida, "[.\\node[]{%c}; \n", letra); // Cambiar a char en la matriz.

    // Tomo el lado izquierdo de num y lo convierto en la raíz.
    if (num > min){
        fprintf(salida, "%s\n", "\\edge[]; ");
        nuevaRaiz(salida, matriz, largo, R, min, num-1);
    }else{
        fprintf(salida, "%s\n", "\\edge[blank]; \\node[blank]{};");
    }

    // Tomo el lado derecho de num y lo convierto en la raíz.
    if (num < max){
        fprintf(salida, "%s\n", "\\edge[]; ");
        nuevaRaiz(salida, matriz, largo, R, num+1, max);
    }else{
        fprintf(salida, "%s\n", "\\edge[blank]; \\node[blank]{};");
    }

    fprintf(salida, "%s\n", "]");
}

//#############################################################
// Función que invoca la creación de árboles.
//#############################################################
void creadorArboles(FILE *salida, struct elemento matriz[], int largo, int R[][largo], int min, int max){
    startTree(salida);
    nuevaRaiz(salida, matriz, largo, R, min, max);
    finishTree(salida);
}

//#############################################################
// Creo la tabla de objetos. Se usa solamente en el modo Ejemplo.
//#######################################################
void createObjectTable(FILE *salida, int numObjects, struct elemento matriz[]){
    char *line = malloc(100);
    char *temp = malloc(100);
    fprintf(salida, "%s\n", "Se muestra a continuación la tabla de objetos con su respectivo costo (peso) y probabilidad \n\
        que fueron asignados aleatoriamente cumpliendo con las restricciones: ");
    fprintf(salida, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(salida, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s\n", "\\begin{tabu} to 0.6\\textwidth { | X[l] | X[l] | X[l] | } ");
    fprintf(salida, "%s\n", "\\hline");
    fprintf(salida, "%s\n", "\\rowcolor{Gray}");
    fprintf(salida, "%s\n", "\\textbf{Letra} & \\textbf{Peso} & \\textbf{Probabilidad}\\\\");
    fprintf(salida, "%s\n", "\\hline");

    for(int i=0; i < numObjects; i++){
        char c = matriz[i].letra;
        sprintf(line, "Object %c & %d & %.2f \\\\", c, matriz[i].peso, matriz[i].prob);
        fprintf(salida, "%s\n", line);
        fprintf(salida, "%s\n", "\\hline");
    }
    fprintf(salida, "%s\n", "\\end{tabu} \\\\");
    fprintf(salida, "%s\n", "\\end{center}");
    free(line);
    free(temp);
}


//#############################################################
// Imprimo la información que aparece por defecto en el modo Ejemplo.
//#############################################################
void informationExample(FILE *salida){
    fprintf(salida, "%s\n", "\\titlepage{\\textbf{Modo Ejemplo:}} \\newline \\newline \n\
        Se resolverá un problema general por medio de diversos algoritmos que nos \n\
        permitan encontrarle una solución. \n\
        El problema es sobre árboles de búsqueda binaria. \\\\ \n\
        Hay que ordenar una serie de valores o llaves en forma de árbol binario, de manera que \n\
        el nivel de búsqueda promedio sea el óptimo. \n\
        Tenemos una serie de llaves que quieren acomodarse en una estructura de árbol, \n\
        pero esas llaves deben tener un respectivo peso, que determinará su probabilidad \n\
        y un cáracter único que será asignado de manera ascendente. \\ \\ \\newline \\newline \n\
        Restricciones: \n\
        \\begin{itemize} \n\
        \\item \\textbf{Estructura:} Se formará un árbol binario óptimo. \n\
        \\item \\textbf{Llaves:} Se generarán 6 llaves de forma ascendente. \n\
        \\item \\textbf{Peso:} Varía entre $1 \\leq C{i} \\leq 1000$. \n\
        \\item Los caracteres ASCII varían. \n\
        \\end{itemize} \n\
        Los dos algoritmos que vamos a implementar son: \n\
        \\begin{itemize} \n\
        \\item \\textbf{Algoritmo de Búsqueda Dinámica:} Algoritmo para el ABB óptimo. \n\
        \\item \\textbf{Algoritmo Greedy Básico:} Cada vez se escoge la llave de máxima probabilidad \n\
         para que sea la raíz del árbol. \n\
        \\end{itemize} \n\
        \\ En el caso de programación dinámica ya que nuestro objetivo es minimizar el costo promedio de la búsqueda, usamos la fórmula: \n\
        \\[ \\textsc{\\normalsize MIN(Z)}\\\\[0.5cm] = \\sum_{i=1}^{n}c_{i}p_{i} \\] \n\
        \\ Que está sujeto a:  \n\
        \\[ \\sum p_{i} \\equiv 1 \\] \n\
        \\ Con cada $c_{i}$ = 1, 2, ... n  \n\
        \\ \\ \\newline \\newline \n\
        ");
}


//#############################################################
// Imprimo la explicación del algoritmo dinámico, con los objetos, los respectivos Z y X.
//#######################################################
void introductionDynamicExample(FILE *salida, int numObjects, struct elemento matriz[]){
    char *line = malloc(100);
    fprintf(salida, "%s\n", "\\section{Algoritmo AAB Óptimo} \n\
        Es un problema de solución de búsqueda óptima:  \n\
        En nuestro caso, queremos minimizar el costo de la búsqueda promedio. \n\
        Para solucionar el problema vamos a hacer uso de una tabla (n+1) x (n+1), donde n es la cantidad \n\
        de objetos o llaves disponibles. \n\
        Como se menciona en las restricciones del problema $n = 6$ por lo que tendremos \n\
        dos tablas (7x7). La tabla A donde estará el costo promedio y la tabla R donde estará \n\
        los índices de búsqueda más rápidos. \\newline \\newline \\newline \n\
        \\textbf{\\Large Fórmula Matemática} \n\
        \\[ \\textsc{\\normalsize MIN(Z)}\\\\[0.5cm] = \\sum_{i=1}^{6}c_{i}p_{i} \\] \n\
        \\ Sujeto a:  \n\
        \\[ \\sum p_{i} \\leq 1 \\] \n\
        \\ En otras palabras tendremos ");
    fprintf(salida, "%s", "\\[ ");
    for (int i = 0; i < numObjects; ++i){
        sprintf(line, "(p_{%d} \\approx %.4f)", i+1, matriz[i].prob);
        fprintf(salida, "%s", line);
        if (i < (numObjects - 1)){
            fprintf(salida, "%s", "+");
        }
    }
    fprintf(salida, "%s\n", " = 1 \\]");
    fprintf(salida, "%s\n", "\\newline Ahora proseguimos realizando la tabla dinámica.");
}

//#############################################################
// Imprimo la explicación del algoritmo greedy básico. La información básica.
//#######################################################
void introductionGreedyExample(FILE *output, int numObjects, struct elemento matriz[]){
    char *line = malloc(100);
    int count = 0;
    fprintf(output, "%s\n", "\\section{Algoritmo Greedy Básico} \n\
        Es un algoritmo que soluciona problemas que a primera vista parece ser \n\
        óptimo. Es característico porque es muy sencillo de entender y explicar. \n\
        Se escoge la llave de máxima probabilidad para que sea la raíz del árbol, las \n\
        demas se separan en dos grupos: las menores que la raíz y las mayores. Este \n\
        procedimiento se repite recursivamente en cada grupo. \n\
        \\[ Llave_{i} = (Peso, Probabilidad), i = 0...n \\]");
    fprintf(output, "%s", "\\[ ");
    for (int i = 0; i < numObjects; ++i){
        sprintf(line, "K_{%c} = (%d, %.2f)", matriz[i].letra, matriz[i].peso, matriz[i].prob);
        fprintf(output, "%s", line);
        if (i < (numObjects - 1)){
            fprintf(output, "%s", ", ");
        }
    }
    fprintf(output, "%s\n", " \\]");
    fprintf(output, "%s\n", "\\newline Ahora proseguimos realizando la tabla greedy básico.");
}

//#############################################################
// Genere la tabla A
//#######################################################
void createExampleTableA(FILE *salida, int largo, float A[][largo]){
    char *line = malloc(100);
    fprintf(salida, "%s\n", "\\newline \\newline \\newline \\textbf{Tabla A: }");
    fprintf(salida, "%s\n", "\\definecolor{Gray}{gray}{0.5}");
    fprintf(salida, "%s\n", "\\definecolor{GreenBlack}{RGB}{2,80,0}");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s", "\\begin{tabu} to 1.0\\textwidth { |");
    for(int i=0; i < (largo + 1); i++){
        fprintf(salida, "%s", " c |");
    }
    fprintf(salida, "%s\n", " }");
    fprintf(salida, "%s\n", "\\hline");
    fprintf(salida, "%s", "\\cellcolor{Gray}\\color{black}\\textbf{X} & ");
    for(int i=0; i < largo; i++){
        sprintf(line, "\\cellcolor{Gray}\\color{black}\\textbf{%d}", i);
        fprintf(salida, "%s", line);
        if (i+1 < largo){
            fprintf(salida, "%s", " & ");
        }else{
            fprintf(salida, "%s\n", " \\\\ ");
        }
    }
    fprintf(salida, "%s\n", "\\hline");
    for(int i=0; i < largo; i++){
        fprintf(salida, "\\cellcolor{Gray}\\color{black}%d & ", i+1);
        for(int j=0; j < largo; j++){
            if(A[i][j] < 0){
                fprintf(salida, "%s", " -- ");
            }else{
                fprintf(salida, "%.2f", A[i][j]);
            }
        
            if (j+1 < largo){
                fprintf(salida, "%s", " & ");
            }else{
                fprintf(salida, "%s\n", " \\\\ ");
            }
        }
        fprintf(salida, "%s\n", "\\hline");
    }
    fprintf(salida, "%s\n", "\\end{tabu} \\\\");
    fprintf(salida, "%s\n", "\\end{center}");
    free(line);
}

//#############################################################
// Genere la tabla R
//#######################################################
void createExampleTableR(FILE *salida, int largo, int R[][largo]){
    char *line = malloc(100);
    fprintf(salida, "%s\n", "\\textbf{Tabla R: }");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s", "\\begin{tabu} to 1.0\\textwidth { |");
    for(int i=0; i < (largo + 1); i++){
        fprintf(salida, "%s", " l |");
    }
    fprintf(salida, "%s\n", " }");
    fprintf(salida, "%s\n", "\\hline");
    fprintf(salida, "%s", "\\cellcolor{Gray}\\color{black}\\textbf{X} & ");
    for(int i=0; i < largo; i++){
        sprintf(line, "\\cellcolor{Gray}\\color{black}\\textbf{%d}", i);
        fprintf(salida, "%s", line);
        if (i+1 < largo){
            fprintf(salida, "%s", " & ");
        }else{
            fprintf(salida, "%s\n", " \\\\ ");
        }
    }
    fprintf(salida, "%s\n", "\\hline");
    for(int i=0; i < largo; i++){
        fprintf(salida, "\\cellcolor{Gray}\\color{black}%d & ", i+1);
        for(int j=0; j < largo; j++){
            if(R[i][j] < 0){
                fprintf(salida, "%s", " - ");
            }else{
                fprintf(salida, " %d ", R[i][j]);
            }
        
            if (j+1 < largo){
                fprintf(salida, "%s", " & ");
            }else{
                fprintf(salida, "%s\n", " \\\\ ");
            }
        }
        fprintf(salida, "%s\n", "\\hline");
    }
    fprintf(salida, "%s\n", "\\end{tabu} \\\\");
    fprintf(salida, "%s\n", "\\end{center}");
    free(line);
}



//#############################################################
// Almaceno en el archivo target lo que tenga escrito el archivo source
//#######################################################
void saveLatex(FILE *target, FILE *source, char *name){
    char c;
    source = fopen(name, "r");
    fseek(source, 0, SEEK_SET);
    while((c=fgetc(source)) != EOF){
        fprintf(target, "%c", c); // Escriba caracter a caracter en el target.
    }
    fclose(source);
}


//#############################################################
// Cambie las coordenadas del documento. (Almacenar las tablas requiere todo el espacio de la pantalla)
//#######################################################
void changeGeometry(FILE *salida, int change){
    if (change){
        fprintf(salida, "%s\n", "\\newgeometry{left=1.5cm,right=1.5cm,top=3.5cm,bottom=3.5cm}");
    }else{
        fprintf(salida, "%s\n", "\\newgeometry{left=3.5cm,right=3.5cm,top=3.5cm,bottom=3.5cm}");
    }
}

//#############################################################
// Imprimo en una página el título de la iteración.
//#######################################################
void writeCase(FILE *output, int iteration){
    fprintf(output, "%s\n", "\\newpage");
    fprintf(output, "%s\n", "\\begin{center}");
    fprintf(output, "%s\n", "\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}");
    fprintf(output, "%s\n", "\\center");
    fprintf(output, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "{\\centering \\Huge\\bfseries Iteración %d}\\\\[0.4cm]\n", iteration);
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(output, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(output, "%s\n", "\\HRule");
    fprintf(output, "%s\n", "\\end{center}");
    fprintf(output, "%s\n", "\\newpage ");
}

//#############################################################
// Genere una tabla de resultados.
//#######################################################
void generateResultsTable(FILE *temp, float mat[10], char* name){

    fprintf(temp, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(temp, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(temp, "%s\n", "\\begin{center}");
    fprintf(temp, "%s\n", "\\begin{table}\\renewcommand{\\arraystretch}{2.5}");
    fprintf(temp, "%s", "\\caption{\\large \\textbf{");
    fprintf(temp, "%s}}\n", name);
    fprintf(temp, "%s\n", "\\centering");
    fprintf(temp, "%s", "\\begin{tabular} { |m{0.5cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|");
    fprintf(temp, "%s\n", "m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|} ");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\rowcolor{Gray}");
    fprintf(temp, "%s", "\\centering \\textbf{X} & ");
    fprintf(temp, "%s", "\\centering \\textbf{10} & \\centering \\textbf{20} & \\centering \\textbf{30}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{40} & \\centering \\textbf{50} & \\centering \\textbf{60}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{70} & \\centering \\textbf{80} & \\centering \\textbf{90}\\ & ");
    fprintf(temp, "%s", "\\textbf{100} \\\\");
    fprintf(temp, "%s\n", "\\hline");


    for(int i=-1; i < 10; i++){

        if (i >= 0){
            fprintf(temp, " & %f", mat[i]);
        }else{
            fprintf(temp, "%s", "Key");
        }
        
    }
    fprintf(temp, "%s\n", " \\\\");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\end{tabular} \\\\");
    fprintf(temp, "%s\n", "\\end{table}");
    fprintf(temp, "%s\n", "\\end{center}");
}


//#############################################################
// Genere una tabla de resultados.
//#######################################################
void generateExecutionTable(FILE *temp, double mat[10], char* name){

    fprintf(temp, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(temp, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(temp, "%s\n", "\\begin{center}");
    fprintf(temp, "%s\n", "\\begin{table}\\renewcommand{\\arraystretch}{2.5}");
    fprintf(temp, "%s", "\\caption{\\large \\textbf{");
    fprintf(temp, "%s}}\n", name);
    fprintf(temp, "%s", "\\begin{tabular} { |m{0.5cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|");
    fprintf(temp, "%s\n", "m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|} ");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\rowcolor{Gray}");
    fprintf(temp, "%s", "\\centering \\textbf{X} & ");
    fprintf(temp, "%s", "\\centering \\textbf{10} & \\centering \\textbf{20} & \\centering \\textbf{30}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{40} & \\centering \\textbf{50} & \\centering \\textbf{60}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{70} & \\centering \\textbf{80} & \\centering \\textbf{90}\\ & ");
    fprintf(temp, "%s", "\\textbf{100} \\\\");
    fprintf(temp, "%s\n", "\\hline");


    for(int i=-1; i < 10; i++){

        if (i >= 0){
            fprintf(temp, " & %.3f$ms$", mat[i]);
        }else{
            fprintf(temp, "%s", "Key");
        }
        
    }
    fprintf(temp, "%s\n", " \\\\");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\end{tabular} \\\\");
    fprintf(temp, "%s\n", "\\end{table}");
    fprintf(temp, "%s\n", "\\end{center}");
}

//#############################################################
// Almacene en latex el tiempo de ejecución.
//#######################################################
void executionTime(FILE *salida, double time){
    fprintf(salida, "%s", "El algoritmo tarda aproximadamente: ");
    fprintf(salida, "%f", time);
    fprintf(salida, "%s\n\n", " segundos en ejecutarse.");
}

//#############################################################
// Cierre el documento de latex y ejecutelo.
//#######################################################
void closeLatex(FILE *salida){
    fprintf(salida, "%s\n", "\\end{document}");
    fclose(salida);
    system("pdflatex arbol.tex && evince -s arbol.pdf &");       
}

//#############################################################
// Imprimo en una página el título Ejecuciones.
//#######################################################
void writeExecCase(FILE *salida){
    fprintf(salida, "%s\n", "\\newpage ");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s\n", "\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}");
    fprintf(salida, "%s\n", "\\center");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "{\\centering \\Huge\\bfseries Tiempo de ejecuciones}\\\\[0.4cm]\n");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule");
    fprintf(salida, "%s\n", "\\end{center}");
    fprintf(salida, "%s\n", "\\newpage ");
}

//#############################################################
// Imprimo la información que aparece por defecto en el modo Experimento con el número de iteraciones.
//#######################################################
void informationExperiment(FILE *salida, int n){

    fprintf(salida, "%s\n", "\\titlepage{\\textbf{Modo Experimento:}} \\newline \\newline ");
    fprintf(salida, "Se resolverán %d ", n);
    fprintf(salida, "%s\n", "problemas de árboles de búsqueda binaria por medio de dos algoritmos que nos \n\
        permitan encontrar soluciones a ese problema. \n\
        \\ \\ \\newline \\newline \n\
        Restricciones: \n\
        \\begin{itemize} \n\
        \\item \\textbf{Llaves:} Se generarán aleatoriamente de 10 a 100 objetos. \n\
        \\item \\textbf{Peso_{i}:} Varía entre $1 < C{i} \\leq 1000 $ de forma aleatoria.\n\
        \\item \\textbf{Prob_{i}:} Valor entre $ 0 < P{i} < 1 $ \n\
        \\end{itemize} \n\
        Los tres algoritmos que vamos a implementar son: \n\
        \\begin{itemize} \n\
        \\item \\textbf{Algoritmo de programación dinámica:} Es el algoritmo A.B.B visto en clase. \n\
        \\item \\textbf{Algoritmo Greedy Básico:} Cada vez se escoge la llave con la máxima \n\
         probabilidad para que sea la raíz del árbol, se repite el proceso con el lado izquierdo y derecho. \n\
        \\end{itemize} \n\
        \\ En el caso de programación dinámica ya que nuestro objetivo es maximizar el valor que obtenemos, usamos la fórmula: \n\
        \\[ \\textsc{\\normalsize MAX(Z)}\\\\[0.5cm] = \\sum_{i=1}^{n}x_{i}v_{i} \\] \n\
        \\ Que está sujeto a:  \n\
        \\[ \\sum x_{i}c_{i} \\leq C \\] \n\
        \\ Con cada $x_{i}$ = 0 o 1.  \n\
        \\ \\ \\newline \\newline \n\
        ");
}

// ############################################################
// Llena el latex knapsack.tex en modo experimento
// ############################################################
void generateExpLatex(FILE *output, FILE *execFile, FILE *respFile, FILE *stadisticFile, int iterations){
    createLatex(output);                       // Inicializo las declaraciones de Latex
    cover(output);                             // Genero la portada
    informationExperiment(output, iterations); // Se declara la información inicial
    changeGeometry(output, 1);                 // Se hace más grande el tamaño (coordenadas)
    saveLatex(output, execFile, execFileName); // Se dibujan las tablas de ejecución
    saveLatex(output, stadisticFile, stadFileName); // Se dibujan las tablas de estadisticas.
    saveLatex(output, respFile, respFileName); // Se dibujan las tablas de resultados
    changeGeometry(output, 0);                 // Se restablecen las coordenadas del tamaño
    closeLatex(output);                        // Se cierra el archivo y se ejecuta.
}



/*


//#############################################################
// Imprimo en una página el título Ejecuciones.
//#######################################################
void writeExecCase(FILE *salida){
    fprintf(salida, "%s\n", "\\newpage ");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s\n", "\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}");
    fprintf(salida, "%s\n", "\\center");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "{\\centering \\Huge\\bfseries Tiempo de ejecuciones}\\\\[0.4cm]\n");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule");
    fprintf(salida, "%s\n", "\\end{center}");
    fprintf(salida, "%s\n", "\\newpage ");
}


//#############################################################
// Imprimo en una página el título Estadísticas.
//#######################################################
void writeStadCase(FILE *salida){
    fprintf(salida, "%s\n", "\\newpage ");
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s\n", "\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}");
    fprintf(salida, "%s\n", "\\center");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "{\\centering \\Huge\\bfseries Estadísticas}\\\\[0.4cm]\n");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule");
    fprintf(salida, "%s\n", "\\end{center}");
    fprintf(salida, "%s\n", "\\newpage ");
}

//#############################################################
// Imprimo en una página el título de la iteración.
//#######################################################
void writeCase(FILE *salida, int iteration){
    fprintf(salida, "%s\n", "\\begin{center}");
    fprintf(salida, "%s\n", "\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}");
    fprintf(salida, "%s\n", "\\center");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "{\\centering \\Huge\\bfseries Iteración %d}\\\\[0.4cm]\n", iteration);
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[0.4cm]");
    fprintf(salida, "%s\n", "\\HRule\\\\[6cm]");
    fprintf(salida, "%s\n", "\\HRule");
    fprintf(salida, "%s\n", "\\end{center}");
    fprintf(salida, "%s\n", "\\newpage ");
}


//#############################################################
// Genere una tabla de ejecución. 
//#######################################################
void generateExecutionTable(FILE *temp, double mat[][10], char* name){

    fprintf(temp, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(temp, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(temp, "%s\n", "\\begin{center}");
    fprintf(temp, "%s\n", "\\begin{table}\\renewcommand{\\arraystretch}{2.5}");
    fprintf(temp, "%s", "\\caption{\\large \\textbf{");
    fprintf(temp, "%s}}\n", name);
    fprintf(temp, "%s\n", "\\centering");
    fprintf(temp, "%s", "\\begin{tabular} { |m{0.5cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|");
    fprintf(temp, "%s\n", "m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|} ");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\rowcolor{Gray}");
    fprintf(temp, "%s", "\\centering \\textbf{X} & ");
    fprintf(temp, "%s", "\\centering \\textbf{10} & \\centering \\textbf{20} & \\centering \\textbf{30}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{40} & \\centering \\textbf{50} & \\centering \\textbf{60}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{70} & \\centering \\textbf{80} & \\centering \\textbf{90}\\ & ");
    fprintf(temp, "%s", "\\textbf{100} \\\\");
    fprintf(temp, "%s\n", "\\hline");


    for(int i=0; i < 10; i++){

        int pos = (i + 1) * 100;
        fprintf(temp, "\\cellcolor{Gray}%d", pos);
        for(int j=0; j < 10; j++){
            fprintf(temp, " & %.3f", mat[i][j]);
            fprintf(temp, "%s", "$ms$");
        }
        fprintf(temp, "%s\n", " \\\\");
        fprintf(temp, "%s\n", "\\hline");
    }
    fprintf(temp, "%s\n", "\\end{tabular} \\\\");
    fprintf(temp, "%s\n", "\\end{table}");
    fprintf(temp, "%s\n", "\\end{center}");
    fprintf(temp, "%s\n", "\\newpage ");
}


//#############################################################
// Genere una tabla de estadísticas. 
//#######################################################
void generateStadisticTable(FILE *temp, float mat[][10], char* name){

    fprintf(temp, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(temp, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(temp, "%s\n", "\\begin{center}");
    fprintf(temp, "%s\n", "\\begin{table}\\renewcommand{\\arraystretch}{2.5}");
    fprintf(temp, "%s", "\\caption{\\large \\textbf{");
    fprintf(temp, "%s}}\n", name);
    fprintf(temp, "%s\n", "\\centering");
    fprintf(temp, "%s", "\\begin{tabular} { |m{0.5cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|");
    fprintf(temp, "%s\n", "m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|} ");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\rowcolor{Gray}");
    fprintf(temp, "%s", "\\centering \\textbf{X} & ");
    fprintf(temp, "%s", "\\centering \\textbf{10} & \\centering \\textbf{20} & \\centering \\textbf{30}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{40} & \\centering \\textbf{50} & \\centering \\textbf{60}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{70} & \\centering \\textbf{80} & \\centering \\textbf{90}\\ & ");
    fprintf(temp, "%s", "\\textbf{100} \\\\");
    fprintf(temp, "%s\n", "\\hline");


    for(int i=0; i < 10; i++){

        int pos = (i + 1) * 100;
        fprintf(temp, "\\cellcolor{Gray}%d", pos);
        for(int j=0; j < 10; j++){
            fprintf(temp, " & %.2f", mat[i][j]);
            fprintf(temp, "%s", "\\%");
        }
        fprintf(temp, "%s\n", " \\\\");
        fprintf(temp, "%s\n", "\\hline");
    }
    fprintf(temp, "%s\n", "\\end{tabular} \\\\");
    fprintf(temp, "%s\n", "\\end{table}");
    fprintf(temp, "%s\n", "\\end{center}");
    fprintf(temp, "%s\n", "\\newpage ");
}

//#############################################################
// Genere una tabla de resultados.
//#######################################################
void generateResultsTable(FILE *temp, int mat[][10], char* name){

    fprintf(temp, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(temp, "%s\n", "\\definecolor{LightCyan}{rgb}{0.88,1,1}");
    fprintf(temp, "%s\n", "\\begin{center}");
    fprintf(temp, "%s\n", "\\begin{table}\\renewcommand{\\arraystretch}{2.5}");
    fprintf(temp, "%s", "\\caption{\\large \\textbf{");
    fprintf(temp, "%s}}\n", name);
    fprintf(temp, "%s\n", "\\centering");
    fprintf(temp, "%s", "\\begin{tabular} { |m{0.5cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|");
    fprintf(temp, "%s\n", "m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|m{1.3cm}|} ");
    fprintf(temp, "%s\n", "\\hline");
    fprintf(temp, "%s\n", "\\rowcolor{Gray}");
    fprintf(temp, "%s", "\\centering \\textbf{X} & ");
    fprintf(temp, "%s", "\\centering \\textbf{10} & \\centering \\textbf{20} & \\centering \\textbf{30}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{40} & \\centering \\textbf{50} & \\centering \\textbf{60}\\ & ");
    fprintf(temp, "%s", "\\centering \\textbf{70} & \\centering \\textbf{80} & \\centering \\textbf{90}\\ & ");
    fprintf(temp, "%s", "\\textbf{100} \\\\");
    fprintf(temp, "%s\n", "\\hline");


    for(int i=0; i < 10; i++){

        int pos = (i + 1) * 100;
        fprintf(temp, "\\cellcolor{Gray}%d", pos);
        for(int j=0; j < 10; j++){
            fprintf(temp, " & \\Large %d", mat[i][j]);
        }
        fprintf(temp, "%s\n", " \\\\");
        fprintf(temp, "%s\n", "\\hline");
    }
    fprintf(temp, "%s\n", "\\end{tabular} \\\\");
    fprintf(temp, "%s\n", "\\end{table}");
    fprintf(temp, "%s\n", "\\end{center}");
    fprintf(temp, "%s\n", "\\newpage ");
}


//#############################################################
// Almacene en latex el tiempo de ejecución.
//#######################################################
void executionTime(FILE *salida, double time){
    fprintf(salida, "%s", "\\newline El algoritmo tarda aproximadamente: ");
    fprintf(salida, "%f", time);
    fprintf(salida, "%s\n", " segundos en ejecutarse");
}

*/