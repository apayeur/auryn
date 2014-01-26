/* 
* Copyright 2014 Friedemann Zenke
*
* This file is part of Auryn, a simulation package for plastic
* spiking neural networks.
* 
* Auryn is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Auryn is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Auryn.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LINEARTRACE_H_
#define LINEARTRACE_H_

#include "auryn_definitions.h"
#include "System.h"

using namespace std;

class LinearTrace
{
private:
	NeuronID size;
	AurynFloat * state;
	AurynFloat * explut;
	AurynFloat tau;
	AurynTime tau_auryntime;
	AurynTime zerointerval;
	AurynTime zerotime_auryntime;
	AurynTime * timestamp;
	AurynTime * clock;
	void init(NeuronID n, AurynFloat timeconstant);
	void free();

public:
	LinearTrace(NeuronID n, AurynFloat timeconstant);
	virtual ~LinearTrace();
	void set(NeuronID i , AurynFloat value);
	void setall( AurynFloat value);
	void add(NeuronID i , AurynFloat value);
	void inc(NeuronID i);
	void update(NeuronID i);
	void evolve();
	AurynFloat get_tau();
	AurynFloat get(NeuronID i);
	AurynFloat * get_state_ptr();
};



extern System * sys;

#endif /*LINEARTRACE_H_*/

