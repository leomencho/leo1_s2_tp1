#include <stdio.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
#include <string.h>  
#include <stdlib.h>  
  
int main ()   
{  
  
/* Datos de conexion */  
char *host = "localhost";  
int port = 9998,salir=0;
  
/* Cadena a enviar */  
char *data = "Yisus por la red";  
  
/* Obtenemos el host */  
struct hostent *host_name;  
if ((host_name = gethostbyname(host))==0)   
{  
perror ("gethostbyname()");  
exit (EXIT_FAILURE);  
}  
  
/* Configura el socket */  
struct sockaddr_in pin;   
bzero (&pin, sizeof(pin));  
pin.sin_family =  AF_INET;  
pin.sin_addr.s_addr = htonl(INADDR_ANY);  
pin.sin_addr.s_addr = ((struct in_addr *)(host_name->h_addr))->s_addr;  
pin.sin_port = htons (port);  
  
  
/* Crea un socket TCP */  
int socket_descriptor = socket (AF_INET, SOCK_STREAM, 0);  
if (socket_descriptor == -1)   
{   
perror ("socket()");  
exit (EXIT_FAILURE);  
}  
  
  
/* Conecta con el servidor */  
if (connect(socket_descriptor, (void *)&pin, sizeof(pin))==-1)   
{  
perror ("connect()");  
exit (EXIT_FAILURE);  
}  
for(salir=0; salir<10;salir++)
{  
/* Envia los datos al servidor */  
if (send(socket_descriptor, data, strlen(data), 0) == -1)   
{  
perror ("send()");  
 //exit (EXIT_FAILURE);  
}  
  
/* Lee la respuesta */  
static char buffer [2048];  
if (recv(socket_descriptor, buffer, sizeof(buffer), 0) == -1) {  
  
perror ("recv()");  
 //exit (EXIT_FAILURE);  
}  
  
/* Datos recibidos */  
printf ("%s\n", buffer);
}
  
}  
