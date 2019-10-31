// Copyright (C) 2019 star.engine at outlook dot com
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
#include <Star/SMathFwd.h>

namespace Eigen {

inline const char* getName(const Matrix<double, 4, 1>&) noexcept { return "Vector4d"; }
inline const char* getName(const Matrix<double, 3, 1>&) noexcept { return "Vector3d"; }
inline const char* getName(const Matrix<double, 2, 1>&) noexcept { return "Vector2d"; }
inline const char* getName(const Matrix<double, 1, 1>&) noexcept { return "Vector1d"; }
inline const char* getName(const Matrix<double, Dynamic, 1>&) noexcept { return "VectorXd"; }
inline const char* getName(const Matrix<float, 4, 1>&) noexcept { return "Vector4f"; }
inline const char* getName(const Matrix<float, 3, 1>&) noexcept { return "Vector3f"; }
inline const char* getName(const Matrix<float, 2, 1>&) noexcept { return "Vector2f"; }
inline const char* getName(const Matrix<float, 1, 1>&) noexcept { return "Vector1f"; }
inline const char* getName(const Matrix<float, Dynamic, 1>&) noexcept { return "VectorXf"; }
inline const char* getName(const Matrix<half, 4, 1>&) noexcept { return "Vector4h"; }
inline const char* getName(const Matrix<half, 3, 1>&) noexcept { return "Vector3h"; }
inline const char* getName(const Matrix<half, 2, 1>&) noexcept { return "Vector2h"; }
inline const char* getName(const Matrix<half, 1, 1>&) noexcept { return "Vector1h"; }
inline const char* getName(const Matrix<half, Dynamic, 1>&) noexcept { return "VectorXh"; }
inline const char* getName(const Matrix<uint32_t, 4, 1>&) noexcept { return "Vector4u"; }
inline const char* getName(const Matrix<uint32_t, 3, 1>&) noexcept { return "Vector3u"; }
inline const char* getName(const Matrix<uint32_t, 2, 1>&) noexcept { return "Vector2u"; }
inline const char* getName(const Matrix<uint32_t, 1, 1>&) noexcept { return "Vector1u"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, 1>&) noexcept { return "VectorXu"; }
inline const char* getName(const Matrix<int32_t, 4, 1>&) noexcept { return "Vector4i"; }
inline const char* getName(const Matrix<int32_t, 3, 1>&) noexcept { return "Vector3i"; }
inline const char* getName(const Matrix<int32_t, 2, 1>&) noexcept { return "Vector2i"; }
inline const char* getName(const Matrix<int32_t, 1, 1>&) noexcept { return "Vector1i"; }
inline const char* getName(const Matrix<int32_t, Dynamic, 1>&) noexcept { return "VectorXi"; }
inline const char* getName(const Matrix<double, 4, 1, RowMajor>&) noexcept { return "Vector4dr"; }
inline const char* getName(const Matrix<double, 3, 1, RowMajor>&) noexcept { return "Vector3dr"; }
inline const char* getName(const Matrix<double, 2, 1, RowMajor>&) noexcept { return "Vector2dr"; }
inline const char* getName(const Matrix<double, 1, 1, RowMajor>&) noexcept { return "Vector1dr"; }
inline const char* getName(const Matrix<double, Dynamic, 1, RowMajor>&) noexcept { return "VectorXdr"; }
inline const char* getName(const Matrix<float, 4, 1, RowMajor>&) noexcept { return "Vector4fr"; }
inline const char* getName(const Matrix<float, 3, 1, RowMajor>&) noexcept { return "Vector3fr"; }
inline const char* getName(const Matrix<float, 2, 1, RowMajor>&) noexcept { return "Vector2fr"; }
inline const char* getName(const Matrix<float, 1, 1, RowMajor>&) noexcept { return "Vector1fr"; }
inline const char* getName(const Matrix<float, Dynamic, 1, RowMajor>&) noexcept { return "VectorXfr"; }
inline const char* getName(const Matrix<half, 4, 1, RowMajor>&) noexcept { return "Vector4hr"; }
inline const char* getName(const Matrix<half, 3, 1, RowMajor>&) noexcept { return "Vector3hr"; }
inline const char* getName(const Matrix<half, 2, 1, RowMajor>&) noexcept { return "Vector2hr"; }
inline const char* getName(const Matrix<half, 1, 1, RowMajor>&) noexcept { return "Vector1hr"; }
inline const char* getName(const Matrix<half, Dynamic, 1, RowMajor>&) noexcept { return "VectorXhr"; }
inline const char* getName(const Matrix<uint32_t, 4, 1, RowMajor>&) noexcept { return "Vector4ur"; }
inline const char* getName(const Matrix<uint32_t, 3, 1, RowMajor>&) noexcept { return "Vector3ur"; }
inline const char* getName(const Matrix<uint32_t, 2, 1, RowMajor>&) noexcept { return "Vector2ur"; }
inline const char* getName(const Matrix<uint32_t, 1, 1, RowMajor>&) noexcept { return "Vector1ur"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, 1, RowMajor>&) noexcept { return "VectorXur"; }
inline const char* getName(const Matrix<int32_t, 4, 1, RowMajor>&) noexcept { return "Vector4ir"; }
inline const char* getName(const Matrix<int32_t, 3, 1, RowMajor>&) noexcept { return "Vector3ir"; }
inline const char* getName(const Matrix<int32_t, 2, 1, RowMajor>&) noexcept { return "Vector2ir"; }
inline const char* getName(const Matrix<int32_t, 1, 1, RowMajor>&) noexcept { return "Vector1ir"; }
inline const char* getName(const Matrix<int32_t, Dynamic, 1, RowMajor>&) noexcept { return "VectorXir"; }
inline const char* getName(const Matrix<double, 4, 1, DontAlign>&) noexcept { return "Vector4du"; }
inline const char* getName(const Matrix<double, 3, 1, DontAlign>&) noexcept { return "Vector3du"; }
inline const char* getName(const Matrix<double, 2, 1, DontAlign>&) noexcept { return "Vector2du"; }
inline const char* getName(const Matrix<double, 1, 1, DontAlign>&) noexcept { return "Vector1du"; }
inline const char* getName(const Matrix<double, Dynamic, 1, DontAlign>&) noexcept { return "VectorXdu"; }
inline const char* getName(const Matrix<float, 4, 1, DontAlign>&) noexcept { return "Vector4fu"; }
inline const char* getName(const Matrix<float, 3, 1, DontAlign>&) noexcept { return "Vector3fu"; }
inline const char* getName(const Matrix<float, 2, 1, DontAlign>&) noexcept { return "Vector2fu"; }
inline const char* getName(const Matrix<float, 1, 1, DontAlign>&) noexcept { return "Vector1fu"; }
inline const char* getName(const Matrix<float, Dynamic, 1, DontAlign>&) noexcept { return "VectorXfu"; }
inline const char* getName(const Matrix<half, 4, 1, DontAlign>&) noexcept { return "Vector4hu"; }
inline const char* getName(const Matrix<half, 3, 1, DontAlign>&) noexcept { return "Vector3hu"; }
inline const char* getName(const Matrix<half, 2, 1, DontAlign>&) noexcept { return "Vector2hu"; }
inline const char* getName(const Matrix<half, 1, 1, DontAlign>&) noexcept { return "Vector1hu"; }
inline const char* getName(const Matrix<half, Dynamic, 1, DontAlign>&) noexcept { return "VectorXhu"; }
inline const char* getName(const Matrix<uint32_t, 4, 1, DontAlign>&) noexcept { return "Vector4uu"; }
inline const char* getName(const Matrix<uint32_t, 3, 1, DontAlign>&) noexcept { return "Vector3uu"; }
inline const char* getName(const Matrix<uint32_t, 2, 1, DontAlign>&) noexcept { return "Vector2uu"; }
inline const char* getName(const Matrix<uint32_t, 1, 1, DontAlign>&) noexcept { return "Vector1uu"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, 1, DontAlign>&) noexcept { return "VectorXuu"; }
inline const char* getName(const Matrix<int32_t, 4, 1, DontAlign>&) noexcept { return "Vector4iu"; }
inline const char* getName(const Matrix<int32_t, 3, 1, DontAlign>&) noexcept { return "Vector3iu"; }
inline const char* getName(const Matrix<int32_t, 2, 1, DontAlign>&) noexcept { return "Vector2iu"; }
inline const char* getName(const Matrix<int32_t, 1, 1, DontAlign>&) noexcept { return "Vector1iu"; }
inline const char* getName(const Matrix<int32_t, Dynamic, 1, DontAlign>&) noexcept { return "VectorXiu"; }
inline const char* getName(const Matrix<double, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4dru"; }
inline const char* getName(const Matrix<double, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3dru"; }
inline const char* getName(const Matrix<double, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2dru"; }
inline const char* getName(const Matrix<double, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1dru"; }
inline const char* getName(const Matrix<double, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXdru"; }
inline const char* getName(const Matrix<float, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4fru"; }
inline const char* getName(const Matrix<float, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3fru"; }
inline const char* getName(const Matrix<float, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2fru"; }
inline const char* getName(const Matrix<float, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1fru"; }
inline const char* getName(const Matrix<float, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXfru"; }
inline const char* getName(const Matrix<half, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4hru"; }
inline const char* getName(const Matrix<half, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3hru"; }
inline const char* getName(const Matrix<half, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2hru"; }
inline const char* getName(const Matrix<half, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1hru"; }
inline const char* getName(const Matrix<half, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXhru"; }
inline const char* getName(const Matrix<uint32_t, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4uru"; }
inline const char* getName(const Matrix<uint32_t, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3uru"; }
inline const char* getName(const Matrix<uint32_t, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2uru"; }
inline const char* getName(const Matrix<uint32_t, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1uru"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXuru"; }
inline const char* getName(const Matrix<int32_t, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4iru"; }
inline const char* getName(const Matrix<int32_t, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3iru"; }
inline const char* getName(const Matrix<int32_t, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2iru"; }
inline const char* getName(const Matrix<int32_t, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1iru"; }
inline const char* getName(const Matrix<int32_t, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXiru"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 1>&) noexcept { return "Vector4cd"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 1>&) noexcept { return "Vector3cd"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 1>&) noexcept { return "Vector2cd"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 1>&) noexcept { return "Vector1cd"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, 1>&) noexcept { return "VectorXcd"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 1>&) noexcept { return "Vector4cf"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 1>&) noexcept { return "Vector3cf"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 1>&) noexcept { return "Vector2cf"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 1>&) noexcept { return "Vector1cf"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, 1>&) noexcept { return "VectorXcf"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 1>&) noexcept { return "Vector4ch"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 1>&) noexcept { return "Vector3ch"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 1>&) noexcept { return "Vector2ch"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 1>&) noexcept { return "Vector1ch"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, 1>&) noexcept { return "VectorXch"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 1>&) noexcept { return "Vector4cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 1>&) noexcept { return "Vector3cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 1>&) noexcept { return "Vector2cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 1>&) noexcept { return "Vector1cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, 1>&) noexcept { return "VectorXcu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 1>&) noexcept { return "Vector4ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 1>&) noexcept { return "Vector3ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 1>&) noexcept { return "Vector2ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 1>&) noexcept { return "Vector1ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, 1>&) noexcept { return "VectorXci"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 1, RowMajor>&) noexcept { return "Vector4cdr"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 1, RowMajor>&) noexcept { return "Vector3cdr"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 1, RowMajor>&) noexcept { return "Vector2cdr"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 1, RowMajor>&) noexcept { return "Vector1cdr"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, 1, RowMajor>&) noexcept { return "VectorXcdr"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 1, RowMajor>&) noexcept { return "Vector4cfr"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 1, RowMajor>&) noexcept { return "Vector3cfr"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 1, RowMajor>&) noexcept { return "Vector2cfr"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 1, RowMajor>&) noexcept { return "Vector1cfr"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, 1, RowMajor>&) noexcept { return "VectorXcfr"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 1, RowMajor>&) noexcept { return "Vector4chr"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 1, RowMajor>&) noexcept { return "Vector3chr"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 1, RowMajor>&) noexcept { return "Vector2chr"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 1, RowMajor>&) noexcept { return "Vector1chr"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, 1, RowMajor>&) noexcept { return "VectorXchr"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 1, RowMajor>&) noexcept { return "Vector4cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 1, RowMajor>&) noexcept { return "Vector3cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 1, RowMajor>&) noexcept { return "Vector2cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 1, RowMajor>&) noexcept { return "Vector1cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, 1, RowMajor>&) noexcept { return "VectorXcur"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 1, RowMajor>&) noexcept { return "Vector4cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 1, RowMajor>&) noexcept { return "Vector3cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 1, RowMajor>&) noexcept { return "Vector2cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 1, RowMajor>&) noexcept { return "Vector1cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, 1, RowMajor>&) noexcept { return "VectorXcir"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 1, DontAlign>&) noexcept { return "Vector4cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 1, DontAlign>&) noexcept { return "Vector3cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 1, DontAlign>&) noexcept { return "Vector2cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 1, DontAlign>&) noexcept { return "Vector1cdu"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, 1, DontAlign>&) noexcept { return "VectorXcdu"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 1, DontAlign>&) noexcept { return "Vector4cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 1, DontAlign>&) noexcept { return "Vector3cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 1, DontAlign>&) noexcept { return "Vector2cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 1, DontAlign>&) noexcept { return "Vector1cfu"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, 1, DontAlign>&) noexcept { return "VectorXcfu"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 1, DontAlign>&) noexcept { return "Vector4chu"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 1, DontAlign>&) noexcept { return "Vector3chu"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 1, DontAlign>&) noexcept { return "Vector2chu"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 1, DontAlign>&) noexcept { return "Vector1chu"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, 1, DontAlign>&) noexcept { return "VectorXchu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 1, DontAlign>&) noexcept { return "Vector4cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 1, DontAlign>&) noexcept { return "Vector3cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 1, DontAlign>&) noexcept { return "Vector2cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 1, DontAlign>&) noexcept { return "Vector1cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, 1, DontAlign>&) noexcept { return "VectorXcuu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 1, DontAlign>&) noexcept { return "Vector4ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 1, DontAlign>&) noexcept { return "Vector3ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 1, DontAlign>&) noexcept { return "Vector2ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 1, DontAlign>&) noexcept { return "Vector1ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, 1, DontAlign>&) noexcept { return "VectorXciu"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4cdru"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3cdru"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2cdru"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1cdru"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXcdru"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4cfru"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3cfru"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2cfru"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1cfru"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXcfru"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4chru"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3chru"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2chru"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1chru"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXchru"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXcuru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 1, RowMajor | DontAlign>&) noexcept { return "Vector4ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 1, RowMajor | DontAlign>&) noexcept { return "Vector3ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 1, RowMajor | DontAlign>&) noexcept { return "Vector2ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 1, RowMajor | DontAlign>&) noexcept { return "Vector1ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, 1, RowMajor | DontAlign>&) noexcept { return "VectorXciru"; }
inline const char* getName(const Matrix<double, 1, 4>&) noexcept { return "RowVector4d"; }
inline const char* getName(const Matrix<double, 1, 3>&) noexcept { return "RowVector3d"; }
inline const char* getName(const Matrix<double, 1, 2>&) noexcept { return "RowVector2d"; }
inline const char* getName(const Matrix<double, 1, Dynamic>&) noexcept { return "RowVectorXd"; }
inline const char* getName(const Matrix<float, 1, 4>&) noexcept { return "RowVector4f"; }
inline const char* getName(const Matrix<float, 1, 3>&) noexcept { return "RowVector3f"; }
inline const char* getName(const Matrix<float, 1, 2>&) noexcept { return "RowVector2f"; }
inline const char* getName(const Matrix<float, 1, Dynamic>&) noexcept { return "RowVectorXf"; }
inline const char* getName(const Matrix<half, 1, 4>&) noexcept { return "RowVector4h"; }
inline const char* getName(const Matrix<half, 1, 3>&) noexcept { return "RowVector3h"; }
inline const char* getName(const Matrix<half, 1, 2>&) noexcept { return "RowVector2h"; }
inline const char* getName(const Matrix<half, 1, Dynamic>&) noexcept { return "RowVectorXh"; }
inline const char* getName(const Matrix<uint32_t, 1, 4>&) noexcept { return "RowVector4u"; }
inline const char* getName(const Matrix<uint32_t, 1, 3>&) noexcept { return "RowVector3u"; }
inline const char* getName(const Matrix<uint32_t, 1, 2>&) noexcept { return "RowVector2u"; }
inline const char* getName(const Matrix<uint32_t, 1, Dynamic>&) noexcept { return "RowVectorXu"; }
inline const char* getName(const Matrix<int32_t, 1, 4>&) noexcept { return "RowVector4i"; }
inline const char* getName(const Matrix<int32_t, 1, 3>&) noexcept { return "RowVector3i"; }
inline const char* getName(const Matrix<int32_t, 1, 2>&) noexcept { return "RowVector2i"; }
inline const char* getName(const Matrix<int32_t, 1, Dynamic>&) noexcept { return "RowVectorXi"; }
inline const char* getName(const Matrix<double, 1, 4, DontAlign>&) noexcept { return "RowVector4du"; }
inline const char* getName(const Matrix<double, 1, 3, DontAlign>&) noexcept { return "RowVector3du"; }
inline const char* getName(const Matrix<double, 1, 2, DontAlign>&) noexcept { return "RowVector2du"; }
inline const char* getName(const Matrix<double, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXdu"; }
inline const char* getName(const Matrix<float, 1, 4, DontAlign>&) noexcept { return "RowVector4fu"; }
inline const char* getName(const Matrix<float, 1, 3, DontAlign>&) noexcept { return "RowVector3fu"; }
inline const char* getName(const Matrix<float, 1, 2, DontAlign>&) noexcept { return "RowVector2fu"; }
inline const char* getName(const Matrix<float, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXfu"; }
inline const char* getName(const Matrix<half, 1, 4, DontAlign>&) noexcept { return "RowVector4hu"; }
inline const char* getName(const Matrix<half, 1, 3, DontAlign>&) noexcept { return "RowVector3hu"; }
inline const char* getName(const Matrix<half, 1, 2, DontAlign>&) noexcept { return "RowVector2hu"; }
inline const char* getName(const Matrix<half, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXhu"; }
inline const char* getName(const Matrix<uint32_t, 1, 4, DontAlign>&) noexcept { return "RowVector4uu"; }
inline const char* getName(const Matrix<uint32_t, 1, 3, DontAlign>&) noexcept { return "RowVector3uu"; }
inline const char* getName(const Matrix<uint32_t, 1, 2, DontAlign>&) noexcept { return "RowVector2uu"; }
inline const char* getName(const Matrix<uint32_t, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXuu"; }
inline const char* getName(const Matrix<int32_t, 1, 4, DontAlign>&) noexcept { return "RowVector4iu"; }
inline const char* getName(const Matrix<int32_t, 1, 3, DontAlign>&) noexcept { return "RowVector3iu"; }
inline const char* getName(const Matrix<int32_t, 1, 2, DontAlign>&) noexcept { return "RowVector2iu"; }
inline const char* getName(const Matrix<int32_t, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXiu"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 4>&) noexcept { return "RowVector4cd"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 3>&) noexcept { return "RowVector3cd"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 2>&) noexcept { return "RowVector2cd"; }
inline const char* getName(const Matrix<std::complex<double>, 1, Dynamic>&) noexcept { return "RowVectorXcd"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 4>&) noexcept { return "RowVector4cf"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 3>&) noexcept { return "RowVector3cf"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 2>&) noexcept { return "RowVector2cf"; }
inline const char* getName(const Matrix<std::complex<float>, 1, Dynamic>&) noexcept { return "RowVectorXcf"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 4>&) noexcept { return "RowVector4ch"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 3>&) noexcept { return "RowVector3ch"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 2>&) noexcept { return "RowVector2ch"; }
inline const char* getName(const Matrix<std::complex<half>, 1, Dynamic>&) noexcept { return "RowVectorXch"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 4>&) noexcept { return "RowVector4cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 3>&) noexcept { return "RowVector3cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 2>&) noexcept { return "RowVector2cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, Dynamic>&) noexcept { return "RowVectorXcu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 4>&) noexcept { return "RowVector4ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 3>&) noexcept { return "RowVector3ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 2>&) noexcept { return "RowVector2ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, Dynamic>&) noexcept { return "RowVectorXci"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 4, DontAlign>&) noexcept { return "RowVector4cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 3, DontAlign>&) noexcept { return "RowVector3cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 1, 2, DontAlign>&) noexcept { return "RowVector2cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXcdu"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 4, DontAlign>&) noexcept { return "RowVector4cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 3, DontAlign>&) noexcept { return "RowVector3cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 1, 2, DontAlign>&) noexcept { return "RowVector2cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXcfu"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 4, DontAlign>&) noexcept { return "RowVector4chu"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 3, DontAlign>&) noexcept { return "RowVector3chu"; }
inline const char* getName(const Matrix<std::complex<half>, 1, 2, DontAlign>&) noexcept { return "RowVector2chu"; }
inline const char* getName(const Matrix<std::complex<half>, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXchu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 4, DontAlign>&) noexcept { return "RowVector4cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 3, DontAlign>&) noexcept { return "RowVector3cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, 2, DontAlign>&) noexcept { return "RowVector2cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXcuu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 4, DontAlign>&) noexcept { return "RowVector4ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 3, DontAlign>&) noexcept { return "RowVector3ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, 2, DontAlign>&) noexcept { return "RowVector2ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 1, Dynamic, DontAlign>&) noexcept { return "RowVectorXciu"; }
inline const char* getName(const Matrix<double, 4, 4>&) noexcept { return "Matrix4d"; }
inline const char* getName(const Matrix<double, 3, 3>&) noexcept { return "Matrix3d"; }
inline const char* getName(const Matrix<double, 2, 2>&) noexcept { return "Matrix2d"; }
inline const char* getName(const Matrix<double, Dynamic, Dynamic>&) noexcept { return "MatrixXd"; }
inline const char* getName(const Matrix<double, 3, 4>&) noexcept { return "Matrix3x4d"; }
inline const char* getName(const Matrix<float, 4, 4>&) noexcept { return "Matrix4f"; }
inline const char* getName(const Matrix<float, 3, 3>&) noexcept { return "Matrix3f"; }
inline const char* getName(const Matrix<float, 2, 2>&) noexcept { return "Matrix2f"; }
inline const char* getName(const Matrix<float, Dynamic, Dynamic>&) noexcept { return "MatrixXf"; }
inline const char* getName(const Matrix<float, 3, 4>&) noexcept { return "Matrix3x4f"; }
inline const char* getName(const Matrix<half, 4, 4>&) noexcept { return "Matrix4h"; }
inline const char* getName(const Matrix<half, 3, 3>&) noexcept { return "Matrix3h"; }
inline const char* getName(const Matrix<half, 2, 2>&) noexcept { return "Matrix2h"; }
inline const char* getName(const Matrix<half, Dynamic, Dynamic>&) noexcept { return "MatrixXh"; }
inline const char* getName(const Matrix<half, 3, 4>&) noexcept { return "Matrix3x4h"; }
inline const char* getName(const Matrix<uint32_t, 4, 4>&) noexcept { return "Matrix4u"; }
inline const char* getName(const Matrix<uint32_t, 3, 3>&) noexcept { return "Matrix3u"; }
inline const char* getName(const Matrix<uint32_t, 2, 2>&) noexcept { return "Matrix2u"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, Dynamic>&) noexcept { return "MatrixXu"; }
inline const char* getName(const Matrix<uint32_t, 3, 4>&) noexcept { return "Matrix3x4u"; }
inline const char* getName(const Matrix<int32_t, 4, 4>&) noexcept { return "Matrix4i"; }
inline const char* getName(const Matrix<int32_t, 3, 3>&) noexcept { return "Matrix3i"; }
inline const char* getName(const Matrix<int32_t, 2, 2>&) noexcept { return "Matrix2i"; }
inline const char* getName(const Matrix<int32_t, Dynamic, Dynamic>&) noexcept { return "MatrixXi"; }
inline const char* getName(const Matrix<int32_t, 3, 4>&) noexcept { return "Matrix3x4i"; }
inline const char* getName(const Matrix<double, 4, 4, RowMajor>&) noexcept { return "Matrix4dr"; }
inline const char* getName(const Matrix<double, 3, 3, RowMajor>&) noexcept { return "Matrix3dr"; }
inline const char* getName(const Matrix<double, 2, 2, RowMajor>&) noexcept { return "Matrix2dr"; }
inline const char* getName(const Matrix<double, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXdr"; }
inline const char* getName(const Matrix<double, 3, 4, RowMajor>&) noexcept { return "Matrix3x4dr"; }
inline const char* getName(const Matrix<float, 4, 4, RowMajor>&) noexcept { return "Matrix4fr"; }
inline const char* getName(const Matrix<float, 3, 3, RowMajor>&) noexcept { return "Matrix3fr"; }
inline const char* getName(const Matrix<float, 2, 2, RowMajor>&) noexcept { return "Matrix2fr"; }
inline const char* getName(const Matrix<float, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXfr"; }
inline const char* getName(const Matrix<float, 3, 4, RowMajor>&) noexcept { return "Matrix3x4fr"; }
inline const char* getName(const Matrix<half, 4, 4, RowMajor>&) noexcept { return "Matrix4hr"; }
inline const char* getName(const Matrix<half, 3, 3, RowMajor>&) noexcept { return "Matrix3hr"; }
inline const char* getName(const Matrix<half, 2, 2, RowMajor>&) noexcept { return "Matrix2hr"; }
inline const char* getName(const Matrix<half, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXhr"; }
inline const char* getName(const Matrix<half, 3, 4, RowMajor>&) noexcept { return "Matrix3x4hr"; }
inline const char* getName(const Matrix<uint32_t, 4, 4, RowMajor>&) noexcept { return "Matrix4ur"; }
inline const char* getName(const Matrix<uint32_t, 3, 3, RowMajor>&) noexcept { return "Matrix3ur"; }
inline const char* getName(const Matrix<uint32_t, 2, 2, RowMajor>&) noexcept { return "Matrix2ur"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXur"; }
inline const char* getName(const Matrix<uint32_t, 3, 4, RowMajor>&) noexcept { return "Matrix3x4ur"; }
inline const char* getName(const Matrix<int32_t, 4, 4, RowMajor>&) noexcept { return "Matrix4ir"; }
inline const char* getName(const Matrix<int32_t, 3, 3, RowMajor>&) noexcept { return "Matrix3ir"; }
inline const char* getName(const Matrix<int32_t, 2, 2, RowMajor>&) noexcept { return "Matrix2ir"; }
inline const char* getName(const Matrix<int32_t, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXir"; }
inline const char* getName(const Matrix<int32_t, 3, 4, RowMajor>&) noexcept { return "Matrix3x4ir"; }
inline const char* getName(const Matrix<double, 4, 4, DontAlign>&) noexcept { return "Matrix4du"; }
inline const char* getName(const Matrix<double, 3, 3, DontAlign>&) noexcept { return "Matrix3du"; }
inline const char* getName(const Matrix<double, 2, 2, DontAlign>&) noexcept { return "Matrix2du"; }
inline const char* getName(const Matrix<double, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXdu"; }
inline const char* getName(const Matrix<double, 3, 4, DontAlign>&) noexcept { return "Matrix3x4du"; }
inline const char* getName(const Matrix<float, 4, 4, DontAlign>&) noexcept { return "Matrix4fu"; }
inline const char* getName(const Matrix<float, 3, 3, DontAlign>&) noexcept { return "Matrix3fu"; }
inline const char* getName(const Matrix<float, 2, 2, DontAlign>&) noexcept { return "Matrix2fu"; }
inline const char* getName(const Matrix<float, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXfu"; }
inline const char* getName(const Matrix<float, 3, 4, DontAlign>&) noexcept { return "Matrix3x4fu"; }
inline const char* getName(const Matrix<half, 4, 4, DontAlign>&) noexcept { return "Matrix4hu"; }
inline const char* getName(const Matrix<half, 3, 3, DontAlign>&) noexcept { return "Matrix3hu"; }
inline const char* getName(const Matrix<half, 2, 2, DontAlign>&) noexcept { return "Matrix2hu"; }
inline const char* getName(const Matrix<half, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXhu"; }
inline const char* getName(const Matrix<half, 3, 4, DontAlign>&) noexcept { return "Matrix3x4hu"; }
inline const char* getName(const Matrix<uint32_t, 4, 4, DontAlign>&) noexcept { return "Matrix4uu"; }
inline const char* getName(const Matrix<uint32_t, 3, 3, DontAlign>&) noexcept { return "Matrix3uu"; }
inline const char* getName(const Matrix<uint32_t, 2, 2, DontAlign>&) noexcept { return "Matrix2uu"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXuu"; }
inline const char* getName(const Matrix<uint32_t, 3, 4, DontAlign>&) noexcept { return "Matrix3x4uu"; }
inline const char* getName(const Matrix<int32_t, 4, 4, DontAlign>&) noexcept { return "Matrix4iu"; }
inline const char* getName(const Matrix<int32_t, 3, 3, DontAlign>&) noexcept { return "Matrix3iu"; }
inline const char* getName(const Matrix<int32_t, 2, 2, DontAlign>&) noexcept { return "Matrix2iu"; }
inline const char* getName(const Matrix<int32_t, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXiu"; }
inline const char* getName(const Matrix<int32_t, 3, 4, DontAlign>&) noexcept { return "Matrix3x4iu"; }
inline const char* getName(const Matrix<double, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4dru"; }
inline const char* getName(const Matrix<double, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3dru"; }
inline const char* getName(const Matrix<double, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2dru"; }
inline const char* getName(const Matrix<double, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXdru"; }
inline const char* getName(const Matrix<double, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4dru"; }
inline const char* getName(const Matrix<float, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4fru"; }
inline const char* getName(const Matrix<float, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3fru"; }
inline const char* getName(const Matrix<float, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2fru"; }
inline const char* getName(const Matrix<float, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXfru"; }
inline const char* getName(const Matrix<float, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4fru"; }
inline const char* getName(const Matrix<half, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4hru"; }
inline const char* getName(const Matrix<half, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3hru"; }
inline const char* getName(const Matrix<half, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2hru"; }
inline const char* getName(const Matrix<half, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXhru"; }
inline const char* getName(const Matrix<half, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4hru"; }
inline const char* getName(const Matrix<uint32_t, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4uru"; }
inline const char* getName(const Matrix<uint32_t, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3uru"; }
inline const char* getName(const Matrix<uint32_t, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2uru"; }
inline const char* getName(const Matrix<uint32_t, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXuru"; }
inline const char* getName(const Matrix<uint32_t, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4uru"; }
inline const char* getName(const Matrix<int32_t, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4iru"; }
inline const char* getName(const Matrix<int32_t, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3iru"; }
inline const char* getName(const Matrix<int32_t, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2iru"; }
inline const char* getName(const Matrix<int32_t, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXiru"; }
inline const char* getName(const Matrix<int32_t, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4iru"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 4>&) noexcept { return "Matrix4cd"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 3>&) noexcept { return "Matrix3cd"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 2>&) noexcept { return "Matrix2cd"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, Dynamic>&) noexcept { return "MatrixXcd"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 4>&) noexcept { return "Matrix3x4cd"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 4>&) noexcept { return "Matrix4cf"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 3>&) noexcept { return "Matrix3cf"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 2>&) noexcept { return "Matrix2cf"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, Dynamic>&) noexcept { return "MatrixXcf"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 4>&) noexcept { return "Matrix3x4cf"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 4>&) noexcept { return "Matrix4ch"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 3>&) noexcept { return "Matrix3ch"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 2>&) noexcept { return "Matrix2ch"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, Dynamic>&) noexcept { return "MatrixXch"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 4>&) noexcept { return "Matrix3x4ch"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 4>&) noexcept { return "Matrix4cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 3>&) noexcept { return "Matrix3cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 2>&) noexcept { return "Matrix2cu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, Dynamic>&) noexcept { return "MatrixXcu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 4>&) noexcept { return "Matrix3x4cu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 4>&) noexcept { return "Matrix4ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 3>&) noexcept { return "Matrix3ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 2>&) noexcept { return "Matrix2ci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, Dynamic>&) noexcept { return "MatrixXci"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 4>&) noexcept { return "Matrix3x4ci"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 4, RowMajor>&) noexcept { return "Matrix4cdr"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 3, RowMajor>&) noexcept { return "Matrix3cdr"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 2, RowMajor>&) noexcept { return "Matrix2cdr"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXcdr"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 4, RowMajor>&) noexcept { return "Matrix3x4cdr"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 4, RowMajor>&) noexcept { return "Matrix4cfr"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 3, RowMajor>&) noexcept { return "Matrix3cfr"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 2, RowMajor>&) noexcept { return "Matrix2cfr"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXcfr"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 4, RowMajor>&) noexcept { return "Matrix3x4cfr"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 4, RowMajor>&) noexcept { return "Matrix4chr"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 3, RowMajor>&) noexcept { return "Matrix3chr"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 2, RowMajor>&) noexcept { return "Matrix2chr"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXchr"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 4, RowMajor>&) noexcept { return "Matrix3x4chr"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 4, RowMajor>&) noexcept { return "Matrix4cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 3, RowMajor>&) noexcept { return "Matrix3cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 2, RowMajor>&) noexcept { return "Matrix2cur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXcur"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 4, RowMajor>&) noexcept { return "Matrix3x4cur"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 4, RowMajor>&) noexcept { return "Matrix4cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 3, RowMajor>&) noexcept { return "Matrix3cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 2, RowMajor>&) noexcept { return "Matrix2cir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, Dynamic, RowMajor>&) noexcept { return "MatrixXcir"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 4, RowMajor>&) noexcept { return "Matrix3x4cir"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 4, DontAlign>&) noexcept { return "Matrix4cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 3, DontAlign>&) noexcept { return "Matrix3cdu"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 2, DontAlign>&) noexcept { return "Matrix2cdu"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXcdu"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 4, DontAlign>&) noexcept { return "Matrix3x4cdu"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 4, DontAlign>&) noexcept { return "Matrix4cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 3, DontAlign>&) noexcept { return "Matrix3cfu"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 2, DontAlign>&) noexcept { return "Matrix2cfu"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXcfu"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 4, DontAlign>&) noexcept { return "Matrix3x4cfu"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 4, DontAlign>&) noexcept { return "Matrix4chu"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 3, DontAlign>&) noexcept { return "Matrix3chu"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 2, DontAlign>&) noexcept { return "Matrix2chu"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXchu"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 4, DontAlign>&) noexcept { return "Matrix3x4chu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 4, DontAlign>&) noexcept { return "Matrix4cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 3, DontAlign>&) noexcept { return "Matrix3cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 2, DontAlign>&) noexcept { return "Matrix2cuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXcuu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 4, DontAlign>&) noexcept { return "Matrix3x4cuu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 4, DontAlign>&) noexcept { return "Matrix4ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 3, DontAlign>&) noexcept { return "Matrix3ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 2, DontAlign>&) noexcept { return "Matrix2ciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, Dynamic, DontAlign>&) noexcept { return "MatrixXciu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 4, DontAlign>&) noexcept { return "Matrix3x4ciu"; }
inline const char* getName(const Matrix<std::complex<double>, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4cdru"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3cdru"; }
inline const char* getName(const Matrix<std::complex<double>, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2cdru"; }
inline const char* getName(const Matrix<std::complex<double>, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXcdru"; }
inline const char* getName(const Matrix<std::complex<double>, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4cdru"; }
inline const char* getName(const Matrix<std::complex<float>, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4cfru"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3cfru"; }
inline const char* getName(const Matrix<std::complex<float>, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2cfru"; }
inline const char* getName(const Matrix<std::complex<float>, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXcfru"; }
inline const char* getName(const Matrix<std::complex<float>, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4cfru"; }
inline const char* getName(const Matrix<std::complex<half>, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4chru"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3chru"; }
inline const char* getName(const Matrix<std::complex<half>, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2chru"; }
inline const char* getName(const Matrix<std::complex<half>, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXchru"; }
inline const char* getName(const Matrix<std::complex<half>, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4chru"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2curu"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXcuru"; }
inline const char* getName(const Matrix<std::complex<uint32_t>, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4curu"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 4, 4, RowMajor | DontAlign>&) noexcept { return "Matrix4ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 3, RowMajor | DontAlign>&) noexcept { return "Matrix3ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 2, 2, RowMajor | DontAlign>&) noexcept { return "Matrix2ciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, Dynamic, Dynamic, RowMajor | DontAlign>&) noexcept { return "MatrixXciru"; }
inline const char* getName(const Matrix<std::complex<int32_t>, 3, 4, RowMajor | DontAlign>&) noexcept { return "Matrix3x4ciru"; }
inline const char* getName(const Matrix<uint8_t, 4, 1>&) noexcept { return "Unorm4"; }
inline const char* getName(const Matrix<uint8_t, 3, 1>&) noexcept { return "Unorm3"; }
inline const char* getName(const Matrix<uint8_t, 2, 1>&) noexcept { return "Unorm2"; }
inline const char* getName(const Matrix<uint8_t, 1, 1>&) noexcept { return "Unorm1"; }
inline const char* getName(const Matrix<int8_t, 4, 1>&) noexcept { return "Snorm4"; }
inline const char* getName(const Matrix<int8_t, 3, 1>&) noexcept { return "Snorm3"; }
inline const char* getName(const Matrix<int8_t, 2, 1>&) noexcept { return "Snorm2"; }
inline const char* getName(const Matrix<int8_t, 1, 1>&) noexcept { return "Snorm1"; }
inline const char* getName(const Rotation2D<double>&) noexcept { return "Rotation2d"; }
inline const char* getName(const Rotation2D<float>&) noexcept { return "Rotation2f"; }
inline const char* getName(const Rotation2D<half>&) noexcept { return "Rotation2h"; }
inline const char* getName(const AngleAxis<double>&) noexcept { return "AngleAxisd"; }
inline const char* getName(const AngleAxis<float>&) noexcept { return "AngleAxisf"; }
inline const char* getName(const AngleAxis<half>&) noexcept { return "AngleAxish"; }
inline const char* getName(const Translation<double, 2>&) noexcept { return "Translation2d"; }
inline const char* getName(const Translation<float, 2>&) noexcept { return "Translation2f"; }
inline const char* getName(const Translation<half, 2>&) noexcept { return "Translation2h"; }
inline const char* getName(const Translation<double, 3>&) noexcept { return "Translation3d"; }
inline const char* getName(const Translation<float, 3>&) noexcept { return "Translation3f"; }
inline const char* getName(const Translation<half, 3>&) noexcept { return "Translation3h"; }
inline const char* getName(const AlignedBox<double, 2>&) noexcept { return "AlignedBox2d"; }
inline const char* getName(const AlignedBox<float, 2>&) noexcept { return "AlignedBox2f"; }
inline const char* getName(const AlignedBox<half, 2>&) noexcept { return "AlignedBox2h"; }
inline const char* getName(const AlignedBox<int32_t, 2>&) noexcept { return "AlignedBox2i"; }
inline const char* getName(const AlignedBox<double, 3>&) noexcept { return "AlignedBox3d"; }
inline const char* getName(const AlignedBox<float, 3>&) noexcept { return "AlignedBox3f"; }
inline const char* getName(const AlignedBox<half, 3>&) noexcept { return "AlignedBox3h"; }
inline const char* getName(const AlignedBox<int32_t, 3>&) noexcept { return "AlignedBox3i"; }
inline const char* getName(const Quaternion<double>&) noexcept { return "Quaterniond"; }
inline const char* getName(const Quaternion<float>&) noexcept { return "Quaternionf"; }
inline const char* getName(const Quaternion<half>&) noexcept { return "Quaternionh"; }
inline const char* getName(const Quaternion<double, DontAlign>&) noexcept { return "Quaterniondu"; }
inline const char* getName(const Quaternion<float, DontAlign>&) noexcept { return "Quaternionfu"; }
inline const char* getName(const Quaternion<half, DontAlign>&) noexcept { return "Quaternionhu"; }
inline const char* getName(const Transform<double, 2, Isometry>&) noexcept { return "Isometry2d"; }
inline const char* getName(const Transform<float, 2, Isometry>&) noexcept { return "Isometry2f"; }
inline const char* getName(const Transform<half, 2, Isometry>&) noexcept { return "Isometry2h"; }
inline const char* getName(const Transform<double, 2, Isometry, DontAlign>&) noexcept { return "Isometry2du"; }
inline const char* getName(const Transform<float, 2, Isometry, DontAlign>&) noexcept { return "Isometry2fu"; }
inline const char* getName(const Transform<half, 2, Isometry, DontAlign>&) noexcept { return "Isometry2hu"; }
inline const char* getName(const Transform<double, 3, Isometry>&) noexcept { return "Isometry3d"; }
inline const char* getName(const Transform<float, 3, Isometry>&) noexcept { return "Isometry3f"; }
inline const char* getName(const Transform<half, 3, Isometry>&) noexcept { return "Isometry3h"; }
inline const char* getName(const Transform<double, 3, Isometry, DontAlign>&) noexcept { return "Isometry3du"; }
inline const char* getName(const Transform<float, 3, Isometry, DontAlign>&) noexcept { return "Isometry3fu"; }
inline const char* getName(const Transform<half, 3, Isometry, DontAlign>&) noexcept { return "Isometry3hu"; }
inline const char* getName(const Transform<double, 2, Affine>&) noexcept { return "Affine2d"; }
inline const char* getName(const Transform<float, 2, Affine>&) noexcept { return "Affine2f"; }
inline const char* getName(const Transform<half, 2, Affine>&) noexcept { return "Affine2h"; }
inline const char* getName(const Transform<double, 2, Affine, DontAlign>&) noexcept { return "Affine2du"; }
inline const char* getName(const Transform<float, 2, Affine, DontAlign>&) noexcept { return "Affine2fu"; }
inline const char* getName(const Transform<half, 2, Affine, DontAlign>&) noexcept { return "Affine2hu"; }
inline const char* getName(const Transform<double, 3, Affine>&) noexcept { return "Affine3d"; }
inline const char* getName(const Transform<float, 3, Affine>&) noexcept { return "Affine3f"; }
inline const char* getName(const Transform<half, 3, Affine>&) noexcept { return "Affine3h"; }
inline const char* getName(const Transform<double, 3, Affine, DontAlign>&) noexcept { return "Affine3du"; }
inline const char* getName(const Transform<float, 3, Affine, DontAlign>&) noexcept { return "Affine3fu"; }
inline const char* getName(const Transform<half, 3, Affine, DontAlign>&) noexcept { return "Affine3hu"; }
inline const char* getName(const Transform<double, 2, AffineCompact>&) noexcept { return "AffineCompact2d"; }
inline const char* getName(const Transform<float, 2, AffineCompact>&) noexcept { return "AffineCompact2f"; }
inline const char* getName(const Transform<half, 2, AffineCompact>&) noexcept { return "AffineCompact2h"; }
inline const char* getName(const Transform<double, 2, AffineCompact, DontAlign>&) noexcept { return "AffineCompact2du"; }
inline const char* getName(const Transform<float, 2, AffineCompact, DontAlign>&) noexcept { return "AffineCompact2fu"; }
inline const char* getName(const Transform<half, 2, AffineCompact, DontAlign>&) noexcept { return "AffineCompact2hu"; }
inline const char* getName(const Transform<double, 3, AffineCompact>&) noexcept { return "AffineCompact3d"; }
inline const char* getName(const Transform<float, 3, AffineCompact>&) noexcept { return "AffineCompact3f"; }
inline const char* getName(const Transform<half, 3, AffineCompact>&) noexcept { return "AffineCompact3h"; }
inline const char* getName(const Transform<double, 3, AffineCompact, DontAlign>&) noexcept { return "AffineCompact3du"; }
inline const char* getName(const Transform<float, 3, AffineCompact, DontAlign>&) noexcept { return "AffineCompact3fu"; }
inline const char* getName(const Transform<half, 3, AffineCompact, DontAlign>&) noexcept { return "AffineCompact3hu"; }
inline const char* getName(const Transform<double, 2, Projective>&) noexcept { return "Projective2d"; }
inline const char* getName(const Transform<float, 2, Projective>&) noexcept { return "Projective2f"; }
inline const char* getName(const Transform<half, 2, Projective>&) noexcept { return "Projective2h"; }
inline const char* getName(const Transform<double, 2, Projective, DontAlign>&) noexcept { return "Projective2du"; }
inline const char* getName(const Transform<float, 2, Projective, DontAlign>&) noexcept { return "Projective2fu"; }
inline const char* getName(const Transform<half, 2, Projective, DontAlign>&) noexcept { return "Projective2hu"; }
inline const char* getName(const Transform<double, 3, Projective>&) noexcept { return "Projective3d"; }
inline const char* getName(const Transform<float, 3, Projective>&) noexcept { return "Projective3f"; }
inline const char* getName(const Transform<half, 3, Projective>&) noexcept { return "Projective3h"; }
inline const char* getName(const Transform<double, 3, Projective, DontAlign>&) noexcept { return "Projective3du"; }
inline const char* getName(const Transform<float, 3, Projective, DontAlign>&) noexcept { return "Projective3fu"; }
inline const char* getName(const Transform<half, 3, Projective, DontAlign>&) noexcept { return "Projective3hu"; }
inline const char* getName(const ParametrizedLine<double, 2>&) noexcept { return "Line2d"; }
inline const char* getName(const ParametrizedLine<float, 2>&) noexcept { return "Line2f"; }
inline const char* getName(const ParametrizedLine<half, 2>&) noexcept { return "Line2h"; }
inline const char* getName(const ParametrizedLine<double, 2, DontAlign>&) noexcept { return "Line2du"; }
inline const char* getName(const ParametrizedLine<float, 2, DontAlign>&) noexcept { return "Line2fu"; }
inline const char* getName(const ParametrizedLine<half, 2, DontAlign>&) noexcept { return "Line2hu"; }
inline const char* getName(const ParametrizedLine<double, 3>&) noexcept { return "Line3d"; }
inline const char* getName(const ParametrizedLine<float, 3>&) noexcept { return "Line3f"; }
inline const char* getName(const ParametrizedLine<half, 3>&) noexcept { return "Line3h"; }
inline const char* getName(const ParametrizedLine<double, 3, DontAlign>&) noexcept { return "Line3du"; }
inline const char* getName(const ParametrizedLine<float, 3, DontAlign>&) noexcept { return "Line3fu"; }
inline const char* getName(const ParametrizedLine<half, 3, DontAlign>&) noexcept { return "Line3hu"; }
inline const char* getName(const Hyperplane<double, 2>&) noexcept { return "Plane2d"; }
inline const char* getName(const Hyperplane<float, 2>&) noexcept { return "Plane2f"; }
inline const char* getName(const Hyperplane<half, 2>&) noexcept { return "Plane2h"; }
inline const char* getName(const Hyperplane<double, 2, DontAlign>&) noexcept { return "Plane2du"; }
inline const char* getName(const Hyperplane<float, 2, DontAlign>&) noexcept { return "Plane2fu"; }
inline const char* getName(const Hyperplane<half, 2, DontAlign>&) noexcept { return "Plane2hu"; }
inline const char* getName(const Hyperplane<double, 3>&) noexcept { return "Plane3d"; }
inline const char* getName(const Hyperplane<float, 3>&) noexcept { return "Plane3f"; }
inline const char* getName(const Hyperplane<half, 3>&) noexcept { return "Plane3h"; }
inline const char* getName(const Hyperplane<double, 3, DontAlign>&) noexcept { return "Plane3du"; }
inline const char* getName(const Hyperplane<float, 3, DontAlign>&) noexcept { return "Plane3fu"; }
inline const char* getName(const Hyperplane<half, 3, DontAlign>&) noexcept { return "Plane3hu"; }
inline const char* getName(const UniformScaling<double>&) noexcept { return "UniformScalingd"; }
inline const char* getName(const UniformScaling<float>&) noexcept { return "UniformScalingf"; }
inline const char* getName(const UniformScaling<half>&) noexcept { return "UniformScalingh"; }

}
