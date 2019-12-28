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