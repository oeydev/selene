// This file is part of the `Selene` library.
// Copyright 2017-2019 Michael Hofmann (https://github.com/kmhofmann).
// Distributed under MIT license. See accompanying LICENSE file in the top-level directory.

#ifndef SELENE_IMG_IMPL_PNG_DETAIL_HPP
#define SELENE_IMG_IMPL_PNG_DETAIL_HPP

#include <selene/selene_config.hpp>

#if defined(SELENE_WITH_LIBPNG)

#include <selene/base/MessageLog.hpp>

#include <png.h>

#include <csetjmp>
#include <cstdio>

namespace sln::impl {

/// \cond INTERNAL

struct PNGErrorManager
{
  bool error_state = false;
  MessageLog message_log;
};

void error_handler(png_structp png_ptr, const char* msg);
void warning_handler(png_structp png_ptr, const char* msg);

/// \endcond

}  // namespace sln::impl

#endif   // defined(SELENE_WITH_LIBPNG)

#endif  // SELENE_IMG_IMPL_PNG_DETAIL_HPP
