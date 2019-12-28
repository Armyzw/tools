#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#define SIZE 4
#define DEV "/dev/ttySAC4"

using namespace std;

static int sg_iFdCom[SIZE];

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
	sg_iFdCom[0] = open(DEV, O_REWR | O_NOCTTY);
	if(sg_iFdCom[0] < 1){
		printf("Open /dev/ttySAC4 failed\n");
	}else {
		InitCom(sg_iaFdCom[0], B115200, 0); // Baudrate by the device
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
		if(sg_iFdCom(0)>0)
		{
			(void)close(sg_iFdCom[0]);
			sg_iFdCom[0]=0;
		}
	#endif 
}
int main(void)
{
	OpenDev();
	while(1)
	{
		WriteDataByUart(sg_iaFdCom[0],"1",1);
		delay(10);
	}
}


