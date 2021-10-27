#include "transform_filter_glm/transform_filter_independent_kalman_rpy.h"

namespace transform_filter_glm {
    
    TransformFilterIndependentKalmanRpy::~TransformFilterIndependentKalmanRpy()
    {}

    void TransformFilterIndependentKalmanRpy::parameterUpdate()
    {
        AbstractTransformFilterObservePredict::params.reversed = params.reversed;
        AbstractTransformFilterObservePredict::params.time_lag = params.time_lag;
        AbstractTransformFilterObservePredict::parameterUpdate();

        m_kalman.set_enable_transpose(params.enable_transpose);
        m_kalman.set_transformation(params.transformation);

        /*
        m_kalman.set_time_variant_angle_observation_uncertainty(
            IndependentKalmanXyzRpy::FilterObservationUncertainty(
                params.uncertainty_angle_observation
            )
        );
        m_kalman.set_time_variant_angle_process_uncertainty(
            IndependentKalmanXyzRpy::FilterProcessUncertainty(
                params.uncertainty_angle_process
            )
        );
        m_kalman.set_time_variant_position_observation_uncertainty(
            IndependentKalmanXyzRpy::FilterObservationUncertainty(
                params.uncertainty_position_observation
            )
        );
        m_kalman.set_time_variant_position_process_uncertainty(
            IndependentKalmanXyzRpy::FilterProcessUncertainty(
                params.uncertainty_position_process
            )
        );
        /*/
        m_kalman.set_time_invariant_angle_observation_uncertainty(
            IndependentKalmanXyzRpy::FilterObservationUncertainty(
                params.uncertainty_angle_observation
            )
        );
        m_kalman.set_time_invariant_position_observation_uncertainty(
            IndependentKalmanXyzRpy::FilterObservationUncertainty(
                params.uncertainty_position_observation
            )
        );
        m_kalman.set_time_variant_angle_process_uncertainty(
            IndependentKalmanXyzRpy::FilterProcessUncertainty(
                params.uncertainty_angle_process, 0,
                0, params.uncertainty_turnrate_process
            )
        );
        m_kalman.set_time_variant_position_process_uncertainty(
            IndependentKalmanXyzRpy::FilterProcessUncertainty(
                params.uncertainty_position_process, 0,
                0, params.uncertainty_velocity_process
            )
        );
        //*/
    }

    void TransformFilterIndependentKalmanRpy::reset_implementation()
    {
        m_kalman.reset();
        parameterUpdate();
    }
    
    StampedTransform TransformFilterIndependentKalmanRpy::observation_implementation(uint32_t observation_idx)
    {
        auto timestamp = m_observations[observation_idx].timestamp;

        m_kalman.observe(timestamp, m_observations[observation_idx].transform );
        
        // return {timestamp};
        return {timestamp, m_kalman.pose_as_mat4()};
    }
    StampedTransform TransformFilterIndependentKalmanRpy::prediction_implementation(uint32_t timestamp_idx)
    {
        auto timestamp = m_timestamps[timestamp_idx] ;

        //
        m_kalman.predict(timestamp);

        // return {timestamp};
        return {timestamp, m_kalman.pose_as_mat4()};
        // return {timestamp, m_kalman.state_as_mat(m_kalman.state())};
    }


} // namespace transform_filter_glm

