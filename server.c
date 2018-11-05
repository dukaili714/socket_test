#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_PORT 8000
int main()
{
	int lfd;//listen fd
	int cfd;
	struct sockaddr_in serv_addr,client_addr;
	socklen_t client_len;
	
	char buf[1024];
	int len;

	//AF_INET:ipv4  SOCKET_STREAM:stream protocol  0:tcp
	lfd=socket(AF_INET,SOCK_STREAM,0);
	if(lfd<0)
	{
		return -1;
	}
	serv_addr.sin_family=AF_INET;//ipv4
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(SERV_PORT);//host to 
	//IP+SERV_PORT 
	bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	listen(lfd,128);

	client_len=sizeof(client_addr);
	cfd=accept(lfd,(struct sockaddr *)&client_addr,&client_len);
	
	len=read(cfd,buf,sizeof(buf));

	//
	write(STDOUT_FILENO,buf,len);
	
	close(cfd);
	close(lfd);
	return 0;
}

