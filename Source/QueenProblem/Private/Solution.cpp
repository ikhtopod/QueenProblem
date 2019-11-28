// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>


#include "Solution.h"

Solution& Solution::operator=(const Solution& solution) {
	if (this != &solution) {
		for (int32 i = 0; i < this->positions.Num(); ++i) {
			this->positions[i] = solution.positions[i];
		}//rof

		this->energy = solution.energy;
	}//fi

	return *this;
}
