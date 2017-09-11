# PoinsNavi Framework for iOS

![swift](https://img.shields.io/badge/swift-3.0-orange.svg?style=flat)
![Platform](https://img.shields.io/cocoapods/p/LFAlertController.svg?style=flat)
> PoinsNavi는 실내 길안내용 View 기반의 라이브러리 입니다.

![](https://dl.dropboxusercontent.com/s/losspm0yxl099pg/launch.PNG)

# Contents
- [Requirements](#requirements)
- [Features](#features)
- [Other Frameworks](#other-frameworks)
- [Installation](#installation)
- [Usage](#usage)

# Requirements
* iOS 8.0+
* Xcode 8.3+

# Features
* 위치 측위
* 경로 안내 
* PoI 명칭 및 편의시설 검색 

# Other Frameworks
PoinsNavi는 다음의 외부 라이브러리를 사용하고 있습니다.
* [Alamofire](https://github.com/trikha/Almofire) : HTTP networking library
* [SwiftyJSON](https://github.com/SwiftyJSON/SwiftyJSON) : JSON parser
* [SQLite.swift](https://github.com/stephencelis/SQLite.swift) : sqlite library

# Installation
1. **PoinsIPS.framework, PoinsNavi.framework, PoinsMapView.framework**를 프로젝트에 추가합니다.
2. [Other Frameworks](#other-frameworks) 를 프로젝트에 추가합니다. 
(또는 ExternalFrameworks폴더 내부의 빌드된 Framework들을 추가할 수 있습니다.)

![](https://dl.dropboxusercontent.com/s/ev1cif2a0efv0ih/add%20frameworks.png)

3. Poject > General > Embedded Binaries 에 1, 2번에서 추가한 framework들을 추가합니다.
![](https://dl.dropboxusercontent.com/s/1gskovjujvfucq8/Embedded%20Binaries.png)

# Usage

### Swift

1. ViewController 내부 PoinsNaviView 생성
* Class : PoinsNaviView
* Module : PoinsNavi
![](https://dl.dropboxusercontent.com/s/5mbr3ajo8xkdkyo/add%20PoinsNaviView.png)

2. PoinsNaviView IBOutlet 연결
![](https://dl.dropboxusercontent.com/s/qh5nargr7u5pexy/createPoinsNaviViewOutlet.png)
```swift
@IBOutlet weak var poinsNaviView: PoinsNaviView!
```
3. import PoinsNavi
```swift
import PoinsNavi
```
4. PoinsNavi Mapview 로딩
맵을 사용하기 위해서는 로딩할 건물의 인덱스 정보를 알아야합니다. 
```swift
poinsNaviView.loadView(mapIdList:[1,2])
```
로딩 시 언어를 설정할 수 있습니다. ('en', 'zh', 'ja', 'ko')
생략 시 기본언어는 시스템 언어입니다. 
```swift
poinsNaviView.loadView(mapIdList:[1,2], language:"ko")
```

다음은 ViewController의 전체 예제 코드입니다. 
```swift
import UIKit
import PoinsNavi

class ViewController: UIViewController {

    @IBOutlet weak var poinsNaviView: PoinsNaviView!
    override func viewDidLoad() {
        super.viewDidLoad()
        poinsNaviView.loadView(mapIdList: [38, 39, 37])
    }
}
```

5. 실행 후 PoinsNavi의 맵 화면을 볼 수 있습니다. 

### Objective-C

1. Swift 1 ~ 2 같이 Swift 프로젝트와 동일하게 리소스를 구성합니다.

2. ViewController를 다음과 같이 작성합니다. 

ViewController.h
```ObjC
@import PoinsNavi;

@interface ViewController : UIViewController

@property (strong, nonatomic) IBOutlet PoinsNaviView *poinsNaviView;

@end
```

ViewController.m

언어 설정을 직접 합니다. ('en', 'zh', 'ja', 'ko')
```ObjC
#import "ViewController.h"
#import "PoinsNavi/PoinsNavi-Swift.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSArray *mapIdList =  [NSArray arrayWithObjects:
                          [NSNumber numberWithInteger:1],
                          [NSNumber numberWithInteger:2],
                          [NSNumber numberWithInteger:3],
                          nil];
    [_poinsNaviView loadViewWithMapIdList:mapIdList language:@"ko"];
}
```

3. Swift Library를 사용할 수 있도록 프로젝트 셋팅을 변경합니다. 
Project > Build Settings > Build Options > Always Embed Swift Standard Libraries : Yes
![](https://dl.dropboxusercontent.com/s/l6jlqnr03wal2u5/buildOptions.png)

4. 실행 후 PoinsNavi의 맵 화면을 볼 수 있습니다. 

* _시뮬레이터에서는 Mapview가 동작하지 않습니다._
