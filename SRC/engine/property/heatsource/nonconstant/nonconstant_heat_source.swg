// -*- C++ -*-

/* This software was produced by NIST, an agency of the U.S. government,
 * and by statute is not subject to copyright in the United States.
 * Recipients of this software assume all responsibilities associated
 * with its operation, modification and maintenance. However, to
 * facilitate maintenance we ask that before distributing modified
 * versions of this software, you first contact the authors at
 * oof_manager@nist.gov.
 */

%module heatsource

%{
#include "engine/property/heatsource/nonconstant/nonconstant_heat_source.h"
%}

%include "common/typemaps.swg"
%include "engine/propertyhdr.swg"
%extern "engine/symmmatrix.swg"

%pragma(python) include="nonconstant_heat_source.spy"

class NonconstantHeatSource : public Property {
};


class TestNonconstantHeatSource : public NonconstantHeatSource {
public:
  TestNonconstantHeatSource(PyObject *reg, char *name, int testno);
};
