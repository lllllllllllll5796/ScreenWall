#include "stdafx.h"
#include "SSFile.h"
#include "ScreenWall.h"

using std::vector;

CSSFile::CSSFile(CString filename)
{

	m_vecStorage.resize(2); //大小根据《配置结构图》
	auto& vecCfg = g_GobalVariable.vecCfg;
	m_vecStreamNode = { 
		//位置链根据《配置结构图》 /*vector成员：配置枚举，流名称，默认配置结构，位置链（idx，名称，父节点指针）*/
		StreamNode(StgCfgEnum_LoginUser, _T("用户"), vecCfg[StgCfgEnum_LoginUser], vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]) })/*位置链*/)/*,
																																				  StreamNode(StgCfgEnumRevision, _T("校对"), vec[StgCfgEnumRevision],
																																				  vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]), StorageNode(1,_T("校对"),m_vecStorage[0]) })),
																																				  StreamNode(StgCfgEnumRevision_AutoAmend,_T("自动更正"), vec[StgCfgEnumRevision_AutoAmend],
																																				  vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("校对"),m_vecStorage[0]), StorageNode(2,_T("自动更正"),m_vecStorage[1]) })),
																																				  StreamNode(StgCfgEnumRevision_Operator,_T("操作"), vec[StgCfgEnumRevision_Operator],
																																				  vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("校对"),m_vecStorage[0]), StorageNode(2,_T("自动更正"),m_vecStorage[1]) }))*/
	};


	bool bRet = true;
	bRet = OpenSSFile(filename, STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	if (false == bRet) {
		//文档不存在，则创建默认配置
		//优化：默认配置在安装程序里写，如果配置结构发生了变化，在安装程序里读取并重新写入配置
		try {
			bRet = CreateSSFile(filename);
			if (false == bRet)
				throw std::logic_error("CreateSSFile Failed !");
		}
		catch (std::logic_error err) {
			AfxMessageBox(CA2T(err.what()));
		}
		return;
	}
	else {
		//根存储没有关闭，文档就无法删除，ReleaseStorage会删除
		m_vecStorage[0] = m_pRootStg;
		m_bOpen = true;
	}

}



CSSFile::~CSSFile()
{
	ReleaseStorage();
}

bool CSSFile::GetAllCfg()
{
	if (m_bOpen) {
		//成功打开文件，则读取配置						
		return ReadAllCfg();
	}
	else {
		return false;
	}
}

bool CSSFile::GetCfg(StgCfgEnum em, LPSTREAM* pStream)
{
	if (m_bOpen) {
		HRESULT hr = S_OK;
		DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
		auto& path = m_vecStreamNode[em].vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end(); ++it) { //位置链
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//不存在
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->OpenStorage(stgnode.name, nullptr, mode, nullptr, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//优化：结构化异常处理
					ReleaseStorage();//释放vecStorage
					return false;
				}
			}
		}
		// 在存储链的最后一个存储对象下创建流，事务模式
		//DWORD sMode = STGM_TRANSACTED;  //基于文档的流对象不支持事务模式！
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		hr = pStg->OpenStream(m_vecStreamNode[em].name, nullptr, mode, 0, pStream);
		if (FAILED(hr)) {
			//pStream->Release();
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool CSSFile::CreateSSFile(const CString & filename, DWORD mode)
{
	if (::StgCreateDocfile(filename, mode, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	//m_strFilename = filename;
	m_vecStorage[0] = m_pRootStg; //其他默认为空

								  //创建默认配置
	HRESULT hr = S_OK;
	for (auto& node : m_vecStreamNode) {
		auto& path = node.vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end(); ++it) { //位置链
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//不存在
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->CreateStorage(stgnode.name, mode, 0, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//优化：结构化异常处理
								 //ReleaseStorage();
					ReleaseStorage();//释放vecStorage
					return false;
				}
			}
		}
		//在存储链的最后一个存储对象下创建流
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		LPSTREAM pStream = nullptr;
		hr = pStg->CreateStream(node.name, mode, 0, 0, &pStream);
		if (FAILED(hr)) {
			pStream->Release();
			return false;
		}
		else {

			StgCfg* p = node.cfg;
			p->Write(pStream);
		}
	}

	return true;
}



bool CSSFile::OpenSSFile(CString & filename, DWORD mode)
{
	//if (m_bOpen)
	//	Close();

	if (StgOpenStorage(filename.GetBuffer(), NULL, mode, NULL, 0, &m_pRootStg) != S_OK) {
		return false;
	}

	return true;
}


bool CSSFile::IsOpen() const
{
	return m_bOpen;
}



void CSSFile::ReleaseStorage()
{
	//释放内存
	for (auto lp : m_vecStorage) {
		if (lp)
			lp->Release();
	}
	m_bOpen = false;
}


bool CSSFile::ReadAllCfg()
{
	HRESULT hr = S_OK;
	DWORD mode = STGM_READ | STGM_SHARE_EXCLUSIVE;
	/*m_vecStreamNode 成员：配置枚举，流名称，默认配置结构，位置链
	*/
	for (auto& node : m_vecStreamNode) {
		auto& path = node.vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end(); ++it) {
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//未打开
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->OpenStorage(stgnode.name, nullptr, mode, nullptr, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//优化：结构化异常处理
					ReleaseStorage();//释放m_vecStorage
					return false;
				}
			}
		}
		//在位置链的最后一个存储对象下读取流
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		LPSTREAM pStream = nullptr;
		hr = pStg->OpenStream(node.name, nullptr, mode, 0, &pStream);
		if (FAILED(hr)) {
			//pStream->Release();  这个要不要呢？
			return false;
		}
		else {
			StgCfg* pCfg = g_GobalVariable.vecCfg[node.em];

			pCfg->Read(pStream);
		}
	}

	return true;
}