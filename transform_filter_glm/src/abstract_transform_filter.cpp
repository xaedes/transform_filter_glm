#include "transform_filter_glm/abstract_transform_filter.h"

namespace transform_filter_glm {
    
    AbstractTransformFilter::~AbstractTransformFilter()
    {}
    
    void AbstractTransformFilter::parameterUpdate()
    {}

    const std::vector<StampedTransform>& AbstractTransformFilter::filter(
        const std::vector<StampedTransform>& observations, 
        const std::vector<double>& timestamps
    )
    {
        m_observations.assign(observations.begin(), observations.end());
        m_timestamps.assign(timestamps.begin(), timestamps.end());


        m_filtered.clear();
        m_valid.clear();
        if (m_timestamps.size() == 0) return m_filtered;
        if (m_observations.size() == 0)
        {
            // we have no know transforms, use identity transform everywhere
            for(int i=0; i<m_timestamps.size(); ++i)
            {
                m_filtered.push_back({m_timestamps[i], glm::mat4(1)});
                m_valid.push_back(true);
            }
        }
        else
        {
            this->filter_implementation();
        }

        return m_filtered;
    }

} // namespace transform_filter_glm

