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

#include "SCamera.h"
#include <unsupported/Eigen/AlignedVector3>

namespace Star::Graphics::Render {

Camera::Camera() = default;
Camera::Camera(Camera&&) = default;
Camera& Camera::operator=(Camera&&) = default;
Camera::~Camera() = default;

void Camera::lookTo(gsl::span<const float, 3> eye,
    gsl::span<const float, 3> dir0, gsl::span<const float, 3> up0
) {
    AlignedVector3f dir(dir0[0], dir0[1], dir0[2]);
    AlignedVector3f up(up0[0], up0[1], up0[2]);

    Expects(dir.squaredNorm() > 0.0f);
    Expects(up.squaredNorm() > 0.0f);

    // camera to world
    // c is camera center, R is cam->world rotation
    // columns of R are x-y-z axes
    //  |R c|
    //  |0 1|

    // world to camera
    // |inv(R) -inv(R)*c| = |R^t R^t*(-c)| = |R^t t|
    // |     0         1|   |  0        1|   |  0 1|

    // X-right, Y-forward, Z-up
    AlignedVector3f R1 = dir.normalized();
    AlignedVector3f R0 = R1.cross(up).normalized();
    AlignedVector3f R2 = R0.cross(R1);
    AlignedVector3f negEye(-eye[0], -eye[1], -eye[2]);

    float t0 = R0.dot(negEye);
    float t1 = R1.dot(negEye);
    float t2 = R2.dot(negEye);

    mRight = R0;
    mForward = R1;
    mUp = R2;

    visit(overload(
        [&](std::monostate) {
            // |1 0 0|
            // |0 1 0| * worldToCam
            // |0 0 1|
            mView.row(0) << R0.transpose(), t0;
            mView.row(1) << R1.transpose(), t1;
            mView.row(2) << R2.transpose(), t2;
        },
        [&](Direct3D_) {
            // |1 0 0|
            // |0 0 1| * worldToCam
            // |0 1 0|
            mView.row(0) << R0.transpose(), t0;
            mView.row(1) << R2.transpose(), t2;
            mView.row(2) << R1.transpose(), t1;
        },
        [&](Vulkan_) {
            // |1 0  0|
            // |0 0 -1| * worldToCam
            // |0 1  0|
            mView.row(0) << R0.transpose(), t0;
            mView.row(1) << -R2.transpose(), -t2;
            mView.row(2) << R1.transpose(), t1;
        },
        [&](OpenGL_) {
            // |1  0 0|
            // |0  0 1| * worldToCam
            // |0 -1 0|
            mView.row(0) << R0.transpose(), t0;
            mView.row(1) << R2.transpose(), t2;
            mView.row(2) << -R1.transpose(), -t1;
        }
    ), mViewSpace);

    Ensures(mView(3, 0) == 0.0f);
    Ensures(mView(3, 1) == 0.0f);
    Ensures(mView(3, 2) == 0.0f);
    Ensures(mView(3, 3) == 1.0f);
}

void Camera::lookAt(gsl::span<const float, 3> eye, gsl::span<const float, 3> at, gsl::span<const float, 3> up) {
    Vector3f dir(at[0] - eye[0], at[1] - eye[1], at[2] - eye[2]);
    lookTo(eye, gsl::span<const float, 3>{ dir.data(), 3 }, up);
}

void Camera::lookTo(const Vector3f& eye, const Vector3f& dir, const Vector3f& up) {
    lookTo(gsl::span<const float, 3>(eye.data(), 3),
        gsl::span<const float, 3>(dir.data(), 3),
        gsl::span<const float, 3>(up.data(), 3));
}

void Camera::lookAt(const Vector3f& eye, const Vector3f& at, const Vector3f& up) {
    lookAt(gsl::span<const float, 3>(eye.data(), 3),
        gsl::span<const float, 3>(at.data(), 3),
        gsl::span<const float, 3>(up.data(), 3));
}

void Camera::perspective(float fovRadY, float aspectWByH, float nearPlane, float farPlane) {
    // https://docs.microsoft.com/en-us/windows/win32/direct3d9/projection-transform
    // Notice: d3d9 matrix is row-major storage, row-vector
    // all matrix is transposed in the webpage

    Expects(fovRadY > 0.0f && fovRadY < S_PI);
    Expects(farPlane > nearPlane);
    Expects(nearPlane > 0.0f);

    visit(overload(
        [&](Direct3D_) {
            float h = 1 / tan(0.5f * fovRadY);
            float w = h / aspectWByH;
            float fRange = farPlane / (farPlane - nearPlane);

            mProj(0, 0) = w;
            mProj(1, 1) = h;
            mProj(2, 2) = fRange;
            mProj(2, 3) = -fRange * nearPlane;
            mProj(3, 2) = 1.0f;
        },
        [&](Vulkan_) {
            throw std::runtime_error("vulkan ndc not supported yet");
        }
    ), mNDC);

    Expects(mProj(1, 0) == 0.f);
    Expects(mProj(2, 0) == 0.f);
    Expects(mProj(3, 0) == 0.f);
    Expects(mProj(0, 1) == 0.f);
    Expects(mProj(2, 1) == 0.f);
    Expects(mProj(3, 1) == 0.f);
    Expects(mProj(0, 2) == 0.f);
    Expects(mProj(1, 2) == 0.f);
    Expects(mProj(0, 3) == 0.f);
    Expects(mProj(1, 3) == 0.f);
    Expects(mProj(3, 3) == 0.f);

    visit(overload(
        [&](std::monostate, Direct3D_) {
            // swap yz
            //     |1 0 0|
            // P * |0 0 1| * Z-up
            //     |0 1 0|
            Eigen::PermutationMatrix<4> permuation;
            permuation.setIdentity();
            permuation.applyTranspositionOnTheRight(1, 2);
            permuation.applyThisOnTheRight(mProj);
        },
        [&](std::monostate, Vulkan_) {
            // 1. swap yz
            // 2. negate y
            //     |1  0 0|   |1 0 0|
            // P * |0 -1 0| * |0 0 1| * Z-up
            //     |0  0 1|   |0 1 0|
            // equal
            // 1. negate P.col(1)
            // 2. transposition
            mProj.col(1) = -mProj.col(1);

            Eigen::PermutationMatrix<4> permuation;
            permuation.setIdentity();
            permuation.applyTranspositionOnTheRight(1, 2);
            permuation.applyThisOnTheRight(mProj);
        },
        [&](Direct3D_, Direct3D_) {
            // do nothing
        },
        [&](Direct3D_, Vulkan_) {
            // negate y
            // equal
            // negate P.col(1)
            mProj.col(1) = -mProj.col(1);
        },
        [&](Vulkan_, Direct3D_) {
            // negate y
            // equal
            // negate P.col(1)
            mProj.col(1) = -mProj.col(1);
        },
        [&](Vulkan_, Vulkan_) {
            // do nothing
        },
        [&](OpenGL_, Direct3D_) {
            // negate z
            // equal
            // negate P.col(2)
            //     |1 0  0|
            // P * |0 1  0| * OpenGL
            //     |0 0 -1|
            mProj.col(2) = -mProj.col(2);
        },
        [&](OpenGL_, Vulkan_) {
            // negate y, z
            // equal
            // negate P.col(1), P.col(2)
            //     |1  0  0|
            // P * |0 -1  0| * OpenGL
            //     |0  0 -1|
            mProj.col(1) = -mProj.col(1);
            mProj.col(2) = -mProj.col(2);
        }
    ), mViewSpace, mNDC);

    mFov = fovRadY;
    mAspect = aspectWByH;
    mNearClip = nearPlane;
    mFarClip = farPlane;
}

}
