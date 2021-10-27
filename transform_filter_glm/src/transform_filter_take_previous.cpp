#include "transform_filter_glm/transform_filter_take_previous.h"

namespace transform_filter_glm {
    
    TransformFilterTakePrevious::~TransformFilterTakePrevious()
    {}

    void TransformFilterTakePrevious::parameterUpdate()
    {

    }
    
    void TransformFilterTakePrevious::filter_implementation()
    {
        // use transforms preceeding the points in time
        uint32_t observation_idx = 0;

        for(int i=0; i<m_timestamps.size(); ++i)
        {
            while (
                (observation_idx+1 < m_observations.size())
             && (m_observations[observation_idx].timestamp < m_timestamps[i])
             && (m_observations[observation_idx+1].timestamp < m_timestamps[i])
            )
            {
                ++observation_idx;
            }
            m_filtered.push_back(m_observations[observation_idx]);
        }
    }

} // namespace transform_filter_glm

