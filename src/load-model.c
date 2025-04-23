#include "load-model.h"

#include <libsup/sup.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int load_model()
{
	int fd;
	struct sockaddr_un svAddr;
	const char* domain;
   
	/* An Igni display server shall use the environment variable
	 * 'IGNI_DISPLAY' to communicate the absolute path of its socket. */
	domain = getenv("IGNI_DISPLAY");
	if (!domain)
	{
		printf("Error: environment variable IGNI_DISPLAY is unset.\n");
		return -1;
	}

	/* Create a socket for ourselves, the client. */
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("Failed to create socket");
		return -1;
	}

	/**/
	svAddr.sun_family = AF_UNIX;
	strncpy(svAddr.sun_path, domain, sizeof(svAddr.sun_path));

	if (connect(fd, (struct sockaddr*)&svAddr, sizeof(svAddr)) == -1)
	{
		perror("Failed to connect to server");
		return -1;
	}

	/* Import a mesh into the scene */
	sup_asset_load(fd, 3, "/usr/share/igni-samples/mesh.obj");

	/* Make the imported mesh visible to viewers */
	sup_asset_show(fd, 3);

	/* Halt for 60 seconds and quit */
	sleep(60);
	return 0;
}


