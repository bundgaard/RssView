#pragma once

#include "Item.g.h"
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::RssView::implementation
{
    struct Item : ItemT<Item>
    {
        Item() = delete;
        Item(hstring const& title, hstring const& content);

        hstring Title();
        hstring Content();
        // Property changed notifications.
        event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const&);
        void PropertyChanged(event_token const&);
    private:
        hstring m_title;
        hstring m_content;

        // Property changed notifications.
        void RaisePropertyChanged(hstring const&);
        event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::RssView::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
