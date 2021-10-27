#pragma once

#include <vector>
#include "transform_filter_glm/abstract_transform_filter.h"

namespace transform_filter_glm {

    struct AbstractTransformFilterObservePredict : public AbstractTransformFilter
    {
        struct Params
        {
            bool reversed = false;
            double time_lag = 0.0;
        };

        Params params;
        virtual void parameterUpdate();
                
        virtual ~AbstractTransformFilterObservePredict();

        std::vector<double> m_timestamps_requested;

    protected:
        virtual void filter_implementation() override;
        virtual void reset_implementation() = 0;
        virtual StampedTransform observation_implementation(uint32_t observation_idx) = 0;
        virtual StampedTransform prediction_implementation(uint32_t timestamp_idx) = 0;
    };

} // namespace transform_filter_glm
