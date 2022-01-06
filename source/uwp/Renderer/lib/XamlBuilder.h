// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

namespace AdaptiveCards::Rendering::Uwp
{
    struct XamlBuilder : winrt::implements<XamlBuilder, IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        void AllImagesLoaded() override;
        void ImagesLoadingHadError() override;

        static winrt::Windows::UI::Xaml::FrameworkElement
        BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard,
                                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                      XamlBuilder* xamlBuilder,
                                      winrt::ContainerStyle defaultContainerStyle =
                                          winrt::ContainerStyle::Default);

        // TODO: not sure what we need this for? Are they for public?
        // TODO: I think these methods are created so people from outside can listen to images loading?
        void AddListener(::AdaptiveCards::Rendering::Uwp::IXamlBuilderListener* listener);
        void RemoveListener(::AdaptiveCards::Rendering::Uwp::IXamlBuilderListener* listener);
        void SetFixedDimensions(uint32_t width, uint32_t height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static void BuildPanelChildren(
            winrt::IVector<winrt::IAdaptiveCardElement> const& children,
            winrt::Panel ParentPanel,
            winrt::AdaptiveRenderContext context,
            winrt::AdaptiveRenderArgs renderArgs,
            std::function<void(rtxaml::UIElement const& child)> childCreatedCallback);

        winrt::Windows::UI::Xaml::UIElement BuildImage(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::com_ptr<ImageLoadTracker> m_imageLoadTracker;
        // TODO: why do we need this?
        std::set<IXamlBuilderListener*> m_listeners;
        std::vector<winrt::IAsyncOperationWithProgress<winrt::IInputStream, winrt::HttpProgress>> m_getStreamOperations;
        std::vector<winrt::IAsyncOperationWithProgress<uint64_t, uint64_t>> m_copyStreamOperations;
        std::vector<winrt::IAsyncOperationWithProgress<uint32_t, uint32_t>> m_writeAsyncOperations;
        uint32_t m_fixedWidth = 0;
        uint32_t m_fixedHeight = 0;

        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;

        // TODO: can we move word static to the function name?
        static std::pair<winrt::Panel, winrt::Windows::UI::Xaml::UIElement>
        CreateRootCardElement(winrt::IAdaptiveCard const& adaptiveCard,
                              winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                              winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                              XamlBuilder* xamlBuilder);

        template<typename T>
        void SetAutoSize(T const& destination,
                         winrt::IInspectable const& parentElement,
                         winrt::IInspectable const& imageContainer,
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T const& destination,
                            winrt::ImageSource const& imageSource,
                            winrt::Stretch stretch = winrt::Stretch::UniformToFill);

        // TODO: do we want to return bool to indicate success/failure?
        template<typename T>
        void SetImageOnUIElement(winrt::Uri const& imageUrl,
                                 T const& uiElement,
                                 winrt::AdaptiveCards::Rendering::Uwp::AdaptiveCardResourceResolvers const& resolvers,
                                 bool isAutoSize,
                                 winrt::IInspectable const& parentElement,
                                 winrt::IInspectable const& imageContainer,
                                 bool isVisible,
                                 winrt::Stretch stretch = winrt::Stretch::UniformToFill);

        template<typename T>
        void PopulateImageFromUrlAsync(winrt::Uri const& imageUrl, T const& imageControl);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
