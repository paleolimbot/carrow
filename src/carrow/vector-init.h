
#pragma once

#include "abi.h"
#include "vector.h"
#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif


int arrow_vector_init(struct ArrowVector* vector, struct ArrowSchema* schema,
                      struct ArrowArray* array, struct ArrowStatus* status);
int arrow_vector_set_schema(struct ArrowVector* vector, struct ArrowSchema* schema,
                            struct ArrowStatus* status);
int arrow_vector_set_array(struct ArrowVector* vector, struct ArrowArray* array,
                           struct ArrowStatus* status);

#ifdef __cplusplus
}
#endif