#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////////////

/*Una empresa que se dedica a la reubicación de empleados tiene una lista de 500
empleados (como máximo) con la siguiente información.

	- Nombre y apellido. Con el formato "Apellidos, Nombres".
	- Fecha de nacimiento del empleado.
	- Sexo (M, F)
	- Nacionalidad

Las nacionalidades pueden ser: Argentina, Uruguaya, Chilena, Peruana, Boliviana,
Paraguaya, Brasileña. Un empleado puede tener más de una nacionalidad.

Se pide armar las estructuras y el programa que permita:

V	A. Realizar la carga de datos. Validar todos los datos ingresados.

V	B- Mostrar un listado de personas nacidas antes de 2000 ordenado por Fecha de
	nacimiento. Mostrar todos los datos de cada empleado.
	
V	C- Ingresar un Apellido por teclado y listar todas las mujeres que se apellidan igual y
	además nacieron en verano. Mostrar todos los datos de cada empleado.
	
V	D- Emitir un informe de empleados uruguayos y argentinos que tengan más de una
	nacionalidad. Mostrar todos los datos de cada empleado.
	
V	E- Indicar el porcentaje de empleados argentinos

*/

//////////////////////////////////////////////////////////////////////////////////////////////

#define MAX 500		// Maximo empleados 
#define MAX_C 20	// Caracteres 
#define MAX_N 8		// Cantidad de naciones (son 7 pero en el primer lugar puse al cero)

//////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {	FALSE,	TRUE} T_Bool;

typedef struct {
	int Dia;
	int Mes;
	int Anio;
} T_Fecha;
//   		     0		 1		    2	     3		  4		    5 	       6		  7
typedef enum { CERO, ARGENTINA, URUGUAYA, CHILENA, PERUANA, BOLIVIANA, PARAGUAYA, BRASILERA
} E_Nacion;	 // Si no agregaba el cero, tenia conflicto en la funcion de Uruguayos y Argentinos

typedef struct {
	E_Nacion Nacionalidad[MAX_N];
	int cantNacion;
} T_Nacion;

typedef struct  {
    char Nombre[MAX_C];
    char Apellido[MAX_C];
    char Sexo[2];
    T_Fecha Fecha;
    T_Nacion Nacion;
    int id;
} T_Empleado;

//////////////////////////////////////////////////////////////////////////////////////////////

int ingresarDatos(T_Empleado vec[MAX],int *cantidadEmpleados){
    int i,j;
    int cantidadNacion=1;
    int nacTemp = 1;

	printf("\n+--------------------------------------------------------+\n|	  INGRESAR DATOS DE LA SIGUIENTE MANERA:         |\n|		> APELLIDO (espacio) NOMBRE              |\n|		> NACIMIENTO DIA/MES/ANIO                |\n|		> SEXO (F/M)                             |\n|		> NACIONALIDAD/ES                        |\n|		  --> [1] ARGENTINA                      |\n|		  --> [2] URUGUAYA                       |\n|		  --> [3] CHILENA                        |\n|		  --> [4] PERUANA                        |\n|		  --> [5] BOLIVIANA                      |\n|		  --> [6] PARAGUAYA                      |\n|		  --> [7] BRASILERA                      |\n+--------------------------------------------------------+\n\n");
		

    printf(" Ingresar cantidad de empleados> ");
    scanf("%i", &*cantidadEmpleados);
    printf("\n----------------------------------------------------------\n");
    
   //Evaluación de máximo lógico, si se pasa del máximo permitido, vuelve a preguntar
    while(*cantidadEmpleados>MAX){	
                	printf("Ingrese nuevamente la cantidad de empleados");
					scanf("%i", &*cantidadEmpleados);	
					}
   //////////////////////////////////////////////////////////////////////////////////////////////////////////					
    
    for(i=0;i<*cantidadEmpleados;i++){
 
		printf("\nIngrese Apellido   > ");
		scanf("%s", vec[i].Apellido);
		fflush(stdin);
		printf("\nIngrese Nombre     > ");
		scanf("%s", vec[i].Nombre);
		fflush(stdin);
		printf("Ingresar nacimiento con formato aa/aa/aaaa         > ");
		scanf("%i/%i/%i", &vec[i].Fecha.Dia, &vec[i].Fecha.Mes, &vec[i].Fecha.Anio);

		printf("Ingresar sexo                 > ");
		scanf("%s", vec[i].Sexo);

		printf("Cantidad de nacionalidades    > ");
		scanf("%i", &cantidadNacion);		
		vec[i].Nacion.cantNacion = cantidadNacion;

		for( j = 0; j < cantidadNacion; j++){
			printf("  > [%i] Ingresar nacionalidad > ", j+1);
			scanf("%i", &nacTemp);
			vec[i].Nacion.Nacionalidad[j] = nacTemp;
		}

        vec[i].id = i;

    printf("\n----------------------------------------------------------\n\n");
    }
    
    return *cantidadEmpleados;
}

T_Bool esVerano(T_Fecha fecha){
	
//	El verano 21 de diciembre a 21 de marzo
	
	T_Bool verano;
	
	if(((fecha.Mes==12)&&(fecha.Dia >= 21)) || ((fecha.Mes == 3)&&(fecha.Dia<=21)) || (fecha.Mes==1) || (fecha.Mes == 2) ){
		verano = TRUE;
	} else {
		verano = FALSE;
	}

	return verano;	
}

void mujeresVerano(T_Empleado vec[MAX], int cantidad){
	
	int i;
	int flag=0;
	char apellido[MAX_C];
	int temp[MAX];	// indices 
	int contador = 0;

    printf("\n-----------------------------------------------------\n");

	printf("\n##################|   Mujeres con mismo apellido y nacidas en verano: |##################   ");
	printf("\nIngresar apellido >");
	scanf("%s", apellido);
	
	for ( i = 0; i < cantidad; i++ ){
		
		if((strcmp(apellido, vec[i].Apellido)==0) && (esVerano(vec[i].Fecha)) && ((strcmp(vec[i].Sexo,"F"))==0)) {
			
			temp[i] = vec[i].id;
			contador++;
			flag=1;
			
		}
		
	}
	
	if(flag == 1){
		for ( i = 0; i < contador; i++){
			informar(vec, temp[i]);
		}	
	} else {
		printf("\n  *** NO SE ENCONTRARON RESULTADOS ***   \n");
	}

	
	printf("\n-----------------------------------------------------\n");

}

int porcentajeArg(T_Empleado vec[MAX], float cantidad){
	
	int resultado = 0;
	int i,j;
	int argentinos = 0;
	
	for( i = 0; i <= cantidad; i++ ){
		for( j = 0; j < MAX_N; j++){
			if(vec[i].Nacion.Nacionalidad[j] == ARGENTINA){
				argentinos++;
			}
		}
	}
	
	resultado =((argentinos*100)/(cantidad));
	
	return resultado;
}

int uru_Argentino(T_Empleado vec[MAX], int cantidad){
	
	int i,j;

	int contador=0;
	int temp[MAX];	// indices 
	int idTemp=0;
	int flag = 0;
	
	T_Bool ARGENTINO, URUGUAYO;
	
	ARGENTINO = FALSE;
	URUGUAYO = FALSE;

	for( i = 0; i <= cantidad; i++ ){
		

		if( vec[i].Nacion.cantNacion > 1 ){

			for( j = 0; j < MAX_N; j++ ){

				if(vec[i].Nacion.Nacionalidad[j] == ARGENTINA) {
					ARGENTINO = TRUE;
				}
				
				if(vec[i].Nacion.Nacionalidad[j] == URUGUAYA) {
					URUGUAYO = TRUE;	
				}
				
			}
			
			if ( ARGENTINO && URUGUAYO) {
				// Sumo al contador y guardo el id del empleado en el vector temporal temp
				temp[i] = vec[contador].id;
				contador++;
				flag = 1;
				
			}
			
			ARGENTINO = FALSE;
			URUGUAYO = FALSE;
		}

	}
	
	printf("\n##################|   INFORME DE URUGUAYOS Y ARGENTINOS CON MAS DE UNA NACIONALIDAD |##################    \n\n");
	
	if(flag == 1){
	
		for ( i = 0; i < contador; i++){
			informar(vec, temp[i]);
		}
		
	} else {
		printf(" *** NO SE ENCONTRARON URUGUAYOS Y/O ARGENTINOS *** \n");
	}

	
	return cantidad;
	
    printf("\n-----------------------------------------------------\n");
}

int antesDosmil(T_Empleado vec[MAX],int cantidad){
	
	int contador=0;
	int i,j,aux=0;
	int temp[MAX];	// indices 
	
	for( i = 0; i < cantidad; i++ ){
		if(vec[i].Fecha.Anio < 2000 ){
			temp[contador] = vec[i].id;
			contador++;
		} else {
			temp[contador] = -1;
		}
	}
	
	for ( i = 0; i < cantidad; i++ ){
		
		for( j = i + 1; j < cantidad; j++ ){
			
			if(vec[temp[i]].Fecha.Anio > vec[temp[j]].Fecha.Anio){
				
				aux=temp[i];
				temp[i]=temp[j];
				temp[j] = aux; 
				
			}
			
		}
				
	}
	
	printf("\n##################|   PERSONAS NACIDAS ANTES DEL 2000 DE MAYOR A MENOR: |##################    \n\n");
	
	for ( i = 0; i < contador; i++){
		informar(vec, temp[i]);
	}
	
	return contador;
	
    printf("\n-----------------------------------------------------\n");
	
}

void informar(T_Empleado vec[MAX], int id ){
	
	int j;
	char nacionTemp[MAX_C];
	strcpy(nacionTemp, "");	

	for( j = 0; j < MAX_N; j++){
		if(vec[id].Nacion.Nacionalidad[j]!=0){
			switch(vec[id].Nacion.Nacionalidad[j]){
				case ARGENTINA:
								strcat(nacionTemp, "ARGENTINA, ");
								break;
				case URUGUAYA:
								strcat(nacionTemp, "URUGUAYA, ");
								break;
				case CHILENA:
								strcat(nacionTemp, "CHILENA, ");
								break;
				case PERUANA:
								strcat(nacionTemp, "PERUANA, ");
								break;
				case BOLIVIANA:
								strcat(nacionTemp, "BOLIVIANA, ");
								break;
				case PARAGUAYA:
								strcat(nacionTemp, "PARAGUAYA, ");
								break;
				case BRASILERA:
								strcat(nacionTemp, "BRASILERA, ");
								break;
			}
		}
	}	
	
	printf("     [%s %s]  Nacido el: [%i/%i/%i]  Sexo: [%s]  Nacionalidad/es: [%s]\n", 
	vec[id].Apellido,
	vec[id].Nombre,
	vec[id].Fecha.Dia,
	vec[id].Fecha.Mes,
	vec[id].Fecha.Anio,
	vec[id].Sexo,
	nacionTemp);
	
	return;
}

void Ejecutar(){
	int ml=0;
    T_Empleado vector[MAX];
    int cant = ingresarDatos(vector, &ml);
	antesDosmil(vector,cant);	
	mujeresVerano(vector, cant);
	uru_Argentino(vector, cant); 

	printf("\n##################|   PORCENTAJE DE EMPLEADOS ARGENTINOS: [%i%%]   |################## \n", porcentajeArg(vector,cant));
	
	return;
}

int main(){

	Ejecutar();

    return 0;
    
}

