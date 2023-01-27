#include "pch.h"
#include "RedditModel.h"


namespace Woo
{
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

		GET_NAMED_STRING(obj, _author); // Kind of meh on writing these by hand, so thought a macro was justifiable
		GET_NAMED_STRING(obj, _url);
		GET_NAMED_STRING(obj, _title);
		GET_NAMED_STRING(obj, _permalink);


	}

}
