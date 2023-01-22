#pragma once

#include "ItemViewModel.g.h"
#include "Item.h"

#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::RssView::implementation
{
    struct ItemViewModel : ItemViewModelT<ItemViewModel>
    {
        ItemViewModel();
        Windows::Foundation::Collections::IObservableVector<RssView::Item> Items();
    private:
        Windows::Foundation::Collections::IObservableVector<RssView::Item> m_items{ nullptr };
    };
}

namespace winrt::RssView::factory_implementation
{
    struct ItemViewModel : ItemViewModelT<ItemViewModel, implementation::ItemViewModel>
    {
    };
}
