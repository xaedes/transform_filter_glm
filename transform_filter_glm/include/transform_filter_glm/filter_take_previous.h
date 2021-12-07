#pragma once

#include <vector>
#include "transform_filter_glm/filter.h"

namespace transform_filter_glm {

    struct FilterTakePrevious : public Filter
    {
        struct Params
        {};

        Params params;
        virtual void parameterUpdate();

        virtual ~FilterTakePrevious();

    protected:
        virtual void filter_implementation() override;
    };

} // namespace transform_filter_glm
