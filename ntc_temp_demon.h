#define NTC_ADC_ARRAY_NUM	92		//-21~+70度温度表一共92数据
#define TEMPER_LEVEL		21 		//以21来区分温度零下和零上分界点

#define TEMPER_MAX			9999  //大于70oC
#define	TEMPER_MIN			684		//小于-20oC
#define ERROR_TEMP_VAL		203 //错误值


//MF52A1_104F3950B Table表modify xudonghai 2016-05-06
const unsigned int ntc_table[NTC_ADC_ARRAY_NUM] = {

    647,                            //-21
	684, 723, 763, 805, 849,		//-20~-16
	895, 942, 992, 1044, 1097,		//-15~-11
	1153, 1211, 1271, 1333, 1398, 		//-10~-6
	1465, 1534, 1606, 1680, 1757,		//-5~-1

	1836,	//0
	1917, 2001, 2088, 2177, 2269, 			//1-5
	2363, 2460, 2559, 2661, 2753,			//6-10
	2872, 2981, 3092, 3206, 3323,			//11-15
	3441, 3562, 3685, 3809, 3936,			//16-20
	4065, 4196, 4328, 4462, 4598,			//21-25
	4735, 4873, 5012, 5153, 5294,		//26-30
	5437, 5580, 5724, 5868, 6013,		//31-35
	6158, 6303, 6448, 6593, 6738,		//36-40
	6883, 7027, 7170, 7313, 7455,		//41-45
	7596, 7736, 7875, 8013, 8154,		//46-50
	8284, 8418, 8550, 8681, 8810,		//51-55
	8937, 9063, 9187, 9308, 9428,		//56-60
	9547, 9663, 9777, 9889, 9999,		//61-65
	10107, 10213, 10317, 10419, 10518,		//66-70
};
//Vt=3.3*R1/R1+Rt+R2 * 1024    Dadc = (Vt *1024) *10(放大10倍)