/*
 * DynamicListDataModel.cpp
 *
 *  Created on: 23/03/2014
 *      Author: daniel
 */

#include "DynamicListDataModel.hpp"

namespace model {

DynamicListDataModel::DynamicListDataModel(QObject *parent) :
		DataModel(parent) {
}

DynamicListDataModel::~DynamicListDataModel(){
}

// Implementing the DataModel interface
int DynamicListDataModel::childCount(const QVariantList &indexPath) {
	if (indexPath.isEmpty())
		return m_list.count();
	else
		return 0;
}

bool DynamicListDataModel::hasChildren(const QVariantList &indexPath) {
	if (indexPath.isEmpty())
		return !m_list.isEmpty();
	else
		return false;
}

QVariant DynamicListDataModel::data(const QVariantList &indexPath) {
	return m_list.at(indexPath.back().toInt());
}

// Implementing dynamic list

void DynamicListDataModel::append(const QVariant &value) {
	m_list.append(value);
	emit itemAdded(QVariantList() << m_list.size() - 1);
	emit sizeChanged();
}

void DynamicListDataModel::appendList(const QVariantList &value) {
	int size = m_list.size();
	m_list.append(value);
	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
			QSharedPointer<ListIndexMapper>(
					new ListIndexMapper(size, value.size(), false)));
	emit sizeChanged();
}

const QVariant &DynamicListDataModel::at(int i) const {
	return m_list.at(i);
}

void DynamicListDataModel::clear() {
	int size = m_list.size();
	m_list.clear();
	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
			QSharedPointer<ListIndexMapper>(
					new ListIndexMapper(0, size, true)));
	emit sizeChanged();
}

int DynamicListDataModel::count(const QVariant &value) const {
	return m_list.count(value);
}

int DynamicListDataModel::count() const {
	return m_list.count();
}

int DynamicListDataModel::indexOf(const QVariant &value, int from) const {
	return m_list.indexOf(value, from);
}

void DynamicListDataModel::insert(int i, const QVariant &value) {
	m_list.insert(i, value);
	emit itemAdded(QVariantList() << i);
	emit sizeChanged();
}

bool DynamicListDataModel::isEmpty() const {
	return m_list.isEmpty();
}

int DynamicListDataModel::length() const {
	return m_list.length();
}

void DynamicListDataModel::prepend(const QVariant &value) {
	m_list.prepend(value);
	emit itemAdded(QVariantList() << 0);
	emit sizeChanged();
}

void DynamicListDataModel::removeAll() {
	m_list.clear();
	emit sizeChanged();
}

int DynamicListDataModel::removeAll(const QVariant &value) {
	int size = m_list.size();
	int removeds = m_list.removeAll(value);
	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
			QSharedPointer<ListIndexMapper>(
					new ListIndexMapper(size, size + removeds, true)));
	emit sizeChanged();
	return removeds;
}

void DynamicListDataModel::removeAt(int i) {
	m_list.removeAt(i);
	emit itemRemoved(QVariantList() << i);
	emit sizeChanged();
}

void DynamicListDataModel::removeFirst() {
	m_list.removeFirst();
	emit itemRemoved(QVariantList() << 0);
	emit sizeChanged();
}

void DynamicListDataModel::removeLast() {
	m_list.removeLast();
	emit itemRemoved(QVariantList() << m_list.size());
	emit sizeChanged();
}

void DynamicListDataModel::replace(int i, const QVariant &value) {
	m_list.replace(i, value);
	emit itemUpdated(QVariantList() << i);
}

int DynamicListDataModel::size() const {
	return m_list.size();
}

void DynamicListDataModel::swap(QVariantList &other) {
	int size = m_list.size();
	m_list.swap(other);
	emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove,
			QSharedPointer<ListIndexMapper>(
					new ListIndexMapper(0, size, true)));
	emit sizeChanged();
}

void DynamicListDataModel::swap(int i, int j) {
	m_list.swap(i, j);
	emit itemUpdated(QVariantList() << i);
	emit itemUpdated(QVariantList() << j);
}

QVariantList DynamicListDataModel::allList() const {
	return m_list;
}

QVariant DynamicListDataModel::takeAt(int i) {
	return m_list.takeAt(i);
}

QVariant DynamicListDataModel::takeFirst() {
	return m_list.takeFirst();
}

QVariant DynamicListDataModel::takeLast() {
	return m_list.takeLast();
}

QVariant DynamicListDataModel::value(int i) const {
	return m_list.value(i);
}

QVariant DynamicListDataModel::value(int i,
		const QVariant &defaultValue) const {
	return m_list.value(i, defaultValue);
}

QVariant &DynamicListDataModel::operator [](int i) {
	return m_list[i];
}

const QVariant &DynamicListDataModel::operator [](int i) const {
	return m_list[i];
}

} /* namespace model */
