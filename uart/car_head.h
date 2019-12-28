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
#include <sstream>
#include <iomanip>

#define SIZE 4
#define DEV "/dev/ttySAC4"

using namespace std;
static int sg_iFdCom[SIZE];

const char *send_data;

static void InitCom(int iFd, unsigned int dwBaudrate, unsigned char ucVerify);
/* 这是初始化串口 */
static void OpenDev(void);
/* 往串口里面写文件的函数 */
int WriteDataByUart(int iFd, const char *buffer, int len);
/* 从串口里面读数据 */
int ReadDataByUart(int iFd, char *buffer, int len);
/*关闭串口*/
static void CloseDev(void);
/*计算发送数据函数*/
int calculate_send_data(int commandl,int speedl,int commandr,int speedr);
