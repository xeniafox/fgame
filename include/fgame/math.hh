#pragma once

#include <mathfu/vector.h>

namespace fgame {
namespace math {

template <class T, std::size_t n> using cpu_vec = mathfu::Vector<T, n>;

using cpu_vec2 = mathfu::Vector<float, 2>;
using cpu_vec3 = mathfu::Vector<float, 3>;

} // namespace math
} // namespace fgame
