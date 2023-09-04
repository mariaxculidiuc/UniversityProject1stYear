#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <QFont>
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\Masina.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class TableModel :public QAbstractTableModel {
    Q_PROPERTY(int count READ count NOTIFY countChanged)
        Q_DISABLE_COPY(TableModel)
        Q_OBJECT
        std::vector<Masina> m;
public:
    TableModel(const std::vector<Masina>& m) :m{m} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return m.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::FontRole) {
            QFont f;
            f.setItalic(index.row() % 10 == 0);
            f.setBold(index.row() % 10 == 3);
            return f;
        }
        if (role == Qt::BackgroundRole) {

            int row = index.row();
            QModelIndex i = index.sibling(index.row(), 1);
            if (i.data().toString() == "Fiat") {
                QBrush bg(Qt::red);
                return bg;
            }
        }

        if (role == Qt::DisplayRole) {

            Masina masina = m[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(masina.getNrInmatriculare());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(masina.getProducator());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(masina.getModel());
            }
            else if (index.column() == 3) {
                return QString::fromStdString(masina.getTip());
            }
        }

        return QVariant{};
    }

    int count() const {
        return m.size();
    }

    void setAct(const vector<Masina> m) {
        this->m = m;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged();
    }

    Qt::ItemFlags flags(const QModelIndex&) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return tr("Nr de inmatriculare");
                case 1:
                    return tr("Producator");
                case 2:
                    return tr("Model");
                case 3:
                    return tr("Tip");
                default:
                    return QString("");
                }
            }
        }
        return QVariant();
    }
signals:
    void countChanged();
};