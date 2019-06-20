#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
//#include "unp.h"
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 5001 /*port*/
void merge(char array[22][15],int first1,int first2,int last1,int last2){
int i;
int j;
int k;
char **newArray;
newArray=(char **)malloc((last2-first1+1)*sizeof(char *));
for(i=0;i<last2-first1+1;i++){
    newArray[i]=(char *)malloc(15*sizeof(char));
}
j=first2; 
i=first1; 
k=0;
while(i<=last1 && j<=last2){

    if(strcmp(array[i],array[j])>0){ 
        strcpy(newArray[k++], array[j++]);
    }
    else{
        strcpy(newArray[k++], array[i++]);
    }
}

while(i<=last1){            
    strcpy(newArray[k++], array[i++]);
}

while(j<=last2){
    strcpy(newArray[k++], array[j++]);
}

for(i=first1,j=0;j<k;i++,j++){
    strcpy(array[i], newArray[j]);
}
}
void mergeSort(char array[22][15],int first,int last){ 
int middle;
if(first<last){
    middle=(first+last)/2;
    mergeSort(array,first,middle);
    mergeSort(array,middle+1,last);
    merge(array,first,middle+1,middle,last); 
}
}

void sig_child(int signo){//this is the method to clear the zombie process.
pid_t pid;
int stat;
while((pid=waitpid(-1,&stat,WNOHANG))>0)
	printf("Child %d terminated\n",pid);
return;
}

int main (int argc, char **argv)
{
 int listenfd, connfd, n;
 pid_t childpid;
 socklen_t clilen;
 char buf[MAXLINE];
buf[0]='\n'; 
struct sockaddr_in cliaddr, servaddr;
//Create a socket for the soclet
 
 if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);

//bind the socket
 bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen (listenfd,4);
//printf("%s\n","Server running...waiting for connections.");
int u=0,read_size;

for ( ; ; ) {
	u++;
  clilen = sizeof(cliaddr);
  //accept a connection
  connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
printf("%s\n","Received request...");
 if ( (childpid = fork ()) == 0 ) {//if it’s 0, it’s child process

  printf ("%s%d\n","Child created for dealing with client requests ",u);
//close listening socket
  close (listenfd);
struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&cliaddr;
struct in_addr ipAddr = pV4Addr->sin_addr;
char str[INET_ADDRSTRLEN];
inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );	
while( (read_size = recv(connfd , buf , 4096 , 0)) > 0 )
	{

//printf("\n");	
int i;
char ar[1024];    

int h = 0;
    char *p = strtok (buf, " ");
    char array[22][15];
     
    while (p != NULL)
    {
	strcpy(array[h],p);	
	
	p = strtok (NULL, " ");
	h++;    
}
//printf("%d",h);  
//for (i = 0; i < h; i++) 
	        
	//printf("%s\n", array[i]);
  //}
	
mergeSort(array,0,h-1);
///ar[0]='\0';

for(i=0;i<h;i++){
		int j;
	//printf("%s",array[i]);
//if( (array[i][0]>='a' && array[i][0]<='z') || (array[i][0]>='A' && array[i][0]<='Z'))	
		
	for(j=0;array[i][j]!='\0';j++)
     {
     if(array[i][j]=='\n')
         {
          array[i][j]=' ';
         }
      }		
		
		strcat(ar,array[i]);	    
		strcat(ar," ");
	

}   
//printf("%s",ar); 

char* buffer = (char*)(&ar);  
//printf("%s","hariiii k cha");
//printf("%s",ar);
//printf("%ld\n",sizeof(ar));
memset(buf, 0, sizeof buf);


send(connfd, buffer, sizeof(ar), 0);
memset(ar, 0, sizeof ar);

	}
if( recv(connfd, buf ,4096, 0) < 0)
	{
		puts("recv failed");
	}
  

  if (n < 0)
   printf("%s\n", "Read error");
  exit(0);
 }
 //close socket of the server
 close(connfd);

}

}
