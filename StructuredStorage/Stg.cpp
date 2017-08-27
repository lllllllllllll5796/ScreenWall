#include "stdafx.h"
#include "Stg.h"

//stg下流的名字
const TCHAR* g_StgStreamNames[] = { _T("常规"),
_T("校对_自动更正"),_T("校对_操作"), _T("校对"), _T("保存"),_T("自定义") };


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
StgNormalCfg& StgNormalCfg::operator=(StgNormalCfg&& rhs) noexcept{
	swap(*this, rhs);
	return *this;
}

inline void swap(StgNormalCfg& lhs, StgNormalCfg& rhs)
{
	using std::swap;
	swap(lhs.bfloatToolbar, rhs.bfloatToolbar);
	swap(lhs.bRealtimePreview, rhs.bRealtimePreview);
	swap(lhs.emColorScheme, rhs.emColorScheme);
	swap(lhs.emScreenTipStyle, rhs.emScreenTipStyle);
	swap(lhs.strUsername, rhs.strUsername);
	swap(lhs.strShortname, rhs.strShortname);
	swap(lhs.bOpenEmailWhenInReadView, rhs.bOpenEmailWhenInReadView);
}


//校对
StgRevisionAutoAmend_AutoAmend& StgRevisionAutoAmend_AutoAmend::operator=(StgRevisionAutoAmend_AutoAmend&& rhs) noexcept {
	swap(*this, rhs);
	return *this;
}

inline void swap(StgRevisionAutoAmend_AutoAmend& lhs, StgRevisionAutoAmend_AutoAmend& rhs)
{
	using std::swap;
	swap(lhs.bShowAutoAmendBtn, rhs.bShowAutoAmendBtn);
	swap(lhs.bUpcaseFirst2Char, rhs.bUpcaseFirst2Char);
	swap(lhs.bAmend3, rhs.bAmend3);
	swap(lhs.bAutoReplace, rhs.bAutoReplace);
	swap(lhs.strAutoRplace, rhs.strAutoRplace);
}



StgRevisionAutoAmend_Operator& StgRevisionAutoAmend_Operator::operator=(StgRevisionAutoAmend_Operator&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}
inline void swap(StgRevisionAutoAmend_Operator& lhs, StgRevisionAutoAmend_Operator& rhs)
{
	using std::swap;
	swap(lhs.bAddOpToContextMenu, rhs.bAddOpToContextMenu);
	swap(lhs.bsOpts, rhs.bsOpts);
}


StgRevisionStyle& StgRevisionStyle::operator=(StgRevisionStyle&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}
inline void swap(StgRevisionStyle& lhs, StgRevisionStyle& rhs)
{
	using std::swap;
	swap(lhs.style, rhs.style);
	swap(lhs.bsStyles, rhs.bsStyles);
}

StgRevision& StgRevision::operator=(StgRevision&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}
inline void swap(StgRevision& lhs, StgRevision& rhs)
{
	using std::swap;
	swap(lhs.stAutoAmend, rhs.stAutoAmend);
	swap(lhs.stOperator, rhs.stOperator);
	swap(lhs.bCheckWhenInput, rhs.bCheckWhenInput);
	swap(lhs.bUseContextCheck, rhs.bUseContextCheck);
	swap(lhs.stStyle, rhs.stStyle);
}


//保存
StgSave& StgSave::operator=(StgSave&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}
inline void swap(StgSave& lhs, StgSave& rhs)
{
	using std::swap;
	swap(lhs.emSaveType, rhs.emSaveType);
	swap(lhs.bAutoRecover, rhs.bAutoRecover);
	swap(lhs.usRecoverTm, rhs.usRecoverTm);
	swap(lhs.strRecoverFilePath, rhs.strRecoverFilePath);
}



//


bool CSSFile::CreateSSFile(const CString & filename, DWORD mode)
{
	if (m_bOpen)
		Close();

	if (::StgCreateDocfile(filename, mode, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	m_strFilename = filename;

	StorageData *sd = new StorageData;
	sd->Stg = m_pRootStg;
	sd->ParentStg = NULL;
	m_pCurrentStg = sd;

	return true;
}


bool CSSFile::OpenSSFile(const CString & filename, DWORD mode)
{
	if (m_bOpen)
		Close();

	if (StgOpenStorage(filename, NULL, mode, NULL, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	m_strFilename = filename;

	StorageData *sd = new StorageData;
	sd->Stg = m_pRootStg;
	sd->ParentStg = NULL;
	m_pCurrentStg = sd;

	return true;
}


bool CSSFile::CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode)
{
	HRESULT hr = m_pCurrentStg->Stg->CreateStream(name, mode, 0, 0, pStream);
	return hr == S_OK;
}

bool CSSFile::OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode)
{
	ASSERT(m_pCurrentStg && m_bOpen);
	HRESULT hr = m_pCurrentStg->Stg->OpenStream(name, 0, mode, 0, pStream);
	return hr == S_OK;
}


void CSSFile::Close()
{
	if (m_bOpen)
	{
		// Release all pointers in the open tree:
		while (ExitStorage())
			;

		m_pCurrentStg->Stg->Release();
		delete m_pCurrentStg;

		m_pCurrentStg = NULL;
		m_pRootStg = NULL;
	}

	m_bOpen = false;
	m_strFilename = _T("");
}

bool CSSFile::ExitStorage()
{
	ASSERT(m_pCurrentStg && m_bOpen);

	if (m_pCurrentStg->ParentStg)
	{
		m_pCurrentStg->Stg->Release();
		StorageData* pSD = m_pCurrentStg->ParentStg;
		delete m_pCurrentStg;
		m_pCurrentStg = pSD;

		return true;
	}
	else
		return false; // no storage to exit out of without closing the file
}

IStorage * CSSFile::GetRootStorage() const
{
	ASSERT(m_pCurrentStg && m_bOpen);

	return m_pRootStg;
}

bool CSSFile::IsOpen() const
{
	return m_bOpen;
}