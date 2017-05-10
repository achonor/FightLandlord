# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cmd.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='cmd.proto',
  package='',
  syntax='proto2',
  serialized_pb=_b('\n\tcmd.proto\"n\n\tMainProto\x12\x10\n\x08playerID\x18\x01 \x02(\x05\x12\x11\n\tmessageID\x18\x02 \x02(\x05\x12\x13\n\x0bmessageName\x18\x03 \x01(\t\x12\x13\n\x0bmessageData\x18\x04 \x01(\t\x12\x12\n\nserverTime\x18\x05 \x01(\x01\"5\n\x10MessagePeopleReq\x12\x10\n\x08peopleID\x18\x01 \x01(\x05\x12\x0f\n\x07isChina\x18\x02 \x01(\x08\"<\n\x10MessagePeopleRsp\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05phone\x18\x02 \x01(\t\x12\x0b\n\x03\x61ge\x18\x03 \x01(\x05\"\x11\n\x0fMessageLoginReq\"#\n\x0fMessageLoginRsp\x12\x10\n\x08playerID\x18\x01 \x01(\x05\"\x15\n\x13MessageStartGameReq\"\x15\n\x13MessageStartGameRsp\"\x10\n\x0eMessageDealReq\"V\n\x0eMessageDealRsp\x12\r\n\x05upNum\x18\x01 \x01(\x05\x12\x0f\n\x07\x64ownNum\x18\x02 \x01(\x05\x12$\n\tpokerList\x18\x03 \x03(\x0b\x32\x11.MessageDataPoker\"\x17\n\x15MessageUpdateStateReq\"\xc3\x01\n\x15MessageUpdateStateRsp\x12\x11\n\tplayerIdx\x18\x01 \x01(\x05\x12\x11\n\tstateType\x18\x02 \x01(\x05\x12\x0f\n\x07\x65ndTime\x18\x03 \x01(\x01\x12#\n\x08midPoker\x18\x04 \x03(\x0b\x32\x11.MessageDataPoker\x12(\n\rlandlordPoker\x18\x05 \x03(\x0b\x32\x11.MessageDataPoker\x12$\n\tselfPoker\x18\x06 \x03(\x0b\x32\x11.MessageDataPoker\"(\n\x16MessageGradLandlordReq\x12\x0e\n\x06isGrad\x18\x01 \x01(\x08\"\x18\n\x16MessageGradLandlordRsp\"6\n\x12MessageOutPokerReq\x12 \n\x05poker\x18\x01 \x03(\x0b\x32\x11.MessageDataPoker\"\x14\n\x12MessageOutPokerRsp\"1\n\x10MessageDataPoker\x12\r\n\x05\x63olor\x18\x01 \x01(\x05\x12\x0e\n\x06number\x18\x02 \x01(\x05')
)




_MAINPROTO = _descriptor.Descriptor(
  name='MainProto',
  full_name='MainProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='playerID', full_name='MainProto.playerID', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='messageID', full_name='MainProto.messageID', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='messageName', full_name='MainProto.messageName', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='messageData', full_name='MainProto.messageData', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='serverTime', full_name='MainProto.serverTime', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=13,
  serialized_end=123,
)


_MESSAGEPEOPLEREQ = _descriptor.Descriptor(
  name='MessagePeopleReq',
  full_name='MessagePeopleReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='peopleID', full_name='MessagePeopleReq.peopleID', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='isChina', full_name='MessagePeopleReq.isChina', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=125,
  serialized_end=178,
)


_MESSAGEPEOPLERSP = _descriptor.Descriptor(
  name='MessagePeopleRsp',
  full_name='MessagePeopleRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='MessagePeopleRsp.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='phone', full_name='MessagePeopleRsp.phone', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='age', full_name='MessagePeopleRsp.age', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=180,
  serialized_end=240,
)


_MESSAGELOGINREQ = _descriptor.Descriptor(
  name='MessageLoginReq',
  full_name='MessageLoginReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=242,
  serialized_end=259,
)


_MESSAGELOGINRSP = _descriptor.Descriptor(
  name='MessageLoginRsp',
  full_name='MessageLoginRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='playerID', full_name='MessageLoginRsp.playerID', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=261,
  serialized_end=296,
)


_MESSAGESTARTGAMEREQ = _descriptor.Descriptor(
  name='MessageStartGameReq',
  full_name='MessageStartGameReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=298,
  serialized_end=319,
)


_MESSAGESTARTGAMERSP = _descriptor.Descriptor(
  name='MessageStartGameRsp',
  full_name='MessageStartGameRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=321,
  serialized_end=342,
)


_MESSAGEDEALREQ = _descriptor.Descriptor(
  name='MessageDealReq',
  full_name='MessageDealReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=344,
  serialized_end=360,
)


_MESSAGEDEALRSP = _descriptor.Descriptor(
  name='MessageDealRsp',
  full_name='MessageDealRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='upNum', full_name='MessageDealRsp.upNum', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='downNum', full_name='MessageDealRsp.downNum', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pokerList', full_name='MessageDealRsp.pokerList', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=362,
  serialized_end=448,
)


_MESSAGEUPDATESTATEREQ = _descriptor.Descriptor(
  name='MessageUpdateStateReq',
  full_name='MessageUpdateStateReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=450,
  serialized_end=473,
)


_MESSAGEUPDATESTATERSP = _descriptor.Descriptor(
  name='MessageUpdateStateRsp',
  full_name='MessageUpdateStateRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='playerIdx', full_name='MessageUpdateStateRsp.playerIdx', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='stateType', full_name='MessageUpdateStateRsp.stateType', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='endTime', full_name='MessageUpdateStateRsp.endTime', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='midPoker', full_name='MessageUpdateStateRsp.midPoker', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='landlordPoker', full_name='MessageUpdateStateRsp.landlordPoker', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='selfPoker', full_name='MessageUpdateStateRsp.selfPoker', index=5,
      number=6, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=476,
  serialized_end=671,
)


_MESSAGEGRADLANDLORDREQ = _descriptor.Descriptor(
  name='MessageGradLandlordReq',
  full_name='MessageGradLandlordReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='isGrad', full_name='MessageGradLandlordReq.isGrad', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=673,
  serialized_end=713,
)


_MESSAGEGRADLANDLORDRSP = _descriptor.Descriptor(
  name='MessageGradLandlordRsp',
  full_name='MessageGradLandlordRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=715,
  serialized_end=739,
)


_MESSAGEOUTPOKERREQ = _descriptor.Descriptor(
  name='MessageOutPokerReq',
  full_name='MessageOutPokerReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='poker', full_name='MessageOutPokerReq.poker', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=741,
  serialized_end=795,
)


_MESSAGEOUTPOKERRSP = _descriptor.Descriptor(
  name='MessageOutPokerRsp',
  full_name='MessageOutPokerRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=797,
  serialized_end=817,
)


_MESSAGEDATAPOKER = _descriptor.Descriptor(
  name='MessageDataPoker',
  full_name='MessageDataPoker',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='color', full_name='MessageDataPoker.color', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='number', full_name='MessageDataPoker.number', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=819,
  serialized_end=868,
)

_MESSAGEDEALRSP.fields_by_name['pokerList'].message_type = _MESSAGEDATAPOKER
_MESSAGEUPDATESTATERSP.fields_by_name['midPoker'].message_type = _MESSAGEDATAPOKER
_MESSAGEUPDATESTATERSP.fields_by_name['landlordPoker'].message_type = _MESSAGEDATAPOKER
_MESSAGEUPDATESTATERSP.fields_by_name['selfPoker'].message_type = _MESSAGEDATAPOKER
_MESSAGEOUTPOKERREQ.fields_by_name['poker'].message_type = _MESSAGEDATAPOKER
DESCRIPTOR.message_types_by_name['MainProto'] = _MAINPROTO
DESCRIPTOR.message_types_by_name['MessagePeopleReq'] = _MESSAGEPEOPLEREQ
DESCRIPTOR.message_types_by_name['MessagePeopleRsp'] = _MESSAGEPEOPLERSP
DESCRIPTOR.message_types_by_name['MessageLoginReq'] = _MESSAGELOGINREQ
DESCRIPTOR.message_types_by_name['MessageLoginRsp'] = _MESSAGELOGINRSP
DESCRIPTOR.message_types_by_name['MessageStartGameReq'] = _MESSAGESTARTGAMEREQ
DESCRIPTOR.message_types_by_name['MessageStartGameRsp'] = _MESSAGESTARTGAMERSP
DESCRIPTOR.message_types_by_name['MessageDealReq'] = _MESSAGEDEALREQ
DESCRIPTOR.message_types_by_name['MessageDealRsp'] = _MESSAGEDEALRSP
DESCRIPTOR.message_types_by_name['MessageUpdateStateReq'] = _MESSAGEUPDATESTATEREQ
DESCRIPTOR.message_types_by_name['MessageUpdateStateRsp'] = _MESSAGEUPDATESTATERSP
DESCRIPTOR.message_types_by_name['MessageGradLandlordReq'] = _MESSAGEGRADLANDLORDREQ
DESCRIPTOR.message_types_by_name['MessageGradLandlordRsp'] = _MESSAGEGRADLANDLORDRSP
DESCRIPTOR.message_types_by_name['MessageOutPokerReq'] = _MESSAGEOUTPOKERREQ
DESCRIPTOR.message_types_by_name['MessageOutPokerRsp'] = _MESSAGEOUTPOKERRSP
DESCRIPTOR.message_types_by_name['MessageDataPoker'] = _MESSAGEDATAPOKER
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

MainProto = _reflection.GeneratedProtocolMessageType('MainProto', (_message.Message,), dict(
  DESCRIPTOR = _MAINPROTO,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MainProto)
  ))
_sym_db.RegisterMessage(MainProto)

MessagePeopleReq = _reflection.GeneratedProtocolMessageType('MessagePeopleReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEPEOPLEREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessagePeopleReq)
  ))
_sym_db.RegisterMessage(MessagePeopleReq)

MessagePeopleRsp = _reflection.GeneratedProtocolMessageType('MessagePeopleRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEPEOPLERSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessagePeopleRsp)
  ))
_sym_db.RegisterMessage(MessagePeopleRsp)

MessageLoginReq = _reflection.GeneratedProtocolMessageType('MessageLoginReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGELOGINREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageLoginReq)
  ))
_sym_db.RegisterMessage(MessageLoginReq)

MessageLoginRsp = _reflection.GeneratedProtocolMessageType('MessageLoginRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGELOGINRSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageLoginRsp)
  ))
_sym_db.RegisterMessage(MessageLoginRsp)

MessageStartGameReq = _reflection.GeneratedProtocolMessageType('MessageStartGameReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGESTARTGAMEREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageStartGameReq)
  ))
_sym_db.RegisterMessage(MessageStartGameReq)

MessageStartGameRsp = _reflection.GeneratedProtocolMessageType('MessageStartGameRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGESTARTGAMERSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageStartGameRsp)
  ))
_sym_db.RegisterMessage(MessageStartGameRsp)

MessageDealReq = _reflection.GeneratedProtocolMessageType('MessageDealReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEDEALREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageDealReq)
  ))
_sym_db.RegisterMessage(MessageDealReq)

MessageDealRsp = _reflection.GeneratedProtocolMessageType('MessageDealRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEDEALRSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageDealRsp)
  ))
_sym_db.RegisterMessage(MessageDealRsp)

MessageUpdateStateReq = _reflection.GeneratedProtocolMessageType('MessageUpdateStateReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEUPDATESTATEREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageUpdateStateReq)
  ))
_sym_db.RegisterMessage(MessageUpdateStateReq)

MessageUpdateStateRsp = _reflection.GeneratedProtocolMessageType('MessageUpdateStateRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEUPDATESTATERSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageUpdateStateRsp)
  ))
_sym_db.RegisterMessage(MessageUpdateStateRsp)

MessageGradLandlordReq = _reflection.GeneratedProtocolMessageType('MessageGradLandlordReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEGRADLANDLORDREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageGradLandlordReq)
  ))
_sym_db.RegisterMessage(MessageGradLandlordReq)

MessageGradLandlordRsp = _reflection.GeneratedProtocolMessageType('MessageGradLandlordRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEGRADLANDLORDRSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageGradLandlordRsp)
  ))
_sym_db.RegisterMessage(MessageGradLandlordRsp)

MessageOutPokerReq = _reflection.GeneratedProtocolMessageType('MessageOutPokerReq', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEOUTPOKERREQ,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageOutPokerReq)
  ))
_sym_db.RegisterMessage(MessageOutPokerReq)

MessageOutPokerRsp = _reflection.GeneratedProtocolMessageType('MessageOutPokerRsp', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEOUTPOKERRSP,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageOutPokerRsp)
  ))
_sym_db.RegisterMessage(MessageOutPokerRsp)

MessageDataPoker = _reflection.GeneratedProtocolMessageType('MessageDataPoker', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEDATAPOKER,
  __module__ = 'cmd_pb2'
  # @@protoc_insertion_point(class_scope:MessageDataPoker)
  ))
_sym_db.RegisterMessage(MessageDataPoker)


# @@protoc_insertion_point(module_scope)
