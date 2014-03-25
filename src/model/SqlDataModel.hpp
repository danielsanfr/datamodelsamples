/*
 * SqlDataModel.hpp
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#ifndef SQLDATAMODEL_HPP_
#define SQLDATAMODEL_HPP_

#include <QString>
#include <QtSql/QtSql>
#include <QVariantMap>
#include <QVariantList>
#include <QSharedPointer>

#include <bb/cascades/DataModel>

//#include "SqlIndexMapper.hpp"
//#include "DataBaseController.hpp"

#define ID_FIELD "id"

class SqlDataModel: public bb::cascades::DataModel {
	Q_OBJECT
	Q_PROPERTY(QString filterBy READ filterBy WRITE setFilterBy NOTIFY onFilterByChanged FINAL)
public:
	SqlDataModel();
	virtual ~SqlDataModel();

	// Implementing the DataModel class
	Q_INVOKABLE int childCount(const QVariantList &indexPath);
	Q_INVOKABLE bool hasChildren(const QVariantList &indexPath);
	Q_INVOKABLE QVariant data(const QVariantList &indexPath);

	Q_INVOKABLE QVariantList getList() const;
	Q_INVOKABLE int count() const;

	Q_INVOKABLE void reLoadData();
	Q_INVOKABLE void loadData();
	Q_INVOKABLE void loadData(QVariantList parameters, QString conditions);
	Q_INVOKABLE void remove(const int id);
	Q_INVOKABLE void remove(const QVariantList &indexPath);
	Q_INVOKABLE void update(const QVariantList &indexPath, QVariantMap data);
	Q_INVOKABLE void update(QVariantMap data);
	Q_INVOKABLE void create(QVariantMap data);
	Q_INVOKABLE int size(QVariantList parameters, QString conditions);

	// A signal that's emitted when the initial set of data has been
	// loaded into the DataModel
	Q_SIGNAL void onFilterByChanged();
	Q_SIGNAL void initialItemsLoaded();
	Q_SIGNAL void onTableNameChanged();
	Q_SIGNAL void sizeChanged(int size);
	Q_INVOKABLE void setFilterBy(QString filterBy);
	Q_INVOKABLE QString filterBy();
	Q_INVOKABLE void setTableName(QString tableName);
	Q_INVOKABLE QString tableName();
	Q_INVOKABLE void setTextFilter(QString filter);
	static void registerQmlTypes() {
		qmlRegisterType<SqlDataModel>("model.custom", 1, 0, "SqlDataModel");
	}
protected:
	void loadData(QVariantList parameters, QVariantList resultList);
private:
	int searchMinorIndex(int i, int length);
	int searchMajorIndex(int i, int length);
	QVariantList getIndexPathByID(int id);
	bool m_filtered;
	QString m_filterBy;
	QString m_tableName;
	QString m_lastFilter;
//	DataBaseController *m_sql;
	QVariantList m_modelList;
	QVariantList m_modelListAux;
	QVariantList m_lastParameters;
	QString m_lastConditions;
};

#endif /* SQLDATAMODEL_HPP_ */
