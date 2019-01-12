// This file is part of the `Selene` library.
// Copyright 2017-2019 Michael Hofmann (https://github.com/kmhofmann).
// Distributed under MIT license. See accompanying LICENSE file in the top-level directory.

#ifndef SELENE_IMG_IO_TIFF_READ_HPP
#define SELENE_IMG_IO_TIFF_READ_HPP

/// @file

#if defined(SELENE_WITH_LIBTIFF)

#include <selene/base/MessageLog.hpp>

#include <selene/img/dynamic/DynImage.hpp>

#include <selene/img_io/TIFFCommon.hpp>

#include <memory>
#include <vector>

namespace sln {

template <typename SourceType> class TIFFReadObject;

template <typename SourceType>
std::vector<TiffImageLayout> read_tiff_layouts(SourceType&&, MessageLog* = nullptr, TIFFReadObject<std::remove_reference_t<SourceType>>* = nullptr);

template <typename SourceType>
DynImage read_tiff(SourceType&&, MessageLog* = nullptr, TIFFReadObject<std::remove_reference_t<SourceType>>* = nullptr);

template <typename SourceType>
std::vector<DynImage> read_tiff_all(SourceType&&, MessageLog* = nullptr, TIFFReadObject<std::remove_reference_t<SourceType>>* = nullptr);


namespace impl {
template <typename SourceType, typename DynImageOrView>
    [[nodiscard]] bool tiff_read_current_directory(TIFFReadObject<SourceType>& tiff_obj,
                                                   MessageLog& message_log,
                                                   DynImageOrView& dyn_img_or_view);
}  // namespace impl

template <typename SourceType>
class TIFFReadObject
{
public:
  TIFFReadObject();
  ~TIFFReadObject();
  TIFFReadObject(const TIFFReadObject&) = delete;
  TIFFReadObject& operator=(const TIFFReadObject&) = delete;
  TIFFReadObject(TIFFReadObject&&) noexcept = default;
  TIFFReadObject& operator=(TIFFReadObject&&) noexcept = default;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;

  bool open(SourceType& source);
  bool open(SourceType&& source);
  TiffImageLayout get_layout();
  bool advance_directory();
  int set_directory(std::uint16_t index);

  template <typename SourceType2> friend std::vector<TiffImageLayout> read_tiff_layouts(SourceType2&&, MessageLog*, TIFFReadObject<std::remove_reference_t<SourceType2>>*);
  template <typename SourceType2> friend DynImage read_tiff(SourceType2&&, MessageLog*, TIFFReadObject<std::remove_reference_t<SourceType2>>*);
  template <typename SourceType2> friend std::vector<DynImage> read_tiff_all(SourceType2&&, MessageLog*, TIFFReadObject<std::remove_reference_t<SourceType2>>*);

  template <typename SourceType2, typename DynImageOrView> friend bool impl::tiff_read_current_directory(TIFFReadObject<SourceType2>&, MessageLog&, DynImageOrView&);
};

// TODO: Implement TIFFReader interface.

// ----------
// Implementation:

template <typename SourceType>
std::vector<TiffImageLayout> read_tiff_layouts(SourceType&& source, MessageLog* message_log, TIFFReadObject<std::remove_reference_t<SourceType>>* tiff_object)
{
  impl::tiff_set_handlers();
  TIFFReadObject<std::remove_reference_t<SourceType>> local_tiff_object;
  TIFFReadObject<std::remove_reference_t<SourceType>>* obj = tiff_object ? tiff_object : &local_tiff_object;

  MessageLog local_message_log;
  std::vector<TiffImageLayout> layouts;

  SELENE_ASSERT(source.is_open());

  if (!obj->open(std::forward<SourceType>(source)))
  {
    local_message_log.add("Data stream could not be opened.", MessageType::Error);
    impl::tiff_assign_message_log(local_message_log, message_log);
    return layouts;
  }

  do
  {
    layouts.push_back(obj->get_layout());
  } while (obj->advance_directory());

  // Reset back to first image
  obj->set_directory(0);

  return layouts;
}


template <typename SourceType>
DynImage read_tiff(SourceType&& source, MessageLog* message_log, TIFFReadObject<std::remove_reference_t<SourceType>>* tiff_object)
{
  impl::tiff_set_handlers();
  TIFFReadObject<std::remove_reference_t<SourceType>> local_tiff_object;
  TIFFReadObject<std::remove_reference_t<SourceType>>* obj = tiff_object ? tiff_object : &local_tiff_object;

  MessageLog local_message_log;

  SELENE_ASSERT(source.is_open());

  if (!obj->open(std::forward<SourceType>(source)))
  {
    local_message_log.add("Data stream could not be opened.", MessageType::Error);
    impl::tiff_assign_message_log(local_message_log, message_log);
    return DynImage{};
  }

  DynImage dyn_img;
  [[maybe_unused]] const bool read_successfully = impl::tiff_read_current_directory(*obj, local_message_log, dyn_img);

  // Reset back to first image
  obj->set_directory(0);

  impl::tiff_assign_message_log(local_message_log, message_log);
  return dyn_img;
}


template <typename SourceType>
std::vector<DynImage> read_tiff_all(SourceType&& source, MessageLog* message_log, TIFFReadObject<std::remove_reference_t<SourceType>>* tiff_object)
{
  impl::tiff_set_handlers();
  TIFFReadObject<std::remove_reference_t<SourceType>> local_tiff_object;
  TIFFReadObject<std::remove_reference_t<SourceType>>* obj = tiff_object ? tiff_object : &local_tiff_object;

  MessageLog local_message_log;
  std::vector<DynImage> images;

  SELENE_ASSERT(source.is_open());

  if (!obj->open(source))
  {
    local_message_log.add("Data stream could not be opened.", MessageType::Error);
    impl::tiff_assign_message_log(local_message_log, message_log);
    return images;
  }

  do
  {
    DynImage dyn_img;
    [[maybe_unused]] const bool read_successfully = impl::tiff_read_current_directory(*obj, local_message_log, dyn_img);
    images.push_back(std::move(dyn_img));
  } while (obj->advance_directory());

  // Reset back to first image
  obj->set_directory(0);

  impl::tiff_assign_message_log(local_message_log, message_log);
  return images;
}

}  // namespace sln

#endif  // defined(SELENE_WITH_LIBTIFF)

#endif  // SELENE_IMG_IO_TIFF_READ_HPP