#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
	int soc,addrlen;
	char buf[1024];
	struct sockaddr_in server;
	soc=socket(AF_INET,SOCK_STREAM,0);
	if(soc<0)
	{
		perror("\nError in opening socket...");
		exit(1);
	}

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	if(connect(soc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("\nError in connection...");
		exit(2);
	}
	addrlen=sizeof(server);
	scanf("%[^\n]",buf);
	write(soc,buf,1024);
	close(soc);
	return 0;
}
