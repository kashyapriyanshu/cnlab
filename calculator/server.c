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
	int pid;
	int soc,len;
	char buf[1024],buf1[1024];
	char c1[1024],c2[1024],c3[1024],c4[1024];
	int d,f,s=0,rem,i=0;
	struct sockaddr_in server,client;
	int msgsock,addrlen=sizeof(client);
	soc=socket(AF_INET,SOCK_STREAM,0);
	if(soc < 0)
	{
		perror("\nError in opening socket....");
		exit(1);
	}
	server.sin_family=AF_INET;                
	server.sin_addr.s_addr=htons(INADDR_ANY);
	server.sin_port=0;

	if(bind(soc,(struct sockaddr*)&server,sizeof(server)))
	{
		perror("\nError in bind ...");
		exit(2);
	}
	len =sizeof(server);
	if(getsockname(soc,(struct sockaddr*)&server,&len))
	{
		perror("\n Error in getting port....");
		exit(3);
	}
	printf("\nSocket has port # %hd \n",ntohs(server.sin_port));
	listen(soc,5);
	msgsock=accept(soc,(struct sockaddr *)&client,&addrlen);
	if(msgsock==-1)
	{
		perror("\nError in accept ... ");
		exit(0);
	}
	//	while(1)
		//{
			bzero(buf,1024);
			read(msgsock,c1,1024);
			read(msgsock,c2,1024);
			read(msgsock,c3,1024);
			printf("\nMessage from client :: \n %s %s %s\n",c1,c2,c3);
			if(atoi(c3)==1)
			{
				d=atoi(c1);
				f=atoi(c2);
				s=d+f;
				//printf("%d\n",s);
			}
			else if(atoi(c3)==2)
			{
				d=atoi(c1);
				f=atoi(c2);
				s=d-f;
			}
			else if(atoi(c3)==3)
			{
				d=atoi(c1);
				f=atoi(c2);
				s=d*f;
			}
			else if(atoi(c3)==4)
			{
				d=atoi(c1);
				f=atoi(c2);
				s=d/f;
			}
			printf("%d\n",s);
			while(s>0)
			{
				rem=s%10;
				c4[i]=rem+'0';
				i++;
				s=s/10;
			}
			write(msgsock,c4,1024);
		
	//	}

		close(msgsock);
		close(soc);
	return 0;
}
