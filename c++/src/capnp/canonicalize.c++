// Copyright (c) 2013-2014 Sandstorm Development Group, Inc. and contributors
// Licensed under the MIT License:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define CAPNP_PRIVATE
#include "dynamic.h"
#include "layout.h"
#include "arena.h"
#include <kj/debug.h>
#include <kj/vector.h>

namespace capnp {

void canonicalize(DynamicValue::Reader value, MessageBuilder* out) {
}

bool isCanonical(MessageReader *msg) {
  _::ReaderArena ra(msg);
  _::SegmentReader *segment = ra.tryGetSegment(_::SegmentId(0));

  if (segment == NULL) {
    // The message has no segments
    return false;
  }

  if (ra.tryGetSegment(_::SegmentId(1))) {
    // The message has more than one segment
    return false;
  }

  // TODO check the message for a captable and reject?

  const word* readHead = segment->getStartPtr() + 1;
  return _::PointerReader::getRoot(segment, nullptr, segment->getStartPtr(),
                                   msg->getOptions().nestingLimit)
                                  .isCanonical(&readHead);
}

bool isCanonical(MessageBuilder *msg) {
  SegmentArrayMessageReader msg_reader(msg->getSegmentsForOutput());
  return isCanonical(&msg_reader);
}

}  // namespace capnp
