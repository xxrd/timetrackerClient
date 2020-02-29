#include "TasksModel.h"

QHash<int, QByteArray> TasksModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles.insert(TitleRole, "title");
    roles.insert(Qt::DisplayRole, "title");
    roles.insert(Qt::EditRole, "title");
    roles.insert(ExecutorRole, "executor");
    roles.insert(StartDateRole, "startDate");
    roles.insert(EndDateRole, "endDate");
    roles.insert(TimerTimeRole, "timerTime");
    roles.insert(TimerStatusRole, "timerStatus");
    roles.insert(StatusRole, "status");
    roles.insert(IdRole, "id");
    return roles;
}

QVariant TasksModel::data(const QModelIndex &index, int nRole) const
{
    if (nRole != Qt::DisplayRole && nRole != Qt::EditRole) return {};

    switch(index.column()) {
        case 0:
            return QVariant();
            break;
        case 1:
            if(tasksVector[index.row()].status == Task::TaskStatus::active) return "active";
            else if(tasksVector[index.row()].status == Task::TaskStatus::complete) return "complete";
            return QVariant();
            break;
        case 2:
            return tasksVector[index.row()].title;
            break;
        case 3:
            return tasksVector[index.row()].executor;
            break;
        case 4:
            return tasksVector[index.row()].startDate;
            break;
        case 5:
            return tasksVector[index.row()].endDate;
            break;
        case 6:
            return QVariant::fromValue<TimeDelta>( tasksVector[index.row()].timerTime ); // tasksVector[index.row()].timerTime;
            break;
        case 7:
            return QVariant();
            break;
        case 8:
            return tasksVector[index.row()].timerStatus;
            break;
        case 9:
            return tasksVector[index.row()].id;
            break;

    }
    return QVariant();
}

bool TasksModel::setData(const QModelIndex& index, const QVariant& value, int nRole) {

    if (nRole != Qt::DisplayRole && nRole != Qt::EditRole) return {};

    switch(index.column()) {
        case 1:
            tasksVector[index.row()].status = static_cast<Task::TaskStatus>(value.toInt());
            emit dataChanged(index, index);
            return true;
            break;
        case 2:
            tasksVector[index.row()].title = value.toString();
            emit dataChanged(index, index);
            return true;
            break;
        case 3:
            tasksVector[index.row()].executor = value.toString();
            emit dataChanged(index, index);
            return true;
            break;
        case 4:
            tasksVector[index.row()].startDate = value.toDateTime();
            emit dataChanged(index, index);
            return true;
            break;
        case 5:
            tasksVector[index.row()].endDate = value.toDateTime();
            emit dataChanged(index, index);
            return true;
            break;
        case 6:
            tasksVector[index.row()].timerTime = qvariant_cast<TimeDelta>(value); // xz
            emit dataChanged(index, index);
            return true;
            break;
        case 8:
            tasksVector[index.row()].timerStatus = static_cast<Task::TaskTimerStatus>(value.toDouble());
            emit dataChanged(index, index);
            return true;
            break;
        case 9:
            tasksVector[index.row()].id = value.toString();
            emit dataChanged(index, index);
            return true;
            break;
    }
    return false;
}

int TasksModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        return 0;
    }
    return tasksVector.size();
}

int TasksModel::columnCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        return 0;
    }
    return Task::columnCount();
}

QVariant TasksModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const {
    if(nRole == Qt::DisplayRole) {
        if(orientation != Qt::Horizontal) return QVariant();

        switch(nSection) {
            case 0:
                return QString("...");
                break;
            case 1:
                return QString("status");
                break;
            case 2:
                return QString("title");
                break;
            case 3:
                return QString("executor");
                break;
            case 4:
                return QString("start date");
                break;
            case 5:
                return QString("end date");
                break;
            case 6:
                return QString("timer time");
                break;
            case 7:
                return QString("");
                break;
            case 8:
                return QString("timer status");
                break;
            case 9:
                return QString("id");
                break;
        }
    }

    return QVariant();
}

Qt::ItemFlags TasksModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(!index.isValid()) return flags;
    if(index.column() == 1 || index.column() == 4 || index.column() == 5 || index.column() == 6) return flags;
    return flags | Qt::ItemIsEditable;
}

bool TasksModel::insertRows(int nRow, int nCount, const QModelIndex& parent) {
    if(parent.isValid()) {
        return false;
    }
    beginInsertRows(QModelIndex(), nRow, nRow + nCount - 1);
    for(int i = 0; i < nCount; i++) {
       tasksVector.insert(nRow, Task());
    }
    endInsertRows();
    return true;
}

bool TasksModel::removeRows(int nRow, int nCount, const QModelIndex &parent) {
    if(parent.isValid()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), nRow, nRow + nCount - 1);
    for(int i = 0; i < nCount; i++) {
        tasksVector.removeAt(nRow);
    }
    endRemoveRows();
    return true;
}

void TasksModel::prepend(const Task & task) {
   beginInsertRows({}, tasksVector.count(), tasksVector.count());
   tasksVector.prepend(task);
   endInsertRows();
}
void TasksModel::append(const Task & task) {
   beginInsertRows({}, tasksVector.count(), tasksVector.count());
   tasksVector.append(task);
   endInsertRows();
}
