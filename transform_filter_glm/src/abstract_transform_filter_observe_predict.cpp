#include "transform_filter_glm/abstract_transform_filter_observe_predict.h"

namespace transform_filter_glm {
    
    AbstractTransformFilterObservePredict::~AbstractTransformFilterObservePredict()
    {}
    
    void AbstractTransformFilterObservePredict::parameterUpdate()
    {}

    void AbstractTransformFilterObservePredict::filter_implementation()
    {
        uint32_t obs_idx = 0;
        uint32_t ts_idx = 0;

        // m_timestamps_lag_fix = m_timestamps + timelag
        m_timestamps_requested.assign(m_timestamps.begin(), m_timestamps.end());

        // change m_timestamps to account for time lag. derived classes will use the changed timestamps.
        // the originally requested timestamps will be used as stamp for the filter results
        auto time_lag = params.reversed ? -params.time_lag : +params.time_lag;
        for (int i=0; i<m_timestamps.size(); ++i)
        {
            // m_timestamps_lag_fix.push_back(m_timestamps[i] + params.timelag);
            m_timestamps[i] = m_timestamps_requested[i] + time_lag;
        }

        reset_implementation();


        bool is_valid = false;
        while (ts_idx < m_timestamps.size())
        {
            if ((obs_idx < m_observations.size()) && ((m_observations[obs_idx].timestamp < m_timestamps[ts_idx]) ^ params.reversed))
            {
                // observation
                is_valid = true;
                auto stamped_transform = observation_implementation(obs_idx);
                //m_filtered.push_back(stamped_transform);
                //m_valid.push_back(is_valid);
                ++obs_idx;
            }
            else
            {
                // prediction
                auto stamped_transform = prediction_implementation(ts_idx);
                stamped_transform.timestamp = m_timestamps_requested[ts_idx];
                m_filtered.push_back(stamped_transform);
                m_valid.push_back(is_valid);
                ++ts_idx;
            }
        }

    }

} // namespace transform_filter_glm

