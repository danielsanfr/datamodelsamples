/*
 * SqlDataModel.cpp
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#include "SqlDataModel.hpp"

using namespace bb::cascades;

SqlDataModel::SqlDataModel() :
		m_filtered(false), m_filterBy(""), m_tableName(""), m_lastFilter("") {/*, m_sql(
				new DataBaseController(this)) {*/
//	emit sizeChanged(0);
}

SqlDataModel::~SqlDataModel() {
}

void SqlDataModel::reLoadData() {
	if (m_lastParameters.isEmpty())
		loadData();
	else
		loadData(m_lastParameters, m_lastConditions);
}

void SqlDataModel::loadData() {
//	loadData(QVariantList(), m_sql->readAll());
}

void SqlDataModel::loadData(QVariantList parameters, QString conditions) {
//	loadData(parameters, m_sql->readWere(parameters, conditions));
	m_lastParameters.clear();
	m_lastParameters.append(parameters);
	m_lastConditions.clear();
	m_lastConditions.append(conditions);
}

void SqlDataModel::loadData(QVariantList parameters, QVariantList resultList) {
	Q_UNUSED(parameters);
	if (!m_modelList.isEmpty()) {
		int size = m_modelList.size();
		m_modelList.clear();
//		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
//				QSharedPointer<SqlIndexMapper>(new SqlIndexMapper(0, size, true)));
	}
	int addIndex;

	addIndex = m_modelList.size();
	m_modelList.append(resultList);

//	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
//			QSharedPointer<SqlIndexMapper>(
//					new SqlIndexMapper(addIndex, resultList.size(), false)));
}

void SqlDataModel::create(QVariantMap data) {
//	int id = m_sql->create(data);
//	data[ID_FIELD] = id;
	int addIndex;

	addIndex = m_modelList.size();
	m_modelList.append(data);

//	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
//			QSharedPointer<SqlIndexMapper>(
//					new SqlIndexMapper(addIndex, 1, false)));
	emit sizeChanged(count());
}

void SqlDataModel::remove(const int id) {
	remove(getIndexPathByID(id));
}

void SqlDataModel::remove(const QVariantList &indexPath) {
//	m_sql->deleteRecord(data(indexPath).toMap()[CLIENT_ID].toInt());
	m_modelList.removeAt(indexPath.at(0).toInt());
//	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
//			QSharedPointer<SqlIndexMapper>(
//					new SqlIndexMapper(indexPath.at(0).toInt(), 1, true)));
	emit sizeChanged(count());
}

void SqlDataModel::update(QVariantMap data) {
	update(getIndexPathByID(data[ID_FIELD].toInt()), data);
}

void SqlDataModel::update(const QVariantList& indexPath, QVariantMap data) {
	m_modelList.replace(indexPath.at(0).toInt(), data);
//	m_sql->update(data);
	emit itemUpdated(indexPath);
}

int SqlDataModel::childCount(const QVariantList &indexPath) {
	if (indexPath.isEmpty())
		return m_modelList.size();
	else
		return 0;
}

bool SqlDataModel::hasChildren(const QVariantList &indexPath) {
	if (indexPath.isEmpty())
		return !m_modelList.isEmpty();
	else
		return false;
}

QVariant SqlDataModel::data(const QVariantList &indexPath) {
	return m_modelList.at(indexPath.back().toInt());
}

void SqlDataModel::setTableName(QString tableName) {
	m_tableName = tableName;
//	m_sql->setTableName(tableName);
}

QString SqlDataModel::tableName() {
	return m_tableName;
}

QVariantList SqlDataModel::getList() const {
	return m_modelList;
}

int SqlDataModel::count() const {
	return m_modelList.count();
}

int SqlDataModel::size(QVariantList parameters, QString conditions) {
//	return m_sql->size(parameters, conditions);
}

QVariantList SqlDataModel::getIndexPathByID(int id) {
	QVariantList defaultIndexPath;
	defaultIndexPath.append(-1);
	for (int i = 0; i < m_modelList.size(); ++i) {
		if (m_modelList.at(i).toMap()[ID_FIELD].toInt() == id) {
			QVariantList indexPath;
			indexPath.append(i);
			return indexPath;
		}
	}
	return defaultIndexPath;
}

void SqlDataModel::setTextFilter(QString filter) {
	if (m_filtered) {
		if (filter.size() > m_lastFilter.size()) {
			int size = m_modelList.size();
			for (int i = size - 1; i >= 0; --i) {
				if (!m_modelList.at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					m_modelListAux.append(m_modelList.at(i).toMap());
					m_modelList.removeAt(i);
//					emit itemsChanged(
//							bb::cascades::DataModelChangeType::AddRemove,
//							QSharedPointer<SqlIndexMapper>(
//									new SqlIndexMapper(i, 1, true)));
				}
			}
		} else {
			int size = m_modelListAux.size();
			for (int i = size - 1; i >= 0; --i) {
				if (m_modelListAux.at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					if (m_modelList.size() == 0) {
						m_modelList.append(m_modelListAux.at(i));
//						emit itemsChanged(
//								bb::cascades::DataModelChangeType::AddRemove,
//								QSharedPointer<SqlIndexMapper>(
//										new SqlIndexMapper(0, 1, false)));
					} else {
						int j, length = m_modelList.size();
						if (m_modelListAux.at(i).toMap()["id"].toInt()
								> m_modelList.at(length / 2).toMap()["id"].toInt())
							j = searchMajorIndex(i, length);
						else
							j = searchMinorIndex(i, length);
						m_modelList.insert(j, m_modelListAux.at(i).toMap());
//						emit itemsChanged(
//								bb::cascades::DataModelChangeType::AddRemove,
//								QSharedPointer<SqlIndexMapper>(
//										new SqlIndexMapper(j, 1, false)));
					}
					m_modelListAux.removeAt(i);
				}
			}
		}
		if (filter == "")
			m_filtered = false;
	} else {
		if (filter != "") {
			m_filtered = true;
			m_modelListAux.clear();
			m_modelListAux.append(m_modelList);
			int size = m_modelList.size();
			for (int i = size - 1; i >= 0; --i) {
				if (!m_modelList.at(i).toMap()[m_filterBy].toString().startsWith(
						filter, Qt::CaseInsensitive)) {
					m_modelList.removeAt(i);
//					emit itemsChanged(
//							bb::cascades::DataModelChangeType::AddRemove,
//							QSharedPointer<SqlIndexMapper>(
//									new SqlIndexMapper(i, 1, true)));
				} else {
					m_modelListAux.removeAt(i);
				}
			}
		}
	}
	m_lastFilter = filter;
}

int SqlDataModel::searchMinorIndex(int i, int length) {
	int index = length / 2;
	for (int j = length / 2; j >= 0; --j) {
		if (m_modelListAux.at(i).toMap()["id"].toInt()
				< m_modelList.at(j).toMap()["id"].toInt())
			index = j;
	}
	return index;
}

int SqlDataModel::searchMajorIndex(int i, int length) {
	int index = length / 2;
	for (int j = length / 2; j < length; ++j) {
		if (m_modelListAux.at(i).toMap()["id"].toInt()
				> m_modelList.at(j).toMap()["id"].toInt())
			index = j + 1;
	}
	return index;
}

void SqlDataModel::setFilterBy(QString filterBy) {
	m_filterBy = filterBy;
}

QString SqlDataModel::filterBy() {
	return m_filterBy;
}
