#pragma once
#include <bitset>
//#include <string>
//#include <vector>

/*
配置结构体都用“移动”
operator= 和 swap后期采用模板
*/

//配置项
enum StgCfgs {
	StgCfgs_Normal,
	StgCfgs_Revision,
	StgCfgs_Save,
	StgCfgs_Custom,
	StgCfgs_Buff
};

//详细配置项
enum StgDetailedCfgs {
	StgDetailedCfgs_Normal,
	StgDetailedCfgs_Revision_AutoAmend,
	StgDetailedCfgs_Revision_Operator,
	StgDetailedCfgs_Revision,
	StgDetailedCfgs_Save,
	StgDetailedCfgs_Custom,
	StgDetailedCfgs_Buff
};
extern const CString g_StgStreamNames[];//const要加


//常规
//enum StgNormalColorScheme {
//	StgNormalColorScheme_Red,
//	StgNormalColorScheme_Green,
//	StgNormalColorScheme_Blue,
//	StgNormalColorScheme_Buff
//};
//const CString StgNormalColorScheme

//enum StgNormalScreenTipStyle {
//	StgNormalScreenTipStyle_1,
//	StgNormalScreenTipStyle_2,
//	StgNormalScreenTipStyle_3,
//	StgNormalScreenTipStyle_Buff
//};

//结构基类
struct StgCfg{};

struct StgNormalCfg : StgCfg{
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	/*StgNormalColorScheme  emColorScheme = StgNormalColorScheme_Green;
	StgNormalScreenTipStyle emScreenTipStyle = StgNormalScreenTipStyle_1;*/
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
	CString strUsername;
	CString strShortname;
	bool bOpenEmailWhenInReadView = false;

	//拷贝构造
	//拷贝赋值
	//移动构造
	//移动赋值
	//析构
	//StgNormalCfg() {}
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
	bool bAutoReplace = false;//勾选了后面字段才有效
	CString strAutoRplace;//格式：acc-abc;你哈-你好;
	
	//StgRevisionAutoAmend_AutoAmend& operator=(StgRevisionAutoAmend_AutoAmend&& rhs) noexcept;
	//friend void swap(StgRevisionAutoAmend_AutoAmend& lhs, StgRevisionAutoAmend_AutoAmend& rhs);
};

struct StgRevisionCfg_Operator : StgCfg {
	bool bAddOpToContextMenu = false;
	std::bitset<8> bsOpts;


	//StgRevisionAutoAmend_Operator& operator=(StgRevisionAutoAmend_Operator&& rhs) noexcept;
	//friend void swap(StgRevisionAutoAmend_Operator& lhs, StgRevisionAutoAmend_Operator& rhs);
};

//enum StgRevisionStyleEnum {
//	StgRevisionStyle_Normal,
//	StgRevisionStyle_Custom,
//	StgRevisionStyle_Buff
//};
//struct StgRevisionStyle {
//	StgRevisionStyleEnum style = StgRevisionStyle_Normal;
//	std::bitset<10> bsStyles;
//
//	StgRevisionStyle() { bsStyles.set(); }
//	//StgRevisionStyle& operator=(StgRevisionStyle&& rhs) noexcept;
//	//friend void swap(StgRevisionStyle& lhs, StgRevisionStyle& rhs);
//
//};

struct StgRevisionCfg : StgCfg {
	//StgRevisionCfg_AutoAmend stAutoAmend;
	//StgRevisionAutoAmend_Operator stOperator;
	bool bCheckWhenInput = false;
	bool bUseContextCheck = false;
	int nStyle = 0;
	//StgRevisionStyle stStyle;
	std::bitset<10> bsStyles;

	StgRevisionCfg() { bsStyles.set(); }
	//拷贝构造
	//拷贝赋值
	//移动构造
	//移动赋值
	//析构
	//StgNormalCfg() {}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	//StgRevision& operator=(StgRevision&& rhs) noexcept;
	//friend void swap(StgRevision& lhs, StgRevision& rhs);
};


//保存
//enum StgSaveSaveType{
//	StgSaveSaveType_Docx,
//	StgSaveSaveType_Doc,
//	StgSaveSaveType_Html,
//	StgSaveSaveType_Txt,
//	StgSaveSaveType_Xml,
//	StgSaveSaveType_Buff
//};
struct StgSaveCfg : StgCfg {
	//StgSaveSaveType emSaveType = StgSaveSaveType_Docx;
	int nSaveType = 0;
	bool bAutoRecover = true;
	int nRecoverTime = 10;
	CString strRecoverFilePath = _T("C:\\Users\\dmxjMao\\Documents\\");

	//StgSave& operator=(StgSave&& rhs) noexcept;
	//friend void swap(StgSave& lhs, StgSave& rhs);
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
	struct StorageData
	{
		IStorage *Stg = nullptr;
		StorageData *ParentStg = nullptr;
	};
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

protected:
	bool m_bOpen = false;
	CString m_strFilename;
	IStorage *m_pRootStg = nullptr;
	StorageData *m_pCurrentStg = nullptr;


};