#ifdef VIRTUINO_ENVIRONMENT
  #define ASSERT( bool_expression, error_message ) \
    if (!bool_expression) { throw error_message; }
#else
  #define ASSERT( bool_expression, error_message ) \
    if (!bool_expression) { log::error(error_message); exit(1); }
#endif
