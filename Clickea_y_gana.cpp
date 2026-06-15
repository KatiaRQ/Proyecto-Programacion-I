#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

/* PROTOTIPOS DE FUNCIONES */
int validar_letras(const char *array);
int validar_numeros(const char *array, int n);
void generacion_codigo_aleatorio(char array[6]);
void llenar_tablero(int array[5][5], int array2[5][5]);
void destape_tablero(int a_original[5][5], int a_final[5][5], int &intentos, int *premio);
void guardar_boletos(const struct datos *dts, int contador);
void guardar_premios(const struct datos *dts, int contador);
void guardar_fondos(int total_boletos, int total_premios, int ganancias);
void mostrar_contenido_archivo(const char *nombre_archivo);
void mostrar_fondos();
void limpiar_buffer();
void imprimir_linea(int longitud, char caracter);
void imprimir_encabezado(const char *titulo);
void mostrar_tabla_boletos();
void mostrar_tabla_premios();
void mostrar_tabla_fondos();

/* ESTRUCTURA PRINCIPAL */
struct datos {
    char nombre[100][40];
    char calle[100][15];
    char numero_dom[100][5];
    char cuenta_bancaria[100][18];
    char banco[100][20];
    char codigo[100][6];
    char tipo_boleto[100][7];
    int costo_boleto[100][1];
    int premio[100][1];
};

/* FUNCIÓN PRINCIPAL */
int main() {
    struct datos dts;
    memset(&dts, 0, sizeof(dts));
    
    int opcion, categoria, configuracion, intentos_totales, intentos = 0, tablero_final[5][5];
    int contador = 0;
    char continuar = 's';
    char input[10];
    int total_boletos = 0, total_premios = 0, ganancias = 0;
    
    // Configuración inicial
    setlocale(LC_CTYPE, "Spanish");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 271);
    srand(time(NULL));

    // Mostrar créditos con color
    SetConsoleTextAttribute(hConsole, 14);
    printf("Programa creado por:\n");
    SetConsoleTextAttribute(hConsole, 11);
    printf("\t187013 Enrique Matancillas Vazquez\n\t187012 Katia Ramos Quezada\n\n");
    SetConsoleTextAttribute(hConsole, 7);
    system("pause");

    while(continuar == 's' || continuar == 'S') {
        system("cls");
        int tablero_num[5][5] = {0};
        intentos = 0;
        
        // Menú principal
        SetConsoleTextAttribute(hConsole, 10);
        printf(" C L I C K E A   Y   G A N A \n\n");
        SetConsoleTextAttribute(hConsole, 14);
        printf("1. Venta de boletos\n");
        printf("2. Consulta de boletos vendidos\n");
        printf("3. Consulta de premios ganados\n");
        printf("4. Fondos recaudados\n");
        printf("5. Configuración\n");
        printf("6. Salir\n\n");
        SetConsoleTextAttribute(hConsole, 7);
        
        // Validación de entrada para el menú
        do {
            printf("Ingresa tu opción (1-6): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            
            int es_numero = 1;
            for(int i = 0; input[i] != '\0'; i++) {
                if(input[i] < '0' || input[i] > '9') {
                    es_numero = 0;
                    break;
                }
            }
            
            if(es_numero) {
                opcion = atoi(input);
                if(opcion < 1 || opcion > 6) {
                    printf("Opción fuera de rango. Intenta de nuevo.\n");
                }
            } else {
                printf("Entrada inválida. Solo se permiten números.\n");
                opcion = 0;
            }
        } while(opcion < 1 || opcion > 6);

        system("cls");
        
        switch(opcion) {
            case 1: {
                imprimir_encabezado("----- V E N T A   D E   B O L E T O S -----");
                
                // Validación de nombre
                do {
                    printf("Nombre completo: ");
                    fgets(dts.nombre[contador], sizeof(dts.nombre[contador]), stdin);
                    dts.nombre[contador][strcspn(dts.nombre[contador], "\n")] = '\0';
                    
                    if(!validar_letras(dts.nombre[contador])) {
                        printf("Error: Solo letras y espacios permitidos\n");
                    }
                } while(!validar_letras(dts.nombre[contador]));
                
                printf("\nDatos domiciliares\n");
                
                // Validación de calle
                do {
                    printf("Calle: ");
                    fgets(dts.calle[contador], sizeof(dts.calle[contador]), stdin);
                    dts.calle[contador][strcspn(dts.calle[contador], "\n")] = '\0';
                    
                    if(!validar_letras(dts.calle[contador])) {
                        printf("Error: Solo letras y espacios permitidos\n");
                    }
                } while(!validar_letras(dts.calle[contador]));
                fflush(stdin);
                
                // Validación de número
                do {
                    printf("Número: ");
                    fgets(dts.numero_dom[contador], sizeof(dts.numero_dom[contador]), stdin);
                    dts.numero_dom[contador][strcspn(dts.numero_dom[contador], "\n")] = '\0';
                    
                    if(!validar_numeros(dts.numero_dom[contador], 0)) {
                        printf("Error: Solo números permitidos\n");
                    }
                } while(!validar_numeros(dts.numero_dom[contador], 0));
                
                printf("\nDatos bancarios\n");
                
                // Validación de CLABE
                do {
                    printf("CLABE interbancaria: ");
                    fflush(stdin);
                    gets(dts.cuenta_bancaria[contador]);
                    if (validar_numeros(dts.cuenta_bancaria[contador], 1) == 0) {
                        printf("Error, toma en cuenta que solo se permiten 18 NÚMEROS \n");
                    }
                } while (validar_numeros(dts.cuenta_bancaria[contador], 1) == 0);
                
                // Validación de banco
                do {
                    printf("Banco: ");
                    fgets(dts.banco[contador], sizeof(dts.banco[contador]), stdin);
                    dts.banco[contador][strcspn(dts.banco[contador], "\n")] = '\0';
                    
                    if(!validar_letras(dts.banco[contador])) {
                        printf("Error: Solo letras y espacios permitidos\n");
                    }
                } while(!validar_letras(dts.banco[contador]));
                
                // Generar código aleatorio
                printf("\nCódigo aleatorio: ");
                generacion_codigo_aleatorio(dts.codigo[contador]);
                
                // Selección de categoría
                printf("\nCategoría de boleto:\n");
                SetConsoleTextAttribute(hConsole, 14);
                printf("1. Básica ($100)\n2. Premium ($250)\n3. Oro ($400)\n");
                SetConsoleTextAttribute(hConsole, 7);
                do {
                    printf("Seleccione (1-3): ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0';
                    
                    int es_numero = 1;
                    for(int i = 0; input[i] != '\0'; i++) {
                        if(input[i] < '0' || input[i] > '9') {
                            es_numero = 0;
                            break;
                        }
                    }
                    
                    if(es_numero) {
                        categoria = atoi(input);
                        if(categoria < 1 || categoria > 3) {
                            printf("Opción fuera de rango. Intenta de nuevo.\n");
                        }
                    } else {
                        printf("Entrada inválida. Solo se permiten números.\n");
                        categoria = 0;
                    }
                } while(categoria < 1 || categoria > 3);
                
                // Configurar según categoría seleccionada
                switch(categoria) {
                    case 1:
                        strcpy(dts.tipo_boleto[contador], "Basica");
                        dts.costo_boleto[contador][0] = 100;
                        intentos_totales = 1;
                        break;
                    case 2:
                        strcpy(dts.tipo_boleto[contador], "Premium");
                        dts.costo_boleto[contador][0] = 250;
                        intentos_totales = 3;
                        break;
                    case 3:
                        strcpy(dts.tipo_boleto[contador], "Oro");
                        dts.costo_boleto[contador][0] = 400;
                        intentos_totales = 5;
                        break;
                }
                
                // Jugar
                llenar_tablero(tablero_num, tablero_final);
                while(intentos < intentos_totales) {
                    destape_tablero(tablero_num, tablero_final, intentos, &dts.premio[contador][0]);
                }
                
                SetConsoleTextAttribute(hConsole, 10);
                printf("\nPremio total: $%d\n", dts.premio[contador][0]);
                SetConsoleTextAttribute(hConsole, 7);
                
                // Guardar datos
                contador++;
                guardar_boletos(&dts, contador);
                
                if(dts.premio[contador-1][0] > 0) {
                    guardar_premios(&dts, contador);
                }
                
                // Guardar fondos (solo el registro actual)
                guardar_fondos(dts.costo_boleto[contador-1][0], dts.premio[contador-1][0], 
                               dts.costo_boleto[contador-1][0] - dts.premio[contador-1][0]);
                
                break;
            }
            
            case 2:
                imprimir_encabezado("----- B O L E T O S   V E N D I D O S -----");
                SetConsoleTextAttribute(hConsole, 11);
		        printf("%-30s %-15s %-6s %-15s %-8s %-8s %-8s %-8s\n", 
        		       "NOMBRE", "CALLE", "NUM", "BANCO", "CODIGO", "TIPO", "COSTO", "PREMIO");
                mostrar_tabla_boletos();
                break;
            
            case 3:
                imprimir_encabezado("----- P R E M I O S   G A N A D O S -----");
                SetConsoleTextAttribute(hConsole, 11);
		        printf("%-30s %-8s %-8s %-8s\n", "NOMBRE", "CODIGO", "TIPO", "PREMIO");
                mostrar_tabla_premios();
                break;
            
            case 4:
                imprimir_encabezado("----- F O N D O S   R E C A U D A D O S -----");
                SetConsoleTextAttribute(hConsole, 11);
		        printf("%-12s %-12s %-12s %-12s %-12s\n", "FECHA", "HORA", "BOLETOS", "PREMIO", "GANANCIA");
                mostrar_tabla_fondos();
                break;
            
            case 5: {
                imprimir_encabezado("----- C O N F I G U R A C I Ó N -----");
                SetConsoleTextAttribute(hConsole, 14);
                printf("1. Participantes\n2. Costos\n\n");
                SetConsoleTextAttribute(hConsole, 7);
                
                // Validación de entrada para configuración
                do {
                    printf("Seleccione (1-2): ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0';
                    
                    int es_numero = 1;
                    for(int i = 0; input[i] != '\0'; i++) {
                        if(input[i] < '0' || input[i] > '9') {
                            es_numero = 0;
                            break;
                        }
                    }
                    
                    if(es_numero) {
                        configuracion = atoi(input);
                        if(configuracion < 1 || configuracion > 2) {
                            printf("Opción fuera de rango. Intenta de nuevo.\n");
                        }
                    } else {
                        printf("Entrada inválida. Solo se permiten números.\n");
                        configuracion = 0;
                    }
                } while(configuracion < 1 || configuracion > 2);
                
                if(configuracion == 1) {
                    SetConsoleTextAttribute(hConsole, 11);
                    printf("\nLímites por categoría:\n");
                    printf("- Básica: 1 intento\n- Premium: 3 intentos\n- Oro: 5 intentos\n");
                } else {
                    SetConsoleTextAttribute(hConsole, 11);
                    printf("\nPrecios:\n");
                    printf("- Básica: $100\n- Premium: $250\n- Oro: $400\n");
                }
                SetConsoleTextAttribute(hConsole, 7);
                break;
            }
            
            case 6:
                continuar = 'n';
                break;
        }
        
        if(opcion != 6) {
            // Validación mejorada para continuar
            do {
                printf("\n¿Desea realizar otra operación? (s/n): ");
                scanf(" %c", &continuar);
                limpiar_buffer();
                
                if(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N') {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("Error: Solo se permite 's' para sí o 'n' para no\n");
                    SetConsoleTextAttribute(hConsole, 7);
                } else if(isdigit(continuar)) {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("Error: No se permiten números. Solo 's' o 'n'\n");
                    SetConsoleTextAttribute(hConsole, 7);
                }
            } while(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N');
        }
    }
    
    return 0;
}

/* IMPLEMENTACIÓN DE FUNCIONES ***********************************************/

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validar_letras(const char *array) {
    for(int i = 0; array[i] != '\0'; i++) {
        char c = array[i];
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
            return 0;
        }
    }
    return 1;
}

int validar_numeros(const char *array, int n) {
    int cont;
    cont = strlen(array);
    
    for(int i = 0; array[i] != '\0'; i++) {
        char c = array[i];
        if((c < '0' || c > '9')) {
            printf("ERROR");
            return 0;
        }
    }
    
    if (n == 1){
        if(cont != 18){
            return 0;
        }
    }
    
    return 1;
}

void generacion_codigo_aleatorio(char array[6]){
    char abecedario[26], aux = 65;
    int al = 0;
    for (int i = 0; i < 26; i ++){
        abecedario[i] = aux;
        aux++;
    } 
    
    for (int i = 0; i < 5; i++){
        do{
            al = rand()%26;    
        }while (abecedario[al] == ' ');
        
        if (abecedario[al] != ' '){
            array[i] = abecedario[al];
            abecedario[al] = ' ';
        }        
    }    
    puts(array);
}

void llenar_tablero(int array[5][5], int array2[5][5]) {
    // Llenar 10 posiciones aleatorias con premios
    for(int i = 0; i < 10; i++) {
        int x, y;
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while(array[x][y] != 0);
        array[x][y] = 5 + rand() % 246;
    }
    
    // Inicializar tablero visible
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            array2[i][j] = 1;
        }
    }
    
    // Mostrar tablero inicial con colores
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    printf("\t1\t2\t3\t4\t5\n\n");
    for(int i = 0; i < 5; i++) {
        printf("%d\t", i + 1);
        for(int j = 0; j < 5; j++) {
            SetConsoleTextAttribute(hConsole, 15);
            printf("%d\t", array2[i][j]);
        }
        printf("\n\n");
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void destape_tablero(int a_original[5][5], int a_final[5][5], int &intentos, int *premio) {
    int x, y;
    char input[10];
    int valido;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Validar coordenada X
    do {
        printf("Fila (1-5): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        valido = 1;
        for(int i = 0; input[i] != '\0'; i++) {
            if(input[i] < '1' || input[i] > '5') {
                valido = 0;
                break;
            }
        }
        
        if(valido) {
            x = atoi(input);
        } else {
            printf("Entrada inválida. Solo números del 1 al 5.\n");
        }
    } while(!valido);
    
    // Validar coordenada Y
    do {
        printf("Columna (1-5): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        valido = 1;
        for(int i = 0; input[i] != '\0'; i++) {
            if(input[i] < '1' || input[i] > '5') {
                valido = 0;
                break;
            }
        }
        
        if(valido) {
            y = atoi(input);
        } else {
            printf("Entrada inválida. Solo números del 1 al 5.\n");
        }
    } while(!valido);
    
    // Procesar selección
    if(a_final[y-1][x-1] == 1) {
        a_final[y-1][x-1] = a_original[y-1][x-1];
        intentos++;
        *premio += a_final[y-1][x-1];
        
        // Mostrar premio con color
        if(a_final[y-1][x-1] > 0) {
            SetConsoleTextAttribute(hConsole, 10);
            printf("\n¡Ganaste $%d!\n\n", a_final[y-1][x-1]);
            SetConsoleTextAttribute(hConsole, 7);
        } else {
            printf("\n¡Casilla vacía!\n\n");
        }
    } else {
        SetConsoleTextAttribute(hConsole, 12);
        printf("\n¡Casilla ya seleccionada! Intenta otra.\n\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
    
    // Mostrar tablero actualizado con colores
    SetConsoleTextAttribute(hConsole, 11);
    printf("\t1\t2\t3\t4\t5\n\n");
    for(int i = 0; i < 5; i++) {
        printf("%d\t", i + 1);
        for(int j = 0; j < 5; j++) {
            if(a_final[i][j] > 1) {
                SetConsoleTextAttribute(hConsole, 10);
            } else {
                SetConsoleTextAttribute(hConsole, 15);
            }
            printf("%d\t", a_final[i][j]);
        }
        printf("\n\n");
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void guardar_boletos(const struct datos *dts, int contador) {
    FILE *f = fopen("boletos_vendidos.txt", "a");
    if(f) {
        // Guardar solo el último boleto
        fprintf(f, "%s|%s|%s|%s|%s|%s|%d|%d\n",
               dts->nombre[contador-1], dts->calle[contador-1], dts->numero_dom[contador-1],
               dts->banco[contador-1], dts->codigo[contador-1], dts->tipo_boleto[contador-1],
               dts->costo_boleto[contador-1][0], dts->premio[contador-1][0]);
        fclose(f);
    }
}

void guardar_premios(const struct datos *dts, int contador) {
    FILE *f = fopen("premios_ganados.txt", "a");
    if(f) {
		// Guardar solo si hay premio
		if(dts->premio[contador-1][0] > 0) {
			fprintf(f, "%s|%s|%s|%d\n",
					dts->nombre[contador-1], dts->codigo[contador-1],
					dts->tipo_boleto[contador-1], dts->premio[contador-1][0]);
		}
		fclose(f);
	}
}

void guardar_fondos(int total_boletos, int total_premios, int ganancias) {
    FILE *f = fopen("fondos_recaudados.txt", "a");
    if(f) {
        // Agregar marca de tiempo
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(f, "%02d/%02d/%04d %02d:%02d - ", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min);
        
        // Guardar datos del registro actual
        fprintf(f, "Boletos: $%d | Premios: $%d | Ganancia: $%d\n", 
               total_boletos, total_premios, ganancias);
        fclose(f);
    }
}

void imprimir_linea(int longitud, char caracter) {
    for(int i = 0; i < longitud; i++) {
        printf("%c", caracter);
    }
    printf("\n");
}

void imprimir_encabezado(const char *titulo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    printf(" %s \n", titulo);
    imprimir_linea(strlen(titulo) + 2, '-');
    SetConsoleTextAttribute(hConsole, 7);
    printf("\n");
}

void mostrar_tabla_boletos() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *f = fopen("boletos_vendidos.txt", "r");
    if(f) {
        char linea[200];
        int primera_linea = 1;      
        
        imprimir_linea(100, '=');
        SetConsoleTextAttribute(hConsole, 15);
        
        // Leer y mostrar datos
        while(fgets(linea, sizeof(linea), f)) {
			char *token;
			char *rest = linea;
			char *datos[8];
			int i = 0;
			
			while((token = strtok_r(rest, "|", &rest))) {
				datos[i++] = token;
			}
            
            if(i >= 8) {
                printf("%-30s %-15s %-6s %-15s %-8s %-8s $%-7d $%-7d\n", 
                       datos[0], datos[1], datos[2], datos[3], datos[4], datos[5], 
                       atoi(datos[6]), atoi(datos[7]));
            }
        }
        fclose(f);
    } else {
        printf("No hay boletos registrados aún.\n");
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void mostrar_tabla_premios() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *f = fopen("premios_ganados.txt", "r");
    if(f) {
        char linea[200];
        int primera_linea = 1;
        
        imprimir_linea(60, '=');
        SetConsoleTextAttribute(hConsole, 15);
        
        // Leer y mostrar datos
        while(fgets(linea, sizeof(linea), f)) {
			char *token;
			char *rest = linea;
			char *datos[4];
			int i = 0;
			
			while((token = strtok_r(rest, "|", &rest))) {
				datos[i++] = token;
			}
			
			if(i >= 4) {
				printf("%-30s %-8s %-8s $%-7d\n", 
						datos[0], datos[1], datos[2], atoi(datos[3]));
			}
		}
		fclose(f);
	} else {
		printf("No hay premios registrados aún.\n");
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void mostrar_tabla_fondos() {
	int ganancia_total = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *f = fopen("fondos_recaudados.txt", "r");
    if(f) {
        char linea[200];
        
        // Encabezado de la tabla (solo una vez)
        
		imprimir_linea(60, '=');
        SetConsoleTextAttribute(hConsole, 15);
        
        // Leer y mostrar datos
        while(fgets(linea, sizeof(linea), f)) {
            char fecha[20], hora[6], resto[100];
            sscanf(linea, "%s %s - %[^\n]", fecha, hora, resto);
            
			int boletos, premios, ganancia;
			sscanf(resto, "Boletos: $%d | Premios: $%d | Ganancia: $%d", &boletos, &premios, &ganancia);
            
            printf("%-12s %-12s %-12d %-12d ", fecha, hora, boletos, premios);
            
            if(ganancia >= 0) {
                SetConsoleTextAttribute(hConsole, 10);
                printf("$%-12d\n", ganancia);
            } else {
                SetConsoleTextAttribute(hConsole, 12);
                printf("-$%-11d\n", -ganancia);
            }
            
            if(ganancia >= 0) {
                SetConsoleTextAttribute(hConsole, 10);
                ganancia_total += ganancia;
            } else {
                SetConsoleTextAttribute(hConsole, 12);
                ganancia_total += -ganancia;
            }
            
            SetConsoleTextAttribute(hConsole, 15);
        }
        fclose(f);
    } else {
        printf("No hay datos de fondos registrados aún.\n");
    }
    
    if(ganancia_total > 0){
    	SetConsoleTextAttribute(hConsole, 7);
    	printf("\n\nEl total de ganancias es: ");
    	SetConsoleTextAttribute(hConsole, 10);
    	printf("$%d \n\n", ganancia_total);
	} else{
		SetConsoleTextAttribute(hConsole, 7);
    	printf("\n\nEl total de ganancias es: ");
    	SetConsoleTextAttribute(hConsole, 4);
    	printf("-$%d \n\n", ganancia_total);
	}
	
    SetConsoleTextAttribute(hConsole, 7);
}
