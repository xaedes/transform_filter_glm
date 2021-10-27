#include "transform_filter_glm/transform_forward_backward_smoother_independent_kalman_rpy.h"

namespace transform_filter_glm {
    
    TransformForwardBackwardSmootherIndependentKalmanRpy::~TransformForwardBackwardSmootherIndependentKalmanRpy()
    {}

    void TransformForwardBackwardSmootherIndependentKalmanRpy::parameterUpdate()
    {
        m_forward_filter.params = params.kalman;
        m_backward_filter.params = params.kalman;
        // m_backward_filter.params.time_lag *= -1; 
        m_forward_filter.params.reversed = false;
        m_backward_filter.params.reversed = true;
        m_forward_filter.parameterUpdate();
        m_backward_filter.parameterUpdate();
    }

    kalman_glm::PoseRpy TransformForwardBackwardSmootherIndependentKalmanRpy::to_smoothing_value(StampedTransform tf)
    {
        return m_forward_filter.m_kalman.mat4_to_pose(tf.transform);
    }

    StampedTransform TransformForwardBackwardSmootherIndependentKalmanRpy::from_smoothing_value(kalman_glm::PoseRpy pose, double timestamp)
    {
        return { timestamp, m_forward_filter.m_kalman.pose_to_mat4(pose) };
    }    
} // namespace transform_filter_glm

