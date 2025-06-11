//
// Created by Romir Kulshrestha on 11/06/2025.
//

#include "ax25.h"

ax25_state ax25_init() {
    return {.max_retries = 8, .half_duplex = true, .timeout = 3000, };
}
