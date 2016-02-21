Basic code conventions for the common folder:

  - Four spaces for indentation. (No tabs! Each tab submitted into this folder kills 4 kittens. Or even 8, depending on your tab settings.)
  - “Egyptian” braces, i.e. opening brace is in the end of the line.
  - Google-style function names: `simple_function()` (constant or log complexity) or `ComplexFunction()` (more than log).
  - `CamelCase` for class names.
  - `kCamelCaseWithSuffix` for constants.
  - `CAPS_FOR_MACROS`, to make them MORE TERRIFYING.
  - `public_variables` are kind of O(1) function... right?
  - `private_variables_` similar to public, but with a trailing underscore (though actually, we don't care).
  - `local_variables` like public variables (actually, whatever).
