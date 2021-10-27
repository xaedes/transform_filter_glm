#pragma once

#include <glm/glm.hpp>

namespace transform_filter_glm {

    struct StampedTransform
    {
        double timestamp;
        glm::mat4 transform;
    };

} // namespace transform_filter_glm
