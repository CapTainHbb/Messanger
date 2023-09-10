#include <SettingsWidget.hpp>

SettingsWidget::SettingsWidget(QWidget *parent)
: QWidget(parent)
{
}

SettingsWidget::~SettingsWidget()
{
}

void SettingsWidget::init_layout()
{
    vbox = new QVBoxLayout(this);
    vbox->setObjectName("settings_widget_vbox");
}
