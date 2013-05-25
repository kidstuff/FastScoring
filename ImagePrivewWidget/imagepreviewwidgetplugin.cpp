#include "imagepreviewwidget.h"
#include "imagepreviewwidgetplugin.h"

#include <QtPlugin>

ImagePreviewWidgetPlugin::ImagePreviewWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImagePreviewWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool ImagePreviewWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImagePreviewWidgetPlugin::createWidget(QWidget *parent)
{
    return new ImagePreviewWidget(parent);
}

QString ImagePreviewWidgetPlugin::name() const
{
    return QLatin1String("ImagePreviewWidget");
}

QString ImagePreviewWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon ImagePreviewWidgetPlugin::icon() const
{
    return QIcon();
}

QString ImagePreviewWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImagePreviewWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImagePreviewWidgetPlugin::isContainer() const
{
    return false;
}

QString ImagePreviewWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImagePreviewWidget\" name=\"imagePreviewWidget\">\n</widget>\n");
}

QString ImagePreviewWidgetPlugin::includeFile() const
{
    return QLatin1String("imagepreviewwidget.h");
}

Q_EXPORT_PLUGIN2(imagepreviewwidgetplugin, ImagePreviewWidgetPlugin)
