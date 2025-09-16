#ifndef RELAY_ITEM_MODEL_H
#define RELAY_ITEM_MODEL_H

#include <QtCore/QAbstractItemModel>
#include "relay_properties_enums.h"
#include <memory>


class project;
struct athlete_t;
class team_item;
#include "relay_calculator.h"

class relay_item_model : public QAbstractItemModel
{
    Q_OBJECT

public:
    relay_item_model (project &proj, QObject *parent = nullptr);

    QModelIndex index (int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent (const QModelIndex &child) const override;

    int rowCount (const QModelIndex &parent) const override;
    int columnCount (const QModelIndex &parent) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData (int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags (const QModelIndex &index) const override;

    void calculate (type_of_relay t_relay, gender_type_of_relay gt_relay);

private:
    team_item *item (int row, team_item *parent) const;
    team_item *parent (team_item *child) const;
    int row (const team_item *item) const;
private:
    project &m_project;
    int m_row_count = 1;
    std::unique_ptr<relay_calculator> m_calculator;
};

#endif // RELAY_ITEM_MODEL_H
