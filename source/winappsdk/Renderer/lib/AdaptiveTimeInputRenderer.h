// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTimeInputRenderer.g.h"

// TODO: do we need this include?
#include "TimeInput.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTimeInputRenderer : AdaptiveTimeInputRendererT<AdaptiveTimeInputRenderer>
    {
        AdaptiveTimeInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveTimeInputRenderer : AdaptiveTimeInputRendererT<AdaptiveTimeInputRenderer, implementation::AdaptiveTimeInputRenderer>
    {
    };
}
