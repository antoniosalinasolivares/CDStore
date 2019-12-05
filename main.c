#include "listas.h"

disco *seleccionar_disco(lista_discos *this);
usuario *login(lista_usuarios *this);
usuario *seleccionar_usuario(lista_usuarios *this);
usuario *new_account();
void comprar(usuario *u, disco *d);


int main() {
  lista_usuarios *userbase = Importar_Usuarios();
  lista_discos *Inventario = Importar_Inventario();
  size_t i;
  usuario *curr = NULL;
  disco *cd = NULL;
  while (1) {
    printf("%s\n", "Bienvenido a moxop");
    printf("%s\n", "Que deseas hacer?");
    printf("%s\n", "1)login");
    printf("%s\n", "2)registrarte");
    printf("%s\n", "3)Salir");

    scanf("%zu",&i);
    if(i == 1)
      curr = login(userbase);
    else if(i==2)
      curr = new_account(userbase);
    else if(i ==3)
      break;
    else
      printf("%s\n", "Opcion incorrecta");
    while (curr != NULL) {
      if(curr == userbase->head){
        printf("%s\n", "Que deseas hacer?");
        printf("%s\n", "1)Enlistar discos");
        printf("%s\n", "2)Enlistar usuarios");
        printf("%s\n", "3)modificar disco");
        printf("%s\n", "4)modificar usuario");
        printf("%s\n", "5)Agregar disco");
        printf("%s\n", "6)Cerrar sesion");
        scanf("%zu",&i );
        int precio, ano, state;
        char artista[20], nombre[50];
        switch (i) {
          case 1:
            print_lista_discos(Inventario);
          break;
          case 2:
            print_lista_usuarios(userbase);
          break;
          case 3:
            modify_disco(seleccionar_disco(Inventario),Inventario);
          break;
          case 4:
            modify_usuario(seleccionar_usuario(userbase),userbase);
          break;
          case 5:
            printf("%s\n", "Introduce el nombre:");
            scanf("%s", nombre);
            printf("%s\n", "Introduce el artista:");
            scanf("%s", artista);
            printf("%s\n", "Introduce el ano:");
            scanf("%d", &ano);
            printf("%s\n", "Introduce el precio:");
            scanf("%d", &precio);
            printf("%s\n", "Introduce cuantos hay en inventario:");
            scanf("%d", &state);
            add_disco(Inventario,disco_builder(nombre,artista,precio,ano,state));
            print_disco(Inventario->tail);
          break;
          case 6:
            curr = NULL;
            i = (int)NULL;
          break;
          default:
            printf("%s\n", "Valor no valido");
          break;
        }
      }
      else{

            printf("%s\n", "Que deseas hacer?");
            printf("%s\n", "1)Enlistar discos");
            printf("%s\n", "2)Comprar");
            printf("%s\n", "3)modificar usuario");
            printf("%s\n", "4)Cerrar sesion");
            printf("%s\n", "5)Ver perfil");

            scanf("%zu",&i );
            switch (i) {
              case 1:
                print_lista_discos(Inventario);
              break;
              case 2:
                printf("%s\n", "Selecciona el disco:");
                cd = seleccionar_disco(Inventario);
                if (cd != NULL){
                  comprar(curr, cd);
                }
                else{
                  printf("%s\n", "ALgo no salió bien, intentalo de nuevo");
                }
              break;
              case 3:
                modify_usuario(curr,userbase);
              break;
              case 4:
                curr = NULL;
                i = (int)NULL;
              break;
              case 5:
                print_usuario(curr);
              break;
              default:
                printf("%s\n", "Valor no valido");
              break;
            }
       }
    }
  }


  exportar_usuarios(userbase);
  exportar_inventario(Inventario);
  return 0;
}

usuario *login(lista_usuarios *this){
  usuario *usr;
  for (size_t i = 0; i < 3; i++){
    char usuario[20], contrasena[50];
    printf("%s\n","Introduce el usuario:");
    scanf("%s",usuario);
    printf("%s\n","Introduce tu contrasena:");
    scanf("%s",contrasena);
    printf("%s:%s\n",usuario,contrasena);

    usr = search_usuario_username(usuario,this);

    if(usr != NULL){
      if(strcmp(usr->contrasena,contrasena)==0){
        print_usuario(usr);
        printf("%s\n", "Bienvenido: ");
        return usr;
      }
      else{
        printf("%s\n", usr->contrasena);
        printf("%s\n", contrasena);
        printf("%d\n", strcmp(usr->contrasena, contrasena));
        printf("%s\n", "Contrasena equivocada");
      }
    }
    else{
      printf("%s\n", "Datos incorrectos, intentelo de nuevo");
    }
  }
  return NULL;
}

usuario *new_account(lista_usuarios *this){
  usuario *new = NULL;
  while (new == NULL){
    char usuario[20], contrasena[50];
    printf("%s\n","Introduce el usuario:");
    scanf("%s",usuario);
    printf("%s\n","Introduce tu contrasena:");
    scanf("%s",contrasena);
    printf("%s:%s\n",usuario,contrasena);

    if(search_usuario_username(usuario,this) != NULL){
      printf("%s\n", "Ese nombre de usuario ya existe, intente con otro.");
    }
    else{
      printf("%s\n", "Bienvenido");
      new = usuario_builder(usuario, contrasena,0,0);
      add_usuario(this,new);
      exportar_usuarios(this);
      print_usuario(new);
      break;
    }
  }
  return new;
}

void comprar(usuario *u, disco *d){
  if(d == NULL){
    printf("%s\n", "Algo salió mal, intentalo de nuevo.");
    return;
  }
  printf("%s\n", "Compraste:");
  print_disco(d);
  (u->compras)++;
  (u->total)+=(d->precio);
  (d->state)--;
}

usuario *seleccionar_usuario(lista_usuarios *this){
  usuario *tmp;
  char usuario[20];
  printf("%s\n", "Introduce el username");
  scanf("%s",usuario);
  tmp = search_usuario_username(usuario, this);
  if(tmp == NULL || tmp->state < 1){
    printf("%s\n", "El usuario no existe");
    return NULL;
  }
  return tmp;
}

disco *seleccionar_disco(lista_discos *this){
  printf("%s\n", "¿Que disco?");
  int elec, tmp;
  char cmp[50];
  disco *aux = NULL;
  while (aux == NULL){
    printf("%s\n", "Cómo quieres buscar el disco?");
    printf("%s\n", "1)Nombre");
    printf("%s\n", "2)Artista");
    printf("%s\n", "3)Ano");
    printf("%s\n", "4)precio");
    printf("%s\n", "5)seleccionar disco");

    scanf("%d", &elec);
    switch (elec) {
      case 1:
        printf("%s\n", "Ingresa el nombre que quieres buscar:");
        scanf("%s",cmp);
        search_disco_nombre(cmp,this);
      break;

      case 2:
        printf("%s\n", "Ingresa el artista que quieres buscar:");
        scanf("%s",cmp);
        search_disco_artista(cmp,this);
      break;

      case 3:
        printf("%s\n", "Ingresa el ano que quieres buscar:");
        scanf("%d",&tmp);
        search_disco_ano(tmp,this);
      break;
      case 4:
        printf("%s\n", "Ingresa el precio que quieres buscar:");
        scanf("%d",&tmp);
        search_disco_precio(tmp,this);
      break;
      case 5:
        printf("%s\n", "Introduce el id del disco:");
        scanf("%d",&tmp);
        aux = get_disco(this,tmp);
      break;
      default:
        printf("%s\n", "Eleccion equivoca");
        return NULL;
      break;
    }
  }
  return aux;
}
