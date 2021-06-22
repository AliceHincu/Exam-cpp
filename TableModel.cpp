//
// Created by Sakura on 6/22/2021.
//

#include "TableModel.h"
#include <qbrush.h>
#include <qfont.h>

int TableModel::rowCount(const QModelIndex& parent) const
{
    return this->serv.getElems().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    // get the events
    std::vector<Building>& list = this->serv.getElems();
    std::sort(
            list.begin(),
            list.end(),
            [this](auto const &b1, auto const &b2) {
                return b1.getThematicArea() == this->ethnologistThematicArea;
            }
    );

    // Allow adding in the table
    // this is to show an empty row at the end of the table - to allow adding new events
    if (row == list.size())
    {
        return QVariant();
    }

    // get the event from the current row
    Building e = list[row];
    std::string aux;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
            case 0:
                return QString::number(e.getIdentifier());
            case 1:
                return QString::fromStdString(e.getThematicArea());
            case 2:
                return QString::fromStdString(e.getDescription());
            case 3:
                return QString::fromStdString(e.getLocationString());
            default:
                break;
        }
    }

    if (role == Qt::BackgroundRole) {
        if (e.getThematicArea() == this->ethnologistThematicArea) {
            return QBrush(Qt::blue);
        }
    }
    /*
    if (role == Qt::FontRole) {
        if (e.getStatus() != "revised") {
            QFont font;
            font.setBold(true);
            return font;
        }
    }*/
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return QString{ "Id" };
                case 1:
                    return QString{ "Description" };
                case 2:
                    return QString{ "Thematic Sector" };
                case 3:
                    return QString{ "Location" };
                default:
                    break;
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}