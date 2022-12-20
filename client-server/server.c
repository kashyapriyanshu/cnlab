#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1

int main()
{
	int soc,len;
	char buf[1024];
	struct sockaddr_in server,client;
	int msgsock,addrlen=sizeof(client);
	soc=socket(AF_INET,SOCK_STREAM,0);
	if(soc<0)
	{
		perror("\nError in opening socket...");
		exit(1);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htons(INADDR_ANY);
	server.sin_port=0;

	if(bind(soc,(struct sockaddr*)&server,sizeof(server)))
	{
		perror("\nError in bind...");
		exit(2);
	}

	len=sizeof(server);
	if(getsockname(soc,(struct sockaddr*)&server,&len))
	{
		perror("\nError in getting port");
		exit(3);
	}

	printf("\nSocket has port #%hd \n",ntohs(server.sin_port));
	listen(soc,5);

	do
	{
		msgsock=accept(soc,(struct sockaddr*)&client,&addrlen);
		if(msgsock==-1)
		{
			perror("\nError in accept...");
			exit(0);
		}
		else
		{
			read(msgsock,buf,1024);
			printf("\nMessage from client :: \n %s\n",buf);
		}
	}
	while(TRUE);
	close(msgsock);
	close(soc);
	return 0;
}
