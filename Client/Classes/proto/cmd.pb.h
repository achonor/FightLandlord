﻿// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cmd.proto

#ifndef PROTOBUF_cmd_2eproto__INCLUDED
#define PROTOBUF_cmd_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
class MainProto;
class MainProtoDefaultTypeInternal;
extern MainProtoDefaultTypeInternal _MainProto_default_instance_;
class MessageLoginReq;
class MessageLoginReqDefaultTypeInternal;
extern MessageLoginReqDefaultTypeInternal _MessageLoginReq_default_instance_;
class MessageLoginRsp;
class MessageLoginRspDefaultTypeInternal;
extern MessageLoginRspDefaultTypeInternal _MessageLoginRsp_default_instance_;
class MessagePeopleReq;
class MessagePeopleReqDefaultTypeInternal;
extern MessagePeopleReqDefaultTypeInternal _MessagePeopleReq_default_instance_;
class MessagePeopleRsp;
class MessagePeopleRspDefaultTypeInternal;
extern MessagePeopleRspDefaultTypeInternal _MessagePeopleRsp_default_instance_;

namespace protobuf_cmd_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_cmd_2eproto

// ===================================================================

class MainProto : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MainProto) */ {
 public:
  MainProto();
  virtual ~MainProto();

  MainProto(const MainProto& from);

  inline MainProto& operator=(const MainProto& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MainProto& default_instance();

  static inline const MainProto* internal_default_instance() {
    return reinterpret_cast<const MainProto*>(
               &_MainProto_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(MainProto* other);

  // implements Message ----------------------------------------------

  inline MainProto* New() const PROTOBUF_FINAL { return New(NULL); }

  MainProto* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MainProto& from);
  void MergeFrom(const MainProto& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MainProto* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string messageName = 3;
  bool has_messagename() const;
  void clear_messagename();
  static const int kMessageNameFieldNumber = 3;
  const ::std::string& messagename() const;
  void set_messagename(const ::std::string& value);
  #if LANG_CXX11
  void set_messagename(::std::string&& value);
  #endif
  void set_messagename(const char* value);
  void set_messagename(const char* value, size_t size);
  ::std::string* mutable_messagename();
  ::std::string* release_messagename();
  void set_allocated_messagename(::std::string* messagename);

  // optional string messageData = 4;
  bool has_messagedata() const;
  void clear_messagedata();
  static const int kMessageDataFieldNumber = 4;
  const ::std::string& messagedata() const;
  void set_messagedata(const ::std::string& value);
  #if LANG_CXX11
  void set_messagedata(::std::string&& value);
  #endif
  void set_messagedata(const char* value);
  void set_messagedata(const char* value, size_t size);
  ::std::string* mutable_messagedata();
  ::std::string* release_messagedata();
  void set_allocated_messagedata(::std::string* messagedata);

  // required int32 playerID = 1;
  bool has_playerid() const;
  void clear_playerid();
  static const int kPlayerIDFieldNumber = 1;
  ::google::protobuf::int32 playerid() const;
  void set_playerid(::google::protobuf::int32 value);

  // required int32 messageID = 2;
  bool has_messageid() const;
  void clear_messageid();
  static const int kMessageIDFieldNumber = 2;
  ::google::protobuf::int32 messageid() const;
  void set_messageid(::google::protobuf::int32 value);

  // optional int64 serverTime = 5;
  bool has_servertime() const;
  void clear_servertime();
  static const int kServerTimeFieldNumber = 5;
  ::google::protobuf::int64 servertime() const;
  void set_servertime(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:MainProto)
 private:
  void set_has_playerid();
  void clear_has_playerid();
  void set_has_messageid();
  void clear_has_messageid();
  void set_has_messagename();
  void clear_has_messagename();
  void set_has_messagedata();
  void clear_has_messagedata();
  void set_has_servertime();
  void clear_has_servertime();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr messagename_;
  ::google::protobuf::internal::ArenaStringPtr messagedata_;
  ::google::protobuf::int32 playerid_;
  ::google::protobuf::int32 messageid_;
  ::google::protobuf::int64 servertime_;
  friend struct protobuf_cmd_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessagePeopleReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MessagePeopleReq) */ {
 public:
  MessagePeopleReq();
  virtual ~MessagePeopleReq();

  MessagePeopleReq(const MessagePeopleReq& from);

  inline MessagePeopleReq& operator=(const MessagePeopleReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessagePeopleReq& default_instance();

  static inline const MessagePeopleReq* internal_default_instance() {
    return reinterpret_cast<const MessagePeopleReq*>(
               &_MessagePeopleReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(MessagePeopleReq* other);

  // implements Message ----------------------------------------------

  inline MessagePeopleReq* New() const PROTOBUF_FINAL { return New(NULL); }

  MessagePeopleReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessagePeopleReq& from);
  void MergeFrom(const MessagePeopleReq& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessagePeopleReq* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 peopleID = 1;
  bool has_peopleid() const;
  void clear_peopleid();
  static const int kPeopleIDFieldNumber = 1;
  ::google::protobuf::int32 peopleid() const;
  void set_peopleid(::google::protobuf::int32 value);

  // optional bool isChina = 2;
  bool has_ischina() const;
  void clear_ischina();
  static const int kIsChinaFieldNumber = 2;
  bool ischina() const;
  void set_ischina(bool value);

  // @@protoc_insertion_point(class_scope:MessagePeopleReq)
 private:
  void set_has_peopleid();
  void clear_has_peopleid();
  void set_has_ischina();
  void clear_has_ischina();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 peopleid_;
  bool ischina_;
  friend struct protobuf_cmd_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessagePeopleRsp : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MessagePeopleRsp) */ {
 public:
  MessagePeopleRsp();
  virtual ~MessagePeopleRsp();

  MessagePeopleRsp(const MessagePeopleRsp& from);

  inline MessagePeopleRsp& operator=(const MessagePeopleRsp& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessagePeopleRsp& default_instance();

  static inline const MessagePeopleRsp* internal_default_instance() {
    return reinterpret_cast<const MessagePeopleRsp*>(
               &_MessagePeopleRsp_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(MessagePeopleRsp* other);

  // implements Message ----------------------------------------------

  inline MessagePeopleRsp* New() const PROTOBUF_FINAL { return New(NULL); }

  MessagePeopleRsp* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessagePeopleRsp& from);
  void MergeFrom(const MessagePeopleRsp& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessagePeopleRsp* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional string phone = 2;
  bool has_phone() const;
  void clear_phone();
  static const int kPhoneFieldNumber = 2;
  const ::std::string& phone() const;
  void set_phone(const ::std::string& value);
  #if LANG_CXX11
  void set_phone(::std::string&& value);
  #endif
  void set_phone(const char* value);
  void set_phone(const char* value, size_t size);
  ::std::string* mutable_phone();
  ::std::string* release_phone();
  void set_allocated_phone(::std::string* phone);

  // optional int32 age = 3;
  bool has_age() const;
  void clear_age();
  static const int kAgeFieldNumber = 3;
  ::google::protobuf::int32 age() const;
  void set_age(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MessagePeopleRsp)
 private:
  void set_has_name();
  void clear_has_name();
  void set_has_phone();
  void clear_has_phone();
  void set_has_age();
  void clear_has_age();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr phone_;
  ::google::protobuf::int32 age_;
  friend struct protobuf_cmd_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessageLoginReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MessageLoginReq) */ {
 public:
  MessageLoginReq();
  virtual ~MessageLoginReq();

  MessageLoginReq(const MessageLoginReq& from);

  inline MessageLoginReq& operator=(const MessageLoginReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageLoginReq& default_instance();

  static inline const MessageLoginReq* internal_default_instance() {
    return reinterpret_cast<const MessageLoginReq*>(
               &_MessageLoginReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(MessageLoginReq* other);

  // implements Message ----------------------------------------------

  inline MessageLoginReq* New() const PROTOBUF_FINAL { return New(NULL); }

  MessageLoginReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageLoginReq& from);
  void MergeFrom(const MessageLoginReq& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessageLoginReq* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:MessageLoginReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  friend struct protobuf_cmd_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessageLoginRsp : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MessageLoginRsp) */ {
 public:
  MessageLoginRsp();
  virtual ~MessageLoginRsp();

  MessageLoginRsp(const MessageLoginRsp& from);

  inline MessageLoginRsp& operator=(const MessageLoginRsp& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageLoginRsp& default_instance();

  static inline const MessageLoginRsp* internal_default_instance() {
    return reinterpret_cast<const MessageLoginRsp*>(
               &_MessageLoginRsp_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    4;

  void Swap(MessageLoginRsp* other);

  // implements Message ----------------------------------------------

  inline MessageLoginRsp* New() const PROTOBUF_FINAL { return New(NULL); }

  MessageLoginRsp* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageLoginRsp& from);
  void MergeFrom(const MessageLoginRsp& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessageLoginRsp* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 playerID = 1;
  bool has_playerid() const;
  void clear_playerid();
  static const int kPlayerIDFieldNumber = 1;
  ::google::protobuf::int32 playerid() const;
  void set_playerid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MessageLoginRsp)
 private:
  void set_has_playerid();
  void clear_has_playerid();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 playerid_;
  friend struct protobuf_cmd_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MainProto

// required int32 playerID = 1;
inline bool MainProto::has_playerid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MainProto::set_has_playerid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MainProto::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MainProto::clear_playerid() {
  playerid_ = 0;
  clear_has_playerid();
}
inline ::google::protobuf::int32 MainProto::playerid() const {
  // @@protoc_insertion_point(field_get:MainProto.playerID)
  return playerid_;
}
inline void MainProto::set_playerid(::google::protobuf::int32 value) {
  set_has_playerid();
  playerid_ = value;
  // @@protoc_insertion_point(field_set:MainProto.playerID)
}

// required int32 messageID = 2;
inline bool MainProto::has_messageid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MainProto::set_has_messageid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MainProto::clear_has_messageid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MainProto::clear_messageid() {
  messageid_ = 0;
  clear_has_messageid();
}
inline ::google::protobuf::int32 MainProto::messageid() const {
  // @@protoc_insertion_point(field_get:MainProto.messageID)
  return messageid_;
}
inline void MainProto::set_messageid(::google::protobuf::int32 value) {
  set_has_messageid();
  messageid_ = value;
  // @@protoc_insertion_point(field_set:MainProto.messageID)
}

// optional string messageName = 3;
inline bool MainProto::has_messagename() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MainProto::set_has_messagename() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MainProto::clear_has_messagename() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MainProto::clear_messagename() {
  messagename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_messagename();
}
inline const ::std::string& MainProto::messagename() const {
  // @@protoc_insertion_point(field_get:MainProto.messageName)
  return messagename_.GetNoArena();
}
inline void MainProto::set_messagename(const ::std::string& value) {
  set_has_messagename();
  messagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MainProto.messageName)
}
#if LANG_CXX11
inline void MainProto::set_messagename(::std::string&& value) {
  set_has_messagename();
  messagename_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MainProto.messageName)
}
#endif
inline void MainProto::set_messagename(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_messagename();
  messagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MainProto.messageName)
}
inline void MainProto::set_messagename(const char* value, size_t size) {
  set_has_messagename();
  messagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MainProto.messageName)
}
inline ::std::string* MainProto::mutable_messagename() {
  set_has_messagename();
  // @@protoc_insertion_point(field_mutable:MainProto.messageName)
  return messagename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MainProto::release_messagename() {
  // @@protoc_insertion_point(field_release:MainProto.messageName)
  clear_has_messagename();
  return messagename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MainProto::set_allocated_messagename(::std::string* messagename) {
  if (messagename != NULL) {
    set_has_messagename();
  } else {
    clear_has_messagename();
  }
  messagename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), messagename);
  // @@protoc_insertion_point(field_set_allocated:MainProto.messageName)
}

// optional string messageData = 4;
inline bool MainProto::has_messagedata() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MainProto::set_has_messagedata() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MainProto::clear_has_messagedata() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MainProto::clear_messagedata() {
  messagedata_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_messagedata();
}
inline const ::std::string& MainProto::messagedata() const {
  // @@protoc_insertion_point(field_get:MainProto.messageData)
  return messagedata_.GetNoArena();
}
inline void MainProto::set_messagedata(const ::std::string& value) {
  set_has_messagedata();
  messagedata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MainProto.messageData)
}
#if LANG_CXX11
inline void MainProto::set_messagedata(::std::string&& value) {
  set_has_messagedata();
  messagedata_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MainProto.messageData)
}
#endif
inline void MainProto::set_messagedata(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_messagedata();
  messagedata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MainProto.messageData)
}
inline void MainProto::set_messagedata(const char* value, size_t size) {
  set_has_messagedata();
  messagedata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MainProto.messageData)
}
inline ::std::string* MainProto::mutable_messagedata() {
  set_has_messagedata();
  // @@protoc_insertion_point(field_mutable:MainProto.messageData)
  return messagedata_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MainProto::release_messagedata() {
  // @@protoc_insertion_point(field_release:MainProto.messageData)
  clear_has_messagedata();
  return messagedata_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MainProto::set_allocated_messagedata(::std::string* messagedata) {
  if (messagedata != NULL) {
    set_has_messagedata();
  } else {
    clear_has_messagedata();
  }
  messagedata_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), messagedata);
  // @@protoc_insertion_point(field_set_allocated:MainProto.messageData)
}

// optional int64 serverTime = 5;
inline bool MainProto::has_servertime() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MainProto::set_has_servertime() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MainProto::clear_has_servertime() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MainProto::clear_servertime() {
  servertime_ = GOOGLE_LONGLONG(0);
  clear_has_servertime();
}
inline ::google::protobuf::int64 MainProto::servertime() const {
  // @@protoc_insertion_point(field_get:MainProto.serverTime)
  return servertime_;
}
inline void MainProto::set_servertime(::google::protobuf::int64 value) {
  set_has_servertime();
  servertime_ = value;
  // @@protoc_insertion_point(field_set:MainProto.serverTime)
}

// -------------------------------------------------------------------

// MessagePeopleReq

// optional int32 peopleID = 1;
inline bool MessagePeopleReq::has_peopleid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessagePeopleReq::set_has_peopleid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessagePeopleReq::clear_has_peopleid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessagePeopleReq::clear_peopleid() {
  peopleid_ = 0;
  clear_has_peopleid();
}
inline ::google::protobuf::int32 MessagePeopleReq::peopleid() const {
  // @@protoc_insertion_point(field_get:MessagePeopleReq.peopleID)
  return peopleid_;
}
inline void MessagePeopleReq::set_peopleid(::google::protobuf::int32 value) {
  set_has_peopleid();
  peopleid_ = value;
  // @@protoc_insertion_point(field_set:MessagePeopleReq.peopleID)
}

// optional bool isChina = 2;
inline bool MessagePeopleReq::has_ischina() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessagePeopleReq::set_has_ischina() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessagePeopleReq::clear_has_ischina() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessagePeopleReq::clear_ischina() {
  ischina_ = false;
  clear_has_ischina();
}
inline bool MessagePeopleReq::ischina() const {
  // @@protoc_insertion_point(field_get:MessagePeopleReq.isChina)
  return ischina_;
}
inline void MessagePeopleReq::set_ischina(bool value) {
  set_has_ischina();
  ischina_ = value;
  // @@protoc_insertion_point(field_set:MessagePeopleReq.isChina)
}

// -------------------------------------------------------------------

// MessagePeopleRsp

// optional string name = 1;
inline bool MessagePeopleRsp::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessagePeopleRsp::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessagePeopleRsp::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessagePeopleRsp::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& MessagePeopleRsp::name() const {
  // @@protoc_insertion_point(field_get:MessagePeopleRsp.name)
  return name_.GetNoArena();
}
inline void MessagePeopleRsp::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessagePeopleRsp.name)
}
#if LANG_CXX11
inline void MessagePeopleRsp::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MessagePeopleRsp.name)
}
#endif
inline void MessagePeopleRsp::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessagePeopleRsp.name)
}
inline void MessagePeopleRsp::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessagePeopleRsp.name)
}
inline ::std::string* MessagePeopleRsp::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:MessagePeopleRsp.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessagePeopleRsp::release_name() {
  // @@protoc_insertion_point(field_release:MessagePeopleRsp.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessagePeopleRsp::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:MessagePeopleRsp.name)
}

// optional string phone = 2;
inline bool MessagePeopleRsp::has_phone() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessagePeopleRsp::set_has_phone() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessagePeopleRsp::clear_has_phone() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessagePeopleRsp::clear_phone() {
  phone_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_phone();
}
inline const ::std::string& MessagePeopleRsp::phone() const {
  // @@protoc_insertion_point(field_get:MessagePeopleRsp.phone)
  return phone_.GetNoArena();
}
inline void MessagePeopleRsp::set_phone(const ::std::string& value) {
  set_has_phone();
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessagePeopleRsp.phone)
}
#if LANG_CXX11
inline void MessagePeopleRsp::set_phone(::std::string&& value) {
  set_has_phone();
  phone_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MessagePeopleRsp.phone)
}
#endif
inline void MessagePeopleRsp::set_phone(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_phone();
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessagePeopleRsp.phone)
}
inline void MessagePeopleRsp::set_phone(const char* value, size_t size) {
  set_has_phone();
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessagePeopleRsp.phone)
}
inline ::std::string* MessagePeopleRsp::mutable_phone() {
  set_has_phone();
  // @@protoc_insertion_point(field_mutable:MessagePeopleRsp.phone)
  return phone_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessagePeopleRsp::release_phone() {
  // @@protoc_insertion_point(field_release:MessagePeopleRsp.phone)
  clear_has_phone();
  return phone_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessagePeopleRsp::set_allocated_phone(::std::string* phone) {
  if (phone != NULL) {
    set_has_phone();
  } else {
    clear_has_phone();
  }
  phone_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), phone);
  // @@protoc_insertion_point(field_set_allocated:MessagePeopleRsp.phone)
}

// optional int32 age = 3;
inline bool MessagePeopleRsp::has_age() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessagePeopleRsp::set_has_age() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessagePeopleRsp::clear_has_age() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessagePeopleRsp::clear_age() {
  age_ = 0;
  clear_has_age();
}
inline ::google::protobuf::int32 MessagePeopleRsp::age() const {
  // @@protoc_insertion_point(field_get:MessagePeopleRsp.age)
  return age_;
}
inline void MessagePeopleRsp::set_age(::google::protobuf::int32 value) {
  set_has_age();
  age_ = value;
  // @@protoc_insertion_point(field_set:MessagePeopleRsp.age)
}

// -------------------------------------------------------------------

// MessageLoginReq

// -------------------------------------------------------------------

// MessageLoginRsp

// optional int32 playerID = 1;
inline bool MessageLoginRsp::has_playerid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageLoginRsp::set_has_playerid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageLoginRsp::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageLoginRsp::clear_playerid() {
  playerid_ = 0;
  clear_has_playerid();
}
inline ::google::protobuf::int32 MessageLoginRsp::playerid() const {
  // @@protoc_insertion_point(field_get:MessageLoginRsp.playerID)
  return playerid_;
}
inline void MessageLoginRsp::set_playerid(::google::protobuf::int32 value) {
  set_has_playerid();
  playerid_ = value;
  // @@protoc_insertion_point(field_set:MessageLoginRsp.playerID)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cmd_2eproto__INCLUDED
