// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GeneralHeader.proto

#ifndef PROTOBUF_GeneralHeader_2eproto__INCLUDED
#define PROTOBUF_GeneralHeader_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)

namespace protobuf_GeneralHeader_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void InitDefaultsAcknowledgeInfoImpl();
void InitDefaultsAcknowledgeInfo();
void InitDefaultsGeneralHeaderImpl();
void InitDefaultsGeneralHeader();
inline void InitDefaults() {
  InitDefaultsAcknowledgeInfo();
  InitDefaultsGeneralHeader();
}
}  // namespace protobuf_GeneralHeader_2eproto
namespace networkif {
namespace protoc {
class AcknowledgeInfo;
class AcknowledgeInfoDefaultTypeInternal;
extern AcknowledgeInfoDefaultTypeInternal _AcknowledgeInfo_default_instance_;
class GeneralHeader;
class GeneralHeaderDefaultTypeInternal;
extern GeneralHeaderDefaultTypeInternal _GeneralHeader_default_instance_;
}  // namespace protoc
}  // namespace networkif
namespace networkif {
namespace protoc {

enum ConfirmationStatus {
  ACK = 1,
  NACK = 2
};
bool ConfirmationStatus_IsValid(int value);
const ConfirmationStatus ConfirmationStatus_MIN = ACK;
const ConfirmationStatus ConfirmationStatus_MAX = NACK;
const int ConfirmationStatus_ARRAYSIZE = ConfirmationStatus_MAX + 1;

// ===================================================================

class AcknowledgeInfo : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:networkif.protoc.AcknowledgeInfo) */ {
 public:
  AcknowledgeInfo();
  virtual ~AcknowledgeInfo();

  AcknowledgeInfo(const AcknowledgeInfo& from);

  inline AcknowledgeInfo& operator=(const AcknowledgeInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AcknowledgeInfo(AcknowledgeInfo&& from) noexcept
    : AcknowledgeInfo() {
    *this = ::std::move(from);
  }

  inline AcknowledgeInfo& operator=(AcknowledgeInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const AcknowledgeInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AcknowledgeInfo* internal_default_instance() {
    return reinterpret_cast<const AcknowledgeInfo*>(
               &_AcknowledgeInfo_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(AcknowledgeInfo* other);
  friend void swap(AcknowledgeInfo& a, AcknowledgeInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AcknowledgeInfo* New() const PROTOBUF_FINAL { return New(NULL); }

  AcknowledgeInfo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const AcknowledgeInfo& from);
  void MergeFrom(const AcknowledgeInfo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(AcknowledgeInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string reason = 3;
  bool has_reason() const;
  void clear_reason();
  static const int kReasonFieldNumber = 3;
  const ::std::string& reason() const;
  void set_reason(const ::std::string& value);
  #if LANG_CXX11
  void set_reason(::std::string&& value);
  #endif
  void set_reason(const char* value);
  void set_reason(const char* value, size_t size);
  ::std::string* mutable_reason();
  ::std::string* release_reason();
  void set_allocated_reason(::std::string* reason);

  // required uint32 ackSeq = 1;
  bool has_ackseq() const;
  void clear_ackseq();
  static const int kAckSeqFieldNumber = 1;
  ::google::protobuf::uint32 ackseq() const;
  void set_ackseq(::google::protobuf::uint32 value);

  // optional uint32 transactionId = 4;
  bool has_transactionid() const;
  void clear_transactionid();
  static const int kTransactionIdFieldNumber = 4;
  ::google::protobuf::uint32 transactionid() const;
  void set_transactionid(::google::protobuf::uint32 value);

  // required .networkif.protoc.ConfirmationStatus confirmation = 2;
  bool has_confirmation() const;
  void clear_confirmation();
  static const int kConfirmationFieldNumber = 2;
  ::networkif::protoc::ConfirmationStatus confirmation() const;
  void set_confirmation(::networkif::protoc::ConfirmationStatus value);

  // @@protoc_insertion_point(class_scope:networkif.protoc.AcknowledgeInfo)
 private:
  void set_has_ackseq();
  void clear_has_ackseq();
  void set_has_confirmation();
  void clear_has_confirmation();
  void set_has_reason();
  void clear_has_reason();
  void set_has_transactionid();
  void clear_has_transactionid();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr reason_;
  ::google::protobuf::uint32 ackseq_;
  ::google::protobuf::uint32 transactionid_;
  int confirmation_;
  friend struct ::protobuf_GeneralHeader_2eproto::TableStruct;
  friend void ::protobuf_GeneralHeader_2eproto::InitDefaultsAcknowledgeInfoImpl();
};
// -------------------------------------------------------------------

class GeneralHeader : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:networkif.protoc.GeneralHeader) */ {
 public:
  GeneralHeader();
  virtual ~GeneralHeader();

  GeneralHeader(const GeneralHeader& from);

  inline GeneralHeader& operator=(const GeneralHeader& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GeneralHeader(GeneralHeader&& from) noexcept
    : GeneralHeader() {
    *this = ::std::move(from);
  }

  inline GeneralHeader& operator=(GeneralHeader&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const GeneralHeader& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GeneralHeader* internal_default_instance() {
    return reinterpret_cast<const GeneralHeader*>(
               &_GeneralHeader_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(GeneralHeader* other);
  friend void swap(GeneralHeader& a, GeneralHeader& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GeneralHeader* New() const PROTOBUF_FINAL { return New(NULL); }

  GeneralHeader* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const GeneralHeader& from);
  void MergeFrom(const GeneralHeader& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(GeneralHeader* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .networkif.protoc.AcknowledgeInfo ackInfo = 3;
  bool has_ackinfo() const;
  void clear_ackinfo();
  static const int kAckInfoFieldNumber = 3;
  const ::networkif::protoc::AcknowledgeInfo& ackinfo() const;
  ::networkif::protoc::AcknowledgeInfo* release_ackinfo();
  ::networkif::protoc::AcknowledgeInfo* mutable_ackinfo();
  void set_allocated_ackinfo(::networkif::protoc::AcknowledgeInfo* ackinfo);

  // required uint64 timestamp = 1;
  bool has_timestamp() const;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  ::google::protobuf::uint64 timestamp() const;
  void set_timestamp(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:networkif.protoc.GeneralHeader)
 private:
  void set_has_timestamp();
  void clear_has_timestamp();
  void set_has_ackinfo();
  void clear_has_ackinfo();

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::networkif::protoc::AcknowledgeInfo* ackinfo_;
  ::google::protobuf::uint64 timestamp_;
  friend struct ::protobuf_GeneralHeader_2eproto::TableStruct;
  friend void ::protobuf_GeneralHeader_2eproto::InitDefaultsGeneralHeaderImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AcknowledgeInfo

// required uint32 ackSeq = 1;
inline bool AcknowledgeInfo::has_ackseq() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AcknowledgeInfo::set_has_ackseq() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AcknowledgeInfo::clear_has_ackseq() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AcknowledgeInfo::clear_ackseq() {
  ackseq_ = 0u;
  clear_has_ackseq();
}
inline ::google::protobuf::uint32 AcknowledgeInfo::ackseq() const {
  // @@protoc_insertion_point(field_get:networkif.protoc.AcknowledgeInfo.ackSeq)
  return ackseq_;
}
inline void AcknowledgeInfo::set_ackseq(::google::protobuf::uint32 value) {
  set_has_ackseq();
  ackseq_ = value;
  // @@protoc_insertion_point(field_set:networkif.protoc.AcknowledgeInfo.ackSeq)
}

// required .networkif.protoc.ConfirmationStatus confirmation = 2;
inline bool AcknowledgeInfo::has_confirmation() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AcknowledgeInfo::set_has_confirmation() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AcknowledgeInfo::clear_has_confirmation() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AcknowledgeInfo::clear_confirmation() {
  confirmation_ = 1;
  clear_has_confirmation();
}
inline ::networkif::protoc::ConfirmationStatus AcknowledgeInfo::confirmation() const {
  // @@protoc_insertion_point(field_get:networkif.protoc.AcknowledgeInfo.confirmation)
  return static_cast< ::networkif::protoc::ConfirmationStatus >(confirmation_);
}
inline void AcknowledgeInfo::set_confirmation(::networkif::protoc::ConfirmationStatus value) {
  assert(::networkif::protoc::ConfirmationStatus_IsValid(value));
  set_has_confirmation();
  confirmation_ = value;
  // @@protoc_insertion_point(field_set:networkif.protoc.AcknowledgeInfo.confirmation)
}

// optional string reason = 3;
inline bool AcknowledgeInfo::has_reason() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AcknowledgeInfo::set_has_reason() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AcknowledgeInfo::clear_has_reason() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AcknowledgeInfo::clear_reason() {
  reason_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_reason();
}
inline const ::std::string& AcknowledgeInfo::reason() const {
  // @@protoc_insertion_point(field_get:networkif.protoc.AcknowledgeInfo.reason)
  return reason_.GetNoArena();
}
inline void AcknowledgeInfo::set_reason(const ::std::string& value) {
  set_has_reason();
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:networkif.protoc.AcknowledgeInfo.reason)
}
#if LANG_CXX11
inline void AcknowledgeInfo::set_reason(::std::string&& value) {
  set_has_reason();
  reason_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:networkif.protoc.AcknowledgeInfo.reason)
}
#endif
inline void AcknowledgeInfo::set_reason(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_reason();
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:networkif.protoc.AcknowledgeInfo.reason)
}
inline void AcknowledgeInfo::set_reason(const char* value, size_t size) {
  set_has_reason();
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:networkif.protoc.AcknowledgeInfo.reason)
}
inline ::std::string* AcknowledgeInfo::mutable_reason() {
  set_has_reason();
  // @@protoc_insertion_point(field_mutable:networkif.protoc.AcknowledgeInfo.reason)
  return reason_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AcknowledgeInfo::release_reason() {
  // @@protoc_insertion_point(field_release:networkif.protoc.AcknowledgeInfo.reason)
  clear_has_reason();
  return reason_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AcknowledgeInfo::set_allocated_reason(::std::string* reason) {
  if (reason != NULL) {
    set_has_reason();
  } else {
    clear_has_reason();
  }
  reason_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), reason);
  // @@protoc_insertion_point(field_set_allocated:networkif.protoc.AcknowledgeInfo.reason)
}

// optional uint32 transactionId = 4;
inline bool AcknowledgeInfo::has_transactionid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AcknowledgeInfo::set_has_transactionid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AcknowledgeInfo::clear_has_transactionid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AcknowledgeInfo::clear_transactionid() {
  transactionid_ = 0u;
  clear_has_transactionid();
}
inline ::google::protobuf::uint32 AcknowledgeInfo::transactionid() const {
  // @@protoc_insertion_point(field_get:networkif.protoc.AcknowledgeInfo.transactionId)
  return transactionid_;
}
inline void AcknowledgeInfo::set_transactionid(::google::protobuf::uint32 value) {
  set_has_transactionid();
  transactionid_ = value;
  // @@protoc_insertion_point(field_set:networkif.protoc.AcknowledgeInfo.transactionId)
}

// -------------------------------------------------------------------

// GeneralHeader

// required uint64 timestamp = 1;
inline bool GeneralHeader::has_timestamp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GeneralHeader::set_has_timestamp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GeneralHeader::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GeneralHeader::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
  clear_has_timestamp();
}
inline ::google::protobuf::uint64 GeneralHeader::timestamp() const {
  // @@protoc_insertion_point(field_get:networkif.protoc.GeneralHeader.timestamp)
  return timestamp_;
}
inline void GeneralHeader::set_timestamp(::google::protobuf::uint64 value) {
  set_has_timestamp();
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:networkif.protoc.GeneralHeader.timestamp)
}

// optional .networkif.protoc.AcknowledgeInfo ackInfo = 3;
inline bool GeneralHeader::has_ackinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GeneralHeader::set_has_ackinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GeneralHeader::clear_has_ackinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GeneralHeader::clear_ackinfo() {
  if (ackinfo_ != NULL) ackinfo_->Clear();
  clear_has_ackinfo();
}
inline const ::networkif::protoc::AcknowledgeInfo& GeneralHeader::ackinfo() const {
  const ::networkif::protoc::AcknowledgeInfo* p = ackinfo_;
  // @@protoc_insertion_point(field_get:networkif.protoc.GeneralHeader.ackInfo)
  return p != NULL ? *p : *reinterpret_cast<const ::networkif::protoc::AcknowledgeInfo*>(
      &::networkif::protoc::_AcknowledgeInfo_default_instance_);
}
inline ::networkif::protoc::AcknowledgeInfo* GeneralHeader::release_ackinfo() {
  // @@protoc_insertion_point(field_release:networkif.protoc.GeneralHeader.ackInfo)
  clear_has_ackinfo();
  ::networkif::protoc::AcknowledgeInfo* temp = ackinfo_;
  ackinfo_ = NULL;
  return temp;
}
inline ::networkif::protoc::AcknowledgeInfo* GeneralHeader::mutable_ackinfo() {
  set_has_ackinfo();
  if (ackinfo_ == NULL) {
    ackinfo_ = new ::networkif::protoc::AcknowledgeInfo;
  }
  // @@protoc_insertion_point(field_mutable:networkif.protoc.GeneralHeader.ackInfo)
  return ackinfo_;
}
inline void GeneralHeader::set_allocated_ackinfo(::networkif::protoc::AcknowledgeInfo* ackinfo) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete ackinfo_;
  }
  if (ackinfo) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      ackinfo = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, ackinfo, submessage_arena);
    }
    set_has_ackinfo();
  } else {
    clear_has_ackinfo();
  }
  ackinfo_ = ackinfo;
  // @@protoc_insertion_point(field_set_allocated:networkif.protoc.GeneralHeader.ackInfo)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace protoc
}  // namespace networkif

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::networkif::protoc::ConfirmationStatus> : ::google::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GeneralHeader_2eproto__INCLUDED