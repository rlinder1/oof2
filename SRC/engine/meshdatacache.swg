// -*- C++ -*-

/* This software was produced by NIST, an agency of the U.S. government,
 * and by statute is not subject to copyright in the United States.
 * Recipients of this software assume all responsibilities associated
 * with its operation, modification and maintenance. However, to
 * facilitate maintenance we ask that before distributing modified
 * versions of this software, you first contact the authors at
 * oof_manager@nist.gov. 
 */

#ifndef MESHDATACACHE_SWG
#define MESHDATACACHE_SWG

%module meshdatacache

%include "engine/typemaps.swg"

%pragma(python) include="meshdatacache.spy"

%{
#include "engine/meshdatacache.h"
%}

class MeshDataCache {
public:
  void setMesh(FEMesh*);
  DoubleList *times();
  int size();
  void restore(double);
  void restoreLatest();
  bool interpolate(double);
  void record();
  void clear();
  double latestTime();
  double earliestTime();
  void transfer(MeshDataCache*);
  bool atLatest();
  bool atEarliest();
};

class MemoryDataCache : public MeshDataCache {
public:
  MemoryDataCache(FEMesh*);
  ~MemoryDataCache();
};

class DiskDataCache : public MeshDataCache {
public:
  DiskDataCache(FEMesh*);
  ~DiskDataCache();
};

#endif
