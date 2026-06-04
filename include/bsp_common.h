#ifndef BSP_COMMON_H
#define BSP_COMMON_H

/** All FSP error codes are returned using this macro. Calls ::FSP_ERROR_LOG function if condition "a" is false. Used
 * to identify runtime errors in FSP functions. */
#define FSP_ERROR_LOG(err)

#define FSP_ERROR_RETURN(a, err)                            \
        {                                                   \
            if ((a))                                        \
            {                                               \
                (void) 0;              /* Do nothing */     \
            }                                               \
            else                                            \
            {                                               \
                FSP_ERROR_LOG(err);                         \
                return err;                                 \
            }                                               \
        }

#if (3 == BSP_CFG_ASSERT)
 #define FSP_ASSERT(a)
#elif (2 == BSP_CFG_ASSERT)
 #define FSP_ASSERT(a)    {assert(a);}
#else
 #define FSP_ASSERT(a)    FSP_ERROR_RETURN((a), FSP_ERR_ASSERTION)
#endif                                 // ifndef FSP_ASSERT

#endif
