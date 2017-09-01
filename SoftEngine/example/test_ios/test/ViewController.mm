//
//  ViewController.m
//  test
//
//  Created by xuyajie on 2017/8/13.
//  Copyright © 2017年 xyj. All rights reserved.
//

#import "ViewController.h"
#include "se.h"
#import <OpenGLES/EAGL.h>

#include <stdio.h>

CSoftEngine softEngine;
ViewController *viewcontrol;
void DrawBuffer(ubyte *buffer)
{
    IDevice *pDevice = softEngine.GetDevice();
    
    size_t width = pDevice->GetWindowWidth();
    size_t height = pDevice->GetWindowHeight();
    
    
    const size_t bufferLength = width * height * 4;
    NSData *data = [NSData dataWithBytes:buffer length:bufferLength];
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGDataProviderRef provider = CGDataProviderCreateWithCFData((CFDataRef)data);
    
    // Creating CGImage from cv::Mat
    CGImageRef imageRef = CGImageCreate(width,          //width
                                        height,         //height
                                        8,              //bits per component
                                        32,             //bits per pixel
                                        width * 4,      //bytesPerRow
                                        colorSpace,     //colorspace
                                        kCGImageAlphaFirst | kCGBitmapByteOrder32Little,// bitmap info
                                        provider,               //CGDataProviderRef
                                        NULL,                   //decode
                                        false,                  //should interpolate
                                        kCGRenderingIntentDefault   //intent
                                         );
    
    // Getting UIImage from CGImage
    UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
    
    [viewcontrol->pImageView setImage:finalImage];
    
    
    
    [finalImage drawInRect:viewcontrol.view.frame];
    

}

@interface ViewController ()

@end


@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    softEngine.InitEngine(RDT_SOFTWARE, 0, 0, self.view.frame.size.width, self.view.frame.size.height);
    
    ISceneManager *sceneMgr = softEngine.GetSceneManager();
    
    IDevice *pDevice = softEngine.GetDevice();
    pDevice->SetDrawCallback(DrawBuffer);
    
    //init scene
    sceneMgr->LoadScene("scene/scene.scene");
    
    NSTimer *pTimer = [NSTimer scheduledTimerWithTimeInterval:0.03
                                                       target:self
                                                     selector:@selector(Run)
                                                     userInfo:nil
                                                      repeats:YES];
    viewcontrol = self;
    
    pImageView = [[UIImageView alloc]initWithFrame:self.view.frame];    
    [self.view addSubview:pImageView];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)Run {
    ISceneManager *sceneMgr = softEngine.GetSceneManager();
    sceneMgr->Update(0);
    
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event{
    IEventManager *pEventMgr = softEngine.GetEventManager();
    
	NSSet *allTouches = [event allTouches];
	int i = 0;
	for (UITouch *touch in touches){
		float dx = [touch locationInView:[touch view]].x;
		float dy = [touch locationInView:[touch view]].y;
		pEventMgr->OnTouchBegin(i, dx, dy, touch.hash, allTouches.count); //touch.tapCount
		++i;
	}

}
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event{

}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event{

}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event{

}


@end
