#include "data.h"

InnerSaveTypeDef innerSaveTypeDef;//内部存储信息


const uint8 menu_row_1[]="   HDC Company  "; //华达川科技
const uint8 password[] = "password:----";	//密码键盘
const uint8 passwordInput1[] = "password:*---";	//密码键盘输入一位
const uint8 passwordInput2[] = "password:**--";	//密码键盘输入二位
const uint8 passwordInput3[] = "password:***-";	//密码键盘输入三位
const uint8 passwordInput4[] = "password:****";	//密码键盘输入三位
const uint8 passwordError[] = "password:error";	//密码键盘输入密码错误

//主菜单
const uint8 programInfo[] = "1.prog info";		//程序信息
const uint8 bootInfo[] 	  = "2.boot info";		//BOOT信息
const uint8 slaveState[]  = "3.slave info";		//从机信息
const uint8 canSetInfo[]  = "4.can info";		//CAN信息
const uint8 inputTest[]   = "5.input test";		//输入测试
const uint8 outputTest[]  = "6.output test";	//输出测试
const uint8 startConfig[] = "7.open config";	//开启配置
const uint8 netInfo[]	  = "8.net info";	    //网络信息
const uint8 point[]  = "->";	//指针
const uint8 nullPoint[]  = "  ";	//无指针


const unsigned char DEFAULT_IP[4]  ={192,168,1,88};											
const unsigned char DEFAULT_SUBNET[4]    ={255,255,255,0};										
const unsigned char DEFAULT_GATEWAY[4]   ={192,168,1,1};											
const unsigned char DEFAULT_DNS[4]={114,114,114,114};	
const unsigned char DEFAULT_MAC[6]={0x00,0x08,0xdc,0x11,0x11,0x11};
const unsigned char DEFAULT_DATE[6]={20,4,1,13,0,0};
const unsigned int 	DEFAULT_PORT=502;
const unsigned char DEFAULT_4851ID=0x01;
const unsigned char DEFAULT_4852ID=0x02;
const unsigned char DEFAULT_CANLIMIT=0x01;
const unsigned char DEFAULT_CANFILTER=0x02;
const unsigned char DEFAULT_SLAVADDRSTART=0x01;
const unsigned char DEFAULT_SLAVESTATE=0x00;

extern uint16 local_tcp_port;	

void read_parameter()
{
	uint8 i=0;
	uint8 buf[sizeof(innerSaveTypeDef)*2];
	memset(buf,0x00,sizeof(buf));
	// STMFLASH_Read(SAVE_DATA_ADDR,(uint16 *)buf,sizeof(innerSaveTypeDef));
	memcpy(&innerSaveTypeDef,buf,sizeof(innerSaveTypeDef));
	
	memset(innerSaveTypeDef.ProgVersion,0x00,sizeof(innerSaveTypeDef.ProgVersion));
	memset(innerSaveTypeDef.progDate,0x00,sizeof(innerSaveTypeDef.progDate));
	memset(innerSaveTypeDef.ProgSize,0x00,sizeof(innerSaveTypeDef.ProgSize));
	memset(innerSaveTypeDef.progMd5,0x00,sizeof(innerSaveTypeDef.progMd5));
	
	memcpy(innerSaveTypeDef.ProgVersion,"V001",strlen("V001"));
	memcpy(innerSaveTypeDef.progDate,"20.4.1.14.50.0",strlen("20.4.1.14.50.0"));
	memcpy(innerSaveTypeDef.ProgSize,"1111",strlen("1111"));
	memcpy(innerSaveTypeDef.progMd5,"abcdefghijklmnopqrstabcdefgjaaaa",strlen("abcdefghijklmnopqrstabcdefgjaaaa"));
	
	
	if(innerSaveTypeDef.configValueTypeDef.configedFlag!=0x01)			//数据没有被初始化过，初始化成默认值
	{
		innerSaveTypeDef.configValueTypeDef.configedFlag=0x01;			//数据已经配置过
		memcpy(&innerSaveTypeDef.configValueTypeDef.localDate,DEFAULT_DATE,sizeof(DEFAULT_DATE));//配置日期
		memcpy(&innerSaveTypeDef.configValueTypeDef.mac,DEFAULT_MAC,sizeof(DEFAULT_MAC));//MAC地址
		memcpy(&innerSaveTypeDef.configValueTypeDef.lip,DEFAULT_IP,sizeof(DEFAULT_IP));//本地IP地址
		memcpy(&innerSaveTypeDef.configValueTypeDef.sub,DEFAULT_SUBNET,sizeof(DEFAULT_SUBNET));//子网掩码
		memcpy(&innerSaveTypeDef.configValueTypeDef.gw,DEFAULT_GATEWAY,sizeof(DEFAULT_GATEWAY));//网关
		memcpy(&innerSaveTypeDef.configValueTypeDef.dns,DEFAULT_DNS,sizeof(DEFAULT_DNS));//DNS服务器地址
		memcpy(&innerSaveTypeDef.configValueTypeDef.rip,DEFAULT_IP,sizeof(DEFAULT_IP));//IP远程IP地址*/
		innerSaveTypeDef.configValueTypeDef.port485=DEFAULT_PORT;
		innerSaveTypeDef.configValueTypeDef.id4851=DEFAULT_4851ID;//485从机一ID
		innerSaveTypeDef.configValueTypeDef.id4852=DEFAULT_4852ID;//485从机二ID
		innerSaveTypeDef.configValueTypeDef.canLimit=DEFAULT_CANLIMIT;//CAN限定位
		innerSaveTypeDef.configValueTypeDef.canFilter=DEFAULT_CANFILTER;//CAN过滤位
		for(i=0;i<sizeof(innerSaveTypeDef.configValueTypeDef.slaveId);i++)//从机ID	
		{
			innerSaveTypeDef.configValueTypeDef.slaveId[i]=DEFAULT_SLAVADDRSTART+i;
		}		
		for(i=0;i<sizeof(innerSaveTypeDef.configValueTypeDef.slaveState);i++)//从机状态
		{
			innerSaveTypeDef.configValueTypeDef.slaveState[i]=DEFAULT_SLAVESTATE;
		}
		memset(buf,0x00,sizeof(buf));
		memcpy(buf,&innerSaveTypeDef,sizeof(innerSaveTypeDef));
		// STMFLASH_Write(SAVE_DATA_ADDR,(uint16 *)buf,sizeof(innerSaveTypeDef));//更新成功存储更新信息
			
	}
	// local_tcp_port = innerSaveTypeDef.configValueTypeDef.port485;
}



















