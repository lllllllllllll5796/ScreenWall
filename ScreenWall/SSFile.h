#pragma once
#include <vector>
#include "Stg.h"

class CSSFile {
public:
	struct StorageNode {
		int idx = 0;
		CString name;
		LPSTORAGE& pParentStorage; //如果是指针，那就是一份copy，源变化不会影响这里
		StorageNode(int i, CString nm, LPSTORAGE& p) : idx(i), name(nm), pParentStorage(p) {}
		StorageNode(const StorageNode& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
	};
	struct StreamNode {//stream节点属性
		StgCfgEnum em;//唯一的，代表这个流（配置项）
		CString name;//流名称
		StgCfg* cfg;//配置
		std::vector<StorageNode> vecPos;//流的位置链

		StreamNode(StgCfgEnum e, CString nm, StgCfg* _cfg, std::vector<StorageNode>&& vec/*位置链*/)
			: em(e), name(nm), cfg(_cfg), vecPos(vec) {}
	};
	//
	std::vector<LPSTORAGE> m_vecStorage; //所有的配置存储对象，存储对象的索引参照《配置文档结构图》定义

										 //打开文档
	CSSFile(CString filename);
	~CSSFile();

	//获取所有配置
	bool GetAllCfg();
	//获取指定配置 只是LPSTREAM没用
	bool GetCfg(StgCfgEnum em, LPSTREAM* pStream);
	//文档是否打开
	bool IsOpen() const;

protected:
	//打开复合文档
	bool OpenSSFile(CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//创建复合文档
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//读取所有配置
	bool ReadAllCfg();
	//释放打开的存储对象
	void ReleaseStorage();

protected:
	bool m_bOpen = false;
	LPSTORAGE m_pRootStg = nullptr;
	std::vector<StreamNode> m_vecStreamNode;
};