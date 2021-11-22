
#ifndef carrow_SCHEMA_H_INCLUDED
#define carrow_SCHEMA_H_INCLUDED

#include <R.h>
#include <Rinternals.h>
#include <memory.h>
#include <stdint.h>
#include <string.h>
#include "carrow/carrow.h"

void finalize_schema_xptr(SEXP schema_xptr);
void finalize_schema(struct ArrowSchema* schema);
unsigned char* metadata_from_sexp(SEXP metadata_sexp, const char* arg);
SEXP sexp_from_metadata(unsigned char* metadata);

static inline struct ArrowSchema* schema_from_xptr(SEXP schema_xptr, const char* arg) {
  if (!Rf_inherits(schema_xptr, "carrow_schema")) {
    Rf_error("`%s` must be an object created with carrow_schema()", arg);
  }

  struct ArrowSchema* schema = (struct ArrowSchema*) R_ExternalPtrAddr(schema_xptr);
  if (schema == NULL) {
    Rf_error("`%s` is an external pointer to NULL", arg); // # nocov
  }

  if (schema->release == NULL) {
    Rf_error("`%s` has already been released and is no longer valid", arg); // # nocov
  }

  return schema;
}

static inline struct ArrowSchema* nullable_schema_from_xptr(SEXP schema_xptr, const char* arg) {
  if (schema_xptr == R_NilValue) {
    return NULL;
  } else {
    return schema_from_xptr(schema_xptr, arg);
  }
}

static inline SEXP schema_xptr_new(struct ArrowSchema* schema) {
  SEXP schema_xptr = PROTECT(R_MakeExternalPtr(schema, R_NilValue, R_NilValue));
  Rf_setAttrib(schema_xptr, R_ClassSymbol, Rf_mkString("carrow_schema"));
  UNPROTECT(1);
  return schema_xptr;
}

#endif
