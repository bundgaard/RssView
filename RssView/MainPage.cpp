#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.System.h>
#include <ppltasks.h>

using namespace concurrency;

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::System;
using namespace RssView;

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
		co_return;
	}

	IAsyncAction MainPage::DoFetch()
	{
		LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Visible);
		auto url = rssURL().Text();
		if (!url.empty()) // TODO: we can check if rss or json... or have a selection box the user can select them selves.
		{

			Uri uri{ url.c_str() };
			Windows::Web::Http::HttpClient httpClient;
			auto respString{ co_await httpClient.GetStringAsync(uri) };

			auto json = Windows::Data::Json::JsonObject::Parse(respString);
			try
			{
				auto data = json.GetNamedObject(L"data");

				auto children = data.GetNamedArray(L"children");
				auto items = RssItemsViewModel().Items();
				items.Clear();
				for (auto const& child : children)
				{
					try {
						auto obj = child.GetObject();
						auto data = obj.GetNamedObject(L"data");
						auto title = data.GetNamedString(L"title");
						auto overridden_url = data.GetNamedString(L"url_overridden_by_dest");
						auto item = make<RssView::implementation::Item>(title.c_str(), overridden_url.c_str());

						items.Append(item);
					}
					catch (winrt::hresult_error const& ex)
					{
						OutputDebugString(L"Failed to add child as we could not find the i");
					}


				}
				if (items.Size() == 0)
				{
					OutputDebugString(L"No items added");
				}
				LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

				/*SyndicationClient client;
				SyndicationFeed feed = co_await client.RetrieveFeedAsync(uri);

				for (auto const& item : feed.Items())
				{
					auto title = item.Title();
					auto content = item.Content();
					auto itm = make<RssView::implementation::Item>(title.Text().c_str(), content.Text().c_str());
					RssItemsViewModel().Items().Append(itm);
				}*/


			}
			catch (winrt::hresult_error const& ex)
			{
				OutputDebugStringW(L"Failed to find element in JSON");
				OutputDebugStringW(ex.message().c_str());
			}

		}
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


