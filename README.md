# DeuteriumC
## What is DeuteriumC
The (still in early design and implementation) language [Hydrogen] uses
Deuterium as its standard library. Currently, Deuterium isn't implemented
yet in Hydrogen, but this project is a port of Deuterium to C. It uses
the same programming style that Hydrogen is aiming to use (ie. functions
always return an integer type for their operation status, other returns are
pointer parameters to the functions).

However, DeuteriumC isn't a complete port(or at least I am not inteding to do a
complete port anytime soon), it only implements what the standard C library is
missing. It is also not a binary compatible port, at least for the time being,
so calling DeuteriumC functions from Hydrogen will require some special syntax
in Hydrogen that I didn't design yet.

## Why DeuteriumC
I have two main reasons why I am porting the non existent yet Deuterium to C;
The first one is getting an idea about how usable the interface is before I get
to write the Hydrogen compiler using it. The second reason is because I got
tired of writing the same dynamic lists, strings and other structures in C every
time I wanted to use them in a new project, so I thought it would be nice to
have Deuterium in C and let it be the library that handles implement those
structures every time I want to use them in C.

# Interface style
## Naming convention
### Global symbol naming
All public and private DeuteriumC symbols are prefixed with `dtc_`, followed by
the name of the module that symbol is related to, for instance, all string
related functions and structures are prefixed `dtc_str` then followed by (an
often abbreviated) name of the symbol.
### Function parameter naming
#### n_ prefix
If a parameter is prefix with `n_`, then that parameter is allowed to be NULL or
0, whether it be a pointer or an integer type.
#### out_ prefix
Parameters prefixed with `out_` are always of pointer type, aren't allowed to be
NULL, and are meant to be outputs of the function.
#### nout_ prefix
Parameters prefixed with `out_` are always of pointer type, and are meant to be
optional outputs of the function. If that parameter has a NULL value, the
function skips all writes to the data it points to.

## Functions
### Return Value
All DeuteriumC functions are made to act as much similarly to Hydrogen
functions. All DeuteriumC functions have a return type of `status`, which is a
typedef of C's `size_t`.

The return of the function should give a general idea to the caller function
about how well the execution of the function went. If the most signficant bit of
the status was set, it means the function returned with an error, and none of
the outputs are guarenteed to be valid. A well written function, and that should
be the case for all DeuteriumC functions, should return a different error code
for each type of error.

A return code of zero is a general success code, but any value with the highest
bit clear means the execution was sucessful.

Return values in the range [-1024, -1] are reserved errors, they are meant to be
common errors that a lot of functions can share.
Return values in the range [0, 1023] are reserved success status codes, they are
meant to be common success status codes that a lot of funtions can share.

### Parameters
#### Input parameters
All DeuteriumC functions can only take as input integer, float or pointer type
parameters, if a more complex data type is required, then it should be passed as
a pointer.

Parameters can have a valid range that is a subset of the valid range provided
by their type, if `DTC_SAFE_PARAM` is defined during compilation, then all
DeuteriumC functions will check if their parameters respect their boundaries.
This is to mimic Hydrogen's `-safe-params` compile option.

Input parameters always come before all, if any, output parameters. Othe than
the few cases documented in the next section, there is no hard rule about how
input parameters should be ordered, but it is preferrable if they are ordered in
an intuitive way, and if multiple functions take the same inputs, they should
take them in a similat order, for example don't do like libc's `fprintf` and
`fputs` when they both take the `stream` parameter, but the first takes it as
the first parameter, while the latter takes it as the last parameter.

##### Input parameters order
Other than the following cases, there is not restriction on the input paramater
type:
- Before all output parameters
- Functions that do transfer must have destination parameters before source
- Buffer size parameters are immediatly after the same buffer pointer paramter
- Optional parameters are last

Breaking any of these rules when it makes sense is allowed.

#### Output parameters
DeuteriumC functions can return multiple values, all as pointer parameters, all
output parameters are prefixed with `out_` or if they are optional with `nout_`.

Non optional output parameters have to be non NULL, unless the documentation of
the function clearly state a defined non error behaviour if one required output
parameter is set to NULL. Otherwise, if `DTC_SAFE_PARAM` is defined, then a
`DTC_STATUS_PTR_NULL` error will be returned, otherwise, the behaviour is
undefined but likely to be a segmentation fault.

Functions must skip writing to data pointed by optional output parameters if
that parameter is set to NULL, regardless of compile flags.


[Hydrogen]: https://github.com/YavaCoco/Hydrogen
