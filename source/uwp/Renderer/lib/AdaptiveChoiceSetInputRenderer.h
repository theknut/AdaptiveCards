// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveChoiceSetInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveChoiceSetInputRenderer : AdaptiveChoiceSetInputRendererT<AdaptiveChoiceSetInputRenderer>
    {
    public:
        AdaptiveChoiceSetInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    private:
        static std::vector<std::string> GetChoiceSetValueVector(winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);

        static bool IsChoiceSelected(std::vector<std::string> selectedValues, winrt::AdaptiveChoiceInput const& choice);

        winrt::Windows::UI::Xaml::UIElement
        BuildExpandedChoiceSetInput(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                    winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                                    winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput,
                                    bool isMultiSelect);

        winrt::Windows::UI::Xaml::UIElement BuildCompactChoiceSetInput(
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
            winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);

        winrt::Windows::UI::Xaml::UIElement BuildFilteredChoiceSetInput(
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
            winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveChoiceSetInputRenderer
        : AdaptiveChoiceSetInputRendererT<AdaptiveChoiceSetInputRenderer, implementation::AdaptiveChoiceSetInputRenderer>
    {
    };
}
