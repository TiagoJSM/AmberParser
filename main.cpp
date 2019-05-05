#include <iostream>
#include <clang-c/Index.h>
using namespace std;

ostream& operator<<(ostream& stream, const CXString& str)
{
  stream << clang_getCString(str);
  clang_disposeString(str);
  return stream;
}

CXChildVisitResult attr_visit(CXCursor cursor, CXCursor parent, CXClientData data) {
    if (clang_isAttribute(cursor)) {
        *data = cursor;
        return CXChildVisit_Break;
    }
    return CXChildVisit_Continue;
}

CXCursor first_attr(const CXCursor& c) {
    CXCursor attr;
    unsigned visit_result = clang_visitChildren(c, attr_visit, &attr);
    if (!visit_result) // attribute not found
        attr = clang_getNullCursor();
    return attr;
}

int main()
{
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(
    index,
    "header.hpp", nullptr, 0,
    nullptr, 0,
    CXTranslationUnit_None);
  if (unit == nullptr)
  {
    cerr << "Unable to parse translation unit. Quitting." << endl;
    exit(-1);
  }

  CXCursor cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(
    cursor,
    [](CXCursor c, CXCursor parent, CXClientData client_data)
    {
      cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
        << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
      return CXChildVisit_Recurse;
    },
    nullptr);

  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
}