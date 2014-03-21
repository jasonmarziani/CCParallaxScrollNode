///
///  CCParallaxScrollOffset.cpp
///  ParallaxScrollNodeTest
///
///  Created by Jason Marziani on 3/26/12.
///  Copyright (c) 2012 Little Wins LLC. All rights reserved.
///
///  Modification for Cocos2d-x 3.0 by Oscar Kurniawan @oscarkm

#include "CCParallaxScrollOffset.h"


using namespace cocos2d;

// on "init" you need to initialize your instance
bool ParallaxScrollOffset::init()
{
    if ( !Layer::init() ) return false;
    
    this->setRelVelocity(Point(0,0));
    this->setScrollOffset(Point(0,0));
    this->setPosition(Point(0,0));
    this->setRatio(Point(0,0));
    return true;
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(Node *node, Point r, Point p, Point s){
    ParallaxScrollOffset *offset = (ParallaxScrollOffset*) ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s);
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(Node *node, Point r, Point p, Point s, Point v){
    ParallaxScrollOffset *offset = (ParallaxScrollOffset*) ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s,v);
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(Node *node, Point r, Point p, Point s, Point v){
    if(!this) return false;
    this->setRatio(r);
    this->setScrollOffset(s);
    this->setRelVelocity(v);
    this->setOrigPosition(p);
    node->setPosition(p);
    node->setAnchorPoint(Point(0, 0));
    this->setTheChild(node);
    return this;
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(Node *node, Point r, Point p, Point s){
    return this->initWithNode(node, r, p, p, Point(0,0));
}