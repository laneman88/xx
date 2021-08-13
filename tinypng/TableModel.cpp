﻿#include "TableModel.h"
#include <QLabel>
#include <QWidget>
#include <QDebug>

TableModel::TableModel(QObject* parent)
	: QAbstractTableModel(parent),
	_data(nullptr)
{
	this->mutex = new QMutex();
	this->_data = new QList<TableModelRow>();
	connect(this, SIGNAL(addRowSignal(TableModelRow)), this, SLOT(addRowx(TableModelRow)));
}

int TableModel::rowCount(const QModelIndex& parent) const {
	int num = this->_data->count();
	return num;
}


int TableModel::columnCount(const QModelIndex& parent) const {
	return 4;
}


QVariant TableModel::data(const QModelIndex& index, int role = Qt::DisplayRole) const {
	if (role != Qt::DisplayRole) {
		if (index.column() == 3) {
			TableModelRow item = this->_data->at(index.row());
			if (role == Qt::ForegroundRole && item.status == 2) {
				QBrush brush(QColor(23, 168, 26, 255));
				return QVariant(brush);
			}
		}

		return QVariant();
	}
	QString label = this->headerData(index.column(), Qt::Orientation::Horizontal, Qt::DisplayRole).toString();
	TableModelRow item = this->_data->at(index.row());
	if (label == "路径") {
		return QVariant(item.path);
	}
	else if (label == "大小") {
		QString size = QLocale(QLocale::English, QLocale::UnitedStates).formattedDataSize(item.size, 2, QLocale::DataSizeTraditionalFormat);
		return QVariant(size);
	}
	else if (label == "状态") {
		QString status;
		switch (item.status)
		{
		case -1:
			status = "失 败";
			break;
		case 0:
			status = "待压缩";
			break;
		case 1:
			status = "压缩中";
			break;
		case 2:
			status = "成功";
			break;
		default:
			break;
		}
		return QVariant(status);
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {

	if (role != Qt::DisplayRole) {
		return QVariant();
	}
	if (orientation != Qt::Orientation::Horizontal) {
		return QAbstractTableModel::headerData(section, orientation, role);
	}
	QString text;
	switch (section)
	{
	case 1:
		text = "路径";
		break;
	case 2:
		text = "大小";
		break;
	case 3:
		text = "状态";
		break;
	default:
		return QVariant();
		break;
	}
	return QVariant(text);

}



void TableModel::addRow(QList<TableModelRow> items) {
	this->mutex->lock();
	int count = this->rowCount();
	this->beginInsertRows(QModelIndex(), count, count + items.length() - 1);
	this->_data->append(items);
	this->endInsertRows();
	this->mutex->unlock();
}
void TableModel::addRow(TableModelRow item) {

	QList<TableModelRow> list;
	list << item;
	this->addRow(list);

}

void TableModel::removeAll() {
	if (this->_data->length() == 0) {
		return;
	}
	this->mutex->lock();
	this->beginRemoveRows(QModelIndex(), 0, this->_data->count() - 1);
	this->_data->clear();
	this->endRemoveRows();
	this->mutex->unlock();
}


void TableModel::removeRow(int row, const QModelIndex& index) {

	if (row < 0 || (row + 1) > this->_data->length()) {
		return;
	}
	this->mutex->lock();
	this->beginRemoveRows(index, row, row);
	this->_data->removeAt(row);
	this->endRemoveRows();
	this->mutex->unlock();
}

void TableModel::removeRange(int first, int last, const QModelIndex& index) {

	if (first < 0 || (last + 1) >= this->_data->length()) {
		return;
	}
	this->mutex->lock();
	this->beginRemoveRows(index, first, last);
	for (int i = first; i <= last; i++) {
		this->_data->removeAt(first);
	}
	this->endRemoveRows();
	this->mutex->unlock();
}




TableModelRow TableModel::getRow(int row) {

	return this->_data->at(row);
}

void TableModel::replaceRow(int row, TableModelRow item) {
	this->mutex->lock();
	this->_data->replace(row, item);
	this->mutex->unlock();
}

void TableModel::updateStatus(int row, int status) {
	TableModelRow rowData = this->_data->at(row);
	rowData.status = status;
	this->_data->replace(row, rowData);
}




TableModel::~TableModel()
{

}
