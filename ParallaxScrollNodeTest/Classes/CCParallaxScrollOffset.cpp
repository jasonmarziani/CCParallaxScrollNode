//
//  CCParallaxScrollOffset.cpp
//  ParallaxScrollNodeTest
//
//  Created by Jason Marziani on 3/26/12.
//  Copyright (c) 2012 Little Wins LLC. All rights reserved.
//

#include "CCParallaxScrollOffset.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool CCParallaxScrollOffset::init()
{
	if ( !CCLayer::init() ) return false;
    
    this->setRelVelocity(ccp(0,0));
    this->setScrollOffset(ccp(0,0));
    this->setPosition(ccp(0,0));
    this->setRatio(ccp(0,0));
    return true;
}

CCParallaxScrollOffset* CCParallaxScrollOffset::scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s){
    CCParallaxScrollOffset *offset = CCParallaxScrollOffset::create();
	return (CCParallaxScrollOffset*)offset->initWithNode(node,r,p,s);
}

CCParallaxScrollOffset* CCParallaxScrollOffset::scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v){
    CCParallaxScrollOffset *offset = CCParallaxScrollOffset::create();
	return (CCParallaxScrollOffset*)offset->initWithNode(node,r,p,s,v);
}

CCParallaxScrollOffset* CCParallaxScrollOffset::initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v){
    if(!this) return false;
    this->setRatio(r);
    this->setScrollOffset(s);
    this->setRelVelocity(v);
    this->setOrigPosition(p);
    node->setPosition(p);
    node->setAnchorPoint(ccp(0, 0));
    this->setTheChild(node);
	return this;
}

CCParallaxScrollOffset* CCParallaxScrollOffset::initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s){
	return this->initWithNode(node, r, p, p, ccp(0,0));
}
