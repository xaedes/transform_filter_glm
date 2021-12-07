#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/filter.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::Filter::Params& params, 
        const TypeHolder<::transform_filter_glm::Filter>&)
    {
        return backend;
    }


    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::FilterObservePredict::Params& params, 
        const TypeHolder<::transform_filter_glm::FilterObservePredict>&)
    {
        return backend;
    }

}
