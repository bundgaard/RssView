#include "pch.h"
#include "RedditModel.h"


namespace Woo
{

	using namespace winrt;
	using namespace Windows::Data::Json;

	RedditModel::RedditModel(winrt::hstring const& jsonstring)
	{
		auto obj = JsonObject::Parse(jsonstring);
		GET_NAMED_STRING(obj, _kind);

		if (obj.HasKey(_data))
		{
			m_data = RedditData(obj.GetNamedObject(_data).Stringify());
		}
	}

}
