// Dynamic Array String Builder
// A simple dynamic array strip off from NOB.h


#ifndef dasb_H
#define dasb_H

#ifndef NOB_ASSERT
#include <assert.h>
#define NOB_ASSERT assert
#endif /* NOB_ASSERT */

#ifndef NOB_REALLOC
#include <stdlib.h>
#define NOB_REALLOC realloc
#endif /* NOB_REALLOC */

#ifndef NOB_FREE
#include <stdlib.h>
#define NOB_FREE free
#endif /* NOB_FREE */

#define shift(xs, xs_sz) (NOB_ASSERT((xs_sz) > 0), (xs_sz)--, *(xs)++)

#define DA_INIT_CAP 256
#define DECLTYPE_CAST(T)

#define da_reserve(da, expected_capacity)                                                                          \
  do {                                                                                                             \
    if ((expected_capacity) > (da)->capacity) {                                                                    \
      if ((da)->capacity == 0) {                                                                                   \
        (da)->capacity = DA_INIT_CAP;                                                                              \
      }                                                                                                            \
      while ((expected_capacity) > (da)->capacity) {                                                               \
        (da)->capacity *= 2;                                                                                       \
      }                                                                                                            \
      (da)->items = DECLTYPE_CAST((da)->items)NOB_REALLOC((da)->items, (da)->capacity * sizeof(*(da)->items));     \
      NOB_ASSERT((da)->items != NULL && "Buy more RAM lol");                                                       \
    }                                                                                                              \
}while(0)

// Append an item to a dynamic array
#define da_append(da, item)             \
  do {                                  \
    da_reserve((da), (da)->count + 1);  \
    (da)->items[(da)->count++] = (item);\
  } while (0)

#define da_free(da) NOB_FREE((da).items)

// Append several items to a dynamic array
#define da_append_many(da, new_items, new_items_count)                                      \
  do {                                                                                      \
    da_reserve((da), (da)->count + (new_items_count));                                      \
    memcpy((da)->items + (da)->count, (new_items), (new_items_count)*sizeof(*(da)->items)); \
    (da)->count += (new_items_count);                                                       \
  } while (0)

#define da_pop(da) (da)->items[(NOB_ASSERT((da)->count > 0), --(da)->count)]
#define da_first(da) (da)->items[(NOB_ASSERT((da)->count > 0), 0)]
#define da_last(da) (da)->items[(NOB_ASSERT((da)->count > 0), (da)->count-1)]

#define da_foreach(Type, it, da) for (Type *it = (da)->items; it < (da)->items + (da)->count; ++it)

#ifndef STRIP_STRING_BUILDER
#define STRIP_STRING_BUILDER

#include <string.h>

typedef struct {
  char* items;
  size_t count;
  size_t capacity;
}String_Builder;

// Append a NULL-terminated string to a string builder
#define sb_append_cstr(sb, cstr)    \
  do {                              \
    const char *s = (cstr);         \
    size_t n = strlen(s);           \
    da_append_many(sb, s, n);       \
  } while (0)

// Append a single NULL character at the end of a string builder. So then you can
// use it a NULL-terminated C string
#define sb_append_null(sb) da_append_many(sb, "", 1)

#define sb_append da_append

// Free the memory allocated by a string builder
#define sb_free(sb) NOB_FREE((sb).items)

#endif // STRIP_STRING_BUILDER

#endif /* dasb_H */
