#include "pch.h"
#include "RedditModel.h"

#define GET_NAMED_STRING(obj, name)				\
	if(obj.HasKey(##name)) {					\
		m##name = (obj.GetNamedString(##name)); \
	}
#define GET_NAMED_OBJECT(obj, name)				\
	if(obj.HasKey(##name))						\
	{											\
		m##name = (obj.GetNamedObject(##name)); \
	}
#define GET_NAMED_ARRAY(obj, name)				\
	if(obj.HasKey(##name))						\
	{											\
		 m##name = (obj.GetNamedArray(##name)); \
	}


#define CATCH_LOG(output) catch(...) { OutputDebugStringW(output); }


namespace Woo
{

	constexpr wchar_t _title[] = L"title";
	constexpr wchar_t _author[] = L"author";
	constexpr wchar_t _url[] = L"url";
	constexpr wchar_t _children[] = L"children";
	constexpr wchar_t _name[] = L"name";


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
				try
				{
					auto childObj = child.GetObject();
					m_children.push_back(RedditModel(childObj.Stringify()));
				}
				CATCH_LOG(L"failed to find object in children");

			}
		}

		GET_NAMED_STRING(obj, _author);
		GET_NAMED_STRING(obj, _url);
		GET_NAMED_STRING(obj, _title);


	}

}
