/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "GestorBiblioteca.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include <stdbool.h>


#define Cls system("clear")
#define Pause system("read -p \"Pulsa la tecla return para continuar..... \" a")
 
void menu();
int MenuPrincipal();
int MenuAdministracion();
void MostrarAviso(const char* texto);
bool_t FiltrarLibros(TLibro *L, char tipo, char *cadena, int nLibros);


void
gestorbiblioteca_1(char *host)
{	
	
 	CLIENT *clnt;
	bool_t  *result_2;
	int  desconexion_1_arg;
	int  guardardatos_1_arg;
	TNuevo  nuevolibro_1_arg;
	int  *result_7;
	bool_t  *result_8;
	TOrdenacion  ordenar_1_arg;
	int  *result_10;
	int  *result_12;
	int  *result_13;

#ifndef	DEBUG

	clnt = clnt_create (host, GESTORBIBLIOTECA, GESTORBIBLIOTECA_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */


		
/*

	result_2 = desconexion_1(&desconexion_1_arg, clnt);
	if (result_2 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = guardardatos_1(&guardardatos_1_arg, clnt);
	if (result_4 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	result_7 = retirar_1(&retirar_1_arg, clnt);
	if (result_7 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_8 = ordenar_1(&ordenar_1_arg, clnt);
	if (result_8 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_9 = nlibros_1(&nlibros_1_arg, clnt);
	if (result_9 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	result_13 = devolver_1(&devolver_1_arg, clnt);
	if (result_13 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

*/
}



int MenuPrincipal()
{
	 int Salida;
	 do
	 {
	 	//Pause;
		Cls;
		printf(" GESTOR BIBLIOTECARIO 1.0 (M. PRINCIPAL)\n");
		printf("*****************************************\n");
		printf("\t1.- M. Administración\n");
		printf("\t2.- Consulta de libros\n");
		printf("\t3.- Préstamo de libros\n");
		printf("\t4.- Devolución de libros\n");
		printf("\t0.- Salir\n\n");
		printf(" Elige opción: ");
		scanf("%d",&Salida);
		
		if(Salida < 0 || Salida >4)
			MostrarAviso("\n\n *** Error en la entrada de Datos.***\n\n");
		if(Salida == 0)
			MostrarAviso("\n\n *** Cerrar aplicacion.***\n\n");
	 }while (Salida<0 || Salida>4);
	 return Salida;
}

void MostrarAviso(const char* texto){
	printf("%s",texto);
	Pause;

}

int MenuAdministracion()
{
	 int Salida;
	 do
	 {
	 	//Pause;
		Cls;
		printf(" GESTOR BIBLIOTECARIO 1.0 (M. ADMINISTRACION)\n");
		printf("**********************************************\n");
		printf("\t1.- Cargar datos Biblioteca\n");
		printf("\t2.- Guardar datos Biblioteca\n");
		printf("\t3.- Nuevo libro\n");
		printf("\t4.- Comprar libros\n");
		printf("\t5.- Retirar libros\n");
		printf("\t6.- Ordenar libros\n");
		printf("\t7.- Buscar libros\n");
		printf("\t8.- Listar libros\n");
		printf("\t0.- Salir\n\n");
		printf(" Elige opción: ");
		scanf("%d",&Salida);
		
		if(Salida < 0 || Salida >8)
			MostrarAviso("\n\n *** Error en la entrada de Datos.***\n\n");
	 }while (Salida<0 /*|| Salida>8*/);
	 return Salida;
}


void Formatea(char *Salida, const char *p, int ancho,char Caracter)
{
	Cadena vacia;
	int len=ancho-strlen(p);
	int l=0,c=0;
	
	while (p[l]!='\0')
	{
		if ((unsigned char)p[l]>128)
			c++;
		l++;
	}
	len+=c/2;
	
	
	if (len<0)
		len=0;
	for (int i=0;i<len; i++)
		vacia[i]=Caracter;
	vacia[len]='\0';
	
	sprintf(Salida,"%s%s",p,vacia);
}

void MostrarLibro(TLibro *L, int Pos, bool_t Cabecera)
{
	Cadena T,A,B,PI;
	if (Cabecera==TRUE)
	{
		printf("%-*s%-*s%-*s%*s%*s%*s\n",5,"POS",58,"TITULO",18,"ISBN",4,"DIS",4,"PRE",4,"RES");
		printf("     %-*s%-*s%-*s\n",30,"AUTOR",28,"PAIS (IDIOMA)",12,"AÑO");
		Formatea(B,"*",93,'*');
		printf("%s\n",B);
	}
	Formatea(T,L->Titulo,58,' ');
	Formatea(A,L->Autor,30,' ');
	strcpy(B,L->Pais);
	strcat(B," (");
	strcat(B,L->Idioma);
	strcat(B,")");
	Formatea(PI,B,28,' ');
	printf("%-5d%s%-*s%*d%*d%*d\n",Pos+1, T, 18,L->Isbn,4,L->NoLibros, 4,L->NoPrestados, 4, L->NoListaEspera);
	printf("     %s%s%-*d\n",A ,PI,12, L->Anio);
}

bool_t FiltrarLibros(TLibro *L, char tipo, char *cadena, int nLibros){

	TLibro *librosFiltrados;
	int nLibrosFiltrados = 0;
        
        bool_t b;
	//for(int i = 0; i < nLibros; i++)
	//{
		b=FALSE;
		switch(tipo){

			case 'I':
				if(strstr(L->Isbn, cadena) != NULL){
					b=TRUE;
				}
				break;
			case 'T':
				if(strstr(L->Titulo, cadena) != NULL){
					b=TRUE;	
				}
				break;
			case 'A':
				if(strstr(L->Autor, cadena) != NULL){
					b=TRUE;	
				}
				break;
			case 'P':
				if(strstr(L->Pais, cadena) != NULL){
					b=TRUE;	
				}
				break;
			case 'D':
				if(strstr(L->Idioma, cadena) != NULL){
					b=TRUE;	
				}
				break;
			case '*':
				
				if(strstr(L->Isbn, cadena) != NULL || strstr(L->Titulo, cadena) != NULL || strstr(L->Autor, cadena) != NULL || strstr(L->Pais, cadena) != NULL || strstr(L->Idioma, cadena))    					{
				b=TRUE;	
				}
				break;

		}/*
		if (b==TRUE)
			MostrarLibro(L, i, FALSE);
	}
	*/
	return b;

}


int main (int argc, char *argv[])
{
	char *host;
	TConsulta  cargardatos_1_arg;
	TConsulta guardardatos_1_arg;
	TConsulta  buscar_1_arg;
	int  conexion_1_arg;
	int  nlibros_1_arg;
	TPosicion  descargar_1_arg;
	TLibro  *result_libro;
	TComRet  comprar_1_arg;
	TComRet  retirar_1_arg;
	TPosicion  prestar_1_arg;
	TPosicion  devolver_1_arg;
	
	bool_t  *result_bool;
	int  *result_int;
	int *numLibros;
	char user[50];
	char text[50];
	int pass = 0;
	int opc1 = 1;
	int opc2 = 0;
	int opc3 = 10;
	int opc4 = 0;
	int idAdmin = 0;
	
	bool registrado = false;
	
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	 CLIENT *clnt;

	clnt = clnt_create (host, GESTORBIBLIOTECA, GESTORBIBLIOTECA_VER, "tcp");
	
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	

	do{

	opc1 = MenuPrincipal();

	switch(opc1){
	
		case 1:	
		
			
			if(registrado == false){
				
				printf("\t***REGISTRAR ADMINISTRADOR***\n");
				printf("Introduce el nombre del admin(admin): ");
				scanf("%s",user);
				printf("Introduce el password del admin(1234): ");
				scanf("%d",&pass);
				conexion_1_arg = pass;
				result_int = conexion_1(&conexion_1_arg, clnt);
				
				printf("El valor del resultado es %d.\n", *result_int);
				if (result_int == (int *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				else if (*result_int == -2)
				{
					printf("ERROR. Password incorrecta\n");
				}
				else if (*result_int == -1)
				{
					printf("ERROR. Administrador ya logueado\n");
				}else{
				printf("CONTRASEÑA CORRECTA");
			      	 idAdmin = *result_int;
				registrado = true;}
			
			}else
			{
			
			opc2 = MenuAdministracion();
				switch(opc2){
					case 1:
						Cls;
						printf("\t***CARGAR DATOS BIBLIOTECA***\n");
						Cadena datos;
						printf("Introduce el nombre de los datos: ");
						scanf("%s", datos);
						
						strcpy(cargardatos_1_arg.Datos, datos);
						cargardatos_1_arg.Ida = idAdmin;
							result_int=cargardatos_1(&cargardatos_1_arg,clnt);
							
							if (result_int == (int *) NULL ) {
								clnt_perror (clnt, "call failed");
							}else if(*result_int == -1){
							printf("ERROR. Numero de libros cargados: %d\n", *result_int);
							}else
							{ 
							printf("DATOS INTRODUCIDOS CORRECTAMENTE, Numero de libros cargados: %d\n", *result_int);
							}
						break;
					case 2:
					 	Cls;
					 	Cadena fichero;
						guardardatos_1_arg;
						printf("\t***GUARDAR DATOS BIBLIOTECA***\n");
						
						// llama a la funcion para guardar los datos en el fichero:
						result_int = guardardatos_1(&idAdmin, clnt);
						
						if(*result_int == 0) {
							numLibros = nlibros_1(&nlibros_1_arg, clnt);
							printf("DATOS GUARDADOS CORRECTAMENTE, Numero de libros guardados: %d\n", *numLibros);
						} else if (result_int == (int *) NULL ) {
							clnt_perror (clnt, "call failed");
						} else if(*result_int == -1){
							printf("ERROR. Id admin: %d\n", *result_int);
						} else if (*result_int == -2) {
							printf("\nError al escribir el numero de libros.");
						} else if (*result_int == -3) {
							printf("\nSe ha producido un error al guardar los datos.");
						}
						
						Pause;
						
						
						break;
					case 3:
						Cls;
						TNuevo nuevolibro_1_arg;
							
								Cls;
								printf("\t***NUEVO LIBRO***\n");
								printf("\t**********************************************\n");
								printf("\tIntroduce el Isbn: ");
								scanf("%s",nuevolibro_1_arg.Libro.Isbn);		
								printf("\tIntroduce el autor:");
								scanf("%s",nuevolibro_1_arg.Libro.Autor);
								printf("\tIntroduce el titulo:");
								scanf("%s",nuevolibro_1_arg.Libro.Titulo);
								printf("\tIntroduce el anio:");
								scanf("%d",&nuevolibro_1_arg.Libro.Anio);
								printf("\tIntroduce el pais:");
								scanf("%s",nuevolibro_1_arg.Libro.Pais);
								printf("\tIntroduce el idioma:");
								scanf("%s",nuevolibro_1_arg.Libro.Idioma);
								printf("\tIntroduce el numero de Libros inicial:");
								scanf("%d",&nuevolibro_1_arg.Libro.NoLibros);
								
								
								result_int = nuevolibro_1(&nuevolibro_1_arg, clnt);
								
									if (result_int == (int *) NULL) {
										clnt_perror (clnt, "call failed");
									}else if(*result_int == 1){
										printf("El libro se ha registrado correctamente");
									}else printf("El libro no se ha creado");
									
						break;	
					case 4:
						Cls;
						printf("\t***COMPRAR LIBROS***\n");
						printf("\tIntroduce el Isbn a buscar: ");
						scanf("%s", comprar_1_arg.Isbn);	
						
						char respuesta;	
						//MostrarLibro(comprar_1_arg->Libro, i, FALSE);	
						printf("\t¿Es este el libro que deseas comprar mas unidades? (s/n)");
						scanf("%c", &respuesta);
						
						
						comprar_1_arg.Ida = idAdmin;
						printf("Introduce Numero de Libros comprados: ");
						scanf("%d",&comprar_1_arg.NoLibros);
						
						result_int = comprar_1(&comprar_1_arg, clnt);
							if (result_int == (int *) NULL) {
								clnt_perror (clnt, "call failed");
							}else{
								printf("**Se han añadido los nuevos libros**");
							}
							
								
						break;
					case 5:
						Cls;
						printf("\t***RETIRAR LIBROS***\n");
						printf("\tIntroduce el Isbn a buscar: ");
						scanf("%s", retirar_1_arg.Isbn);	
						
						char respuesta2;	
						//MostrarLibro(comprar_1_arg->Libro, i, FALSE);	
						printf("\t¿Es este el libro que deseas comprar mas unidades? (s/n)");
						scanf("%c", &respuesta);
						
						
						comprar_1_arg.Ida = idAdmin;
						printf("Introduce Numero de Libros comprados: ");
						scanf("%d",&retirar_1_arg.NoLibros);
						
						result_int = retirar_1(&retirar_1_arg, clnt);
							if (result_int == (int *) NULL) {
								clnt_perror (clnt, "call failed");
							}else{
								printf("**Se han añadido los nuevos libros**");
							}
						break;
					case 6:
						Cls;
						
						printf("\t***ORDENAR LIBROS***\n");
						

						printf("\n");
						printf("Codigo de ordenacion\n");
						printf("0.- Por Isbn\n");
						printf("1.- Por Titulo\n");
						printf("2.- Por Autor\n");
						printf("3.- Por Anio\n");
						printf("4.- Por Pais\n");
						printf("5.- Por Idioma\n");
						printf("6.- Por nº libros Disponibles\n");
						printf("7.- Por nº libros Prestados\n");
						printf("8.- Por nº libros en espera\n");
					
						printf("Introduce Codigo: ");
						scanf("%d",&opc3);						
						
						
						
						break;	
					case 7:
						Cls;
						printf("\t***BUSCAR LIBROS***\n");
						
						printf("Introduce el texto a Buscar: ");
						scanf("%s",text);
						printf("\n");
						printf("Codigo de consulta\n");
						printf("I.- Por Isbn\n");
						printf("T.- Por Titulo\n");
						printf("A.- Por Autor\n");
						printf("P.- Por Pais\n");
						printf("D.- Por Idioma\n");
						printf("*.- Por todos los campos\n");
						
						char opcBuscar;
						printf("Introduce Codigo: ");
						scanf(" %c",&opcBuscar);	
				    			result_int = nlibros_1(&nlibros_1_arg, clnt);
								if(result_int == (int *) NULL){
									clnt_perror(clnt, "call failed" );
								}else{
									int totalLibros = *result_int;
									
									if(totalLibros == 0){
										printf("No hay libros cargados");
									}else{
									
									printf("POS TITULO                                 \tISBN         			     DIS PRE RES\n");
			    						printf(" AUTOR                                   PAIS (IDIOMA)    AÑO\n");
			    						printf("*********************************************************************************************\n");
									descargar_1_arg.Ida=idAdmin;
									int j = 0;
									for(int i = 0; i < totalLibros; i++){
										descargar_1_arg.Pos = i;
										result_libro = descargar_1(&descargar_1_arg, clnt);
										
										if(result_libro == (TLibro *)NULL){
										printf("ERROR. No se han obtenido los detalles del libro %d\n", i + 1);
										}else{
											bool_t cierto = FiltrarLibros(result_libro, opcBuscar, text, 1);
											if(cierto==TRUE) {
												j++;
												MostrarLibro(result_libro, j-1, FALSE);
											} 
											
										}
									
									    }
									    printf("Total libros: %d\n", j);	
							}
						}							
						break;
					case 8:
						Cls;
						printf("\t***LISTAR LIBROS***\n");
						
						result_int = nlibros_1(&nlibros_1_arg, clnt);
						if(result_int == (int *) NULL){
							clnt_perror(clnt, "call failed" );
						}else{
							int totalLibros = *result_int;
							printf("Total libros: %d\n", *result_int);
							if(totalLibros == 0){
								printf("No hay libros cargados");
							}else{
							
							printf("POS TITULO                                 \tISBN    		             DIS PRE RES\n");
            						printf(" AUTOR                                   PAIS (IDIOMA)    AÑO\n");
            						printf("*********************************************************************************************\n");
							descargar_1_arg.Ida=idAdmin;
							for(int i = 0; i < totalLibros; i++){
								descargar_1_arg.Pos = i;
								result_libro = descargar_1(&descargar_1_arg, clnt);
								
								if(result_libro == (TLibro *)NULL){
								printf("ERROR. No se han obtenido los detalles del libro %d\n", i + 1);
								}else{
									MostrarLibro(result_libro, i, FALSE);
								}
							
							    }
							
							}
						}
						
						break;
					case 0:
						Cls;
						printf("\t***SALIR***\n");
						break;	
					
						}
						
			}
		
			break;
		case 2:
			Cls;
			printf("\t***CONSULTA DE LIBROS***\n");		
			printf("Introduce el texto a Buscar: ");
			scanf("%s",text);
			printf("\n");
			printf("Codigo de consulta\n");
			printf("I.- Por Isbn\n");
			printf("T.- Por Titulo\n");
			printf("A.- Por Autor\n");
			printf("P.- Por Pais\n");
			printf("D.- Por Idioma\n");
			printf("*.- Por todos los campos\n");
			char opcConsulta;
			printf("Introduce Codigo: ");
			scanf(" %c",&opcConsulta);	
	    			result_int = nlibros_1(&nlibros_1_arg, clnt);
					if(result_int == (int *) NULL){
						clnt_perror(clnt, "call failed" );
					}else{
						int totalLibros = *result_int;						
						if(totalLibros == 0){
							printf("No hay libros cargados");
						}else{
						printf("POS TITULO                                 \tISBN         			     DIS PRE RES\n");
    						printf(" AUTOR                                   PAIS (IDIOMA)    AÑO\n");
    						printf("*********************************************************************************************\n");
						descargar_1_arg.Ida=idAdmin;
						int j = 0;
						for(int i = 0; i < totalLibros; i++){
							descargar_1_arg.Pos = i;
							result_libro = descargar_1(&descargar_1_arg, clnt);
							
							if(result_libro == (TLibro *)NULL){
							printf("ERROR. No se han obtenido los detalles del libro %d\n", i + 1);
							}else{
								bool_t cierto = FiltrarLibros(result_libro, opcConsulta, text, 1);
								if(cierto==TRUE) {
									j++;
									MostrarLibro(result_libro, i, FALSE);
								} 
								
							}
						
						    }
						    printf("Total libros: %d\n", j);
							
				}
			}
			break;
		case 3:
			Cls;
			printf("\t***PRESTAMO DE LIBROS***\n");
			
			printf("Introduce el texto a Buscar: ");
			scanf("%s",text);
			printf("\n");
			printf("Codigo de consulta\n");
			printf("I.- Por Isbn\n");
			printf("T.- Por Titulo\n");
			printf("A.- Por Autor\n");
			printf("P.- Por Pais\n");
			printf("D.- Por Idioma\n");
			printf("*.- Por todos los campos\n");
			
			char opcBuscar;
			printf("Introduce Codigo: ");
			scanf(" %c", &opcBuscar);
			
			result_int = nlibros_1(&nlibros_1_arg, clnt);
								if(result_int == (int *) NULL){
									clnt_perror(clnt, "call failed" );
								}else{
									int totalLibros = *result_int;
									
									if(totalLibros == 0){
										printf("No hay libros cargados");
									}else{
									
									printf("POS TITULO                                 \tISBN         			     DIS PRE RES\n");
			    						printf(" AUTOR                                   PAIS (IDIOMA)    AÑO\n");
			    						printf("*********************************************************************************************\n");
									descargar_1_arg.Ida=idAdmin;
									int j = 0;
									for(int i = 0; i < totalLibros; i++){
										descargar_1_arg.Pos = i;
										result_libro = descargar_1(&descargar_1_arg, clnt);
										
										if(result_libro == (TLibro *)NULL){
										printf("ERROR. No se han obtenido los detalles del libro %d\n", i + 1);
										}else{
											bool_t cierto = FiltrarLibros(result_libro, opcBuscar, text, 1);
											if(cierto==TRUE) {
												j++;
												MostrarLibro(result_libro, i, FALSE);
											} 
											
										}
									
									    }
									    printf("Total libros: %d\n", j);	
							}
							
							char opcBuscar2;
							printf("¿Quieres sacar algun libro de la biblioteca?(s/n) ");
							scanf(" %c",&opcBuscar2);
							
							if(opcBuscar2 != 's'){
							
							}else{
								printf("Introduce la posicion del libro a realizar su prestamo: ");
								scanf("%d",&opc3);
								prestar_1_arg.Pos = opc3-1;
								
								result_int = prestar_1(&prestar_1_arg, clnt);
								if (result_int == (int *) NULL) {
									clnt_perror (clnt, "call failed");
								}else if(*result_int == -1){
									printf("ERROR. La biblioteca no se ha inicializado");
								}else if(*result_int == -2){
									printf("ERROR. Algo");
								}else if(*result_int == -3){
									printf("ERROR. Algo");
								}else{
									printf("**EL prestamo se ha concedido, recoge el libro en el mostrador.**\n");
								}
							}
							
							
							
							
						}	
			
			
			
			break;
		case 4:
			Cls;
			printf("\t***DEVOLUCION DE LIBROS***\n");
			printf("Introduce el texto a Buscar: ");
			scanf("%s",text);
			printf("\n");
			printf("Codigo de consulta\n");
			printf("I.- Por Isbn\n");
			printf("T.- Por Titulo\n");
			printf("A.- Por Autor\n");
			printf("P.- Por Pais\n");
			printf("D.- Por Idioma\n");
			printf("*.- Por todos los campos\n");
			
			char opcBuscar2;
			printf("Introduce Codigo: ");
			scanf(" %c", &opcBuscar2);
			
			result_int = nlibros_1(&nlibros_1_arg, clnt);
								if(result_int == (int *) NULL){
									clnt_perror(clnt, "call failed" );
								}else{
									int totalLibros = *result_int;
									
									if(totalLibros == 0){
										printf("No hay libros cargados");
									}else{
									
									printf("POS TITULO                                 \tISBN         			     DIS PRE RES\n");
			    						printf(" AUTOR                                   PAIS (IDIOMA)    AÑO\n");
			    						printf("*********************************************************************************************\n");
									descargar_1_arg.Ida=idAdmin;
									int j = 0;
									for(int i = 0; i < totalLibros; i++){
										descargar_1_arg.Pos = i;
										result_libro = descargar_1(&descargar_1_arg, clnt);
										
										if(result_libro == (TLibro *)NULL){
										printf("ERROR. No se han obtenido los detalles del libro %d\n", i + 1);
										}else{
											bool_t cierto = FiltrarLibros(result_libro, opcBuscar, text, 1);
											if(cierto==TRUE) {
												j++;
												MostrarLibro(result_libro, i, FALSE);
											} 
											
										}
									
									    }
									    printf("Total libros: %d\n", j);	
							}
							
							char opcBuscar2;
							printf("¿Quieres sacar algun libro de la biblioteca?(s/n) ");
							scanf(" %c",&opcBuscar2);
							
							if(opcBuscar2 != 's'){
							
							}else{
							
							printf("Introduce la posicion del libro a realizar la devolucion: ");
							scanf("%d",&opc3);
							devolver_1_arg.Pos = opc3-1;
							
							result_int = devolver_1(&devolver_1_arg, clnt);
							if (result_int == (int *) NULL) {
								clnt_perror (clnt, "call failed");
							}else if(*result_int == -1){
								printf("ERROR. La biblioteca no se ha inicializado");
							}else if(*result_int == -2){
								printf("ERROR. Algo");
							}else if(*result_int == -3){
								printf("ERROR. Algo");
							}else{
								printf("**Se ha devuelto el libro y se pondra en la estanteria.**\n");
							}
							
							}
						}	
			
			
			
			break;

	
	}
	Pause;
	}while(opc1 != 0);

	
	

clnt_destroy (clnt);

	exit (0);
}


