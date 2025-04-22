#include "load-model.h"

#include <libsup/sup.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd;
	struct sockaddr_un svAddr;
	const char* domain = getenv("IGNI_DISPLAY");

	if (!domain)
	{
		printf("Error: environment variable IGNI_DISPLAY is unset.\n");
		return -1;
	}

	svAddr.sun_family = AF_UNIX;
	strncpy(svAddr.sun_path, domain, sizeof(svAddr.sun_path));

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("Failed to create socket");
		return -1;
	}

	if (connect(fd, (struct sockaddr*)&svAddr, sizeof(svAddr)) == -1)
	{
		perror("Failed to connect to server");
		return -1;
	}

	sup_asset_load(fd, 3, "/usr/share/igni-samples/mesh.obj");

	return 0;
}


