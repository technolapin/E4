
int
main()
{
  int soc, res;
  soc = socket(AF_INET, SOCK_DGRAM, 0);
  if (soc!=0){...}

  struct sockaddr_in MyAddr;
  MyAddr.sin_familly = AF_INET;
  MyAddr.sin_port = 6500;
  MyAddr.sin_addr.s_addr = IN_ADDR_ANY; // permet de bind la socket à toutes les addresses ip de la machines (si elle en a plusieures)

  res = bind(soc, (struct sockaddr*) &MyAddr, sizeof(MyAddr));

  //////////////////////////////

  int temp;
  temp = 50;

  sendto(soc, &temp, sizeof(int), 0, (struct sockaddr*) &addr_dest, sizeof(addr_dest));
  // l'autre machine fera recvfrom(soc, &temp, sizeof(int), 0, (struct sokaddr*) &addr_emet, sizeof(addr_emet));


  
}

  
