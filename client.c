#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 5001 /*port*/
#include <unistd.h>

int
main(int argc, char **argv)
{
 int sockfd;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE], recvline[MAXLINE];
 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=3) {
  perror("Usage: TCPClient <IP address of the server");
  exit(1);
 }
if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT);
char *a;
if (strcmp(argv[2],"1")==0){
	a="data1.txt";	
}
else if(strcmp(argv[2],"2")==0){
	a="data2.txt";
}
else{
a="data3.txt";
}
if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }
FILE * fp;
char ab[1024];    
char * st = NULL;
    size_t len = 0;
ssize_t read;
fp = fopen(a, "r");	

while ((read = getline(&st, &len, fp)) != -1 ) {
//memset(sendline, 0, sizeof sendline);
//memset(recvline, 0, sizeof sendline);
//printf("%s",st);
strcpy(sendline,st);
printf("Unsorted string: %s",sendline);


send(sockfd, sendline, strlen(sendline), 0);

if( recv(sockfd, recvline ,4096, 0) < 0)
	{
		puts("recv failed");
	}

   
   
   
  
  printf("%s\n\n", "Sorted String from server: ");
int i;
int y=0;
char ot[50];
printf("%s\n\n",recvline);		
sleep(4);

}
fclose(fp);
if (st)
        free(st);
    exit(EXIT_SUCCESS);

}
