#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>



int main(){

const int PORT = 8080;
long valread;
int sock = 0;
struct sockaddr_in serv_addr;

char *hello = "Hello from Knight's client";
char buffer[1024] = {0};


if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
{
	perror("Could not create a Scoket");
	return -1;

}


memset(&serv_addr, '0', sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <=0)
{
	printf("\n Perhaps worth checking the server address\n");
}

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr) ) < 0)
{
	printf("Connection Failed");
	return -1;
}

send(sock, hello, strlen(hello), 0);
printf("Hello to Knight\n");

valread = read(sock, buffer, 1024); //only reading 1024 bytes here

printf("%s\n", buffer);


return 0;
}
