// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 7000

int main(int argc, char const *argv[]) 
{ 
  int s = 0, valread; 
  struct sockaddr_in ad;
  
  int mickey = 0;
  while (1)
  {

  s = socket(AF_INET, SOCK_STREAM, 0);

  ad.sin_family = AF_INET; 
  ad.sin_port = htons(PORT); 
	
  // Convert IPv4 and IPv6 addresses from text to binary form 
  inet_pton(AF_INET, "127.0.0.1", &ad.sin_addr);

  

    connect(s, (struct sockaddr *) &ad, sizeof(ad));
    
    send(s, &mickey, sizeof(int), 0 );
    usleep(100000);

    printf("%d sent\n", mickey); 
    read( s , &mickey, sizeof(int));
    
    printf("%d\n", mickey );
    usleep(100000);
  }
  return 0; 
} 
