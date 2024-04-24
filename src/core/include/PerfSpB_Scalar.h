#pragma once
#include "PerfSparseBLAS_func.h"
#include "PerfSparseBLAS_type.h"
#include <stdlib.h>

typedef union
{
    bool BOOL_value;
    int8_t INT8_value;
    int16_t INT16_value;
    int32_t INT32_value;
    int64_t INT64_value;
    uint8_t UINT8_value;
    uint16_t UINT16_value;
    uint32_t UINT32_value;
    uint64_t UINT64_value;
    float FP32_value;
    double FP64_value;
} Scalar_Value;

/**
 * @ingroup perfSpB_scalar
 * @brief A structure to represent scalar.
 * @details This class stores basic information about a scalar.
 */
struct perfSpB_scalar_opaque
{
    perfSpB_type element_type; /**< Element data type */
    Scalar_Value value;    /**< Scalar value*/
};

perfSpB_info perfSpB_scalar_setZero(perfSpB_scalar s);
