/*Parcial

consigna: 
1._ Cree un programa para el ingreso de alumnos, con sus nombres, apellidos, cantidad de materias, promedio de materias, validar promedio de materias este entre3 y 7-
2.- Ordene de forma ascendente y muestre todos los datos segun numero de padron
3.- Realice una busqueda binaria segun numero de padron donde muestre todos los datos del alumno
*/

#include<stdio.h>
#define MAX 50
#define MAX_C 50
typedef struct{
int legajo;
char nombre[MAX_C];
char apellido[MAX_C];
int cant_materias;
int prom_materias;	
int id;
}t_alumno;
typedef t_alumno vec_alumno[MAX];//en adelante vec_alumno es un struct
typedef vec_alumno alu;//en adelante alu es un vector de tipo struct

//declaracion de todas las funciones
int leer_val(int *n, int min,int max);
int ingresar_datos(vec_alumno alu, int *ml);
void mostrar_datos(vec_alumno alu,int ml);
int ordenar(vec_alumno alu, int maxlog);
void mostrar_ordenados(vec_alumno alu, int id);
void buscar_binario(vec_alumno alu, int a_buscar, int ml );
void mostrar_busqueda(vec_alumno alu, int medio);
void busqueda_secuencial(vec_alumno alu, int ml, int a_buscar);
//////////////////////////

//funcion principal
void main(){
	
vec_alumno alum;	
int a_buscar,ml,a_buscar2;
int i,id=0;	
ingresar_datos(alum, &ml);//adentro de esta funcion llamaré a int mostrar_datos;
ordenar(alum, ml);//adentro llamo a mostrar_ordenados;

printf("\n -Buscar por padron      > ");
scanf("%i", &a_buscar);
buscar_binario(alum, a_buscar, ml);

printf("\n -Buscar por padron 2    > ");
scanf("%i", &a_buscar);
busqueda_secuencial(alum , ml, a_buscar);
}

//funcion ingresar datos
int ingresar_datos(vec_alumno alu, int *ml)
{
*ml=1;
int prom,contador=0;
int ingreso=0;
 // 0 : si
 // 1 : no
int i=0;
    while((i<500)&&(ingreso!=1))//mientras este adentro del maximo fisico y el ingreso sea distinto de 1.
    {
	printf("Ingrese nombre\n ");
	scanf("%s", &alu[i].nombre);
	printf(" \n\npromedio de materias\n");
	leer_val(&prom,3,10);
	alu[i].prom_materias=prom;
	printf("\nIngrese legajo\n");
	scanf("%i", &alu[i].legajo);
	printf("\nIngrese cantidad de materias\n");
	scanf("%i", &alu[i].cant_materias);

	printf("\nSi desea ingresar otro alumno presione 0 para continuar, 1 para finalizar\n");
	fflush(stdin);
	scanf("%i", &ingreso);
	
	i++;
	contador++;

	}
	*ml=contador;
	

    mostrar_datos(alu, *ml);
    return *ml;//este ml lo necesito para que lo reciba la funcion ordenar
    
}


//funcion leer valido, valido que el promedio solo este entre 3 y 10.
int leer_val(int *n, int min,int max)
{
printf("Ingrese un número entre %d y %d \n",min,max);
  scanf("%i", n);
  	while((*n>max)||(*n<min))
  {
   	printf("Vuelva a ingresar un número válido\n");
    scanf("%i", n);
  }
  return *n;
}



//funcion mostrar datos crudos, simple y llanamente los que fueron ingresados
void mostrar_datos(vec_alumno alu,int ml)
{
int i=0;
printf("el maxinmo logico que llega a esta funcion es : %i\n", ml);
for(i=0;i<ml;i++)
{
printf("\nLegajo %i, Nombre del alumno es %s,Cant materias %i, prom materias %i\n ", alu[i].legajo, alu[i].nombre, alu[i].cant_materias, alu[i].prom_materias);	

}
}

//funcion ordenar
int ordenar(vec_alumno alu, int ml)
{
int i,j;
t_alumno aux;
	for(i=1;i<ml;i++)//Numero de pasos, +externo: elementos ml-1  
	{
			for(j=0;j<ml;j++)//Numero de comparaciones, +interno: ml
				{									//vuelta 1 i=1------------legajo 0 vs legajo1     
				if(alu[j].legajo>alu[i].legajo)		//vuelta 2 i=2------------legajo 1 vs legajo2
                {                                   //Ascendente j<i, caso contrario intercambiar
		    	aux=alu[j];                  //Acciones: alu[0].legajo<alu[1].legajo <<<--el alumno 1 ahora es el alumno cero         
				alu[j]=alu[i];
				alu[i] = aux; 
	 
				}
    			  
          }
     
  	}
  	
  	
  	for(i=0;i<ml;i++)
	  {
  	 mostrar_ordenados(alu, i);	
   	  }
    return ml;
      }

//funcion mostrar datos ORDENADOS
void mostrar_ordenados(vec_alumno alu, int id)
{
printf("\nLegajo %i  del alumno  %s Cant materias %i\n", alu[id].legajo,  alu[id].nombre, alu[id].cant_materias);	
}

//funcion buscar binaria, como condicion el arreglo debe volver arreglado
void buscar_binario(vec_alumno alu, int a_buscar, int ml )
{
int inicio,medio,fin;
int flag = 0;
inicio = 0;
fin = ml;

printf("........................................");
while((inicio<fin)&&(flag==0))
  { medio = (inicio+fin)/2;
	if(alu[medio].legajo<a_buscar)//el medio para atras seguro que no estaaaaa
	{ 
	inicio = medio + 1;           //redefino inicio,si legajo mayor a la mitad, empieza desde la mitad
    }else{
    
			if(alu[medio].legajo==a_buscar)//el medio es la busqueda. listo-.
			{
    		   printf("El alumno bi buscado es: %i %s", alu[medio].legajo, alu[medio].nombre );
			   //mostrar_busqueda(alu, medio);
			   flag=1;                     //encontrado, detener la busqueda	
			}else{                      
	 				fin=medio-1;	       //redefino fin, si el legajo es menor que el medio. termina en el medio
				 }
			        //redefino el medio.
	
	    }
	if(inicio>fin)
	printf("No se encontró");
	
  }
 
}


//mostrar_busqueda
void mostrar_busqueda(vec_alumno alu, int medio)
{
printf("El alumno buscado es: %i %s", alu[medio].legajo, alu[medio].nombre );	
}


//busqueda secuencial
void busqueda_secuencial(vec_alumno alu, int ml, int a_buscar)

{

int i;
int pos;
pos=-1;
while((i<ml)&&(pos<0)&&(alu[i].legajo<=a_buscar))
 {
 
  if(alu[i].legajo==a_buscar)
  {pos=i;
  }else{
   i++;
  }
 
}

 mostrar_busqueda(alu, pos);

	
}
