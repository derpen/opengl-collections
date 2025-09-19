#pragma once


class OmniDirectionalShadowMapping {
public:
	unsigned int depthMapFBO;
	unsigned int depthCubemap;

	OmniDirectionalShadowMapping(const unsigned int SHADOW_WIDTH = 1024, const unsigned int SHADOW_HEIGHT = 1024);

	void UpdateCubemap();
	//void 

};
