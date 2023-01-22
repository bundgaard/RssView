#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.Web.Syndication.h>
#include <ppltasks.h>

using namespace concurrency;

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace RssView;

namespace winrt::RssView::implementation
{


	ItemViewModel MainPage::RssItemsViewModel()
	{
		return m_items;
	}

	IAsyncAction MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		auto url = rssURL().Text();
		if (!url.empty())
		{

			Uri uri{ url.c_str() };

			SyndicationClient client;
			SyndicationFeed feed = co_await client.RetrieveFeedAsync(uri);
			
			for (auto const& item : feed.Items())
			{
				auto title = item.Title();
				auto content = item.Content();
				auto itm = make<RssView::implementation::Item>(title.Text().c_str(), content.Text().c_str());
				RssItemsViewModel().Items().Append(itm);
			}

		}

		co_return;
	}
}
