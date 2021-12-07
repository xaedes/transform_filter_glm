#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/smoother_sfb_rpy.h"

namespace im_param {

    template <class backend_type, class Arg>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::SmootherSfbRpy<Arg>::Params& params, 
        const TypeHolder<::transform_filter_glm::SmootherSfbRpy<Arg>>&)
    {
        return backend;
    }

}
