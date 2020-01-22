// Copyright (C) 2019-2020 star.engine at outlook dot com
//
// This file is part of StarEngine
//
// StarEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// StarEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with StarEngine.  If not, see <https://www.gnu.org/licenses/>.

#pragma once
#include <Star/Graphics/SConfig.h>
#include <Star/Graphics/SContentTypes.h>

namespace Star::Graphics::Render {

class STAR_GRAPHICS_API Camera : public CameraData {
public:
    Camera();
    Camera(Camera&&);
    Camera& operator=(Camera&&);
    ~Camera();

    // Localization: X-Right, Y-Forward, Z-Up
    // Chirality: Right-handed
    void lookTo(gsl::span<const float, 3> eye, gsl::span<const float, 3> dir, gsl::span<const float, 3> up);
    void lookAt(gsl::span<const float, 3> eye, gsl::span<const float, 3> at, gsl::span<const float, 3> up);
    void lookTo(const Vector3f& eye, const Vector3f& dir, const Vector3f& up);
    void lookAt(const Vector3f& eye, const Vector3f& at, const Vector3f& up);

    void perspective(float fovRadY, float aspectWByH, float nearPlane, float farPlane);
};

}
