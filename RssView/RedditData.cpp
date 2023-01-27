#include "pch.h"
#include "RedditModel.h"

namespace Woo
{

	constexpr wchar_t _title[] = L"title";
	constexpr wchar_t _author[] = L"author";
	constexpr wchar_t _url[] = L"url";
	constexpr wchar_t _children[] = L"children";


	using namespace winrt;
	using namespace Windows::Data::Json;


	RedditData::RedditData(winrt::hstring const& jsonstring)
	{
		auto obj = JsonObject::Parse(jsonstring);
		if (obj.HasKey(_children))
		{
			auto children = obj.GetNamedArray(_children);
			for (auto const& child : children)
			{
				auto childObj = child.GetObject();
				m_children.push_back(RedditModel(childObj.Stringify()));
			}
		}
		if (obj.HasKey(_author))
		{
			m_author = (obj.GetNamedString(_author));
		}

		if (obj.HasKey(_url))
		{
			m_url = (obj.GetNamedString(_url));
		}

		if (obj.HasKey(_title))
		{
			m_title = (obj.GetNamedString(_title));
		}



	}

}
