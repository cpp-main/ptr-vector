SET(LIB_SRC ptr_vector.c str_vector.c)
SET(INC_HEAD ptr_vector.h str_vector.h)
SET(CMAKE_C_FLAGS "-std=c99")

ADD_LIBRARY(ptr_vector_static STATIC ${LIB_SRC})
SET_TARGET_PROPERTIES(ptr_vector_static PROPERTIES OUTPUT_NAME "ptr_vector")

INSTALL(TARGETS ptr_vector_static
    ARCHIVE DESTINATION lib
    )
INSTALL(FILES ${INC_HEAD} DESTINATION include/)
