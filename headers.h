#import <SpringBoard/SpringBoard.h>
#import <SpringBoard/SBIconModel.h>
#import <SpringBoard/SBIcon.h>
#import <SpringBoard/SBIconController.h>
#import <SpringBoard/SBApplicationIcon.h>
#import <SpringBoard/SBIconImageView.h>
#import <UIKit/UIImage.h>
#import <UIKit/UIImageView.h>
#import <SpringBoard/SBIconLabel.h>
#import <SpringBoard/SBApplication.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>
#import <substrate.h>
#import <SpringBoard/SBApplication.h>
#include <mach/mach.h>
#include <libkern/OSCacheControl.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <sys/sysctl.h>
#import <notify.h>
#import <IOKit/hid/IOHIDEvent.h>

@interface UIInternalEvent : UIEvent {
    __GSEvent *_gsEvent;
    __IOHIDEvent *_hidEvent;
}

- (__GSEvent*)_gsEvent;
- (__IOHIDEvent*)_hidEvent;
- (id)_screen;
- (void)_setGSEvent:(__GSEvent*)arg1;
- (void)_setHIDEvent:(__IOHIDEvent*)arg1;
@end

@interface UIKeyboardImpl
+ (id)activeInstance;
+ (id)sharedInstance;
- (void)handleKeyEvent:(id)arg1;
- (void)handleKeyWithString:(id)arg1 forKeyEvent:(id)arg2 executionContext:(id)arg3;
- (void)deleteBackward;
@end

@interface UIPhysicalKeyboardEvent
+ (id)_eventWithInput:(id)arg1 inputFlags:(int)arg2;
@property(retain, nonatomic) NSString *_privateInput; // @synthesize _privateInput;
@property(nonatomic) int _inputFlags; // @synthesize _inputFlags;
@property(nonatomic) int _modifierFlags; // @synthesize _modifierFlags;
@property(retain, nonatomic) NSString *_markedInput; // @synthesize _markedInput;
@property(retain, nonatomic) NSString *_commandModifiedInput; // @synthesize _commandModifiedInput;
@property(retain, nonatomic) NSString *_shiftModifiedInput; // @synthesize _shiftModifiedInput;
@property(retain, nonatomic) NSString *_unmodifiedInput; // @synthesize _unmodifiedInput;
@property(retain, nonatomic) NSString *_modifiedInput; // @synthesize _modifiedInput;
@property(readonly, nonatomic) int _gsModifierFlags;
- (void)_privatizeInput;
- (void)dealloc;
- (id)_cloneEvent;
- (BOOL)isEqual:(id)arg1;
- (BOOL)_matchesKeyCommand:(id)arg1;
- (void)_setHIDEvent:(struct __IOHIDEvent *)arg1 keyboard:(struct __GSKeyboard *)arg2;
@property(readonly, nonatomic) long _keyCode;
@property(readonly, nonatomic) BOOL _isKeyDown;
- (int)type;
@end

@interface SBWorkspace 
+(id) sharedInstance;
-(void) RA_animateWidgetSelectorOut:(id)completion;
-(void) RA_setView:(UIView*)view preferredHeight:(CGFloat)preferredHeight;
-(void) RA_launchTopAppWithIdentifier:(NSString*) bundleIdentifier;
-(void) RA_showWidgetSelector;
-(void) updateViewSizes:(CGPoint)center animate:(BOOL)animate;
-(void) RA_closeCurrentView;
@end

@interface SBDisplayLayout : NSObject {
	int _layoutSize;
	NSMutableArray* _displayItems;
	NSString* _uniqueStringRepresentation;
}
@property(readonly, assign, nonatomic) NSArray* displayItems;
@property(readonly, assign, nonatomic) int layoutSize;
+(id)fullScreenDisplayLayoutForApplication:(id)application;
+(id)homeScreenDisplayLayout;
+(id)displayLayoutWithPlistRepresentation:(id)plistRepresentation;
+(id)displayLayoutWithLayoutSize:(int)layoutSize displayItems:(id)items;
-(id)displayLayoutBySettingSize:(int)size;
-(id)displayLayoutByReplacingDisplayItemOnSide:(int)side withDisplayItem:(id)displayItem;
-(id)displayLayoutByRemovingDisplayItems:(id)items;
-(id)displayLayoutByRemovingDisplayItem:(id)item;
-(id)displayLayoutByAddingDisplayItem:(id)item side:(int)side withLayout:(int)layout;
-(BOOL)isEqual:(id)equal;
-(unsigned)hash;
-(id)uniqueStringRepresentation;
-(id)_calculateUniqueStringRepresentation;
-(id)description;
-(id)copyWithZone:(NSZone*)zone;
-(void)dealloc;
-(id)plistRepresentation;
-(id)initWithLayoutSize:(int)layoutSize displayItems:(id)items;
@end

@interface FBProcessManager : NSObject
+ (id)sharedInstance;
- (void)_updateWorkspaceLockedState;
- (void)applicationProcessWillLaunch:(id)arg1;
- (void)noteProcess:(id)arg1 didUpdateState:(id)arg2;
- (void)noteProcessDidExit:(id)arg1;
- (id)_serviceClientAddedWithPID:(int)arg1 isUIApp:(BOOL)arg2 isExtension:(BOOL)arg3 bundleID:(id)arg4;
- (id)_serviceClientAddedWithConnection:(id)arg1;
- (id)_systemServiceClientAdded:(id)arg1;
- (BOOL)_isWorkspaceLocked;
- (id)createApplicationProcessForBundleID:(id)arg1 withExecutionContext:(id)arg2;
- (id)createApplicationProcessForBundleID:(id)arg1;
- (id)applicationProcessForPID:(int)arg1;
- (id)processForPID:(int)arg1;
- (id)applicationProcessesForBundleIdentifier:(id)arg1;
- (id)processesForBundleIdentifier:(id)arg1;
- (id)allApplicationProcesses;
- (id)allProcesses;
@end

@interface UIGestureRecognizerTarget : NSObject {
	id _target;
}
@end

typedef NS_ENUM(NSUInteger, BKSProcessAssertionReason)
{
    kProcessAssertionReasonAudio = 1,
    kProcessAssertionReasonLocation,
    kProcessAssertionReasonExternalAccessory,
    kProcessAssertionReasonFinishTask,
    kProcessAssertionReasonBluetooth,
    kProcessAssertionReasonNetworkAuthentication,
    kProcessAssertionReasonBackgroundUI,
    kProcessAssertionReasonInterAppAudioStreaming,
    kProcessAssertionReasonViewServices
};

typedef NS_ENUM(NSUInteger, ProcessAssertionFlags)
{
    ProcessAssertionFlagNone = 0,
    ProcessAssertionFlagPreventSuspend         = 1 << 0,
    ProcessAssertionFlagPreventThrottleDownCPU = 1 << 1,
    ProcessAssertionFlagAllowIdleSleep         = 1 << 2,
    ProcessAssertionFlagWantsForegroundResourcePriority  = 1 << 3
};


@interface FBWindowContextHostManager
- (id)hostViewForRequester:(id)arg1 enableAndOrderFront:(BOOL)arg2;
- (void)resumeContextHosting;
- (id)_hostViewForRequester:(id)arg1 enableAndOrderFront:(BOOL)arg2;
- (id)snapshotViewWithFrame:(CGRect)arg1 excludingContexts:(id)arg2 opaque:(BOOL)arg3;
- (id)visibleContexts;
- (void)orderRequesterFront:(id)arg1;
- (void)enableHostingForRequester:(id)arg1 orderFront:(BOOL)arg2;
- (void)enableHostingForRequester:(id)arg1 priority:(int)arg2;
- (void)disableHostingForRequester:(id)arg1;
- (void)_updateHostViewFrameForRequester:(id)arg1;
- (void)invalidate;
@end

@interface FBSSceneSettings : NSObject <NSCopying, NSMutableCopying>
{
    CGRect _frame;
    CGPoint _contentOffset;
    float _level;
    int _interfaceOrientation;
    BOOL _backgrounded;
    BOOL _occluded;
    BOOL _occludedHasBeenCalculated;
    NSSet *_ignoreOcclusionReasons;
    NSArray *_occlusions;
    //BSSettings *_otherSettings;
    //BSSettings *_transientLocalSettings;
}

+ (BOOL)_isMutable;
+ (id)settings;
@property(readonly, copy, nonatomic) NSArray *occlusions; // @synthesize occlusions=_occlusions;
@property(readonly, nonatomic, getter=isBackgrounded) BOOL backgrounded; // @synthesize backgrounded=_backgrounded;
@property(readonly, nonatomic) int interfaceOrientation; // @synthesize interfaceOrientation=_interfaceOrientation;
@property(readonly, nonatomic) float level; // @synthesize level=_level;
@property(readonly, nonatomic) CGPoint contentOffset; // @synthesize contentOffset=_contentOffset;
@property(readonly, nonatomic) CGRect frame; // @synthesize frame=_frame;
- (id)valueDescriptionForFlag:(int)arg1 object:(id)arg2 ofSetting:(unsigned int)arg3;
- (id)keyDescriptionForSetting:(unsigned int)arg1;
- (id)description;
- (BOOL)isEqual:(id)arg1;
- (unsigned int)hash;
- (id)_descriptionOfSettingsWithMultilinePrefix:(id)arg1;
- (id)transientLocalSettings;
- (BOOL)isIgnoringOcclusions;
- (id)ignoreOcclusionReasons;
- (id)otherSettings;
- (BOOL)isOccluded;
- (CGRect)bounds;
- (void)dealloc;
- (id)init;
- (id)initWithSettings:(id)arg1;

@end

@interface FBSMutableSceneSettings : FBSSceneSettings
{
}

+ (BOOL)_isMutable;
- (id)mutableCopyWithZone:(struct _NSZone *)arg1;
- (id)copyWithZone:(struct _NSZone *)arg1;
@property(copy, nonatomic) NSArray *occlusions;
- (id)transientLocalSettings;
- (id)ignoreOcclusionReasons;
- (id)otherSettings;
@property(nonatomic, getter=isBackgrounded) BOOL backgrounded;
@property(nonatomic) int interfaceOrientation;
@property(nonatomic) float level;
@property(nonatomic) struct CGPoint contentOffset;
@property(nonatomic) struct CGRect frame;

@end

@interface FBScene
-(FBWindowContextHostManager*) contextHostManager;
@property(readonly, retain, nonatomic) FBSMutableSceneSettings *mutableSettings; // @synthesize mutableSettings=_mutableSettings;
- (void)updateSettings:(id)arg1 withTransitionContext:(id)arg2;
- (void)_applyMutableSettings:(id)arg1 withTransitionContext:(id)arg2 completion:(id)arg3;
@end

@interface SBApplication ()
-(FBScene*) mainScene;
- (void)activate;

- (void)processDidLaunch:(id)arg1;
- (void)processWillLaunch:(id)arg1;
- (void)resumeForContentAvailable;
- (void)resumeToQuit;
- (void)_sendDidLaunchNotification:(_Bool)arg1;
- (void)notifyResumeActiveForReason:(long long)arg1;

@property(readonly, nonatomic) int pid;
@end

@interface SBApplicationController
+(id) sharedInstance;
-(SBApplication*) applicationWithBundleIdentifier:(NSString*)identifier;
-(SBApplication*)applicationWithPid:(int)arg1;
@end

@interface FBWindowContextHostWrapperView : UIView
@property(readonly, nonatomic) FBWindowContextHostManager *manager; // @synthesize manager=_manager;
@property(nonatomic) unsigned int appearanceStyle; // @synthesize appearanceStyle=_appearanceStyle;
- (void)_setAppearanceStyle:(unsigned int)arg1 force:(BOOL)arg2;
- (id)_stringForAppearanceStyle;
- (id)window;
@property(readonly, nonatomic) struct CGRect referenceFrame; // @dynamic referenceFrame;
@property(readonly, nonatomic, getter=isContextHosted) BOOL contextHosted; // @dynamic contextHosted;
- (void)clearManager;
- (void)_hostingStatusChanged;
- (BOOL)_isReallyHosting;
- (void)updateFrame;
@end
@interface FBWindowContextHostView : UIView
@end

@interface UIKeyboard : UIView
+ (id)activeKeyboard;

- (BOOL)isMinimized;
- (void)minimize;
@end

@interface BKSProcessAssertion
- (id)initWithPID:(int)arg1 flags:(unsigned int)arg2 reason:(unsigned int)arg3 name:(id)arg4 withHandler:(id)arg5;
- (id)initWithBundleIdentifier:(id)arg1 flags:(unsigned int)arg2 reason:(unsigned int)arg3 name:(id)arg4 withHandler:(id)arg5;
- (void)invalidate;
@property(readonly, nonatomic) BOOL valid;
@end

@interface SBReachabilityManager
+ (id)sharedInstance;
@property(readonly, nonatomic) _Bool reachabilityModeActive; // @synthesize reachabilityModeActive=_reachabilityModeActive;
- (void)_handleReachabilityDeactivated;
- (void)_handleReachabilityActivated;
@end
@interface SBAppSwitcherModel : NSObject
+ (id)sharedInstance;
- (id)snapshotOfFlattenedArrayOfAppIdentifiersWhichIsOnlyTemporary;
- (id)snapshot;
- (void)remove:(id)arg1;
- (void)removeDisplayItem:(id)arg1;
- (void)addToFront:(id)arg1;
- (void)_verifyAppList;
- (id)_recentsFromPrefs;
- (id)_recentsFromLegacyPrefs;
@end

@interface UIImage ()
+ (id)_applicationIconImageForBundleIdentifier:(id)arg1 format:(int)arg2 scale:(float)arg3;
+ (id)_applicationIconImageForBundleIdentifier:(id)arg1 format:(int)arg2;
@end

@interface FBApplicationProcess : NSObject
- (void)launchIfNecessary;
- (BOOL)bootstrapAndExec;
@end

@interface UITextEffectsWindow : UIWindow
+ (id)sharedTextEffectsWindow;
@end

@interface UIWindow () 
+(id) keyWindow;
-(id) firstResponder;
+ (void)setAllWindowsKeepContextInBackground:(BOOL)arg1;
-(void) _setRotatableViewOrientation:(UIInterfaceOrientation)orientation duration:(CGFloat)duration force:(BOOL)force;
- (void)_setRotatableViewOrientation:(int)arg1 updateStatusBar:(BOOL)arg2 duration:(double)arg3 force:(BOOL)arg4;
- (void)_rotateWindowToOrientation:(int)arg1 updateStatusBar:(BOOL)arg2 duration:(double)arg3 skipCallbacks:(BOOL)arg4;
@end

@interface UIApplication ()
- (id)_mainScene;

// SpringBoard methods
-(BOOL)launchApplicationWithIdentifier:(id)identifier suspended:(BOOL)suspended;
-(SBApplication*) _accessibilityFrontMostApplication;

- (void)_setStatusBarHidden:(BOOL)arg1 animationParameters:(id)arg2 changeApplicationFlag:(BOOL)arg3;
- (void)RA_forceRotationToInterfaceOrientation:(UIInterfaceOrientation)orientation isReverting:(BOOL)reverting;
- (void)applicationDidResume;
- (void)_sendWillEnterForegroundCallbacks;
- (void)suspend;
- (void)applicationWillSuspend;
- (void)_setSuspended:(BOOL)arg1;
- (void)applicationSuspend;
- (void)_deactivateForReason:(int)arg1 notify:(BOOL)arg2;
@end

@interface SBIconLabelView : UIView
@end

@interface SBIcon (iOS81)
-(BOOL) isBeta;
@end

@interface SBIconModel (iOS81)
- (id)visibleIconIdentifiers;
- (id)applicationIconForBundleIdentifier:(id)arg1;
@end

@interface SBIconModel (iOS40)
- (/*SBApplicationIcon*/SBIcon *)applicationIconForDisplayIdentifier:(NSString *)displayIdentifier;
@end

@interface SBIcon (iOS40)
- (void)prepareDropGlow;
- (UIImageView *)dropGlow;
- (void)showDropGlow:(BOOL)showDropGlow;
- (long long)badgeValue;
- (id)leafIdentifier;
- (SBApplication*)application;
- (NSString*)applicationBundleID;
@end

@interface SBIconController (iOS40)
- (BOOL)canUninstallIcon:(SBIcon *)icon;
@end

@protocol SBIconViewDelegate, SBIconViewLocker;
@class SBIconImageContainerView, SBIconBadgeImage;

@interface SBIconView : UIView {
	SBIcon *_icon;
	id<SBIconViewDelegate> _delegate;
	id<SBIconViewLocker> _locker;
	SBIconImageContainerView *_iconImageContainer;
	SBIconImageView *_iconImageView;
	UIImageView *_iconDarkeningOverlay;
	UIImageView *_ghostlyImageView;
	UIImageView *_reflection;
	UIImageView *_shadow;
	SBIconBadgeImage *_badgeImage;
	UIImageView *_badgeView;
	SBIconLabel *_label;
	BOOL _labelHidden;
	BOOL _labelOnWallpaper;
	UIView *_closeBox;
	int _closeBoxType;
	UIImageView *_dropGlow;
	unsigned _drawsLabel : 1;
	unsigned _isHidden : 1;
	unsigned _isGrabbed : 1;
	unsigned _isOverlapping : 1;
	unsigned _refusesRecipientStatus : 1;
	unsigned _highlighted : 1;
	unsigned _launchDisabled : 1;
	unsigned _isJittering : 1;
	unsigned _allowJitter : 1;
	unsigned _touchDownInIcon : 1;
	unsigned _hideShadow : 1;
	NSTimer *_delayedUnhighlightTimer;
	unsigned _onWallpaper : 1;
	unsigned _ghostlyRequesters;
	int _iconLocation;
	float _iconImageAlpha;
	float _iconImageBrightness;
	float _iconLabelAlpha;
	float _accessoryAlpha;
	CGPoint _unjitterPoint;
	CGPoint _grabPoint;
	NSTimer *_longPressTimer;
	unsigned _ghostlyTag;
	UIImage *_ghostlyImage;
	BOOL _ghostlyPending;
}
+ (CGSize)defaultIconSize;
+ (CGSize)defaultIconImageSize;
+ (BOOL)allowsRecycling;
+ (id)_jitterPositionAnimation;
+ (id)_jitterTransformAnimation;
+ (struct CGSize)defaultIconImageSize;
+ (struct CGSize)defaultIconSize;

- (id)initWithDefaultSize;
- (void)dealloc;

@property(assign) id<SBIconViewDelegate> delegate;
@property(assign) id<SBIconViewLocker> locker;
@property(readonly, retain) SBIcon *icon;
- (void)setIcon:(SBIcon *)icon;

- (int)location;
- (void)setLocation:(int)location;
- (void)showIconAnimationDidStop:(id)showIconAnimation didFinish:(id)finish icon:(id)icon;
- (void)setIsHidden:(BOOL)hidden animate:(BOOL)animate;
- (BOOL)isHidden;
- (BOOL)isRevealable;
- (void)positionIconImageView;
- (void)applyIconImageTransform:(CATransform3D)transform duration:(float)duration delay:(float)delay;
- (void)setDisplayedIconImage:(id)image;
- (id)snapshotSettings;
- (id)iconImageSnapshot:(id)snapshot;
- (id)reflectedIconWithBrightness:(CGFloat)brightness;
- (void)setIconImageAlpha:(CGFloat)alpha;
- (void)setIconLabelAlpha:(CGFloat)alpha;
- (SBIconImageView *)iconImageView;
- (void)setLabelHidden:(BOOL)hidden;
- (void)positionLabel;
- (CGSize)_labelSize;
- (Class)_labelClass;
- (void)updateLabel;
- (void)_updateBadgePosition;
- (id)_overriddenBadgeTextForText:(id)text;
- (void)updateBadge;
- (id)_automationID;
- (BOOL)pointMostlyInside:(CGPoint)inside withEvent:(UIEvent *)event;
- (CGRect)frameForIconOverlay;
- (void)placeIconOverlayView;
- (void)updateIconOverlayView;
- (void)_updateIconBrightness;
- (BOOL)allowsTapWhileEditing;
- (BOOL)delaysUnhighlightWhenTapped;
- (BOOL)isHighlighted;
- (void)setHighlighted:(BOOL)highlighted;
- (void)setHighlighted:(BOOL)highlighted delayUnhighlight:(BOOL)unhighlight;
- (void)_delayedUnhighlight;
- (BOOL)isInDock;
- (id)_shadowImage;
- (void)_updateShadow;
- (void)updateReflection;
- (void)setDisplaysOnWallpaper:(BOOL)wallpaper;
- (void)setLabelDisplaysOnWallpaper:(BOOL)wallpaper;
- (BOOL)showsReflection;
- (float)_reflectionImageOffset;
- (void)setFrame:(CGRect)frame;
- (void)setIsJittering:(BOOL)isJittering;
- (void)setAllowJitter:(BOOL)allowJitter;
- (BOOL)allowJitter;
- (void)removeAllIconAnimations;
- (void)setIconPosition:(CGPoint)position;
- (void)setRefusesRecipientStatus:(BOOL)status;
- (BOOL)canReceiveGrabbedIcon:(id)icon;
- (double)grabDurationForEvent:(id)event;
- (void)setIsGrabbed:(BOOL)grabbed;
- (BOOL)isGrabbed;
- (void)setIsOverlapping:(BOOL)overlapping;
- (CGAffineTransform)transformToMakeDropGlowShrinkToIconSize;
- (void)prepareDropGlow;
- (void)showDropGlow:(BOOL)glow;
- (void)removeDropGlow;
- (id)dropGlow;
- (BOOL)isShowingDropGlow;
- (void)placeGhostlyImageView;
- (id)_genGhostlyImage:(id)image;
- (void)prepareGhostlyImageIfNeeded;
- (void)prepareGhostlyImage;
- (void)prepareGhostlyImageView;
- (void)setGhostly:(BOOL)ghostly requester:(int)requester;
- (void)setPartialGhostly:(float)ghostly requester:(int)requester;
- (void)removeGhostlyImageView;
- (BOOL)isGhostly;
- (int)ghostlyRequesters;
- (void)longPressTimerFired;
- (void)cancelLongPressTimer;
- (void)touchesCancelled:(id)cancelled withEvent:(id)event;
- (void)touchesBegan:(id)began withEvent:(id)event;
- (void)touchesMoved:(id)moved withEvent:(id)event;
- (void)touchesEnded:(id)ended withEvent:(id)event;
- (BOOL)isTouchDownInIcon;
- (void)setTouchDownInIcon:(BOOL)icon;
- (void)hideCloseBoxAnimationDidStop:(id)hideCloseBoxAnimation didFinish:(id)finish closeBox:(id)box;
- (void)positionCloseBoxOfType:(int)type;
- (id)_newCloseBoxOfType:(int)type;
- (void)setShowsCloseBox:(BOOL)box;
- (void)setShowsCloseBox:(BOOL)box animated:(BOOL)animated;
- (BOOL)isShowingCloseBox;
- (void)closeBoxTapped;
- (BOOL)pointInside:(CGPoint)inside withEvent:(id)event;
- (UIEdgeInsets)snapshotEdgeInsets;
- (void)setShadowsHidden:(BOOL)hidden;
- (void)_updateShadowFrameForShadow:(id)shadow;
- (void)_updateShadowFrame;
- (BOOL)_delegatePositionIsEditable;
- (void)_delegateTouchEnded:(BOOL)ended;
- (BOOL)_delegateTapAllowed;
- (int)_delegateCloseBoxType;
- (id)createShadowImageView;
- (void)prepareForRecycling;
- (CGRect)defaultFrameForProgressBar;
- (void)iconImageDidUpdate:(id)iconImage;
- (void)iconAccessoriesDidUpdate:(id)iconAccessories;
- (void)iconLaunchEnabledDidChange:(id)iconLaunchEnabled;
- (SBIconImageView*)_iconImageView;

@end

@class NSMapTable;

@interface SBIconViewMap : NSObject {
	NSMapTable* _iconViewsForIcons;
	id<SBIconViewDelegate> _iconViewdelegate;
	NSMapTable* _recycledIconViewsByType;
	NSMapTable* _labels;
	NSMapTable* _badges;
}
+ (SBIconViewMap *)switcherMap;
+(SBIconViewMap *)homescreenMap;
+(Class)iconViewClassForIcon:(SBIcon *)icon location:(int)location;
-(id)init;
-(void)dealloc;
-(SBIconView *)mappedIconViewForIcon:(SBIcon *)icon;
-(SBIconView *)_iconViewForIcon:(SBIcon *)icon;
-(SBIconView *)iconViewForIcon:(SBIcon *)icon;
-(void)_addIconView:(SBIconView *)iconView forIcon:(SBIcon *)icon;
-(void)purgeIconFromMap:(SBIcon *)icon;
-(void)_recycleIconView:(SBIconView *)iconView;
-(void)recycleViewForIcon:(SBIcon *)icon;
-(void)recycleAndPurgeAll;
-(id)releaseIconLabelForIcon:(SBIcon *)icon;
-(void)captureIconLabel:(id)label forIcon:(SBIcon *)icon;
-(void)purgeRecycledIconViewsForClass:(Class)aClass;
-(void)_modelListAddedIcon:(SBIcon *)icon;
-(void)_modelRemovedIcon:(SBIcon *)icon;
-(void)_modelReloadedIcons;
-(void)_modelReloadedState;
-(void)iconAccessoriesDidUpdate:(SBIcon *)icon;
@end

@interface SBIconViewMap (iOS6)
@property (nonatomic, readonly) SBIconModel *iconModel;
@end

@interface SBApplication (iOS6)
- (BOOL)isRunning;
- (id)badgeNumberOrString;
- (NSString*)bundleIdentifier;
- (_Bool)_isRecentlyUpdated;
- (_Bool)_isNewlyInstalled;
@end

@interface SBIconBlurryBackgroundView : UIView
{
    struct CGRect _wallpaperRelativeBounds;
    _Bool _isBlurring;
    id _wantsBlurEvaluator;
    struct CGPoint _wallpaperRelativeCenter;
}

@property(copy, nonatomic) id wantsBlurEvaluator; // @synthesize wantsBlurEvaluator=_wantsBlurEvaluator;
@property(readonly, nonatomic) _Bool isBlurring; // @synthesize isBlurring=_isBlurring;
@property(nonatomic) struct CGPoint wallpaperRelativeCenter; // @synthesize wallpaperRelativeCenter=_wallpaperRelativeCenter;
- (_Bool)_shouldAnimatePropertyWithKey:(id)arg1;
- (void)setBlurring:(_Bool)arg1;
- (void)setWallpaperColor:(struct CGColor *)arg1 phase:(struct CGSize)arg2;
- (_Bool)wantsBlur:(id)arg1;
- (struct CGRect)wallpaperRelativeBounds;
- (void)didAddSubview:(id)arg1;
- (void)dealloc;
- (id)initWithFrame:(struct CGRect)arg1;
@end

@interface SBFolderIconBackgroundView : SBIconBlurryBackgroundView
- (id)initWithDefaultSize;
@end

@interface SBIconImageView ()
{
    UIImageView *_overlayView;
    //SBIconProgressView *_progressView;
    _Bool _isPaused;
    UIImage *_cachedSquareContentsImage;
    _Bool _showsSquareCorners;
    SBIcon *_icon;
    double _brightness;
    double _overlayAlpha;
}

+ (id)dequeueRecycledIconImageViewOfClass:(Class)arg1;
+ (void)recycleIconImageView:(id)arg1;
+ (double)cornerRadius;
@property(nonatomic) _Bool showsSquareCorners; // @synthesize showsSquareCorners=_showsSquareCorners;
@property(nonatomic) double overlayAlpha; // @synthesize overlayAlpha=_overlayAlpha;
@property(nonatomic) double brightness; // @synthesize brightness=_brightness;
@property(retain, nonatomic) SBIcon *icon; // @synthesize icon=_icon;
- (_Bool)_shouldAnimatePropertyWithKey:(id)arg1;
- (void)iconImageDidUpdate:(id)arg1;
- (struct CGRect)visibleBounds;
- (struct CGSize)sizeThatFits:(struct CGSize)arg1;
- (id)squareDarkeningOverlayImage;
- (id)darkeningOverlayImage;
- (id)squareContentsImage;
- (UIImage*)contentsImage;
- (void)_clearCachedImages;
- (id)_generateSquareContentsImage;
- (void)_updateProgressMask;
- (void)_updateOverlayImage;
- (id)_currentOverlayImage;
- (void)updateImageAnimated:(_Bool)arg1;
- (id)snapshot;
- (void)prepareForReuse;
- (void)layoutSubviews;
- (void)setPaused:(_Bool)arg1;
- (void)setProgressAlpha:(double)arg1;
- (void)_clearProgressView;
- (void)progressViewCanBeRemoved:(id)arg1;
- (void)setProgressState:(long long)arg1 paused:(_Bool)arg2 percent:(double)arg3 animated:(_Bool)arg4;
- (void)_updateOverlayAlpha;
- (void)setIcon:(id)arg1 animated:(_Bool)arg2;
- (void)dealloc;
- (id)initWithFrame:(struct CGRect)arg1;
@end

@interface BBBulletin
@property(copy, nonatomic) NSString *bulletinID; // @synthesize bulletinID=_bulletinID;
@property(copy, nonatomic) NSString *sectionID; // @synthesize sectionID=_sectionID;
@property(copy, nonatomic) NSString *section;
@property(copy, nonatomic) NSString *message;
@property(copy, nonatomic) NSString *subtitle;
@property(copy, nonatomic) NSString *title;
@end

@interface BBServer
- (void)publishBulletin:(id)arg1 destinations:(unsigned long long)arg2 alwaysToLockScreen:(_Bool)arg3;
- (id)_allBulletinsForSectionID:(id)arg1;

- (id)allBulletinIDsForSectionID:(id)arg1;
- (id)noticesBulletinIDsForSectionID:(id)arg1;
- (id)bulletinIDsForSectionID:(id)arg1 inFeed:(unsigned long long)arg2;
@end

