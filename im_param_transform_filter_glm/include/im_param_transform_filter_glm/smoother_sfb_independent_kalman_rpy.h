#pragma once

#include "im_param/im_param.h"
#include "im_param_transform_filter_glm/filter_independent_kalman_rpy.h"
#include "transform_filter_glm/smoother_sfb_independent_kalman_rpy.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::SmootherSfbIndependentKalmanRpy::Params& params, 
        const TypeHolder<::transform_filter_glm::SmootherSfbIndependentKalmanRpy>&)
    {
        parameter(
            backend, "kalman", 
            static_cast<::transform_filter_glm::FilterIndependentKalmanRpy::Params&>(params.kalman), 
            TypeHolder<::transform_filter_glm::FilterIndependentKalmanRpy>()
        );
        return backend;
    }

}
