#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/smoother_sfb.h"

namespace im_param {

    template <class backend_type, class... Args>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::SmootherSfb<Args...>::Params& params, 
        const TypeHolder<::transform_filter_glm::SmootherSfb<Args...>>&)
    {
        return backend;
    }

}
