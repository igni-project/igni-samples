#include "model_load.h"
#include <libigni/render.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	/* 1. Connect to the render engine's socket */
	int scene = igniConnect(getenv("IGNI_RENDER_SRV"));

	if (scene == -1)
	{
		printf("Failed to connect to Igni Render server\n");
		return -1;
	}

	/* 2. Load mesh */
	igniRndMeshCreate(scene, 44, "./mesh.obj");

	/* 3. Load texture */
	igniRndTextureCreate(scene, 23, "./texture.png");

	/* 4. Bind texture to mesh */
	igniRndMeshBindTexture(scene, 44, 23, IGNI_RENDER_TEXTURE_TARGET_DIFFUSE);

	/* Halt for 10 seconds */
	sleep(10);

	/* Quit */
	close(scene);
	return 0;
}

