
# Code Style of Sargasso Engine

```c++
// Files are autoformatted by clang-format.
// Consistency & Readability are the two No. 1 priorities of this codestyle:
//   Avoid messy template shenanigans whenever possible.
//   If the file is becoming big, consider extraction.
//   When extraction is not possible, organize code in sections with comments.
//   Refactor often and always.
//   Consider writing unit tests.

// Headers in alphabetical order.
// Local headers first, grouped together. Libraries and system headers go after.
// Full path starting from `src/` directory.
#include "sargasso/common/log.h"
#include "sargasso/engine.h"

// Include system/library headers even if local headers already include them.
#include <cstdio>
#include <string>
#include <sml/sml.h>

#define MACRO_NAME_IN_UPPER_CASE

// Sargasso namespace for all inner modules.
namespace sargasso {

// Avoid long named namespaces. Try to keep it a one word at max.
// Do not repeat namespaces names from different a hierarchy.
// Try to avoid deep-nested namespaces.
// Namespaces are not indented.
namespace lowercase {

class PascalCaseClassName {
   public:
    // 4 space indentation.
    void camelCaseMethodName(int camelCaseParamName);

   private:
    // -1 space indentation for public and private keywords.
    int _underscoreCamelCasePrivateAttributeName;
};

// Abstract classes are preceded by an I
class IAbstractClass {
    public:
    IAbstractClass(const IAbstractClass&) = delete;
    IAbstractClass(const IAbstractClass&&) = delete;
    virtual void method() const = 0;
}

static void camelCaseLocalHelperFunctionName() {
    // Comment starts with space, uses sentence case, and ends in period.
}

// Applies for class static constants too.
constexpr const int UPPER_SNAKE_CASE_FOR_CONSTANTS = 42;

enum EPascalCaseEnumNamePrecededByE {
    kPascalCaseEnumItem,
    kPascalCaseEnumSize,
}; // Applies for class enums as well.

} // sargasso
} // lowercase

// No trailing whitespaces. Single trailing newline at the end of file.

```
