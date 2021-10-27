#pragma once

#include <vector>
#include "kalman_glm/independent_kalman_xyz_rpy.h"
#include "transform_filter_glm/abstract_transform_filter_observe_predict.h"

namespace transform_filter_glm {

    struct TransformFilterIndependentKalmanRpy : public AbstractTransformFilterObservePredict
    {
        virtual ~TransformFilterIndependentKalmanRpy();

        struct Params
        {
            glm::mat4 transformation = glm::mat4(
                0, -1, 0, 0,
                0, 0, 1, 0,
                -1, 0, 0, 0,
                0, 0, 0, 1
            );
            bool enable_transpose = true;
            float uncertainty_angle_observation = 0.44f;
            float uncertainty_angle_process = 1.3f;
            float uncertainty_turnrate_process = 0.1f;
            float uncertainty_position_observation = 0.1f * 0.1f;
            float uncertainty_position_process = 0.001f;
            float uncertainty_velocity_process = 1.0f;

            float time_lag = 0.0f;

            bool reversed = false;
        };

        Params params;
        void parameterUpdate();

        using IndependentKalmanXyzRpy = kalman_glm::IndependentKalmanXyzRpy<>;
        IndependentKalmanXyzRpy m_kalman;
    protected:
        virtual void reset_implementation() override;
        virtual StampedTransform observation_implementation(uint32_t observation_idx) override;
        virtual StampedTransform prediction_implementation(uint32_t timestamp_idx) override;

        
        Params m_params;
    };

} // namespace transform_filter_glm
