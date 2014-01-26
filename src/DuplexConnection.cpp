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

#include "DuplexConnection.h"

void DuplexConnection::init() 
{
	fwd = w; // for consistency declared here. fwd can be overwritten later though
	bkw = new BackwardMatrix ( get_n_cols(), get_m_rows(), w->get_nonzero() );
	compute_reverse_matrix();
}

void DuplexConnection::finalize() // finalize at this level is called only for reconnecting or non-Constructor building of the matrix
{
	stringstream oss;
	oss << "DuplexConnection: Finalizing ...";
	logger->msg(oss.str(),NOTIFICATION);

	bkw->clear();
	compute_reverse_matrix();
}


DuplexConnection::DuplexConnection(const char * filename) 
: SparseConnection(filename)
{
	if ( dst->get_post_size() > 0 ) 
		init();
}

DuplexConnection::DuplexConnection(SpikingGroup * source, NeuronGroup * destination, 
		TransmitterType transmitter) 
: SparseConnection(source, destination, transmitter)
{
}

DuplexConnection::DuplexConnection(SpikingGroup * source, NeuronGroup * destination, 
		const char * filename , 
		TransmitterType transmitter) 
: SparseConnection(source, destination, filename, transmitter)
{
	if ( dst->get_post_size() > 0 ) 
		init();
}


DuplexConnection::DuplexConnection(NeuronID rows, NeuronID cols) 
: SparseConnection(rows,cols)
{
	init();
}

DuplexConnection::DuplexConnection( SpikingGroup * source, NeuronGroup * destination, 
		AurynWeight weight, AurynFloat sparseness, 
		TransmitterType transmitter, string name) 
: SparseConnection(source,destination,weight,sparseness,transmitter, name)
{
	if ( dst->get_post_size() > 0 ) 
		init();
}

void DuplexConnection::free()
{
	delete bkw;
}


DuplexConnection::~DuplexConnection()
{
	if ( dst->get_post_size() > 0 ) 
		free();
}


void DuplexConnection::compute_reverse_matrix()
{
	stringstream oss;
	oss << "DuplexConnection: ("<< get_name() << "): Computing backward matrix ...";
	logger->msg(oss.str(),NOTIFICATION);

	NeuronID maxrows = get_m_rows();
	NeuronID maxcols = get_n_cols();
	NeuronID ** rowwalker = new NeuronID * [maxrows+1];
	// copy pointer arrays
	for ( NeuronID i = 0 ; i < maxrows+1 ; ++i ) {
		rowwalker[i] = (fwd->get_rowptrs())[i];
	}
	for ( NeuronID j = 0 ; j < maxcols ; ++j ) {
		if ( dst->localrank(j) ) {
			for ( NeuronID i = 0 ; i < maxrows ; ++i ) {
				if (rowwalker[i] < fwd->get_rowptrs()[i+1]) { // stop when reached end of row
					if (*rowwalker[i]==j) { // if there is an element for that column add pointer to backward matrix
						bkw->push_back(j,i,fwd->get_ptr(i,j));
						++rowwalker[i];  // move on when processed element
					}
				}
			}
		}
	}
	bkw->fill_zeros();
	delete [] rowwalker;

	if ( fwd->get_nonzero() != bkw->get_nonzero() ) {
		oss.str("");
		oss << "DuplexConnection: ("<< get_name() << "): " 
			<< bkw->get_nonzero() 
			<< " different number of non-zero elements in bkw and fwd matrix.";
		logger->msg(oss.str(),ERROR);
	}
}

