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
#include <cstdint>
#include <Eigen/src/Core/util/Constants.h>
#include <Eigen/src/Core/util/ForwardDeclarations.h>
#include <unsupported/Eigen/AlignedVector3>

namespace std {
template <class T> class complex;
}

namespace Eigen {
struct half;
}

namespace Star {

using Eigen::half;

using Vector4d = Eigen::Matrix<double, 4, 1>;
using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector2d = Eigen::Matrix<double, 2, 1>;
using Vector1d = Eigen::Matrix<double, 1, 1>;
using VectorXd = Eigen::Matrix<double, Eigen::Dynamic, 1>;

using Vector4f = Eigen::Matrix<float, 4, 1>;
using Vector3f = Eigen::Matrix<float, 3, 1>;
using Vector2f = Eigen::Matrix<float, 2, 1>;
using Vector1f = Eigen::Matrix<float, 1, 1>;
using VectorXf = Eigen::Matrix<float, Eigen::Dynamic, 1>;

using Vector4h = Eigen::Matrix<half, 4, 1>;
using Vector3h = Eigen::Matrix<half, 3, 1>;
using Vector2h = Eigen::Matrix<half, 2, 1>;
using Vector1h = Eigen::Matrix<half, 1, 1>;
using VectorXh = Eigen::Matrix<half, Eigen::Dynamic, 1>;

using Vector4u = Eigen::Matrix<uint32_t, 4, 1>;
using Vector3u = Eigen::Matrix<uint32_t, 3, 1>;
using Vector2u = Eigen::Matrix<uint32_t, 2, 1>;
using Vector1u = Eigen::Matrix<uint32_t, 1, 1>;
using VectorXu = Eigen::Matrix<uint32_t, Eigen::Dynamic, 1>;

using Vector4i = Eigen::Matrix<int32_t, 4, 1>;
using Vector3i = Eigen::Matrix<int32_t, 3, 1>;
using Vector2i = Eigen::Matrix<int32_t, 2, 1>;
using Vector1i = Eigen::Matrix<int32_t, 1, 1>;
using VectorXi = Eigen::Matrix<int32_t, Eigen::Dynamic, 1>;

using Vector4dr = Eigen::Matrix<double, 4, 1, Eigen::RowMajor>;
using Vector3dr = Eigen::Matrix<double, 3, 1, Eigen::RowMajor>;
using Vector2dr = Eigen::Matrix<double, 2, 1, Eigen::RowMajor>;
using Vector1dr = Eigen::Matrix<double, 1, 1, Eigen::RowMajor>;
using VectorXdr = Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4fr = Eigen::Matrix<float, 4, 1, Eigen::RowMajor>;
using Vector3fr = Eigen::Matrix<float, 3, 1, Eigen::RowMajor>;
using Vector2fr = Eigen::Matrix<float, 2, 1, Eigen::RowMajor>;
using Vector1fr = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>;
using VectorXfr = Eigen::Matrix<float, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4hr = Eigen::Matrix<half, 4, 1, Eigen::RowMajor>;
using Vector3hr = Eigen::Matrix<half, 3, 1, Eigen::RowMajor>;
using Vector2hr = Eigen::Matrix<half, 2, 1, Eigen::RowMajor>;
using Vector1hr = Eigen::Matrix<half, 1, 1, Eigen::RowMajor>;
using VectorXhr = Eigen::Matrix<half, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4ur = Eigen::Matrix<uint32_t, 4, 1, Eigen::RowMajor>;
using Vector3ur = Eigen::Matrix<uint32_t, 3, 1, Eigen::RowMajor>;
using Vector2ur = Eigen::Matrix<uint32_t, 2, 1, Eigen::RowMajor>;
using Vector1ur = Eigen::Matrix<uint32_t, 1, 1, Eigen::RowMajor>;
using VectorXur = Eigen::Matrix<uint32_t, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4ir = Eigen::Matrix<int32_t, 4, 1, Eigen::RowMajor>;
using Vector3ir = Eigen::Matrix<int32_t, 3, 1, Eigen::RowMajor>;
using Vector2ir = Eigen::Matrix<int32_t, 2, 1, Eigen::RowMajor>;
using Vector1ir = Eigen::Matrix<int32_t, 1, 1, Eigen::RowMajor>;
using VectorXir = Eigen::Matrix<int32_t, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4du = Eigen::Matrix<double, 4, 1, Eigen::DontAlign>;
using Vector3du = Eigen::Matrix<double, 3, 1, Eigen::DontAlign>;
using Vector2du = Eigen::Matrix<double, 2, 1, Eigen::DontAlign>;
using Vector1du = Eigen::Matrix<double, 1, 1, Eigen::DontAlign>;
using VectorXdu = Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4fu = Eigen::Matrix<float, 4, 1, Eigen::DontAlign>;
using Vector3fu = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
using Vector2fu = Eigen::Matrix<float, 2, 1, Eigen::DontAlign>;
using Vector1fu = Eigen::Matrix<float, 1, 1, Eigen::DontAlign>;
using VectorXfu = Eigen::Matrix<float, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4hu = Eigen::Matrix<half, 4, 1, Eigen::DontAlign>;
using Vector3hu = Eigen::Matrix<half, 3, 1, Eigen::DontAlign>;
using Vector2hu = Eigen::Matrix<half, 2, 1, Eigen::DontAlign>;
using Vector1hu = Eigen::Matrix<half, 1, 1, Eigen::DontAlign>;
using VectorXhu = Eigen::Matrix<half, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4uu = Eigen::Matrix<uint32_t, 4, 1, Eigen::DontAlign>;
using Vector3uu = Eigen::Matrix<uint32_t, 3, 1, Eigen::DontAlign>;
using Vector2uu = Eigen::Matrix<uint32_t, 2, 1, Eigen::DontAlign>;
using Vector1uu = Eigen::Matrix<uint32_t, 1, 1, Eigen::DontAlign>;
using VectorXuu = Eigen::Matrix<uint32_t, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4iu = Eigen::Matrix<int32_t, 4, 1, Eigen::DontAlign>;
using Vector3iu = Eigen::Matrix<int32_t, 3, 1, Eigen::DontAlign>;
using Vector2iu = Eigen::Matrix<int32_t, 2, 1, Eigen::DontAlign>;
using Vector1iu = Eigen::Matrix<int32_t, 1, 1, Eigen::DontAlign>;
using VectorXiu = Eigen::Matrix<int32_t, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4dru = Eigen::Matrix<double, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3dru = Eigen::Matrix<double, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2dru = Eigen::Matrix<double, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1dru = Eigen::Matrix<double, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXdru = Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4fru = Eigen::Matrix<float, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3fru = Eigen::Matrix<float, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2fru = Eigen::Matrix<float, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1fru = Eigen::Matrix<float, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXfru = Eigen::Matrix<float, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4hru = Eigen::Matrix<half, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3hru = Eigen::Matrix<half, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2hru = Eigen::Matrix<half, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1hru = Eigen::Matrix<half, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXhru = Eigen::Matrix<half, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4uru = Eigen::Matrix<uint32_t, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3uru = Eigen::Matrix<uint32_t, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2uru = Eigen::Matrix<uint32_t, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1uru = Eigen::Matrix<uint32_t, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXuru = Eigen::Matrix<uint32_t, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4iru = Eigen::Matrix<int32_t, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3iru = Eigen::Matrix<int32_t, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2iru = Eigen::Matrix<int32_t, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1iru = Eigen::Matrix<int32_t, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXiru = Eigen::Matrix<int32_t, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4cd = Eigen::Matrix<std::complex<double>, 4, 1>;
using Vector3cd = Eigen::Matrix<std::complex<double>, 3, 1>;
using Vector2cd = Eigen::Matrix<std::complex<double>, 2, 1>;
using Vector1cd = Eigen::Matrix<std::complex<double>, 1, 1>;
using VectorXcd = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>;

using Vector4cf = Eigen::Matrix<std::complex<float>, 4, 1>;
using Vector3cf = Eigen::Matrix<std::complex<float>, 3, 1>;
using Vector2cf = Eigen::Matrix<std::complex<float>, 2, 1>;
using Vector1cf = Eigen::Matrix<std::complex<float>, 1, 1>;
using VectorXcf = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, 1>;

using Vector4ch = Eigen::Matrix<std::complex<half>, 4, 1>;
using Vector3ch = Eigen::Matrix<std::complex<half>, 3, 1>;
using Vector2ch = Eigen::Matrix<std::complex<half>, 2, 1>;
using Vector1ch = Eigen::Matrix<std::complex<half>, 1, 1>;
using VectorXch = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, 1>;

using Vector4cu = Eigen::Matrix<std::complex<uint32_t>, 4, 1>;
using Vector3cu = Eigen::Matrix<std::complex<uint32_t>, 3, 1>;
using Vector2cu = Eigen::Matrix<std::complex<uint32_t>, 2, 1>;
using Vector1cu = Eigen::Matrix<std::complex<uint32_t>, 1, 1>;
using VectorXcu = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, 1>;

using Vector4ci = Eigen::Matrix<std::complex<int32_t>, 4, 1>;
using Vector3ci = Eigen::Matrix<std::complex<int32_t>, 3, 1>;
using Vector2ci = Eigen::Matrix<std::complex<int32_t>, 2, 1>;
using Vector1ci = Eigen::Matrix<std::complex<int32_t>, 1, 1>;
using VectorXci = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, 1>;

using Vector4cdr = Eigen::Matrix<std::complex<double>, 4, 1, Eigen::RowMajor>;
using Vector3cdr = Eigen::Matrix<std::complex<double>, 3, 1, Eigen::RowMajor>;
using Vector2cdr = Eigen::Matrix<std::complex<double>, 2, 1, Eigen::RowMajor>;
using Vector1cdr = Eigen::Matrix<std::complex<double>, 1, 1, Eigen::RowMajor>;
using VectorXcdr = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4cfr = Eigen::Matrix<std::complex<float>, 4, 1, Eigen::RowMajor>;
using Vector3cfr = Eigen::Matrix<std::complex<float>, 3, 1, Eigen::RowMajor>;
using Vector2cfr = Eigen::Matrix<std::complex<float>, 2, 1, Eigen::RowMajor>;
using Vector1cfr = Eigen::Matrix<std::complex<float>, 1, 1, Eigen::RowMajor>;
using VectorXcfr = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4chr = Eigen::Matrix<std::complex<half>, 4, 1, Eigen::RowMajor>;
using Vector3chr = Eigen::Matrix<std::complex<half>, 3, 1, Eigen::RowMajor>;
using Vector2chr = Eigen::Matrix<std::complex<half>, 2, 1, Eigen::RowMajor>;
using Vector1chr = Eigen::Matrix<std::complex<half>, 1, 1, Eigen::RowMajor>;
using VectorXchr = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4cur = Eigen::Matrix<std::complex<uint32_t>, 4, 1, Eigen::RowMajor>;
using Vector3cur = Eigen::Matrix<std::complex<uint32_t>, 3, 1, Eigen::RowMajor>;
using Vector2cur = Eigen::Matrix<std::complex<uint32_t>, 2, 1, Eigen::RowMajor>;
using Vector1cur = Eigen::Matrix<std::complex<uint32_t>, 1, 1, Eigen::RowMajor>;
using VectorXcur = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4cir = Eigen::Matrix<std::complex<int32_t>, 4, 1, Eigen::RowMajor>;
using Vector3cir = Eigen::Matrix<std::complex<int32_t>, 3, 1, Eigen::RowMajor>;
using Vector2cir = Eigen::Matrix<std::complex<int32_t>, 2, 1, Eigen::RowMajor>;
using Vector1cir = Eigen::Matrix<std::complex<int32_t>, 1, 1, Eigen::RowMajor>;
using VectorXcir = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, 1, Eigen::RowMajor>;

using Vector4cdu = Eigen::Matrix<std::complex<double>, 4, 1, Eigen::DontAlign>;
using Vector3cdu = Eigen::Matrix<std::complex<double>, 3, 1, Eigen::DontAlign>;
using Vector2cdu = Eigen::Matrix<std::complex<double>, 2, 1, Eigen::DontAlign>;
using Vector1cdu = Eigen::Matrix<std::complex<double>, 1, 1, Eigen::DontAlign>;
using VectorXcdu = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4cfu = Eigen::Matrix<std::complex<float>, 4, 1, Eigen::DontAlign>;
using Vector3cfu = Eigen::Matrix<std::complex<float>, 3, 1, Eigen::DontAlign>;
using Vector2cfu = Eigen::Matrix<std::complex<float>, 2, 1, Eigen::DontAlign>;
using Vector1cfu = Eigen::Matrix<std::complex<float>, 1, 1, Eigen::DontAlign>;
using VectorXcfu = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4chu = Eigen::Matrix<std::complex<half>, 4, 1, Eigen::DontAlign>;
using Vector3chu = Eigen::Matrix<std::complex<half>, 3, 1, Eigen::DontAlign>;
using Vector2chu = Eigen::Matrix<std::complex<half>, 2, 1, Eigen::DontAlign>;
using Vector1chu = Eigen::Matrix<std::complex<half>, 1, 1, Eigen::DontAlign>;
using VectorXchu = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4cuu = Eigen::Matrix<std::complex<uint32_t>, 4, 1, Eigen::DontAlign>;
using Vector3cuu = Eigen::Matrix<std::complex<uint32_t>, 3, 1, Eigen::DontAlign>;
using Vector2cuu = Eigen::Matrix<std::complex<uint32_t>, 2, 1, Eigen::DontAlign>;
using Vector1cuu = Eigen::Matrix<std::complex<uint32_t>, 1, 1, Eigen::DontAlign>;
using VectorXcuu = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4ciu = Eigen::Matrix<std::complex<int32_t>, 4, 1, Eigen::DontAlign>;
using Vector3ciu = Eigen::Matrix<std::complex<int32_t>, 3, 1, Eigen::DontAlign>;
using Vector2ciu = Eigen::Matrix<std::complex<int32_t>, 2, 1, Eigen::DontAlign>;
using Vector1ciu = Eigen::Matrix<std::complex<int32_t>, 1, 1, Eigen::DontAlign>;
using VectorXciu = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, 1, Eigen::DontAlign>;

using Vector4cdru = Eigen::Matrix<std::complex<double>, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3cdru = Eigen::Matrix<std::complex<double>, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2cdru = Eigen::Matrix<std::complex<double>, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1cdru = Eigen::Matrix<std::complex<double>, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXcdru = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4cfru = Eigen::Matrix<std::complex<float>, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3cfru = Eigen::Matrix<std::complex<float>, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2cfru = Eigen::Matrix<std::complex<float>, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1cfru = Eigen::Matrix<std::complex<float>, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXcfru = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4chru = Eigen::Matrix<std::complex<half>, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3chru = Eigen::Matrix<std::complex<half>, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2chru = Eigen::Matrix<std::complex<half>, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1chru = Eigen::Matrix<std::complex<half>, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXchru = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4curu = Eigen::Matrix<std::complex<uint32_t>, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3curu = Eigen::Matrix<std::complex<uint32_t>, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2curu = Eigen::Matrix<std::complex<uint32_t>, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1curu = Eigen::Matrix<std::complex<uint32_t>, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXcuru = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using Vector4ciru = Eigen::Matrix<std::complex<int32_t>, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector3ciru = Eigen::Matrix<std::complex<int32_t>, 3, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector2ciru = Eigen::Matrix<std::complex<int32_t>, 2, 1, Eigen::RowMajor | Eigen::DontAlign>;
using Vector1ciru = Eigen::Matrix<std::complex<int32_t>, 1, 1, Eigen::RowMajor | Eigen::DontAlign>;
using VectorXciru = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, 1, Eigen::RowMajor | Eigen::DontAlign>;

using RowVector4d = Eigen::Matrix<double, 1, 4>;
using RowVector3d = Eigen::Matrix<double, 1, 3>;
using RowVector2d = Eigen::Matrix<double, 1, 2>;
using RowVectorXd = Eigen::Matrix<double, 1, Eigen::Dynamic>;

using RowVector4f = Eigen::Matrix<float, 1, 4>;
using RowVector3f = Eigen::Matrix<float, 1, 3>;
using RowVector2f = Eigen::Matrix<float, 1, 2>;
using RowVectorXf = Eigen::Matrix<float, 1, Eigen::Dynamic>;

using RowVector4h = Eigen::Matrix<half, 1, 4>;
using RowVector3h = Eigen::Matrix<half, 1, 3>;
using RowVector2h = Eigen::Matrix<half, 1, 2>;
using RowVectorXh = Eigen::Matrix<half, 1, Eigen::Dynamic>;

using RowVector4u = Eigen::Matrix<uint32_t, 1, 4>;
using RowVector3u = Eigen::Matrix<uint32_t, 1, 3>;
using RowVector2u = Eigen::Matrix<uint32_t, 1, 2>;
using RowVectorXu = Eigen::Matrix<uint32_t, 1, Eigen::Dynamic>;

using RowVector4i = Eigen::Matrix<int32_t, 1, 4>;
using RowVector3i = Eigen::Matrix<int32_t, 1, 3>;
using RowVector2i = Eigen::Matrix<int32_t, 1, 2>;
using RowVectorXi = Eigen::Matrix<int32_t, 1, Eigen::Dynamic>;

using RowVector4du = Eigen::Matrix<double, 1, 4, Eigen::DontAlign>;
using RowVector3du = Eigen::Matrix<double, 1, 3, Eigen::DontAlign>;
using RowVector2du = Eigen::Matrix<double, 1, 2, Eigen::DontAlign>;
using RowVectorXdu = Eigen::Matrix<double, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4fu = Eigen::Matrix<float, 1, 4, Eigen::DontAlign>;
using RowVector3fu = Eigen::Matrix<float, 1, 3, Eigen::DontAlign>;
using RowVector2fu = Eigen::Matrix<float, 1, 2, Eigen::DontAlign>;
using RowVectorXfu = Eigen::Matrix<float, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4hu = Eigen::Matrix<half, 1, 4, Eigen::DontAlign>;
using RowVector3hu = Eigen::Matrix<half, 1, 3, Eigen::DontAlign>;
using RowVector2hu = Eigen::Matrix<half, 1, 2, Eigen::DontAlign>;
using RowVectorXhu = Eigen::Matrix<half, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4uu = Eigen::Matrix<uint32_t, 1, 4, Eigen::DontAlign>;
using RowVector3uu = Eigen::Matrix<uint32_t, 1, 3, Eigen::DontAlign>;
using RowVector2uu = Eigen::Matrix<uint32_t, 1, 2, Eigen::DontAlign>;
using RowVectorXuu = Eigen::Matrix<uint32_t, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4iu = Eigen::Matrix<int32_t, 1, 4, Eigen::DontAlign>;
using RowVector3iu = Eigen::Matrix<int32_t, 1, 3, Eigen::DontAlign>;
using RowVector2iu = Eigen::Matrix<int32_t, 1, 2, Eigen::DontAlign>;
using RowVectorXiu = Eigen::Matrix<int32_t, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4cd = Eigen::Matrix<std::complex<double>, 1, 4>;
using RowVector3cd = Eigen::Matrix<std::complex<double>, 1, 3>;
using RowVector2cd = Eigen::Matrix<std::complex<double>, 1, 2>;
using RowVectorXcd = Eigen::Matrix<std::complex<double>, 1, Eigen::Dynamic>;

using RowVector4cf = Eigen::Matrix<std::complex<float>, 1, 4>;
using RowVector3cf = Eigen::Matrix<std::complex<float>, 1, 3>;
using RowVector2cf = Eigen::Matrix<std::complex<float>, 1, 2>;
using RowVectorXcf = Eigen::Matrix<std::complex<float>, 1, Eigen::Dynamic>;

using RowVector4ch = Eigen::Matrix<std::complex<half>, 1, 4>;
using RowVector3ch = Eigen::Matrix<std::complex<half>, 1, 3>;
using RowVector2ch = Eigen::Matrix<std::complex<half>, 1, 2>;
using RowVectorXch = Eigen::Matrix<std::complex<half>, 1, Eigen::Dynamic>;

using RowVector4cu = Eigen::Matrix<std::complex<uint32_t>, 1, 4>;
using RowVector3cu = Eigen::Matrix<std::complex<uint32_t>, 1, 3>;
using RowVector2cu = Eigen::Matrix<std::complex<uint32_t>, 1, 2>;
using RowVectorXcu = Eigen::Matrix<std::complex<uint32_t>, 1, Eigen::Dynamic>;

using RowVector4ci = Eigen::Matrix<std::complex<int32_t>, 1, 4>;
using RowVector3ci = Eigen::Matrix<std::complex<int32_t>, 1, 3>;
using RowVector2ci = Eigen::Matrix<std::complex<int32_t>, 1, 2>;
using RowVectorXci = Eigen::Matrix<std::complex<int32_t>, 1, Eigen::Dynamic>;

using RowVector4cdu = Eigen::Matrix<std::complex<double>, 1, 4, Eigen::DontAlign>;
using RowVector3cdu = Eigen::Matrix<std::complex<double>, 1, 3, Eigen::DontAlign>;
using RowVector2cdu = Eigen::Matrix<std::complex<double>, 1, 2, Eigen::DontAlign>;
using RowVectorXcdu = Eigen::Matrix<std::complex<double>, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4cfu = Eigen::Matrix<std::complex<float>, 1, 4, Eigen::DontAlign>;
using RowVector3cfu = Eigen::Matrix<std::complex<float>, 1, 3, Eigen::DontAlign>;
using RowVector2cfu = Eigen::Matrix<std::complex<float>, 1, 2, Eigen::DontAlign>;
using RowVectorXcfu = Eigen::Matrix<std::complex<float>, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4chu = Eigen::Matrix<std::complex<half>, 1, 4, Eigen::DontAlign>;
using RowVector3chu = Eigen::Matrix<std::complex<half>, 1, 3, Eigen::DontAlign>;
using RowVector2chu = Eigen::Matrix<std::complex<half>, 1, 2, Eigen::DontAlign>;
using RowVectorXchu = Eigen::Matrix<std::complex<half>, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4cuu = Eigen::Matrix<std::complex<uint32_t>, 1, 4, Eigen::DontAlign>;
using RowVector3cuu = Eigen::Matrix<std::complex<uint32_t>, 1, 3, Eigen::DontAlign>;
using RowVector2cuu = Eigen::Matrix<std::complex<uint32_t>, 1, 2, Eigen::DontAlign>;
using RowVectorXcuu = Eigen::Matrix<std::complex<uint32_t>, 1, Eigen::Dynamic, Eigen::DontAlign>;

using RowVector4ciu = Eigen::Matrix<std::complex<int32_t>, 1, 4, Eigen::DontAlign>;
using RowVector3ciu = Eigen::Matrix<std::complex<int32_t>, 1, 3, Eigen::DontAlign>;
using RowVector2ciu = Eigen::Matrix<std::complex<int32_t>, 1, 2, Eigen::DontAlign>;
using RowVectorXciu = Eigen::Matrix<std::complex<int32_t>, 1, Eigen::Dynamic, Eigen::DontAlign>;

using Matrix4d = Eigen::Matrix<double, 4, 4>;
using Matrix3d = Eigen::Matrix<double, 3, 3>;
using Matrix2d = Eigen::Matrix<double, 2, 2>;
using MatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4d = Eigen::Matrix<double, 3, 4>;

using Matrix4f = Eigen::Matrix<float, 4, 4>;
using Matrix3f = Eigen::Matrix<float, 3, 3>;
using Matrix2f = Eigen::Matrix<float, 2, 2>;
using MatrixXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4f = Eigen::Matrix<float, 3, 4>;

using Matrix4h = Eigen::Matrix<half, 4, 4>;
using Matrix3h = Eigen::Matrix<half, 3, 3>;
using Matrix2h = Eigen::Matrix<half, 2, 2>;
using MatrixXh = Eigen::Matrix<half, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4h = Eigen::Matrix<half, 3, 4>;

using Matrix4u = Eigen::Matrix<uint32_t, 4, 4>;
using Matrix3u = Eigen::Matrix<uint32_t, 3, 3>;
using Matrix2u = Eigen::Matrix<uint32_t, 2, 2>;
using MatrixXu = Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4u = Eigen::Matrix<uint32_t, 3, 4>;

using Matrix4i = Eigen::Matrix<int32_t, 4, 4>;
using Matrix3i = Eigen::Matrix<int32_t, 3, 3>;
using Matrix2i = Eigen::Matrix<int32_t, 2, 2>;
using MatrixXi = Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4i = Eigen::Matrix<int32_t, 3, 4>;

using Matrix4dr = Eigen::Matrix<double, 4, 4, Eigen::RowMajor>;
using Matrix3dr = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>;
using Matrix2dr = Eigen::Matrix<double, 2, 2, Eigen::RowMajor>;
using MatrixXdr = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4dr = Eigen::Matrix<double, 3, 4, Eigen::RowMajor>;

using Matrix4fr = Eigen::Matrix<float, 4, 4, Eigen::RowMajor>;
using Matrix3fr = Eigen::Matrix<float, 3, 3, Eigen::RowMajor>;
using Matrix2fr = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>;
using MatrixXfr = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4fr = Eigen::Matrix<float, 3, 4, Eigen::RowMajor>;

using Matrix4hr = Eigen::Matrix<half, 4, 4, Eigen::RowMajor>;
using Matrix3hr = Eigen::Matrix<half, 3, 3, Eigen::RowMajor>;
using Matrix2hr = Eigen::Matrix<half, 2, 2, Eigen::RowMajor>;
using MatrixXhr = Eigen::Matrix<half, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4hr = Eigen::Matrix<half, 3, 4, Eigen::RowMajor>;

using Matrix4ur = Eigen::Matrix<uint32_t, 4, 4, Eigen::RowMajor>;
using Matrix3ur = Eigen::Matrix<uint32_t, 3, 3, Eigen::RowMajor>;
using Matrix2ur = Eigen::Matrix<uint32_t, 2, 2, Eigen::RowMajor>;
using MatrixXur = Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4ur = Eigen::Matrix<uint32_t, 3, 4, Eigen::RowMajor>;

using Matrix4ir = Eigen::Matrix<int32_t, 4, 4, Eigen::RowMajor>;
using Matrix3ir = Eigen::Matrix<int32_t, 3, 3, Eigen::RowMajor>;
using Matrix2ir = Eigen::Matrix<int32_t, 2, 2, Eigen::RowMajor>;
using MatrixXir = Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4ir = Eigen::Matrix<int32_t, 3, 4, Eigen::RowMajor>;

using Matrix4du = Eigen::Matrix<double, 4, 4, Eigen::DontAlign>;
using Matrix3du = Eigen::Matrix<double, 3, 3, Eigen::DontAlign>;
using Matrix2du = Eigen::Matrix<double, 2, 2, Eigen::DontAlign>;
using MatrixXdu = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4du = Eigen::Matrix<double, 3, 4, Eigen::DontAlign>;

using Matrix4fu = Eigen::Matrix<float, 4, 4, Eigen::DontAlign>;
using Matrix3fu = Eigen::Matrix<float, 3, 3, Eigen::DontAlign>;
using Matrix2fu = Eigen::Matrix<float, 2, 2, Eigen::DontAlign>;
using MatrixXfu = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4fu = Eigen::Matrix<float, 3, 4, Eigen::DontAlign>;

using Matrix4hu = Eigen::Matrix<half, 4, 4, Eigen::DontAlign>;
using Matrix3hu = Eigen::Matrix<half, 3, 3, Eigen::DontAlign>;
using Matrix2hu = Eigen::Matrix<half, 2, 2, Eigen::DontAlign>;
using MatrixXhu = Eigen::Matrix<half, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4hu = Eigen::Matrix<half, 3, 4, Eigen::DontAlign>;

using Matrix4uu = Eigen::Matrix<uint32_t, 4, 4, Eigen::DontAlign>;
using Matrix3uu = Eigen::Matrix<uint32_t, 3, 3, Eigen::DontAlign>;
using Matrix2uu = Eigen::Matrix<uint32_t, 2, 2, Eigen::DontAlign>;
using MatrixXuu = Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4uu = Eigen::Matrix<uint32_t, 3, 4, Eigen::DontAlign>;

using Matrix4iu = Eigen::Matrix<int32_t, 4, 4, Eigen::DontAlign>;
using Matrix3iu = Eigen::Matrix<int32_t, 3, 3, Eigen::DontAlign>;
using Matrix2iu = Eigen::Matrix<int32_t, 2, 2, Eigen::DontAlign>;
using MatrixXiu = Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4iu = Eigen::Matrix<int32_t, 3, 4, Eigen::DontAlign>;

using Matrix4dru = Eigen::Matrix<double, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3dru = Eigen::Matrix<double, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2dru = Eigen::Matrix<double, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXdru = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4dru = Eigen::Matrix<double, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4fru = Eigen::Matrix<float, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3fru = Eigen::Matrix<float, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2fru = Eigen::Matrix<float, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXfru = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4fru = Eigen::Matrix<float, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4hru = Eigen::Matrix<half, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3hru = Eigen::Matrix<half, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2hru = Eigen::Matrix<half, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXhru = Eigen::Matrix<half, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4hru = Eigen::Matrix<half, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4uru = Eigen::Matrix<uint32_t, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3uru = Eigen::Matrix<uint32_t, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2uru = Eigen::Matrix<uint32_t, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXuru = Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4uru = Eigen::Matrix<uint32_t, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4iru = Eigen::Matrix<int32_t, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3iru = Eigen::Matrix<int32_t, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2iru = Eigen::Matrix<int32_t, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXiru = Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4iru = Eigen::Matrix<int32_t, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4cd = Eigen::Matrix<std::complex<double>, 4, 4>;
using Matrix3cd = Eigen::Matrix<std::complex<double>, 3, 3>;
using Matrix2cd = Eigen::Matrix<std::complex<double>, 2, 2>;
using MatrixXcd = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4cd = Eigen::Matrix<std::complex<double>, 3, 4>;

using Matrix4cf = Eigen::Matrix<std::complex<float>, 4, 4>;
using Matrix3cf = Eigen::Matrix<std::complex<float>, 3, 3>;
using Matrix2cf = Eigen::Matrix<std::complex<float>, 2, 2>;
using MatrixXcf = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4cf = Eigen::Matrix<std::complex<float>, 3, 4>;

using Matrix4ch = Eigen::Matrix<std::complex<half>, 4, 4>;
using Matrix3ch = Eigen::Matrix<std::complex<half>, 3, 3>;
using Matrix2ch = Eigen::Matrix<std::complex<half>, 2, 2>;
using MatrixXch = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4ch = Eigen::Matrix<std::complex<half>, 3, 4>;

using Matrix4cu = Eigen::Matrix<std::complex<uint32_t>, 4, 4>;
using Matrix3cu = Eigen::Matrix<std::complex<uint32_t>, 3, 3>;
using Matrix2cu = Eigen::Matrix<std::complex<uint32_t>, 2, 2>;
using MatrixXcu = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4cu = Eigen::Matrix<std::complex<uint32_t>, 3, 4>;

using Matrix4ci = Eigen::Matrix<std::complex<int32_t>, 4, 4>;
using Matrix3ci = Eigen::Matrix<std::complex<int32_t>, 3, 3>;
using Matrix2ci = Eigen::Matrix<std::complex<int32_t>, 2, 2>;
using MatrixXci = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, Eigen::Dynamic>;
using Matrix3x4ci = Eigen::Matrix<std::complex<int32_t>, 3, 4>;

using Matrix4cdr = Eigen::Matrix<std::complex<double>, 4, 4, Eigen::RowMajor>;
using Matrix3cdr = Eigen::Matrix<std::complex<double>, 3, 3, Eigen::RowMajor>;
using Matrix2cdr = Eigen::Matrix<std::complex<double>, 2, 2, Eigen::RowMajor>;
using MatrixXcdr = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4cdr = Eigen::Matrix<std::complex<double>, 3, 4, Eigen::RowMajor>;

using Matrix4cfr = Eigen::Matrix<std::complex<float>, 4, 4, Eigen::RowMajor>;
using Matrix3cfr = Eigen::Matrix<std::complex<float>, 3, 3, Eigen::RowMajor>;
using Matrix2cfr = Eigen::Matrix<std::complex<float>, 2, 2, Eigen::RowMajor>;
using MatrixXcfr = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4cfr = Eigen::Matrix<std::complex<float>, 3, 4, Eigen::RowMajor>;

using Matrix4chr = Eigen::Matrix<std::complex<half>, 4, 4, Eigen::RowMajor>;
using Matrix3chr = Eigen::Matrix<std::complex<half>, 3, 3, Eigen::RowMajor>;
using Matrix2chr = Eigen::Matrix<std::complex<half>, 2, 2, Eigen::RowMajor>;
using MatrixXchr = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4chr = Eigen::Matrix<std::complex<half>, 3, 4, Eigen::RowMajor>;

using Matrix4cur = Eigen::Matrix<std::complex<uint32_t>, 4, 4, Eigen::RowMajor>;
using Matrix3cur = Eigen::Matrix<std::complex<uint32_t>, 3, 3, Eigen::RowMajor>;
using Matrix2cur = Eigen::Matrix<std::complex<uint32_t>, 2, 2, Eigen::RowMajor>;
using MatrixXcur = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4cur = Eigen::Matrix<std::complex<uint32_t>, 3, 4, Eigen::RowMajor>;

using Matrix4cir = Eigen::Matrix<std::complex<int32_t>, 4, 4, Eigen::RowMajor>;
using Matrix3cir = Eigen::Matrix<std::complex<int32_t>, 3, 3, Eigen::RowMajor>;
using Matrix2cir = Eigen::Matrix<std::complex<int32_t>, 2, 2, Eigen::RowMajor>;
using MatrixXcir = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using Matrix3x4cir = Eigen::Matrix<std::complex<int32_t>, 3, 4, Eigen::RowMajor>;

using Matrix4cdu = Eigen::Matrix<std::complex<double>, 4, 4, Eigen::DontAlign>;
using Matrix3cdu = Eigen::Matrix<std::complex<double>, 3, 3, Eigen::DontAlign>;
using Matrix2cdu = Eigen::Matrix<std::complex<double>, 2, 2, Eigen::DontAlign>;
using MatrixXcdu = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4cdu = Eigen::Matrix<std::complex<double>, 3, 4, Eigen::DontAlign>;

using Matrix4cfu = Eigen::Matrix<std::complex<float>, 4, 4, Eigen::DontAlign>;
using Matrix3cfu = Eigen::Matrix<std::complex<float>, 3, 3, Eigen::DontAlign>;
using Matrix2cfu = Eigen::Matrix<std::complex<float>, 2, 2, Eigen::DontAlign>;
using MatrixXcfu = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4cfu = Eigen::Matrix<std::complex<float>, 3, 4, Eigen::DontAlign>;

using Matrix4chu = Eigen::Matrix<std::complex<half>, 4, 4, Eigen::DontAlign>;
using Matrix3chu = Eigen::Matrix<std::complex<half>, 3, 3, Eigen::DontAlign>;
using Matrix2chu = Eigen::Matrix<std::complex<half>, 2, 2, Eigen::DontAlign>;
using MatrixXchu = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4chu = Eigen::Matrix<std::complex<half>, 3, 4, Eigen::DontAlign>;

using Matrix4cuu = Eigen::Matrix<std::complex<uint32_t>, 4, 4, Eigen::DontAlign>;
using Matrix3cuu = Eigen::Matrix<std::complex<uint32_t>, 3, 3, Eigen::DontAlign>;
using Matrix2cuu = Eigen::Matrix<std::complex<uint32_t>, 2, 2, Eigen::DontAlign>;
using MatrixXcuu = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4cuu = Eigen::Matrix<std::complex<uint32_t>, 3, 4, Eigen::DontAlign>;

using Matrix4ciu = Eigen::Matrix<std::complex<int32_t>, 4, 4, Eigen::DontAlign>;
using Matrix3ciu = Eigen::Matrix<std::complex<int32_t>, 3, 3, Eigen::DontAlign>;
using Matrix2ciu = Eigen::Matrix<std::complex<int32_t>, 2, 2, Eigen::DontAlign>;
using MatrixXciu = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::DontAlign>;
using Matrix3x4ciu = Eigen::Matrix<std::complex<int32_t>, 3, 4, Eigen::DontAlign>;

using Matrix4cdru = Eigen::Matrix<std::complex<double>, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3cdru = Eigen::Matrix<std::complex<double>, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2cdru = Eigen::Matrix<std::complex<double>, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXcdru = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4cdru = Eigen::Matrix<std::complex<double>, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4cfru = Eigen::Matrix<std::complex<float>, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3cfru = Eigen::Matrix<std::complex<float>, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2cfru = Eigen::Matrix<std::complex<float>, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXcfru = Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4cfru = Eigen::Matrix<std::complex<float>, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4chru = Eigen::Matrix<std::complex<half>, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3chru = Eigen::Matrix<std::complex<half>, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2chru = Eigen::Matrix<std::complex<half>, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXchru = Eigen::Matrix<std::complex<half>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4chru = Eigen::Matrix<std::complex<half>, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4curu = Eigen::Matrix<std::complex<uint32_t>, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3curu = Eigen::Matrix<std::complex<uint32_t>, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2curu = Eigen::Matrix<std::complex<uint32_t>, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXcuru = Eigen::Matrix<std::complex<uint32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4curu = Eigen::Matrix<std::complex<uint32_t>, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Matrix4ciru = Eigen::Matrix<std::complex<int32_t>, 4, 4, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3ciru = Eigen::Matrix<std::complex<int32_t>, 3, 3, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix2ciru = Eigen::Matrix<std::complex<int32_t>, 2, 2, Eigen::RowMajor | Eigen::DontAlign>;
using MatrixXciru = Eigen::Matrix<std::complex<int32_t>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::DontAlign>;
using Matrix3x4ciru = Eigen::Matrix<std::complex<int32_t>, 3, 4, Eigen::RowMajor | Eigen::DontAlign>;

using Unorm4 = Eigen::Matrix<uint8_t, 4, 1>;
using Unorm3 = Eigen::Matrix<uint8_t, 3, 1>;
using Unorm2 = Eigen::Matrix<uint8_t, 2, 1>;
using Unorm1 = Eigen::Matrix<uint8_t, 1, 1>;

using Snorm4 = Eigen::Matrix<int8_t, 4, 1>;
using Snorm3 = Eigen::Matrix<int8_t, 3, 1>;
using Snorm2 = Eigen::Matrix<int8_t, 2, 1>;
using Snorm1 = Eigen::Matrix<int8_t, 1, 1>;

using Rotation2d = Eigen::Rotation2D<double>;
using Rotation2f = Eigen::Rotation2D<float>;
using Rotation2h = Eigen::Rotation2D<half>;

using AngleAxisd = Eigen::AngleAxis<double>;
using AngleAxisf = Eigen::AngleAxis<float>;
using AngleAxish = Eigen::AngleAxis<half>;

using Translation2d = Eigen::Translation<double, 2>;
using Translation2f = Eigen::Translation<float, 2>;
using Translation2h = Eigen::Translation<half, 2>;

using Translation3d = Eigen::Translation<double, 3>;
using Translation3f = Eigen::Translation<float, 3>;
using Translation3h = Eigen::Translation<half, 3>;

using AlignedBox2d = Eigen::AlignedBox<double, 2>;
using AlignedBox2f = Eigen::AlignedBox<float, 2>;
using AlignedBox2h = Eigen::AlignedBox<half, 2>;
using AlignedBox2i = Eigen::AlignedBox<int32_t, 2>;

using AlignedBox3d = Eigen::AlignedBox<double, 3>;
using AlignedBox3f = Eigen::AlignedBox<float, 3>;
using AlignedBox3h = Eigen::AlignedBox<half, 3>;
using AlignedBox3i = Eigen::AlignedBox<int32_t, 3>;

using Quaterniond = Eigen::Quaternion<double>;
using Quaternionf = Eigen::Quaternion<float>;
using Quaternionh = Eigen::Quaternion<half>;
using Quaterniondu = Eigen::Quaternion<double, Eigen::DontAlign>;
using Quaternionfu = Eigen::Quaternion<float, Eigen::DontAlign>;
using Quaternionhu = Eigen::Quaternion<half, Eigen::DontAlign>;

using Isometry2d = Eigen::Transform<double, 2, Eigen::Isometry>;
using Isometry2f = Eigen::Transform<float, 2, Eigen::Isometry>;
using Isometry2h = Eigen::Transform<half, 2, Eigen::Isometry>;
using Isometry2du = Eigen::Transform<double, 2, Eigen::Isometry, Eigen::DontAlign>;
using Isometry2fu = Eigen::Transform<float, 2, Eigen::Isometry, Eigen::DontAlign>;
using Isometry2hu = Eigen::Transform<half, 2, Eigen::Isometry, Eigen::DontAlign>;

using Isometry3d = Eigen::Transform<double, 3, Eigen::Isometry>;
using Isometry3f = Eigen::Transform<float, 3, Eigen::Isometry>;
using Isometry3h = Eigen::Transform<half, 3, Eigen::Isometry>;
using Isometry3du = Eigen::Transform<double, 3, Eigen::Isometry, Eigen::DontAlign>;
using Isometry3fu = Eigen::Transform<float, 3, Eigen::Isometry, Eigen::DontAlign>;
using Isometry3hu = Eigen::Transform<half, 3, Eigen::Isometry, Eigen::DontAlign>;

using Affine2d = Eigen::Transform<double, 2, Eigen::Affine>;
using Affine2f = Eigen::Transform<float, 2, Eigen::Affine>;
using Affine2h = Eigen::Transform<half, 2, Eigen::Affine>;
using Affine2du = Eigen::Transform<double, 2, Eigen::Affine, Eigen::DontAlign>;
using Affine2fu = Eigen::Transform<float, 2, Eigen::Affine, Eigen::DontAlign>;
using Affine2hu = Eigen::Transform<half, 2, Eigen::Affine, Eigen::DontAlign>;

using Affine3d = Eigen::Transform<double, 3, Eigen::Affine>;
using Affine3f = Eigen::Transform<float, 3, Eigen::Affine>;
using Affine3h = Eigen::Transform<half, 3, Eigen::Affine>;
using Affine3du = Eigen::Transform<double, 3, Eigen::Affine, Eigen::DontAlign>;
using Affine3fu = Eigen::Transform<float, 3, Eigen::Affine, Eigen::DontAlign>;
using Affine3hu = Eigen::Transform<half, 3, Eigen::Affine, Eigen::DontAlign>;

using AffineCompact2d = Eigen::Transform<double, 2, Eigen::AffineCompact>;
using AffineCompact2f = Eigen::Transform<float, 2, Eigen::AffineCompact>;
using AffineCompact2h = Eigen::Transform<half, 2, Eigen::AffineCompact>;
using AffineCompact2du = Eigen::Transform<double, 2, Eigen::AffineCompact, Eigen::DontAlign>;
using AffineCompact2fu = Eigen::Transform<float, 2, Eigen::AffineCompact, Eigen::DontAlign>;
using AffineCompact2hu = Eigen::Transform<half, 2, Eigen::AffineCompact, Eigen::DontAlign>;

using AffineCompact3d = Eigen::Transform<double, 3, Eigen::AffineCompact>;
using AffineCompact3f = Eigen::Transform<float, 3, Eigen::AffineCompact>;
using AffineCompact3h = Eigen::Transform<half, 3, Eigen::AffineCompact>;
using AffineCompact3du = Eigen::Transform<double, 3, Eigen::AffineCompact, Eigen::DontAlign>;
using AffineCompact3fu = Eigen::Transform<float, 3, Eigen::AffineCompact, Eigen::DontAlign>;
using AffineCompact3hu = Eigen::Transform<half, 3, Eigen::AffineCompact, Eigen::DontAlign>;

using Projective2d = Eigen::Transform<double, 2, Eigen::Projective>;
using Projective2f = Eigen::Transform<float, 2, Eigen::Projective>;
using Projective2h = Eigen::Transform<half, 2, Eigen::Projective>;
using Projective2du = Eigen::Transform<double, 2, Eigen::Projective, Eigen::DontAlign>;
using Projective2fu = Eigen::Transform<float, 2, Eigen::Projective, Eigen::DontAlign>;
using Projective2hu = Eigen::Transform<half, 2, Eigen::Projective, Eigen::DontAlign>;

using Projective3d = Eigen::Transform<double, 3, Eigen::Projective>;
using Projective3f = Eigen::Transform<float, 3, Eigen::Projective>;
using Projective3h = Eigen::Transform<half, 3, Eigen::Projective>;
using Projective3du = Eigen::Transform<double, 3, Eigen::Projective, Eigen::DontAlign>;
using Projective3fu = Eigen::Transform<float, 3, Eigen::Projective, Eigen::DontAlign>;
using Projective3hu = Eigen::Transform<half, 3, Eigen::Projective, Eigen::DontAlign>;

using Line2d = Eigen::ParametrizedLine<double, 2>;
using Line2f = Eigen::ParametrizedLine<float, 2>;
using Line2h = Eigen::ParametrizedLine<half, 2>;
using Line2du = Eigen::ParametrizedLine<double, 2, Eigen::DontAlign>;
using Line2fu = Eigen::ParametrizedLine<float, 2, Eigen::DontAlign>;
using Line2hu = Eigen::ParametrizedLine<half, 2, Eigen::DontAlign>;

using Line3d = Eigen::ParametrizedLine<double, 3>;
using Line3f = Eigen::ParametrizedLine<float, 3>;
using Line3h = Eigen::ParametrizedLine<half, 3>;
using Line3du = Eigen::ParametrizedLine<double, 3, Eigen::DontAlign>;
using Line3fu = Eigen::ParametrizedLine<float, 3, Eigen::DontAlign>;
using Line3hu = Eigen::ParametrizedLine<half, 3, Eigen::DontAlign>;

using Plane2d = Eigen::Hyperplane<double, 2>;
using Plane2f = Eigen::Hyperplane<float, 2>;
using Plane2h = Eigen::Hyperplane<half, 2>;
using Plane2du = Eigen::Hyperplane<double, 2, Eigen::DontAlign>;
using Plane2fu = Eigen::Hyperplane<float, 2, Eigen::DontAlign>;
using Plane2hu = Eigen::Hyperplane<half, 2, Eigen::DontAlign>;

using Plane3d = Eigen::Hyperplane<double, 3>;
using Plane3f = Eigen::Hyperplane<float, 3>;
using Plane3h = Eigen::Hyperplane<half, 3>;
using Plane3du = Eigen::Hyperplane<double, 3, Eigen::DontAlign>;
using Plane3fu = Eigen::Hyperplane<float, 3, Eigen::DontAlign>;
using Plane3hu = Eigen::Hyperplane<half, 3, Eigen::DontAlign>;

using UniformScalingd = Eigen::UniformScaling<double>;
using UniformScalingf = Eigen::UniformScaling<float>;
using UniformScalingh = Eigen::UniformScaling<half>;

//---------------------------------------------
// Alias 
using double4 = Vector4d;
using double3 = Vector3d;
using double2 = Vector2d;
using double1 = Vector1d;

using float4 = Vector4f;
using float3 = Vector3f;
using float2 = Vector2f;
using float1 = Vector1f;

using half4 = Vector4h;
using half3 = Vector3h;
using half2 = Vector2h;
using half1 = Vector1h;

using uint4 = Vector4u;
using uint3 = Vector3u;
using uint2 = Vector2u;
using uint1 = Vector1u;

using int4 = Vector4i;
using int3 = Vector3i;
using int2 = Vector2i;
using int1 = Vector1i;

using fixed4 = Unorm4;
using fixed3 = Unorm3;
using fixed2 = Unorm2;
using fixed1 = Unorm1;

//---------------------------------------------
// Special types
using AlignedVector3d = Eigen::AlignedVector3<double>;
using AlignedVector3f = Eigen::AlignedVector3<float>;

using Bool = int32_t;

using matrix = Matrix4f;
using fixed = uint8_t;
using uint = uint32_t;

#define STAR_ALIGNED_OPERATOR_NEW EIGEN_MAKE_ALIGNED_OPERATOR_NEW

static const float S_PI = 3.141592654f;
static const float S_2PI = 6.283185307f;
static const float S_1DIVPI = 0.318309886f;
static const float S_1DIV2PI = 0.159154943f;
static const float S_PIDIV2 = 1.570796327f;
static const float S_PIDIV4 = 0.785398163f;

}
