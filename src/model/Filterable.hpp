/*
 * Filterable.hpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#ifndef FILTERABLE_HPP_
#define FILTERABLE_HPP_

namespace model {

class Filterable {
public:
	Filterable() {
	}
	virtual ~Filterable() {
	}
	virtual void at(int i) = 0;
	virtual void removeAt(int i) = 0;
	virtual void append(const QVariant &value) = 0;
};

} /* namespace model */
#endif /* FILTERABLE_HPP_ */
