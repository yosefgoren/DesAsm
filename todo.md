# Features:
* add preprocessor support for WasmAPI
* nested multiple statments, and make it not depend on charecter 'k '.
* 'inline latex' feature.
* basic type properties and checking to exressions.
* 3d graphics projections.
* colors and custom colors
* unary operators (like -1)
* type system: generate type errors
* vscode linter error integration

## Sliders
### Resources
got example json (created by saving graph state using OfflineDesmos, with graph which had slider).

### Functionality
Sliders should have the following features & functionalities:
1. initial assignment
2. min, max values
3. step size

optionally - sliders may have persistancy as a feature: meaning updating the source code in places unrelated to certain sliders should not modify the current state of these unrelated sliders.

### Syntax
example:
```
let Q=0 [-9:9:-3] period 18
```
will create a `Q` slider which will take the values:
```
0, -3, -6, -9, 6, 3, 0, -3
```
where the time interval from the start of the first `0` to the start of the second `0` is 18 seconds.

note that the negative sign means we are going from right to left.
we could have a `+` (and also nothing as default) meaning going left to right,
and `~` symbol meaning going back and foruth.


# Internals & Refactors:
* throw an error when script ends but a local scope is still open (likely only possible with internal errors).

# Project Managment:
* add readme:
    - dependencies (emsdk, flex, bison, npm)
    - dev env setup instructions
    - about