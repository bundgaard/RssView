#include "pch.h"
#include "ItemViewModel.h"
#if __has_include("ItemViewModel.g.cpp")
#include "ItemViewModel.g.cpp"
#endif

namespace winrt::RssView::implementation
{
    
    ItemViewModel::ItemViewModel()
    {
        m_items = winrt::single_threaded_observable_vector<RssView::Item>();
    }

    Windows::Foundation::Collections::IObservableVector<RssView::Item> ItemViewModel::Items()
    {
        return m_items;
    }
}
