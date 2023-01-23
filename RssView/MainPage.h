#pragma once

#include "MainPage.g.h"
#include "ItemViewModel.h"
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Web.Syndication.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.UI.Xaml.Input.h>

#include <winrt/Windows.UI.Xaml.Media.Imaging.h>


namespace winrt::RssView::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
	private:
		
		RssView::ItemViewModel m_items{ nullptr };

	public:
		MainPage()
		{
			m_items = make<RssView::implementation::ItemViewModel>();
			// Xaml objects should not call InitializeComponent during construction.
			// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

		}

		RssView::ItemViewModel RssItemsViewModel();


		Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		Windows::Foundation::IAsyncAction DoFetch();

		void rssItems_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
		Windows::Foundation::IAsyncAction KeyUp_OnEnter(winrt::Windows::Foundation::IInspectable const& sender, ::winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);



	};
}

namespace winrt::RssView::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}
