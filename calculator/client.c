#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc,char*argv[])
{
	int d=0,i=0;
	int c=1;
	int soc,addrlen,msgsock;
	char buf4[1024];
	char ans[1024];
	char buf2[1024],buf3[1024],buf[1024];
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
//	while(1){
		printf("Enter the numbers :");
		scanf("%[^\n] %[^\n]",buf,buf2);
		printf("Enter operator :\n1)Add \n2)Sub \n3)Mul \n4)Div\n");
		scanf(" %[^\n]",buf3);
		write(soc,buf,1024);
		write(soc,buf2,1024);
		write(soc,buf3,1024);
		printf("Message from server :");
		read(soc,buf4,1024);
		while(buf4[i]-'0'>=0)
		{
			//printf("%c\n",buf4[i]);
			d=(buf4[i]-'0')*c+d;
			i++;
			c=c*10;
		}	
		printf("\nOutput=%d\n",d);
//	}
	close(soc);
	return 0;
}

