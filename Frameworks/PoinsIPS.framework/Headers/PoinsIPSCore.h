#ifndef __POINS_IPS__
#define __POINS_IPS__

#define POINS_NAVIGATION


#define TAG_DBDATA_INIT_YES 1001
#define TAG_DBDATA_INIT_NO 1002

#define byte int
#define boolean _Bool
#define bool _Bool
//#define false 0
//#define true  1
#define String char*
#define ARRAY_SIZE 200          // 200
#define PARTICLE_SIZE 2000      // 2000


typedef struct SensorData SensorData;
struct SensorData {
    
    float 	AccXYZ[3]; 	// Accelerometer raw data
    float 	GrvXYZ[3]; 	// Gravity force data
    
    float 	UGyrXYZ[6]; 	// GyroScope raw data
    float 	CGyrXYZ[3]; 	// GyroScope raw data
    long long int	TimeStampGyr[2];		// Time stamp of GyroScope
    
    float	UMgnXYZ[6]; 	// Magnetometer raw data (XYZ) in Body frame
    float	CMgnXYZ[4]; 	// Calibrated Magnetometer data by android API
    int 	MgnAccuracy;
    
    boolean isGotUMgnXYZ ;
    boolean isGotUGyrXYZ ;
    boolean isGotCGyrXYZ ;
    boolean isGotGrvXYZ ;
};


typedef struct ServerControlData ServerControlData;
struct ServerControlData {
    int MgnLikelihoodOption;	// = MGN_LIKELIHOOD_T; 	// MGN_LIKELIHOOD_NO=0 : MGN_LIKELIHOOD_T=1 : MGN_LIKELIHOOD_HV=2 : MGN_LIKELIHOOD_THV=3  : : MGN_LIKELIHOOD_H=4
    
    int Ref_P_Particle_Num;		// = 57;      			// if 3d :|  9 -> 0.71m | 21 -> 1.12m | 37 -> 1.58m | 57 -> 2.06m |
    // if 2d :|             | 5  -> 1.00m |  7 -> 1.50m |  9 -> 2.00m |
    int P_S_Generation_Num;		// = 57 ; 				// 		  |  9 -> 0.71m | 21 -> 1.12m | 37 -> 1.58m | 57 -> 2.06m |
    
    float P_Selection_Criteria;	// = 0.95f;
    float MgnSigma;				// = 6.50f;  			//  3.5f  // CIO
    float WifiSigma;			// = 17.0f;				//12.7f
    float BleSigma;				// = 17.0f;
    
    float MgnWeight;			// = 1.0f;  			//
    float WifiWeight;			// = 2.0f;				// 4
    float BleWeight;			// = 2.0f;				// 4
    bool isMGN50pUsing;		// = false;
};


typedef struct WifiData WifiData;
struct WifiData {

    int NumAP; 							// Number of Scanned Wifi AP (MAX:100)
    int i_level[ARRAY_SIZE]; 		// Wifi Level of 100 higher Level
    String S_BSSID[ARRAY_SIZE]; 	// String Type of Wifi BSSID
    String S_SSID[ARRAY_SIZE]; 	// String Type of Wifi SSID
    long long int L_BSSID[ARRAY_SIZE];
    bool is5GHz[ARRAY_SIZE];
    bool Wifi_Vector_chaged; 	// if Wifi Vector is changed, then it's true
    bool Wifi_Vector_New; 	// if Wifi Vector is new, then it's true
    bool Wifi_Vector_1stInput;
};

typedef struct BleData BleData;
struct BleData {
    int  	NumBeacon;   							// Number of Scanned Wifi AP  (MAX:100)
    int    i_level[ARRAY_SIZE];	// Wifi Level of 100 higher Level
    long long int l_BSSID[ARRAY_SIZE];  // String Type of Wifi BSSID
    bool 	Beacon_Vector_chaged ;		// if Wifi Vector is changed, then it's true
    bool 	Beacon_Vector_New ;			// if Wifi Vector is new, then it's true
    bool 	Beacon_Vector_1stInput;
};


typedef struct PositionData PositionData;
struct PositionData {
    int   L;   									// layer of Position
    float X; 									// X coordinate of Position
    float Y; 									// X coordinate of Position
    int	  mode;
    
#ifdef POINS_NAVIGATION
    float H; 									// Heading Angle
    float A;									// Accuracy
    float Pitch; 								// Pitch Angle
    float Roll; 								// Roll Angle
    float Qtrn[4];
#endif

};

typedef struct PositioningData PositioningData;
struct PositioningData {
    
    int 	NumWifiAp;							// Number of WiFi Ap
    long long int	L_BSSID[ARRAY_SIZE];						// long Value of WiFi BSSID
    int     b_level[ARRAY_SIZE];						// Level of WiFi Signal
    /**/int 	b_level_M[ARRAY_SIZE]; // Level of WiFi Signal
    bool		B_WifiIs5GHz[ARRAY_SIZE];
    bool  isEndResetVariable;				// is Variable Reseted for Positioning
    
#ifdef POINS_NAVIGATION
    // for Main Activity
    float 	Runtime;							// POINS Runtime
    bool  isReseted;							// is POINS Reseted
    bool  isNeedPositionInitializing;        // is POINS Reseted
    bool  isEndGetMgnCailbData;				// is get Sensor Data for Magnetometer Calibration
    
    bool  isEndResetVariable_previous;       // is Variable Reseted for Positioning at previous time
    bool  isEndPositionInitializing;			// is Position Initializing end
    bool  isEndPositionInitializing_Previous;
    bool  isTrackingMode;
    
    /**/bool isTimeToSaveUserCalibrationData;	// added Code 2014.12.22 by HIO (ver.061) // revised Code 2015.01.12 by HIO (ver.061)
    /**/bool isMeasureState;						// added Code 2014.12.22 by HIO (ver.061)
    
    float 	InitializingTime;					// Position Initializing Time
    
    float 	MgnBias[3];                     	// Magnetometer Bias
    float   GyrBias[3];                 		// Gyroscope Bias Error, added 2014.10.27
    float   GyrCalib[4];						// Bias Error Calibrated Gyroscope Data,  added 2014.10.27
    
    float 	JulianYear;							//added 2014.10.25
    
    // for Magnetometer Calibration
    float 	Gyro_LPfiltered;					// Low-Pass Filtered Gyroscope Sensor data
    /**/float Acc_LPfiltered[2];					// added Code 2014.12.22 by HIO (ver.061)
    
    // for Measurement
    float 	MgnCalib[4];						// Bias Calibrated Magnetometer Data
    float 	MgnN_HVA[3];						// Bias Calibrated Magnetometer Data in Navigation frame
    
    // for SLAM Measurement
    //    bool  isStep4SLAM;						// is Step detected for SLAM
    float 	StepYaw[5];							// Step Yaw Angles at 5 time steps
    float 	StepLength;							// Step Length
    float	StepT[6];            				// Step Time at 3 time steps
    /**/float 	StepTime[6]; 						// Step Time at 6 time steps// added Code 2014.12.22 by HIO (ver.061)
    
    // for Similarity Checking
    float Wifi_Similarity;
    float Mgn_Similarity;
    float PDR_Similarity;
    float Poins_Similarity;
#endif

};

typedef struct PositioningT PositioningT;
struct PositioningT {

    //for TestDataView, ON
#ifdef POINS_NAVIGATION
    
    int		P_GridL;
    int 	P_Particle_Num;
    int 	P_Particle_Num_net;
    
    float   TUpDataTime;
    
    int 	MotionModes[10];
    int 	Num_ConSteps[10];
    int  	P_Particle_ID[2000];
    int 	NodeIDs_Position_linked[2];
    
    float	StepDT;
    float	Mgn_HorizontalStrength;
    
    float	AccCalib[3];
    float   Gravity[3];
    float 	StepHeading[10];
    float	StepLengths[10]; 			// added Code 2014.12.28 by HIO (ver.061)
    float 	VelVariances[10];
    float 	MaxAccs[10];
    float 	MinAccs[10];
    float	P_Particle_Similarity[2000];   // = new float[P_Particle_Num]; //10
    float 	P_RPY[3]; //	Roll Pitch Yaw Angle
    
#endif
    
    float 	threshold_WifiSimilarity;
};


typedef struct MgnCalibration MgnCalibration;
struct MgnCalibration {
    
    bool  	isStartFuction;
    bool 	isStartMgnClab;
    bool		isFinishMgnClab;
    bool		isEndGetMgnCailbData_previous;
    bool  	isForcedEndMgnCailb;
    bool  	isStoreMgnCaliDateToDB;
    
    float		NoMotionfromGyro[2];
    float		NoMotion_T;
    float 		CailbratedAccurcy;
    
    float		MgnDataMatrix[1000][3]; // And : 1000
    int  		MgnData_i;
    int			Num_getMgnCalibData;
    
};

typedef struct DbData DbData;
struct DbData {
    

    /* ************************************************
     *
     * 0. SQLite DB name : version.db
     *
     * ************************************************/
    
    /* 0.1. SQLite table name : tVersion  */
    int  	Version; 	// 0 : IPIN Version
    
    
    /* ************************************************
     *
     * 1. SQLite DB name : mapconfig.db
     *
     * ************************************************/
    
    /* 1.0. SQLite table name : tMapInfor  */
    String 	IDX;					// IDX of Indoor Map
    
#ifdef POINS_NAVIGATION
    int  	LocationID; 			// 0 : Location ID
    int 	Ver_Map;  				// 1 : Version of Map
#endif
    
    int 	Num_GridL;  			// 2 : Number of Layer
    
#ifdef POINS_NAVIGATION
    int 	Num_GridX;  			// 3 : size of Grid X
    int 	Num_GridY;  			// 4 : size of Grid Y
    int 	OriginX_OnTheMapImage;	// 5 : OriginX On The Map Image [pixel]
    int 	OriginY_OnTheMapImage;  // 6 : OriginY On The Ma pImage [pixel]
    double 	Lati_Map;  				// 7 : Latitude of Location
    double 	Longi_Map;  			// 8 : Longitude of Location
    float	Decli_Map;  			// 9 : Declination of Map wrt Geodetic North
    float	Ratio_Map;  			// 10 : Ratio of Map Image [pixel/m]
    float 	dx_Grid;  				// 11 : size of a Grid in X direction
    float 	dy_Grid;  				// 12 :size of a Grid Y direction
    String 	LocationName;  			// 13 : Location Name
    int 	maxLayerLevel; 			// 14 : 최고 층수
    int 	minLayerLevel; 			// 15 : 최저 층수
    
    /* ************************************************
     *
     * 2. SQLite DB name : mapdata.db
     *
     * ************************************************/
    
    
    /* 2.1. SQLite   table : tNodeInfor */
    short	*Num_NodeConected;	// 0 : Number of Nodes connected the Node of ID[]
#endif
    
    int		*Node_Layer;			// 1 : Layer of Node
    float	**Node_PositionXY;	// 2~3 : Position X & Y of Node
    
#ifdef POINS_NAVIGATION
    int		*isWirelessNode; // PoinsVer.1.0;
    
    /* 2.2 SQLite table name : tLinkInfor */
    int		*ID_NodeConected;	// 0 : ID of Nodes connected the Node of ID[]
    
    /* 2.3. SQLite table name : tMeasure */
    short 	**MgnTHVA; 		//  0 ~ 3 : Magnetic field Measurement ([id][0] : total, [id][1] : Horizontal, [id][2] : Vertical, [id][3] : Declination Angle)
#endif
    
    /* 2.4. SQLite table name : tWifiRefBSSID */
    
    
    int 	*NodeID;
    long long int	**L_WifiBSSID; // PoinsVer.1.0;
    int 	**I_WifiRSSI;  // PoinsVer.1.0;
    int		Num_WifiNode;    // PoinsVer.1.0;
    
    long long int	**L_BleBSSID; // added 2015.05.03 by Hio
    int 	**I_BleRSSI;  // added 2015.05.03 by Hio
    int		Num_BleNode;    // added 2015.05.03 by Hio
    
#ifdef POINS_NAVIGATION
    /* 2.6. SQLite table name : tMgnCali */
    float 	MgnBiasXYZ[3];  		// 0 ~ 2 : Magnetometer Bias X, Y & Z  axes
    
    float 	MgnCaliAccu;  		// 3 : Magnetometer Calibration Accuracy
#endif
    
    float 	WifiAlpha; 			// added Code 2014.01.12 by HIO (ver.061)
    
    float 	WifiBeta;			// added Code 2014.01.12 by HIO (ver.061)
    
    float 	BleAlpha; 			// added Code 2014.01.12 by HIO (ver.061)
    
    float 	BleBeta;			// added Code 2014.01.12 by HIO (ver.061)
    
    
    /* Computational Variable for Positioning  */
    
#ifdef POINS_NAVIGATION
    int 	Num_Node;  			// notDb : 계산 : Number of Nodes  (데이터 갯수로 계산 가능)
    
    int 	Num_MapDataID;  	// notDb : 계산 : size of data ID  (데이터 갯수로 계산 가능)
    
    int		Num_WifiData;   	// notDb : 측량 : Number of Wifi Data  (Measurement에 작성하여 DB서버로 전송) (데이터 갯수로 계산 가능)
    
    int		Num_LinkInfor;		// notDb : 측량 : Number of Wifi Data  (Measurement에 작성하여 DB서버로 전송) (데이터 갯수로 계산 가능)
    
    
    int		*NodeID2MapDataID;	// notDb : ID of Nodes connected the Node of ID[]
    
    int		*StartID_LinkInfor;	// notDb : Start ID of Link Information Data
    
    int		***Grid2ID;   			// notDb :Converting form [Layer][GridX][GridY] to MapData ID
    
    int 	**ID2LinkedNodeID;// notDb : Converting from MapData ID to Linked Node ID #1 [id][0] & Linked Node ID #2 [id][1]
    
    int 	**GridLXY;		// notDb : Converting from MapData ID to Grid Layer[id][0] , Grid X [id][1], Grid Y [id][2]
    
    float 	**PositionXY;		// notDb : Converting from MapData ID to  Position X [id][0] & Position Y [id][1]
    
    float 	*NodeDistence;		// notDb : Distance of  between the connected Nodes and the Node of ID[]
#endif
    
    boolean 	isEndGetDbDatafromDB;
    boolean 	isEndGetDbDatafromDB_previous;
    boolean 	isEndGetDbDatafromServer;
    boolean 	isEndGetDbDatafromServer_previous;
};

extern SensorData          mSensorData;
extern WifiData            mWifiData;
extern PositionData        mPositionData;
extern DbData				mDbData;
extern PositioningData		mPositioningData;
extern MgnCalibration		mMgnCalibration;
//extern  Positioning			mPositioning;
extern PositioningT			mPositioningT;
extern BleData         		mBleData;
extern ServerControlData	mServerControlData;

extern int DbDataInitializeTAG;
extern bool isDbDataSetinC;
extern bool isServerControlDataSetinC;

/**********************************************************************
 * API
 **********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif 
    
    void IPSSignalOption(bool wifiUsed, bool bleUsed);
    void IPSMgnInitialize(MgnCalibration *pMgnCalibration, DbData *pDbData, SensorData *pSensorData, PositioningData *pPositioningData);
    void IPSGetMgnBias(MgnCalibration *pMgnCalibration, DbData *pDbData, SensorData *pSensorData, PositioningData *pPositioningData);
    void IPSResetVariable(SensorData *pSensorData, WifiData *pWifiData, BleData *pBleData, PositionData *pPositionData, DbData *pDbData,
                          ServerControlData *pServerControlData, PositioningData *pPositioningData, PositioningT *pPositioningT);
    void IPSInitializeDBData(DbData *pDbData);
    void IPSPositioningMain(SensorData *pSensorData, WifiData *pWifiData, BleData *pBleData,
                            PositionData *pPositionData, DbData *pDbData, ServerControlData *pServerControlData,
                            PositioningData *pPositioningData, PositioningT *pPositioningT);
    void IPSPositioningMainTEST(SensorData *pSensorData, WifiData *pWifiData, BleData *pBleData,
                                PositionData *pPositionData, DbData *pDbData, ServerControlData *pServerControlData,
                                PositioningData *pPositioningData, PositioningT *pPositioningT);

#ifdef __cplusplus
};
#endif


#endif // __POINS_IPS__
