#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
void *recvs(void *);
void *sends(void *);
int main(int argc, char *argv[]){
      int port;
     if( argc == 2 ) {
       port =  atoi(argv[1]);
     }
     else port = 5000;
     int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     struct sockaddr_in serv_addr;
     memset(&serv_addr, 0, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     serv_addr.sin_port = htons(port);
     bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
     listen(serv_sock, 20);

     struct sockaddr_in clnt_addr;
     socklen_t clnt_addr_size = sizeof(clnt_addr);
     int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
     pthread_t t1, t2;
     pthread_create(&t1, NULL, recvs, &clnt_sock);
     pthread_create(&t2, NULL, sends, &clnt_sock);
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);   
     //sends(clnt_sock);
     //recvs(clnt_sock);
     close(clnt_sock);
     close(serv_sock);
     return 0;
}
void *recvs(void *sock)
{
     int *soc = (int *)sock;
     char buffer[1024] = {0};
     while(1){
        memset(buffer, 0, 1024);
        read((*soc), buffer, sizeof(buffer)-1);
	printf("%s", buffer);
     }
}
void *sends(void *clnt_sock)
{
     int *soc = (int *)clnt_sock;
        char str[1024]  = {0};
     while(1){
        memset(str, 0, 1024);
	fgets(str, 1024, stdin);
	str[strlen(str) - 1] = 0;
	fflush(stdin);
        write((*soc), str, sizeof(str));
     }
}
