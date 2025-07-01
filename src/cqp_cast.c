#include "cqp_cast.h"

/* Sample: CQP Cast
 * Difficulty: Easy */

#include <libcqp/cqp.h> /* cqp_cast_point and cqp_cast_ray */
#include <stdio.h> /* printf, scanf and perror */
#include <string.h> /* strncpy */
#include <sys/socket.h> /* socket and connect*/
#include <sys/un.h> /* sockaddr_un */
#include <stdlib.h> /* getenv */

/* 'Cast Point' Request 
 *
 * The ‘cast point’ request consists of 3 floating-point integers: the X, Y
 * and Z location of the point to be cast, in that order. */
struct point_cast_req
{
	float x;
	float y;
	float z;
}; 

/* 'Cast Ray' Request
 *
 * The ‘cast ray’ request consists of 2 sets of floating-point X-Y-Z
 * coordinates: the origin of the ray, followed by its vector. */
struct ray_cast_req
{
	float x_loc;
	float y_loc;
	float z_loc;
	float x_dir;
	float y_dir;
	float z_dir;
};

/* This example only needs to store one request of uncertain type. To save
 * unused space, the structs of both requests are unified. */
union cast_data
{
	struct point_cast_req point;
	struct ray_cast_req ray;
};

int cqp_cast()
{
	/* Igni trigger socket */

	/* Socket descriptor */
	int fd;

	/* Address */
	struct sockaddr_un sv_addr;

	/* Path to socket */
	const char* domain;

	/* ------------------- */

	/* CQP request code */
	int cast_mode;

	/* CQP request data */
	union cast_data cast;

	printf("Running sample: CQP Cast\n");

	/* The environment variable 'IGNI_TRIGGER' should point to a broadcast
	 * socket such as one made by udscast. */
	domain = getenv("IGNI_TRIGGER");
	if (!domain)
	{
		printf("Error: environment variable IGNI_TRIGGER is unset.\n");
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
	 * the socket of path IGNI_TRIGGER. */
	sv_addr.sun_family = AF_UNIX;
	strncpy(sv_addr.sun_path, domain, sizeof(sv_addr.sun_path));

	/* The client may now connect to the server. */
	if (connect(fd, (struct sockaddr*)&sv_addr, sizeof(sv_addr)) == -1)
	{
		perror("Failed to connect to server");
		return -1;
	}

	/* User is to specify the type of hitbox trigger to cast. */
	printf("Select cast mode:\n");
	printf("0: Cast Point\n");
	printf("1: Cast Ray\n");

	scanf("%i", &cast_mode);

	switch (cast_mode)
	{
	case 0:
		/* Prompt user for further trigger details */
		printf("Enter point X.\n");
		scanf("%f", &cast.point.x);
		printf("Enter point Y.\n");
		scanf("%f", &cast.point.y);
		printf("Enter point Z.\n");
		scanf("%f", &cast.point.z);

		printf("Casting point.");

		/* Send a request to cast a point. */
		cqp_cast_point(
			fd,
			cast.point.x,
			cast.point.y,
			cast.point.z
		);
		

		break;

	case 1:
		/* Prompt user for further trigger details */
		printf("Enter ray X location.\n");
		scanf("%f", &cast.ray.x_loc);
		printf("Enter ray Y location.\n");
		scanf("%f", &cast.ray.y_loc);
		printf("Enter ray Z location.\n");
		scanf("%f", &cast.ray.z_loc);
		
		printf("Enter ray X angle.\n");
		scanf("%f", &cast.ray.x_dir);
		printf("Enter ray Y angle.\n");
		scanf("%f", &cast.ray.y_dir);
		printf("Enter ray Z angle.\n");
		scanf("%f", &cast.ray.z_dir);

		printf("Casting ray.");

		/* Send a request to cast a ray. */
		cqp_cast_ray(
			fd,
			cast.ray.x_loc,
			cast.ray.y_loc,
			cast.ray.z_loc,
			cast.ray.x_dir,
			cast.ray.y_dir,
			cast.ray.z_dir
		);
		
		break;

	default:
		break;
	}

	return 0;
}

