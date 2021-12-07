#pragma once

#include <vector>
#include "transform_filter_glm/filter.h"

namespace transform_filter_glm {

    /**
     * @brief       smoother, simple forward backward
     *
     * @tparam     SmoothingValueType   { description }
     * @tparam     TransformFilterType  { description }
     */
    template<
        class SmoothingValueType,
        class TransformFilterType
    >
    struct SmootherSfb : public Filter
    {
        using transform_filter_type = TransformFilterType;
        using smoothing_value_type = SmoothingValueType;

        using Params = typename transform_filter_type::Params;

        Params params;
        virtual void parameterUpdate();
        

        virtual ~SmootherSfb();

        std::vector<StampedTransform> m_reversed_observations;
        std::vector<double> m_reversed_timestamps;

        TransformFilterType m_forward_filter;
        TransformFilterType m_backward_filter;

        std::vector<smoothing_value_type> m_forward_filtered;
        std::vector<smoothing_value_type> m_backward_filtered;

        std::vector<float> m_forward_weights;
        std::vector<float> m_backward_weights;

        std::vector<smoothing_value_type> m_smoothed;


        protected:
        virtual void filter_implementation() override;

        virtual void compute_weights();
        virtual void compute_smooth_values();
        virtual void compute_validity();

        inline int reverse_idx(int idx) const;

        void to_smoothing_values(const std::vector<StampedTransform>& transforms, std::vector<smoothing_value_type>& values);
        void from_smoothing_values(const std::vector<smoothing_value_type>& smooth, const std::vector<double>& timestamps, std::vector<StampedTransform>& transforms);

        virtual smoothing_value_type to_smoothing_value(StampedTransform) = 0;
        virtual StampedTransform from_smoothing_value(smoothing_value_type, double timestamp) = 0;
        virtual smoothing_value_type mix(smoothing_value_type a, smoothing_value_type b, float k) = 0;

    };

} // namespace transform_filter_glm

#include "transform_filter_glm/smoother_sfb.impl.h"
