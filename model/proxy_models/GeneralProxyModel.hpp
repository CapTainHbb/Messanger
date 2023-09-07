#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QString>
#include <iostream>

#include <GeneralModel.hpp>
#include <Contact.hpp>


class GeneralProxyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    GeneralProxyModel(GeneralModel *_source_model,  QObject *parent = nullptr ):
    source_model{ _source_model }, QAbstractListModel(parent)
    {
    }
    ~GeneralProxyModel() = default;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    virtual void add_index_mapping(const QModelIndex& source_index) {};

public slots:
    virtual void source_data_changed(const QModelIndex &topLeft, 
        const QModelIndex &bottomRight, 
        const QVector<int> &roles = QVector<int>()) { };

public:
    struct LocalModelIndex
    {
        int row {};
        int column{ };

        int get_row() const 
        { return row; }

        int get_column() const
        { return column;}
    };

    struct IndexMap
    {
        LocalModelIndex source_index;
        LocalModelIndex proxy_index;
    };

    GeneralModel *source_model{ nullptr };
    std::vector<IndexMap> index_mapping;

};

