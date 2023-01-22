#include "pch.h"
#include "Item.h"
#if __has_include("Item.g.cpp")
#include "Item.g.cpp"
#endif

namespace winrt::RssView::implementation
{
    Item::Item(hstring const& title, hstring const& content) : m_title(title), m_content(content)
    {
    }
    hstring Item::Title()
    {
        return m_title;
    }
    hstring Item::Content()
    {
        return m_content;
    }
}
