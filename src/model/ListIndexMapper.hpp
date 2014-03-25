/*
 * ListIndexMapper.h
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#ifndef LISTINDEXMAPPER_H_
#define LISTINDEXMAPPER_H_

#include <bb/cascades/DataModel>

class ListIndexMapper: public bb::cascades::DataModel::IndexMapper {
public:
	ListIndexMapper(int index, int count, bool deleted);
	bool newIndexPath(QVariantList *pNewIndexPath, int *pReplacementIndex,
			const QVariantList &oldIndexPath) const;
private:
	int m_index;
	int m_count;
	bool m_deleted;
};

#endif /* LISTINDEXMAPPER_H_ */
