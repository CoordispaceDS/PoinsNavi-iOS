//
//  ViewController.swift
//  PoinsNaviExample
//
//  Created by jeong on 2017. 9. 7..
//  Copyright © 2017년 coordispace. All rights reserved.
//

import UIKit
import PoinsNavi

class ViewController: UIViewController {

    @IBOutlet weak var poinsNaviView: PoinsNaviView!
    override func viewDidLoad() {
        super.viewDidLoad()
        poinsNaviView.loadView(mapIdList: [38,39,37])
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

