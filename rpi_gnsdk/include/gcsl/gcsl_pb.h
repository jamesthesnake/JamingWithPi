/*
 * Copyright (c) 2011 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* --- gcsl_pb.h: GCSL public protobuf c runtime api --- */

/*
 * Copyright 2008, Dave Benson.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with
 * the License. You may obtain a copy of the License
 * at http://www.apache.org/licenses/LICENSE-2.0 Unless
 * required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _GCSL_PB_RUNTIME_H_
#define _GCSL_PB_RUNTIME_H_

#ifdef __cplusplus
extern "C"{
#endif

/* initialize file system subsystem	*/
gcsl_error_t	gcsl_pb_initialize		(void);
gcsl_error_t	gcsl_pb_shutdown		(void);

gcsl_cstr_t		gcsl_pb_get_version		(void);
gcsl_cstr_t		gcsl_pb_get_build_date	(void);

/*
** Global PB Options APIs
*/
gcsl_error_t	gcsl_pb_option_set			(gcsl_cstr_t option_name, gcsl_cstr_t option_value);
gcsl_error_t	gcsl_pb_option_get			(gcsl_cstr_t option_name, gcsl_cstr_t* p_option_value);


#if defined(offsetof)
#undef	offsetof
#endif
#define offsetof(struct,member)   (gcsl_size_t)&(((struct *)0)->member)

#if defined(GN_PB_OFFSETOF)
#undef	GN_PB_OFFSETOF
#endif
#define GN_PB_OFFSETOF(struct, member) offsetof(struct, member)


typedef enum
{
  GN_PB_LABEL_REQUIRED,
  GN_PB_LABEL_OPTIONAL,
  GN_PB_LABEL_REPEATED
} GN_PB_Label;

typedef enum
{
  GN_PB_TYPE_INT32,
  GN_PB_TYPE_SINT32,
  GN_PB_TYPE_SFIXED32,
  GN_PB_TYPE_UINT32,
  GN_PB_TYPE_FIXED32,
  GN_PB_TYPE_BOOL,
  GN_PB_TYPE_ENUM,
  GN_PB_TYPE_STRING,
  GN_PB_TYPE_BYTES,
  GN_PB_TYPE_MESSAGE
} GN_PB_Type;


typedef struct _GN_PB_BinaryData GN_PB_BinaryData;
struct _GN_PB_BinaryData
{
  gcsl_size_t	len;
  gcsl_byte_t*	data;
};

typedef struct _GN_PB_IntRange GN_PB_IntRange; /* private */

/* --- memory management --- */
typedef struct _GN_PB_Allocator GN_PB_Allocator;
struct _GN_PB_Allocator
{
	void*			(*alloc)(void *allocator_data, gcsl_size_t size);
	void			(*free)(void *allocator_data, void *pointer);
	void*			(*tmp_alloc)(void *allocator_data, gcsl_size_t size);
	gcsl_uint32_t	max_alloca;
	void*			allocator_data;
};

/* This is a configurable allocator.
 * By default, it uses the system allocator (meaning malloc() and free()).
 * This is typically done to incorporate into frameworks that provide
 * some nonstandard allocation functions.
 */
extern GN_PB_Allocator gcsl_pb_default_allocator; /* settable */

/* This is the system allocator, meaning it uses malloc() and free() */
extern GN_PB_Allocator gcsl_pb_system_allocator;  /* use malloc, free etc */

/* This is the function that our default allocators call when they 
   run out-of-memory.  The default behavior of this function is to
   terminate your program. */
extern void (*gcsl_pb_out_of_memory) (void);

/* --- append-only data buffer --- */
typedef struct _GN_PB_Buffer GN_PB_Buffer;
struct _GN_PB_Buffer
{
	void (*append)(	GN_PB_Buffer*		buffer,
					gcsl_size_t			len,
					const gcsl_byte_t*	data);
};
/* --- enums --- */
typedef struct _GN_PB_EnumValue GN_PB_EnumValue;
typedef struct _GN_PB_EnumValueIndex GN_PB_EnumValueIndex;
typedef struct _GN_PB_EnumDescriptor GN_PB_EnumDescriptor;

/* GN_PB_EnumValue:  this represents a single value of
 * an enumeration.
 * 'name' is the string identifying this value, as given in the .proto file.
 * 'c_name' is the full name of the C enumeration value.
 * 'value' is the number assigned to this value, as given in the .proto file.
 */
struct _GN_PB_EnumValue
{
	gcsl_cstr_t		name;
	gcsl_cstr_t		c_name;
	gcsl_int32_t	value;
};

/* GN_PB_EnumDescriptor: the represents the enum as a whole,
 * with all its values.
 * 'magic' is a code we check to ensure that the api is used correctly.
 * 'name' is the qualified name (e.g. "namespace.Type").
 * 'short_name' is the unqualified name ("Type"), as given in the .proto file.
 * 'package_name' is the '.'-separated namespace
 * 'n_values' is the number of distinct values.
 * 'values' is the array of distinct values.
 * 'n_value_names' number of named values (including aliases).
 * 'value_names' are the named values (including aliases).
 *
 * The rest of the values are private essentially.
 *
 * see also: Use gn_pb_enum_descriptor_get_value_by_name()
 * and gn_pb_enum_descriptor_get_value() to efficiently
 * lookup values in the descriptor.
 */
struct _GN_PB_EnumDescriptor
{
	gcsl_uint32_t				magic;

	gcsl_cstr_t					name;
	gcsl_cstr_t					short_name;
	gcsl_cstr_t					c_name;
	gcsl_cstr_t					package_name;

	/* sorted by value */
	gcsl_uint32_t				n_values;
	const GN_PB_EnumValue*		values;

	/* sorted by name */
	gcsl_uint32_t				n_value_names;
	const GN_PB_EnumValueIndex*	values_by_name;

	/* value-ranges, for faster lookups by number */
	gcsl_uint32_t				n_value_ranges;
	const GN_PB_IntRange*		value_ranges;

	gcsl_void_t*				reserved1;
	gcsl_void_t*				reserved2;
	gcsl_void_t*				reserved3;
	gcsl_void_t*				reserved4;
};

/* --- messages --- */
typedef struct _GN_PB_MessageDescriptor GN_PB_MessageDescriptor;
typedef struct _GN_PB_FieldDescriptor GN_PB_FieldDescriptor;
/* GN_PB_FieldDescriptor: description of a single field
 * in a message.
 * 'name' is the name of the field, as given in the .proto file.
 * 'id' is the code representing the field, as given in the .proto file.
 * 'label' is one of GN_PB_LABEL_{REQUIRED,OPTIONAL,REPEATED}
 * 'type' is the type of field.
 * 'quantifier_offset' is the offset in bytes into the message's C structure
 *        for this member's "has_MEMBER" field (for optional members) or
 *        "n_MEMBER" field (for repeated members).
 * 'offset' is the offset in bytes into the message's C structure
 *        for the member itself.
 * 'descriptor' is a pointer to a GN_PB_{Enum,Message}Descriptor
 *        if type is GN_PB_TYPE_{ENUM,MESSAGE} respectively,
 *        otherwise GCSL_NULL.
 * 'default_value' is a pointer to a default value for this field,
 *        where allowed.
 */
struct _GN_PB_FieldDescriptor
{
	gcsl_cstr_t					name;
	gcsl_uint32_t				id;
	GN_PB_Label					label;
	GN_PB_Type					type;
	gcsl_uint32_t				quantifier_offset;
	gcsl_uint32_t				offset;
	const gcsl_void_t*			descriptor;   /* for MESSAGE and ENUM types */
	const gcsl_void_t*			default_value;   /* or GCSL_NULL if no default-value */

	gcsl_void_t*				reserved1;
	gcsl_void_t*				reserved2;
};
/* GN_PB_MessageDescriptor: description of a message.
 *
 * 'magic' is a code we check to ensure that the api is used correctly.
 * 'name' is the qualified name (e.g. "namespace.Type").
 * 'short_name' is the unqualified name ("Type"), as given in the .proto file.
 * 'c_name' is the c-formatted name of the structure
 * 'package_name' is the '.'-separated namespace
 * 'sizeof_message' is the size in bytes of the C structure
 *        representing an instance of this type of message.
 * 'n_fields' is the number of known fields in this message.
 * 'fields' is the fields sorted by id number.
 * 'fields_sorted_by_name', 'n_field_ranges' and 'field_ranges'
 *       are used for looking up fields by name and id. (private)
 */
struct _GN_PB_MessageDescriptor
{
	gcsl_uint32_t					magic;

	gcsl_cstr_t						name;
	gcsl_cstr_t						short_name;
	gcsl_cstr_t						c_name;
	gcsl_cstr_t						package_name;

	gcsl_size_t						sizeof_message;

	/* sorted by field-id */
	gcsl_uint32_t					n_fields;
	const GN_PB_FieldDescriptor*	fields;
	const gcsl_uint32_t*			fields_sorted_by_name;

	/* ranges, optimization for looking up fields */
	gcsl_uint32_t					n_field_ranges;
	const GN_PB_IntRange*			field_ranges;

	gcsl_void_t*					reserved1;
	gcsl_void_t*					reserved2;
	gcsl_void_t*					reserved3;
	gcsl_void_t*					reserved4;
};


/* GN_PB_Message: an instance of a message.
 *
 * GN_PB_Message is sort-of a lightweight
 * base-class for all messages.
 * 
 * In particular, GN_PB_Message doesn't have
 * any allocation policy associated with it.
 * That's because it is common to create GN_PB_Message's
 * on the stack.  In fact, we that's what we recommend
 * for sending messages (because if you just allocate from the
 * stack, then you can't really have a memory leak).
 *
 * This means that functions like gn_pb_message_unpack()
 * which return a GN_PB_Message must be paired
 * with a free function, like gn_pb_message_free_unpacked().
 *
 * 'descriptor' gives the locations and types of the members of message
 * 'n_unknown_fields' is the number of fields we didn't recognize.
 * 'unknown_fields' are fields we didn't recognize.
 */
typedef struct _GN_PB_Message GN_PB_Message;
typedef struct _GN_PB_MessageUnknownField GN_PB_MessageUnknownField;
struct _GN_PB_Message
{
	const GN_PB_MessageDescriptor*		descriptor;
	gcsl_uint32_t						n_unknown_fields;
	GN_PB_MessageUnknownField*			unknown_fields;
};
#define GN_PB_MESSAGE_INIT(descriptor) { descriptor, 0, GCSL_NULL }

/* To pack a message: you have two options:
   (1) you can compute the size of the message
	   using gn_pb_message_get_packed_size() 
	   then pass gn_pb_message_pack() a buffer of
	   that length.
   (2) Provide a virtual buffer (a GN_PB_Buffer) to
	   accept data as we scan through it.
 */
gcsl_error_t	gcsl_pb_message_get_packed_size	(const GN_PB_Message* message, gcsl_size_t* size);
gcsl_error_t	gcsl_pb_message_pack			(const GN_PB_Message* message, gcsl_byte_t* out, gcsl_size_t* size);
gcsl_error_t	gcsl_pb_message_unpack			(const GN_PB_MessageDescriptor *, GN_PB_Allocator* allocator, gcsl_size_t len, const gcsl_byte_t* data, GN_PB_Message** message);
gcsl_error_t	gcsl_pb_message_free_unpacked	(GN_PB_Message* message, GN_PB_Allocator* allocator);

/* WARNING: 'to_init' must be a block of memory of size description->sizeof_message. */
gcsl_size_t		gcsl_pb_message_init			(const GN_PB_MessageDescriptor *, GN_PB_Message* to_init);

/* --- querying the descriptors --- */
gcsl_error_t	gcsl_pb_enum_descriptor_get_value_by_name	(const GN_PB_EnumDescriptor* desc, gcsl_cstr_t name, const GN_PB_EnumValue **output);
gcsl_error_t	gcsl_pb_enum_descriptor_get_value			(const GN_PB_EnumDescriptor* desc, gcsl_int32_t value, const GN_PB_EnumValue **output);
gcsl_error_t	gcsl_pb_message_descriptor_get_field_by_name(const GN_PB_MessageDescriptor* desc, gcsl_cstr_t name, const GN_PB_FieldDescriptor** output);
gcsl_error_t	gcsl_pb_message_descriptor_get_field		(const GN_PB_MessageDescriptor* desc, gcsl_uint32_t value, const GN_PB_FieldDescriptor** output);

/* --- wire format enums --- */
typedef enum
{
	GN_PB_WIRE_TYPE_VARINT,
	GN_PB_WIRE_TYPE_64BIT,
	GN_PB_WIRE_TYPE_LENGTH_PREFIXED,
	GN_PB_WIRE_TYPE_START_GROUP,     /* unsupported */
	GN_PB_WIRE_TYPE_END_GROUP,       /* unsupported */
	GN_PB_WIRE_TYPE_32BIT
} GN_PB_WireType;

/* --- unknown message fields --- */
struct _GN_PB_MessageUnknownField
{
	gcsl_uint32_t		tag;
	GN_PB_WireType		wire_type;
	gcsl_size_t			len;
	gcsl_byte_t*		data;
};

/* ====== private ====== */

/* === stuff which needs to be declared for use in the generated code === */

struct _GN_PB_EnumValueIndex
{
	gcsl_cstr_t			name;
	gcsl_uint32_t		index;               /* into values[] array */
};

/* IntRange: helper structure for optimizing
	 gcsl_int32_t => index lookups
   in the case where the keys are mostly consecutive values,
   as they presumably are for enums and fields.

   The data structures assumes that the values in the original
   array are sorted */
struct _GN_PB_IntRange
{
	gcsl_int32_t		start_value;
	gcsl_uint32_t		orig_index;
	/* NOTE: the number of values in the range can
	   be inferred by looking at the next element's orig_index.
	   a dummy element is added to make this simple */
};


/* === declared for exposition on GN_PB_IntRange === */
/* note: ranges must have an extra sentinel IntRange at the end whose
   orig_index is set to the number of actual values in the original array */
/* returns -1 if no orig_index found */
gcsl_int32_t	gcsl_pb_int_ranges_lookup		(gcsl_uint32_t n_ranges, GN_PB_IntRange* ranges);

#define GN_PB_SERVICE_DESCRIPTOR_MAGIC  0x14159bc3
#define GN_PB_MESSAGE_DESCRIPTOR_MAGIC  0x28aaeef9
#define GN_PB_ENUM_DESCRIPTOR_MAGIC     0x114315af


#ifdef __cplusplus
}
#endif

#endif /* _GN_PB_RUNTIME_H_ */
