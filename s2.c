#include <sys/types.h> /*Incluímos las librerías*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#define TRUE 1  /*Definición de constantes*/


main () /*Programa Principal*/

{
    char buf_in[1024];  /*Definición de variables*/
    char buf_out[1024];
    int rval,caracter,caracter0;
    int i,contador;
    int sock,length;
    struct sockaddr_in server ;
    int msgsock;


    sock=socket(AF_INET,SOCK_STREAM,0); /*Creamos el socket*/
    if(sock<0){  /*Si el identificador de socket es negativo...*/
                /*Imprime por pantalla el error*/
      fprintf(stderr,"Abriendo un socket de tipo stream. n");

               exit(1);   /*y sale del programa*/

               }


    server.sin_family=AF_INET; /*Familia de protocolo AF_INET*/
    server.sin_addr.s_addr=inet_network("127.0.0.1");
/*Dirección del servidor*/
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(1999);  /*Nº de puerto*/
/*Asociamos socket a la dirección del servidor*/
    if(bind(sock,&server,sizeof(server)) ){
fprintf(stderr,"Nombrando al socket de tipo stream.n");

/*Si ha habido un error, se imprime en pantalla
     y sale del programa*/
        exit(1);
                  }

/*Función que averigua el nº de puerto que ha asignado el
sistema operativo, en el caso de que se le pida a éste que
asigne un puerto automáticamente*/

/*  length=sizeof(server);
    if(getsockname(sock,&server,&length)) {
         fprintf(stderr,"Obteniendo el puerto para el socket");
         exit(1);}*/


printf("El socket tiene el puerto %dn", ntohs(server.sin_port));



  /*Nos quedamos a la escucha con una cola para 5 clientes*/
listen(sock,5);

do { /*Repite el bucle infinítamente*/

   /*Aceptamos la petición de conexión del cliente*/
   msgsock=accept(sock,0,0);

/*Si ha habido un fallo en la aceptación de conexión...*/
   if(msgsock==-1)
     /*...imprime el error por pantalla*/
    fprintf(stderr,"Fallo en la función accept.n");

/*Si todo ha ido bien y mientras el cliente
    no cierre la conexión...*/
   else do


     bzero(buf_in,sizeof(buf_in)); /*Vacía el búfer de entrada*/
/*Lee datos del cliente y si obtiene un error...*/
     if((rval=read(msgsock,buf_in,1024))<0)
/*...lo imprime en pantalla*/
     perror("ERROR: Leyendo el mensaje.n");

     if(rval==0) /*Si lee un NULL (Desconexión) del cliente...*/
/*...imprime que finaliza la conexión*/
      printf("Finalizando la conexion.n");

     else /*Si no...*/
/*Imprime el mensaje que recibe del cliente*/
      printf("Mensaje: %sn",buf_in);

      contador=0; /*Inicializamos contador*/
/*Vaciamos el bufer de salida*/
      bzero(buf_out,sizeof(buf_out));

      for(contador=0;contador<strlen(buf_in);contador=contador+2)
      { /*Algoritmo de encriptación*/
        caracter0=buf_in[contador];
        caracter=buf_in[contador+1];
    /*Si la palabra es impar no cambia el último carácter*/
        if(caracter!=0){buf_out[contador]=caracter;}
else{buf_out[contador]=1;}
buf_out[contador+1]=caracter0;}

/*Envía respuesta al cliente*/
   if(write(msgsock,buf_out,strlen(buf_out))<0)
/*Si hay error lo muestra*/
    fprintf(stderr,"Fallo en la funcion Write.n");

    /*Mientras que el cliente no cierre la conexión*/
}while (rval !=0);

close(msgsock); /*Cierra el socket y la conexión con el cliente*/

}while(TRUE); /*Bucle infinito*/

}
