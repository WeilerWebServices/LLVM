//===- FIRLexer.cpp - .fir file lexer implementation ----------------------===//
//
// This implements a .fir file lexer.
//
//===----------------------------------------------------------------------===//

#include "FIRLexer.h"
#include "mlir/IR/Diagnostics.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/SourceMgr.h"

using namespace circt;
using namespace firrtl;
using namespace mlir;
using llvm::SMLoc;
using llvm::SMRange;
using llvm::SourceMgr;

#define isdigit(x) DO_NOT_USE_SLOW_CTYPE_FUNCTIONS
#define isalpha(x) DO_NOT_USE_SLOW_CTYPE_FUNCTIONS

//===----------------------------------------------------------------------===//
// FIRToken
//===----------------------------------------------------------------------===//

SMLoc FIRToken::getLoc() const {
  return SMLoc::getFromPointer(spelling.data());
}

SMLoc FIRToken::getEndLoc() const {
  return SMLoc::getFromPointer(spelling.data() + spelling.size());
}

SMRange FIRToken::getLocRange() const { return SMRange(getLoc(), getEndLoc()); }

/// Return true if this is one of the keyword token kinds (e.g. kw_wire).
bool FIRToken::isKeyword() const {
  switch (kind) {
  default:
    return false;
#define TOK_KEYWORD(SPELLING)                                                  \
  case kw_##SPELLING:                                                          \
    return true;
#include "FIRTokenKinds.def"
  }
}

/// Given a token containing a string literal, return its value, including
/// removing the quote characters and unescaping the contents of the string. The
/// lexer has already verified that this token is valid.
std::string FIRToken::getStringValue() const {
  assert(getKind() == string);
  return getStringValue(getSpelling());
}

std::string FIRToken::getStringValue(StringRef spelling) {
  // Start by dropping the quotes.
  StringRef bytes = spelling.drop_front().drop_back();

  std::string result;
  result.reserve(bytes.size());
  for (unsigned i = 0, e = bytes.size(); i != e;) {
    auto c = bytes[i++];
    if (c != '\\') {
      result.push_back(c);
      continue;
    }

    assert(i + 1 <= e && "invalid string should be caught by lexer");
    auto c1 = bytes[i++];
    switch (c1) {
    case '"':
    case '\\':
      result.push_back(c1);
      continue;
    case 'n':
      result.push_back('\n');
      continue;
    case 't':
      result.push_back('\t');
      continue;
      // TODO: Handle the rest of the escapes.
    default:
      break;
    }

    assert(i + 1 <= e && "invalid string should be caught by lexer");
    auto c2 = bytes[i++];

    assert(llvm::isHexDigit(c1) && llvm::isHexDigit(c2) && "invalid escape");
    result.push_back((llvm::hexDigitValue(c1) << 4) | llvm::hexDigitValue(c2));
  }

  return result;
}

//===----------------------------------------------------------------------===//
// FIRLexer
//===----------------------------------------------------------------------===//

FIRLexer::FIRLexer(const llvm::SourceMgr &sourceMgr, MLIRContext *context)
    : sourceMgr(sourceMgr), context(context) {
  auto bufferID = sourceMgr.getMainFileID();
  curBuffer = sourceMgr.getMemoryBuffer(bufferID)->getBuffer();
  curPtr = curBuffer.begin();
}

/// Encode the specified source location information into a Location object
/// for attachment to the IR or error reporting.
Location FIRLexer::translateLocation(llvm::SMLoc loc) {
  unsigned mainFileID = sourceMgr.getMainFileID();
  auto lineAndColumn = sourceMgr.getLineAndColumn(loc, mainFileID);
  auto *buffer = sourceMgr.getMemoryBuffer(mainFileID);

  return FileLineColLoc::get(buffer->getBufferIdentifier(), lineAndColumn.first,
                             lineAndColumn.second, context);
}

/// Emit an error message and return a FIRToken::error token.
FIRToken FIRLexer::emitError(const char *loc, const Twine &message) {
  mlir::emitError(translateLocation(SMLoc::getFromPointer(loc)), message);
  return formToken(FIRToken::error, loc);
}

/// Return the indentation level of the specified token.
Optional<unsigned> FIRLexer::getIndentation(const FIRToken &tok) const {
  // Count the number of horizontal whitespace characters before the token.
  auto *bufStart = curBuffer.begin();

  auto isHorizontalWS = [](char c) -> bool {
    return c == ' ' || c == '\t' || c == ',';
  };
  auto isVerticalWS = [](char c) -> bool {
    return c == '\n' || c == '\r' || c == '\f' || c == '\v';
  };

  unsigned indent = 0;
  const auto *ptr = (const char *)tok.getSpelling().data();
  while (ptr != bufStart && isHorizontalWS(ptr[-1]))
    --ptr, ++indent;

  // If the character we stopped at isn't the start of line, then return none.
  if (ptr != bufStart && !isVerticalWS(ptr[-1]))
    return None;

  return indent;
}

//===----------------------------------------------------------------------===//
// Lexer Implementation Methods
//===----------------------------------------------------------------------===//

FIRToken FIRLexer::lexToken() {
  while (true) {
    const char *tokStart = curPtr;
    switch (*curPtr++) {
    default:
      // Handle identifiers.
      if (llvm::isAlpha(curPtr[-1]))
        return lexIdentifierOrKeyword(tokStart);

      // Unknown character, emit an error.
      return emitError(tokStart, "unexpected character");

    case 0:
      // This may either be a nul character in the source file or may be the EOF
      // marker that llvm::MemoryBuffer guarantees will be there.
      if (curPtr - 1 == curBuffer.end())
        return formToken(FIRToken::eof, tokStart);

      LLVM_FALLTHROUGH; // Treat as whitespace.

    case ' ':
    case '\t':
    case '\n':
    case '\r':
    case ',':
      // Handle whitespace.
      continue;

    case '_':
      // Handle identifiers.
      return lexIdentifierOrKeyword(tokStart);

    case '.':
      return formToken(FIRToken::period, tokStart);
    case ':':
      return formToken(FIRToken::colon, tokStart);
    case '(':
      return formToken(FIRToken::l_paren, tokStart);
    case ')':
      return formToken(FIRToken::r_paren, tokStart);
    case '{':
      return formToken(FIRToken::l_brace, tokStart);
    case '}':
      return formToken(FIRToken::r_brace, tokStart);
    case '[':
      return formToken(FIRToken::l_square, tokStart);
    case ']':
      return formToken(FIRToken::r_square, tokStart);
    case '<':
      if (*curPtr == '-')
        return ++curPtr, formToken(FIRToken::less_minus, tokStart);
      if (*curPtr == '=')
        return ++curPtr, formToken(FIRToken::less_equal, tokStart);
      return formToken(FIRToken::less, tokStart);
    case '>':
      return formToken(FIRToken::greater, tokStart);
    case '=':
      if (*curPtr == '>')
        return ++curPtr, formToken(FIRToken::equal_greater, tokStart);
      return formToken(FIRToken::equal, tokStart);
    case '?':
      return formToken(FIRToken::question, tokStart);
    case '@':
      if (*curPtr == '[')
        return lexFileInfo(tokStart);
      // Unknown character, emit an error.
      return emitError(tokStart, "unexpected character");

    case ';':
      skipComment();
      continue;

    case '"':
      return lexString(tokStart);

    case '+':
    case '-':
      if (!llvm::isDigit(*curPtr))
        return emitError(tokStart, "unexpected character");
      ++curPtr;
      return lexFloatingPoint(tokStart);

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return lexNumber(tokStart);
    }
  }
}

/// Lex a file info specifier.
///
///   FileInfo ::= '@[' ('\]'|.)* ']'
///
FIRToken FIRLexer::lexFileInfo(const char *tokStart) {
  while (1) {
    switch (*curPtr++) {
    case ']': // This is the end of the fileinfo literal.
      return formToken(FIRToken::fileinfo, tokStart);
    case '\\':
      // Ignore escaped ']'
      if (*curPtr == ']')
        ++curPtr;
      break;
    case 0:
      // This could be the end of file in the middle of the fileinfo.  If so
      // emit an error.
      if (curPtr - 1 != curBuffer.end())
        break;
      LLVM_FALLTHROUGH;
    case '\n': // Vertical whitespace isn't allowed in a fileinfo.
    case '\v':
    case '\f':
      return emitError(tokStart, "unterminated file info specifier");
    default:
      // Skip over other characters.
      break;
    }
  }
}

/// Lex an identifier or keyword that starts with a letter.
///
///   LegalStartChar ::= [a-zA-Z_]
///   LegalIdChar    ::= LegalStartChar | [0-9] | '$'
//
///   Id ::= LegalStartChar (LegalIdChar)*
///
FIRToken FIRLexer::lexIdentifierOrKeyword(const char *tokStart) {
  // Match the rest of the identifier regex: [0-9a-zA-Z_$-]*
  while (llvm::isAlpha(*curPtr) || llvm::isDigit(*curPtr) || *curPtr == '_' ||
         *curPtr == '$' || *curPtr == '-')
    ++curPtr;

  StringRef spelling(tokStart, curPtr - tokStart);

  // Check to see if this is a 'primop', which is an identifier juxtaposed with
  // a '(' character.
  if (*curPtr == '(') {
    FIRToken::Kind kind = llvm::StringSwitch<FIRToken::Kind>(spelling)
#define TOK_LPKEYWORD(SPELLING) .Case(#SPELLING, FIRToken::lp_##SPELLING)
#include "FIRTokenKinds.def"
                              .Default(FIRToken::identifier);
    if (kind != FIRToken::identifier) {
      ++curPtr;
      return formToken(kind, tokStart);
    }
  }

  // Check to see if this identifier is a keyword.
  FIRToken::Kind kind = llvm::StringSwitch<FIRToken::Kind>(spelling)
#define TOK_KEYWORD(SPELLING) .Case(#SPELLING, FIRToken::kw_##SPELLING)
#include "FIRTokenKinds.def"
                            .Default(FIRToken::identifier);

  return FIRToken(kind, spelling);
}

/// Skip a comment line, starting with a ';' and going to end of line.
void FIRLexer::skipComment() {
  while (true) {
    switch (*curPtr++) {
    case '\n':
    case '\r':
      // Newline is end of comment.
      return;
    case 0:
      // If this is the end of the buffer, end the comment.
      if (curPtr - 1 == curBuffer.end()) {
        --curPtr;
        return;
      }
      LLVM_FALLTHROUGH;
    default:
      // Skip over other characters.
      break;
    }
  }
}

/// StringLit      ::= '"' UnquotedString? '"'
/// UnquotedString ::= ( '\\\'' | '\\"' | ~[\r\n] )+?
///
FIRToken FIRLexer::lexString(const char *tokStart) {
  while (1) {
    switch (*curPtr++) {
    case '"': // This is the end of the string literal.
      return formToken(FIRToken::string, tokStart);
    case '\\':
      // Ignore escaped '"'
      if (*curPtr == '"')
        ++curPtr;
      break;
    case 0:
      // This could be the end of file in the middle of the string.  If so
      // emit an error.
      if (curPtr - 1 != curBuffer.end())
        break;
      LLVM_FALLTHROUGH;
    case '\n': // Vertical whitespace isn't allowed in a string.
    case '\v':
    case '\f':
      return emitError(tokStart, "unterminated string");
    default:
      // Skip over other characters.
      break;
    }
  }
}

/// Lex a number literal.
///
///   UnsignedInt ::= '0' | PosInt
///   PosInt ::= [1-9] ([0-9])*
///
FIRToken FIRLexer::lexNumber(const char *tokStart) {
  assert(llvm::isDigit(curPtr[-1]));

  while (llvm::isDigit(*curPtr))
    ++curPtr;

  // If we encounter a '.', then this is a floating point literal.
  if (*curPtr == '.' && llvm::isDigit(curPtr[1]))
    return lexFloatingPoint(tokStart);

  return formToken(FIRToken::integer, tokStart);
}

/// Lex a floating point literal.  This is called after lexing the optional
/// sign, as well as at least one digit.
///
/// DoubleLit ::=
///       ( '+' | '-' )? Digit+ '.' Digit+ ( 'E' ( '+' | '-' )? Digit+ )?
FIRToken FIRLexer::lexFloatingPoint(const char *tokStart) {
  assert(llvm::isDigit(curPtr[-1]));

  // Consume any more digits we may encounter.
  while (llvm::isDigit(*curPtr))
    ++curPtr;

  if (*curPtr != '.')
    return emitError(tokStart, "expected '.' in floating point literal");
  if (!llvm::isDigit(curPtr[1]))
    return emitError(tokStart, "expected digit in floating point literal");
  curPtr += 2;
  while (llvm::isDigit(*curPtr))
    ++curPtr;

  if (*curPtr == 'E') {
    ++curPtr;
    if (*curPtr == '+' || *curPtr == '-')
      ++curPtr;
    while (llvm::isDigit(*curPtr))
      ++curPtr;
  }
  return formToken(FIRToken::floatingpoint, tokStart);
}