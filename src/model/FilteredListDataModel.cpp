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
	qDebug() << "FilteredListDataModel::setFilter:" << filter;
	if (m_filtered) {
		if (filter.size() > m_lastFilter.size()) {
			int size = this->size();
			for (int i = size - 1; i >= 0; --i) {
				if (!this->at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					m_filteredList.append(this->at(i).toMap());
					this->removeAt(i);
				}
			}
		} else {
			int size = m_filteredList.size();
			for (int i = size - 1; i >= 0; --i) {
				if (m_filteredList.at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					if (this->size() == 0)
						this->append(m_filteredList.at(i));
					else {
						int j, length = this->size();
						if (m_filteredList.at(i).toMap()["id"].toInt()
								> this->at(length / 2).toMap()["id"].toInt())
							j = searchMajorIndex(i, length);
						else
							j = searchMinorIndex(i, length);
						this->insert(j, m_filteredList.at(i).toMap());
					}
					m_filteredList.removeAt(i);
				}
			}
		}
		if (filter == "")
			m_filtered = false;
	} else {
		if (filter != "") {
			m_filtered = true;
			m_filteredList.clear();
			m_filteredList.append(this->allList());
			int size = this->size();
			for (int i = size - 1; i >= 0; --i) {
				if (!this->at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive))
					this->removeAt(i);
				else
					m_filteredList.removeAt(i);
			}
		}
	}
	qDebug() << "FilteredListDataModel::setFilter:List:" << this->allList();
	qDebug() << "FilteredListDataModel::setFilter:FilteredList:" << m_filteredList;
	qDebug() << "FilteredListDataModel::setFilter:List: =========================";
	m_lastFilter = filter;
}


int FilteredListDataModel::searchMinorIndex(int i, int length) {
	int index = length / 2;
	for (int j = length / 2; j >= 0; --j) {
		if (m_filteredList.at(i).toMap()["id"].toInt()
				< this->at(j).toMap()["id"].toInt())
			index = j;
	}
	return index;
}

int FilteredListDataModel::searchMajorIndex(int i, int length) {
	int index = length / 2;
	for (int j = length / 2; j < length; ++j) {
		if (m_filteredList.at(i).toMap()["id"].toInt()
				> this->at(j).toMap()["id"].toInt())
			index = j + 1;
	}
	return index;
}

} /* namespace model */
