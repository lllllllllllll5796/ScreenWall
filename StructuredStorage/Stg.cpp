#include "stdafx.h"
#include "Stg.h"
#include <algorithm>
#include <functional>


//stg下流的名字
const CString g_StgStreamNames[] = { _T("常规"),
_T("校对_自动更正"),_T("校对_操作"), _T("校对"), _T("保存"),_T("自定义") };

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


//校对
//StgRevisionAutoAmend_AutoAmend& StgRevisionAutoAmend_AutoAmend::operator=(StgRevisionAutoAmend_AutoAmend&& rhs) noexcept {
//	swap(*this, rhs);
//	return *this;
//}
//
//inline void swap(StgRevisionAutoAmend_AutoAmend& lhs, StgRevisionAutoAmend_AutoAmend& rhs)
//{
//	using std::swap;
//	swap(lhs.bShowAutoAmendBtn, rhs.bShowAutoAmendBtn);
//	swap(lhs.bUpcaseFirst2Char, rhs.bUpcaseFirst2Char);
//	swap(lhs.bAmend3, rhs.bAmend3);
//	swap(lhs.bAutoReplace, rhs.bAutoReplace);
//	swap(lhs.strAutoRplace, rhs.strAutoRplace);
//}



//StgRevisionAutoAmend_Operator& StgRevisionAutoAmend_Operator::operator=(StgRevisionAutoAmend_Operator&& rhs) noexcept
//{
//	swap(*this, rhs);
//	return *this;
//}
//inline void swap(StgRevisionAutoAmend_Operator& lhs, StgRevisionAutoAmend_Operator& rhs)
//{
//	using std::swap;
//	swap(lhs.bAddOpToContextMenu, rhs.bAddOpToContextMenu);
//	swap(lhs.bsOpts, rhs.bsOpts);
//}
//
//
//StgRevisionStyle& StgRevisionStyle::operator=(StgRevisionStyle&& rhs) noexcept
//{
//	swap(*this, rhs);
//	return *this;
//}
//inline void swap(StgRevisionStyle& lhs, StgRevisionStyle& rhs)
//{
//	using std::swap;
//	swap(lhs.style, rhs.style);
//	swap(lhs.bsStyles, rhs.bsStyles);
//}
//
//StgRevision& StgRevision::operator=(StgRevision&& rhs) noexcept
//{
//	swap(*this, rhs);
//	return *this;
//}
//inline void swap(StgRevision& lhs, StgRevision& rhs)
//{
//	using std::swap;
//	swap(lhs.stAutoAmend, rhs.stAutoAmend);
//	swap(lhs.stOperator, rhs.stOperator);
//	swap(lhs.bCheckWhenInput, rhs.bCheckWhenInput);
//	swap(lhs.bUseContextCheck, rhs.bUseContextCheck);
//	swap(lhs.stStyle, rhs.stStyle);
//}
//
//
////保存
//StgSave& StgSave::operator=(StgSave&& rhs) noexcept
//{
//	swap(*this, rhs);
//	return *this;
//}
//inline void swap(StgSave& lhs, StgSave& rhs)
//{
//	using std::swap;
//	swap(lhs.emSaveType, rhs.emSaveType);
//	swap(lhs.bAutoRecover, rhs.bAutoRecover);
//	swap(lhs.usRecoverTm, rhs.usRecoverTm);
//	swap(lhs.strRecoverFilePath, rhs.strRecoverFilePath);
//}



//
CSSFile::CSSFile()
{
	//（节点名，父节点名，节点类型）
	m_liNode = {
		Node(_T("STGCFG"),_T(""),Storage), //根节点要赋值一下
		Node(_T("常规"),_T("STGCFG"),Stream, new StgNormalCfg),
		Node(_T("校对"),_T("STGCFG"),Storage),
		Node(_T("自动更正"),_T("校对"),Storage),
		Node(_T("校对"),_T("校对"),Stream, new StgRevisionCfg),
		Node(_T("自动更正"),_T("自动更正"),Stream, new StgRevisionCfg_AutoAmend),
		Node(_T("操作"),_T("自动更正"),Stream, new StgRevisionCfg_Operator)
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
	it->pStorage = m_pRootStg;
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
		else if (Stream == node.type) {
			LPSTREAM pStream = nullptr;
			hr = parentNode.pStorage->CreateStream(node.name, mode, 0, 0, &pStream);
			if (FAILED(hr)) {
				pStream->Release();
				return false;
			}
			else {
				//pStream->Write(node.pCfg, );
				pStream->Release();
			}
			

				
		}
		else {

		}
		
	}

	//释放内存
	for (auto& node : m_liNode) {
		if (node.pStorage)
			node.pStorage->Release();
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

	if (StgOpenStorage(filename, NULL, mode, NULL, 0, &m_pRootStg) != S_OK) {
		//不存在配置文档，创建
		if (!CreateSSFile(filename))
			return false;
	}

	//m_bOpen = true;
	//m_strFilename = filename;

	//StorageData *sd = new StorageData;
	//sd->Stg = m_pRootStg;
	//sd->ParentStg = NULL;
	//m_pCurrentStg = sd;

	return true;
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