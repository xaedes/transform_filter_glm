#pragma once

#include <vector>
#include "transform_filter_glm/stamped_transform.h"

namespace transform_filter_glm {

    struct Filter
    {
        struct Params
        {};

        Params params;
        virtual void parameterUpdate();

        const std::vector<StampedTransform>& filter(
            const std::vector<StampedTransform>& observations, 
            const std::vector<double>& timestamps
        );

        virtual ~Filter();

    public:


        std::vector<StampedTransform> m_observations;
        std::vector<double> m_timestamps;
        std::vector<StampedTransform> m_filtered;
        std::vector<bool> m_valid;
        // std::vector<StampedTransform> m_filtered;


    protected:
        virtual void filter_implementation() = 0;
    };

    struct FilterObservePredict : public Filter
    {
        struct Params
        {
            bool reversed = false;
            double time_lag = 0.0;
        };

        Params params;
        virtual void parameterUpdate();
                
        virtual ~FilterObservePredict();

        std::vector<double> m_timestamps_requested;

    protected:
        virtual void filter_implementation() override;
        virtual void reset_implementation() = 0;
        virtual StampedTransform observation_implementation(uint32_t observation_idx) = 0;
        virtual StampedTransform prediction_implementation(uint32_t timestamp_idx) = 0;
    };

} // namespace transform_filter_glm
