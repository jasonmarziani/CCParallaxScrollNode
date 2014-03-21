///
///  ParallaxScrollNode.h
///  ParallaxScrollNodeTest
///
///  Created by Jason Marziani on 3/26/12.
///  Copyright (c) 2012 Little Wins LLC. All rights reserved.
///
///  Modification for Cocos2d-x 3.0 by Oscar Kurniawan @oscarkm

#include "CCParallaxScrollNode.h"

using namespace cocos2d;
using namespace std;

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif

#ifndef SIGN
#define SIGN(x) ((x < 0) ? -1 : (x > 0))
#endif

ParallaxScrollNode::ParallaxScrollNode() : _scrollOffsets(100)
{
}

bool ParallaxScrollNode::init()
{
	if ( !Layer::init() ) return false;
    
    
    Size screen = Director::getInstance()->getWinSize();
    _range = Size::Size(screen.width, screen.height);
    this->setAnchorPoint(Point(0,0));
    
	log("size: %i", _scrollOffsets.size());

    return true;
}

// Used with box2d style velocity (m/s where m = 32 pixels), but box2d is not required
void ParallaxScrollNode::updateWithVelocity(Point vel, float dt)
{
	vel = vel * PTM_RATIO;
	//log("count: %i", _scrollOffsets.size());
    //Object *obj;
    for(auto obj: this->_scrollOffsets)
    {
        ParallaxScrollOffset *scrollOffset = (ParallaxScrollOffset*) obj;
		Point relVel = scrollOffset->getRelVelocity() * PTM_RATIO;
		Point totalVel = vel + relVel;
		Point offset = ccpCompMult(totalVel * dt, scrollOffset->getRatio());
        
        Node *child = scrollOffset->getTheChild();
		child->setPosition(child->getPosition() + offset);
		
		if ( (offset.x < 0 && child->getPosition().x + child->getContentSize().width < 0) ||
            (offset.x > 0 && child->getPosition().x > _range.width) ) {
			child->setPosition(child->getPosition() + Point(-SIGN(offset.x) * fabs(scrollOffset->getScrollOffset().x), 0));
		}
		
		// Positive y indicates upward movement in cocos2d
		if ( (offset.y < 0 && child->getPosition().y + child->getContentSize().height < 0) ||
			(offset.y > 0 && child->getPosition().y > _range.height) ) {
			child->setPosition((child->getPosition() + Point(0, -SIGN(offset.y) * fabs(scrollOffset->getScrollOffset().y))));
		}
	}
}


void ParallaxScrollNode::updateWithYPosition(float y, float dt)
{	
	for(auto obj: this->_scrollOffsets)
    {
        ParallaxScrollOffset *scrollOffset = (ParallaxScrollOffset*) obj;
		Node *child = scrollOffset->getTheChild();
		float offset = y * scrollOffset->getRatio().y;
		child->setPosition(Point(child->getPosition().x, scrollOffset->getOrigPosition().y + offset));
	}
}


void ParallaxScrollNode::addChild(Sprite *node, int z, Point r, Point p, Point so, Point v)
{
	node->setAnchorPoint(Point(0,0));
    
	ParallaxScrollOffset *obj = ParallaxScrollOffset::scrollWithNode(node, r, p, so, v);
	//->addObject(obj);
	this->_scrollOffsets.pushBack(obj);
	this->cocos2d::Node::addChild(node, z);
}

void ParallaxScrollNode::addChild(Sprite *node, int z, Point r, Point p, Point so){
	this->addChild(node,z,r,p,so,Point(0,0));
}

void ParallaxScrollNode::removeChild(Sprite *node, bool cleanup)
{
    //Array *dealloc = new Array;
    //dealloc->autorelease();
	Vector<ParallaxScrollOffset*> dealloc;
	int i,idx;
	i = idx = 0;
    
	for(auto obj: this->_scrollOffsets)
    {
        ParallaxScrollOffset *scrollOffset = (ParallaxScrollOffset*) obj;
		if( scrollOffset->getTheChild() == node){
			//dealloc->addObject(scrollOffset);
			dealloc.pushBack(scrollOffset);
			break;
		}
		i++;
	}

	for (auto _dealloc : dealloc)
	{
		_scrollOffsets.eraseObject(_dealloc, true);
	}
    //_scrollOffsets.erase(_scrollOffsets.begin()+idx);
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(Vector<Sprite*> objects, int z, Point ratio, Point pos, Point dir, Point relVel, Point padding)
{
	// NOTE: corrects for 1 pixel at end of each sprite to avoid thin lines appearing
	
	// Calculate total width and height
	float totalWidth = 0;
	float totalHeight = 0;
    
	for(auto obj: objects)
    {
        Sprite *object = (Sprite*) obj;
		totalWidth += object->getContentSize().width + dir.x * padding.x;
		totalHeight += object->getContentSize().height + dir.y * padding.y;
	}
    
	// Position objects, add to parallax
	Point currPos = pos;
    for(auto obj: objects)
    {
        Sprite *object = (Sprite*) obj;
		this->addChild(object, z, ratio, currPos, Point(totalWidth, totalHeight), relVel);
		Point nextPosOffset = Point(dir.x * (object->getContentSize().width + padding.x), dir.y * (object->getContentSize().height + padding.y));
		currPos = (currPos + nextPosOffset);
	}
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(Vector<Sprite*> objects, int z, Point ratio, Point pos, Point dir, Point relVel)
{
	this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, relVel, Point(-1,-1));
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(Vector<Sprite*> objects, int z, Point ratio, Point pos, Point dir)
{
	this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, Point(0,0));
}

void ParallaxScrollNode::addInfiniteScrollXWithZ(int z, Point ratio, Point pos, Sprite* firstObject, ...){
	va_list args;
    va_start(args, firstObject);
	
	//Array *argArray = new Array;
	Vector<Sprite*> arguArray;
	for (Sprite *arg = firstObject; arg != NULL; arg = va_arg(args, Sprite*)) {
		//argArray->addObject(arg);
		arguArray.pushBack(arg);
	}
	va_end(args);
	
	this->addInfiniteScrollWithObjects(arguArray, z, ratio, pos, Point(1,0));
}

void ParallaxScrollNode::addInfiniteScrollYWithZ(int z, Point ratio, Point pos, Sprite* firstObject, ...){
	va_list args;
    va_start(args, firstObject);
	
	//Array *argArray = new Array;
	Vector<Sprite*> arguArray;
	for (Sprite *arg = firstObject; arg != NULL; arg = va_arg(args, Sprite*)) {
		//argArray->addObject(arg);
		arguArray.pushBack(arg);
	}
	va_end(args);
	
	this->addInfiniteScrollWithObjects(arguArray, z, ratio, pos, Point(0,1));
}
