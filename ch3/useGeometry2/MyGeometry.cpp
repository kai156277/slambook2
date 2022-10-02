#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fmt/core.h>
#include <fmt/ostream.h>

using namespace std;
using namespace Eigen;

const double ARC_TO_DEG = 57.29577951308238;
const double DEG_TO_ARC = 0.0174532925199433;

void printRMat(const Matrix3d &m, const string &name = "rotation matrix")
{
    fmt::print("{} = \n{}\n", name, m); // 注意添加 <fmt/ostream.h>
}

void printV3(const Vector3d &v, const string &name = "v")
{
    fmt::print("{} = {}\n", name, v.transpose());
}

int main(int argc, char **argv)
{
    Matrix3d rotation_matrix = Matrix3d::Identity();
    printRMat(rotation_matrix);

    AngleAxisd rotation_vector(M_PI_4, Vector3d(0, 0, 1));
    cout.precision(3);
    cout << rotation_vector.axis() << "\t" << rotation_vector.angle() << endl;
    cout << rotation_vector.matrix() << endl;

    Vector3d v(1, 0, 0);
    Vector3d v_rot = rotation_vector * v;

    cout << "(1,0,0) after rotation :" << v_rot.transpose() << endl;

    rotation_matrix = rotation_vector.toRotationMatrix();
    printRMat(rotation_matrix);

    // 使用Eigen库将欧拉角转换为旋转矩阵
    Eigen::Matrix3d rotation_matrix1;
    AngleAxisd x_phi(20 * DEG_TO_ARC, Eigen::Vector3d::UnitX()); // 绕X轴转 60 度
    AngleAxisd y_phi(40 * DEG_TO_ARC, Eigen::Vector3d::UnitY()); // 绕Y轴转 40 度
    AngleAxisd z_phi(60 * DEG_TO_ARC, Eigen::Vector3d::UnitZ()); // 绕Z轴转 20 度
    AngleAxisd phi[3] = {x_phi, y_phi, z_phi};
    {
        // rotation_matrix1 = z_phi * y_phi * x_phi; // 按X, Y, Z轴的顺序旋转
        rotation_matrix1 = phi[2] * phi[1] * phi[0];               // 按X, Y, Z轴的顺序旋转
        fmt::print("rotation matrix1 = \n{}\n", rotation_matrix1); // 注意添加 <fmt/ostream.h>

        Eigen::Vector3d eulerAngle1 = rotation_matrix1.eulerAngles(2, 1, 0) * ARC_TO_DEG; // XYZ顺序
        fmt::print("x, y, z = {:.2f}, {:.2f}, {:.2f}\n", eulerAngle1[2], eulerAngle1[1], eulerAngle1[0]);
    }
    {
        // rotation_matrix1 = y_phi * x_phi * z_phi; // 按Z, X, Y 轴的顺序旋转
        rotation_matrix1 = phi[1] * phi[0] * phi[2]; // 按Z, X, Y 轴的顺序旋转

        fmt::print("rotation matrix1 = \n{}\n", rotation_matrix1); // 注意添加 <fmt/ostream.h>

        Eigen::Vector3d eulerAngle1 = rotation_matrix1.eulerAngles(1, 0, 2) * ARC_TO_DEG; // ZXY顺序
        fmt::print("x, y, z = {:.2f}, {:.2f}, {:.2f}\n", eulerAngle1[1], eulerAngle1[0], eulerAngle1[2]);
    }
    {
        // rotation_matrix1 = y_phi * x_phi * z_phi; // 按Z, X, Y 轴的顺序旋转
        rotation_matrix1 = phi[1] * phi[0] * phi[2]; // 按Z, X, Y 轴的顺序旋转

        fmt::print("rotation matrix1 = \n{}\n", rotation_matrix1); // 注意添加 <fmt/ostream.h>

        Eigen::Vector3d eulerAngle1 = rotation_matrix1.eulerAngles(1, 0, 2) * ARC_TO_DEG; // ZXY顺序
        fmt::print("x, y, z = {:.2f}, {:.2f}, {:.2f}\n", eulerAngle1[1], eulerAngle1[0], eulerAngle1[2]);
    }

    // 欧式变换矩阵 Eigen::Isometry
    Isometry3d T = Isometry3d::Identity();
    T.rotate(rotation_matrix);
    T.pretranslate(Vector3d(1, 3, 4));
    fmt::print("transform matrx = \n{}\n", T.matrix());

    Vector3d v_transformed = T * v;

    printV3(v_transformed, "v trnsformed");

    // Affine3d A = Affine3d::Identity(); // 仿射变换

    Quaterniond q = Quaterniond(rotation_vector);

    fmt::print("q from rotation vec = {} \n", q.coeffs().transpose());
    // # Math: v = qvq^{-1}
    v_rot = q * v;
    fmt::print("(1, 0, 0) after rotation = {} \n", v_rot.transpose());
    return 0;
}