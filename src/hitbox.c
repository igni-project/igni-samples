#include "hitbox.h"

#include <libcqp/cqp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

/* Sample: Hitbox
 * Difficulty: Easy to Medium, depending on complexity of collisions */
int hitbox()
{
	char box_hit;
	uint8_t cqp_cast;
	float cqp_float_param;

	/* Igni trigger socket */

	/* Socket descriptor */
	int fd;

	/* Address */
	struct sockaddr_un sv_addr;

	/* Path to socket */
	const char* domain;

	/* ------------------- */

	printf("Running sample: Hitbox\n");

	domain = getenv("IGNI_TRIGGER");
	if (!domain)
	{
		printf("Error: environment variable IGNI_TRIGGER is unset.\n");
		return -1;
	}

	/* Create a socket for the client. */
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("Failed to create socket");
		return -1;
	}

	sv_addr.sun_family = AF_UNIX;
	strncpy(sv_addr.sun_path, domain, sizeof(sv_addr.sun_path));

	if (connect(fd, (struct sockaddr*)&sv_addr, sizeof(sv_addr)) == -1)
	{
		perror("Failed to connect to server");
		return -1;
	}

	while (1)
	{
		/* Wait until client recieves a CQP request */
		recv(fd, &cqp_cast, sizeof(cqp_cast), 0);

		/* As of right now, this sample only includes point collision
		 * detection. */
		if (cqp_cast != CQP_REQ_CODE_CAST_POINT)
		{
			printf("Unsupported cast type: %i\n", cqp_cast);
			return -1;
		}

		/* Hitbox has a location of 0 and a width, height and depth of 5 */

		box_hit = 1;
		
		/* Detect collisions on X axis */
		recv(fd, &cqp_float_param, sizeof(cqp_float_param), 0);
		if (cqp_float_param < -5 || cqp_float_param > 5)
		{
			box_hit = 0;
		}

		/* Detect collisions on Y axis */
		recv(fd, &cqp_float_param, sizeof(cqp_float_param), 0);
		if (cqp_float_param < -5 || cqp_float_param > 5)
		{
			box_hit = 0;
		}

		/* Detect collisions on Z axis */
		recv(fd, &cqp_float_param, sizeof(cqp_float_param), 0);
		if (cqp_float_param < -5 || cqp_float_param > 5)
		{
			box_hit = 0;
		}

		if (box_hit)
		{
			printf("Point hit.\n");
		}
		else
		{
			printf("Point miss.\n");
		}
	}

	return 0;
}

