#pragma once

#include "Item.g.h"

namespace winrt::RssView::implementation
{
    struct Item : ItemT<Item>
    {
        Item() = delete;
        Item(hstring const& title, hstring const& content);

        hstring Title();
        hstring Content();

    private:
        hstring m_title;
        hstring m_content;
    };
}

namespace winrt::RssView::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
