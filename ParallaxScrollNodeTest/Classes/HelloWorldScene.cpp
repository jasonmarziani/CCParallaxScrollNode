#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	CCScene *scene = CCScene::create();
	HelloWorld *layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}


bool HelloWorld::init()
{
	if (!CCLayer::init())return false;

    parallax = CCParallaxScrollNode::create();
    CCSize screen = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *land1 = CCSprite::create("land_green.png");
    CCSprite *land2 = CCSprite::create("land_green.png");
    parallax->addInfiniteScrollXWithZ(0, ccp(0.5,0.2), ccp(0,0), land1, land2, NULL);
    
    CCSprite *land3 = CCSprite::create("land_grey.png");
    CCSprite *land4 = CCSprite::create("land_grey.png");
    parallax->addInfiniteScrollXWithZ(-2,ccp(0.05,0.1),ccp(0,60),land3, land4, NULL);
    
    CCSprite *clouds1 = CCSprite::create("clouds.png");
    CCSprite *clouds2 = CCSprite::create("clouds.png");
    parallax->addInfiniteScrollXWithZ(1,ccp(0.1,0.1),ccp(0, screen.height - clouds1->getContentSize().height), clouds1, clouds2, NULL);
    
    for (int i = 0; i < 10; i++) {
        CCSprite *mountain = CCSprite::create("mountain_grey.png");
        CCPoint pos = ccp(this->randomValueBetween(0, land1->getContentSize().width * 2), this->randomValueBetween(screen.height*0.1f,screen.height*0.25f));
        
        float speedMountainX = this->randomValueBetween(0.15f,0.25f);
        parallax->addChild(mountain,-1,ccp(speedMountainX,.015f),pos,ccp(land1->getContentSize().width * 2, 0));
        
        mountain->setScale(this->randomValueBetween(0.6f, 1));
    }
    
    CCSprite *sky = CCSprite::create("sky_evening.png");
    sky->setAnchorPoint(ccp(0,0));
    this->addChild(parallax);
    this->addChild(sky, -1);
    this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	parallax->updateWithVelocity(ccp(-0.5, 0), dt);
}

 float HelloWorld::randomValueBetween(float low, float high)
{
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}
