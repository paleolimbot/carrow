
#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include <R.h>
#include <Rinternals.h>
#include "carrow/carrow.h"

void finalize_array_xptr(SEXP array_xptr);

static inline struct ArrowArray* array_from_xptr(SEXP array_xptr, const char* arg) {
  if (!Rf_inherits(array_xptr, "arrowvctrs_array")) {
    Rf_error("`%s` must be an object created with arrow_array()", arg);
  }

  struct ArrowArray* array = (struct ArrowArray*) R_ExternalPtrAddr(array_xptr);
  if (array == NULL) {
    Rf_error("`%s` is an external pointer to NULL", arg); // # nocov
  }

  if (array->release == NULL) {
    Rf_error("`%s` has already been released and is no longer valid", arg); // # nocov
  }

  return array;
}

static inline struct ArrowArray* nullable_array_from_xptr(SEXP array_xptr, const char* arg) {
  if (array_xptr == R_NilValue) {
    return NULL;
  } else {
    return array_from_xptr(array_xptr, arg);
  }
}

static inline SEXP array_xptr_new(struct ArrowArray* array) {
  SEXP array_xptr = PROTECT(R_MakeExternalPtr(array, R_NilValue, R_NilValue));
  Rf_setAttrib(array_xptr, R_ClassSymbol, Rf_mkString("arrowvctrs_array"));
  UNPROTECT(1);
  return array_xptr;
}

#endif