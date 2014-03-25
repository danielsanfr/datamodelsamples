/*
 * FilteredListDataModel.hpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#ifndef FILTEREDLISTDATAMODEL_HPP_
#define FILTEREDLISTDATAMODEL_HPP_

#include <QDebug>
#include <QObject>
#include <QString>
#include "DynamicListDataModel.hpp"

namespace model {

class FilteredListDataModel : public DynamicListDataModel {
	Q_OBJECT
	Q_PROPERTY(QString filterBy READ filterBy WRITE setFilterBy NOTIFY filterByChanged FINAL)
public:
	FilteredListDataModel(QObject *parent = 0);
	virtual ~FilteredListDataModel();
	static void registerQmlTypes() {
		qmlRegisterType<FilteredListDataModel>("model.custom", 1, 0, "FilteredListDataModel");
	}
	Q_INVOKABLE void clearFilter();
	Q_INVOKABLE void setFilter(QString filter);
	Q_INVOKABLE void setFilterBy(QString filterBy);
	Q_INVOKABLE QString filterBy();
Q_SIGNALS:
	void filterByChanged();
private:
	int searchMinorIndex(int i, int length);
	int searchMajorIndex(int i, int length);
	QString m_filterBy;
	QString m_lastFilter;
	bool m_filtered;
	QVariantList m_filteredList;
};

} /* namespace model */
#endif /* FILTEREDLISTDATAMODEL_HPP_ */
