#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>

void comms(int new_socket){

	char buffer[30000] = {0};
	long valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	if(valread < 0){
		printf("No bytes are there to read");
	}
	
	char *hello = "Hello from the Knight";
	write(new_socket, hello, strlen(hello));
};

int main(){

struct sockaddr_in address;
const int PORT = 8080;

int server_fd, new_socket;
int addrlen = sizeof(address);

if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
{
	perror("Could not create a Scoket");

}

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

memset( address.sin_zero, '\0', sizeof(address.sin_zero));


if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
{
		perror("Bind failed");
}
	
if(listen(server_fd, 3) <0)
{
	perror("In Listen");
	exit(EXIT_FAILURE);
}
	
	
while(1){
	printf("\n Waiting here for new conns\n");

	if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){

		perror("In accept");
		exit(EXIT_FAILURE);
	}
	comms(new_socket);
	close(new_socket);
}
return 0;
}
