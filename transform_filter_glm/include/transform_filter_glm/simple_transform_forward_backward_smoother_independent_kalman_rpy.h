#pragma once

#include <vector>
#include "kalman_glm/independent_kalman_xyz_rpy.h"
#include "transform_filter_glm/generic_simple_transform_forward_backward_smoother_rpy.h"
#include "transform_filter_glm/transform_filter_independent_kalman_rpy.h"

namespace transform_filter_glm {

    struct SimpleTransformForwardBackwardSmootherIndependentKalmanRpy : public GenericSimpleTransformForwardBackwardSmootherRpy<TransformFilterIndependentKalmanRpy>
    {
        virtual ~SimpleTransformForwardBackwardSmootherIndependentKalmanRpy();

        struct Params
        {
            using ParamsIndependentKalmanRpy = typename TransformFilterIndependentKalmanRpy::Params;

            ParamsIndependentKalmanRpy kalman;
        };
        Params params;
        void parameterUpdate();

        virtual kalman_glm::PoseRpy to_smoothing_value(StampedTransform tf) override;
        virtual StampedTransform from_smoothing_value(kalman_glm::PoseRpy pose, double timestamp) override;

    };

} // namespace transform_filter_glm
