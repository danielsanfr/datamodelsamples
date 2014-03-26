/*
 * FilteredListDataModel.cpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#include "FilteredListDataModel.hpp"

namespace model {

FilteredListDataModel::FilteredListDataModel(QObject *parent) :
		DynamicListDataModel(parent), m_filterBy("") {
	// TODO Auto-generated constructor stub
	m_filtered = false;
	bool ok = connect(this, SIGNAL(itemAdded(QVariantList)), this,
			SLOT(onItemAdded(QVariantList)));
	Q_ASSERT(ok);
	ok = connect(this, SIGNAL(itemRemoved(QVariantList)), this,
			SLOT(onItemRemoved(QVariantList)));
	Q_ASSERT(ok);
	ok = connect(this, SIGNAL(itemUpdated(QVariantList)), this,
			SLOT(onItemUpdated(QVariantList)));
	Q_ASSERT(ok);
	ok =
			connect(this,
					SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type, QSharedPointer<bb::cascades::DataModel::IndexMapper>)),
					this,
					SLOT(onItemsChanged(bb::cascades::DataModelChangeType::Type, QSharedPointer<bb::cascades::DataModel::IndexMapper>)));
	Q_ASSERT(ok);
}

FilteredListDataModel::~FilteredListDataModel() {
	// TODO Auto-generated destructor stub
}

void FilteredListDataModel::clearFilter() {
	setFilter("");
}

void FilteredListDataModel::setFilterBy(QString filterBy) {
	m_filterBy = filterBy;
}

QString FilteredListDataModel::filterBy() {
	return m_filterBy;
}

void FilteredListDataModel::setFilter(QString filter) {
	if (m_filtered) {
		if (filter.size() > m_lastFilter.size()) {
			int size = length();
			for (int i = size - 1; i >= 0; --i) {
				if (!at(i).toMap()[m_filterBy].toString().startsWith(filter,
						Qt::CaseInsensitive)) {
					m_filteredList.append(at(i));
					m_filteredIndexList.insert(i, i);
					removeAt(i);
				}
			}
		} else if (filter.size() < m_lastFilter.size()) {
			QHash<int, QVariant> indexs;
			int size = m_filteredList.size();
			for (int i = size - 1; i >= 0; --i) {
				if (m_filteredList.at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					indexs.insert(m_filteredIndexList.at(i),
							m_filteredList.at(i));
					m_filteredList.removeAt(i);
					m_filteredIndexList.removeAt(i);
				}
			}
			foreach (int key, indexs.keys())
				insert(key, indexs.value(key));
		}
	} else {
		if (filter != "") {
			m_filteredList.clear();
			m_filteredList.append(allList());
			m_filteredIndexList.clear();
			m_filteredIndexList.append(m_indexList);
			int size = this->size();
			for (int i = size - 1; i >= 0; --i) {
				if (!at(i).toMap()[m_filterBy].toString().startsWith(filter,
						Qt::CaseInsensitive))
					removeAt(i);
				else {
					m_filteredList.removeAt(i);
					m_filteredIndexList.removeAt(i);
				}
			}
		}
	}
	m_lastFilter = filter;
	m_filtered = (filter != "");
}

void FilteredListDataModel::onItemAdded(QVariantList indexPath) {
	int index = indexPath.back().toInt();
	m_indexList.insert(index, index);
}

void FilteredListDataModel::onItemRemoved(QVariantList indexPath) {
	m_indexList.removeAt(indexPath.back().toInt());
}

void FilteredListDataModel::onItemUpdated(QVariantList indexPath) {
	Q_UNUSED(indexPath);
	setFilter(m_lastFilter);
}

void FilteredListDataModel::onItemsChanged(
		bb::cascades::DataModelChangeType::Type eChangeType,
		QSharedPointer<bb::cascades::DataModel::IndexMapper> indexMapper) {
	Q_UNUSED(eChangeType);
	Q_UNUSED(indexMapper);
	int length = size();
	m_indexList.clear();
	for (int i = 0; i < length; ++i)
		m_indexList.append(i);
}

} /* namespace model */
