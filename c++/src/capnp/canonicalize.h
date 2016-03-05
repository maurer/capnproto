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

#ifndef CAPNP_CANONICALIZE_H_
#define CAPNP_CANONICALIZE_H_

#if defined(__GNUC__) && !CAPNP_HEADER_WARNINGS
#pragma GCC system_header
#endif

#include "dynamic.h"
#include "message.h"

namespace capnp {

// Canonicalize the given Cap'n Proto value into the provided message builder.
// This format is suitable for signing or bytewise equality comparisons, as
// described at https://capnproto.org/encoding.html#canonicalization
//
// Design note:
// This interface is provided as a postprocessing step, rather than as a
// builder, because there are too many conditions that would necessitate
// a retranslation (for example, when incrementally generating a list,
// it would be impossible to know until the last element of the list was
// present how to encode the list).
void canonicalize(DynamicValue::Reader value, MessageBuilder *out);

// Validate the canonicity of a message.
bool isCanonical(MessageReader *msg);
bool isCanonical(MessageBuilder *msg);

}  // namespace capnp

#endif  // CANONICALIZE_H_
