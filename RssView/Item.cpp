#include "pch.h"
#include "Item.h"
#if __has_include("Item.g.cpp")
#include "Item.g.cpp"
#endif

namespace winrt::RssView::implementation
{
    using namespace Windows::UI::Xaml::Data;
}

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
    
    event_token Item::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value)
    {
        return m_propertyChanged.add(value);
    }
    
    void Item::PropertyChanged(event_token const& token)
    {
         m_propertyChanged.remove(token);
    }
    void Item::RaisePropertyChanged(hstring const& propertyName)
    {
        m_propertyChanged(*this, PropertyChangedEventArgs(propertyName));
    }
}
