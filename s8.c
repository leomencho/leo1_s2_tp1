#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
//Funcion principal
int main(int argc, char **argv)
{
//Definir variables,estructuras
struct sockaddr_in server;
struct sockaddr_in client;
int fd,fd2,longitud_cliente,numbytes,puerto;
char buf[1024]; //Para recibir mensaje
char enviar2[1024]; //Para enviar mensaje
char enviar[1024]; //Para enviar mensaje
 
system("clear");
 printf("La direccion del servidor es 127.0.0.1\n\n");
 printf("Por favor introduzca el puerto de escucha: \n\n");
 scanf("%d",&puerto);
 
 server.sin_family= AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr.s_addr = INADDR_ANY;
 bzero(&(server.sin_zero),8);
 
 //Definicion de socket
 if (( fd=socket(AF_INET,SOCK_STREAM,0) )<0){
 perror("Error de apertura de socket");
 exit(-1);
 }
 
 //Avisar al sistema que se creo un socket
 if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
 printf("error en bind() \n");
 exit(-1);
 }
 
 //Establecer el socket en modo escucha
 if(listen(fd,5) == -1) {
 printf("error en listen()\n");
 exit(-1);
 }
 
 printf("SERVIDOR EN ESPERA...\n");
 longitud_cliente= sizeof(struct sockaddr_in);
 if ((fd2 = accept(fd,(struct sockaddr *)&client,&longitud_cliente))==-1) {
 printf("error en accept()\n");
 exit(-1);
 }
 
 printf("------SESION INICIADA------\n");
 printf("CLIENTE CONECTADO\n");
 strcpy(enviar,"SERVIDOR CONECTADO...");
 send(fd2, enviar, 1024,0);
 
//Ciclo para enviar y recibir mensajes
 while(1){
 //El servidor espera el primer mensaje
 recv(fd2,buf,1024,0);
 if(strcmp(&buf,"salir")==0){
 break;
 }
 printf("Cliente: %s\n",buf);
 
 //El cliente recibe el mensaje del servidor
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar2);
 send(fd2,enviar2,1024,0);
 if(strcmp(enviar2,"salir")==0){
 break;
 }
}
 close(fd2);
 close(fd);
return 0;
}
