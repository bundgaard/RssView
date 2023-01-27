#pragma once

#include "pch.h"
#include "MainPage.g.h"
#include "ItemViewModel.h"
#include <winrt/Windows.System.h>
#include <ppltasks.h>
#include <pplawait.h>


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
		Windows::Foundation::IAsyncAction ClearHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
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
