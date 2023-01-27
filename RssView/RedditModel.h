#pragma once
#include "pch.h"

#define GET_PROPERTY_WSTRING(name, variable) std::wstring  name()			\
	{																		\
		return variable;													\
	}
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
	constexpr wchar_t _permalink[] = L"permalink";
	constexpr wchar_t _kind[] = L"kind";
	constexpr wchar_t _data[] = L"data";

	inline std::string ConvertToUTF8(winrt::hstring const& text)
	{
		auto reserve = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), nullptr, 0, "", nullptr);
		std::string output;
		output.resize(reserve);

		return output;
	}


	inline std::string ConvertToUTF8(std::wstring const& text)
	{
		auto reserve = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), nullptr, 0, "", nullptr);
		std::string output;
		output.resize(reserve);

		return output;
	}


	class RedditModel; // Forward declaration

	class RedditData
	{
		std::vector<RedditModel> m_children;
		std::wstring m_title;
		std::wstring m_author;
		std::wstring m_url;
		std::wstring m_name;
		std::wstring m_permalink;

	public:
		RedditData() = default;
		explicit RedditData(winrt::hstring const& jsonstring);


		std::vector<RedditModel> Children()
		{
			return m_children;
		}

		GET_PROPERTY_WSTRING(Title, m_title); // Might be a bad idea, but kind of meh on writing these by hand, so thought a macro was justifiable for now.
		GET_PROPERTY_WSTRING(Author, m_author);
		GET_PROPERTY_WSTRING(Url, m_url);
		GET_PROPERTY_WSTRING(Name, m_name);
		GET_PROPERTY_WSTRING(Permalink, m_permalink);

	};

	class RedditModel
	{
		std::wstring m_kind;
		RedditData m_data;

	public:
		RedditModel() = default;
		explicit RedditModel(winrt::hstring const& jsonstring);


		RedditData Data()
		{
			return m_data;
		}

		GET_PROPERTY_WSTRING(Kind, m_kind);
	};




}
