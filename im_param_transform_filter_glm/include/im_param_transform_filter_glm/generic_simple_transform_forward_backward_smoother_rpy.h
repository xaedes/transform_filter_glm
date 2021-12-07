#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/generic_simple_transform_forward_backward_smoother_rpy.h"

namespace im_param {

    template <class backend_type, class Arg>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::GenericSimpleTransformForwardBackwardSmootherRpy<Arg>::Params& params, 
        const TypeHolder<::transform_filter_glm::GenericSimpleTransformForwardBackwardSmootherRpy<Arg>>&)
    {
        return backend;
    }

}
