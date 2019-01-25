# ezsh Tests

ezsh uses a lightweight unit testing framework known as [CU](https://github.com/danfis/cu). 


### Installing CUnit

To install CUnit, run the `install_CUnit` shell script.


### Running Tests

Running `make` should be enough to generate what's needed. To run the tests, run the `./test` file generated in this diectory.

While running tests stdout and stderr are redirected to files. Each test suite has its own files stored in tmp..{out,err} where is prefix defined using CU_SET_OUT_PREFIX macro and is name of test suite.

To compare the regressions run `touch regressions/T1.{out,err}` and then run `./cu/cu-check-regressions`. 
