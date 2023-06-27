#include "fibonacci.h"

#include <pybind11/pybind11.h> 
#include <pybind11/stl_bind.h> 


PYBIND11_MAKE_OPAQUE(std::vector<long long int>);

PYBIND11_MODULE(pyfibonacci, module) {

    // module
    module.doc() = "Fibinacci module"
                   "Test C++ module for using with python";  // module description

    // functions
    module.def(
        "calc",                                   // function name
        &calc_fibonacci,                          // function realization
        "Fibonacci number calculation",           // function description
        pybind11::arg("index")                    // argument's names
    );

    // classes
    pybind11::class_<SeriesCalculator>(module, "SeriesCalculator")
        .def(pybind11::init<>())
        .def("put_index", &SeriesCalculator::put_index, pybind11::arg("index"))
        .def("calc", &SeriesCalculator::calc);

    // binding used containers
    pybind11::bind_vector<std::vector<long long int>>(module, "IntList");

    // adding variables
    module.attr("the_answer") = 42;
    {
        pybind11::object world = pybind11::cast("World");
        module.attr("what") = world;
    }

#ifdef VERSION_INFO
    module.attr("__version__") = VERSION_INFO;
#else
    module.attr("__version__") = "dev";
#endif

}
