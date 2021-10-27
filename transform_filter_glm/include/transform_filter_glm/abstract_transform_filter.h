#pragma once

#include <vector>
#include "transform_filter_glm/stamped_transform.h"

namespace transform_filter_glm {

    struct AbstractTransformFilter
    {
        struct Params
        {};

        Params params;
        virtual void parameterUpdate();

        const std::vector<StampedTransform>& filter(
            const std::vector<StampedTransform>& observations, 
            const std::vector<double>& timestamps
        );

        virtual ~AbstractTransformFilter();

    public:


    // protected:
        std::vector<StampedTransform> m_observations;
        std::vector<double> m_timestamps;
        std::vector<StampedTransform> m_filtered;
        std::vector<bool> m_valid;
        // std::vector<StampedTransform> m_filtered;


    protected:
        virtual void filter_implementation() = 0;
    };

} // namespace transform_filter_glm
