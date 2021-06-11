//
// Created by beiyu on 2020-12-09.
//

#ifndef DECODE_FILECODER_H
#define DECODE_FILECODER_H

#include "daunit.h"
#include <string>
#include <vector>

namespace gisl {
/*!
 * @brief file operate
 * @details base class of DaDecoder and DaEncoder
 */
class DaCodecvt {
protected:
  char* buffer{};
  std::string textDisOrder;
  std::string binaryFilename;
  std::string textFilename;
  DaUnit** pUnits;
  int daUnitSize = sizeof(int) + sizeof(char);
  int unitCount = 0;

  static int fileSize(std::ifstream& ifs);

  std::string textInOrder;

public:
  /*!
   * @brief file operate enum
   * @details file operate enum, 1 for ENCODE, and 2 for DECODE
   */
  enum CodecvtMode { ENCODE = 1, DECODE = 2 };

  DaCodecvt();

  ~DaCodecvt();

  /*!
   * @bug SIGTRAP (Trace/breakpoint trap) when delete the last pUnits[i]
   */
  void clear();

  //        virtual int initSize(std::ifstream &ifs) = 0;

  void setTextInOrder(const std::string& textInOrder);

  const std::string& getTextInOrder() const;
};

} // namespace gisl

#endif // DECODE_FILECODER_H
