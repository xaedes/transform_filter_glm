#pragma once

#include <vector>
#include "kalman_glm/pose_rpy.h"
#include "transform_filter_glm/abstract_transform_forward_backward_smoother.h"

namespace transform_filter_glm {

    template<
        class TransformFilterType
    >
        struct GenericTransformForwardBackwardSmootherRpy : public AbstractTransformForwardBackwardSmoother<kalman_glm::PoseRpy, TransformFilterType>
    {
        using AbstractTransformForwardBackwardSmoother::AbstractTransformForwardBackwardSmoother;

        using Params = typename transform_filter_type::Params;

        Params params;
        virtual void parameterUpdate() {};

        virtual ~GenericTransformForwardBackwardSmootherRpy() {}

        virtual kalman_glm::PoseRpy to_smoothing_value(StampedTransform tf) override
        {
            return kalman_glm::PoseRpy::mat4_to_pose(tf.transform);
        }

        virtual StampedTransform from_smoothing_value(kalman_glm::PoseRpy pose, double timestamp) override
        {
            return { timestamp, kalman_glm::PoseRpy::pose_to_mat4(pose) };
        }

        kalman_glm::PoseRpy mix(kalman_glm::PoseRpy a, kalman_glm::PoseRpy b, float k) override
        {
            return kalman_glm::PoseRpy{
                glm::mix(a.position, b.position, k),
                glm::mix(a.roll_pitch_yaw, b.roll_pitch_yaw, k),
            };
        }

    };


} // namespace transform_filter_glm
