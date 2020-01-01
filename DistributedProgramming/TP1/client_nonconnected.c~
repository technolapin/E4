// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

struct Message
{
  int pid;
  char string[30];
};

int main(int argc, char *argv[]) 
{

  if (argc < 4)
  {
    printf("Pas assez d'arguments!\n");
    return 1;
  }

  int s = 0, valread; 
  struct sockaddr_in ad;

  int port = atoi(argv[2]);
  char* url = argv[1];
  struct hostent * ip_struct;

  ip_struct = gethostbyname(url);
  printf("aaa\n");
  struct in_addr ip = *(struct in_addr *)(ip_struct->h_addr);
  printf("url: %s\nip: %s\n", url, inet_ntoa( ip));

  s = socket(AF_INET, SOCK_STREAM, 0);

  ad.sin_family = AF_INET;
  ad.sin_port = htons(port); 
  ad.sin_addr = ip;



  
  

  connect(s, (struct sockaddr *) &ad, sizeof(ad));
    




  


  int pid = getpid();
  struct Message message;
  message.pid = pid;
  strcpy(message.string, argv[3]);
  int message_len = sizeof(message);


  send(s, &message, message_len, 0 );
  usleep(100000);

  printf("{%d '%s'} sent\n", message.pid, message.string); 

  read( s , &message, message_len);
    
  printf("{%d '%s'}\n", message.pid, message.string );
  usleep(100000);
  return 0; 
} 
