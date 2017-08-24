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

@interface ViewController ()

@end



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
    

    
    CGRect myRect;
    UIImageView *pView = [[UIImageView alloc] initWithImage:finalImage];
    
    [viewcontrol.view addSubview:pView];
    myRect.origin.x = 0.0 ;
    myRect.origin.y = 0.0;
    myRect.size = finalImage.size;
    [finalImage drawInRect:myRect];

}

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    softEngine.InitEngine(RDT_SOFTWARE, 0, 0, 400, 600);
    
    IResourceManager *resMgr = softEngine.GetResourceManager();
    ISceneManager *sceneMgr = softEngine.GetSceneManager();
    
    
    IDevice *pDevice = softEngine.GetDevice();
    pDevice->SetDrawCallback(DrawBuffer);
    
    //init scene
    IScene *scene = sceneMgr->LoadScene("scene/scene.scene");
    
    NSTimer *pTimer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                       target:self
                                                     selector:@selector(Run)
                                                     userInfo:nil
                                                      repeats:YES];
    viewcontrol = self;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)Run {
    ISceneManager *sceneMgr = softEngine.GetSceneManager();
    sceneMgr->Update(0);
    
}


@end
