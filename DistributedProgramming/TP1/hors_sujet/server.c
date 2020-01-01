

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 



#define PORT 7000
int main(int argc, char const *argv[]) 
{ 
  int s, s2, mickey;
  struct sockaddr_in ad;
    
    int addrlen = sizeof(ad); 
       
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("HAA ÇA MARCHE PAS");
        exit(EXIT_FAILURE); 
    } 

    /*
    if (setsockopt(server_fd,
		   SOL_SOCKET,
		   0,
		   &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }
    */
    
    ad.sin_family = AF_INET; 
    ad.sin_addr.s_addr = INADDR_ANY; 
    ad.sin_port = htons( PORT ); 
       
    bind(s,
	 (struct sockaddr *) &ad,
	 sizeof(ad));
    
    listen(s, 3);

   
    while (1)
    {
      s2 = accept(s,
		  (struct sockaddr *) &ad,  
		  (socklen_t*)&addrlen);
    
      read( s2 , &mickey, sizeof(int));
      printf("server recieved %d\n", mickey);
      mickey++;
      usleep(100000);
      send(s2, &mickey, sizeof(mickey), 0 );
      printf("%d sent\n", mickey);
      usleep(100000);
    }
    return 0;
}
