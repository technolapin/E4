

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

  int port = atoi(argv[1]);
  int s, s2;
  struct sockaddr_in ad,ad_emet;  
  int addrlen = sizeof(ad); 
  
  s = socket(AF_INET, SOCK_STREAM, 0);    
  ad.sin_family = AF_INET; 
  ad.sin_addr.s_addr = INADDR_ANY; 
  ad.sin_port = htons( port ); 

  int res = bind(s,
		 (struct sockaddr *) &ad,
		 sizeof(ad));
  if (res ==-1)
  {
    printf("Erreur de bind\n");
    return 1;
  }
  listen(s, 3);
  s2 = accept(s,
	      (struct sockaddr *) &ad_emet,  
	      (socklen_t*) &addrlen);

  struct Message message;
  int message_len = sizeof(message) ;

  printf("ABDEFAVAZA\n");
  read( s2 , &message, message_len);
  printf("ABDEFAVAZA\n");

  printf("server received {%d '%s'}\n", message.pid, message.string);
  
  printf("%d lolilol\n", message_len);
  usleep(100000);

  message.pid = getpid();
  
  send(s2, &message, message_len, 0 );

  printf("{%d '%s'} sent\n", message.pid, message.string);
  usleep(100000);
  return 0;
}
