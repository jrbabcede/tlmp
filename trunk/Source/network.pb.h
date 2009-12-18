// Generated by the protocol buffer compiler.  DO NOT EDIT!

#ifndef PROTOBUF_network_2eproto__INCLUDED
#define PROTOBUF_network_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>

namespace TLMP {
namespace NetworkMessages {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_network_2eproto();
void protobuf_AssignDesc_network_2eproto();
void protobuf_ShutdownFile_network_2eproto();

class Player;
class Player_Pet;

enum Player_ClassType {
  Player_ClassType_ALCHEMIST = 0,
  Player_ClassType_VANQUISHER = 1,
  Player_ClassType_DESTROYER = 2
};
bool Player_ClassType_IsValid(int value);
const Player_ClassType Player_ClassType_ClassType_MIN = Player_ClassType_ALCHEMIST;
const Player_ClassType Player_ClassType_ClassType_MAX = Player_ClassType_DESTROYER;

const ::google::protobuf::EnumDescriptor* Player_ClassType_descriptor();
inline const ::std::string& Player_ClassType_Name(Player_ClassType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Player_ClassType_descriptor(), value);
}
inline bool Player_ClassType_Parse(
    const ::std::string& name, Player_ClassType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Player_ClassType>(
    Player_ClassType_descriptor(), name, value);
}
enum Player_PetType {
  Player_PetType_DOG = 0,
  Player_PetType_CAT = 1
};
bool Player_PetType_IsValid(int value);
const Player_PetType Player_PetType_PetType_MIN = Player_PetType_DOG;
const Player_PetType Player_PetType_PetType_MAX = Player_PetType_CAT;

const ::google::protobuf::EnumDescriptor* Player_PetType_descriptor();
inline const ::std::string& Player_PetType_Name(Player_PetType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Player_PetType_descriptor(), value);
}
inline bool Player_PetType_Parse(
    const ::std::string& name, Player_PetType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Player_PetType>(
    Player_PetType_descriptor(), name, value);
}
// ===================================================================

class Player_Pet : public ::google::protobuf::Message {
 public:
  Player_Pet();
  virtual ~Player_Pet();
  
  Player_Pet(const Player_Pet& from);
  
  inline Player_Pet& operator=(const Player_Pet& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Player_Pet& default_instance();
  void Swap(Player_Pet* other);
  
  // implements Message ----------------------------------------------
  
  Player_Pet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Player_Pet& from);
  void MergeFrom(const Player_Pet& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int64 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int64 id() const;
  inline void set_id(::google::protobuf::int64 value);
  
  // required .TLMP.NetworkMessages.Player.PetType type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::TLMP::NetworkMessages::Player_PetType type() const;
  inline void set_type(::TLMP::NetworkMessages::Player_PetType value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::int64 id_;
  int type_;
  friend void  protobuf_AddDesc_network_2eproto();
  friend void protobuf_AssignDesc_network_2eproto();
  friend void protobuf_ShutdownFile_network_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Player_Pet* default_instance_;
};
// -------------------------------------------------------------------

class Player : public ::google::protobuf::Message {
 public:
  Player();
  virtual ~Player();
  
  Player(const Player& from);
  
  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Player& default_instance();
  void Swap(Player* other);
  
  // implements Message ----------------------------------------------
  
  Player* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Player& from);
  void MergeFrom(const Player& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Player_Pet Pet;
  
  typedef Player_ClassType ClassType;
  static const ClassType ALCHEMIST = Player_ClassType_ALCHEMIST;
  static const ClassType VANQUISHER = Player_ClassType_VANQUISHER;
  static const ClassType DESTROYER = Player_ClassType_DESTROYER;
  static inline bool ClassType_IsValid(int value) {
    return Player_ClassType_IsValid(value);
  }
  static const ClassType ClassType_MIN =
    Player_ClassType_ClassType_MIN;
  static const ClassType ClassType_MAX =
    Player_ClassType_ClassType_MAX;
  static inline const ::google::protobuf::EnumDescriptor*
  ClassType_descriptor() {
    return Player_ClassType_descriptor();
  }
  static inline const ::std::string& ClassType_Name(ClassType value) {
    return Player_ClassType_Name(value);
  }
  static inline bool ClassType_Parse(const ::std::string& name,
      ClassType* value) {
    return Player_ClassType_Parse(name, value);
  }
  
  typedef Player_PetType PetType;
  static const PetType DOG = Player_PetType_DOG;
  static const PetType CAT = Player_PetType_CAT;
  static inline bool PetType_IsValid(int value) {
    return Player_PetType_IsValid(value);
  }
  static const PetType PetType_MIN =
    Player_PetType_PetType_MIN;
  static const PetType PetType_MAX =
    Player_PetType_PetType_MAX;
  static inline const ::google::protobuf::EnumDescriptor*
  PetType_descriptor() {
    return Player_PetType_descriptor();
  }
  static inline const ::std::string& PetType_Name(PetType value) {
    return Player_PetType_Name(value);
  }
  static inline bool PetType_Parse(const ::std::string& name,
      PetType* value) {
    return Player_PetType_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  
  // required int64 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::int64 id() const;
  inline void set_id(::google::protobuf::int64 value);
  
  // required .TLMP.NetworkMessages.Player.ClassType type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  inline ::TLMP::NetworkMessages::Player_ClassType type() const;
  inline void set_type(::TLMP::NetworkMessages::Player_ClassType value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* name_;
  static const ::std::string _default_name_;
  ::google::protobuf::int64 id_;
  int type_;
  friend void  protobuf_AddDesc_network_2eproto();
  friend void protobuf_AssignDesc_network_2eproto();
  friend void protobuf_ShutdownFile_network_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Player* default_instance_;
};
// ===================================================================


// ===================================================================


// ===================================================================

// Player_Pet

// required int64 id = 1;
inline bool Player_Pet::has_id() const {
  return _has_bit(0);
}
inline void Player_Pet::clear_id() {
  id_ = GOOGLE_LONGLONG(0);
  _clear_bit(0);
}
inline ::google::protobuf::int64 Player_Pet::id() const {
  return id_;
}
inline void Player_Pet::set_id(::google::protobuf::int64 value) {
  _set_bit(0);
  id_ = value;
}

// required .TLMP.NetworkMessages.Player.PetType type = 2;
inline bool Player_Pet::has_type() const {
  return _has_bit(1);
}
inline void Player_Pet::clear_type() {
  type_ = 0;
  _clear_bit(1);
}
inline ::TLMP::NetworkMessages::Player_PetType Player_Pet::type() const {
  return static_cast< ::TLMP::NetworkMessages::Player_PetType >(type_);
}
inline void Player_Pet::set_type(::TLMP::NetworkMessages::Player_PetType value) {
  GOOGLE_DCHECK(::TLMP::NetworkMessages::Player_PetType_IsValid(value));
  _set_bit(1);
  type_ = value;
}

// -------------------------------------------------------------------

// Player

// required string name = 1;
inline bool Player::has_name() const {
  return _has_bit(0);
}
inline void Player::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Player::name() const {
  return *name_;
}
inline void Player::set_name(const ::std::string& value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Player::set_name(const char* value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Player::set_name(const char* value, size_t size) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Player::mutable_name() {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// required int64 id = 2;
inline bool Player::has_id() const {
  return _has_bit(1);
}
inline void Player::clear_id() {
  id_ = GOOGLE_LONGLONG(0);
  _clear_bit(1);
}
inline ::google::protobuf::int64 Player::id() const {
  return id_;
}
inline void Player::set_id(::google::protobuf::int64 value) {
  _set_bit(1);
  id_ = value;
}

// required .TLMP.NetworkMessages.Player.ClassType type = 3;
inline bool Player::has_type() const {
  return _has_bit(2);
}
inline void Player::clear_type() {
  type_ = 0;
  _clear_bit(2);
}
inline ::TLMP::NetworkMessages::Player_ClassType Player::type() const {
  return static_cast< ::TLMP::NetworkMessages::Player_ClassType >(type_);
}
inline void Player::set_type(::TLMP::NetworkMessages::Player_ClassType value) {
  GOOGLE_DCHECK(::TLMP::NetworkMessages::Player_ClassType_IsValid(value));
  _set_bit(2);
  type_ = value;
}


}  // namespace NetworkMessages
}  // namespace TLMP

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::TLMP::NetworkMessages::Player_ClassType>() {
  return ::TLMP::NetworkMessages::Player_ClassType_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::TLMP::NetworkMessages::Player_PetType>() {
  return ::TLMP::NetworkMessages::Player_PetType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

#endif  // PROTOBUF_network_2eproto__INCLUDED
