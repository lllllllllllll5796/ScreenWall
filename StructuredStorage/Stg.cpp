#include "stdafx.h"
#include "Stg.h"
#include <algorithm>
#include <functional>


//stg下流的名字
//const CString g_StgStreamNames[] = { _T("常规"),
//_T("校对_自动更正"),_T("校对_操作"), _T("校对"), _T("保存"),_T("自定义") };

namespace {
	struct lambdaFindNodeName {
		bool operator()(const CSSFile::Node& node, const CString& name) {
			return node.name == name;
		}
	};
};


//常规

//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept {
//	swap(*this, rhs);
//}
//StgNormalCfg& StgNormalCfg::operator=(const StgNormalCfg& rhs) {
//	swap(*this, const_cast<StgNormalCfg&>(rhs));
//	return *this;
//}
//StgNormalCfg& StgNormalCfg::operator=(StgNormalCfg rhs) {
//	/*如果rhs是右值，则没有拷贝*/
//	swap(*this, rhs);
//	return *this;
//}
//StgNormalCfg& StgNormalCfg::operator=(StgNormalCfg&& rhs) noexcept{
//	swap(*this, rhs);
//	return *this;
//}
//
//inline void swap(StgNormalCfg& lhs, StgNormalCfg& rhs)
//{
//	using std::swap;
//	swap(lhs.bfloatToolbar, rhs.bfloatToolbar);
//	swap(lhs.bRealtimePreview, rhs.bRealtimePreview);
//	swap(lhs.emColorScheme, rhs.emColorScheme);
//	swap(lhs.emScreenTipStyle, rhs.emScreenTipStyle);
//	swap(lhs.strUsername, rhs.strUsername);
//	swap(lhs.strShortname, rhs.strShortname);
//	swap(lhs.bOpenEmailWhenInReadView, rhs.bOpenEmailWhenInReadView);
//}


//
CSSFile::CSSFile()
{
	//（节点名，父节点名，节点类型）
	auto& vec = g_GobalVariable.vecCfg;
	m_liNode = {
		Node(_T("STGCFG"),_T(""),Storage), //根节点要赋值一下
		Node(_T("Normal"),_T("STGCFG"),Stream, vec[StgCfgEnumNormal], StgCfgEnumNormal),
		Node(_T("Revision"),_T("STGCFG"),Storage),
		Node(_T("AutoAmend"),_T("Revision"),Storage),
		Node(_T("Revision"),_T("Revision"),Stream, vec[StgCfgEnumRevision], StgCfgEnumRevision),
		Node(_T("AutoAmend"),_T("AutoAmend"),Stream, vec[StgCfgEnumRevision_AutoAmend], StgCfgEnumRevision_AutoAmend),
		Node(_T("Operator"),_T("AutoAmend"),Stream, vec[StgCfgEnumRevision_Operator], StgCfgEnumRevision_Operator)
	};
}


bool CSSFile::CreateSSFile(const CString & filename, DWORD mode)
{
	if (::StgCreateDocfile(filename, mode, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	//m_strFilename = filename;

	//创建默认配置
	HRESULT hr = S_OK;
	auto it = m_liNode.begin();
	it->pStorage = m_pRootStg; //赋值根节点
	//it->info.pStorage = m_pRootStg;
	std::advance(it, 1); //跳过根节点
	for (; it != m_liNode.end(); ++it) {
		Node& node = *it;
		Node& parentNode = FindParentNode(it, node.parentName);//查找父节点

		if(Storage == node.type){
			hr = parentNode.pStorage->CreateStorage(node.name, mode, 0, 0, &node.pStorage);
			if (FAILED(hr))
				return false;
		}
		else/* if (Stream == node.type)*/ {
			LPSTREAM pStream = nullptr;
			hr = parentNode.pStorage->CreateStream(node.name, mode, 0, 0, &pStream);
			if (FAILED(hr)) {
				pStream->Release();
				return false;
			}
			else {
				ULONG ulWritten(0);
				hr = pStream->Write(node.pCfg, node.pCfg->nSize, &ulWritten);
				pStream->Release();
			}			
		}
		
	}

	//StorageData *sd = new StorageData;
	//sd->Stg = m_pRootStg;
	//sd->ParentStg = NULL;
	//m_pCurrentStg = sd;

	return true;
}


bool CSSFile::OpenSSFile(const CString & filename, DWORD mode)
{
	if (m_bOpen)
		Close();

	bool bRet = true;
	if (StgOpenStorage(filename, NULL, mode, NULL, 0, &m_pRootStg) != S_OK) {
		//不存在配置文档，则创建
		bRet = CreateSSFile(filename);
		ReleaseStorage();
	}

	//m_bOpen = true;
	//m_strFilename = filename;

	//StorageData *sd = new StorageData;
	//sd->Stg = m_pRootStg;
	//sd->ParentStg = NULL;
	//m_pCurrentStg = sd;

	return bRet;
}
bool CSSFile::CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode)
{
	//ASSERT(m_pCurrentStg && m_bOpen);

	//LPSTORAGE pStorage;
	//HRESULT hr = m_pCurrentStg->Stg->CreateStorage(name, mode, 0, 0, &pStorage);
	////if (S_OK == hr) {

	////}
	//return hr == S_OK;
	return true;
}

bool CSSFile::OpenStroage(const CString & name, /*LPSTORAGE* pStorage, */DWORD mode)
{
	/*ASSERT(m_pCurrentStg && m_bOpen);

	IStorage* pStg;
	HRESULT hr = m_pCurrentStg->Stg->OpenStorage(name, NULL, mode, NULL, 0, &pStg);
	if (hr == S_OK) {
		m_pCurrentStg->ParentStg = m_pCurrentStg;
		m_pCurrentStg->Stg = pStg;
	}
	else {
		if (CreateStroage(name, pStg)) {
			StorageData* pSD = new StorageData;
			pSD->ParentStg = m_pCurrentStg;
			pSD->Stg = pStg;

			m_pCurrentStg = pSD;

			return true;
		}

	}*/
	return false;
}

bool CSSFile::CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode)
{
	//HRESULT hr = m_pCurrentStg->Stg->CreateStream(name, mode, 0, 0, pStream);
	//return hr == S_OK;
	return true;
}

bool CSSFile::OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode)
{
	//ASSERT(m_pCurrentStg && m_bOpen);

	//HRESULT hr = m_pCurrentStg->Stg->OpenStream(name, 0, mode, 0, pStream);
	//if (S_OK != hr) {
	//	if (!CreateStream(name, pStream)) {
	//		return false;
	//	}
	//}
	return false;
}


void CSSFile::Close()
{
	//if (m_bOpen)
	//{
	//	// Release all pointers in the open tree:
	//	while (ExitStorage())
	//		;

	//	m_pCurrentStg->Stg->Release();
	//	delete m_pCurrentStg;

	//	m_pCurrentStg = NULL;
	//	m_pRootStg = NULL;
	//}

	//m_bOpen = false;
	//m_strFilename = _T("");
}

bool CSSFile::ExitStorage()
{
	//ASSERT(m_pCurrentStg && m_bOpen);

	//if (m_pCurrentStg->ParentStg)
	//{
	//	m_pCurrentStg->Stg->Release();
	//	StorageData* pSD = m_pCurrentStg->ParentStg;
	//	delete m_pCurrentStg;
	//	m_pCurrentStg = pSD;

	//	return true;
	//}
	//else
	//	return false; // no storage to exit out of without closing the file
	return true;
}

IStorage * CSSFile::GetRootStorage() const
{
	//ASSERT(m_pCurrentStg && m_bOpen);

	return m_pRootStg;
}

bool CSSFile::IsOpen() const
{
	return m_bOpen;
}

//bool CSSFile::CreateDefaultCfg()
//{
//	return true;
//}


CSSFile::Node& CSSFile::FindParentNode(std::list<Node>::iterator it/*当前节点*/, const CString& name/*父节点名*/)
{
	using std::placeholders::_1;
	auto f = std::bind(lambdaFindNodeName(), _1, name);
	auto itFind = std::find_if(m_liNode.begin(), it, f);
	return (*itFind);
}


void CSSFile::ReleaseStorage()
{
	//释放内存
	for (auto& node : m_liNode) {
		if (node.pStorage)
			node.pStorage->Release();
	}
}