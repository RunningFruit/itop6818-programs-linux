#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 56789

int main(int argc, char const *argv[])
{

	int sock;
	char buf[128];
	int client_fd;
	int size;
	char* close_led = "closeled";
	char* open_led = "openled";
	char* open_curtain = "opencurtain";
	char* close_curtain = "closecurtain";
	struct sockaddr_in server_addr,client_addr;

	sock = socket(AF_INET,SOCK_STREM,0);

	if(socket == -1){
		printf("error create socket!\n");
		return -1;
	}

	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sock,10);
	client_fd = accept(sock,(struct sockaddr*)&client_addr,&size);

	while(1){
		memset(buf,0,sizeof(buf));
		read(client_fd,buf,sizeof(buf));
		printf("buf is %s\n",buf );
		if(strcmp(buf,open_led) == 0){
			printf("open_led\n");
			system("./zigbee 1 FE 05 91 90 E7 AE 01 FF");
		}
		if(strcmp(buf,close_led) == 0){
			printf("close_led\n");
			system("./zigbee 1 FE 05 91 90 E7 AE 02 FF");
		}
		if(strcmp(buf,open_curtain) == 0){
			printf("open_curtain\n");
			system("./zigbee 1 FE 05 91 90 E7 AE 03 FF");
		}
		if(strcmp(buf,close_curtain) == 0){
			printf("close_curtain\n");
			system("./zigbee 1 FE 05 91 90 E7 AE 04 FF");
		}

	}

	close(client_fd);
	close(sock);
	return 0;
}