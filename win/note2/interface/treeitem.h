#ifndef TREEITEM_H
#define TREEITEM_H

#include <QTreeWidget>
#include <QDateTime>

class TreeItem {
public:
    TreeItem(QTreeWidget *treeWidget);
    virtual ~TreeItem();
    void clear();

    int fillTreeByDateList(QList<QDate *> *dateList);
    int installSignalsForExistedTree(void (*handler)(QTreeWidgetItem *item));
    void getDaysList(QList<QTreeWidgetItem *> *items);
    int sortChildrenOfItem(QTreeWidgetItem *item);

private:
    QTreeWidget *treeWidget = nullptr;
    QList<QTreeWidgetItem *> yearItems;

    int appendNewDate(QString year, QString month, QString day);
    int appendOnceElement(QTreeWidgetItem *item, QString text);

    // get id of finded element, -1 if not exist
    int isExistElementInList(QList<QTreeWidgetItem *> *items, QString keyword);
    int isExistChildInElement(QTreeWidgetItem *item, QString keyword);
};

#endif // TREEITEM_H
