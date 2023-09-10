#pragma once
#include <QWidget>
#include <QVBoxLayout>

class SettingsWidget : public QWidget
{
private:
    QVBoxLayout *vbox{ nullptr };
    void init_layout();
    
public:
    SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();
};

