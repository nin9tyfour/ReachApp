#import "headers.h"
#import "RAAllAppsWidget.h"
#import "RAReachabilityManager.h"
#import "RAWidgetSectionManager.h"
#import "RASettings.h"

@implementation RAAllAppsWidget
-(BOOL) enabled { return [RASettings.sharedInstance showAllAppsInWidgetSelector]; }

-(NSInteger) sortOrder { return 3; }

-(NSString*) displayName { return @"All Apps"; }
-(NSString*) identifier { return @"com.efrederickson.reachapp.widgets.sections.allapps"; }

-(UIView*) viewForFrame:(CGRect)frame preferredIconSize:(CGSize)size_ iconsThatFitPerLine:(NSInteger)iconsPerLine spacing:(CGFloat)spacing
{
	UIScrollView *allAppsView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, 200)];

	CGSize size = [%c(SBIconView) defaultIconSize];
	spacing = (frame.size.width - (iconsPerLine * size.width)) / iconsPerLine;
	//NSString *currentBundleIdentifier = [[UIApplication sharedApplication] _accessibilityFrontMostApplication].bundleIdentifier;
	//if (!currentBundleIdentifier)
	//	return nil;
	CGSize contentSize = CGSizeMake(10, 10);
	CGFloat interval = (size.width + spacing) * iconsPerLine;
	NSInteger intervalCount = 1;
	BOOL isTop = YES;
	BOOL hasSecondRow = NO;
	SBApplication *app = nil;
	CGFloat width = interval;

	allAppsView.backgroundColor = [UIColor clearColor];
	allAppsView.pagingEnabled = [RASettings.sharedInstance pagingEnabled];

	static NSMutableArray *allApps = nil;
	if (!allApps)
	{
		allApps = [[[[%c(SBIconViewMap) homescreenMap] iconModel] visibleIconIdentifiers] mutableCopy];
	    [allApps sortUsingComparator: ^(NSString* a, NSString* b) {
	    	NSString *a_ = [[%c(SBApplicationController) sharedInstance] applicationWithBundleIdentifier:a].displayName;
	    	NSString *b_ = [[%c(SBApplicationController) sharedInstance] applicationWithBundleIdentifier:b].displayName;
	        return [a_ caseInsensitiveCompare:b_];
		}];
		//[allApps removeObject:currentBundleIdentifier];
	}

	width = interval;
	isTop = YES;
	contentSize = CGSizeMake(10, 10);
	intervalCount = 1;
	hasSecondRow = NO;
	for (NSString *str in allApps)
	{
		app = [[%c(SBApplicationController) sharedInstance] applicationWithBundleIdentifier:str];
        SBIcon *icon = [[[%c(SBIconViewMap) homescreenMap] iconModel] applicationIconForBundleIdentifier:app.bundleIdentifier];
        SBIconView *iconView = [[%c(SBIconViewMap) homescreenMap] _iconViewForIcon:icon];
        if (!iconView || [icon isKindOfClass:[%c(SBApplicationIcon) class]] == NO)
        	continue;
        
        if (interval != 0 && contentSize.width + iconView.frame.size.width > interval * intervalCount)
		{
			if (isTop)
			{
				contentSize.height += size.height + 10;
				contentSize.width -= interval;
			}
			else
			{
				intervalCount++;
				contentSize.height -= (size.height + 10);
				width += interval;
			}
			hasSecondRow = YES;
			isTop = !isTop;
		}

        iconView.frame = CGRectMake(contentSize.width, contentSize.height, iconView.frame.size.width, iconView.frame.size.height);
        switch (UIApplication.sharedApplication.statusBarOrientation)
        {
        	case UIInterfaceOrientationLandscapeRight:
        		iconView.transform = CGAffineTransformMakeRotation(M_PI_2);
        		break;
        	case UIInterfaceOrientationLandscapeLeft:
        		iconView.transform = CGAffineTransformMakeRotation(-M_PI_2);
        		break;
        	case UIInterfaceOrientationPortraitUpsideDown:
        	case UIInterfaceOrientationPortrait:
        	default:
        		break;
        }

        iconView.tag = app.pid;
        iconView.restorationIdentifier = app.bundleIdentifier;
        UITapGestureRecognizer *iconViewTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(appViewItemTap:)];
        [iconView addGestureRecognizer:iconViewTapGestureRecognizer];

        [allAppsView addSubview:iconView];

        contentSize.width += iconView.frame.size.width + spacing;
	}
	contentSize.width = width;
	contentSize.height = 10 + ((size.height + 10) * (hasSecondRow ? 2 : 1));
	frame = allAppsView.frame;
	frame.size.height = contentSize.height;
	allAppsView.frame = frame;
	[allAppsView setContentSize:contentSize];
	return allAppsView;
}

-(void) appViewItemTap:(UIGestureRecognizer*)gesture
{
	[[%c(SBWorkspace) sharedInstance] appViewItemTap:gesture];
	//[[RAReachabilityManager sharedInstance] launchTopAppWithIdentifier:gesture.view.restorationIdentifier];
}
@end

%ctor
{
	static id _widget = [[RAAllAppsWidget alloc] init];
	[RAWidgetSectionManager.sharedInstance registerSection:_widget];
}