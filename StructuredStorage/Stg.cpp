#include "stdafx.h"
#include "Stg.h"



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