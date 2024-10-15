#include "hitbox.h"
#include <stdlib.h>
#include <libigni/hit.h>
#include <libigni/render.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	/* Server info. */
	int hitboxes;
	int render;

	/* Scene element IDs */
	const int ball = 1;
	const int lPad = 2;
	const int rPad = 3;
	const int ballTex = 1;
	const int padTex = 2;
	const int ballBox = 1;
	const int lPadBox = 2;
	const int rPadBox = 3;

	IgniAffineTransform3D lPadTf = {0};
	IgniAffineTransform3D rPadTf = {0};
	IgniAffineTransform3D lPadBoxTf = {0};
	IgniAffineTransform3D rPadBoxTf = {0};
	IgniAffineTransform3D ballTf = {0};
	IgniXYZ ballVel = {0};

	/* Connect to hitbox server */
	hitboxes = igniConnect(getenv("IGNI_HIT_SRV"));
	if (hitboxes == -1) {
		printf("Failed to connect to Igni Hit server\n");
		exit(EXIT_FAILURE);
	}

	render = igniConnect(getenv("IGNI_RENDER_SRV"));
	if (render == -1) {
		printf("Failed to connect to Igni Render server\n");
		exit(EXIT_FAILURE);
	}

	/* Configure connections */
	igniRndConfigure(render, IGNI_RENDER_VERSION);
	igniHitConfigure(hitboxes, IGNI_HIT_VERSION);

	/* Add assets to scene */
	igniRndMeshCreate(render, ball, "ball.obj");
	igniRndMeshCreate(render, lPad, "paddle.obj");
	igniRndMeshCreate(render, rPad, "paddle.obj");
	igniRndTextureCreate(render, ballTex, "tennisball.png");
	igniRndTextureCreate(render, padTex, "paddle.png");
	igniHitHitboxCreate(hitboxes, ballBox);
	igniHitHitboxCreate(hitboxes, lPadBox);
	igniHitHitboxCreate(hitboxes, rPadBox);

	/* Put assets into places */
	lPadTf.scale.x = 1.0f;
	lPadTf.scale.y = 1.0f;
	lPadTf.scale.z = 1.0f;
	lPadTf.location.y = -1.25f;
	lPadTf.rotation.x = 0.5f * 3.14159;
	igniRndMeshTransform(render, lPad, lPadTf);

	rPadTf.scale.x = 1.0f;
	rPadTf.scale.y = 1.0f;
	rPadTf.scale.z = 1.0f;
	rPadTf.location.y = 1.25f;
	rPadTf.rotation.x = 0.5f * 3.14159;
	igniRndMeshTransform(render, rPad, rPadTf);

	lPadBoxTf.scale.x = 0.4f;
	lPadBoxTf.scale.y = 0.1;
	lPadBoxTf.scale.z = 1.5f;
	lPadBoxTf.location.y = -1.25f;
	lPadBoxTf.rotation.x = 0.5f * 3.14159;
	igniHitHitboxTransform(hitboxes, lPadBox, lPadBoxTf);

	lPadBoxTf.scale.x = 0.4f;
	lPadBoxTf.scale.y = 0.1;
	lPadBoxTf.scale.z = 1.5f;
	rPadBoxTf.location.y = 1.25f;
	rPadBoxTf.rotation.x = 0.5f * 3.14159;
	igniHitHitboxTransform(hitboxes, lPadBox, rPadBoxTf);

	/* Texture meshes */
	igniRndMeshBindTexture(
		render,
		ball,
		ballTex,
		IGNI_RENDER_TEXTURE_TARGET_DIFFUSE
	);
	
	igniRndMeshBindTexture(
		render,
		lPad,
		padTex,
		IGNI_RENDER_TEXTURE_TARGET_DIFFUSE
	);
	
	igniRndMeshBindTexture(
		render,
		rPad,
		padTex,
		IGNI_RENDER_TEXTURE_TARGET_DIFFUSE
	);

	/* Main loop */


	ballVel.y = -0.01f;

	while (1) {
		while (igniHitEventGet(hitboxes)) {
		}

		if (abs(ballTf.location.y) > 0.5f) {
			ballVel.y = -ballVel.y;
		}

		/* Transform tennis ball */
		ballTf.rotation.x += 0.1f;
		ballTf.rotation.y += 0.1f;
		ballTf.rotation.z += 0.1f;
		ballTf.location.x += ballVel.x;
		ballTf.location.y += ballVel.y;
		ballTf.location.z += ballVel.z;
		ballTf.scale.x = 2.0f;
		ballTf.scale.y = 2.0f;
		ballTf.scale.z = 2.0f;
		igniRndMeshTransform(render, ball, ballTf);

		usleep(16666);
	}

	/* Quit */
	close(render);
	close(hitboxes);
	return 0;
}

