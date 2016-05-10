/**********************************************
*Desc	: 按校准值调整温度差异表
*Param	: n_adc_val--ADC获取值
*Ret		: other--成功；0--失败
*Author	: xudonghai	2016-05-06
***********************************************/
float Fur_Temp_Differe_Val(unsigned int n_adc_val)
{
	float Col_TempVal = 0.0;

	if(n_adc_val >= 864 && n_adc_val < 1153) ///-20oC~-10oC温度差异
	{
		Col_TempVal = 2.0;

		return Col_TempVal;
	}
	else if(n_adc_val >= 1153 && n_adc_val < 1836) ///-10oC~-0oC温度差异
	{
		Col_TempVal = 1.0;

		return Col_TempVal;
	}
	else if(n_adc_val >= 1836 && n_adc_val < 2753) ///0oC~+10oC温度差异
	{
		Col_TempVal = 2.6;

		return Col_TempVal;
	}
	else if(n_adc_val >= 2753 && n_adc_val < 5294) ///+10oC~+30oC温度差异
	{
		Col_TempVal = 2.5;

		return Col_TempVal;
	}
	else if(n_adc_val >= 5294 && n_adc_val < 8154) ///+30oC~+50oC温度差异
	{
		Col_TempVal = 1.8;

		return Col_TempVal;
	}
	else if(n_adc_val >= 8154 && n_adc_val < 10518) ///+50oC~+70oC温度差异
	{
		Col_TempVal = 0.9;

		return Col_TempVal;
	}
	else
	{
		; //todo
	}

	return 0.0;

}


/****************************************************
*Desc	: 获取温度线性值
*Param	: adc_val--ADC获取值，index--R-T表索引值
*Ret		: other--成功；0--失败
*Author	: xudonghai	2016-05-06
******************************************************/
unsigned int
Fur_Temp_Line_Inser(unsigned int adc_val, unsigned int index)
{
	int x, y, x1, y1, y2, temper;
	float devia, Temp_ColVal = 0.0;

	x1 = adc_val;
	y1 = ntc_table[index - 1];
	y2 = ntc_table[index + 1];

	x = (x1 - y1);
	y = (y2 - y1);

	devia = (float)(x) / (float)(y);

	Temp_ColVal = Fur_Temp_Differe_Val(adc_val); //温度校准值

	//temper = ((float)index  + devia - TEMPER_LEVEL - Temp_ColVal) * 10; //modify xudonghai 2016-05-06

	temper = ((float)index  + devia - TEMPER_LEVEL) * 10; //modify xudonghai 2016-05-06

	printf("[15sx_Driver]adc_val:%d, index:%d, temper:%d\n", adc_val, index, temper);

	return temper;

}

/**********************************************
*Desc	: 获取温度值程序
*Param	: void
*Ret		: -20~100--成功；203--失败
*Author	: xudonghai	2015-09-24
***********************************************/
int
Fur_Get_Temp(unsigned int adc_val)
{
	int i = 0;
	int temp = 0;

	for(i = 1; i < NTC_ADC_ARRAY_NUM; i++)
	{
		if((ntc_table[i-1] < adc_val) && (ntc_table[i+1] > adc_val) && (adc_val != 0))
		{
			temp = i;

			if(temp < TEMPER_LEVEL)			//	-20~-1
			{
				//temp = (temp - TEMPER_LEVEL - 1) * 10;	//	加负温度标志 * 10

				//return temp;
				return Fur_Temp_Line_Inser(adc_val, temp); //modify xudonghai 2016-05-09 //添加温度线性表
			}
			else					//	0~100
			{
				return Fur_Temp_Line_Inser(adc_val, temp);
			}
		}
		else if(adc_val < TEMPER_MIN && adc_val > 0)
		{
			temp = -200; //-20 oC * 10

			return temp;
		}
		else if(adc_val > TEMPER_MAX)
		{
			temp = 700;		//70 oC * 10

			return temp;
		}
		else
		{
			;
		}
	}

	return ERROR_TEMP_VAL;
}

int main(void)
{
    int ret = 0;
    float RetVal = 0.0;

    //unsigned int n_adc_val = 684; //-20
    //unsigned int n_adc_val = 723; //-19
    //unsigned int n_adc_val = 1757; //-1
  //unsigned int n_adc_val = 1836; //0
   unsigned int n_adc_val = 1917; //+1
   //unsigned int n_adc_val = 2088; //+2


    ret = Fur_Get_Temp(n_adc_val);
    RetVal = ret;

    printf("Temp RetVal:%f\n", RetVal / 10.0);

    return 0;
}
