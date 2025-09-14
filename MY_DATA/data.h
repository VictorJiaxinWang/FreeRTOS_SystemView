#ifndef _DATA_H_
#define _DATA_H_
#include "mydef.h"
//#include "stmflash.h"
#include "string.h"

typedef struct											
{
	uint8 configedFlag;						//是否已经配置
	uint8 localDate[6];						//配置日期
	uint8 mac[6];							/*MAC地址*/
	uint8 lip[4];							/*local IP本地IP地址*/
	uint8 sub[4];							/*子网掩码*/
	uint8 gw[4];							/*网关*/	
	uint8 dns[4];							/*DNS服务器地址*/
	uint8 rip[4];							/*remote IP远程IP地址*/
	uint16 port485;							//485端口
	uint8 id4851;							//485从机一ID
	uint8 id4852;							//485从机二ID
	uint8 canLimit;							//CAN限定位
	uint8 canFilter;						//CAN过滤位
	uint8 slaveId[20];						//从机ID		
	uint8 slaveState[20];					//从机状态
}ConfigValueTypeDef;						//配置消息


typedef struct
{
	uint8 ProgVersion[5];						//版本号		
	uint8 ProgSize[7];							//字节数
	uint8 progMd5[33];							//MD5值
	uint8 progDate[20];							//更新日期
	ConfigValueTypeDef configValueTypeDef;		//配置数据
}InnerSaveTypeDef;

typedef enum
{
	size_12=12,
	size_16=16,
	size_24=24
}OledSize;		//OLED字体尺寸

typedef struct
{
	uint8 row;									//显示行
	uint8 col;									//显示列
	OledSize size;									//字体大小
	uint8 oledShowData[17];		 				//OLED显示数据
}OledShowTypeDef;            	 			    //OLED控制结构体


typedef enum
{
	no_key,										//无按键
	up_key,										//上键
	down_key,									//下键
	ok_key,										//确定
	esc_key,									//退出
	//下面是虚拟按键
	open_screen,								//打开屏幕
	close_screen,								//熄灭屏幕
}KeyEnum;										//按键枚举
typedef enum
{
	subMenu,
	noSubMenu
}MenuIsFirsr;									//菜单首页
typedef enum
{
	firstSubMenu,
	secondSubMenu,
	thirdSubMenu,
	fourthSubMenu,
	maxSubMenu
}MenuPoint;										//子菜单
typedef enum
{
	firstPage,
	secondPage,
	maxPage
}MenuPage;
typedef struct
{
	MenuIsFirsr isSubMenu;								//是否在首页
	MenuPoint pointSubMenu;								//首页第几个菜单
	MenuPage menuPage;
}MenuInfoTypeDef;								//菜单操作结构体


extern InnerSaveTypeDef innerSaveTypeDef;//内部存储信息


extern const uint8 menu_row_1[];				//华达川科技
extern const uint8 password[]; 					//密码键盘
extern const uint8 passwordInput1[];	//密码键盘输入一位
extern const uint8 passwordInput2[];	//密码键盘输入二位
extern const uint8 passwordInput3[];	//密码键盘输入三位
extern const uint8 passwordInput4[];   	//密码键盘输入四位
extern const uint8 passwordError[];	//密码键盘输入密码错误

//主菜单
extern const uint8 programInfo[];		//程序信息
extern const uint8 bootInfo[];		//程序信息
extern const uint8 slaveState[];		//从机信息
extern const uint8 canSetInfo[];		//CAN信息
extern const uint8 inputTest[];		//输入测试
extern const uint8 outputTest[];	//输出测试
extern const uint8 startConfig[];		//保留菜单
extern const uint8 netInfo[];	    //保留菜单
extern const uint8 point[];			//指针
extern const uint8 nullPoint[];     //空指针

void read_parameter(void);
#endif


