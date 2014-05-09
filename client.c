/**
 * ****************************************************************************
 * * @File: client.c
 * * @Brief: This file contains the telnet client code.
 * * @Revision History:
 * * 	     OCT-11-2013; Prashant Tripathi; Initial file commit
 * ****************************************************************************
 * */

#include "network.h"
#include "encrypt.h"

void send_cmd(int sock, int pid) {
	char str[MAX_MSG_LENGTH] = {0};
	printf(PROMPT_STRING);
	while (fgets(str, MAX_MSG_LENGTH, stdin) == str) {
		if(strncmp(str, END_STRING, strlen(END_STRING)) == 0) break;
		sym_encrypt(str, true);
		if(send(sock, str, strlen(str)+1, 0) < 0)
			errorString("send");
	}
	kill(pid, SIGKILL);
	printf("Goodbye.\n");
}

void receive(int sock) {
	char buf[MAX_MSG_LENGTH] = {0};
	int filled = 0;	
	while((filled = recv(sock, buf, MAX_MSG_LENGTH-1, 0))) {
		buf[filled] = '\0';
		printf("%s", buf);
		fflush(stdout);		
	}	
	printf("Server disconnected.\n");
}

int main(int argc, char **argv) {
	if(argc != 2)
		errorString("args");

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		errorString("socket");

	struct in_addr server_addr;
	if(!inet_aton(argv[1], &server_addr))
		errorString("inet_aton");

	struct sockaddr_in connection;
	connection.sin_family = AF_INET;
	memcpy(&connection.sin_addr, &server_addr, sizeof(server_addr));
	connection.sin_port = htons(PORT);
	if (connect(sock, (const struct sockaddr*) &connection, sizeof(connection)) != 0)
		errorString("connect");
	
	int pid;	
	if((pid = fork())) send_cmd(sock, pid);
	else receive(sock);
	
	return 0;
}
