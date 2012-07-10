//
//  ParallaxScrollNode.cpp
//  ParallaxScrollNodeTest
//
//  Created by Jason Marziani on 3/26/12.
//  Copyright (c) 2012 Little Wins LLC. All rights reserved.
//

#include "CCParallaxScrollNode.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif

#ifndef SIGN
#define SIGN(x) ((x < 0) ? -1 : (x > 0))
#endif

bool CCParallaxScrollNode::init()
{
	if ( !CCLayer::init() ) return false;
    
    _scrollOffsets = CCArray::create();
    _scrollOffsets->retain();
    CCSize screen = CCDirector::sharedDirector()->getWinSize();
    _range = CCSizeMake(screen.width, screen.height);
    this->setAnchorPoint(ccp(0,0));
    
    return true;
}

CCParallaxScrollNode::~CCParallaxScrollNode()
{
    if (_scrollOffsets) {
        _scrollOffsets->release();
    }
}

// Used with box2d style velocity (m/s where m = 32 pixels), but box2d is not required
void CCParallaxScrollNode::updateWithVelocity(CCPoint vel, float dt)
{
	vel = ccpMult(vel, PTM_RATIO);
//	CCLog("count: %i", _scrollOffsets->count());
    CCObject* object;
    CCARRAY_FOREACH(_scrollOffsets, object)
    {
        CCParallaxScrollOffset* scrollOffset = dynamic_cast<CCParallaxScrollOffset*>(object); 
		CCPoint relVel = ccpMult(scrollOffset->getRelVelocity(), PTM_RATIO);
		CCPoint totalVel = ccpAdd(vel, relVel);
		CCPoint offset = ccpCompMult(ccpMult(totalVel, dt), scrollOffset->getRatio());
        
        CCNode *child = scrollOffset->getTheChild();
		child->setPosition(ccpAdd(child->getPosition(), offset));
		
		if ( (offset.x < 0 && child->getPosition().x + child->getContentSize().width < 0) ||
            (offset.x > 0 && child->getPosition().x > _range.width) ) {
			child->setPosition(ccpAdd(child->getPosition(), ccp(-SIGN(offset.x) * fabs(scrollOffset->getScrollOffset().x), 0)));
		}
		
		// Positive y indicates upward movement in cocos2d
		if ( (offset.y < 0 && child->getPosition().y + child->getContentSize().height < 0) ||
			(offset.y > 0 && child->getPosition().y > _range.height) ) {
			child->setPosition(ccpAdd(child->getPosition(), ccp(0, -SIGN(offset.y) * fabs(scrollOffset->getScrollOffset().y))));
		}
	}
}


void CCParallaxScrollNode::updateWithYPosition(float y, float dt)
{	
    
    CCObject* object;
    CCARRAY_FOREACH(_scrollOffsets, object)
    {
        CCParallaxScrollOffset* scrollOffset = dynamic_cast<CCParallaxScrollOffset*>(object); 
		CCNode *child = scrollOffset->getTheChild();
		float offset = y * scrollOffset->getRatio().y;
		child->setPosition(ccp(child->getPosition().x, scrollOffset->getOrigPosition().y + offset));
	}
}


void CCParallaxScrollNode::addChild(CCSprite *node, int z, CCPoint r, CCPoint p, CCPoint so, CCPoint v)
{
	node->setAnchorPoint(ccp(0,0));
    
	CCParallaxScrollOffset *obj = CCParallaxScrollOffset::scrollWithNode(node, r, p, so, v);
	_scrollOffsets->addObject(obj);
    this->cocos2d::CCNode::addChild(node, z);
}

void CCParallaxScrollNode::addChild(CCSprite *node, int z, CCPoint r, CCPoint p, CCPoint so){
	this->addChild(node,z,r,p,so,ccp(0,0));
}

void CCParallaxScrollNode::removeChild(CCSprite *node, bool cleanup)
{
    CCArray *dealloc = new CCArray();
    dealloc->autorelease();
    
    
    CCObject* object;
    CCARRAY_FOREACH(_scrollOffsets, object)
    {
        CCParallaxScrollOffset* scrollOffset = dynamic_cast<CCParallaxScrollOffset*>(object); 
		if( scrollOffset->getTheChild() == node){
			dealloc->addObject(scrollOffset);
			break;
		}
	}
    _scrollOffsets->removeObjectsInArray(dealloc);
}

void CCParallaxScrollNode::addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir, CCPoint relVel, CCPoint padding)
{
	// NOTE: corrects for 1 pixel at end of each sprite to avoid thin lines appearing
	
	// Calculate total width and height
	float totalWidth = 0;
	float totalHeight = 0;
    
    
    CCObject* object;
    CCARRAY_FOREACH(objects, object)
    {
        CCSprite* sprite = dynamic_cast<CCSprite*>(object);
		totalWidth += sprite->getContentSize().width + dir.x * padding.x;
		totalHeight += sprite->getContentSize().height + dir.y * padding.y;
	}
    
	// Position objects, add to parallax
	CCPoint currPos = pos;
    CCARRAY_FOREACH(objects, object)
    {
        CCSprite* sprite = dynamic_cast<CCSprite*>(object);
		this->addChild(sprite, z, ratio, currPos, ccp(totalWidth, totalHeight), relVel);
		CCPoint nextPosOffset = ccp(dir.x * (sprite->getContentSize().width + padding.x), dir.y * (sprite->getContentSize().height + padding.y));
		currPos = ccpAdd(currPos, nextPosOffset);
	}
}

void CCParallaxScrollNode::addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir, CCPoint relVel)
{
	this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, relVel, ccp(-1,-1));
}

void CCParallaxScrollNode::addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir)
{
	this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, ccp(0,0));
}

void CCParallaxScrollNode::addInfiniteScrollXWithZ(int z, CCPoint ratio, CCPoint pos, CCSprite* firstObject, ...){
	va_list args;
    va_start(args, firstObject);
	
	CCArray* argArray = new CCArray();
	for (CCSprite *arg = firstObject; arg != NULL; arg = va_arg(args, CCSprite*)) {
		argArray->addObject(arg);
	}
	va_end(args);
	
	this->addInfiniteScrollWithObjects(argArray, z, ratio, pos, ccp(1,0));
}
