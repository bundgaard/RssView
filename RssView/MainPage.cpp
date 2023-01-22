#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.Web.Syndication.h>
#include <winrt/Windows.Web.Http.h>
#include <ppltasks.h>

using namespace concurrency;

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;
using namespace RssView;

namespace winrt::RssView::implementation
{


	RssView::ItemViewModel MainPage::RssItemsViewModel()
	{
		return m_items;
	}

	IAsyncAction MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		auto url = rssURL().Text();
		if (!url.empty())
		{

			Uri uri{ url.c_str() };
			Windows::Web::Http::HttpClient httpClient;
			auto respString = co_await httpClient.GetStringAsync(uri);
			auto json = Windows::Data::Json::JsonObject::Parse(respString);
			auto data = json.GetNamedObject(L"data");
			auto children = data.GetNamedArray(L"children");
			for(auto  const& child : children)
			{
				auto line = child.Stringify();
				auto obj = child.GetObject();
				auto data = obj.GetNamedObject(L"data");
				auto title = data.GetNamedString(L"title");
				auto overridden_url = data.GetNamedString(L"url_overridden_by_dest");
				auto item = make<RssView::implementation::Item>(title.c_str(), overridden_url.c_str());
				
				
				
				
				
				RssItemsViewModel().Items().Append(item);

			}
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

		co_return;
	}
}
