/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco adapted for Linux by Bernd Porr

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPFILTERS_RBJ_H
#define DSPFILTERS_RBJ_H

#include "Common.h"
#include "Biquad.h"
#include "State.h"

namespace Iir {

/*
 * Filter realizations based on Robert Bristol-Johnson formulae:
 *
 * http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
 *
 */

namespace RBJ {

	template <class StateType>
	struct DllExport RBJbase : BiquadBase
	{
	public:
		template <typename Sample>
			inline Sample filter(Sample s) {
			return state.filter(s,*this);
		}
	private:
		StateType state;
	};

	struct DllExport LowPass : RBJbase<DEFAULT_STATE>
	{
		void setup(double sampleRate,
			    double cutoffFrequency,
			    double q);
	};

	struct DllExport HighPass : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double q);
	};

	struct DllExport BandPass1 : RBJbase<DEFAULT_STATE>
	{
		// (constant skirt gain, peak gain = Q)
		void setup (double sampleRate,
			    double centerFrequency,
			    double bandWidth);
	};

	struct DllExport BandPass2 : RBJbase<DEFAULT_STATE>
	{
		// (constant 0 dB peak gain)
		void setup (double sampleRate,
			    double centerFrequency,
			    double bandWidth);
	};

	struct DllExport BandStop : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double centerFrequency,
			    double bandWidth);
	};

	struct DllExport LowShelf : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double shelfSlope);
	};

	struct DllExport HighShelf : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double shelfSlope);
	};

	struct DllExport BandShelf : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double centerFrequency,
			    double gainDb,
			    double bandWidth);
	};

	struct DllExport AllPass : RBJbase<DEFAULT_STATE>
	{
		void setup (double sampleRate,
			    double phaseFrequency,
			    double q);
	};
	
}

}


#endif
