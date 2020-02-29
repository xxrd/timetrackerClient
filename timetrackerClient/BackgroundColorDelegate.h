#ifndef BACKGROUNDCOLORDELEGATE_H
#define BACKGROUNDCOLORDELEGATE_H

#include <qstyleditemdelegate.h>


class BackgroundColorDelegate : public QStyledItemDelegate {

public:
    BackgroundColorDelegate(QObject *parent = 0);

    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const;
};

#endif // BACKGROUNDCOLORDELEGATE_H
