#pragma once
#include <bitset>
#include <string>
#include <vector>
//#include <list>
#include <map>




//配置项
enum StgCfgEnum {
	StgCfgEnumNormal,
	StgCfgEnumRevision,
	StgCfgEnumRevision_AutoAmend,
	StgCfgEnumRevision_Operator,
	StgCfgEnumSave,
	StgCfgEnumCustom,
	StgCfgEnumBuff
};
//extern const CString g_StgStreamNames[];//const要加

const unsigned short STGCFG_UsernameLen = 16;
const unsigned int STGCFG_AutoReplaceLen = 1024;


//结构基类
struct StgCfg{
	//int nSize;//结构体大小
	//StgCfg(int sz) : nSize(sz) {}
	//将读写绑定到每个子类中去
	virtual void Read(LPSTREAM/*,StgCfg*&*/) = 0;
	virtual void Write(LPSTREAM/*,const StgCfg*&*/) = 0;
};

struct StgNormalCfg : StgCfg{
	int bfloatToolbar = 1;
	int bRealtimePreview = 1;
	int bOpenEmailWhenInReadView = 0;
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
	/*
	pStream读写，不像FILE能直接将TCHAR*读写，
	所以没办法，暂时用TCHAR[]，既然是配置，合理定义大小即可，
	*/
	LPTSTR pszUsername /*= _T("hello")*/ = nullptr; //这样变量就不能写入了！
	int cchUsername = 0; //这两个写入之前一定要赋值
	//std::hash_map<
	virtual void Read(LPSTREAM/*, StgCfg*&*/);
	virtual void Write(LPSTREAM/*, const StgCfg*&*/);
	//TCHAR szUsername[STGCFG_UsernameLen] = { 0 };
	//CString szUsername;  没用
	//int cchUsername = 0;
	//TCHAR szShortname[STGCFG_UsernameLen] = { 0 };
	//int cchShortname = 0;	

	//拷贝构造
	//拷贝赋值
	//移动构造
	//移动赋值
	//析构
	//StgNormalCfg(/*int sz*/) /*: StgCfg(sz)*/{}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	//StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	//friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};

//
//校对

struct StgRevisionCfg : StgCfg {
	int nCheckWhenInput = 0;
	int nUseContextCheck = 0;
	int nStyle = 0;
	UINT8 szStyles[10] = { 0 };
	//std::bitset<10> bsStyles;

	//StgRevisionCfg(/*int sz*/)/* : StgCfg(sz)*/ { /*bsStyles.set();*/ }
};

struct StgRevisionCfg_AutoAmend : StgCfg {
	int nShowAutoAmendBtn = 0;
	int nUpcaseFirst2Char = 0;
	int nAmend3 = 0;
	int nAutoReplace = 0;//勾选了后面的字段才有效
	TCHAR szAutoReplace[STGCFG_AutoReplaceLen] = { 0 };//格式：acc-abc;你哈-你好;
	//int cchAutoReplace = 0;
	
	//StgRevisionCfg_AutoAmend(/*int sz*/) /*: StgCfg(sz)*/ {}
};

struct StgRevisionCfg_Operator : StgCfg {
	int nAddOpToContextMenu = 0;
	//std::bitset<8> bsOpts;
	UINT8 szOpts[8] = { 0 };

	//StgRevisionCfg_Operator(/*int sz*/)/* : StgCfg(sz)*/ {}
};


//
//
////保存
//struct StgSaveCfg : StgCfg {
//	int nSaveType = 0;
//	int nRecoverTime = 10;
//	bool bAutoRecover = true;
//	LPTSTR strRecoverFilePath;
//	int cchRecoverFilePath = 0;
//
//	StgSaveCfg(/*int sz*/) /*: StgCfg(sz)*/ {}
//};
//
//
////自定义



//Stg辅助类
class CSSFile;
class IStgCfgOperator {
public:
	//virtual HRESULT GetStgCfgs() = 0;
	//virtual HRESULT SetStgCfgs() = 0;

protected:
	//StgCfg* m_cfg = nullptr;
	CSSFile* m_pSSFile = nullptr;
	LPSTREAM m_pStream = nullptr;
	//bool m_bDirty = false;
};

//
class CSSFile {
public:
	//子存储名字、类型
	//enum TYPE { Storage, Stream };
	//union INFO {
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//};
	//struct Node {
	//	CString name, parentName;
	//	TYPE type;//节点类型
	//	//INFO info;
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//	StgCfgEnum emCfg;//配置类型
	//	Node(CString nm, CString fnm, TYPE t, StgCfg* p = nullptr, StgCfgEnum em = StgCfgEnumBuff) :
	//		name(nm), parentName(fnm), type(t), pCfg(p), emCfg(em) {}
	//};

	struct StorageNode {
		int idx = 0;
		CString name;
		LPSTORAGE& pParentStorage; //如果是指针，那就是一份copy，源变化不会影响这里
		//LPSTORAGE pParentStorage = nullptr;
		//StorageNode() {}
		StorageNode(int i,CString nm, LPSTORAGE& p) : idx(i),name(nm), pParentStorage(p){}
		StorageNode(const StorageNode& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
		//StorageNode(StorageNode&& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
		//StorageNode& operator=(StorageNode&& rhs) noexcept {
		//	idx = rhs.idx; name = rhs.name; pParentStorage = rhs.pParentStorage; }
	};
	struct StreamNode {//stream节点属性
		StgCfgEnum em;//唯一的，代表这个流（配置项）
		CString name;//流名称
		StgCfg* cfg;//配置
		std::vector<StorageNode> vecPos;//流的位置链

		StreamNode(StgCfgEnum e, CString nm, StgCfg* _cfg, std::vector<StorageNode>&& vec/*位置链*/)
			: em(e),name(nm),cfg(_cfg), vecPos(vec){}
	};
	//
	std::vector<LPSTORAGE> m_vecStorage; //所有的配置存储对象，存储对象的索引参照《配置文档结构图》定义

	//打开文档
	CSSFile(CString& filename);
	~CSSFile();
	//struct StorageData
	//{
	//	IStorage *Stg = nullptr;
	//	StorageData *ParentStg = nullptr;
	//};

	//获取所有配置
	bool GetAllCfg();
	//获取指定配置 只是LPSTREAM没用
	bool GetCfg(StgCfgEnum em, LPSTREAM* pStream);
	//文档是否打开
	bool IsOpen() const;

protected:
	//打开复合文档
	bool OpenSSFile(CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//关闭复合文档
	//void Close();
	//创建复合文档
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//读取所有配置
	bool ReadAllCfg();
	//打开存储对象
	//bool OpenStroage(const CString & name, /*LPSTORAGE pStorage, */DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//打开流
	//bool OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//创建存储对象
	//bool CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//创建流
	//bool CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);

	//获取根存储
	//IStorage * GetRootStorage() const;
	//创建默认配置
	//bool CreateDefaultCfg();
	//释放打开的存储对象
	void ReleaseStorage();

private:
	//查找父节点存储对象
	//Node& FindParentNode(std::list<Node>::iterator it/*当前节点*/, const CString& name/*父节点名*/);
	//处理继承关系
	void TransformBase2Derived(StreamNode& node, void*& pv, ULONG& len);


protected:
	bool m_bOpen = false;
	//CString m_strFilename;
	LPSTORAGE m_pRootStg = nullptr;
	//StorageData *m_pCurrentStg = nullptr;
	//std::list<Node> m_liNode;
	std::vector<StreamNode> m_vecStreamNode;
};