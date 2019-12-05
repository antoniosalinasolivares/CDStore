#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct disco_ {
  size_t state;
  char nombre[50];
  char artista[20];
  int precio;
  int ano;
  struct disco_ *sig;
};
typedef struct disco_ disco;

disco *disco_builder(char nombre[50], char artista[20],int precio,int ano,int state){
  disco *aux=(disco*)malloc(sizeof(disco));
  aux->state = state;
  aux->precio = precio;
  aux->ano = ano;
  aux->sig = NULL;
  strcpy(aux->nombre , nombre);
  strcpy(aux->artista , artista);
  return aux;
}

void print_disco(disco *this){

    printf("._______.\n");
    printf("|/     \\| %s\n",this->nombre);
    printf("|   o   | %s\n",this->artista);
    printf("|\\_____/| %d $%d\n",this->ano, this->precio);

}

char *disco_toFile(disco *this){
  char *tmp = malloc(100*sizeof(char));
  strcat(tmp,this->nombre);
  strcat(tmp,"|");
  strcat(tmp,this->artista);
  strcat(tmp,"|");
  char ano[12];
  sprintf(ano, "%d", this->ano);
  strcat(tmp,ano);
  strcat(tmp,"|");
  char precio[12];
  sprintf(precio, "%d", this->precio);
  strcat(tmp,precio);
  strcat(tmp,"|");
  char elementos[12];
  sprintf(elementos, "%zu", this->state);
  strcat(tmp,elementos);

  return tmp;
}
/*-----------------------------------------------------------------------------------*/

struct usuario_ {
  size_t state;
  char username[20];
  char contrasena[50];
  int compras;
  int total;
  struct usuario_ *sig;
};
typedef struct usuario_ usuario;

usuario *usuario_builder(char username[20], char contrasena[50],int compras,int total){
  usuario *this = (usuario*)malloc(sizeof(usuario));
  this->compras = compras;
  this->total = total;
  this->sig = NULL;
  this->state =1;
  strcpy(this->username, username);
  strcpy(this->contrasena, contrasena);
  return this;
}

void print_usuario(usuario *this){
  if (this == NULL) return;
  printf("._______.\n");
  printf("| (·u·) | %s\n",this->username);
  printf("| ||_|L | compras:%d\n",this->compras);
  printf("|__|M|__| total:$%d\n", this->total);
}

char *usuario_toFile(usuario *this)
{
  char *tmp = malloc(100*sizeof(char));
  strcat(tmp,this->username);
  strcat(tmp,"|");
  char compras[12];
  sprintf(compras, "%d", this->compras);
  strcat(tmp,compras);
  strcat(tmp,"|");
  char total[12];
  sprintf(total, "%d", this->total);
  strcat(tmp,total);
  strcat(tmp,"|");
  strcat(tmp,this->contrasena);
  strcat(tmp,"|");
  strcat(tmp,"\n");
  return tmp;
}
