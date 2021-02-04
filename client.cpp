#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

using namespace std;
int sockfd = 0;
void* recvdata(void*){
  while(1){
    char recvmsg[255] = {};
    if(recv(sockfd, recvmsg, sizeof(recvmsg), 0) <= 0) pthread_exit(NULL);
    cout<< recvmsg << "9999\n";

  }


}

int main(int arc, char *argv[]){
  pthread_t t1;
  //int sockfd = 0;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd == -1){
    cout << "Fail to create a socket\n";
  }

  struct sockaddr_in info;
  memset(&info, 0, sizeof(info));

  info.sin_family = PF_INET;
  info.sin_addr.s_addr = inet_addr("127.0.0.1");
  info.sin_port = htons(55146);

  int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
  if(err == -1){
    cout<< "Connection error\n";
  }

  pthread_create(&t1,NULL,recvdata,NULL);

  char message[255] = {"Hi"};
  char recvmessage[100] = {};
  while(message != "end"){
    //char recvmsg[255] = {};
    cout << "fff\n";
    if(send(sockfd, message, sizeof(message), 0) < 0) break;
    //recv(sockfd, recvmsg, sizeof(recvmsg), 0);

    //cout << recvmsg << "\n";
    memset(message,0,sizeof(message));
    cin>>message;
  }
  cout << "close Socket\n";
  close(sockfd);

  return 0;
}
