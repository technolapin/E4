all:
	bat Makefile
connected: clean server_connected client_connected

nonconnected: clean server_nonconnected client_nonconnected


clean:
	- rm client server


client_connected:
	gcc client_connected.c -o client
server_connected:
	gcc serveur_connected.c -o server

client_nonconnected:
	gcc client_nonconnected.c -o client
server_nonconnected:
	gcc serveur_nonconnected.c -o server

