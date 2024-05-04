/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "GestorBiblioteca.h"
#include <unistd.h>
#define MAX_LIBROS 10000	

TLibro *Biblioteca = NULL;

int numLibros = 0;
int tam = 0;
int idAdmin = -1;
Cadena nameFich = "";
int campoOrd = 0;

  // Convertir pass a una cadena de caracteres
  // char pass_str[10];
  // sprintf(pass_str, "%d", pass);

  // Imprimir el valor de pass utilizando perror
  // perror("El valor de pass es");
  // perror(pass_str);


int *
conexion_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;
	int pass = *argp;
	if(pass != 1234){
		result = -2;
	}else if(idAdmin != -1){
		result = -1;
	}else{
		idAdmin = 1 + rand() % RAND_MAX;
		result = idAdmin;
	}


	return &result;
}

bool_t *
desconexion_1_svc(int *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	if(idAdmin != -1){
		idAdmin = -1;
		result = idAdmin;
	}

	return &result;
}

int *
cargardatos_1_svc(TConsulta *argp, struct svc_req *rqstp)
{
	//printf("Ejecucion cargar datos servidor");
	static int  result;
	
	if(idAdmin != argp-> Ida){
		result = -1;
	}else{
		
		FILE *archivo = fopen(argp->Datos, "rb");
	
		if(archivo != NULL){
			
		result = fread(&numLibros, sizeof(numLibros), 1, archivo);
		
		Biblioteca = (TLibro *) malloc(sizeof(TLibro)*numLibros);

		
		if(Biblioteca == NULL){
			perror("ERROR: No se ha reservado memoria para la biblioteca");
		}else{
		
			fread(Biblioteca, sizeof(TLibro), numLibros, archivo);
		}
		fclose(archivo);
		strcpy(nameFich, argp->Datos);
		result = numLibros;
		}
		else
		   result = -1;		
	
	}
	
	return &result;
}

int *
guardardatos_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result, valor;
	
	if(idAdmin != *argp){
		result = -1;
	}else{
		FILE *archivo = fopen(nameFich, "w+b");
		
		/*
		if (access(argp->Datos, F_OK) == 0) {
		    // el archivo existe se abre en modo de escritura
		    archivo = fopen(argp->Datos, "wb");
		} else {
		    // el archivo no existe se crea en modo de escritura
		    archivo = fopen(argp->Datos, "wb+");
		}*/		
	
		if(archivo != NULL){
			// escribir el numero de libros en el fichero:
			valor = fwrite(&numLibros, sizeof(numLibros), 1, archivo);
			
			if(valor!=1) {
				perror("\nError al escribir el numero de libros.");
				result = -2;				
			} else {
				//guardar los datos de los libros:
				
				//Biblioteca = (TLibro *) malloc(sizeof(TLibro)*numLibros); //necesario?
				
				valor = fwrite(Biblioteca, sizeof(TLibro), numLibros, archivo);
				
				if(valor != numLibros) {
					perror("\nError al escribir los datos de los libros.");
					result = -3;
				} else {
					result = 0; //datos guardados
				}
			}
			fclose(archivo);	
		} else {
			perror("\nError al abrir el archivo");
			result = -4;
		}	
	}
	return &result;
		
}

int *
nuevolibro_1_svc(TNuevo *argp, struct svc_req *rqstp)
{
	static int  result;

	TLibro nuevoLibro = argp->Libro;
	
	if(Biblioteca == NULL){
		result = -1;
	}else{
			
		if(numLibros < MAX_LIBROS)
		{
			Biblioteca[numLibros] = nuevoLibro;
			numLibros++;
			result = 1;
		}else result = 0;	
	}
	

	
	return &result;
}

int *
comprar_1_svc(TComRet *argp, struct svc_req *rqstp)
{
	static int  result;

	int i = 0;
	 bool_t encontrado = FALSE;
	do{
		if(strstr(argp->Isbn, Biblioteca[i].Isbn) != NULL){
					encontrado = TRUE;
			}else i++;
	}while(!encontrado && i < numLibros);

	if(encontrado){
	Biblioteca[i].NoLibros += argp->NoLibros;
		result = Biblioteca[i].NoLibros;
	}else{
	perror("El libro no se ha encontrado");
	}

	return &result;
}

int *
retirar_1_svc(TComRet *argp, struct svc_req *rqstp)
{
	static int  result;

	int i = 0;
	 bool_t encontrado = FALSE;
	do{
		if(strstr(argp->Isbn, Biblioteca[i].Isbn) != NULL){
					encontrado = TRUE;
			}else i++;
	}while(!encontrado && i < numLibros);

	if(encontrado){
	Biblioteca[i].NoLibros -= argp->NoLibros;
		result = Biblioteca[i].NoLibros;
	}else{
	perror("El libro no se ha encontrado");
	}

	return &result;
}

bool_t *
ordenar_1_svc(TOrdenacion *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
nlibros_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	result = numLibros;

	return &result;
}

int *
buscar_1_svc(TConsulta *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

TLibro *
descargar_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static TLibro  result;

	/*if(argp->Pos < 0 || argp->Pos >= numLibros){
	perror("ERROR. La posicion no esta permitida\n");
	return NULL;
	}
*/
	result = Biblioteca[argp->Pos];

	return &result;
}

int *
prestar_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static int  result;
	int pos = argp->Pos;
	
	if(Biblioteca == NULL){
		perror("ERROR. Biblioteca no inicializada");
		result = -2; // biblioteca no inicializada
	}else if(pos < 0 || pos >=numLibros){
		perror("ERROR.Posicion fuera de rango");
		result = -1; // error fuera de rango
	}else{
		TLibro *libro = &Biblioteca[pos];
		if(libro->NoLibros == 0){
			//perror("ERROR. No hay suficientes libros disponibles");
			libro->NoListaEspera += 1;
			result = 0; // usuario en lista de espera
		}else if(libro->NoLibros > 0){
		libro->NoPrestados+=1;
		result = 1; // libro prestado
		libro->NoLibros -=1; // restar un disponible?
		}
	}
	
	return &result;
}

int *
devolver_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static int  result;

	int pos = argp->Pos;
	
	if(Biblioteca == NULL){
		perror("ERROR. Biblioteca no inicializada");
		result = -2;
	}else if(pos < 0 || pos >=numLibros){
		perror("ERROR.Posicion fuera de rango");
		result = -1; // fuera de rango
	}else{
		TLibro *libro = &Biblioteca[pos];
		if(libro->NoPrestados == 0){
			perror("ERROR. No hay libros prestados, por tanto no puedes devolverlo");
			result = 2; // no hay libros prestados.
		}else if(libro->NoListaEspera > 0){
			libro->NoListaEspera -= 1;
			result = 0; // se ha reducido la lista de espera
		} else {
			libro->NoPrestados-=1; // se quita un libro prestado
			libro->NoLibros+=1;//se añade un libro mas disponible
			result = 1; // el libro se ha devuelto y hay un libro disponible mas
		}
	}
	return &result;
}



