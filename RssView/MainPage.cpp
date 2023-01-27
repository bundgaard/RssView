#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Microsoft.Web.WebView2.Core.h>

#include "RedditModel.h"

namespace winrt::RssView::implementation
{
	using namespace winrt;
	using namespace concurrency;


	using namespace Windows::Foundation;
	using namespace Windows::System;

	using namespace Windows::UI::Xaml;
	using namespace Windows::Web::Syndication;
	using namespace Windows::Web::Http;
	using namespace Windows::Data::Json;
	using namespace Windows::UI::Xaml::Input;
	using namespace Windows::UI::Xaml::Media::Imaging;

	using namespace RssView;
	using namespace Woo;

}

namespace winrt::RssView::implementation
{


	RssView::ItemViewModel MainPage::RssItemsViewModel()
	{
		return m_items;
	}

	IAsyncAction MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		co_await DoFetch();
		co_return;
	}

	Windows::Foundation::IAsyncAction MainPage::ClearHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
	{
		RssItemsViewModel().Items().Clear();
		BigImage().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
		rssURL().Text(L"");
		co_return;
	}
	IAsyncAction MainPage::DoFetch()
	{
		LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Visible);
		auto url = rssURL().Text();
		if (url.empty()) // TODO: we can check if rss or json... or have a selection box the user can select them selves.
		{
			OutputDebugString(L"URL was empty");
			co_return;
		}
		auto items = RssItemsViewModel().Items();
		items.Clear();

		Uri uri{ url.c_str() };
		Windows::Web::Http::HttpClient httpClient;
		try
		{
			hstring respString;
			auto response = co_await httpClient.GetAsync(uri);
			(void)response.EnsureSuccessStatusCode();
			respString = co_await response.Content().ReadAsStringAsync();
			auto model = RedditModel(respString);
			for (auto& child : model.Data().Children())
			{
				auto data = child.Data();
				auto item = make<RssView::implementation::Item>(data.Title().c_str(), data.Url().c_str());

				items.Append(item);
			}
		}
		catch (...)
		{
			OutputDebugStringW(L" caught exception foo");
		}


		if (items.Size() == 0)
		{
			OutputDebugString(L"No items added");
		}
		LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

		co_return;
	}

	void MainPage::rssItems_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
	{
		auto foo = e.ClickedItem().as<RssView::Item>();
		OutputDebugString(foo.Title().c_str());
		OutputDebugStringW(L"\n");
		OutputDebugStringW(foo.Content().c_str());
		OutputDebugStringW(L"\n");
		if (foo != nullptr)
		{
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap = Windows::UI::Xaml::Media::Imaging::BitmapImage{};
			Uri uri{ foo.Content().c_str() };
			bitmap.UriSource(uri);
			BigImage().Source(bitmap);

			BigImage().Visibility(Visibility::Visible);
		}


	}

	IAsyncAction MainPage::KeyUp_OnEnter(winrt::Windows::Foundation::IInspectable const& sender, ::winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
		if (e.Key() == Windows::System::VirtualKey::Enter)
		{
			OutputDebugString(L"OnEnter");
			co_await DoFetch();
		}
		co_return;
	}
}


