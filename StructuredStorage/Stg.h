#pragma once
#include <bitset>
//#include <string>
//#include <vector>
#include <list>

/*
配置结构体都用“移动”
operator= 和 swap后期采用模板
*/

//enum StgCfgs {
//	StgCfgs_Normal,
//	StgCfgs_Revision,
//	StgCfgs_Save,
//	StgCfgs_Custom,
//	StgCfgs_Buff
//};

//配置项
enum StgCfgEnum {
	StgCfgEnumNormal,
	StgCfgEnumRevision_AutoAmend,
	StgCfgEnumRevision_Operator,
	StgCfgEnumRevision,
	StgCfgEnumSave,
	StgCfgEnumCustom,
	StgCfgEnumBuff
};
//extern const CString g_StgStreamNames[];//const要加

//结构基类
struct StgCfg{
	int nSize;//结构体大小
	StgCfg(int sz) : nSize(sz) {}
};

struct StgNormalCfg : StgCfg{
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	bool bOpenEmailWhenInReadView = false;
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
	LPTSTR pszUsername;
	int cchUsername = 0;
	LPTSTR pszShortname;
	int cchShortname = 0;	

	//拷贝构造
	//拷贝赋值
	//移动构造
	//移动赋值
	//析构
	StgNormalCfg(int sz) : StgCfg(sz){}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	//StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	//friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};


//校对

struct StgRevisionCfg_AutoAmend : StgCfg {
	bool bShowAutoAmendBtn = false;
	bool bUpcaseFirst2Char = false;
	bool bAmend3 = false;
	bool bAutoReplace = false;//勾选了后面的字段才有效
	LPTSTR pszAutoReplace;//格式：acc-abc;你哈-你好;
	int cchAutoReplace = 0;
	
	StgRevisionCfg_AutoAmend(int sz) : StgCfg(sz) {}
};

struct StgRevisionCfg_Operator : StgCfg {
	bool bAddOpToContextMenu = false;
	//std::bitset<8> bsOpts;
	char szOpts[8] = { 0 };

	StgRevisionCfg_Operator(int sz) : StgCfg(sz) {}
};

struct StgRevisionCfg : StgCfg {
	bool bCheckWhenInput = false;
	bool bUseContextCheck = false;
	char szStyles[10] = { 0 };
	int nStyle = 0;
	//std::bitset<10> bsStyles;

	StgRevisionCfg(int sz) : StgCfg(sz) { /*bsStyles.set();*/ }
};


//保存
struct StgSaveCfg : StgCfg {
	int nSaveType = 0;
	int nRecoverTime = 10;
	bool bAutoRecover = true;
	LPTSTR strRecoverFilePath;
	int cchRecoverFilePath = 0;

	StgSaveCfg(int sz) : StgCfg(sz) {}
};


//自定义



//Stg操作类
class IStgCfgOperator {
public:
	virtual HRESULT GetStgCfgs() = 0;
	//virtual bool IsDirty() = 0;
	virtual HRESULT SetStgCfgs() = 0;

protected:
	StgCfg* m_cfg = nullptr;
	LPSTREAM m_pStream = nullptr;
	bool m_bDirty = false;
};

//
class CSSFile {
public:
	//子存储名字、类型
	enum TYPE { Storage, Stream };
	//union INFO {
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//};
	struct Node {
		CString name, parentName;
		TYPE type;//节点类型
		//INFO info;
		LPSTORAGE pStorage;//type=Storage
		StgCfg* pCfg;//type=Stream
		StgCfgEnum emCfg;//配置类型
		Node(CString nm, CString fnm, TYPE t, StgCfg* p = nullptr, StgCfgEnum em = StgCfgEnumBuff) :
			name(nm), parentName(fnm), type(t), pCfg(p), emCfg(em) {}
	};

	CSSFile();
	//struct StorageData
	//{
	//	IStorage *Stg = nullptr;
	//	StorageData *ParentStg = nullptr;
	//};
	//打开复合文档
	bool OpenSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//打开存储对象
	bool OpenStroage(const CString & name, /*LPSTORAGE pStorage, */DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//打开流
	bool OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//关闭复合文档
	void Close();

protected:
	//创建复合文档
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//创建存储对象
	bool CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//创建流
	bool CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//释放打开的存储对象
	bool ExitStorage();
	//获取根存储
	IStorage * GetRootStorage() const;
	//文档是否打开
	bool IsOpen() const;
	//创建默认配置
	//bool CreateDefaultCfg();
	//释放打开的存储对象
	void ReleaseStorage();

private:
	//查找父节点存储对象
	Node& FindParentNode(std::list<Node>::iterator it/*当前节点*/, const CString& name/*父节点名*/);

protected:
	bool m_bOpen = false;
	//CString m_strFilename;
	LPSTORAGE m_pRootStg = nullptr;
	//StorageData *m_pCurrentStg = nullptr;
	std::list<Node> m_liNode;
	//const std::vector  配置可能同名
};