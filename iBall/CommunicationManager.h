//
//  CommunicationManager.h
//  iBall
//
//  Created by iNghia on 12/12/12.
//  Copyright (c) 2012 iNghia. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import <GLKit/GLKit.h>
#import "Common.h"

@class CommunicationManager;

@protocol CommunicationManagerDelegate <NSObject>
    - (void)connectionStatusChanged;
- (void)drawConnectionLine:(NSString *)peerID andTransitionMatrix:(GLKMatrix4)matrix andDirection:(int)pDirection andStartPoint:(GLKVector3)sPoint andEndPoint:(GLKVector3)ePoint;

    - (void)receiveGameStart;
    - (void)receiveCalibrationData;
    - (void)receiveNewBall:(NSString *)peerId andStartPosition:(GLKVector3)startPosition andVelocity:(GLKVector3)startVelocity andTexIndex:(int)texIndex;
@end


extern CommunicationManager *gCommunicationManager;

@interface CommunicationManager : NSObject <GKSessionDelegate>
{
    NSString *sessionID;
    GKSession *mySession;
    
    NSMutableArray *connectedPeersInfor;
    
    Boolean searchOn;
    Boolean isMainDevice;
    
    NSMutableArray *connectedPeerList;
    NSMutableArray *availablePeerList;
    
    int DEVICE_TYPE;
    int DEVICE_WIDTH;
    int DEVICE_HEIGHT;
    float DEVICE_RATIO;
    
    
    // for position, direction matrix
    NSDate *startGesture;
    
    CGPoint point1;
    CGPoint point2;
    
    int direction; //up: 1, right: 2, down: 3, left: 4
    GLKVector3 endPoint;
}

@property (assign) id<CommunicationManagerDelegate> delegate;

@property (nonatomic, assign) Boolean isMainDevice;
@property (nonatomic, readonly) NSMutableArray *availablePeerList;
@property (nonatomic, readonly) NSMutableArray  *connectedPeerList;

@property (nonatomic, assign) int DEVICE_TYPE;
@property (nonatomic, assign) int DEVICE_WIDTH;
@property (nonatomic, assign) int DEVICE_HEIGHT;
@property (nonatomic, assign) float DEVICE_RATIO;

+ (CommunicationManager *) instance;

- (void) initSession;
- (NSString *)getNameOfDevice:(NSString *)peerId;
- (void) connectToDevice:(NSString *)peerId;

- (void) sendCalibrationData:(CGPoint)pEndPoint andDirection:(int)pDirection;
- (void) sendBallData:(NSString *)peerId andStartPosition:(GLKVector3) startPosition andVelocity:(GLKVector3)startVelocity andTexIndex:(int)texIndex;

- (void) calculateTransitionMatrix:(NSString *)peerId andPeerDeviceType:(int)peerDeviceType andDeviceDirection:(int)peerDeviceDirection andPeerEndpoint:(GLKVector3)peerEndPoint;

- (GLKVector3) convertCoordinationTo3D:(CGPoint) point;

- (void) destroyMySession;

@end
