/*
 * FilteredListDataModel.hpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#ifndef FILTEREDLISTDATAMODEL_HPP_
#define FILTEREDLISTDATAMODEL_HPP_

#include <QHash>
#include <QDebug>
#include <QObject>
#include <QString>
#include "DynamicListDataModel.hpp"

namespace model {

class FilteredListDataModel: public DynamicListDataModel {
Q_OBJECT
Q_PROPERTY(QString filterBy READ filterBy WRITE setFilterBy NOTIFY filterByChanged FINAL)
public:
	FilteredListDataModel(QObject *parent = 0);
	virtual ~FilteredListDataModel();
	static void registerQmlTypes() {
		qmlRegisterType<FilteredListDataModel>("model.custom", 1, 0,
				"FilteredListDataModel");
	}
	Q_INVOKABLE void clearFilter();
	Q_INVOKABLE void setFilter(QString filter);
	Q_INVOKABLE void setFilterBy(QString filterBy);
	Q_INVOKABLE QString filterBy();
	Q_SIGNAL void filterByChanged();
private:
	Q_SLOT void onItemAdded(QVariantList indexPath);
	Q_SLOT void onItemRemoved(QVariantList indexPath);
	Q_SLOT void onItemUpdated(QVariantList indexPath);
	Q_SLOT void onItemsChanged(bb::cascades::DataModelChangeType::Type eChangeType,
            QSharedPointer<bb::cascades::DataModel::IndexMapper> indexMapper);
	QString m_filterBy;
	QString m_lastFilter;
	bool m_filtered;
	QList<int> m_indexList;
	QList<int> m_filteredIndexList;
	QVariantList m_filteredList;
};

} /* namespace model */
#endif /* FILTEREDLISTDATAMODEL_HPP_ */
