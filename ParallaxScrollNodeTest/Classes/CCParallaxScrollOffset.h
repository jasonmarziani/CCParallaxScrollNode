///
///  CCParallaxScrollOffset.h
///  ParallaxScrollNodeTest
///
///  Created by Jason Marziani on 3/26/12.
///  Copyright (c) 2012 Little Wins LLC. All rights reserved.
///
///  Modification for Cocos2d-x 3.0 by Oscar Kurniawan @oscarkm

#pragma once

#include "cocos2d.h"
using namespace cocos2d;


class ParallaxScrollOffset :
    public cocos2d::Layer
{
public:
    virtual bool init();  
    CREATE_FUNC(ParallaxScrollOffset);
    //

    CC_SYNTHESIZE(Point, scrollOffset, ScrollOffset);
    CC_SYNTHESIZE(Point, origPosition, OrigPosition);
    CC_SYNTHESIZE(Point, relVelocity, RelVelocity);
    CC_SYNTHESIZE(Point, ratio, Ratio);
    CC_SYNTHESIZE(Point, buffer, Buffer);
    CC_SYNTHESIZE(Node*, theChild, TheChild);
    
    static ParallaxScrollOffset* scrollWithNode(Node *node, Point r, Point p, Point s);
    static ParallaxScrollOffset* scrollWithNode(Node *node, Point r, Point p, Point s, Point v);
    ParallaxScrollOffset* initWithNode(Node *node, Point r, Point p, Point s, Point v);
    ParallaxScrollOffset* initWithNode(Node *node, Point r, Point p, Point s);
};

