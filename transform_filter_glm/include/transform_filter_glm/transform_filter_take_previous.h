#pragma once

#include <vector>
#include "transform_filter_glm/abstract_transform_filter.h"

namespace transform_filter_glm {

    struct TransformFilterTakePrevious : public AbstractTransformFilter
    {
        struct Params
        {};

        Params params;
        virtual void parameterUpdate();

        virtual ~TransformFilterTakePrevious();

    protected:
        virtual void filter_implementation() override;
    };

} // namespace transform_filter_glm
