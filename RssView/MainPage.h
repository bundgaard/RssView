#pragma once

#include "MainPage.g.h"
#include "ItemViewModel.h"
#include <winrt/Windows.Data.Json.h>

namespace winrt::RssView::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage()
		{
			m_items = make<RssView::implementation::ItemViewModel>();
			// Xaml objects should not call InitializeComponent during construction.
			// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

		}

		RssView::ItemViewModel RssItemsViewModel();


		Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);


	private:
		RssView::ItemViewModel m_items{ nullptr };
	};
}

namespace winrt::RssView::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}
