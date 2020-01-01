

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

struct Message{
  int pid;
  char  string[30];
};

int main(int argc, char const *argv[]) { 
  if (argc < 2)  {
    printf("Pas assez d'arguments!\n");
    return 1;
  }

  struct Message message;
  int message_len = sizeof(message) ;

  
  int port = atoi(argv[1]);
  int s;
  struct sockaddr_in ad, ad_emet;  
  int addrlen = sizeof(ad); 
  
  s = socket(AF_INET, SOCK_DGRAM, 0);    
  ad.sin_family = AF_INET; 
  ad.sin_addr.s_addr = INADDR_ANY; 
  ad.sin_port = htons( port ); 


  int taille_ad_emet = sizeof(ad_emet);
  
  int res = bind(s,
		 (struct sockaddr *) &ad,
		 sizeof(ad));
  if (res ==-1)
  {
    printf("Erreur de bind\n");
    return 1;
  }

  while (1)
  {
    recvfrom(s,
	     &message, message_len,
	     0,
	     (struct sockaddr *) &ad_emet, &taille_ad_emet
	     );
    printf("server received {%d '%s'}\n", message.pid, message.string);
  
    usleep(100000);

    message.pid = getpid();
  
    sendto(s,
	   &message, sizeof( message ),
	   0,
	   (struct sockaddr *) &ad_emet, sizeof( ad_emet ));
    
    printf("{%d '%s'} sent\n", message.pid, message.string);
    usleep(100000);
  }
  return 0;
}
