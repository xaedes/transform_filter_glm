#pragma once

#include <vector>
#include "kalman_glm/pose_rpy.h"
#include "transform_filter_glm/smoother_sfb.h"

namespace transform_filter_glm {

    /**
     * @brief      PoseRpy smoother, simple forward backward
     *
     * @tparam     TransformFilterType  { description }
     */
    template<
        class TransformFilterType
    >
    struct SmootherSfbRpy : public SmootherSfb<kalman_glm::PoseRpy, TransformFilterType>
    {
        using SmootherSfb::SmootherSfb;

        using Params = typename transform_filter_type::Params;

        Params params;
        virtual void parameterUpdate() {};

        virtual ~SmootherSfbRpy() {}

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
