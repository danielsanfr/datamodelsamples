/*
 * DynamicListDataModel.hpp
 *
 *  Created on: 23/03/2014
 *      Author: daniel
 */

#ifndef DYNAMICLISTDATAMODEL_HPP_
#define DYNAMICLISTDATAMODEL_HPP_

#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QSharedPointer>

#include <bb/cascades/DataModel>

#include "ListIndexMapper.hpp"

namespace model {

class DynamicListDataModel: public bb::cascades::DataModel {
Q_OBJECT
public:
	DynamicListDataModel(QObject *parent = 0);
	~DynamicListDataModel();
	static void registerQmlTypes() {
		qmlRegisterType<DynamicListDataModel>("model.custom", 1, 0, "DynamicListDataModel");
	}
	// Implementing the DataModel interface
	Q_INVOKABLE int childCount(const QVariantList &indexPath);
	Q_INVOKABLE bool hasChildren(const QVariantList &indexPath);
	Q_INVOKABLE QVariant data(const QVariantList &indexPath);
	// Implementing dynamic list
	Q_INVOKABLE void append(const QVariant &value);
	Q_INVOKABLE void appendList(const QVariantList &value);
	Q_INVOKABLE const QVariant &at(int i) const;
	Q_INVOKABLE void clear();
	Q_INVOKABLE int count(const QVariant &value) const;
	Q_INVOKABLE int count() const;
	Q_INVOKABLE int indexOf(const QVariant &value, int from = 0) const;
	Q_INVOKABLE void insert(int i, const QVariant &value);
	Q_INVOKABLE bool isEmpty () const;
	Q_INVOKABLE int length () const;
	Q_INVOKABLE void prepend(const QVariant &value);
	Q_INVOKABLE void removeAll(); // Not a standard list
	Q_INVOKABLE int removeAll(const QVariant &value);
	Q_INVOKABLE void removeAt(int i);
	Q_INVOKABLE void removeFirst();
	Q_INVOKABLE void removeLast ();
	Q_INVOKABLE void replace(int i, const QVariant &value);
	Q_INVOKABLE int size () const;
	Q_INVOKABLE void swap(QVariantList &other);
	Q_INVOKABLE void swap(int i, int j);
	Q_INVOKABLE QVariantList allList() const;
	Q_INVOKABLE QVariant takeAt(int i);
	Q_INVOKABLE QVariant takeFirst();
	Q_INVOKABLE QVariant takeLast();
	Q_INVOKABLE QVariant value(int i) const;
	Q_INVOKABLE QVariant value(int i, const QVariant &defaultValue) const;
	Q_INVOKABLE QVariant &operator[](int i);
	Q_INVOKABLE const QVariant &operator[](int i) const;
Q_SIGNALS:
	void sizeChanged();
private:
	QVariantList m_list;
};

} /* namespace model */
#endif /* DYNAMICLISTDATAMODEL_HPP_ */
