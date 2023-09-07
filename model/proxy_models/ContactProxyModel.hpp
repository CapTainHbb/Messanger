#pragma once

#include <GeneralProxyModel.hpp>
#include <Contact.hpp>
#include <iostream>

class ContactProxyModel : public GeneralProxyModel
{
    Q_OBJECT    
    
public:
    ContactProxyModel(GeneralModel *source_model, QObject *parent = nullptr);
    ~ContactProxyModel() = default;
};
