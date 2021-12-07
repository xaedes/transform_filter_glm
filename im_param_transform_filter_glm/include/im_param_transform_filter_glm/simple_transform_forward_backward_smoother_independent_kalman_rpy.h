#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/simple_transform_forward_backward_smoother_independent_kalman_rpy.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::SimpleTransformForwardBackwardSmootherIndependentKalmanRpy::Params& params, 
        const TypeHolder<::transform_filter_glm::SimpleTransformForwardBackwardSmootherIndependentKalmanRpy>&)
    {
        parameter(
            backend, "kalman", 
            static_cast<::transform_filter_glm::TransformFilterIndependentKalmanRpy::Params&>(params.kalman), 
            TypeHolder<::transform_filter_glm::TransformFilterIndependentKalmanRpy>()
        );
        return backend;
    }

}
