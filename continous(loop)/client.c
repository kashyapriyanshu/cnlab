#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(int argc,char*argv[])
{
	int soc,addrlen,msgsock;
	char buf[1024],buf1[1024];
	struct sockaddr_in server;
	soc=socket(AF_INET,SOCK_STREAM,0);
	if(soc<0)
	{
		perror("\nError in opening socket ...");
		exit(1);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	if(connect(soc,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("\nError in connection ...");
		exit(2);
	}
	addrlen=sizeof(server);
	while(1){
		bzero(buf,1024);
		scanf(" %[^\n]",buf);
		write(soc,buf,1024);
		printf("Message from server :");
		read(soc,buf1,1024);
		printf("\n%s\n",buf1);
	}
	close(soc);
	return 0;
}

