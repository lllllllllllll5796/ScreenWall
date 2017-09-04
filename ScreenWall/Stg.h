#pragma once

/*配置*/

enum StgCfgEnum {
	StgCfgEnum_LoginUser, //登录用户
	//StgCfgEnum_ServerStation,//服务站
	StgCfgEnum_Buff
};





//配置基类
struct StgCfg{
	virtual void Read(LPSTREAM) = 0;
	virtual void Write(LPSTREAM) = 0;
};

//登录用户
struct StgCfgLoginUser : StgCfg {
	LPTSTR pszUsername = nullptr;//用户名
	int ccUsername = 0;//用户名字符个数
	LPTSTR pszPswd = nullptr;//密码
	int ccPswd = 0;
	bool bRemPswd = false; //记住密码

	virtual void Read(LPSTREAM);
	virtual void Write(LPSTREAM);

};


