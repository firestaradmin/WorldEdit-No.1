/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Joystick Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
//const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
//  {
//    0x12,                       /*bLength */
//    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
//    0x00,                       /*bcdUSB */
//    0x02,
//    0x00,                       /*bDeviceClass*/
//    0x00,                       /*bDeviceSubClass*/
//    0x00,                       /*bDeviceProtocol*/
//    0x40,                       /*bMaxPacketSize 64*/
//    0x83,                       /*idVendor (0x0483)*/
//    0x04,
//    0x10,                       /*idProduct = 0x5710*/
//    0x57,
//    0x00,                       /*bcdDevice rel. 2.00*/
//    0x02,
//    1,                          /*Index of string descriptor describing
//                                                  manufacturer */
//    2,                          /*Index of string descriptor describing
//                                                 product*/
//    3,                          /*Index of string descriptor describing the
//                                                 device serial number */
//    0x01                        /*bNumConfigurations*/
//  }
//  ; /* Joystick_DeviceDescriptor */
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
  {
      0x12, 		         /*bLength：长度，设备描述符的长度为18字节*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType：类型，设备描述符的编号是0x01*/
    0x00,                       /*bcdUSB：所使用的USB版本为2.0*/
    0x02,
    0x00,                       /*bDeviceClass：设备所使用的类代码*/
    0x00,                       /*bDeviceSubClass：设备所使用的子类代码*/
    0x00,                       /*bDeviceProtocol：设备所使用的协议*/
    0x40,                       /*bMaxPacketSize：最大包长度为8字节*/
    0x78,                       /*idVendor：厂商ID为0x7788*/
    0x67,
    0x12,                      	/*idProduct：产品ID为0x1122*/
    0x01,
    0x00,                       /*bcdDevice：设备的版本号为2.00*/
    0x02,
    1,                          /*iManufacturer:厂商字符串的索引*/
    2,                          /*iProduct：产品字符串的索引*/
    3,                          /*iSerialNumber：设备的序列号字符串索引*/
    0x01                        /*bNumConfiguration：设备有1种配置*/
}; /* keyboard设备描述符 */

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
//const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
//  {
//    0x09, /* bLength: Configuration Descriptor size */
//    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
//    JOYSTICK_SIZ_CONFIG_DESC,
//    /* wTotalLength: Bytes returned */
//    0x00,
//    0x01,         /*bNumInterfaces: 1 interface*/
//    0x01,         /*bConfigurationValue: Configuration value*/
//    0x00,         /*iConfiguration: Index of string descriptor describing
//                                     the configuration*/
//    0xE0,         /*bmAttributes: Self powered */
//    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

//    /************** Descriptor of Joystick Mouse interface ****************/
//    /* 09 */
//    0x09,         /*bLength: Interface Descriptor size*/
//    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
//    0x00,         /*bInterfaceNumber: Number of Interface*/
//    0x00,         /*bAlternateSetting: Alternate setting*/
//    0x01,         /*bNumEndpoints*/
//    0x03,         /*bInterfaceClass: HID*/
//    0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
//    0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
//    0,            /*iInterface: Index of string descriptor*/
//    /******************** Descriptor of Joystick Mouse HID ********************/
//    /* 18 */
//    0x09,         /*bLength: HID Descriptor size*/
//    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
//    0x00,         /*bcdHID: HID Class Spec release number*/
//    0x01,
//    0x00,         /*bCountryCode: Hardware target country*/
//    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
//    0x22,         /*bDescriptorType*/
//    JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
//    0x00,
//    /******************** Descriptor of Joystick Mouse endpoint ********************/
//    /* 27 */
//    0x07,          /*bLength: Endpoint Descriptor size*/
//    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

//    0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
//    0x03,          /*bmAttributes: Interrupt endpoint*/
//    0x04,          /*wMaxPacketSize: 4 Byte max */
//    0x00,
//    0x20,          /*bInterval: Polling Interval (32 ms)*/
//    /* 34 */
//  }
//  ; /* MOUSE_ConfigDescriptor */

/* USB配置描述符集合(配置、接口、端点、类、厂商)(Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
{
    0x09, 		  	/*bLength：长度，设备字符串的长度为9字节*/
    USB_CONFIGURATION_DESCRIPTOR_TYPE, 	/*bDescriptorType：类型，配置描述符的类型编号为0x2*/
    JOYSTICK_SIZ_CONFIG_DESC,	   		/*wTotalLength：配置描述符的总长度为41字节*/    
    0x00,
    0x01,         	/*bNumInterfaces：配置所支持的接口数量1个*/
    0x01,         	/*bConfigurationValue：该配置的值*/
    0x00,         	/*iConfiguration：该配置的字符串的索引值，该值为0表示没有字符串*/              
    0xC0,         	/* bmAttributes:设备的一些特性，0xc0表示自供电，不支持远程唤醒
						D7:保留必须为1，D6:是否自供电，D5：是否支持远程唤醒，D4~D0：保留设置为0*/
    0x32,         	/*从总线上获得的最大电流为100mA */
//    0x96,         /*MaxPower：设备需要从总线上获取多少电流，单位为2mA，0x96表示300mA*/

    /************** 接口描述符****************/
	/* 09 */
    0x09,         	/*bLength：长度，接口描述符的长度为9字节 */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType：接口描述符的类型为0x4 */
    0x00,         	/*bInterfaceNumber：该接口的编号*/
    0x00,        	/*bAlternateSetting：该接口的备用编号 */
    0x02,         	/*bNumEndpoints：该接口所使用的端点数*/
    0x03,         	/*bInterfaceClass该接口所使用的类为HID*/
    0x01,         	/*bInterfaceSubClass：该接口所用的子类 1=BOOT, 0=no boot */
    0x01,         	/*nInterfaceProtocol :该接口使用的协议0=none, 1=keyboard, 2=mouse */
    0,            	/*iInterface: 该接口字符串的索引 */

    /*****************HID描述符 ********************/
	/* 18 */
    0x09,         	/*bLength: HID描述符的长度为9字节 */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID的描述符类型为0x21 */
    0x10,         	/*bcdHID: HID协议的版本为1.1 */
    0x01,
    0x21,         	/*bCountryCode: 国家代号 */
    0x01,         	/*bNumDescriptors: 下级描述符的数量*/
    0x22,         	/*bDescriptorType：下级描述符的类型*/
    JOYSTICK_SIZ_REPORT_DESC,/* wItemLength: 下一集描述符的长度*/
    0x00,

    /********************输入端点描述符******************/
	/* 27 */
    0x07,         	/* bLength: 端点描述符的长度为7字节*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: 端点描述符的类型为0x05*/
    0x81,         	/* bEndpointAddress: 该端点(输入)的地址,D7:0(OUT),1(IN),D6~D4:保留,D3~D0:端点号*/               
    0x03,         	/* bmAttributes: 端点的属性为为中断端点.
			D0~D1表示传输类型:0(控制传输),1(等时传输),2(批量传输),3(中断传输)
			非等时传输端点:D2~D7:保留为0
			等时传输端点：
			D2~D3表示同步的类型:0(无同步),1(异步),2(适配),3(同步)
			D4~D5表示用途:0(数据端点),1(反馈端点),2(暗含反馈的数据端点),3(保留)，D6~D7:保留,*/
    0x08,         	/* wMaxPacketSize: 该端点支持的最大包长度为8字节*/
    0x00,
    0x0A,         	/* bInterval: 轮询间隔(32ms) */

	/********************输出端点描述符*******************/
	/* 34 */
	0x07,         	/* bLength: 端点描述符的长度为7字节*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: 端点描述符的类型为0x05*/
    0x01,         	/* bEndpointAddress: 该端点(输入)的地址,D7:0(OUT),1(IN),D6~D4:保留,D3~D0:端点号*/               
    0x03,         	/* bmAttributes: 端点的属性为为中断端点.
			D0~D1表示传输类型:0(控制传输),1(等时传输),2(批量传输),3(中断传输)
			非等时传输端点:D2~D7:保留为0
			等时传输端点：
			D2~D3表示同步的类型:0(无同步),1(异步),2(适配),3(同步)
			D4~D5表示用途:0(数据端点),1(反馈端点),2(暗含反馈的数据端点),3(保留)，D6~D7:保留,*/
    0x01,         	/* wMaxPacketSize: 该端点支持的最大包长度为字节*/
    0x00,
    0x0A,         	/* bInterval: 轮询间隔(32ms) */
   /* 41 */
}; 

//const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] =
//  {
//    0x05,          /*Usage Page(Generic Desktop)*/
//    0x01,
//    0x09,          /*Usage(Mouse)*/
//    0x02,
//    0xA1,          /*Collection(Logical)*/
//    0x01,
//    0x09,          /*Usage(Pointer)*/
//    0x01,
//    /* 8 */
//    0xA1,          /*Collection(Linked)*/
//    0x00,
//    0x05,          /*Usage Page(Buttons)*/
//    0x09,
//    0x19,          /*Usage Minimum(1)*/
//    0x01,
//    0x29,          /*Usage Maximum(3)*/
//    0x03,
//    /* 16 */
//    0x15,          /*Logical Minimum(0)*/
//    0x00,
//    0x25,          /*Logical Maximum(1)*/
//    0x01,
//    0x95,          /*Report Count(3)*/
//    0x03,
//    0x75,          /*Report Size(1)*/
//    0x01,
//    /* 24 */
//    0x81,          /*Input(Variable)*/
//    0x02,
//    0x95,          /*Report Count(1)*/
//    0x01,
//    0x75,          /*Report Size(5)*/
//    0x05,
//    0x81,          /*Input(Constant,Array)*/
//    0x01,
//    /* 32 */
//    0x05,          /*Usage Page(Generic Desktop)*/
//    0x01,
//    0x09,          /*Usage(X axis)*/
//    0x30,
//    0x09,          /*Usage(Y axis)*/
//    0x31,
//    0x09,          /*Usage(Wheel)*/
//    0x38,
//    /* 40 */
//    0x15,          /*Logical Minimum(-127)*/
//    0x81,
//    0x25,          /*Logical Maximum(127)*/
//    0x7F,
//    0x75,          /*Report Size(8)*/
//    0x08,
//    0x95,          /*Report Count(3)*/
//    0x03,
//    /* 48 */
//    0x81,          /*Input(Variable, Relative)*/
//    0x06,
//    0xC0,          /*End Collection*/
//    0x09,
//    0x3c,
//    0x05,
//    0xff,
//    0x09,
//    /* 56 */
//    0x01,
//    0x15,
//    0x00,
//    0x25,
//    0x01,
//    0x75,
//    0x01,
//    0x95,
//    /* 64 */
//    0x02,
//    0xb1,
//    0x22,
//    0x75,
//    0x06,
//    0x95,
//    0x01,
//    0xb1,
//    /* 72 */
//    0x01,
//    0xc0
//  }
//  ; /* Joystick_ReportDescriptor */


/* HID的报告描述符*/
/*定义了8字节发送：
**  第一字节表示特殊件是否按下：D0:Ctrl D1:Shift D2:Alt
**  第二字节保留，值为0
**  第三~第八字节:普通键键值的数组,最多能同时按下6个键
**定义了1字节接收:对应键盘上的LED灯,这里只用了两个位。
**	D0:Num Lock   D1:Cap Lock   D2:Scroll Lock   D3:Compose   D4:Kana*/
const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] = 
{ 	
	/*short Item   D7~D4:bTag;D3~D2:bType;D1~D0:bSize
	**bTag ---主条目  	1000:输入(Input) 1001:输出(Output) 1011:特性(Feature)	1010:集合(Collection) 1100:关集合(End Collection) 
	**		  全局条目 	0000:用途页(Usage Page) 0001:逻辑最小值(Logical Minimum) 0010:逻辑最大值(Logical Maximum) 0011:物理最小值(Physical Minimum)
	**					0100:物理最大值(Physical Maximum) 0101:单元指数(Unit Exponet) 0110:单元(Unit) 0111:数据域大小(Report Size)
	**					1000:报告ID(Report ID) 1001:数据域数量(Report Count) 1010:压栈(Push) 1011:出栈(Pop) 1100~1111:保留(Reserved)
	**		  局部条目	0000:用途(Usage) 0001:用途最小值(Usage Minimum) 0010:用途最大值(Usage Maximum) 0011:标识符索引(Designator Index)
	**					0100:标识符最小值(Designator Minimum) 0101:标识符最大值(Designator Maximum) 0111:字符串索引(String Index) 1000:字符串最小值(String Minimum)   
	**					1001:字符串最大值(String Maximum) 1010:分隔符(Delimiter) 其他：保留(Reserved)
	**bType---00:主条目(main)  01:全局条目(globle)  10:局部条目(local)  11:保留(reserved)
	**bSize---00:0字节  01:1字节  10:2字节  11:4字节*/
	
	//0x05:0000 01 01 这是个全局条目，用途页选择为普通桌面页
	0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	//0x09:0000 10 01 这是个全局条目，用途选择为键盘
	0x09, 0x06, // USAGE (Keyboard)
	//0xa1:1010 00 01 这是个主条目，选择为应用集合，
	0xa1, 0x01, // COLLECTION (Application)
	//0x05:0000 01 11 这是个全局条目，用途页选择为键盘/按键
	0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)

	//0x19:0001 10 01 这是个局部条目，用途的最小值为0xe0，对应键盘上的左ctrl键
	0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
	//0x29:0010 10 01 这是个局部条目，用途的最大值为0xe7，对应键盘上的有GUI(WIN)键
	0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
	//0x15:0001 01 01 这是个全局条目，说明数据的逻辑值最小值为0
	0x15, 0x00, // LOGICAL_MINIMUM (0)
	//0x25:0010 01 01 这是个全局条目，说明数据的逻辑值最大值为1
	0x25, 0x01, // LOGICAL_MAXIMUM (1)

	//0x95:1001 01 01 这是个全局条目，数据域的数量为8个
	0x95, 0x08, // REPORT_COUNT (8)
	//0x75:0111 01 01 这是个全局条目，每个数据域的长度为1位
	0x75, 0x01, // REPORT_SIZE (1)	   
	//0x81:1000 00 01 这是个主条目，有8*1bit数据域作为输入，属性为:Data,Var,Abs
	0x81, 0x02, // INPUT (Data,Var,Abs)

	//0x95:1001 01 01 这是个全局条目,数据域的数量为1个
	0x95, 0x01, // REPORT_COUNT (1)
	//0x75:0111 01 01 这是个全局条目，每个数据域的长度为8位
	0x75, 0x08, // REPORT_SIZE (8)
	//0x81:1000 00 01 这是个主条目，有1*8bit数据域作为输入，属性为:Cnst,Var,Abs
	0x81, 0x03, // INPUT (Cnst,Var,Abs)

	//0x95:1001 01 01 这是个全局条目，数据域的数量为6个
	0x95, 0x06, // REPORT_COUNT (6)
	//0x75:0111 01 01 这是个全局条目，每个数据域的长度为8位
	0x75, 0x08, // REPORT_SIZE (8)
	//0x25:0010 01 01 这是个全局条目，逻辑最大值为255
	0x25, 0xFF, // LOGICAL_MAXIMUM (255)
	//0x19:0001 10 01 这是个局部条目，用途的最小值为0
	0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
	//0x29:0010 10 01 这是个局部条目，用途的最大值为0x65
	0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
	//0x81:1000 00 01 这是个主条目，有6*8bit的数据域作为输入，属相为属性为:Data,Var,Abs
	0x81, 0x00, // INPUT (Data,Ary,Abs)

	//0x25:0010 01 01 这是个全局条目，逻辑的最大值为1
	0x25, 0x01, // LOGICAL_MAXIMUM (1)
	//0x95:1001 01 01 这是个全局条目，数据域的数量为2
	0x95, 0x02, // REPORT_COUNT (2)
	//0x75:0111 01 01 这是个全局条目，每个数据域的长度为1位
	0x75, 0x01, // REPORT_SIZE (1)
	//0x05:0000 01 01 这是个全局条目，用途页选择为LED页
	0x05, 0x08, // USAGE_PAGE (LEDs)
	//0x19:0001 10 01 这是个局部条目，用途的最小值为0x01,对应键盘上的Num Lock
	0x19, 0x01, // USAGE_MINIMUM (Num Lock)
	//0x29:0010 10 01 这是个局部条目，用途的最大值为0x02,对应键盘上的Caps Lock
	0x29, 0x02, // USAGE_MAXIMUM (Caps Lock)
	//0x91:1001 00 01 这是个主条目，有2*1bit的数据域作为输出，属性为:Data,Var,Abs
	0x91, 0x02, // OUTPUT (Data,Var,Abs)

	//0x95:1001 01 01 这是个全局条目，数据域的数量为1个
	0x95, 0x01, // REPORT_COUNT (1)
	//0x75:0111 01 01 这是个全局条目，每个数据域的长度为6bit,正好与前面的2bit组成1字节
	0x75, 0x06, // REPORT_SIZE (6)
	//0x91:1001 00 01 这是个主条目，有1*6bit数据域最为输出，属性为:Cnst,Var,Abs
	0x91, 0x03, // OUTPUT (Cnst,Var,Abs)

	0xc0        // END_COLLECTION
}; 

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
{
	JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	'L', 0, 'X', 0, 'G', 0, '-', 0, 'W', 0, 'O', 0, 'R', 0, 'L', 0, 'D', 0, ' ', 0, 'E', 0, 'D', 0, 'I', 0, 'T', 0,
	' ', 0, 
	0X1B,0X52,//
	0x16,0X4E,//
	0X00,0X4E,//鼠
	0XF7,0X53,//标 
};

uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

