# PoinsNavi Framework for iOS

![swift](https://img.shields.io/badge/swift-3.0-orange.svg?style=flat)
![Platform](https://img.shields.io/cocoapods/p/LFAlertController.svg?style=flat)
> PoinsNavi는 실내 길안내용 View 기반의 라이브러리 입니다.

![](https://dl.dropboxusercontent.com/s/losspm0yxl099pg/launch.PNG)

# Contents
* [Requirements](#requirements)
* [Features](#features)
* [Other Frameworks](#other-frameworks)
* [Installation](#installation)
* [Usage](#usage)
  * [swift](#swift)
    * [View 생성 (Swift)](#view-생성-swift)
    * [지도보기 및 길찾기 (Swift)](#지도보기-및-길찾기-swift)
  * [Objective-C](#objective-c)
    * [View 생성 (Objective C)](#view-생성-objective-c)
    * [지도보기 및 길찾기 (Objective C)](#지도보기-및-길찾기-objective-c)

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
* [Toast-Swift](https://github.com/scalessec/Toast-Swift) : toast popup library

# Installation
1. **PoinsIPS.framework, PoinsNavi.framework, PoinsMapView.framework**를 프로젝트에 추가합니다.
2. [Other Frameworks](#other-frameworks) 를 프로젝트에 추가합니다. 
(또는 ExternalFrameworks폴더 내부의 빌드된 Framework들을 추가할 수 있습니다.)

![](https://dl.dropboxusercontent.com/s/ev1cif2a0efv0ih/add%20frameworks.png)

3. Poject > General > Embedded Binaries 에 1, 2번에서 추가한 framework들을 추가합니다.
![](https://dl.dropboxusercontent.com/s/1gskovjujvfucq8/Embedded%20Binaries.png)

4. Beacon을 통한 위치정보 사용을 위해 다음과 같이 설정을 추가합니다. <br>
 Project > Target > Info > Custom iOS Target Properties 로 이동 후 <br>
`+` 버튼으로 Privacy - Location Always Usage Description key를 추가합니다.
![](https://dl.dropboxusercontent.com/s/0co5zv7823no319/customProperties.png)

# Usage

## Swift

### View 생성 (Swift)

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

### 지도보기 및 길찾기 (Swift)

매장의 index 및 매장명으로 매장 바로가기 및 길찾기를 할 수 있습니다. 
1. 매장의 room index를 아는 경우

* 지도보기
```swift
poinsNaviView.findPosition(index: 6494, guide: false)
```
* 길찾기
```swift
poinsNaviView.findPosition(index: 6494, guide: true)
```

2. 매장명(POI명)을 아는 경우
동일한 매장명을 사용하는 경우 일치하는 첫번째 검색 결과를 사용합니다.

* 지도보기
```swift
poinsNaviView.findPosition(name: "코스메데코르테", guide: false)
```

* 길찾기
```swift
poinsNaviView.findPosition(name: "코스메데코르테", guide: true)
```

### Framework 버전 확인

다음 코드로 PoinsNavi Framework의 버전을 확인할 수 있습니다.
```swift
if let sdkVersion = Bundle(for: PoinsNaviView.self).infoDictionary?["CFBundleVersion"] {
    // sdkVersion is available here
}
```

## Objective-C

### View 생성 (Objective C)

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

언어는 다음 4가지로 설정 가능합니다. ('en', 'zh', 'ja', 'ko')
language가 nil일 경우 시스템 언어를 사용합니다. 
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

### 지도보기 및 길찾기 (Objective C)

매장의 index 및 매장명으로 매장 바로가기 및 길찾기를 할 수 있습니다. 
1. 매장의 room index를 아는 경우

* 지도보기
```ObjC
[_poinsNaviView findPositionWithIndex:6494 guide:false];
```
* 길찾기
```ObjC
[_poinsNaviView findPositionWithIndex:6494 guide:true];
```

2. 매장명(POI명)을 아는 경우
동일한 매장명을 사용하는 경우 일치하는 첫번째 검색 결과를 사용합니다.

* 지도보기
```ObjC
[_poinsNaviView findPositionWithName:@"코스메데코르테" guide:false];
```

* 길찾기
```ObjC
[_poinsNaviView findPositionWithName:@"코스메데코르테" guide:true];
```

* _시뮬레이터에서는 Mapview가 동작하지 않습니다._
* _맵의 크기에 따라 로딩시간이 오래 걸릴 수 있어 맵과의 전환이 잦은 시나리오를 사용할 경우 맵뷰 위에 UI를 작성한 후 View전환을 하는 형태로 개발하는 것을 권장합니다._

* 상세 기능 문의 및 요청 사항은 bonhyuk2@coordispace.com로 연락주시기 바랍니다.
