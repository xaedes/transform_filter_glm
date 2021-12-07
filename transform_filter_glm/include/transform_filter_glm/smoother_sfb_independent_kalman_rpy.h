#pragma once

#include <vector>
#include "kalman_glm/independent_kalman_xyz_rpy.h"
#include "transform_filter_glm/smoother_sfb_rpy.h"
#include "transform_filter_glm/filter_independent_kalman_rpy.h"

namespace transform_filter_glm {

    struct SmootherSfbIndependentKalmanRpy : public SmootherSfbRpy<FilterIndependentKalmanRpy>
    {
        virtual ~SmootherSfbIndependentKalmanRpy();

        struct Params
        {
            using ParamsIndependentKalman = typename FilterIndependentKalmanRpy::Params;

            ParamsIndependentKalman kalman;
        };
        Params params;
        void parameterUpdate();

        virtual kalman_glm::PoseRpy to_smoothing_value(StampedTransform tf) override;
        virtual StampedTransform from_smoothing_value(kalman_glm::PoseRpy pose, double timestamp) override;

    };

} // namespace transform_filter_glm
