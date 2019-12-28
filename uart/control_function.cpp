#include <iostream>

#include "car_head.h"


/*将int转成16进制字符串*/
/*string dec2hex(int i) //将int转成16进制字符串
{
	stringstream ioss; //定义字符串流
	string s_temp; //存放转化后字符
	ioss << setiosflags(ios::uppercase) << hex << i; //以十六制(大写)形式输出
	//ioss << resetiosflags(ios::uppercase) << hex << i; //以十六制(小写)形式输出//取消大写的设置
	ioss >> s_temp;
	return s_temp;
}*/
/*十六进制转Ascii*/
/*unsigned char HexToChar(unsigned char bChar)
{
	if((bChar>=0x30)&&(bChar<=0x39))
	{
		bChar -= 0x30;
	}
	else if((bChar>=0x41)&&(bChar<=0x46)) // Capital
	{
		bChar -= 0x37;
	}
	else if((bChar>=0x61)&&(bChar<=0x66)) //littlecase
	{
		bChar -= 0x57;
	}
	else 
	{
		bChar = 0xff;
	}
	return bChar;
}
*/

static void InitCom(int iFd, unsigned int dwBaudrate, unsigned char ucVerify)
{
    struct termios sTermios;
    memset(&sTermios,0,sizeof(sTermios));       //清空串口设置结构体
    sTermios.c_cflag = CLOCAL | CREAD; //CLOCAL:本地连接, CREAD:允许接收数据

    (void)cfsetispeed(&sTermios,dwBaudrate);
    (void)cfsetospeed(&sTermios,dwBaudrate);
	
    if (ucVerify>0){
        sTermios.c_cflag |= PARENB;       //Enable parity bit
        if (ucVerify==1){
            sTermios.c_cflag |= PARODD;   //Use odd parity instead of even
        }else{
            sTermios.c_cflag &= ~PARODD;  //Use even parity instead of odd
       	}
    }else{
		sTermios.c_cflag &=~ PARENB;      //Disable parity bit
	}
	
    sTermios.c_cflag &= ~CSTOPB;  		// 1 stop bits 
    sTermios.c_cflag &= ~CSIZE;       // Mask the character size bits 
    sTermios.c_cflag |= CS8;      	// Select 8 data bits 
    //不处理，原始数据输入
    sTermios.c_lflag = 0;
    //INPCK   : 奇偶校验检查    
    sTermios.c_iflag = INPCK;
    //不处理，原始数据输出
    sTermios.c_oflag = 0;     

    (void)tcflush(iFd, TCIFLUSH);
    (void)tcsetattr(iFd,TCSANOW,&sTermios);
}

/* 这是初始化串口 */
static void OpenDev(void)
{
	sg_iFdCom[0] = open(DEV, O_RDWR | O_NOCTTY);
	if(sg_iFdCom[0] < 1){
		printf("Open /dev/ttySAC4 failed\n");
	}else {
		InitCom(sg_iFdCom[0], B9600, 0); // Baudrate by the device
	}
}

/* 往串口里面写文件的函数 */
int WriteDataByUart(int iFd, const char *buffer, int len)
{
	int n;
	n = write(iFd, buffer, len);
	return n;
}

/* 从串口里面读数据 */
int ReadDataByUart(int iFd, char *buffer, int len)
{
	int n;
	n = read(iFd, buffer, len);
	return n;
}

/*关闭串口*/
static void CloseDev(void)
{
	int i = 0;
	#if 0
		for(i=0;i<SIZE;i++)
		{
			if(sg_iFdCom[1]>0)
			{
				(void)colse(sg_iFdCom[1]);
				sg_iFdCom[1]=0;
			}
		}
	#else
		if(sg_iFdCom[0]>0)
		{
			(void)close(sg_iFdCom[0]);
			sg_iFdCom[0]=0;
		}
	#endif 
}


unsigned char HexToChar(unsigned char bChar)
{
	if((bChar>=0x30)&&(bChar<=0x39))
	{
		bChar -= 0x30;
	}
	else if((bChar>=0x41)&&(bChar<=0x46)) // Capital
	{
		bChar -= 0x37;
	}
	else if((bChar>=0x61)&&(bChar<=0x66)) //littlecase
	{
		bChar -= 0x57;
	}
	else 
	{
		bChar = 0xff;
	}
	return bChar;
}

/*计算发送数据*/
/*int calculate_send_data(int commandl,int speedl,int commandr,int speedr)
{
	int address = 130;
	int check_digitl;
	int check_digitr;
	string address_str;
	string commandl_str;
	string speedl_str;
	string check_digitl_str;
	string commandr_str;
	string speedr_str;
	string check_digitr_str;
	string send_data_str;

	char *address_char;
	char *commandl_char;
	char *speedl_char;
	char *check_digitl_char;
	char *commandr_char;
	char *speedr_char;
	char *check_digitr_char;
	char *send_data_char;

	check_digitl = ((address + commandl + speedl) & 127);
	check_digitr = ((address + commandr + speedr) & 127);
	*/
	/*将int型转换成十六进制的char后转换成Ascii*/
	/*address_str=dec2hex(address);
send_data = (char*)send_data_str.data();
	commandl_str=dec2hex(commandl);
send_data = (char*)send_data_str.data();
	speedl_str=dec2hex(speedl);
send_data = (char*)send_data_str.data();
	check_digitl_str=dec2hex(check_digitl);
send_data = (char*)send_data_str.data();

	commandr_str=dec2hex(commandr);
send_data = (char*)send_data_str.data();
	speedr_str=dec2hex(speedr);
send_data = (char*)send_data_str.data();
	check_digitr_str=dec2hex(check_digitr);
send_data = (char*)send_data_str.data();
	*/
	/****************************************/
/*
	send_data_str = address_str + commandl_str + speedl_str + check_digitl_str + address_str + commandr_str + speedr_str + check_digitr_str;
	send_data = (char*)send_data_str.data();
	return 0;
	
}*/

/**************************************/
/*前进：速度40:"8200282a8204282e"
/**************************************/
int main(void)
{
	OpenDev();
	char go_data[16]={0x82,0x00,0x28,0x2a,0x82,0x04,0x28,0x2e};
	//char *go=go_data;
	char stop_data[16]={0x82,0x00,0x00,0x02,0x82,0x04,0x00,0x06};
	while(1)
	{
		//calculate_send_data(0,40,1,40);
		WriteDataByUart(sg_iFdCom[0],go_data,8);
		sleep(10);

		//calculate_send_data(0,0,1,0);
		WriteDataByUart(sg_iFdCom[0],stop_data,8);
		sleep(13);

		
	}
}
