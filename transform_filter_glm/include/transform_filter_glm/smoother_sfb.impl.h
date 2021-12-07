#pragma once

#include "transform_filter_glm/smoother_sfb.h"

namespace transform_filter_glm {

    #define TEMPLATE_DEF template<class SmoothingValueType, class TransformFilterType>
    #define CLASS_DECL SmootherSfb<SmoothingValueType, TransformFilterType>

    TEMPLATE_DEF CLASS_DECL::~SmootherSfb()
    {}

    TEMPLATE_DEF void CLASS_DECL::parameterUpdate()
    {}

    TEMPLATE_DEF void CLASS_DECL::filter_implementation()
    {
        m_reversed_observations.assign(m_observations.rbegin(), m_observations.rend());
        m_reversed_timestamps.assign(m_timestamps.rbegin(), m_timestamps.rend());

        m_forward_filter.filter(m_observations, m_timestamps);
        m_backward_filter.filter(m_reversed_observations, m_reversed_timestamps);
        
        to_smoothing_values(m_forward_filter.m_filtered, m_forward_filtered);
        to_smoothing_values(m_backward_filter.m_filtered, m_backward_filtered);

        compute_validity();
        compute_weights();
        compute_smooth_values();

        from_smoothing_values(m_smoothed, m_timestamps, m_filtered);
    }
    
    TEMPLATE_DEF void CLASS_DECL::compute_weights()
    {
        m_forward_weights.clear();
        m_backward_weights.clear();
        assert(m_forward_filter.m_valid.size() == m_backward_filter.m_valid.size());
        for (int i = 0; i < m_forward_filter.m_valid.size(); ++i)
        {
            float w0 = m_forward_filter.m_valid[i] ? 1 : 0;
            float w1 = m_backward_filter.m_valid[reverse_idx(i)] ? 1 : 0;
            if (abs(w0+w1) < 1e-9) 
            {
                w0 = 0;
                w1 = 1;
            }
            m_forward_weights.push_back(w0);
            m_backward_weights.push_back(w1);
        }
    }

    TEMPLATE_DEF void CLASS_DECL::compute_smooth_values()
    {
        assert(m_forward_filter.m_valid.size() == m_backward_filter.m_valid.size());
        m_smoothed.clear();
        for (int i = 0; i < m_forward_filter.m_valid.size(); ++i)
        {
            float w0 = m_forward_weights[i];
            float w1 = m_backward_weights[i];
            float wsum = w0+w1;
            if (abs(wsum) < 1e-9) 
            {
                w0 = w1 = 0;
                wsum = 1;
            }
            
            m_smoothed.push_back(mix(
                m_forward_filtered[i],
                m_backward_filtered[reverse_idx(i)],
                w1 / wsum
            ));
        }
    }

    TEMPLATE_DEF void CLASS_DECL::compute_validity()
    {
        assert(m_forward_filter.m_valid.size() == m_backward_filter.m_valid.size());
        m_valid.clear();
        for (int i = 0; i < m_forward_filter.m_valid.size(); ++i)
        {
            m_valid.push_back(m_forward_filter.m_valid[i] || m_backward_filter.m_valid[reverse_idx(i)]);
        }
    }
    
    TEMPLATE_DEF int CLASS_DECL::reverse_idx(int idx) const
    {
        return m_forward_filter.m_valid.size() - 1 - idx;
    }

    TEMPLATE_DEF void CLASS_DECL::to_smoothing_values(const std::vector<StampedTransform>& transforms, std::vector<smoothing_value_type>& values)
    {
        values.clear();
        for (int i = 0; i < transforms.size(); ++i)
        {
            values.push_back(to_smoothing_value(transforms[i]));
        }
    }

    TEMPLATE_DEF void CLASS_DECL::from_smoothing_values(const std::vector<smoothing_value_type>& smooth, const std::vector<double>& timestamps, std::vector<StampedTransform>& transforms)
    {
        transforms.clear();
        assert(smooth.size() == timestamps.size());
        for (int i = 0; i < smooth.size(); ++i)
        {
            transforms.push_back(from_smoothing_value(smooth[i], timestamps[i]));
        }
    }

    #undef TEMPLATE_DEF
    #undef CLASS_DECL    

} // namespace transform_filter_glm
