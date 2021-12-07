#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/filter_take_previous.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::FilterTakePrevious::Params& params, 
        const TypeHolder<::transform_filter_glm::FilterTakePrevious>&)
    {
        return backend;
    }

}
