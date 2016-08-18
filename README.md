Auryn 
=====

This is the README file that comes with your version of Auryn.

![Auryn logo](http://www.fzenke.net/uploads/images/logo_trans_small.png "Auryn logo")

Auryn is a source package used to create highly specialized and optimized code
to simulate recurrent spiking neural networks with spike timing dependent
plasticity (STDP). It comes with the GPLv3 (please see COPYING).


Quick start
-----------

To download and compile the examples try:

```
sudo apt-get install cmake git build-essential libboost-all-dev
git clone https://github.com/fzenke/auryn.git && cd auryn/build/release
./bootstrap.sh && make
```

Then to install the library:
```
sudo make install
```
which will put it under `/usr/local/` or for a local install
```
make DESTDIR=./your/dir/ install
```


Documentation 
-------------

Please visit the wiki at http://www.fzenke.net/auryn/


Requirements
------------

Auryn needs the boost libraries (www.boost.org) with MPI support installed 
in development versions to compile.


Citing Auryn
------------

If you find Auryn useful and you use it, please cite:

Zenke, F. and Gerstner, W., 2014.  Limits to high-speed simulations of spiking
neural networks using general-purpose computers.  Front Neuroinform 8, 76. 
doi: 10.3389/fninf.2014.00076

url: http://journal.frontiersin.org/Journal/10.3389/fninf.2014.00076/abstract

Bibtex:
```
@article{zenke_limits_2014,
	title = {Limits to high-speed simulations of spiking neural networks using general-purpose computers},
	author = {Zenke, Friedemann and Gerstner, Wulfram},
	journal = {Front Neuroinform},
	year = {2014},
	volume = {8},
	url = {http://journal.frontiersin.org/Journal/10.3389/fninf.2014.00076/abstract},
	doi = {10.3389/fninf.2014.00076}
}
```



License & Copyright 
-------------------

Copyright 2014-2016 Friedemann Zenke

Auryn is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Auryn is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Auryn.  If not, see <http://www.gnu.org/licenses/>.

If you are using Auryn or parts of it for your work please cite:
Zenke, F. and Gerstner, W., 2014. Limits to high-speed simulations 
of spiking neural networks using general-purpose computers. 
Front Neuroinform 8, 76. doi: 10.3389/fninf.2014.00076
