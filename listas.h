#include "nodos.h"
#include <stdlib.h>
#include <assert.h>

struct lista_discos_ {
  disco *head, *tail;
  int size;
};
typedef struct lista_discos_ lista_discos;

char** str_split(char* a_str, const char a_delim);


lista_discos *lista_discos_builder(){
  lista_discos *tmp = (lista_discos*)malloc(sizeof(lista_discos));
  tmp->head = NULL;
  tmp->tail = NULL;
  tmp->size = 0;
  return tmp;
}

void add_disco(lista_discos *this, disco *cd){
  if(this->head == NULL && this->tail == NULL){
    this->head = cd;
    this->tail = cd;
  }else{
    this->tail->sig = cd;
    this->tail = cd;
  }
  (this->size)++;
}

void print_lista_discos(lista_discos *this){
  if(this->head != NULL){
    disco *scout = this->head;
    int i = 1;
    while (0==0) {
      if(scout->state > 0){
      printf("\nid %d\n",i);
      print_disco(scout);
      }
      if(scout->sig == NULL){
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

void search_disco_nombre(char *nombre, lista_discos *this){
  if(this->head != NULL){
    disco *scout = this->head;
    int coincidencias = 0 , i = 1;
    while (0==0) {
      if(strcmp(scout->nombre,nombre)==0){

        printf("\n%d",i);
        print_disco(scout);
        coincidencias++;
      }
      if(scout->sig == NULL){
        if (coincidencias == 0) {
          printf("No se encontraron coincidencias para: %s\n",nombre);
        }
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

void search_disco_artista(char *artista, lista_discos *this){
  if(this->head != NULL){
    disco *scout = this->head;
    int coincidencias = 0 , i = 1;
    while (0==0) {
      if(strcmp(scout->artista,artista)==0){

        printf("\n%d",i);
        print_disco(scout);
        coincidencias++;
      }
      if(scout->sig == NULL){
        if (coincidencias == 0) {
          printf("No se encontraron coincidencias para: %s\n",artista);
        }
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

void search_disco_ano(int ano, lista_discos *this){
  if(this->head != NULL){
    disco *scout = this->head;
    int coincidencias = 0 , i = 1;
    while (0==0) {
      if(scout->ano == ano){
        printf("\n%d",i);
        print_disco(scout);
        coincidencias++;
      }
      if(scout->sig == NULL){
        if (coincidencias == 0) {
          printf("No se encontraron coincidencias para: %d\n",ano);
        }
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

void search_disco_precio(int precio, lista_discos *this){
  if(this->head != NULL){
    disco *scout = this->head;
    int coincidencias = 0 , i = 1;
    while (0==0) {
      if(scout->precio == precio){
        printf("\n%d",i);
        print_disco(scout);
        coincidencias++;
      }
      if(scout->sig == NULL){
        if (coincidencias == 0) {
          printf("No se encontraron coincidencias para: %d\n",precio);
        }
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

void exportar_inventario(lista_discos *this){
  FILE *Inventario = fopen("discos.txt","w");
  if(Inventario == NULL){
    printf("Error al crear archivo\n");
    return;
  }
  if(this->head != NULL){
    disco *scout = this->head;
    int i = 1;
    while (0==0) {
      if(scout->state > 0){
        fprintf(Inventario, "%s\n", disco_toFile(scout));
      }
      if(scout->sig == NULL){
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
  fclose(Inventario);
}

lista_discos *Importar_Inventario(){

  lista_discos *this = lista_discos_builder();
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("discos.txt", "r");
  if (fp == NULL)
      return NULL;

  while ((read = getline(&line, &len, fp)) != -1) {
      size_t state,index=0;
      int precio;
      int ano;
      char **tokens;
      tokens = str_split(line, '|');
      add_disco(this,disco_builder(tokens[0],tokens[1],atoi(tokens[3]),atoi(tokens[2]),atoi(tokens[4])));

  }

  fclose(fp);
  if (line)
      free(line);
  return this;
}

disco *get_disco(lista_discos *this, int index){
  if(this->size <= index|| index <1 ){
    return NULL;
  }
  else{
    if(this->head != NULL){
      disco *scout = this->head;
      int i = 1;
      while (0==0) {
        if(scout->state > 0){
        if(index == i)
          return scout;
        }
        if(scout->sig == NULL){
          return NULL;
        }
        scout = scout->sig;
        i++;
      }
    }
  }
  return NULL;
}

void modify_disco(disco *this, lista_discos *ld){
  if (this == NULL) return;
  size_t i = 0;
  int ano, precio;
  char nombre[50];
  char artista[20];
  print_disco(this);
  printf("%s\n", "Que deseas modificar? 1)Nombre, 2)Artista, 3)precio, 4)ano, 5)cantidad ");
  scanf("%zu",&i );
  switch (i) {
    case 1:
      printf("%s\n", "Introduzca el nuevo nombre:");
      scanf("%s", nombre);
      strcpy(this->nombre, nombre);
    break;

    case 2:
      printf("%s\n", "Introduzca el nuevo artista:");
      scanf("%s", artista);
      strcpy(this->artista, artista);
    break;

    case 3:
      printf("%s\n", "Introduzca el nuevo precio:");
      scanf("%d", &precio);
      this->precio = precio;
    break;

    case 4:
    printf("%s\n", "Introduzca el nuevo ano:");
    scanf("%d", &ano);
    this->ano = ano;
    break;

    case 5:
    printf("%s\n", "Introduzca la cantidad de discos:");
    scanf("%d", &ano);
    this->state = ano;
    break;

    default: printf("%s\n", "Opcion equivocada"); break;
  }
  exportar_inventario(ld);
  print_disco(this);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


struct lista_usuarios_{
  usuario *head,*tail;
  size_t size;
};

typedef struct lista_usuarios_ lista_usuarios;

usuario *search_usuario_username(char *username, lista_usuarios *this);


lista_usuarios *lista_usuarios_builder(){
  lista_usuarios *this = (lista_usuarios*)malloc(sizeof(lista_usuarios));
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
  return this;
}

void add_usuario(lista_usuarios *this, usuario *cd){
  if(NULL != search_usuario_username(cd->username,this)){
    printf("El usuario ya existe\n" );
    free(cd);
    return;
   }
  if(this->tail == NULL){
    this->head = cd;
    this->tail = cd;
  }else{
    this->tail->sig = cd;
    this->tail = cd;
  }
  (this->size)++;
}

void print_lista_usuarios(lista_usuarios *this){
  if(this->head != NULL){
    usuario *scout = this->head;
    int i = 1;
    while (0==0) {
      if(scout->state > 0){
        printf("\nid %d\n",i);
        print_usuario(scout);
      }
      if(scout->sig == NULL){
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
}

usuario *search_usuario_username(char *username, lista_usuarios *this){
  if(this->head != NULL){
    usuario *scout = this->head;
    while (0==0) {
      if(strcmp(scout->username,username)==0){
        return scout;
      }
      if(scout->sig == NULL){
          return NULL;
      }
      scout = scout->sig;
    }
  }
  return NULL;
}

void exportar_usuarios(lista_usuarios *this){
  FILE *Inventario = fopen("usuarios.txt","w");
  if(Inventario == NULL){
    printf("Error al crear archivo\n");
    return;
  }
  if(this->head != NULL){
    usuario *scout = this->head;
    int i = 1;
    while (0==0) {
      if(scout->state > 0){
        fprintf(Inventario, "%s", usuario_toFile(scout));
      }
      if(scout->sig == NULL){
        return;
      }
      scout = scout->sig;
      i++;
    }
  }
  fclose(Inventario);
}

lista_usuarios *Importar_Usuarios(){

  lista_usuarios *this = lista_usuarios_builder();
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("usuarios.txt", "r");
  if (fp == NULL)
      return NULL;

  while ((read = getline(&line, &len, fp)) != -1) {
      size_t state,index=0;
      int precio;
      int ano;
      char **tokens;
      tokens = str_split(line, '|');
      add_usuario(this,usuario_builder(tokens[0],tokens[3],atoi(tokens[1]),atoi(tokens[2])));
  }

  fclose(fp);
  if (line)
      free(line);
  return this;
}

void remove_user(usuario *paquito, lista_usuarios *this){
  if(this->head == paquito){
    printf("%s\n", "No puedes eliminar al administrador");
  }
  else{
    paquito->state = 0;
  }
  exportar_usuarios(this);
}

void modify_usuario(usuario *this, lista_usuarios *lu){
  if (this == NULL){
    printf("%s\n", "Intentalo de nuevo");
    return;
  }
  size_t i = 0;
  char password[50];
  char username[20];
  print_usuario(this);
  printf("%s\n", "Que deseas modificar? 1)username, 2)contrasena 3)borrar cuenta: ");
  scanf("%zu",&i );
  switch (i) {
    case 1:
      printf("%s\n", "Introduzca el nuevo nombre:");
      scanf("%s", username);
      strcpy(this->username, username);
    break;

    case 2:
      printf("%s\n", "Introduzca el nuevo password:");
      scanf("%s", password);
      strcpy(this->contrasena, password);
      strcat(this->contrasena,"\n");
    break;
    case 3:
      remove_user(this,lu);
    break;
    default:
      printf("%s\n", "Valor equívoco");
    break;
  }
  exportar_usuarios(lu);
}
/*---------------------------------------------------------------------------*/
void print_file(){
  FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("discos.txt", "r");
    if (fp == NULL){
        return;
      }

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("\n%c", line[0]);
    }

    fclose(fp);
    if (line)
        free(line);
    return;

}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
