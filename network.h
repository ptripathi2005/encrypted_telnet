#ifndef __MT_H
#define __MT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <signal.h>

#define PORT 1111
#define MAX_MSG_LENGTH 1024
#define PROMPT_STRING "$>"
#define END_STRING "bye\n"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

#define errorString(x) {fprintf(stderr, "%s:%d: %s: %s\n", __FILE__, __LINE__, x, strerror(errno));exit(1);}
#define DEBUG_MSG(...) fprintf(new_stream, __VA_ARGS__)

#endif
