#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 4
#define DEV "/dev/ttySAC4"

static int sg_iFdCom[SIZE];

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