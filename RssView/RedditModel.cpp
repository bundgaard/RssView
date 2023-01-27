#include "pch.h"
#include "RedditModel.h"


namespace Woo
{
	constexpr wchar_t _kind[] = L"kind";
	constexpr wchar_t _data[] = L"data";


	using namespace winrt;
	using namespace Windows::Data::Json;

	RedditModel::RedditModel(winrt::hstring const& jsonstring)
	{
		auto obj = JsonObject::Parse(jsonstring);
		if (obj.HasKey(_kind))
		{
			m_kind = ConvertToUTF8(obj.GetNamedString(_kind));
		}

		if (obj.HasKey(_data))
		{
			m_data = RedditData(obj.GetNamedObject(_data).Stringify());
		}
	}

}
