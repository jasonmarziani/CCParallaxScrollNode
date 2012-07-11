#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxScrollNode.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	LAYER_CREATE_FUNC(HelloWorld);
    
    CCParallaxScrollNode *parallax;
    
    void update(float dt);
    float randomValueBetween(float low, float high);
};

#endif // __HELLOWORLD_SCENE_H__
