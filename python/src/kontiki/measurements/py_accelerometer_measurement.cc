#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/Dense>

#include <boost/hana.hpp>
namespace hana = boost::hana;

#include <kontiki/measurements/accelerometer_measurement.h>

#include "measurement_helper.h"
#include "../imu_defs.h"

namespace py = pybind11;

PYBIND11_MODULE(_accelerometer_measurement, m) {
  m.doc() = "Accelerometer measurement";

  hana::for_each(imu_types, [&](auto imu_type) {
    using ImuModel = typename decltype(imu_type)::type;

    using Class = kontiki::measurements::AccelerometerMeasurement<ImuModel>;
    std::string pyclass_name = "AccelerometerMeasurement_" + std::string(ImuModel::CLASS_ID);
    auto cls = py::class_<Class, std::shared_ptr<Class>>(m, pyclass_name.c_str());
    cls.def(py::init<std::shared_ptr<ImuModel>, double, const Eigen::Vector3d &, double>());
    cls.def(py::init<std::shared_ptr<ImuModel>, double, const Eigen::Vector3d &>());
    cls.def_readonly("imu", &Class::imu_);
    cls.def_readonly("t", &Class::t);
    cls.def_readonly("a", &Class::a);
    cls.def_readonly("weight", &Class::weight);

    declare_measurement_common<Class>(cls);
  }); // for_each(imu_types)

}