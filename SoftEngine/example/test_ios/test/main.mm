//
//  main.m
//  test
//
//  Created by xuyajie on 2017/8/13.
//  Copyright © 2017年 xyj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    const char *path = argv[0];
    
    static char szParentDirectory[256];
    
    strncpy(szParentDirectory, path, sizeof(szParentDirectory));
    szParentDirectory[255] = '\0';

    
    char *p = strrchr(szParentDirectory, '/');
    if (p)
      *(++p) = 0;
    strncat(szParentDirectory, "/res/", sizeof("/res/"));
    
    chdir(szParentDirectory);
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
