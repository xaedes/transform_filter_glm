#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/abstract_transform_filter_observe_predict.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::AbstractTransformFilterObservePredict::Params& params, 
        const TypeHolder<::transform_filter_glm::AbstractTransformFilterObservePredict>&)
    {
        return backend;
    }

}
