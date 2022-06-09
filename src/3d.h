#pragma once
#include <mat4x4.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <quaternion.hpp>
#include <ext/quaternion_common.hpp>
#include <glm.hpp>

using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix3 = glm::mat3x3;
using Matrix4 = glm::mat4x4;
using Quaternion = glm::quat;

struct PosQuat
{
    Vector3 position;
    Quaternion rotation;
};

namespace Math3D
{
    Quaternion ToQuaternion(Matrix3 rotationMatrix)
    {
        return glm::toQuat(rotationMatrix);
    }

    Vector3 ApplyRotationOn(const Quaternion& rotation, const Vector3& subject)
    {
        return glm::rotate(rotation, subject);
    }

    PosQuat ApplyRotationOn(const Quaternion& rotation, const PosQuat& subject)
    {
        Matrix4 subjectMatrix = Matrix4()
        glm::rotate(rotation, subjectMatrix);
    }
}