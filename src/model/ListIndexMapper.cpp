/*
 * ListIndexMapper.cpp
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#include "ListIndexMapper.hpp"

using namespace bb::cascades;

ListIndexMapper::ListIndexMapper(int index, int count, bool deleted) :
		m_index(index), m_count(count), m_deleted(deleted) {
}

bool ListIndexMapper::newIndexPath(QVariantList *pNewIndexPath,
		int *pReplacementIndex, const QVariantList &oldIndexPath) const {

	// Unaffected indices
	if (oldIndexPath[0].toInt() < m_index) {
		(*pNewIndexPath).append(oldIndexPath);
		return true;

	// Deleted indices
	} else if (m_deleted && oldIndexPath[0].toInt() <= m_index + m_count) {
		*pReplacementIndex = m_index;
		return false;

	// Indices after a deletion or addition
	} else {
		if (m_deleted)
			(*pNewIndexPath).append(oldIndexPath[0].toInt() - m_count);
		else
			(*pNewIndexPath).append(oldIndexPath[0].toInt() + m_count);
		return true;
	}
}

