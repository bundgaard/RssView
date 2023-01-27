#pragma once
#include "pch.h"


namespace Woo
{



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


	class RedditModel;
	class RedditData
	{
		std::vector<RedditModel> m_children;
		std::wstring m_title;
		std::wstring m_author;
		std::wstring m_url;

	public:
		RedditData() = default;
		explicit RedditData(winrt::hstring const& jsonstring);


		std::vector<RedditModel> Children()
		{
			return m_children;
		}

		std::wstring Title()
		{
			return m_title;
		}

		std::wstring Author()
		{
			return m_author;
		}

		std::wstring Url() { return m_url; }
	};

	class RedditModel
	{
		std::string m_kind;
		RedditData m_data;

	public:
		RedditModel() = default;
		explicit RedditModel(winrt::hstring const& jsonstring);


		RedditData Data()
		{
			return m_data;
		}

		std::string Kind()
		{
			return m_kind;
		}
	};




}
