//file protocol.h
/***************************************************************************************************
* 1、 Class      ： comm_define
* 2、 Version    ： *.*
* 3、 Description： 网络解析的公共头文件
* 4、 Author     ： QNA (http://www.9cpp.com/)
* 5、 Created    ： 2012-10-21 14:14:03
* 6、 History    ： 
* 7、 Remark     ： 
****************************************************************************************************/

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__




enum SAVE_TYPE_TAG
{
	KeyWord1,          //保存类型tCompanyLog  sKeyWord1
	sKeyWord1,         //保存数据库tCompanyLog  sKeyWord2
	sMemoChar,         //保存数据库tCompanyLog  sMemoChar
	File               //保存文件
}SAVETYPE, *PSAVETYPE;


/*
* Encoding type
*/
#define ENCT_URL             0x0001
#define ENCT_GB1212          0x0002
#define ENCT_UTF_8           0x0008
#define ENCT_UNICODE         0x0020


//查找标记链结构表  这个结构体不关乎协议 保存着需要获取内容的关键字体 对一种关键字一个链表
class CMarkfind
{
	CMarkfind()
	{
		memset(this, 0, sizeof(*this));
	}

	~CMarkfind()
	{
		Reset();
	}

public:
	//创建一个新的标记查找结构链表并初始化为0  成功返回 链表指针 失败返回NULL
	inline MARK_FIND_TAG* NewMarkFind()
	{
		MARK_FIND_TAG* pstuMarkFind = new MARK_FIND_TAG;
		if (pstuMarkFind)
		{
			memset(pstuMarkFind, 0, sizeof(MARK_FIND_TAG));
			return pstuMarkFind;
		}
		return NULL;
	}

	//给标记查找结构链表增加一个新的标记结构，并初始化为0  失败回返false
	inline bool AddMarkFind()
	{
		MARK_FIND_TAG* pstuMarkFind = new MARK_FIND_TAG;
		if (pstuMarkFind)
		{
			memset(pstuMarkFind, 0, sizeof(MARK_FIND_TAG));
			pstuMarkFindNext = pstuMarkFind;
			return true;
		}
		return false;
	}

	//清除当前结构链表所指的下一个结构链表
	inline void ClearNext()
	{
		//清除当前结构链表所指的下一个结构链表
		if (pstuMarkFindNext)
		{
			//清除下一个结构后面的结构
			while(pstuMarkFindNext->pstuMarkFindNext)
			{
				pstuMarkFindNext->ClearNext();
			}

			memset(pstuMarkFindNext, 0, sizeof(MARK_FIND_TAG));
			delete pstuMarkFindNext;
			pstuMarkFindNext = NULL;
		}
	}

	//重置当前结点开始的链表
	inline void Reset()
	{
		ClearNext();
		memset(this, 0, sizeof(*this));
	}

public:
	int iEncodingType; 	                  //编码类型 URL GB1212 UTF_8 UNICODE 因为有的数据前后标记不一样 Coding type值
	int iPacketNum;                       //该内容在当前包之后第几个包之内？ 需要组包的情况下
	char szMarkStart[64];                 //开始标记
	char szMarkEnd[16];                   //结束标记
	SAVE_TYPE_TAG enumSaveType;           //标记中的数据保存类型
	CMarkfind* pstuMarkFindNext;
};

//包 检查结构 链表   第二种关乎包的类型  像http包  可简单区分开来 
typedef struct FIND_INFO_TAG
{
	bool bIsExtendFind;           //是否需要延伸查找(即在第二个包查找)  true是  false否	
	int iFindType;                //查找类型   默认0 帐号 eg;首页，1回帖 2发贴 -1搜索引擎
	char szHost[128];             //http类型用域名 当类型为非http协议时为空 最长度为128位
	char szPacketHeadTag[64];     //包头标记  最长度为64位             头和域名用来确定包数据的类型 
	PMARKFIND pstuMarkFind;       //查找标记链表
	FIND_INFO_TAG* pstuFindInfoNext;

	FIND_INFO_TAG()
	{
		memset(this, 0, sizeof(*this));
	}

	~FIND_INFO_TAG()
	{
		Reset();
	}

	//检查包头标记
	bool CheckPacketHeadTag(BYTE* pInBuffer, int iBufLen)
	{
		if (strlen(szPacketHeadTag)>iBufLen) return false;
		//……这里还需要调用检查包头函数

	}	

	//创建一个新的标记查找结构链表并初始化为0  成功返回 链表指针 失败返回NULL
	inline FIND_INFO_TAG* NewFindInfo()
	{
		FIND_INFO_TAG* pstuFindInfo = new FIND_INFO_TAG;
		if (pstuFindInfo)
		{
			memset(pstuFindInfo, 0, sizeof(FIND_INFO_TAG));
			return pstuFindInfo;
		}
		return NULL;
	}

	//给标记查找结构链表增加一个新的标记结构，并初始化为0  失败回返false
	inline bool AddFindInfo()
	{
		FIND_INFO_TAG* pstuFindInfo = new FIND_INFO_TAG;
		if (pstuFindInfo)
		{
			memset(pstuFindInfo, 0, sizeof(FIND_INFO_TAG));
			pstuFindInfoNext = pstuFindInfo;
			return true;
		}
		return false;
	}

	//清除当前结构链表所指的下一个结构链表
	inline void ClearNext()
	{
		//清除本结构所指的下一个结构链表
		if (pstuFindInfoNext)
		{
			//清除下一个结构后面的结构
			while(pstuFindInfoNext->pstuFindInfoNext)
			{
				pstuFindInfoNext->ClearNext();
			}

			//先清空查找标记链表
			if (pstuFindInfoNext->pstuMarkFind)
			{
				pstuFindInfoNext->pstuMarkFind->Reset();
				delete pstuFindInfoNext->pstuMarkFind;
				pstuFindInfoNext->pstuMarkFind = NULL;
			}

			//再清空包 检查结构 链表
			memset(pstuFindInfoNext, 0, sizeof(FIND_INFO_TAG));
			delete pstuFindInfoNext;
			pstuFindInfoNext = NULL;
		}
	}

	//重置当前结点开始的链表
	inline void Reset()
	{		
		ClearNext();
		//清空查找标记链表
		if (pstuMarkFind)
		{
			pstuMarkFind->Reset();
			delete pstuMarkFind;
			pstuMarkFind = NULL;
		}
		//清空包检查结构链表
		memset(this, 0, sizeof(*this));
	}
}FINDINFO, *PFINDINFO;

//服务检查结构链表  这个结构只关乎协议
typedef struct SERVICES_FIND_INFO_TAG
{
	int iServicesType;                                                     //服务类型,与enum ApplicationProtocolType相对应  eg baidu
	PFINDINFO pstuFindInfo;                                                //包头检查结构 链
	SERVICES_FIND_INFO_TAG* pstuServicesFindInfoNext;                      //

	SERVICES_FIND_INFO_TAG()
	{
		memset(this, 0, sizeof(*this));
	}

	~SERVICES_FIND_INFO_TAG()
	{
		Reset();
	}

	//创建一个新的标记查找结构链表并初始化为0  成功返回 链表指针 失败返回NULL
	inline bool Init()
	{
		iServicesType = 0;
		pstuFindInfo = pstuFindInfo->NewFindInfo();
		if (pstuFindInfo)
			return true;
		else
			pstuFindInfo = NULL;
		return false;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//创建一个新的标记查找结构链表并初始化为0  成功返回 链表指针 失败返回NULL
	inline SERVICES_FIND_INFO_TAG* NewServicesFindInfo()
	{
		SERVICES_FIND_INFO_TAG* pstuServicesFindInfo = new SERVICES_FIND_INFO_TAG;
		if (pstuServicesFindInfo)
		{
			memset(pstuServicesFindInfo, 0, sizeof(SERVICES_FIND_INFO_TAG));
			//创建 
			if (!(pstuServicesFindInfo->pstuFindInfo = pstuServicesFindInfo->pstuFindInfo->NewFindInfo()))
			{
				Reset();
				pstuServicesFindInfo = NULL;
			}
			return pstuServicesFindInfo;
		}
		return NULL;
	}

	//给标记查找结构链表增加一个新的标记结构，并初始化为0  失败回返false
	inline bool AddServicesFindInfo()
	{
		SERVICES_FIND_INFO_TAG* pstuServicesFindInfo = new SERVICES_FIND_INFO_TAG;
		if (pstuServicesFindInfo)
		{
			memset(pstuServicesFindInfo, 0, sizeof(SERVICES_FIND_INFO_TAG));
			pstuServicesFindInfoNext = pstuServicesFindInfo;
			return true;
		}
		return false;
	}

	//清除当前结构链表所指的下一个结构链表
	inline void ClearNext()
	{
		//清除当前结构链表所指的下一个结构链表
		if (pstuServicesFindInfoNext)
		{
			//清除下一个结构后面的结构
			while(pstuServicesFindInfoNext->pstuServicesFindInfoNext)
			{
				pstuServicesFindInfoNext->ClearNext();
			}

			//先清空查找标记链表
			if (pstuServicesFindInfoNext->pstuFindInfo)
			{
				pstuServicesFindInfoNext->pstuFindInfo->Reset();
				delete pstuServicesFindInfoNext->pstuFindInfo;
				pstuServicesFindInfoNext->pstuFindInfo = NULL;
			}

			memset(pstuServicesFindInfoNext, 0, sizeof(MARK_FIND_TAG));
			delete pstuServicesFindInfoNext;
			pstuServicesFindInfoNext = NULL;
		}
	}

	//重置当前结点开始的链表
	inline void Reset()
	{
		ClearNext();
		if (pstuFindInfo)
		{
			pstuFindInfo->Reset();
			delete pstuFindInfo;
			pstuFindInfo = NULL;
		}
		memset(this, 0, sizeof(*this));
	}
}SERVICESFINDINFO, *PSERVICESFINDINFO;

//这个对XML没用 但是可以跟据出现的频率调整遍历的顺序
typedef struct FILTER_FIND_INFO_TAG
{
	int iFilterType;                        //筛选类型 eg http  Smtp
	PSERVICESFINDINFO pstuServicesFindInfo; //其下对应多种服务 eg baidu mop 163 126
}FILTERFINDINFO, *PFILTERFINDINFO;
#endif /*__PROTOCOL_H__*/