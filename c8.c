#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
int main(int argc, char *argv[])
{
 //Definir variables,estructuras
 struct sockaddr_in server;
 char ip[16];
 int fd, numbytes,puerto;
 char buf[1024];
 char enviar[1024];
 
 system("clear");
 
printf("ingrese la ip del servidor\n");
 scanf("%s",ip);
 
printf("ingrese el puerto de conexion\n");
 scanf("%d",&puerto);
 
 //Socket
 if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
 printf("socket() error\n");
 exit(-1);
 }
 
 //Datos del servidor
 server.sin_family = AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr.s_addr=inet_addr(ip);
 bzero(&(server.sin_zero),8);
 
//Conectarse al servidor
 if(connect(fd, (struct sockaddr *)&server,
 sizeof(struct sockaddr))==-1){
 printf("connect() error\n");
 exit(-1);
 }
 //Recibir mensaje de bienvenida
 if ((numbytes=recv(fd,buf,1024,0)) == -1){
 printf("Error en recv() \n");
 exit(-1);
 }
 printf("%s\n",buf);
//Ciclo para enviar y recibir mensajes
while(1){
 //El servidor espera el primer mensaje
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar);
 send(fd,enviar,1024,0);
 if(strcmp(enviar,"salir")==0){
 break;
 }
 
 //El cliente recibe el mensaje del servidor
 recv(fd,buf,1024,0);
 if(strcmp(buf,"salir")==0){
 break;
 }
 printf("Servidor: %s\n",buf);
}
 close(fd);
}
