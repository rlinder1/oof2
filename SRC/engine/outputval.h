// -*- C++ -*-


/* This software was produced by NIST, an agency of the U.S. government,
* and by statute is not subject to copyright in the United States.
 * Recipients of this software assume all responsibilities associated
 * with its operation, modification and maintenance. However, to
 * facilitate maintenance we ask that before distributing modified
 * versions of this software, you first contact the authors at
 * oof_manager@nist.gov. 
 */

#include <oofconfig.h>

#ifndef OUTPUTVAL_H
#define OUTPUTVAL_H

#include "common/pythonexportable.h"

#include <iostream>
#include <math.h>
#include <vector>

class IndexP;
class IteratorP;

// The OutputVal classes defined here are used to ferry values from
// the finite element mesh out to the Python output machinery. The
// classes give the output machinery the ability to decide what
// further processing is possible (eg computing components or
// invariants).

// OutputVal does not have a template parameter for the output type
// (ie, OutputVal<double>, OutputVal<SymmMatrix3> etc) because the
// templated subclasses would still have to be swigged separately, so
// there wouldn't be much effort saved.

class OutputVal : public PythonExportable<OutputVal> {
protected:
  static std::string modulename_;
  int refcount;
public:
  OutputVal();
  virtual ~OutputVal();
  virtual unsigned int dim() const = 0;
  virtual OutputVal *clone() const = 0;
  virtual OutputVal *zero() const = 0;
  virtual OutputVal *one() const = 0;
  virtual const std::string &modulename() const { return modulename_; }
  virtual double operator[](const IndexP&) const = 0;
  virtual double &operator[](const IndexP&) = 0;
  virtual OutputVal &operator+=(const OutputVal&) = 0;
  virtual OutputVal &operator-=(const OutputVal&) = 0;
  virtual OutputVal &operator*=(double) = 0;
  // Component-wise operations.
  virtual void component_pow(int) = 0;
  virtual void component_square() = 0;
  virtual void component_sqrt() = 0;
  virtual std::vector<double> *value_list() const = 0;
  virtual double magnitude() const = 0;
  // IO ops.
  virtual void print(std::ostream&) const = 0;
  // getIndex converts the string representation of a component index
  // into an IndexP object that can be used to extract a component.
  virtual IndexP getIndex(const std::string&) const = 0;
  virtual IteratorP getIterator() const = 0;
  friend class OutputValue;
};

std::ostream &operator<<(std::ostream &, const OutputVal&);

class ScalarOutputVal : public OutputVal {
private:
  static std::string classname_;
  double val;
public:
  ScalarOutputVal(double x) : val(x) {}
  virtual unsigned int dim() const { return 1; }
  virtual OutputVal *clone() const { return new ScalarOutputVal(val); }
  virtual OutputVal *zero() const { return new ScalarOutputVal(0.0); }
  virtual OutputVal *one() const { return new ScalarOutputVal(1.0); }
  virtual const std::string &classname() const { return classname_; }
  virtual OutputVal &operator+=(const OutputVal &other) {
    const ScalarOutputVal &another =
      dynamic_cast<const ScalarOutputVal&>(other);
    val += another.val;
    return *this;
  }
  virtual OutputVal &operator-=(const OutputVal &other) {
    const ScalarOutputVal &another =
      dynamic_cast<const ScalarOutputVal&>(other);
    val -= another.val;
    return *this;
  }
  virtual OutputVal &operator*=(double a) {
    val *= a;
    return *this;
  }
  ScalarOutputVal &operator+=(double x) {
    val += x;
    return *this;
  }
  virtual void component_pow(int p) {
    val = pow(val, p);
  }
  virtual void component_square() {
    val *= val;
  }
  virtual void component_sqrt() {
    val = sqrt(val);
  }
  virtual std::vector<double> *value_list() const;
  virtual double magnitude() const { return fabs(val); }
  double value() const { return val; }
  double &value() { return val; }
  virtual double operator[](const IndexP&) const;
  virtual double &operator[](const IndexP&);
  virtual IndexP getIndex(const std::string&) const;
  virtual IteratorP getIterator() const;
  
  virtual void print(std::ostream&) const;
};

ScalarOutputVal operator+(const ScalarOutputVal&, const ScalarOutputVal&);
ScalarOutputVal operator-(const ScalarOutputVal&, const ScalarOutputVal&);
ScalarOutputVal operator*(const ScalarOutputVal&, double);
ScalarOutputVal operator*(double, const ScalarOutputVal&);
ScalarOutputVal operator/(ScalarOutputVal&, double);

class VectorOutputVal : public OutputVal {
private:
  unsigned int size_;
  double *data;
  static std::string classname_;
public:
  VectorOutputVal(int n);
  VectorOutputVal(const VectorOutputVal&);
  VectorOutputVal(const std::vector<double>&);
  virtual ~VectorOutputVal() { delete [] data; }
  virtual unsigned int dim() const { return size_; }
  virtual OutputVal *clone() const;
  virtual OutputVal *zero() const;
  virtual OutputVal *one() const;
  virtual const std::string &classname() const { return classname_; }
  unsigned int size() const { return size_; }
  virtual OutputVal &operator+=(const OutputVal &other) {
    const VectorOutputVal &another = 
      dynamic_cast<const VectorOutputVal&>(other);
    for(unsigned int i=0; i<size_; i++)
      data[i] += another.data[i];
    return *this;
  }
  virtual OutputVal &operator-=(const OutputVal &other) {
    const VectorOutputVal &another = 
      dynamic_cast<const VectorOutputVal&>(other);
    for(unsigned int i=0; i<size_; i++)
      data[i] -= another.data[i];
    return *this;
  }
  virtual OutputVal &operator*=(double a) {
    for(unsigned int i=0; i<size_; i++)
      data[i] *= a;
    return *this;
  }

  virtual void component_pow(int p) {
    for(unsigned int i=0;i<size_;i++)
      data[i] = pow(data[i],p);
  }
  virtual void component_square() {
    for(unsigned int i=0;i<size_;i++)
      data[i] *= data[i];
  }
  virtual void component_sqrt() {
    for(unsigned int i=0;i<size_;i++)
      data[i] = sqrt(data[i]);
  }

  double dot(const std::vector<double>&) const;

  virtual std::vector<double> *value_list() const;
  double operator[](int i) const { return data[i]; }
  double &operator[](int i) { return data[i]; }
  virtual double operator[](const IndexP &p) const;
  virtual double &operator[](const IndexP &p);
  virtual IndexP getIndex(const std::string&) const;
  virtual IteratorP getIterator() const;
  virtual double magnitude() const;
  virtual void print(std::ostream&) const;
};

VectorOutputVal operator+(const VectorOutputVal&, const VectorOutputVal&);
VectorOutputVal operator-(const VectorOutputVal&, const VectorOutputVal&);
VectorOutputVal operator*(const VectorOutputVal&, double);
VectorOutputVal operator*(double, const VectorOutputVal&);
VectorOutputVal operator/(VectorOutputVal&, double);


//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=//

// OutputValue is a generic wrapper for the different OutputVal
// classes.  It takes ownership of the OutputVal that it's initialized
// with, handles the reference counting, and deletes the OutputVal
// when the reference count goes to zero.

class OutputValue {
private:
  OutputVal *val;
public:
  OutputValue() {}  // Dummy constructor
  OutputValue(OutputVal*);
  OutputValue(const OutputValue&);
  ~OutputValue();

  unsigned int dim() const { return val->dim(); }

  // valueRef and valuePtr do *not* increment the reference count, so
  // it's important to use them only in situations in which the
  // returned reference or pointer cannot possibly outlive the
  // OutputValue.
  const OutputVal &valueRef() const { return *val; }
  const OutputVal *valuePtr() const { return val; } 
  // For situations in which the OutputVal might outlive the
  // OutputValue, use valueClone instead of valueRef or valuePtr.
  // valueClone returns a new copy of the OutputVal.  It's the calling
  // function's responsibility to see that the copy is deleted.
  OutputVal *valueClone() const { return val->clone(); }

  const OutputValue &operator+=(const OutputValue &other) {
    *val += *other.val;
    return *this;
  }
  const OutputValue &operator-=(const OutputValue &other) {
    *val -= *other.val;
    return *this;
  }
  const OutputValue &operator *=(double x) {
    *val *= x;
    return *this;
  }
  double operator[](const IndexP &p) const { return (*val)[p]; }
  double &operator[](const IndexP &p) { return (*val)[p]; }
  int nrefcount() { return (*val).refcount; } // for debugging
  friend std::ostream &operator<<(std::ostream&, const OutputValue&);
};

OutputValue operator*(double x, const OutputValue &ov);
OutputValue operator*(const OutputValue &ov, double x);
OutputValue operator/(const OutputValue &ov, double x);
OutputValue operator+(const OutputValue &a, const OutputValue &b);
OutputValue operator-(const OutputValue &a, const OutputValue &b);

std::ostream &operator<<(std::ostream&, const OutputValue&);

// TODO: Energies should not be calculated by using the properties
// (each property contributing its part).  Instead, the Fluxes should
// be used.  e += Flux*Grad Field.  Need a better abstract way of
// defining Energies.

#endif // OUTPUTVAL_H
