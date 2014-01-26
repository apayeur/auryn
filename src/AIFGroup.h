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

#ifndef AIFGROUP_H_
#define AIFGROUP_H_

#include "auryn_definitions.h"
#include "NeuronGroup.h"
#include "System.h"
#include <gsl/gsl_blas.h>

/*! \brief A simple extension of IFGroup with spike triggered adaptation */
class AIFGroup : public NeuronGroup
{
private:
	void free();

protected:
	gsl_vector_float * dmem;
	gsl_vector_float * t_leak;
	gsl_vector_float * t_exc;
	gsl_vector_float * t_inh;
	gsl_vector_float * g_adapt1;

	AurynFloat scale_ampa,scale_gaba, scale_thr;
	AurynFloat scale_adapt1;
	AurynFloat tau_adapt1;


	AurynFloat e_rest,e_rev,thr_rest,tau_mem,tau_thr,dthr;
	AurynFloat tau_ampa,tau_gaba,tau_nmda;
	AurynFloat A_ampa,A_nmda;

	void init();
	void vector_scale( float mul, gsl_vector_float * v );
	void integrate_linear_nmda_synapses();
	void integrate_membrane();
	void check_thresholds();
	string get_output_line(NeuronID i);
	void load_input_line(NeuronID i, const char * buf);
public:
	AurynFloat dg_adapt1;

	AIFGroup( NeuronID size, AurynFloat load = 1.0, NeuronID total = 0 );
	virtual ~AIFGroup();
	void set_tau_mem(AurynFloat taum);
	AurynFloat get_tau_mem();
	void set_tau_ampa(AurynFloat tau);
	void set_tau_gaba(AurynFloat tau);
	void set_tau_nmda(AurynFloat tau);
	void set_tau_adapt(AurynFloat tau);
	AurynFloat get_tau_ampa();
	AurynFloat get_tau_gaba();
	AurynFloat get_tau_nmda();
	AurynFloat get_tau_adapt();
	void random_adapt(AurynState mean, AurynState sigma);
	void set_ampa_nmda_ratio(AurynFloat ratio);
	void calculate_scale_constants();


	void clear();
	void evolve();
};

#endif /*AIFGROUP_H_*/

