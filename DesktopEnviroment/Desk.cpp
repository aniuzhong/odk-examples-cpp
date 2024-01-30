#include <cstdio>
#include <iostream>

extern "C" {
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>
}

#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/awt/WindowDescriptor.hpp>
#include <com/sun/star/awt/Toolkit.hpp>
#include <com/sun/star/awt/XSystemChildFactory.hpp>
#include <com/sun/star/frame/XFramesSupplier.hpp>
#include <com/sun/star/frame/XFrames.hpp>
#include <com/sun/star/frame/FrameSearchFlag.hpp>

void load(Window window)
{
     try {
        css::uno::Reference<css::uno::XComponentContext> context = cppu::bootstrap();
        css::uno::Reference<css::lang::XMultiComponentFactory> comp_factory = context->getServiceManager();

        css::uno::Reference<css::frame::XFrame> frame(comp_factory->createInstanceWithContext("com.sun.star.frame.Frame", context), css::uno::UNO_QUERY);

        css::uno::Reference<css::awt::XToolkit> toolkit(comp_factory->createInstanceWithContext("com.sun.star.awt.Toolkit", context), css::uno::UNO_QUERY);

        css::uno::Reference<css::awt::XSystemChildFactory> child_factory(toolkit, css::uno::UNO_QUERY);
        css::uno::Reference<css::awt::XWindowPeer> peer = child_factory->createSystemChild(css::uno::Any(window), css::uno::Sequence<sal_Int8>(), 6);
        if (!peer.is())
            printf("Could not initialize XWindowPeer\n");
        css::uno::Reference<css::awt::XWindow> xwindow(peer, css::uno::UNO_QUERY);
        if (!xwindow.is())
            printf("Could not initialize XWindow\n");
        frame->initialize(xwindow);
        css::uno::Reference<css::frame::XFramesSupplier> tree_root(comp_factory->createInstanceWithContext("com.sun.star.frame.Desktop", context), css::uno::UNO_QUERY);
        if (!tree_root.is())
            printf("Could not instantiate XFramsSupplier\n");
        css::uno::Reference<css::frame::XFrames> child_container = tree_root->getFrames();
        child_container->append(frame);
        rtl::OUString old_name = frame->getName();
        frame->setName("odk_officedev_desk");

        css::uno::Reference<css::uno::XInterface> desktop = comp_factory->createInstanceWithContext("com.sun.star.frame.Desktop", context);
        css::uno::Reference<css::frame::XComponentLoader> loader(desktop, css::uno::UNO_QUERY);
        
        css::uno::Sequence<css::beans::PropertyValue> load_props(0);
        css::uno::Reference<css::lang::XComponent> doc = loader->loadComponentFromURL("file:///home/aniu/Documents/Presentation.pptx",
                                                                                      "odk_officedev_desk", css::frame::FrameSearchFlag::CHILDREN, load_props);
        frame->setName(old_name);

        xwindow->setVisible(true);
    } catch (css::uno::Exception &e) {
        std::cout << e.Message << '\n';
        return;
    }
}

int main()
{
    printf("Press any key to load the document\n");

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }
    
    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 1920, 1080, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
        } else if (event.type == KeyPress) {
            printf("Key pressed\n");
            load(window);
        }
    }

    XCloseDisplay(display);

    return 0;
}
