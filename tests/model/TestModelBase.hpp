#pragma once

#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

#include <TestBase.hpp>

class TestModelBase : public TestBase
{
    Q_OBJECT;

public:
    TestModelBase();
    ~TestModelBase();

protected slots:

    virtual void initTestCase() = 0;
};