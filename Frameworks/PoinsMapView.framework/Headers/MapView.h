//
//  MapView.h
//  mapview
//
//  Created by 강현석 on 2017. 8. 1..
//  Copyright © 2017년 KangHyeonSeok. All rights reserved.
//

#import <QuartzCore/CADisplayLink.h>
#import "RenderPluginDelegate.h"
#import "JSONModelLib.h"

@interface Map2DFileInfo : JSONModel
    @property (nonatomic) NSString * FilePath;
    @property (nonatomic) NSNumber * Width;
    @property (nonatomic) NSNumber * Height;
@end

@protocol RoomDataForMap;
@interface RoomDataForMap : JSONModel
    @property (nonatomic) NSString * RoomNm;
    @property (nonatomic) NSNumber * SvgPointX;
    @property (nonatomic) NSNumber * SvgPointY;
    
    @property (nonatomic) NSNumber * dPositionX;
    @property (nonatomic) NSNumber * dPositionY;
    
    @property (nonatomic) NSString * imageUrl;
    
    @property (nonatomic) NSString * icon;
    @property (nonatomic) NSNumber * importance;
    
    @property (nonatomic) NSNumber * lodLevel;
    
    @property (nonatomic) BOOL HasEvent;
@end

@interface FloorData : JSONModel
    @property (nonatomic) NSNumber * FloorIndex;
    @property (nonatomic) NSMutableArray<RoomDataForMap> *RoomDataList;
@end

@protocol RoutePositionData;
@interface RoutePositionData : JSONModel
    @property (nonatomic) NSNumber * X;
    @property (nonatomic) NSNumber * Y;
    @property (nonatomic) NSNumber * FloorIndex;
    @property (nonatomic) NSNumber * Type;
@end

@interface RouteData : JSONModel
    @property (nonatomic) NSMutableArray<RoutePositionData>* RouteDataList;
    @property (nonatomic) NSString* EndPointLabel;
    @property (nonatomic) BOOL ShowStartMarker;
    @property (nonatomic) BOOL ShowWholePath;
@end


@protocol MapViewDelegate <NSObject>
-(Map2DFileInfo*)get2DMapInfo:(NSNumber*)mapID withFloorIndex : (NSNumber*) floorIndex;
-(void)showRoomInfo:(NSNumber *) floorIndex withRoomIndex : (NSNumber *) roomIndex;
-(NSString*) getFloorDisplayName:(NSNumber*) floorIndex;
-(FloorData*) getFloorData : (NSNumber*)mapID withFloorIndex : (NSNumber*)floorIndex;
-(void) loadingComplete:(NSNumber*)mapID withFloorIndex : (NSNumber*) floorIndex;
-(void) cancelFollow;
@end


@class UnityView;
@class DisplayConnection;

@interface MapView : UIView {
    UnityView*          _unityView;
    UIWindow*           _window;
    CADisplayLink*      _displayLink;
    DisplayConnection*  _mainDisplay;
    id<RenderPluginDelegate>    _renderDelegate;
    
    UIView*             _rootView;
    UIViewController*   _rootController;
    UIView*             _snapshotView;
}

-(void)start;
-(void)initialize:(id)mapViewDelegate;
-(void)show2DMap:(NSNumber*) mapID withFloorIndex : (NSNumber*) floorIndex;
-(void)show3DMap:(NSString*) filePath withMapID : (NSNumber*)mapID withFloorIndex : (NSNumber*) floorIndex withRoomIndex:(NSNumber*) roomIndex;
-(void)followMyPosition;
-(void)setUserPosition:(NSNumber*) mapID withFloorIndex:(NSNumber*)floorIndex withX:(NSNumber*) x withY:(NSNumber*) y withHeading:(NSNumber*) heading withPathNodeIndex:(NSNumber*) currentPathNodeIndex;
-(void)clearFollowMyPosition;

-(void)showRoute:(NSMutableArray<RoutePositionData>*) routeDataList withEndPointLabel:(NSString*) endPointLabel withShowStartMarker:(BOOL)showStartMarker withShowWholePath:(BOOL)showWholePath;

-(NSString*)toJson:(id)obj;

+(MapView*)getMakedInstance;

@property (readonly, copy, nonatomic) UnityView*            unityView;
@property (retain, nonatomic) UIWindow* window;
@property (readonly, copy, nonatomic) CADisplayLink*        unityDisplayLink;
//
@property (readonly, copy, nonatomic) DisplayConnection*    mainDisplay;
@property (readonly, copy, nonatomic) UIView*               rootView;
@property (readonly, copy, nonatomic) UIViewController*     rootViewController;
//
//@property (readonly, nonatomic) UIInterfaceOrientation      interfaceOrientation;
//
@property (nonatomic, retain) id                            renderDelegate;
//@property (nonatomic, copy)                                 void(^quitHandler)();
@property (weak, nonatomic) id<MapViewDelegate> delegate;
@end

// these are simple wrappers about ios api, added for convenience
void AppController_SendNotification(NSString* name);
void AppController_SendNotificationWithArg(NSString* name, id arg);

void AppController_SendUnityViewControllerNotification(NSString* name);
