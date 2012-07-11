//
//  ParallaxScrollNodeTestAppController.h
//  ParallaxScrollNodeTest
//
//  Created by Brandon Dorris on 7/6/12.
//  Copyright sirrodnodnarb inc 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

