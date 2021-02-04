#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

using namespace std;
int forClientSockfd = 0;

void* recvdata(void*){
  while(1){
    char inputBuffer[255] = {};
    recv(forClientSockfd, inputBuffer, sizeof(inputBuffer),0);
    cout<< inputBuffer << "\n";
  }
}

int main(int argc, char *argv[]){
  pthread_t t1;
  char message[255] = {"Hi, I'm server."};
  int sockfd = 0;//, forClientSockfd =0;
  sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == -1){
      cout<< "Fail to create a socket\n";
    }
  int flag =1;
  struct sockaddr_in serverInfo,clientInfo;
  unsigned int addrlen = sizeof(clientInfo);
  memset(&clientInfo, 0, sizeof(serverInfo));

  serverInfo.sin_family = PF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(55146);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
  bind(sockfd,(struct sockaddr *)&serverInfo, sizeof(serverInfo));
  listen(sockfd,5);
  forClientSockfd = accept(sockfd,(struct sockaddr *)&clientInfo,&addrlen);

  pthread_create(&t1,NULL,recvdata,NULL);

  while(1){
    char inputBuffer[255] = {};
    send(forClientSockfd,message,sizeof(message),0);
    //recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
    //cout<< inputBuffer <<"\n";
    memset(message,0,sizeof(message));
    cin>>message;
  }
  return 0;
}
