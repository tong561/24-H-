#ifndef _PID_H
#define _PID_H
typedef struct 
{
	
  float Kp;
	float Ki;
	float Kd;   // PID参
	float OUT_j;
  short error_j;     // 积分累计值
	short error;     //误差
	short error_last;//上次误差
	short error_Last_Last;//上上次误差
	short Out_Pu;    //输出
	
//	unsigned short out;
} PID;



extern float P_out,I_out,D_out,erro;
void PID_Init(PID *pid, float Kp, float Ki, float Kd );
short PID_JiSuan(PID *pid, short setpoint,short newpoint) ;
short PID_Increment(PID *pid, short setpoint,short newpoint);
short PID_XunJi(PID *pid,unsigned char BaiZheng);
short Limit_Output(short value,  short max);
//void number_chuli(PID *pid,unsigned char *arr);
void Munber_Count(PID *pid,unsigned char *arr);
unsigned char write_String(float number, unsigned char buffer[40]);
unsigned char write_cann(int a,unsigned char  *buffer);
unsigned int Cube(unsigned int Cu,unsigned int Be);
short PID_Zhixian(PID *pid, float temp_YAW);
#endif
































//初代
///***********************************************************************************

//功能：接收串口的数据ASCLL值，调整pid的值

//参数：pid定义的结构体，uint8_t arr[40]接收的数组

//***********************************************************************************/
//void number_chuli(PID *pid, uint8_t arr[40]) {
//    float kp = 0, ki = 0, kd = 0;
//    uint8_t index = 0; // 当前处理位置
//    uint8_t param_idx = 0; // 参数索引（0=Kp, 1=Ki, 2=Kd）
//    float current_param = 0.0; // 当前解析的参数值
//    uint8_t is_decimal = 0; // 标记是否进入小数部分
//    float decimal_factor = 1.0; // 小数位权因子（初始为1，小数部分为0.1, 0.01...）

//    while (index < 40 && arr[index] != '\n') 
//	{ // 遍历直到结束符或数组末尾
//        if (arr[index] == ',') 
//		{ // 遇到逗号，结束当前参数
//            switch (param_idx) 
//			{
//                case 0: kp = current_param; break;
//                case 1: ki = current_param; break;
//                case 2: kd = current_param; break;
//                default: return; // 超过3个参数，非法格式
//            }
//            param_idx++;
//            current_param = 0.0; // 重置当前参数
//            is_decimal = 0; // 重置小数标记
//            decimal_factor = 1.0;
//        } 
//		else if (arr[index] == '.') 
//		{ // 遇到小数点，进入小数部分
//            is_decimal = 1;
//        } 
//		else if (arr[index] >= '0' && arr[index] <= '9') 
//		{ // 数字字符处理
//            uint8_t digit = arr[index] - '0';
//            if (!is_decimal) 
//			{ // 整数部分：直接乘10累加
//                current_param = current_param * 10 + digit;
//            } 
//			else 
//			{ // 小数部分：乘以位权因子累加
//                decimal_factor /= 10; // 先更新位权（如第一个小数位是0.1，第二个是0.01）
//                current_param += digit * decimal_factor;
//            }
//        } 
//		else 
//		{ // 非法字符（非数字、逗号、小数点）
//            return; // 直接返回，不处理
//        }
//        index++;
//    }
//    // 处理最后一个参数（逗号后到\n之间的数字）
//    if (param_idx == 2 && index < 40) 
//	{ // 确保是第三个参数
//        kd = current_param;
//    } 
//	else if (param_idx < 2) 
//	{ // 参数不足
//        return;
//    }

//    // 赋值给PID结构体
//    pid->Kp = kp;
//    pid->Ki = ki;
//    pid->Kd = kd;
//}
