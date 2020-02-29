#ifndef MAINTABLEVIEW_H
#define MAINTABLEVIEW_H

#include "TasksSortFilterProxyModel.h"
#include <qtableview.h>

class MainTableView : public QTableView {
    Q_OBJECT
public:
    explicit MainTableView(QWidget* parent = nullptr);
    void setup();
    void updateView(TasksSortFilterProxyModel* model);
};

#endif // MAINTABLEVIEW_H
