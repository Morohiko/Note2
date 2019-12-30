#include "treeitem.h"

#include "config.h"

#include <QDebug>

int TreeItem::isExistElementInList(QList<QTreeWidgetItem *> *items, QString keyword) {
    for (int i = 0; i < items->size(); i++) {
        if (items->at(i)->text(DEFAULT_COLUMN) == keyword) {
            return i;
        }
    }
    qDebug() << "WARNING: isExistElement not found";
    return -1;
}

int TreeItem::isExistChildInElement(QTreeWidgetItem *item, QString keyword) {
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->text(DEFAULT_COLUMN) == keyword) {
            return i;
        }
    }
    return -1;
}

int TreeItem::sortChildrenOfItem(QTreeWidgetItem *item) {
    for (int i = 0; i < item->childCount(); i++) {
        for (int n = i; n >= 0; n--) {
            if (item->child(i)->text(DEFAULT_COLUMN).toInt() < item->child(n)->text(DEFAULT_COLUMN).toInt()) {
                QTreeWidgetItem buff;
                buff = *item->child(i);
                *item->child(i) = *item->child(n);
                *item->child(n) = buff;
                i = n;
            }
        }
    }

    return 0;
}

int TreeItem::appendOnceElement(QTreeWidgetItem *item, QString text) {
    int retval = isExistChildInElement(item, text);
    if (retval == -1) {
        retval = item->childCount();
        QTreeWidgetItem *buffItem = new QTreeWidgetItem(QStringList(text));
        buffItem->setText(DEFAULT_COLUMN, text);
        item->insertChild(retval, buffItem);
    }
    return retval;
}

int TreeItem::appendNewDate(QString year, QString month, QString day) {
    QTreeWidgetItem *buffItem = nullptr;

    int retval = -1;
    retval = isExistElementInList(&yearItems, year);

    if (retval == -1) {
        QTreeWidgetItem *yearItem = new QTreeWidgetItem(QStringList(year));
        yearItem->setText(DEFAULT_COLUMN, year);
        retval = yearItems.size();
        yearItems.append(yearItem);
    }

    buffItem = dynamic_cast<QTreeWidgetItem *> (yearItems.at(retval));

    retval = appendOnceElement(buffItem, month);

    buffItem = buffItem->child(retval);

    retval = appendOnceElement(buffItem, day);

    return 0;
}

int TreeItem::fillTreeByDateList(QList<QDate *> *dateList) {
    Q_ASSERT(dateList->size() >= 1);

    QListIterator<QDate *> iterator(*dateList);

    int year; int month; int day;

    do {
        iterator.next()->getDate(&year, &month, &day);
        qDebug() << "DEBUG: fillTreeByDateTimeList year:" << year << ", month: " << month << ", day: " << day;

        appendNewDate(QString::number(year), QString::number(month), QString::number(day));

    } while(iterator.hasNext());

    treeWidget->insertTopLevelItems(0, yearItems);
    return 0;
}

void TreeItem::getDaysList(QList<QTreeWidgetItem *> *items) {
    QTreeWidgetItem *buffItem;
    for (int i = 0; i < yearItems.size(); i++) {
        if (yearItems.at(i) == nullptr) continue;
        for (int k = 0; k < yearItems.at(i)->childCount(); k++) {
            if (yearItems.at(i)->child(k) == nullptr) continue;
            buffItem = yearItems.at(i)->child(k);
            for (int n = 0; n < buffItem->childCount(); n++) {
                if (buffItem->child(n) == nullptr) continue;
                items->append(buffItem->child(n));
            }
        }
    }
}

int TreeItem::installSignalsForExistedTree(void (*handler)(QTreeWidgetItem *item)) {
    QTreeWidgetItem *monthItems = nullptr;

    for (int i = 0; i < yearItems.size(); i++) {
        monthItems = dynamic_cast<QTreeWidgetItem *> (yearItems.at(i));
        if (monthItems == nullptr) continue;
        for (int k = 0; k < monthItems->childCount(); k++) {
            handler(monthItems->child(k));
        }
    }
    return 0;
}

void TreeItem::clear() {
    QListIterator<QTreeWidgetItem *> iteratorYears(yearItems);

    for (int i = 0; i < yearItems.length(); i++) {
        QTreeWidgetItem *month = iteratorYears.next()->child(i);
        for (int n = 0; n < month->childCount(); n++) {
            month->removeChild(month->child(n));
        }
    }

    yearItems.clear();
}

TreeItem::~TreeItem(){
    this->clear();
}

TreeItem::TreeItem(QTreeWidget *treeWidget) {
    this->treeWidget = treeWidget;
    this->treeWidget->setColumnCount(DEFAULT_COLUMN);
}
