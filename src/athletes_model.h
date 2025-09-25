#ifndef ATHLETES_MODEL_H
#define ATHLETES_MODEL_H

#include <QtCore/QAbstractTableModel>

class project;
class athlete_t;

class athlete_wrapper
{
public:
  athlete_wrapper (std::pair<athlete_t, bool> &athlete);

  QVariant get_data_by_section (int section) const;
  void set_data_by_section (int section, QVariant data);
  QVariant checked ();
  void set_is_checked (QVariant state);
  static QString get_string_by_section (int section);

private:
  std::pair<athlete_t, bool> &m_athlete;
};

class athletes_model : public QAbstractTableModel
{
  Q_OBJECT
public:
  athletes_model (project &proj, QObject *parent = 0);
  virtual ~athletes_model();

  int rowCount (const QModelIndex &parent = QModelIndex()) const;
  int columnCount (const QModelIndex &parent = QModelIndex()) const;
  QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  void delete_row (const QModelIndex &index);

private:
  project &m_project;
  const int m_column_count = 7;
};

#include <QStyledItemDelegate>

class  combo_box_delegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    combo_box_delegate (QObject *parent = nullptr);

    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData (QWidget *editor, const QModelIndex &index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry (QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

};

class  spin_box_delegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    spin_box_delegate (QObject *parent = nullptr);

    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData (QWidget *editor, const QModelIndex &index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry (QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // ATHLETES_MODEL_H
