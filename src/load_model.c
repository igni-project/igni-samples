#include "load_model.h"

/* Sample: Load Model
 * Difficulty: Easy */

#include <libsup/sup.h> /* sup_asset_load and sup_asset_show */
#include <stdio.h> /* printf and perror */
#include <string.h> /* strncpy */
#include <sys/socket.h> /* socket and connect*/
#include <sys/un.h> /* sockaddr_un */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* getenv */

/* SUP requires all meshes have a unique identification code. */
#define MESH_ID 3

int load_model()
{
	/* Igni display socket */

	/* Socket descriptor */
	int fd;

	/* Address */
	struct sockaddr_un sv_addr;

	/* Path to socket */
	const char* domain;

	/* ------------------- */

	printf("Running sample: Load Model\n");

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

	/* A sockaddr_un struct points to the socket to connect to. In this case,
	 * the socket of path IGNI_DISPLAY. */
	sv_addr.sun_family = AF_UNIX;
	strncpy(sv_addr.sun_path, domain, sizeof(sv_addr.sun_path));

	/* The client may now connect to the server. */
	if (connect(fd, (struct sockaddr*)&sv_addr, sizeof(sv_addr)) == -1)
	{
		perror("Failed to connect to server");
		return -1;
	}

	/* Import a mesh into the scene */
	sup_asset_load(fd, MESH_ID, "/usr/share/igni-samples/mesh.obj");

	/* Make the imported mesh visible to viewers */
	sup_asset_show(fd, MESH_ID);

	/* Halt for 60 seconds and quit */
	sleep(60);

	return 0;
}


