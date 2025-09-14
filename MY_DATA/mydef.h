#ifndef _MYDEF_H_
#define _MYDEF_H_


#define SAVE_DATA_ADDR    0x08018800    //数据内部存储起始地址
#define SAVE_PROGRAM_ADDR 0x08019000	//程序内部存储起始地址

typedef enum
{
	MY_OK,								//成功
	MY_ERR								//失败
}ResultState;							//状态




//数据类型定义
typedef unsigned char uint8;		//无符号8位
typedef unsigned short uint16;		//无符号16位
typedef unsigned uint32;		//无符号32位
typedef unsigned long long uint64;		//无符号64位

typedef char int8;					//有符号8位
typedef short int16;				//有符号16位
typedef int int32;					//有符号32位
typedef long long int64;					//有符号64位


typedef struct
{
    unsigned char  b0:1; 
    unsigned char  b1:1; 
    unsigned char  b2:1; 
    unsigned char  b3:1; 
    unsigned char  b4:1;
    unsigned char  b5:1;
    unsigned char  b6:1;
    unsigned char  b7:1;
} BIT8;


#define CLOSE_TIME 10				//熄灭屏幕时间，单位秒
#define PASSWORD 933				//解锁密码值
#define CMD_PASSWORD "1882598"		//命令输入密码值

#endif

