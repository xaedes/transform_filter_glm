#pragma once

#include "im_param/im_param.h"
#include "transform_filter_glm/transform_filter_independent_kalman_rpy.h"

namespace im_param {

    template <class backend_type>
    backend_type& parameter(
        backend_type& backend,
        ::transform_filter_glm::TransformFilterIndependentKalmanRpy::Params& params, 
        const TypeHolder<::transform_filter_glm::TransformFilterIndependentKalmanRpy>&)
    {
        parameter(backend, "transformation",   params.transformation);
        parameter(backend, "enable_transpose", params.enable_transpose);
        parameter(backend, "uncertainty_angle_observation",    params.uncertainty_angle_observation,    0.0f, 2.0f);
        parameter(backend, "uncertainty_angle_process",        params.uncertainty_angle_process,        0.0f, 2.0f);
        parameter(backend, "uncertainty_turnrate_process",     params.uncertainty_turnrate_process,     0.0f, 2.0f);
        parameter(backend, "uncertainty_position_observation", params.uncertainty_position_observation, 0.0f, 2.0f);
        parameter(backend, "uncertainty_position_process",     params.uncertainty_position_process,     0.0f, 2.0f);
        parameter(backend, "uncertainty_velocity_process",     params.uncertainty_velocity_process,     0.0f, 2.0f);
        parameter(backend, "time_lag",                         params.time_lag,                        -1.0f, 1.0f);
        return backend;
    }

}
