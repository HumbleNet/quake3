// CORE

/*** Start of inlined file: humblenet_core.cpp ***/

/*** Start of inlined file: humblenet.h ***/
#ifndef HUMBLENET_H
#define HUMBLENET_H

#include <stddef.h>
#include <stdint.h>

#ifdef HUMBLENET_STATIC
	#define HUMBLENET_DLL_EXPORT
#else
	#ifdef WIN32
		#ifdef HUMBLENET_DLL_BUILD
			#define HUMBLENET_DLL_EXPORT __declspec(dllexport)
		#else
			#define HUMBLENET_DLL_EXPORT __declspec(dllimport)
		#endif
	#else // GCC
		#if defined(__GNUC__) && __GNUC__ >= 4
		# define HUMBLENET_DLL_EXPORT __attribute__ ((visibility("default")))
		#else
		# define HUMBLENET_DLL_EXPORT
		#endif
	#endif
#endif

#if defined(WIN32)
	#define HUMBLENET_CALL __cdecl
#elif defined(__GNUC__)
	#if defined(__LP64__)
		#define HUMBLENET_CALL
	#else
		#define HUMBLENET_CALL __attribute__((cdecl))
	#endif
#else
	#define HUMBLENET_CALL
#endif

#define HUMBLENET_API HUMBLENET_DLL_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ha_bool;
typedef uint32_t PeerId;

/*
 * Initialize the core humblenet library
 */
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_init();

/*
 * Shutdown the entire humblenet library
 */
HUMBLENET_API void HUMBLENET_CALL humblenet_shutdown();

/*
 * Allow network polling to occur. This is already thread safe and must NOT be within a lock/unlock block
 */
HUMBLENET_API void HUMBLENET_CALL humblenet_poll(int ms);

/*
 * Get error string
 * Return value will stay valid until next call to humblenet_set_error
 * or humblenet_clear_error() is called
 */
HUMBLENET_API const char * HUMBLENET_CALL humblenet_get_error();

/*
 * Set error string
 * Parameter is copied to private storage
 * Must not be NULL
 */
HUMBLENET_API void HUMBLENET_CALL humblenet_set_error(const char *error);

/*
 * Clear error string
 */
HUMBLENET_API void HUMBLENET_CALL humblenet_clear_error();

/*
 * Set the value of a hint
 */
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_set_hint(const char* name, const char* value);

/*
 * Get the value of a hint
 */
HUMBLENET_API const char* HUMBLENET_CALL humblenet_get_hint(const char* name);

#ifdef __cplusplus
}
#endif

#endif /*HUMBLENET_H */

/*** End of inlined file: humblenet.h ***/


/*** Start of inlined file: humblenet_p2p.h ***/
#ifndef HUMBLENET_P2P_H
#define HUMBLENET_P2P_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SendMode {

	// Send the message reliably.
	SEND_RELIABLE = 0,

	// As above but buffers the data for more efficient packets transmission
	SEND_RELIABLE_BUFFERED = 1
} SendMode;

/*
* Is the peer-to-peer network supported on this platform.
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_supported();

/*
* Initialize the peer-to-peer library.
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_init(const char* server, const char* client_token, const char* client_secret, const char* auth_token);

/*
* Is the peer-to-peer network supported on this platform.
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_is_initialized();

/*
* Shut down the networking library
*/
HUMBLENET_API void HUMBLENET_CALL humblenet_p2p_shutdown();

/*
* Get the current peer ID of this client
* returns 0 if not yet connected
*/
HUMBLENET_API PeerId HUMBLENET_CALL humblenet_p2p_get_my_peer_id();

/*
* Register an alias for this peer so it can be found by name
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_register_alias(const char* name);

/*
 * Unregister an alias for this peer. Passing NULL will unpublish all aliases for the peer.
 */
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_unregister_alias(const char* name);

/*
 * Create a virtual peer for an alias on the server
 */
HUMBLENET_API PeerId HUMBLENET_CALL humblenet_p2p_virtual_peer_for_alias(const char* name);

/*
* Send a message to a peer.
*/
HUMBLENET_API int HUMBLENET_CALL humblenet_p2p_sendto(const void* message, uint32_t length, PeerId topeer, SendMode mode, uint8_t nChannel);

/*
* Test if a message is available on the specified channel.
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_peek(uint32_t* length, uint8_t nChannel);

/*
* Receive a message sent from a peer
*/
HUMBLENET_API int HUMBLENET_CALL humblenet_p2p_recvfrom(void* message, uint32_t length, PeerId* frompeer, uint8_t nChannel);

/*
* Disconnect a peer
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_disconnect(PeerId peer);

/*
* Wait for an IO event to occur
*/
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_p2p_wait(int ms);

#ifndef EMSCRIPTEN
/*
* POSIX compatible select use to wait on IO from either humblenet or use supplied fds
*/
HUMBLENET_API int HUMBLENET_CALL humblenet_p2p_select(int nfds, struct fd_set *readfds, struct fd_set *writefds,
													  struct fd_set *exceptfds, struct timeval *timeout);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HUMBLENET_P2P_H */

/*** End of inlined file: humblenet_p2p.h ***/


/*** Start of inlined file: humblenet_p2p_internal.h ***/
#ifndef HUMBLENET_P2P_INTERNAL
#define HUMBLENET_P2P_INTERNAL


/*** Start of inlined file: humblepeer.h ***/
#ifndef HUMBLEPEER_H
#define HUMBLEPEER_H

// HumbleNet internal, do not include

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>


/*** Start of inlined file: humblepeer_generated.h ***/
// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_HUMBLEPEER_HUMBLENET_HUMBLEPEER_H_
#define FLATBUFFERS_GENERATED_HUMBLEPEER_HUMBLENET_HUMBLEPEER_H_


/*** Start of inlined file: flatbuffers.h ***/
#ifndef FLATBUFFERS_H_
#define FLATBUFFERS_H_

#include <assert.h>

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>

/// @cond FLATBUFFERS_INTERNAL
#if __cplusplus <= 199711L && \
	(!defined(_MSC_VER) || _MSC_VER < 1600) && \
	(!defined(__GNUC__) || \
	  (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40400))
  #error A C++11 compatible compiler with support for the auto typing is required for FlatBuffers.
  #error __cplusplus _MSC_VER __GNUC__  __GNUC_MINOR__  __GNUC_PATCHLEVEL__
#endif

#if !defined(__clang__) && \
	defined(__GNUC__) && \
	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40600)
  // Backwards compatability for g++ 4.4, and 4.5 which don't have the nullptr and constexpr
  // keywords. Note the __clang__ check is needed, because clang presents itself as an older GNUC
  // compiler.
  #ifndef nullptr_t
	const class nullptr_t {
	public:
	  template<class T> inline operator T*() const { return 0; }
	private:
	  void operator&() const;
	} nullptr = {};
  #endif
  #ifndef constexpr
	#define constexpr const
  #endif
#endif

// The wire format uses a little endian encoding (since that's efficient for
// the common platforms).
#if !defined(FLATBUFFERS_LITTLEENDIAN)
  #if defined(__GNUC__) || defined(__clang__)
	#ifdef __BIG_ENDIAN__
	  #define FLATBUFFERS_LITTLEENDIAN 0
	#else
	  #define FLATBUFFERS_LITTLEENDIAN 1
	#endif // __BIG_ENDIAN__
  #elif defined(_MSC_VER)
	#if defined(_M_PPC)
	  #define FLATBUFFERS_LITTLEENDIAN 0
	#else
	  #define FLATBUFFERS_LITTLEENDIAN 1
	#endif
  #else
	#error Unable to determine endianness, define FLATBUFFERS_LITTLEENDIAN.
  #endif
#endif // !defined(FLATBUFFERS_LITTLEENDIAN)

#define FLATBUFFERS_VERSION_MAJOR 1
#define FLATBUFFERS_VERSION_MINOR 0
#define FLATBUFFERS_VERSION_REVISION 0
#define FLATBUFFERS_STRING_EXPAND(X) #X
#define FLATBUFFERS_STRING(X) FLATBUFFERS_STRING_EXPAND(X)

#if (!defined(_MSC_VER) || _MSC_VER > 1600) && \
	(!defined(__GNUC__) || (__GNUC__ * 100 + __GNUC_MINOR__ >= 407))
  #define FLATBUFFERS_FINAL_CLASS final
#else
  #define FLATBUFFERS_FINAL_CLASS
#endif
/// @endcond

/// @file
namespace flatbuffers {

/// @cond FLATBUFFERS_INTERNAL
// Our default offset / size type, 32bit on purpose on 64bit systems.
// Also, using a consistent offset type maintains compatibility of serialized
// offset values between 32bit and 64bit systems.
typedef uint32_t uoffset_t;

// Signed offsets for references that can go in both directions.
typedef int32_t soffset_t;

// Offset/index used in v-tables, can be changed to uint8_t in
// format forks to save a bit of space if desired.
typedef uint16_t voffset_t;

typedef uintmax_t largest_scalar_t;

// Pointer to relinquished memory.
typedef std::unique_ptr<uint8_t, std::function<void(uint8_t * /* unused */)>>
		  unique_ptr_t;

// Wrapper for uoffset_t to allow safe template specialization.
template<typename T> struct Offset {
  uoffset_t o;
  Offset() : o(0) {}
  Offset(uoffset_t _o) : o(_o) {}
  Offset<void> Union() const { return Offset<void>(o); }
};

inline void EndianCheck() {
  int endiantest = 1;
  // If this fails, see FLATBUFFERS_LITTLEENDIAN above.
  assert(*reinterpret_cast<char *>(&endiantest) == FLATBUFFERS_LITTLEENDIAN);
  (void)endiantest;
}

template<typename T> T EndianScalar(T t) {
  #if FLATBUFFERS_LITTLEENDIAN
	return t;
  #else
	#if defined(_MSC_VER)
	  #pragma push_macro("__builtin_bswap16")
	  #pragma push_macro("__builtin_bswap32")
	  #pragma push_macro("__builtin_bswap64")
	  #define __builtin_bswap16 _byteswap_ushort
	  #define __builtin_bswap32 _byteswap_ulong
	  #define __builtin_bswap64 _byteswap_uint64
	#endif
	// If you're on the few remaining big endian platforms, we make the bold
	// assumption you're also on gcc/clang, and thus have bswap intrinsics:
	if (sizeof(T) == 1) {   // Compile-time if-then's.
	  return t;
	} else if (sizeof(T) == 2) {
	  auto r = __builtin_bswap16(*reinterpret_cast<uint16_t *>(&t));
	  return *reinterpret_cast<T *>(&r);
	} else if (sizeof(T) == 4) {
	  auto r = __builtin_bswap32(*reinterpret_cast<uint32_t *>(&t));
	  return *reinterpret_cast<T *>(&r);
	} else if (sizeof(T) == 8) {
	  auto r = __builtin_bswap64(*reinterpret_cast<uint64_t *>(&t));
	  return *reinterpret_cast<T *>(&r);
	} else {
	  assert(0);
	}
	#if defined(_MSC_VER)
	  #pragma pop_macro("__builtin_bswap16")
	  #pragma pop_macro("__builtin_bswap32")
	  #pragma pop_macro("__builtin_bswap64")
	#endif
  #endif
}

template<typename T> T ReadScalar(const void *p) {
  return EndianScalar(*reinterpret_cast<const T *>(p));
}

template<typename T> void WriteScalar(void *p, T t) {
  *reinterpret_cast<T *>(p) = EndianScalar(t);
}

template<typename T> size_t AlignOf() {
  #ifdef _MSC_VER
	return __alignof(T);
  #else
	#ifndef alignof
	  return __alignof__(T);
	#else
	  return alignof(T);
	#endif
  #endif
}

// When we read serialized data from memory, in the case of most scalars,
// we want to just read T, but in the case of Offset, we want to actually
// perform the indirection and return a pointer.
// The template specialization below does just that.
// It is wrapped in a struct since function templates can't overload on the
// return type like this.
// The typedef is for the convenience of callers of this function
// (avoiding the need for a trailing return decltype)
template<typename T> struct IndirectHelper {
  typedef T return_type;
  static const size_t element_stride = sizeof(T);
  static return_type Read(const uint8_t *p, uoffset_t i) {
	return EndianScalar((reinterpret_cast<const T *>(p))[i]);
  }
};
template<typename T> struct IndirectHelper<Offset<T>> {
  typedef const T *return_type;
  static const size_t element_stride = sizeof(uoffset_t);
  static return_type Read(const uint8_t *p, uoffset_t i) {
	p += i * sizeof(uoffset_t);
	return reinterpret_cast<return_type>(p + ReadScalar<uoffset_t>(p));
  }
};
template<typename T> struct IndirectHelper<const T *> {
  typedef const T *return_type;
  static const size_t element_stride = sizeof(T);
  static return_type Read(const uint8_t *p, uoffset_t i) {
	return reinterpret_cast<const T *>(p + i * sizeof(T));
  }
};

// An STL compatible iterator implementation for Vector below, effectively
// calling Get() for every element.
template<typename T, bool bConst>
struct VectorIterator : public
  std::iterator < std::input_iterator_tag,
  typename std::conditional < bConst,
  const typename IndirectHelper<T>::return_type,
  typename IndirectHelper<T>::return_type > ::type, uoffset_t > {

  typedef std::iterator<std::input_iterator_tag,
	typename std::conditional<bConst,
	const typename IndirectHelper<T>::return_type,
	typename IndirectHelper<T>::return_type>::type, uoffset_t> super_type;

public:
  VectorIterator(const uint8_t *data, uoffset_t i) :
	  data_(data + IndirectHelper<T>::element_stride * i) {};
  VectorIterator(const VectorIterator &other) : data_(other.data_) {}
  VectorIterator(VectorIterator &&other) : data_(std::move(other.data_)) {}

  VectorIterator &operator=(const VectorIterator &other) {
	data_ = other.data_;
	return *this;
  }

  VectorIterator &operator=(VectorIterator &&other) {
	data_ = other.data_;
	return *this;
  }

  bool operator==(const VectorIterator& other) const {
	return data_ == other.data_;
  }

  bool operator!=(const VectorIterator& other) const {
	return data_ != other.data_;
  }

  ptrdiff_t operator-(const VectorIterator& other) const {
	return (data_ - other.data_) / IndirectHelper<T>::element_stride;
  }

  typename super_type::value_type operator *() const {
	return IndirectHelper<T>::Read(data_, 0);
  }

  typename super_type::value_type operator->() const {
	return IndirectHelper<T>::Read(data_, 0);
  }

  VectorIterator &operator++() {
	data_ += IndirectHelper<T>::element_stride;
	return *this;
  }

  VectorIterator operator++(int) {
	VectorIterator temp(data_);
	data_ += IndirectHelper<T>::element_stride;
	return temp;
  }

private:
  const uint8_t *data_;
};

// This is used as a helper type for accessing vectors.
// Vector::data() assumes the vector elements start after the length field.
template<typename T> class Vector {
public:
  typedef VectorIterator<T, false> iterator;
  typedef VectorIterator<T, true> const_iterator;

  uoffset_t size() const { return EndianScalar(length_); }

  // Deprecated: use size(). Here for backwards compatibility.
  uoffset_t Length() const { return size(); }

  typedef typename IndirectHelper<T>::return_type return_type;

  return_type Get(uoffset_t i) const {
	assert(i < size());
	return IndirectHelper<T>::Read(Data(), i);
  }

  return_type operator[](uoffset_t i) const { return Get(i); }

  // If this is a Vector of enums, T will be its storage type, not the enum
  // type. This function makes it convenient to retrieve value with enum
  // type E.
  template<typename E> E GetEnum(uoffset_t i) const {
	return static_cast<E>(Get(i));
  }

  const void *GetStructFromOffset(size_t o) const {
	return reinterpret_cast<const void *>(Data() + o);
  }

  iterator begin() { return iterator(Data(), 0); }
  const_iterator begin() const { return const_iterator(Data(), 0); }

  iterator end() { return iterator(Data(), size()); }
  const_iterator end() const { return const_iterator(Data(), size()); }

  // Change elements if you have a non-const pointer to this object.
  // Scalars only. See reflection.h, and the documentation.
  void Mutate(uoffset_t i, T val) {
	assert(i < size());
	WriteScalar(data() + i, val);
  }

  // Change an element of a vector of tables (or strings).
  // "val" points to the new table/string, as you can obtain from
  // e.g. reflection::AddFlatBuffer().
  void MutateOffset(uoffset_t i, const uint8_t *val) {
	assert(i < size());
	assert(sizeof(T) == sizeof(uoffset_t));
	WriteScalar(data() + i, val - (Data() + i * sizeof(uoffset_t)));
  }

  // The raw data in little endian format. Use with care.
  const uint8_t *Data() const {
	return reinterpret_cast<const uint8_t *>(&length_ + 1);
  }

  uint8_t *Data() {
	return reinterpret_cast<uint8_t *>(&length_ + 1);
  }

  // Similarly, but typed, much like std::vector::data
  const T *data() const { return reinterpret_cast<const T *>(Data()); }
  T *data() { return reinterpret_cast<T *>(Data()); }

  template<typename K> return_type LookupByKey(K key) const {
	void *search_result = std::bsearch(&key, Data(), size(),
		IndirectHelper<T>::element_stride, KeyCompare<K>);

	if (!search_result) {
	  return nullptr;  // Key not found.
	}

	const uint8_t *element = reinterpret_cast<const uint8_t *>(search_result);

	return IndirectHelper<T>::Read(element, 0);
  }

protected:
  // This class is only used to access pre-existing data. Don't ever
  // try to construct these manually.
  Vector();

  uoffset_t length_;

private:
  template<typename K> static int KeyCompare(const void *ap, const void *bp) {
	const K *key = reinterpret_cast<const K *>(ap);
	const uint8_t *data = reinterpret_cast<const uint8_t *>(bp);
	auto table = IndirectHelper<T>::Read(data, 0);

	// std::bsearch compares with the operands transposed, so we negate the
	// result here.
	return -table->KeyCompareWithValue(*key);
  }
};

// Represent a vector much like the template above, but in this case we
// don't know what the element types are (used with reflection.h).
class VectorOfAny {
public:
  uoffset_t size() const { return EndianScalar(length_); }

  const uint8_t *Data() const {
	return reinterpret_cast<const uint8_t *>(&length_ + 1);
  }
  uint8_t *Data() {
	return reinterpret_cast<uint8_t *>(&length_ + 1);
  }
protected:
  VectorOfAny();

  uoffset_t length_;
};

// Convenient helper function to get the length of any vector, regardless
// of wether it is null or not (the field is not set).
template<typename T> static inline size_t VectorLength(const Vector<T> *v) {
  return v ? v->Length() : 0;
}

struct String : public Vector<char> {
  const char *c_str() const { return reinterpret_cast<const char *>(Data()); }
  std::string str() const { return std::string(c_str(), Length()); }

  bool operator <(const String &o) const {
	return strcmp(c_str(), o.c_str()) < 0;
  }
};

// Simple indirection for buffer allocation, to allow this to be overridden
// with custom allocation (see the FlatBufferBuilder constructor).
class simple_allocator {
 public:
  virtual ~simple_allocator() {}
  virtual uint8_t *allocate(size_t size) const { return new uint8_t[size]; }
  virtual void deallocate(uint8_t *p) const { delete[] p; }
};

// This is a minimal replication of std::vector<uint8_t> functionality,
// except growing from higher to lower addresses. i.e push_back() inserts data
// in the lowest address in the vector.
class vector_downward {
 public:
  explicit vector_downward(size_t initial_size,
						   const simple_allocator &allocator)
	: reserved_(initial_size),
	  buf_(allocator.allocate(reserved_)),
	  cur_(buf_ + reserved_),
	  allocator_(allocator) {
	assert((initial_size & (sizeof(largest_scalar_t) - 1)) == 0);
  }

  ~vector_downward() {
	if (buf_)
	  allocator_.deallocate(buf_);
  }

  void clear() {
	if (buf_ == nullptr)
	  buf_ = allocator_.allocate(reserved_);

	cur_ = buf_ + reserved_;
  }

  // Relinquish the pointer to the caller.
  unique_ptr_t release() {
	// Actually deallocate from the start of the allocated memory.
	std::function<void(uint8_t *)> deleter(
	  std::bind(&simple_allocator::deallocate, allocator_, buf_));

	// Point to the desired offset.
	unique_ptr_t retval(data(), deleter);

	// Don't deallocate when this instance is destroyed.
	buf_ = nullptr;
	cur_ = nullptr;

	return retval;
  }

  size_t growth_policy(size_t bytes) {
	return (bytes / 2) & ~(sizeof(largest_scalar_t) - 1);
  }

  uint8_t *make_space(size_t len) {
	if (len > static_cast<size_t>(cur_ - buf_)) {
	  auto old_size = size();
	  auto largest_align = AlignOf<largest_scalar_t>();
	  reserved_ += (std::max)(len, growth_policy(reserved_));
	  // Round up to avoid undefined behavior from unaligned loads and stores.
	  reserved_ = (reserved_ + (largest_align - 1)) & ~(largest_align - 1);
	  auto new_buf = allocator_.allocate(reserved_);
	  auto new_cur = new_buf + reserved_ - old_size;
	  memcpy(new_cur, cur_, old_size);
	  cur_ = new_cur;
	  allocator_.deallocate(buf_);
	  buf_ = new_buf;
	}
	cur_ -= len;
	// Beyond this, signed offsets may not have enough range:
	// (FlatBuffers > 2GB not supported).
	assert(size() < (1UL << (sizeof(soffset_t) * 8 - 1)) - 1);
	return cur_;
  }

  uoffset_t size() const {
	assert(cur_ != nullptr && buf_ != nullptr);
	return static_cast<uoffset_t>(reserved_ - (cur_ - buf_));
  }

  uint8_t *data() const {
	assert(cur_ != nullptr);
	return cur_;
  }

  uint8_t *data_at(size_t offset) const { return buf_ + reserved_ - offset; }

  // push() & fill() are most frequently called with small byte counts (<= 4),
  // which is why we're using loops rather than calling memcpy/memset.
  void push(const uint8_t *bytes, size_t num) {
	auto dest = make_space(num);
	for (size_t i = 0; i < num; i++) dest[i] = bytes[i];
  }

  void fill(size_t zero_pad_bytes) {
	auto dest = make_space(zero_pad_bytes);
	for (size_t i = 0; i < zero_pad_bytes; i++) dest[i] = 0;
  }

  void pop(size_t bytes_to_remove) { cur_ += bytes_to_remove; }

 private:
  // You shouldn't really be copying instances of this class.
  vector_downward(const vector_downward &);
  vector_downward &operator=(const vector_downward &);

  size_t reserved_;
  uint8_t *buf_;
  uint8_t *cur_;  // Points at location between empty (below) and used (above).
  const simple_allocator &allocator_;
};

// Converts a Field ID to a virtual table offset.
inline voffset_t FieldIndexToOffset(voffset_t field_id) {
  // Should correspond to what EndTable() below builds up.
  const int fixed_fields = 2;  // Vtable size and Object Size.
  return (field_id + fixed_fields) * sizeof(voffset_t);
}

// Computes how many bytes you'd have to pad to be able to write an
// "scalar_size" scalar if the buffer had grown to "buf_size" (downwards in
// memory).
inline size_t PaddingBytes(size_t buf_size, size_t scalar_size) {
  return ((~buf_size) + 1) & (scalar_size - 1);
}
/// @endcond

/// @addtogroup flatbuffers_cpp_api
/// @{
/// @class FlatBufferBuilder
/// @brief Helper class to hold data needed in creation of a FlatBuffer.
/// To serialize data, you typically call one of the `Create*()` functions in
/// the generated code, which in turn call a sequence of `StartTable`/
/// `PushElement`/`AddElement`/`EndTable`, or the builtin `CreateString`/
/// `CreateVector` functions. Do this is depth-first order to build up a tree to
/// the root. `Finish()` wraps up the buffer ready for transport.
class FlatBufferBuilder
/// @cond FLATBUFFERS_INTERNAL
FLATBUFFERS_FINAL_CLASS
/// @endcond
{
 public:
  /// @brief Default constructor for FlatBufferBuilder.
  /// @param[in] initial_size The initial size of the buffer, in bytes. Defaults
  /// to`1024`.
  /// @param[in] allocator A pointer to the `simple_allocator` that should be
  /// used. Defaults to `nullptr`, which means the `default_allocator` will be
  /// be used.
  explicit FlatBufferBuilder(uoffset_t initial_size = 1024,
							 const simple_allocator *allocator = nullptr)
	  : buf_(initial_size, allocator ? *allocator : default_allocator),
		nested(false), finished(false), minalign_(1), force_defaults_(false),
		string_pool(nullptr) {
	offsetbuf_.reserve(16);  // Avoid first few reallocs.
	vtables_.reserve(16);
	EndianCheck();
  }

  ~FlatBufferBuilder() {
	if (string_pool) delete string_pool;
  }

  /// @brief Reset all the state in this FlatBufferBuilder so it can be reused
  /// to construct another buffer.
  void Clear() {
	buf_.clear();
	offsetbuf_.clear();
	nested = false;
	finished = false;
	vtables_.clear();
	minalign_ = 1;
	if (string_pool) string_pool->clear();
  }

  /// @brief The current size of the serialized buffer, counting from the end.
  /// @return Returns an `uoffset_t` with the current size of the buffer.
  uoffset_t GetSize() const { return buf_.size(); }

  /// @brief Get the serialized buffer (after you call `Finish()`).
  /// @return Returns an `uint8_t` pointer to the FlatBuffer data inside the
  /// buffer.
  uint8_t *GetBufferPointer() const {
	Finished();
	return buf_.data();
  }

  /// @brief Get a pointer to an unfinished buffer.
  /// @return Returns a `uint8_t` pointer to the unfinished buffer.
  uint8_t *GetCurrentBufferPointer() const { return buf_.data(); }

  /// @brief Get the released pointer to the serialized buffer.
  /// @warning Do NOT attempt to use this FlatBufferBuilder afterwards!
  /// @return The `unique_ptr` returned has a special allocator that knows how
  /// to deallocate this pointer (since it points to the middle of an
  /// allocation). Thus, do not mix this pointer with other `unique_ptr`'s, or
  /// call `release()`/`reset()` on it.
  unique_ptr_t ReleaseBufferPointer() {
	Finished();
	return buf_.release();
  }

  /// @cond FLATBUFFERS_INTERNAL
  void Finished() const {
	// If you get this assert, you're attempting to get access a buffer
	// which hasn't been finished yet. Be sure to call
	// FlatBufferBuilder::Finish with your root table.
	// If you really need to access an unfinished buffer, call
	// GetCurrentBufferPointer instead.
	assert(finished);
  }
  /// @endcond

  /// @brief In order to save space, fields that are set to their default value
  /// don't get serialized into the buffer.
  /// @param[in] bool fd When set to `true`, always serializes default values.
  void ForceDefaults(bool fd) { force_defaults_ = fd; }

  /// @cond FLATBUFFERS_INTERNAL
  void Pad(size_t num_bytes) { buf_.fill(num_bytes); }

  void Align(size_t elem_size) {
	if (elem_size > minalign_) minalign_ = elem_size;
	buf_.fill(PaddingBytes(buf_.size(), elem_size));
  }

  void PushFlatBuffer(const uint8_t *bytes, size_t size) {
	PushBytes(bytes, size);
	finished = true;
  }

  void PushBytes(const uint8_t *bytes, size_t size) {
	buf_.push(bytes, size);
  }

  void PopBytes(size_t amount) { buf_.pop(amount); }

  template<typename T> void AssertScalarT() {
	// The code assumes power of 2 sizes and endian-swap-ability.
	static_assert(std::is_scalar<T>::value
		// The Offset<T> type is essentially a scalar but fails is_scalar.
		|| sizeof(T) == sizeof(Offset<void>),
		   "T must be a scalar type");
  }

  // Write a single aligned scalar to the buffer
  template<typename T> uoffset_t PushElement(T element) {
	AssertScalarT<T>();
	T litle_endian_element = EndianScalar(element);
	Align(sizeof(T));
	PushBytes(reinterpret_cast<uint8_t *>(&litle_endian_element), sizeof(T));
	return GetSize();
  }

  template<typename T> uoffset_t PushElement(Offset<T> off) {
	// Special case for offsets: see ReferTo below.
	return PushElement(ReferTo(off.o));
  }

  // When writing fields, we track where they are, so we can create correct
  // vtables later.
  void TrackField(voffset_t field, uoffset_t off) {
	FieldLoc fl = { off, field };
	offsetbuf_.push_back(fl);
  }

  // Like PushElement, but additionally tracks the field this represents.
  template<typename T> void AddElement(voffset_t field, T e, T def) {
	// We don't serialize values equal to the default.
	if (e == def && !force_defaults_) return;
	auto off = PushElement(e);
	TrackField(field, off);
  }

  template<typename T> void AddOffset(voffset_t field, Offset<T> off) {
	if (!off.o) return;  // An offset of 0 means NULL, don't store.
	AddElement(field, ReferTo(off.o), static_cast<uoffset_t>(0));
  }

  template<typename T> void AddStruct(voffset_t field, const T *structptr) {
	if (!structptr) return;  // Default, don't store.
	Align(AlignOf<T>());
	PushBytes(reinterpret_cast<const uint8_t *>(structptr), sizeof(T));
	TrackField(field, GetSize());
  }

  void AddStructOffset(voffset_t field, uoffset_t off) {
	TrackField(field, off);
  }

  // Offsets initially are relative to the end of the buffer (downwards).
  // This function converts them to be relative to the current location
  // in the buffer (when stored here), pointing upwards.
  uoffset_t ReferTo(uoffset_t off) {
	// Align to ensure GetSize() below is correct.
	Align(sizeof(uoffset_t));
	// Offset must refer to something already in buffer.
	assert(off && off <= GetSize());
	return GetSize() - off + sizeof(uoffset_t);
  }

  void NotNested() {
	// If you hit this, you're trying to construct a Table/Vector/String
	// during the construction of its parent table (between the MyTableBuilder
	// and table.Finish().
	// Move the creation of these sub-objects to above the MyTableBuilder to
	// not get this assert.
	// Ignoring this assert may appear to work in simple cases, but the reason
	// it is here is that storing objects in-line may cause vtable offsets
	// to not fit anymore. It also leads to vtable duplication.
	assert(!nested);
  }

  // From generated code (or from the parser), we call StartTable/EndTable
  // with a sequence of AddElement calls in between.
  uoffset_t StartTable() {
	NotNested();
	nested = true;
	return GetSize();
  }

  // This finishes one serialized object by generating the vtable if it's a
  // table, comparing it against existing vtables, and writing the
  // resulting vtable offset.
  uoffset_t EndTable(uoffset_t start, voffset_t numfields) {
	// If you get this assert, a corresponding StartTable wasn't called.
	assert(nested);
	// Write the vtable offset, which is the start of any Table.
	// We fill it's value later.
	auto vtableoffsetloc = PushElement<soffset_t>(0);
	// Write a vtable, which consists entirely of voffset_t elements.
	// It starts with the number of offsets, followed by a type id, followed
	// by the offsets themselves. In reverse:
	buf_.fill(numfields * sizeof(voffset_t));
	auto table_object_size = vtableoffsetloc - start;
	assert(table_object_size < 0x10000);  // Vtable use 16bit offsets.
	PushElement<voffset_t>(static_cast<voffset_t>(table_object_size));
	PushElement<voffset_t>(FieldIndexToOffset(numfields));
	// Write the offsets into the table
	for (auto field_location = offsetbuf_.begin();
			  field_location != offsetbuf_.end();
			++field_location) {
	  auto pos = static_cast<voffset_t>(vtableoffsetloc - field_location->off);
	  // If this asserts, it means you've set a field twice.
	  assert(!ReadScalar<voffset_t>(buf_.data() + field_location->id));
	  WriteScalar<voffset_t>(buf_.data() + field_location->id, pos);
	}
	offsetbuf_.clear();
	auto vt1 = reinterpret_cast<voffset_t *>(buf_.data());
	auto vt1_size = ReadScalar<voffset_t>(vt1);
	auto vt_use = GetSize();
	// See if we already have generated a vtable with this exact same
	// layout before. If so, make it point to the old one, remove this one.
	for (auto it = vtables_.begin(); it != vtables_.end(); ++it) {
	  auto vt2 = reinterpret_cast<voffset_t *>(buf_.data_at(*it));
	  auto vt2_size = *vt2;
	  if (vt1_size != vt2_size || memcmp(vt2, vt1, vt1_size)) continue;
	  vt_use = *it;
	  buf_.pop(GetSize() - vtableoffsetloc);
	  break;
	}
	// If this is a new vtable, remember it.
	if (vt_use == GetSize()) {
	  vtables_.push_back(vt_use);
	}
	// Fill the vtable offset we created above.
	// The offset points from the beginning of the object to where the
	// vtable is stored.
	// Offsets default direction is downward in memory for future format
	// flexibility (storing all vtables at the start of the file).
	WriteScalar(buf_.data_at(vtableoffsetloc),
				static_cast<soffset_t>(vt_use) -
				  static_cast<soffset_t>(vtableoffsetloc));

	nested = false;
	return vtableoffsetloc;
  }

  // This checks a required field has been set in a given table that has
  // just been constructed.
  template<typename T> void Required(Offset<T> table, voffset_t field) {
	auto table_ptr = buf_.data_at(table.o);
	auto vtable_ptr = table_ptr - ReadScalar<soffset_t>(table_ptr);
	bool ok = ReadScalar<voffset_t>(vtable_ptr + field) != 0;
	// If this fails, the caller will show what field needs to be set.
	assert(ok);
	(void)ok;
  }

  uoffset_t StartStruct(size_t alignment) {
	Align(alignment);
	return GetSize();
  }

  uoffset_t EndStruct() { return GetSize(); }

  void ClearOffsets() { offsetbuf_.clear(); }

  // Aligns such that when "len" bytes are written, an object can be written
  // after it with "alignment" without padding.
  void PreAlign(size_t len, size_t alignment) {
	buf_.fill(PaddingBytes(GetSize() + len, alignment));
  }
  template<typename T> void PreAlign(size_t len) {
	AssertScalarT<T>();
	PreAlign(len, sizeof(T));
  }
  /// @endcond

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// @param[in] str A const char pointer to the data to be stored as a string.
  /// @param[in] len The number of bytes that should be stored from `str`.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateString(const char *str, size_t len) {
	NotNested();
	PreAlign<uoffset_t>(len + 1);  // Always 0-terminated.
	buf_.fill(1);
	PushBytes(reinterpret_cast<const uint8_t *>(str), len);
	PushElement(static_cast<uoffset_t>(len));
	return Offset<String>(GetSize());
  }

  /// @brief Store a string in the buffer, which is null-terminated.
  /// @param[in] str A const char pointer to a C-string to add to the buffer.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateString(const char *str) {
	return CreateString(str, strlen(str));
  }

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// @param[in] str A const reference to a std::string to store in the buffer.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateString(const std::string &str) {
	return CreateString(str.c_str(), str.length());
  }

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// @param[in] str A const pointer to a `String` struct to add to the buffer.
  /// @return Returns the offset in the buffer where the string starts
  Offset<String> CreateString(const String *str) {
	return CreateString(str->c_str(), str->Length());
  }

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// If a string with this exact contents has already been serialized before,
  /// instead simply returns the offset of the existing string.
  /// @param[in] str A const char pointer to the data to be stored as a string.
  /// @param[in] len The number of bytes that should be stored from `str`.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateSharedString(const char *str, size_t len) {
	if (!string_pool)
	  string_pool = new StringOffsetMap(StringOffsetCompare(buf_));
	auto size_before_string = buf_.size();
	// Must first serialize the string, since the set is all offsets into
	// buffer.
	auto off = CreateString(str, len);
	auto it = string_pool->find(off);
	// If it exists we reuse existing serialized data!
	if (it != string_pool->end()) {
	  // We can remove the string we serialized.
	  buf_.pop(buf_.size() - size_before_string);
	  return *it;
	}
	// Record this string for future use.
	string_pool->insert(off);
	return off;
  }

  /// @brief Store a string in the buffer, which null-terminated.
  /// If a string with this exact contents has already been serialized before,
  /// instead simply returns the offset of the existing string.
  /// @param[in] str A const char pointer to a C-string to add to the buffer.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateSharedString(const char *str) {
	return CreateSharedString(str, strlen(str));
  }

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// If a string with this exact contents has already been serialized before,
  /// instead simply returns the offset of the existing string.
  /// @param[in] str A const reference to a std::string to store in the buffer.
  /// @return Returns the offset in the buffer where the string starts.
  Offset<String> CreateSharedString(const std::string &str) {
	return CreateSharedString(str.c_str(), str.length());
  }

  /// @brief Store a string in the buffer, which can contain any binary data.
  /// If a string with this exact contents has already been serialized before,
  /// instead simply returns the offset of the existing string.
  /// @param[in] str A const pointer to a `String` struct to add to the buffer.
  /// @return Returns the offset in the buffer where the string starts
  Offset<String> CreateSharedString(const String *str) {
	return CreateSharedString(str->c_str(), str->Length());
  }

  /// @cond FLATBUFFERS_INTERNAL
  uoffset_t EndVector(size_t len) {
	assert(nested);  // Hit if no corresponding StartVector.
	nested = false;
	return PushElement(static_cast<uoffset_t>(len));
  }

  void StartVector(size_t len, size_t elemsize) {
	NotNested();
	nested = true;
	PreAlign<uoffset_t>(len * elemsize);
	PreAlign(len * elemsize, elemsize);  // Just in case elemsize > uoffset_t.
  }

  // Call this right before StartVector/CreateVector if you want to force the
  // alignment to be something different than what the element size would
  // normally dictate.
  // This is useful when storing a nested_flatbuffer in a vector of bytes,
  // or when storing SIMD floats, etc.
  void ForceVectorAlignment(size_t len, size_t elemsize, size_t alignment) {
	PreAlign(len * elemsize, alignment);
  }

  uint8_t *ReserveElements(size_t len, size_t elemsize) {
	return buf_.make_space(len * elemsize);
  }
  /// @endcond

  /// @brief Serialize an array into a FlatBuffer `vector`.
  /// @tparam T The data type of the array elements.
  /// @param[in] v A pointer to the array of type `T` to serialize into the
  /// buffer as a `vector`.
  /// @param[in] len The number of elements to serialize.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<T>> CreateVector(const T *v, size_t len) {
	StartVector(len, sizeof(T));
	for (auto i = len; i > 0; ) {
	  PushElement(v[--i]);
	}
	return Offset<Vector<T>>(EndVector(len));
  }

  /// @brief Serialize a `std::vector` into a FlatBuffer `vector`.
  /// @tparam T The data type of the `std::vector` elements.
  /// @param v A const reference to the `std::vector` to serialize into the
  /// buffer as a `vector`.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<T>> CreateVector(const std::vector<T> &v) {
	return CreateVector(v.data(), v.size());
  }

  /// @brief Serialize an array of structs into a FlatBuffer `vector`.
  /// @tparam T The data type of the struct array elements.
  /// @param[in] v A pointer to the array of type `T` to serialize into the
  /// buffer as a `vector`.
  /// @param[in] len The number of elements to serialize.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<const T *>> CreateVectorOfStructs(
													   const T *v, size_t len) {
	StartVector(len * sizeof(T) / AlignOf<T>(), AlignOf<T>());
	PushBytes(reinterpret_cast<const uint8_t *>(v), sizeof(T) * len);
	return Offset<Vector<const T *>>(EndVector(len));
  }

  /// @brief Serialize a `std::vector` of structs into a FlatBuffer `vector`.
  /// @tparam T The data type of the `std::vector` struct elements.
  /// @param[in]] v A const reference to the `std::vector` of structs to
  /// serialize into the buffer as a `vector`.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<const T *>> CreateVectorOfStructs(
													  const std::vector<T> &v) {
	return CreateVectorOfStructs(v.data(), v.size());
  }

  /// @cond FLATBUFFERS_INTERNAL
  template<typename T>
  struct TableKeyComparator {
  TableKeyComparator(vector_downward& buf) : buf_(buf) {}
	bool operator()(const Offset<T> &a, const Offset<T> &b) const {
	  auto table_a = reinterpret_cast<T *>(buf_.data_at(a.o));
	  auto table_b = reinterpret_cast<T *>(buf_.data_at(b.o));
	  return table_a->KeyCompareLessThan(table_b);
	}
	vector_downward& buf_;

  private:
	TableKeyComparator& operator= (const TableKeyComparator&);
  };
  /// @endcond

  /// @brief Serialize an array of `table` offsets as a `vector` in the buffer
  /// in sorted order.
  /// @tparam T The data type that the offset refers to.
  /// @param[in] v An array of type `Offset<T>` that contains the `table`
  /// offsets to store in the buffer in sorted order.
  /// @param[in] len The number of elements to store in the `vector`.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<Offset<T>>> CreateVectorOfSortedTables(
													 Offset<T> *v, size_t len) {
	std::sort(v, v + len, TableKeyComparator<T>(buf_));
	return CreateVector(v, len);
  }

  /// @brief Serialize an array of `table` offsets as a `vector` in the buffer
  /// in sorted order.
  /// @tparam T The data type that the offset refers to.
  /// @param[in] v An array of type `Offset<T>` that contains the `table`
  /// offsets to store in the buffer in sorted order.
  /// @return Returns a typed `Offset` into the serialized data indicating
  /// where the vector is stored.
  template<typename T> Offset<Vector<Offset<T>>> CreateVectorOfSortedTables(
													std::vector<Offset<T>> *v) {
	return CreateVectorOfSortedTables(v->data(), v->size());
  }

  /// @brief Specialized version of `CreateVector` for non-copying use cases.
  /// Write the data any time later to the returned buffer pointer `buf`.
  /// @param[in] len The number of elements to store in the `vector`.
  /// @param[in] elemsize The size of each element in the `vector`.
  /// @param[out] buf A pointer to a `uint8_t` pointer that can be
  /// written to at a later time to serialize the data into a `vector`
  /// in the buffer.
  uoffset_t CreateUninitializedVector(size_t len, size_t elemsize,
									  uint8_t **buf) {
	NotNested();
	StartVector(len, elemsize);
	*buf = buf_.make_space(len * elemsize);
	return EndVector(len);
  }

  /// @brief Specialized version of `CreateVector` for non-copying use cases.
  /// Write the data any time later to the returned buffer pointer `buf`.
  /// @tparam T The data type of the data that will be stored in the buffer
  /// as a `vector`.
  /// @param[in] len The number of elements to store in the `vector`.
  /// @param[out] buf A pointer to a pointer of type `T` that can be
  /// written to at a later time to serialize the data into a `vector`
  /// in the buffer.
  template<typename T> Offset<Vector<T>> CreateUninitializedVector(
													size_t len, T **buf) {
	return CreateUninitializedVector(len, sizeof(T),
									 reinterpret_cast<uint8_t **>(buf));
  }

  /// @brief The length of a FlatBuffer file header.
  static const size_t kFileIdentifierLength = 4;

  /// @brief Finish serializing a buffer by writing the root offset.
  /// @param[in] file_identifier If a `file_identifier` is given, the buffer
  /// will be prefixed with a standard FlatBuffers file header.
  template<typename T> void Finish(Offset<T> root,
								   const char *file_identifier = nullptr) {
	NotNested();
	// This will cause the whole buffer to be aligned.
	PreAlign(sizeof(uoffset_t) + (file_identifier ? kFileIdentifierLength : 0),
			 minalign_);
	if (file_identifier) {
	  assert(strlen(file_identifier) == kFileIdentifierLength);
	  buf_.push(reinterpret_cast<const uint8_t *>(file_identifier),
				kFileIdentifierLength);
	}
	PushElement(ReferTo(root.o));  // Location of root.
	finished = true;
  }

 private:
  // You shouldn't really be copying instances of this class.
  FlatBufferBuilder(const FlatBufferBuilder &);
  FlatBufferBuilder &operator=(const FlatBufferBuilder &);

  struct FieldLoc {
	uoffset_t off;
	voffset_t id;
  };

  simple_allocator default_allocator;

  vector_downward buf_;

  // Accumulating offsets of table members while it is being built.
  std::vector<FieldLoc> offsetbuf_;

  // Ensure objects are not nested.
  bool nested;

  // Ensure the buffer is finished before it is being accessed.
  bool finished;

  std::vector<uoffset_t> vtables_;  // todo: Could make this into a map?

  size_t minalign_;

  bool force_defaults_;  // Serialize values equal to their defaults anyway.

  struct StringOffsetCompare {
	StringOffsetCompare(const vector_downward &buf) : buf_(buf) {}
	bool operator() (const Offset<String> &a, const Offset<String> &b) const {
	  auto stra = reinterpret_cast<const String *>(buf_.data_at(a.o));
	  auto strb = reinterpret_cast<const String *>(buf_.data_at(b.o));
	  return strncmp(stra->c_str(), strb->c_str(),
					 std::min(stra->size(), strb->size()) + 1) < 0;
	}
	const vector_downward &buf_;
  };

  // For use with CreateSharedString. Instantiated on first use only.
  typedef std::set<Offset<String>, StringOffsetCompare> StringOffsetMap;
  StringOffsetMap *string_pool;
};
/// @}

/// @cond FLATBUFFERS_INTERNAL
// Helpers to get a typed pointer to the root object contained in the buffer.
template<typename T> T *GetMutableRoot(void *buf) {
  EndianCheck();
  return reinterpret_cast<T *>(reinterpret_cast<uint8_t *>(buf) +
	EndianScalar(*reinterpret_cast<uoffset_t *>(buf)));
}

template<typename T> const T *GetRoot(const void *buf) {
  return GetMutableRoot<T>(const_cast<void *>(buf));
}

// Helper to see if the identifier in a buffer has the expected value.
inline bool BufferHasIdentifier(const void *buf, const char *identifier) {
  return strncmp(reinterpret_cast<const char *>(buf) + sizeof(uoffset_t),
				 identifier, FlatBufferBuilder::kFileIdentifierLength) == 0;
}

// Helper class to verify the integrity of a FlatBuffer
class Verifier FLATBUFFERS_FINAL_CLASS {
 public:
  Verifier(const uint8_t *buf, size_t buf_len, size_t _max_depth = 64,
		   size_t _max_tables = 1000000)
	: buf_(buf), end_(buf + buf_len), depth_(0), max_depth_(_max_depth),
	  num_tables_(0), max_tables_(_max_tables)
	{}

  // Central location where any verification failures register.
  bool Check(bool ok) const {
	#ifdef FLATBUFFERS_DEBUG_VERIFICATION_FAILURE
	  assert(ok);
	#endif
	return ok;
  }

  // Verify any range within the buffer.
  bool Verify(const void *elem, size_t elem_len) const {
	return Check(elem_len <= (size_t) (end_ - buf_) && elem >= buf_ && elem <= end_ - elem_len);
  }

  // Verify a range indicated by sizeof(T).
  template<typename T> bool Verify(const void *elem) const {
	return Verify(elem, sizeof(T));
  }

  // Verify a pointer (may be NULL) of a table type.
  template<typename T> bool VerifyTable(const T *table) {
	return !table || table->Verify(*this);
  }

  // Verify a pointer (may be NULL) of any vector type.
  template<typename T> bool Verify(const Vector<T> *vec) const {
	const uint8_t *end;
	return !vec ||
		   VerifyVector(reinterpret_cast<const uint8_t *>(vec), sizeof(T),
						&end);
  }

  // Verify a pointer (may be NULL) of a vector to struct.
  template<typename T> bool Verify(const Vector<const T *> *vec) const {
	return Verify(reinterpret_cast<const Vector<T> *>(vec));
  }

  // Verify a pointer (may be NULL) to string.
  bool Verify(const String *str) const {
	const uint8_t *end;
	return !str ||
		   (VerifyVector(reinterpret_cast<const uint8_t *>(str), 1, &end) &&
			Verify(end, 1) &&      // Must have terminator
			Check(*end == '\0'));  // Terminating byte must be 0.
  }

  // Common code between vectors and strings.
  bool VerifyVector(const uint8_t *vec, size_t elem_size,
					const uint8_t **end) const {
	// Check we can read the size field.
	if (!Verify<uoffset_t>(vec)) return false;
	// Check the whole array. If this is a string, the byte past the array
	// must be 0.
	auto size = ReadScalar<uoffset_t>(vec);
	auto byte_size = sizeof(size) + elem_size * size;
	*end = vec + byte_size;
	return Verify(vec, byte_size);
  }

  // Special case for string contents, after the above has been called.
  bool VerifyVectorOfStrings(const Vector<Offset<String>> *vec) const {
	  if (vec) {
		for (uoffset_t i = 0; i < vec->size(); i++) {
		  if (!Verify(vec->Get(i))) return false;
		}
	  }
	  return true;
  }

  // Special case for table contents, after the above has been called.
  template<typename T> bool VerifyVectorOfTables(const Vector<Offset<T>> *vec) {
	if (vec) {
	  for (uoffset_t i = 0; i < vec->size(); i++) {
		if (!vec->Get(i)->Verify(*this)) return false;
	  }
	}
	return true;
  }

  // Verify this whole buffer, starting with root type T.
  template<typename T> bool VerifyBuffer() {
	// Call T::Verify, which must be in the generated code for this type.
	return Verify<uoffset_t>(buf_) &&
	  reinterpret_cast<const T *>(buf_ + ReadScalar<uoffset_t>(buf_))->
		Verify(*this);
  }

  // Called at the start of a table to increase counters measuring data
  // structure depth and amount, and possibly bails out with false if
  // limits set by the constructor have been hit. Needs to be balanced
  // with EndTable().
  bool VerifyComplexity() {
	depth_++;
	num_tables_++;
	return Check(depth_ <= max_depth_ && num_tables_ <= max_tables_);
  }

  // Called at the end of a table to pop the depth count.
  bool EndTable() {
	depth_--;
	return true;
  }

 private:
  const uint8_t *buf_;
  const uint8_t *end_;
  size_t depth_;
  size_t max_depth_;
  size_t num_tables_;
  size_t max_tables_;
};

// "structs" are flat structures that do not have an offset table, thus
// always have all members present and do not support forwards/backwards
// compatible extensions.

class Struct FLATBUFFERS_FINAL_CLASS {
 public:
  template<typename T> T GetField(uoffset_t o) const {
	return ReadScalar<T>(&data_[o]);
  }

  template<typename T> T GetPointer(uoffset_t o) const {
	auto p = &data_[o];
	return reinterpret_cast<T>(p + ReadScalar<uoffset_t>(p));
  }

  template<typename T> T GetStruct(uoffset_t o) const {
	return reinterpret_cast<T>(&data_[o]);
  }

  const uint8_t *GetAddressOf(uoffset_t o) const { return &data_[o]; }
  uint8_t *GetAddressOf(uoffset_t o) { return &data_[o]; }

 private:
  uint8_t data_[1];
};

// "tables" use an offset table (possibly shared) that allows fields to be
// omitted and added at will, but uses an extra indirection to read.
class Table {
 public:
  // This gets the field offset for any of the functions below it, or 0
  // if the field was not present.
  voffset_t GetOptionalFieldOffset(voffset_t field) const {
	// The vtable offset is always at the start.
	auto vtable = data_ - ReadScalar<soffset_t>(data_);
	// The first element is the size of the vtable (fields + type id + itself).
	auto vtsize = ReadScalar<voffset_t>(vtable);
	// If the field we're accessing is outside the vtable, we're reading older
	// data, so it's the same as if the offset was 0 (not present).
	return field < vtsize ? ReadScalar<voffset_t>(vtable + field) : 0;
  }

  template<typename T> T GetField(voffset_t field, T defaultval) const {
	auto field_offset = GetOptionalFieldOffset(field);
	return field_offset ? ReadScalar<T>(data_ + field_offset) : defaultval;
  }

  template<typename P> P GetPointer(voffset_t field) {
	auto field_offset = GetOptionalFieldOffset(field);
	auto p = data_ + field_offset;
	return field_offset
	  ? reinterpret_cast<P>(p + ReadScalar<uoffset_t>(p))
	  : nullptr;
  }
  template<typename P> P GetPointer(voffset_t field) const {
	return const_cast<Table *>(this)->GetPointer<P>(field);
  }

  template<typename P> P GetStruct(voffset_t field) const {
	auto field_offset = GetOptionalFieldOffset(field);
	auto p = const_cast<uint8_t *>(data_ + field_offset);
	return field_offset ? reinterpret_cast<P>(p) : nullptr;
  }

  template<typename T> bool SetField(voffset_t field, T val) {
	auto field_offset = GetOptionalFieldOffset(field);
	if (!field_offset) return false;
	WriteScalar(data_ + field_offset, val);
	return true;
  }

  bool SetPointer(voffset_t field, const uint8_t *val) {
	auto field_offset = GetOptionalFieldOffset(field);
	if (!field_offset) return false;
	WriteScalar(data_ + field_offset, val - (data_ + field_offset));
	return true;
  }

  uint8_t *GetAddressOf(voffset_t field) {
	auto field_offset = GetOptionalFieldOffset(field);
	return field_offset ? data_ + field_offset : nullptr;
  }
  const uint8_t *GetAddressOf(voffset_t field) const {
	return const_cast<Table *>(this)->GetAddressOf(field);
  }

  uint8_t *GetVTable() { return data_ - ReadScalar<soffset_t>(data_); }

  bool CheckField(voffset_t field) const {
	return GetOptionalFieldOffset(field) != 0;
  }

  // Verify the vtable of this table.
  // Call this once per table, followed by VerifyField once per field.
  bool VerifyTableStart(Verifier &verifier) const {
	// Check the vtable offset.
	if (!verifier.Verify<soffset_t>(data_)) return false;
	auto vtable = data_ - ReadScalar<soffset_t>(data_);
	// Check the vtable size field, then check vtable fits in its entirety.
	return verifier.VerifyComplexity() &&
		   verifier.Verify<voffset_t>(vtable) &&
		   verifier.Verify(vtable, ReadScalar<voffset_t>(vtable));
  }

  // Verify a particular field.
  template<typename T> bool VerifyField(const Verifier &verifier,
										voffset_t field) const {
	// Calling GetOptionalFieldOffset should be safe now thanks to
	// VerifyTable().
	auto field_offset = GetOptionalFieldOffset(field);
	// Check the actual field.
	return !field_offset || verifier.Verify<T>(data_ + field_offset);
  }

  // VerifyField for required fields.
  template<typename T> bool VerifyFieldRequired(const Verifier &verifier,
										voffset_t field) const {
	auto field_offset = GetOptionalFieldOffset(field);
	return verifier.Check(field_offset != 0) &&
		   verifier.Verify<T>(data_ + field_offset);
  }

 private:
  // private constructor & copy constructor: you obtain instances of this
  // class by pointing to existing data only
  Table();
  Table(const Table &other);

  uint8_t data_[1];
};

// Helper function to test if a field is present, using any of the field
// enums in the generated code.
// `table` must be a generated table type. Since this is a template parameter,
// this is not typechecked to be a subclass of Table, so beware!
// Note: this function will return false for fields equal to the default
// value, since they're not stored in the buffer (unless force_defaults was
// used).
template<typename T> bool IsFieldPresent(const T *table, voffset_t field) {
  // Cast, since Table is a private baseclass of any table types.
  return reinterpret_cast<const Table *>(table)->CheckField(field);
}

// Utility function for reverse lookups on the EnumNames*() functions
// (in the generated C++ code)
// names must be NULL terminated.
inline int LookupEnum(const char **names, const char *name) {
  for (const char **p = names; *p; p++)
	if (!strcmp(*p, name))
	  return static_cast<int>(p - names);
  return -1;
}

// These macros allow us to layout a struct with a guarantee that they'll end
// up looking the same on different compilers and platforms.
// It does this by disallowing the compiler to do any padding, and then
// does padding itself by inserting extra padding fields that make every
// element aligned to its own size.
// Additionally, it manually sets the alignment of the struct as a whole,
// which is typically its largest element, or a custom size set in the schema
// by the force_align attribute.
// These are used in the generated code only.

#if defined(_MSC_VER)
  #define MANUALLY_ALIGNED_STRUCT(alignment) \
	__pragma(pack(1)); \
	struct __declspec(align(alignment))
  #define STRUCT_END(name, size) \
	__pragma(pack()); \
	static_assert(sizeof(name) == size, "compiler breaks packing rules")
#elif defined(__GNUC__) || defined(__clang__)
  #define MANUALLY_ALIGNED_STRUCT(alignment) \
	_Pragma("pack(1)") \
	struct __attribute__((aligned(alignment)))
  #define STRUCT_END(name, size) \
	_Pragma("pack()") \
	static_assert(sizeof(name) == size, "compiler breaks packing rules")
#else
  #error Unknown compiler, please define structure alignment macros
#endif

// String which identifies the current version of FlatBuffers.
// flatbuffer_version_string is used by Google developers to identify which
// applications uploaded to Google Play are using this library.  This allows
// the development team at Google to determine the popularity of the library.
// How it works: Applications that are uploaded to the Google Play Store are
// scanned for this version string.  We track which applications are using it
// to measure popularity.  You are free to remove it (of course) but we would
// appreciate if you left it in.

// Weak linkage is culled by VS & doesn't work on cygwin.
#if !defined(_WIN32) && !defined(__CYGWIN__)

extern volatile __attribute__((weak)) const char *flatbuffer_version_string;
volatile __attribute__((weak)) const char *flatbuffer_version_string =
  "FlatBuffers "
  FLATBUFFERS_STRING(FLATBUFFERS_VERSION_MAJOR) "."
  FLATBUFFERS_STRING(FLATBUFFERS_VERSION_MINOR) "."
  FLATBUFFERS_STRING(FLATBUFFERS_VERSION_REVISION);

#endif  // !defined(_WIN32) && !defined(__CYGWIN__)

/// @endcond
}  // namespace flatbuffers

#endif  // FLATBUFFERS_H_

/*** End of inlined file: flatbuffers.h ***/

namespace humblenet {
namespace HumblePeer {

struct Attribute;

struct ICEServer;

struct HelloServer;

struct HelloClient;

struct P2POffer;

struct P2PAnswer;

struct P2PConnected;

struct P2PDisconnect;

struct P2PReject;

struct ICECandidate;

struct P2PRelayData;

struct AliasRegister;

struct AliasUnregister;

struct AliasLookup;

struct AliasResolved;

struct Message;

enum class ICEServerType : uint8_t {
  STUNServer = 1,
  TURNServer = 2,
  MIN = STUNServer,
  MAX = TURNServer
};

inline const char **EnumNamesICEServerType() {
  static const char *names[] = { "STUNServer", "TURNServer", nullptr };
  return names;
}

inline const char *EnumNameICEServerType(ICEServerType e) { return EnumNamesICEServerType()[static_cast<int>(e) - static_cast<int>(ICEServerType::STUNServer)]; }

enum class P2PRejectReason : uint8_t {
  NotFound = 1,
  PeerRefused = 2,
  MIN = NotFound,
  MAX = PeerRefused
};

inline const char **EnumNamesP2PRejectReason() {
  static const char *names[] = { "NotFound", "PeerRefused", nullptr };
  return names;
}

inline const char *EnumNameP2PRejectReason(P2PRejectReason e) { return EnumNamesP2PRejectReason()[static_cast<int>(e) - static_cast<int>(P2PRejectReason::NotFound)]; }

enum class MessageType : uint8_t {
  NONE = 0,
  HelloServer = 1,
  HelloClient = 2,
  P2PConnected = 10,
  P2PDisconnect = 11,
  P2POffer = 12,
  P2PAnswer = 13,
  P2PReject = 14,
  ICECandidate = 15,
  P2PRelayData = 16,
  AliasRegister = 20,
  AliasUnregister = 21,
  AliasLookup = 22,
  AliasResolved = 23,
  MIN = NONE,
  MAX = AliasResolved
};

inline const char **EnumNamesMessageType() {
  static const char *names[] = { "NONE", "HelloServer", "HelloClient", "", "", "", "", "", "", "", "P2PConnected", "P2PDisconnect", "P2POffer", "P2PAnswer", "P2PReject", "ICECandidate", "P2PRelayData", "", "", "", "AliasRegister", "AliasUnregister", "AliasLookup", "AliasResolved", nullptr };
  return names;
}

inline const char *EnumNameMessageType(MessageType e) { return EnumNamesMessageType()[static_cast<int>(e)]; }

inline bool VerifyMessageType(flatbuffers::Verifier &verifier, const void *union_obj, MessageType type);

struct Attribute FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_KEY = 4,
	VT_VALUE = 6
  };
  const flatbuffers::String *key() const { return GetPointer<const flatbuffers::String *>(VT_KEY); }
  bool KeyCompareLessThan(const Attribute *o) const { return *key() < *o->key(); }
  int KeyCompareWithValue(const char *val) const { return strcmp(key()->c_str(), val); }
  const flatbuffers::String *value() const { return GetPointer<const flatbuffers::String *>(VT_VALUE); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_KEY) &&
		   verifier.Verify(key()) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_VALUE) &&
		   verifier.Verify(value()) &&
		   verifier.EndTable();
  }
};

struct AttributeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_key(flatbuffers::Offset<flatbuffers::String> key) { fbb_.AddOffset(Attribute::VT_KEY, key); }
  void add_value(flatbuffers::Offset<flatbuffers::String> value) { fbb_.AddOffset(Attribute::VT_VALUE, value); }
  AttributeBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AttributeBuilder &operator=(const AttributeBuilder &);
  flatbuffers::Offset<Attribute> Finish() {
	auto o = flatbuffers::Offset<Attribute>(fbb_.EndTable(start_, 2));
	fbb_.Required(o, Attribute::VT_KEY);  // key
	fbb_.Required(o, Attribute::VT_VALUE);  // value
	return o;
  }
};

inline flatbuffers::Offset<Attribute> CreateAttribute(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> key = 0,
   flatbuffers::Offset<flatbuffers::String> value = 0) {
  AttributeBuilder builder_(_fbb);
  builder_.add_value(value);
  builder_.add_key(key);
  return builder_.Finish();
}

struct ICEServer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_TYPE = 4,
	VT_SERVER = 6,
	VT_USERNAME = 8,
	VT_PASSWORD = 10
  };
  ICEServerType type() const { return static_cast<ICEServerType>(GetField<uint8_t>(VT_TYPE, 1)); }
  const flatbuffers::String *server() const { return GetPointer<const flatbuffers::String *>(VT_SERVER); }
  const flatbuffers::String *username() const { return GetPointer<const flatbuffers::String *>(VT_USERNAME); }
  const flatbuffers::String *password() const { return GetPointer<const flatbuffers::String *>(VT_PASSWORD); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint8_t>(verifier, VT_TYPE) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_SERVER) &&
		   verifier.Verify(server()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_USERNAME) &&
		   verifier.Verify(username()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_PASSWORD) &&
		   verifier.Verify(password()) &&
		   verifier.EndTable();
  }
};

struct ICEServerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(ICEServerType type) { fbb_.AddElement<uint8_t>(ICEServer::VT_TYPE, static_cast<uint8_t>(type), 1); }
  void add_server(flatbuffers::Offset<flatbuffers::String> server) { fbb_.AddOffset(ICEServer::VT_SERVER, server); }
  void add_username(flatbuffers::Offset<flatbuffers::String> username) { fbb_.AddOffset(ICEServer::VT_USERNAME, username); }
  void add_password(flatbuffers::Offset<flatbuffers::String> password) { fbb_.AddOffset(ICEServer::VT_PASSWORD, password); }
  ICEServerBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ICEServerBuilder &operator=(const ICEServerBuilder &);
  flatbuffers::Offset<ICEServer> Finish() {
	auto o = flatbuffers::Offset<ICEServer>(fbb_.EndTable(start_, 4));
	fbb_.Required(o, ICEServer::VT_SERVER);  // server
	return o;
  }
};

inline flatbuffers::Offset<ICEServer> CreateICEServer(flatbuffers::FlatBufferBuilder &_fbb,
   ICEServerType type = ICEServerType::STUNServer,
   flatbuffers::Offset<flatbuffers::String> server = 0,
   flatbuffers::Offset<flatbuffers::String> username = 0,
   flatbuffers::Offset<flatbuffers::String> password = 0) {
  ICEServerBuilder builder_(_fbb);
  builder_.add_password(password);
  builder_.add_username(username);
  builder_.add_server(server);
  builder_.add_type(type);
  return builder_.Finish();
}

struct HelloServer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_VERSION = 4,
	VT_FLAGS = 6,
	VT_GAMETOKEN = 8,
	VT_GAMESIGNATURE = 10,
	VT_AUTHTOKEN = 12,
	VT_RECONNECTTOKEN = 14,
	VT_ATTRIBUTES = 16
  };
  uint32_t version() const { return GetField<uint32_t>(VT_VERSION, 0); }
  uint8_t flags() const { return GetField<uint8_t>(VT_FLAGS, 0); }
  const flatbuffers::String *gameToken() const { return GetPointer<const flatbuffers::String *>(VT_GAMETOKEN); }
  const flatbuffers::String *gameSignature() const { return GetPointer<const flatbuffers::String *>(VT_GAMESIGNATURE); }
  const flatbuffers::String *authToken() const { return GetPointer<const flatbuffers::String *>(VT_AUTHTOKEN); }
  const flatbuffers::String *reconnectToken() const { return GetPointer<const flatbuffers::String *>(VT_RECONNECTTOKEN); }
  const flatbuffers::Vector<flatbuffers::Offset<Attribute>> *attributes() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Attribute>> *>(VT_ATTRIBUTES); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_VERSION) &&
		   VerifyField<uint8_t>(verifier, VT_FLAGS) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_GAMETOKEN) &&
		   verifier.Verify(gameToken()) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_GAMESIGNATURE) &&
		   verifier.Verify(gameSignature()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_AUTHTOKEN) &&
		   verifier.Verify(authToken()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_RECONNECTTOKEN) &&
		   verifier.Verify(reconnectToken()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_ATTRIBUTES) &&
		   verifier.Verify(attributes()) &&
		   verifier.VerifyVectorOfTables(attributes()) &&
		   verifier.EndTable();
  }
};

struct HelloServerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_version(uint32_t version) { fbb_.AddElement<uint32_t>(HelloServer::VT_VERSION, version, 0); }
  void add_flags(uint8_t flags) { fbb_.AddElement<uint8_t>(HelloServer::VT_FLAGS, flags, 0); }
  void add_gameToken(flatbuffers::Offset<flatbuffers::String> gameToken) { fbb_.AddOffset(HelloServer::VT_GAMETOKEN, gameToken); }
  void add_gameSignature(flatbuffers::Offset<flatbuffers::String> gameSignature) { fbb_.AddOffset(HelloServer::VT_GAMESIGNATURE, gameSignature); }
  void add_authToken(flatbuffers::Offset<flatbuffers::String> authToken) { fbb_.AddOffset(HelloServer::VT_AUTHTOKEN, authToken); }
  void add_reconnectToken(flatbuffers::Offset<flatbuffers::String> reconnectToken) { fbb_.AddOffset(HelloServer::VT_RECONNECTTOKEN, reconnectToken); }
  void add_attributes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Attribute>>> attributes) { fbb_.AddOffset(HelloServer::VT_ATTRIBUTES, attributes); }
  HelloServerBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  HelloServerBuilder &operator=(const HelloServerBuilder &);
  flatbuffers::Offset<HelloServer> Finish() {
	auto o = flatbuffers::Offset<HelloServer>(fbb_.EndTable(start_, 7));
	fbb_.Required(o, HelloServer::VT_GAMETOKEN);  // gameToken
	fbb_.Required(o, HelloServer::VT_GAMESIGNATURE);  // gameSignature
	return o;
  }
};

inline flatbuffers::Offset<HelloServer> CreateHelloServer(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t version = 0,
   uint8_t flags = 0,
   flatbuffers::Offset<flatbuffers::String> gameToken = 0,
   flatbuffers::Offset<flatbuffers::String> gameSignature = 0,
   flatbuffers::Offset<flatbuffers::String> authToken = 0,
   flatbuffers::Offset<flatbuffers::String> reconnectToken = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Attribute>>> attributes = 0) {
  HelloServerBuilder builder_(_fbb);
  builder_.add_attributes(attributes);
  builder_.add_reconnectToken(reconnectToken);
  builder_.add_authToken(authToken);
  builder_.add_gameSignature(gameSignature);
  builder_.add_gameToken(gameToken);
  builder_.add_version(version);
  builder_.add_flags(flags);
  return builder_.Finish();
}

struct HelloClient FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_RECONNECTTOKEN = 6,
	VT_ICESERVERS = 8
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  const flatbuffers::String *reconnectToken() const { return GetPointer<const flatbuffers::String *>(VT_RECONNECTTOKEN); }
  const flatbuffers::Vector<flatbuffers::Offset<ICEServer>> *iceServers() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<ICEServer>> *>(VT_ICESERVERS); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_RECONNECTTOKEN) &&
		   verifier.Verify(reconnectToken()) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_ICESERVERS) &&
		   verifier.Verify(iceServers()) &&
		   verifier.VerifyVectorOfTables(iceServers()) &&
		   verifier.EndTable();
  }
};

struct HelloClientBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(HelloClient::VT_PEERID, peerId, 0); }
  void add_reconnectToken(flatbuffers::Offset<flatbuffers::String> reconnectToken) { fbb_.AddOffset(HelloClient::VT_RECONNECTTOKEN, reconnectToken); }
  void add_iceServers(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ICEServer>>> iceServers) { fbb_.AddOffset(HelloClient::VT_ICESERVERS, iceServers); }
  HelloClientBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  HelloClientBuilder &operator=(const HelloClientBuilder &);
  flatbuffers::Offset<HelloClient> Finish() {
	auto o = flatbuffers::Offset<HelloClient>(fbb_.EndTable(start_, 3));
	return o;
  }
};

inline flatbuffers::Offset<HelloClient> CreateHelloClient(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   flatbuffers::Offset<flatbuffers::String> reconnectToken = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ICEServer>>> iceServers = 0) {
  HelloClientBuilder builder_(_fbb);
  builder_.add_iceServers(iceServers);
  builder_.add_reconnectToken(reconnectToken);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct P2POffer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_FLAGS = 6,
	VT_OFFER = 8
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  uint8_t flags() const { return GetField<uint8_t>(VT_FLAGS, 0); }
  const flatbuffers::String *offer() const { return GetPointer<const flatbuffers::String *>(VT_OFFER); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<uint8_t>(verifier, VT_FLAGS) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_OFFER) &&
		   verifier.Verify(offer()) &&
		   verifier.EndTable();
  }
};

struct P2POfferBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2POffer::VT_PEERID, peerId, 0); }
  void add_flags(uint8_t flags) { fbb_.AddElement<uint8_t>(P2POffer::VT_FLAGS, flags, 0); }
  void add_offer(flatbuffers::Offset<flatbuffers::String> offer) { fbb_.AddOffset(P2POffer::VT_OFFER, offer); }
  P2POfferBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2POfferBuilder &operator=(const P2POfferBuilder &);
  flatbuffers::Offset<P2POffer> Finish() {
	auto o = flatbuffers::Offset<P2POffer>(fbb_.EndTable(start_, 3));
	return o;
  }
};

inline flatbuffers::Offset<P2POffer> CreateP2POffer(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   uint8_t flags = 0,
   flatbuffers::Offset<flatbuffers::String> offer = 0) {
  P2POfferBuilder builder_(_fbb);
  builder_.add_offer(offer);
  builder_.add_peerId(peerId);
  builder_.add_flags(flags);
  return builder_.Finish();
}

struct P2PAnswer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_OFFER = 6
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  const flatbuffers::String *offer() const { return GetPointer<const flatbuffers::String *>(VT_OFFER); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_OFFER) &&
		   verifier.Verify(offer()) &&
		   verifier.EndTable();
  }
};

struct P2PAnswerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2PAnswer::VT_PEERID, peerId, 0); }
  void add_offer(flatbuffers::Offset<flatbuffers::String> offer) { fbb_.AddOffset(P2PAnswer::VT_OFFER, offer); }
  P2PAnswerBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2PAnswerBuilder &operator=(const P2PAnswerBuilder &);
  flatbuffers::Offset<P2PAnswer> Finish() {
	auto o = flatbuffers::Offset<P2PAnswer>(fbb_.EndTable(start_, 2));
	return o;
  }
};

inline flatbuffers::Offset<P2PAnswer> CreateP2PAnswer(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   flatbuffers::Offset<flatbuffers::String> offer = 0) {
  P2PAnswerBuilder builder_(_fbb);
  builder_.add_offer(offer);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct P2PConnected FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   verifier.EndTable();
  }
};

struct P2PConnectedBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2PConnected::VT_PEERID, peerId, 0); }
  P2PConnectedBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2PConnectedBuilder &operator=(const P2PConnectedBuilder &);
  flatbuffers::Offset<P2PConnected> Finish() {
	auto o = flatbuffers::Offset<P2PConnected>(fbb_.EndTable(start_, 1));
	return o;
  }
};

inline flatbuffers::Offset<P2PConnected> CreateP2PConnected(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0) {
  P2PConnectedBuilder builder_(_fbb);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct P2PDisconnect FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   verifier.EndTable();
  }
};

struct P2PDisconnectBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2PDisconnect::VT_PEERID, peerId, 0); }
  P2PDisconnectBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2PDisconnectBuilder &operator=(const P2PDisconnectBuilder &);
  flatbuffers::Offset<P2PDisconnect> Finish() {
	auto o = flatbuffers::Offset<P2PDisconnect>(fbb_.EndTable(start_, 1));
	return o;
  }
};

inline flatbuffers::Offset<P2PDisconnect> CreateP2PDisconnect(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0) {
  P2PDisconnectBuilder builder_(_fbb);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct P2PReject FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_REASON = 6
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  P2PRejectReason reason() const { return static_cast<P2PRejectReason>(GetField<uint8_t>(VT_REASON, 1)); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<uint8_t>(verifier, VT_REASON) &&
		   verifier.EndTable();
  }
};

struct P2PRejectBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2PReject::VT_PEERID, peerId, 0); }
  void add_reason(P2PRejectReason reason) { fbb_.AddElement<uint8_t>(P2PReject::VT_REASON, static_cast<uint8_t>(reason), 1); }
  P2PRejectBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2PRejectBuilder &operator=(const P2PRejectBuilder &);
  flatbuffers::Offset<P2PReject> Finish() {
	auto o = flatbuffers::Offset<P2PReject>(fbb_.EndTable(start_, 2));
	return o;
  }
};

inline flatbuffers::Offset<P2PReject> CreateP2PReject(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   P2PRejectReason reason = P2PRejectReason::NotFound) {
  P2PRejectBuilder builder_(_fbb);
  builder_.add_peerId(peerId);
  builder_.add_reason(reason);
  return builder_.Finish();
}

struct ICECandidate FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_OFFER = 6
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  const flatbuffers::String *offer() const { return GetPointer<const flatbuffers::String *>(VT_OFFER); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_OFFER) &&
		   verifier.Verify(offer()) &&
		   verifier.EndTable();
  }
};

struct ICECandidateBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(ICECandidate::VT_PEERID, peerId, 0); }
  void add_offer(flatbuffers::Offset<flatbuffers::String> offer) { fbb_.AddOffset(ICECandidate::VT_OFFER, offer); }
  ICECandidateBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ICECandidateBuilder &operator=(const ICECandidateBuilder &);
  flatbuffers::Offset<ICECandidate> Finish() {
	auto o = flatbuffers::Offset<ICECandidate>(fbb_.EndTable(start_, 2));
	return o;
  }
};

inline flatbuffers::Offset<ICECandidate> CreateICECandidate(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   flatbuffers::Offset<flatbuffers::String> offer = 0) {
  ICECandidateBuilder builder_(_fbb);
  builder_.add_offer(offer);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct P2PRelayData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_PEERID = 4,
	VT_DATA = 6
  };
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  const flatbuffers::Vector<int8_t> *data() const { return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
		   verifier.Verify(data()) &&
		   verifier.EndTable();
  }
};

struct P2PRelayDataBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(P2PRelayData::VT_PEERID, peerId, 0); }
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) { fbb_.AddOffset(P2PRelayData::VT_DATA, data); }
  P2PRelayDataBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  P2PRelayDataBuilder &operator=(const P2PRelayDataBuilder &);
  flatbuffers::Offset<P2PRelayData> Finish() {
	auto o = flatbuffers::Offset<P2PRelayData>(fbb_.EndTable(start_, 2));
	return o;
  }
};

inline flatbuffers::Offset<P2PRelayData> CreateP2PRelayData(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t peerId = 0,
   flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  P2PRelayDataBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_peerId(peerId);
  return builder_.Finish();
}

struct AliasRegister FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_ALIAS = 4
  };
  const flatbuffers::String *alias() const { return GetPointer<const flatbuffers::String *>(VT_ALIAS); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_ALIAS) &&
		   verifier.Verify(alias()) &&
		   verifier.EndTable();
  }
};

struct AliasRegisterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_alias(flatbuffers::Offset<flatbuffers::String> alias) { fbb_.AddOffset(AliasRegister::VT_ALIAS, alias); }
  AliasRegisterBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AliasRegisterBuilder &operator=(const AliasRegisterBuilder &);
  flatbuffers::Offset<AliasRegister> Finish() {
	auto o = flatbuffers::Offset<AliasRegister>(fbb_.EndTable(start_, 1));
	fbb_.Required(o, AliasRegister::VT_ALIAS);  // alias
	return o;
  }
};

inline flatbuffers::Offset<AliasRegister> CreateAliasRegister(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> alias = 0) {
  AliasRegisterBuilder builder_(_fbb);
  builder_.add_alias(alias);
  return builder_.Finish();
}

struct AliasUnregister FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_ALIAS = 4
  };
  const flatbuffers::String *alias() const { return GetPointer<const flatbuffers::String *>(VT_ALIAS); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_ALIAS) &&
		   verifier.Verify(alias()) &&
		   verifier.EndTable();
  }
};

struct AliasUnregisterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_alias(flatbuffers::Offset<flatbuffers::String> alias) { fbb_.AddOffset(AliasUnregister::VT_ALIAS, alias); }
  AliasUnregisterBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AliasUnregisterBuilder &operator=(const AliasUnregisterBuilder &);
  flatbuffers::Offset<AliasUnregister> Finish() {
	auto o = flatbuffers::Offset<AliasUnregister>(fbb_.EndTable(start_, 1));
	return o;
  }
};

inline flatbuffers::Offset<AliasUnregister> CreateAliasUnregister(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> alias = 0) {
  AliasUnregisterBuilder builder_(_fbb);
  builder_.add_alias(alias);
  return builder_.Finish();
}

struct AliasLookup FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_ALIAS = 4
  };
  const flatbuffers::String *alias() const { return GetPointer<const flatbuffers::String *>(VT_ALIAS); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_ALIAS) &&
		   verifier.Verify(alias()) &&
		   verifier.EndTable();
  }
};

struct AliasLookupBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_alias(flatbuffers::Offset<flatbuffers::String> alias) { fbb_.AddOffset(AliasLookup::VT_ALIAS, alias); }
  AliasLookupBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AliasLookupBuilder &operator=(const AliasLookupBuilder &);
  flatbuffers::Offset<AliasLookup> Finish() {
	auto o = flatbuffers::Offset<AliasLookup>(fbb_.EndTable(start_, 1));
	fbb_.Required(o, AliasLookup::VT_ALIAS);  // alias
	return o;
  }
};

inline flatbuffers::Offset<AliasLookup> CreateAliasLookup(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> alias = 0) {
  AliasLookupBuilder builder_(_fbb);
  builder_.add_alias(alias);
  return builder_.Finish();
}

struct AliasResolved FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_ALIAS = 4,
	VT_PEERID = 6
  };
  const flatbuffers::String *alias() const { return GetPointer<const flatbuffers::String *>(VT_ALIAS); }
  uint32_t peerId() const { return GetField<uint32_t>(VT_PEERID, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, VT_ALIAS) &&
		   verifier.Verify(alias()) &&
		   VerifyField<uint32_t>(verifier, VT_PEERID) &&
		   verifier.EndTable();
  }
};

struct AliasResolvedBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_alias(flatbuffers::Offset<flatbuffers::String> alias) { fbb_.AddOffset(AliasResolved::VT_ALIAS, alias); }
  void add_peerId(uint32_t peerId) { fbb_.AddElement<uint32_t>(AliasResolved::VT_PEERID, peerId, 0); }
  AliasResolvedBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AliasResolvedBuilder &operator=(const AliasResolvedBuilder &);
  flatbuffers::Offset<AliasResolved> Finish() {
	auto o = flatbuffers::Offset<AliasResolved>(fbb_.EndTable(start_, 2));
	fbb_.Required(o, AliasResolved::VT_ALIAS);  // alias
	return o;
  }
};

inline flatbuffers::Offset<AliasResolved> CreateAliasResolved(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> alias = 0,
   uint32_t peerId = 0) {
  AliasResolvedBuilder builder_(_fbb);
  builder_.add_peerId(peerId);
  builder_.add_alias(alias);
  return builder_.Finish();
}

struct Message FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
	VT_MESSAGE_TYPE = 4,
	VT_MESSAGE = 6
  };
  MessageType message_type() const { return static_cast<MessageType>(GetField<uint8_t>(VT_MESSAGE_TYPE, 0)); }
  const void *message() const { return GetPointer<const void *>(VT_MESSAGE); }
  bool Verify(flatbuffers::Verifier &verifier) const {
	return VerifyTableStart(verifier) &&
		   VerifyField<uint8_t>(verifier, VT_MESSAGE_TYPE) &&
		   VerifyField<flatbuffers::uoffset_t>(verifier, VT_MESSAGE) &&
		   VerifyMessageType(verifier, message(), message_type()) &&
		   verifier.EndTable();
  }
};

struct MessageBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_message_type(MessageType message_type) { fbb_.AddElement<uint8_t>(Message::VT_MESSAGE_TYPE, static_cast<uint8_t>(message_type), 0); }
  void add_message(flatbuffers::Offset<void> message) { fbb_.AddOffset(Message::VT_MESSAGE, message); }
  MessageBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  MessageBuilder &operator=(const MessageBuilder &);
  flatbuffers::Offset<Message> Finish() {
	auto o = flatbuffers::Offset<Message>(fbb_.EndTable(start_, 2));
	return o;
  }
};

inline flatbuffers::Offset<Message> CreateMessage(flatbuffers::FlatBufferBuilder &_fbb,
   MessageType message_type = MessageType::NONE,
   flatbuffers::Offset<void> message = 0) {
  MessageBuilder builder_(_fbb);
  builder_.add_message(message);
  builder_.add_message_type(message_type);
  return builder_.Finish();
}

inline bool VerifyMessageType(flatbuffers::Verifier &verifier, const void *union_obj, MessageType type) {
  switch (type) {
	case MessageType::NONE: return true;
	case MessageType::HelloServer: return verifier.VerifyTable(reinterpret_cast<const HelloServer *>(union_obj));
	case MessageType::HelloClient: return verifier.VerifyTable(reinterpret_cast<const HelloClient *>(union_obj));
	case MessageType::P2PConnected: return verifier.VerifyTable(reinterpret_cast<const P2PConnected *>(union_obj));
	case MessageType::P2PDisconnect: return verifier.VerifyTable(reinterpret_cast<const P2PDisconnect *>(union_obj));
	case MessageType::P2POffer: return verifier.VerifyTable(reinterpret_cast<const P2POffer *>(union_obj));
	case MessageType::P2PAnswer: return verifier.VerifyTable(reinterpret_cast<const P2PAnswer *>(union_obj));
	case MessageType::P2PReject: return verifier.VerifyTable(reinterpret_cast<const P2PReject *>(union_obj));
	case MessageType::ICECandidate: return verifier.VerifyTable(reinterpret_cast<const ICECandidate *>(union_obj));
	case MessageType::P2PRelayData: return verifier.VerifyTable(reinterpret_cast<const P2PRelayData *>(union_obj));
	case MessageType::AliasRegister: return verifier.VerifyTable(reinterpret_cast<const AliasRegister *>(union_obj));
	case MessageType::AliasUnregister: return verifier.VerifyTable(reinterpret_cast<const AliasUnregister *>(union_obj));
	case MessageType::AliasLookup: return verifier.VerifyTable(reinterpret_cast<const AliasLookup *>(union_obj));
	case MessageType::AliasResolved: return verifier.VerifyTable(reinterpret_cast<const AliasResolved *>(union_obj));
	default: return false;
  }
}

inline const humblenet::HumblePeer::Message *GetMessage(const void *buf) { return flatbuffers::GetRoot<humblenet::HumblePeer::Message>(buf); }

inline bool VerifyMessageBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<humblenet::HumblePeer::Message>(); }

inline void FinishMessageBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<humblenet::HumblePeer::Message> root) { fbb.Finish(root); }

}  // namespace HumblePeer
}  // namespace humblenet

#endif  // FLATBUFFERS_GENERATED_HUMBLEPEER_HUMBLENET_HUMBLEPEER_H_

/*** End of inlined file: humblepeer_generated.h ***/

#ifdef __GNUC__
#define WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#else
#define WARN_UNUSED_RESULT
#endif

namespace humblenet {

	// Ice Server definition
	struct ICEServer {
		HumblePeer::ICEServerType type;
		std::string server;
		std::string username;
		std::string password;

		ICEServer(const std::string& _server)
		: type(HumblePeer::ICEServerType::STUNServer), server(_server) {}
		ICEServer(const std::string& _server, const std::string& _username, const std::string& _password)
		: type(HumblePeer::ICEServerType::TURNServer), server(_server), username(_username), password(_password) {}
	};

	// abstract type for P2P signaling connection
	// we could use C++ classes and inheritance
	// but since there's only ever one type of connection in any binary
	// we opt for static dispatch instead
	struct P2PSignalConnection;
	ha_bool sendP2PMessage(P2PSignalConnection *conn, const uint8_t *buff, size_t length) WARN_UNUSED_RESULT;

	/*
	  P2POffer contains
		PeerID
		  client->server who want to connect to
		  server->client who wants to connect to us
		connectionOffer generated by the browser (stringified JSON)

	   P2PAnswer contains
		PeerID
		connectionOffer generated by the other browser (also str JSON)

	   HelloServer
		auth token which allows server to look up client details in database

	   HelloClient
		PeerID  this is who you are
		IP address?

	  https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Architecture/Connectivity

	  peer1                        server                        peer2

			 P2POffer ->
											   P2POffer ->

											  <- P2PAnswer
			<- P2PAnswer
			 ICECandidate ->
												ICECandidate ->
											 <- ICECandidate
			<- ICECandidate
	*/

	typedef ha_bool(*ProcessMsgFunc) (const HumblePeer::Message* msg, void *data);

	/*
	 returns true if all went wel
			 false if something is wrong, sync is lost and channel should be closed
			 TODO: should this be a tristate (process, noprocess, error)?
			 does anyone care if progress happened or not?
	 */
	ha_bool parseMessage(std::vector<uint8_t> &recvBuf, ProcessMsgFunc processFunc, void *user_data);

	// Peer server connection
	ha_bool sendHelloServer(humblenet::P2PSignalConnection *conn, uint8_t flags,
							const std::string& gametoken, const std::string& gamesecret,
							const std::string& authToken, const std::string& reconnectToken,
							const std::map<std::string, std::string>& attributes);
	ha_bool sendHelloClient(humblenet::P2PSignalConnection *conn, PeerId peerId,
							const std::string& reconnectToken,
							const std::vector<ICEServer>& iceServers);

	// P2P Handling
	ha_bool sendNoSuchPeer(humblenet::P2PSignalConnection *conn, PeerId peerId);
	ha_bool sendPeerRefused(humblenet::P2PSignalConnection *conn, PeerId peerId);
	ha_bool sendP2PConnect(P2PSignalConnection *conn, PeerId peerId, uint8_t flags, const char* offer);
	ha_bool sendP2PResponse(P2PSignalConnection *conn, PeerId peerId, const char* offer);
	ha_bool sendICECandidate(humblenet::P2PSignalConnection *conn, PeerId peerId, const char* offer);
	ha_bool sendP2PDisconnect(humblenet::P2PSignalConnection *conn, PeerId peer);
	ha_bool sendP2PRelayData(humblenet::P2PSignalConnection *conn, PeerId peer, const void* data, uint16_t length);

	// Name Alias
	ha_bool sendAliasRegister(P2PSignalConnection *conn, const std::string& alias);
	ha_bool sendAliasUnregister(P2PSignalConnection *conn, const std::string& alias);
	ha_bool sendAliasLookup(P2PSignalConnection *conn, const std::string& alias);
	ha_bool sendAliasResolved(P2PSignalConnection *conn, const std::string& alias, PeerId peer);

}  // namespace humblenet

#endif  // HUMBLEPEER_H

/*** End of inlined file: humblepeer.h ***/


/*** Start of inlined file: libsocket.h ***/
//
//  libsocket.h
//  humblenet
//
//  Created by Chris Rudd on 3/11/16.
//
//

#ifndef LIBSOCKET_H
#define LIBSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

struct internal_socket_t;
struct internal_context_t;

struct internal_callbacks_t {
	// called to return the local sdp offer
	int (*on_sdp)( internal_socket_t*, const char* offer, void* user_data );
	// called when a local candidate is discovered
	int (*on_ice_candidate)( internal_socket_t*, const char* candidate, void* user_data);

	// called for incoming connections to indicate the connection process is completed.
	int (*on_accept) (internal_socket_t*, void* user_data);
	// called for outgoing connections to indicate the connection process is completed.
	int (*on_connect) (internal_socket_t*, void* user_data);
	// called when an incoming datachannel is established
	int (*on_accept_channel)(internal_socket_t*, const char* name, void* user_data);
	// called when an outgoing datachannel is established
	int (*on_connect_channel)(internal_socket_t*, const char* name, void* user_data);
	// called each time data is received.
	int (*on_data)( internal_socket_t* s, const void* data, int len, void* user_data );
	// called to indicate the connection is wriable.
	int (*on_writable) (internal_socket_t*, void* user_data);
	// called when the conenction is terminated (from either side)
	int (*on_disconnect)( internal_socket_t* s, void* user_data );
	// called when socket object will be destroyed.
	int (*on_destroy)( internal_socket_t* s, void* user_data );
};

internal_context_t* internal_init(internal_callbacks_t*);
void internal_deinit(internal_context_t*);

bool internal_supports_webRTC( internal_context_t *);
void internal_register_protocol( internal_context_t*, const char* protocol, internal_callbacks_t* callbacks );

internal_socket_t* internal_connect_websocket( const char* addr, const char* protocol );
void internal_set_stun_servers( internal_context_t*, const char** servers, int count);
internal_socket_t* internal_create_webrtc(internal_context_t *);
int internal_create_offer( internal_socket_t* socket );
int internal_set_offer( internal_socket_t* socket, const char* offer );
int internal_set_answer( internal_socket_t* socket, const char* offer );
int internal_create_channel( internal_socket_t* socket, const char* name );
int internal_add_ice_candidate( internal_socket_t*, const char* candidate );

void internal_set_data( internal_socket_t*, void* user_data);
void internal_set_callbacks(internal_socket_t* socket, internal_callbacks_t* callbacks );
int internal_write_socket( internal_socket_t*, const void* buf, int len );
void internal_close_socket( internal_socket_t* );

#ifdef __cplusplus
}
#endif

#endif /* LIBSOCKET_H */

/*** End of inlined file: libsocket.h ***/

#include <memory>

// TODO: should have a way to disable this on release builds
#define LOG printf
#define TRACE( ... )

namespace humblenet {
	struct P2PSignalConnection {
		internal_socket_t *wsi;
		std::vector<uint8_t> recvBuf;
		std::vector<char> sendBuf;

		P2PSignalConnection()
		: wsi(NULL)
		{
		}

		void disconnect() {
			if( wsi )
				internal_close_socket(wsi);
			wsi = NULL;
		}
	};
}

enum InOrOut
{
	Incoming
	, Outgoing
};

// Connection status
typedef enum ConnectionStatus {
	HUMBLENET_CONNECTION_CLOSED,
	HUMBLENET_CONNECTION_CONNECTING,
	HUMBLENET_CONNECTION_CONNECTED,
} ConnectionStatus;

struct Connection {
	InOrOut inOrOut;
	ConnectionStatus status;

	// peerId of the other peer
	// 0 if not a p2p connection
	PeerId otherPeer;

	std::vector<char> recvBuffer;

	ha_bool writable;

	struct internal_socket_t* socket;

	Connection( InOrOut inOrOut_, struct internal_socket_t *s = NULL)
	: inOrOut(inOrOut_)
	, status(HUMBLENET_CONNECTION_CONNECTING)
	, otherPeer(0)
	, writable(true)
	, socket(NULL)
	{
	}
};

typedef struct HumbleNetState {
	// established connections indexed by socket id
	// pointer not owned
	std::unordered_map<internal_socket_t *, Connection *> connections;

	// new incoming connections waiting accept
	std::unordered_set<Connection *> pendingNewConnections;

	// connections with pending data in buffer
	// pointer not owned
	std::unordered_set<Connection *> pendingDataConnections;

	// connections which have been closed by remote and need user notification
	std::unordered_set<Connection *> remoteClosedConnections;

	// pending outgoing (not established) p2p connections
	// pointer not owned (owned by whoever called humblenet_connect_peer)
	std::unordered_map<PeerId, Connection *> pendingPeerConnectionsOut;

	// pending incoming P2P connections
	// these ARE owned (until humblenet_connection_accept which removes them)
	std::unordered_map<PeerId, Connection *> pendingPeerConnectionsIn;

	// outgoing pending (not established) alias connections
	// pointer not owned
	std::unordered_map<std::string, Connection *> pendingAliasConnectionsOut;

	// map of peers that are blacklisted, value is when they they were blacklisted
	// incomming peers are added to this list when they are disconnected.
	// this is to prevent anemic connection attempts.
	std::unordered_map<PeerId, uint64_t> peerBlacklist;

	PeerId myPeerId;

	std::unique_ptr<humblenet::P2PSignalConnection> p2pConn;

	std::string signalingServerAddr;
	std::string gameToken;
	std::string gameSecret;
	std::string authToken;
	std::string reconnectToken;
	std::vector<humblenet::ICEServer> iceServers;

	ha_bool webRTCSupported;

	internal_context_t *context;

	HumbleNetState()
	:  myPeerId(0)
	, webRTCSupported(false)
	, context(NULL)
	{
	}
} HumbleNetState;

extern HumbleNetState humbleNetState;

#define INIT_GUARD( msg, check, ... ) \
if( ! (check) ) { humblenet_set_error( msg ); return __VA_ARGS__ ; }

// Initialize P2P system with websocket layer
ha_bool internal_p2p_register_protocol();

// internal...
void internal_poll_io();
void humblenet_connection_set_closed( Connection* conn );
bool is_peer_blacklisted( PeerId peer );

void humblenet_lock();
void humblenet_unlock();

struct Guard {
	Guard() {
		humblenet_lock();
	}

	~Guard() {
		humblenet_unlock();
	}
};

#ifdef EMSCRIPTEN
	#define HUMBLENET_GUARD()
#else
	#define HUMBLENET_GUARD() Guard lock
#endif

/*
 * Get connection status
 */
ConnectionStatus humblenet_connection_status(Connection *connection);

/*
 * Connect to server server_addr
 */
Connection *humblenet_connect_websocket(const char *server_addr);

/*
 * Connect to peer peer_id
 */
Connection *humblenet_connect_peer(PeerId peer_id);

/*
 * Close the Connection
 */
void humblenet_connection_close(Connection *connection);

/*
 * Returns true if connection has data to read, false otherwise
 */
ha_bool humblenet_connection_is_readable(Connection *connection);

/*
 * Returns true if connection can be written into, false otherwise
 */
ha_bool humblenet_connection_is_writable(Connection *connection);

/*
 * Send data through Connection
 * Returns the number of bytes sent, -1 on error
 */
int humblenet_connection_write(Connection *connection, const void *buf, uint32_t bufsize);

/*
 * Receive data through Connection
 * Returns the number of bytes received, -1 on error
 */
int humblenet_connection_read(Connection *connection, void *buf, uint32_t bufsize);

/*
 * Receive data through Connection
 * Returns a malloc() -allocated buffer
 * You are responsible for freeing it
 * sets *retval to number of bytes in buffer or negative on error
 */
void *humblenet_connection_read_all(Connection *connection, int *retval);

/*
 * Poll all connections
 * timeout_ms Timeout in milliseconds
 * 0 = return immediately if no pending connections
 * negative = wait indefinitely
 * returns a connection with readable data, NULL if no such connections
 */
Connection *humblenet_poll_all(int timeout_ms);

/*
 * Poll a single connection
 * connection to poll
 * timeout_ms Timeout in milliseconds
 * 0 = return immediately if no pending connections
 * negative = wait indefinitely
 * returns true if readable
 */
ha_bool humblenet_connection_poll(Connection *connection, int timeout_ms);

/*
 * Accepts new connections
 * returns a new Connection (which you now own) or NULL if no new connections
 * Humblenet will include this connection in future humblenet_connection_poll calls
 */
Connection *humblenet_connection_accept();

/*
 * Get the PeerId of this connection
 * returns PeerId or 0 if not a p2p connection
 */
PeerId humblenet_connection_get_peer_id(Connection *connection);

uint64_t sys_milliseconds();

#endif // HUMBLENET_P2P_INTERNAL

/*** End of inlined file: humblenet_p2p_internal.h ***/


/*** Start of inlined file: humblenet_alias.h ***/
#ifndef HUMBLENET_ALIAS_H
#define HUMBLENET_ALIAS_H

#ifndef HUMBLENET_P2P_INTERNAL
#error Cannot use this header outside humblenet
#endif

/**
 * Register an alias for this peer.
 *
 *
 * NOTE: The peer server can reject the alias, but that will notify via the events.
 */
ha_bool internal_alias_register(const char* alias );

/**
 * Unregister an alias for this peer.
 *
 *
 * Passing NULL means unregister ALL aliases
 */
ha_bool internal_alias_unregister(const char* alias );

/**
 * Return a virtual PeerId that represents the alias.
 *
 */
PeerId internal_alias_lookup(const char* alias );

/**
 * Is this peer id a vritual peer id
 */
ha_bool internal_alias_is_virtual_peer( PeerId peer );

/**
 * Get the virtual peer associated with this conenction (if there is one)
 *
 */
PeerId internal_alias_get_virtual_peer( Connection* conn );

/**
 * Find the connection associated with the virtual peer
 *
 */
Connection* internal_alias_find_connection( PeerId );

/**
 * Setup a connection to the virtual peer
 *
 */
Connection* internal_alias_create_connection( PeerId );

/**
 * Remove the connection from the alias system
 *
 */
void internal_alias_remove_connection( Connection* conn );

/**
 * Called when the peer server resolves the peerid for a a name
 *
 */
void internal_alias_resolved_to( const std::string& alias, PeerId peer );

#endif // HUMBLENET_ALIAS_H

/*** End of inlined file: humblenet_alias.h ***/

#define NOMINMAX

#include <cassert>

#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#if defined(__APPLE__) || defined(__linux__)
	#include <sys/utsname.h>
#endif

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#else
	#include <sys/time.h>
#endif

#if defined(EMSCRIPTEN)
	#include <emscripten/emscripten.h>
#endif


/*** Start of inlined file: humblenet_utils.h ***/
#ifndef HUMBLENET_UTILS_H
#define HUMBLENET_UTILS_H

template <typename A, typename B>
class BidiractionalMap {
public:
	typedef A key_type;
	typedef B mapped_type;
	typedef std::map<A, B> AtoB;
	typedef std::map<B, A> BtoA;
private:
	AtoB list_a;
	BtoA list_b;
public:
	void insert(const A& a, const B& b) {
		list_a.emplace(a, b);
		list_b.emplace(b, a);
	}

	void erase(const A& a) {
		auto it = list_a.find(a);
		if (it != list_a.end()) {
			list_b.erase(it->second);
			list_a.erase(it);
		}
	}

	void erase(const B& a) {
		auto it = list_b.find(a);
		if (it != list_b.end()) {
			list_a.erase(it->second);
			list_b.erase(it);
		}
	}

	void erase(typename AtoB::iterator& it) {
		list_b.erase(it->second);
		list_a.erase(it);
	}

	void erase(typename BtoA::iterator& it) {
		list_a.erase(it->second);
		list_b.erase(it);
	}

	typename AtoB::iterator find(const A& a) { return list_a.find(a); }

	typename BtoA::iterator find(const B& b) { return list_b.find(b); }

	bool is_end(typename AtoB::iterator& it) {
		return list_a.end() == it;
	}

	bool is_end(typename BtoA::iterator& it) {
		return list_b.end() == it;
	}
};

template< class MapType >
void erase_value( MapType& map, const typename MapType::mapped_type& value ) {
	for( auto it = map.begin(); it != map.end(); ){
		if( it->second == value )
			map.erase( it++ );
		else
			++it;
	}
}

#endif // HUMBLENET_UTILS_H
/*** End of inlined file: humblenet_utils.h ***/

#define USE_STUN

HumbleNetState humbleNetState;

#ifdef WIN32
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
uint64_t sys_milliseconds(void)
{
	FILETIME ft;
	ULARGE_INTEGER temp;

	GetSystemTimeAsFileTime(&ft);
	memcpy(&temp, &ft, sizeof(temp));

	return (temp.QuadPart - DELTA_EPOCH_IN_MICROSECS) / 100000;
}

#else
uint64_t sys_milliseconds (void)
{
	struct timeval tp;
	struct timezone tzp;
	static uint64_t	secbase = 0;

	gettimeofday(&tp, &tzp);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return tp.tv_usec/1000;
	}

	return (tp.tv_sec - secbase)*1000 + tp.tv_usec/1000;
}
#endif

void blacklist_peer( PeerId peer ) {
	humbleNetState.peerBlacklist.insert( std::make_pair( peer, sys_milliseconds() + 5000 ) );
}

/*
 * Deterimine if the peer is currently blacklisted.
 *
 * Side effect: will clear expired blacklist entries.
 */
bool is_peer_blacklisted( PeerId peer_id ) {
	auto it = humbleNetState.peerBlacklist.find(peer_id);
	if( it == humbleNetState.peerBlacklist.end() )
		return false;

	if( it->second <= sys_milliseconds() ) {
		humbleNetState.peerBlacklist.erase(it);
		return true;
	}

	return true;
}

/*
 * See if we can try a connection to this peer
 *
 * Side effect: sets error to reason on failure
 */
bool can_try_peer( PeerId peer_id ) {
	if (!humbleNetState.p2pConn) {
		humblenet_set_error("Signaling connection not established");
		// no signaling connection
		return false;
	}
	if (humbleNetState.myPeerId == 0) {
		humblenet_set_error("No peer ID from server");
		return false;
	}
	if (humbleNetState.pendingPeerConnectionsOut.find(peer_id)
		!= humbleNetState.pendingPeerConnectionsOut.end()) {
		// error, already a pending outgoing connection to this peer
		humblenet_set_error("already a pending connection to peer");
		LOG("humblenet_connect_peer: already a pending connection to peer %u\n", peer_id);
		return false;
	}
	if( is_peer_blacklisted(peer_id) ) {
		// peer is currently black listed
		humblenet_set_error("peer blacklisted");
		LOG("humblenet_connect_peer: peer blacklisted %u\n", peer_id);
		return false;
	}

	return true;
}

// BEGIN CONNECTION HANDLING

void humblenet_connection_set_closed( Connection* conn ) {
	if( conn->socket ) {
		// clear our state first so callbacks dont work on us.
		humbleNetState.connections.erase(conn->socket);
		internal_set_data(conn->socket, NULL );
		internal_close_socket(conn->socket);
		conn->socket = NULL;
	}

	if( conn->inOrOut == Incoming ) {
		blacklist_peer( conn->otherPeer );
	}

	conn->status = HUMBLENET_CONNECTION_CLOSED;

	LOG("Marking connections closed: %u\n", conn->otherPeer );

	// make sure were not in any lists...
	erase_value( humbleNetState.connections, conn );
	humbleNetState.pendingNewConnections.erase( conn );
	humbleNetState.pendingDataConnections.erase( conn );
//    humbleNetState.remoteClosedConnections.erase( conn );
	erase_value( humbleNetState.pendingPeerConnectionsOut, conn );
	erase_value( humbleNetState.pendingPeerConnectionsIn, conn );
	erase_value( humbleNetState.pendingAliasConnectionsOut, conn );

	// mark it as being close pending.
	humbleNetState.remoteClosedConnections.insert( conn );
}

ha_bool humblenet_connection_is_readable(Connection *connection) {
	return !connection->recvBuffer.empty();
}

ha_bool humblenet_connection_is_writable(Connection *connection) {
	assert(connection != NULL);
	if (connection->status == HUMBLENET_CONNECTION_CONNECTED) {
		return connection->writable;
	}
	return false;
}

int humblenet_connection_write(Connection *connection, const void *buf, uint32_t bufsize) {
	assert(connection != NULL);

	switch (connection->status) {
		case HUMBLENET_CONNECTION_CLOSED:
			// connection has been closed
			assert(connection->socket == NULL);
			return -1;

		case HUMBLENET_CONNECTION_CONNECTING:
			assert(connection->socket != NULL);
			return 0;

		case HUMBLENET_CONNECTION_CONNECTED:
			assert(connection->socket != NULL);

			const char* use_relay = humblenet_get_hint("p2p_use_relay");
			if( use_relay && *use_relay == '1' ) {
				if( ! sendP2PRelayData( humbleNetState.p2pConn.get(), connection->otherPeer, buf, bufsize ) ) {
					return -1;
				}
				return bufsize;
			}

			return internal_write_socket( connection->socket, buf, bufsize );
	}
	return -1;
}

int humblenet_connection_read(Connection *connection, void *buf, uint32_t bufsize) {
	assert(connection != NULL);

	switch (connection->status) {
		case HUMBLENET_CONNECTION_CLOSED:
			// connection has been closed
			assert(connection->socket == NULL);
			return -1;

		case HUMBLENET_CONNECTION_CONNECTING:
			assert(connection->socket != NULL);
			return 0;

		case HUMBLENET_CONNECTION_CONNECTED:
			assert(connection->socket != NULL);

			if( connection->recvBuffer.empty() )
				return 0;

			bufsize = std::min<uint32_t>(bufsize, connection->recvBuffer.size() );
			memcpy(buf, &connection->recvBuffer[0], bufsize);
			connection->recvBuffer.erase(connection->recvBuffer.begin()
										 , connection->recvBuffer.begin() + bufsize);

			if( ! connection->recvBuffer.empty() )
				humbleNetState.pendingDataConnections.insert(connection);
			else
				humbleNetState.pendingDataConnections.erase(connection);

			return bufsize;
	}
	return -1;
}

ConnectionStatus humblenet_connection_status(Connection *connection) {
	assert(connection != NULL);

	return connection->status;
}

Connection *humblenet_connect_websocket(const char *server_addr) {
	humblenet_set_error("Websocket support deprecated");
	return NULL;
}

Connection *humblenet_connect_peer(PeerId peer_id) {
	if( ! can_try_peer( peer_id ) )
		return NULL;

	Connection *connection = new Connection(Outgoing);
	connection->otherPeer = peer_id;
	connection->socket = internal_create_webrtc(humbleNetState.context);
	internal_set_data(connection->socket, connection);

	humbleNetState.pendingPeerConnectionsOut.emplace(peer_id, connection);

	if( ! internal_create_offer( connection->socket ) ) {
		LOG("Unable to generate sdp offer to peer: %d\n", peer_id);
		humblenet_set_error("Unable to generate sdp offer");
		humblenet_connection_close(connection);
		return NULL;
	}

	LOG("connecting to peer: %d\n", peer_id);
	return connection;
}

void humblenet_connection_close(Connection *connection) {
	assert(connection != NULL);

	humblenet_connection_set_closed(connection);

	internal_alias_remove_connection( connection );

	humbleNetState.remoteClosedConnections.erase(connection);

	delete connection;
}

PeerId humblenet_connection_get_peer_id(Connection *connection) {
	assert(connection != NULL);

	return connection->otherPeer;
}

// called to return the sdp offer
int on_sdp( internal_socket_t* s, const char* offer, void* user_data ) {
	Connection* conn = reinterpret_cast<Connection*>(user_data);

	if( conn == NULL ) {
		LOG("Got socket w/o state?\n");
		return -1;
	}

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTING );

	// no trickle ICE
	int flags = 0x2;

	if( conn->inOrOut == Incoming ) {
		LOG("P2PConnect SDP sent %u response offer = \"%s\"\n", conn->otherPeer, offer);
		sendP2PResponse(humbleNetState.p2pConn.get(), conn->otherPeer, offer);
	} else {
		LOG("outgoing SDP sent %u offer: \"%s\"\n", conn->otherPeer, offer);
		sendP2PConnect(humbleNetState.p2pConn.get(), conn->otherPeer, flags, offer);
	}
	return 0;
}

// called to send a candidate
int on_ice_candidate( internal_socket_t* s, const char* offer, void* user_data ) {
	Connection* conn = reinterpret_cast<Connection*>(user_data);

	if( conn == NULL ) {
		LOG("Got socket w/o state?\n");
		return -1;
	}

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTING );

	LOG("Sending ice candidate to peer: %u, %s\n", conn->otherPeer, offer );
	sendICECandidate(humbleNetState.p2pConn.get(), conn->otherPeer, offer);

	return 0;
}

// called for incomming connections to indicate the connection process is completed.
int on_accept (internal_socket_t* s, void* user_data) {
	auto it = humbleNetState.connections.find( s );

	// TODO: Rework this ?
	Connection* conn = NULL;
	if( it == humbleNetState.connections.end() ) {
		// its a websocket connection
		conn = new Connection( Incoming, s );

		// track the connection, ALL connections will reside here.
		humbleNetState.connections.insert( std::make_pair( s, conn ) );
	} else {
		// should be a webrtrc connection (as we create the socket inorder to start the process)
		conn = it->second;
	}

	// TODO: This should be "waiting for accept"
	conn->status = HUMBLENET_CONNECTION_CONNECTED;

	// expose it as an incomming connection to be accepted...
	humbleNetState.pendingNewConnections.insert( conn );

	LOG("accepted peer: %d\n", conn->otherPeer );

	return 0;
}

// called for outgoing connections to indicate the connection process is completed.
int on_connect (internal_socket_t* s, void* user_data) {
	assert( user_data );

	auto it = humbleNetState.connections.find( s );

	// TODO: Rework this ?
	Connection* conn = reinterpret_cast<Connection*>(user_data);
	if( it == humbleNetState.connections.end() ) {
		// track the connection, ALL connections will reside here.
		humbleNetState.connections.insert( std::make_pair( s, conn ) );
	}

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTING );

	// outgoing always initiates the channel
	if( conn->inOrOut == Outgoing ) {
		if( ! internal_create_channel(s, "dataChannel") )
			return -1;
	}

	LOG("connected peer: %d\n", conn->otherPeer );

	return 0;
}

int on_accept_channel( internal_socket_t* s, const char* name, void* user_data ) {
	assert( user_data );

	Connection* conn = reinterpret_cast<Connection*>(user_data);

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTING );
	conn->status = HUMBLENET_CONNECTION_CONNECTED;

	LOG("accepted channel: %d:%s\n", conn->otherPeer, name );
	return 0;
}

int on_connect_channel( internal_socket_t* s, const char* name, void* user_data ) {
	assert( user_data );

	Connection* conn = reinterpret_cast<Connection*>(user_data);

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTING );
	conn->status = HUMBLENET_CONNECTION_CONNECTED;

	LOG("connected channel: %d:%s\n", conn->otherPeer, name );
	return 0;
}

// called each time data is received.
int on_data( internal_socket_t* s, const void* data, int len, void* user_data ) {
	assert( user_data );

	Connection* conn = reinterpret_cast<Connection*>(user_data);

	assert( conn->status == HUMBLENET_CONNECTION_CONNECTED );

	if( conn->recvBuffer.empty() ) {
		assert( humbleNetState.pendingDataConnections.find(conn) == humbleNetState.pendingDataConnections.end() );
		humbleNetState.pendingDataConnections.insert(conn);
	}

	conn->recvBuffer.insert( conn->recvBuffer.end(), reinterpret_cast<const char*>(data),
							reinterpret_cast<const char*>(data)+len);
	return 0;
}

// called to indicate the connection is wriable.
int on_writable (internal_socket_t* s, void* user_data) {
	auto it = humbleNetState.connections.find( s );

	if( it != humbleNetState.connections.end() ) {
		// its not here anymore
		return -1;
	}

	Connection* conn = it->second;
	conn->writable = true;

	return 0;
}

// called when the conenction is terminated (from either side)
int on_disconnect( internal_socket_t* s, void* user_data ) {

	// find Connection object
	auto it = humbleNetState.connections.find(s);

	if (it != humbleNetState.connections.end()) {
		// it's still in connections map, not user-initiated close
		// find Connection object and set wsi to NULL
		// to signal that it's dead
		// user code will then call humblenet_close to dispose of
		// the Connection object

		humblenet_connection_set_closed( it->second );
	} else if( user_data != NULL ) {
		// just to be sure...
		humblenet_connection_set_closed( reinterpret_cast<Connection*>( user_data ) );
	}
	// if it wasn't in the table, no need to do anything
	// humblenet_close has already disposed of everything else
	return 0;
}

int on_destroy( internal_socket_t* s, void* user_data ) {
	// if no user_data attached, then nothing to cleanup.
	if( ! user_data )
		return 0;

	// make sure we are fully detached...
	Connection* conn = reinterpret_cast<Connection*>(user_data);
	humblenet_connection_set_closed( conn );

	return 0;
}

// END CONNECTION HANDLING

// BEGIN SIGNALING

static ha_bool p2pSignalProcess(const humblenet::HumblePeer::Message *msg, void *user_data);

namespace humblenet {
	ha_bool sendP2PMessage(P2PSignalConnection *conn, const uint8_t *buff, size_t length)
	{
		assert(conn != NULL);
		if (conn->wsi == NULL) {
			// this really shouldn't happen but apparently it can
			// if the game hasn't properly opened a signaling connection
			return false;
		}

		int ret = internal_write_socket(conn->wsi, (const void*)buff, length );
		assert( ret == length );

		return true;
	}

	// called for incomming connections to indicate the connection process is completed.
	int on_accept (internal_socket_t* s, void* user_data) {
		// we dont accept incomming connections
		return -1;
	}

	// called for outgoing commentions to indicate the connection process is completed.
	int on_connect (internal_socket_t* s, void* user_data) {
		assert(s != NULL);
		if (!humbleNetState.p2pConn) {
			// there is no signaling connection in humbleNetState
			// this one must be obsolete, close it
			return -1;
		}

		// temporary copy, doesn't transfer ownership
		P2PSignalConnection *conn = humbleNetState.p2pConn.get();
		if (conn->wsi != s) {
			// this connection is not the one currently active in humbleNetState.
			// this one must be obsolete, close it
			return -1;
		}
		// platform info
		std::string pinfo;
#if defined(__APPLE__) || defined(__linux__)
		struct utsname buf;
		memset(&buf, 0, sizeof(struct utsname));
		int retval = uname(&buf);
		if (retval == 0)
		{
			pinfo.append("Sysname: ");
			pinfo.append(buf.sysname);
			pinfo.append(", Release: ");
			pinfo.append(buf.release);
			pinfo.append(", Version: ");
			pinfo.append(buf.version);
			pinfo.append(", Machine: ");
			pinfo.append(buf.machine);
		}
		else
		{
			LOG("Failed getting system info with uname\n");
		}
#elif defined(_WIN32)
		OSVERSIONINFO osvi;
		ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		pinfo.append("Windows " + std::to_string(osvi.dwMajorVersion) + "." + std::to_string(osvi.dwMinorVersion) + ", build " + std::to_string(osvi.dwBuildNumber));

		SYSTEM_INFO si;
		ZeroMemory(&si, sizeof(SYSTEM_INFO));
		GetSystemInfo(&si);
		switch (si.wProcessorArchitecture)
		{
			case PROCESSOR_ARCHITECTURE_INTEL:
				pinfo.append(", Intel x86");
				break;
			case PROCESSOR_ARCHITECTURE_IA64:
				pinfo.append(", Intel Itanium");
				break;
			case PROCESSOR_ARCHITECTURE_AMD64:
				pinfo.append(", AMD or Intel x64");
				break;
			default:
				pinfo.append(", non-desktop architecture");
				break;
		}
#elif defined(EMSCRIPTEN)
		char buff[512];
		int len = EM_ASM_INT({
			var buff = new Uint8Array(Module.HEAPU8.buffer, $0, $1);
			return stringToUTF8Array(navigator.userAgent, buff, 0, $1);
		}, buff, sizeof(buff));
		pinfo = buff;
#endif

		uint8_t flags = 0;
		if (humbleNetState.webRTCSupported) {
			// No trickle ICE on native
			flags = (0x1 | 0x2);
		}
		std::map<std::string, std::string> attributes;
		attributes.emplace("platform", pinfo);
		ha_bool helloSuccess = sendHelloServer(conn, flags, humbleNetState.gameToken, humbleNetState.gameSecret, humbleNetState.authToken, humbleNetState.reconnectToken, attributes);
		if (!helloSuccess) {
			// something went wrong, close the connection
			// don't humblenet_set_error, sendHelloServer should have done that
			humbleNetState.p2pConn.reset();
			return -1;
		}
		return 0;
	}

	// called each time data is received.
	int on_data( internal_socket_t* s, const void* data, int len, void* user_data ) {
		assert(s != NULL);

		if (!humbleNetState.p2pConn) {
			// there is no signaling connection in humbleNetState
			// this one must be obsolete, close it
			return -1;
		}

		// temporary copy, doesn't transfer ownership
		P2PSignalConnection *conn = humbleNetState.p2pConn.get();
		if (conn->wsi != s) {
			// this connection is not the one currently active in humbleNetState.
			// this one must be obsolete, close it
			return -1;
		}

		//        LOG("Data: %d -> %s\n", len, std::string((const char*)data,len).c_str());

		conn->recvBuf.insert(conn->recvBuf.end()
							 , reinterpret_cast<const char *>(data)
							 , reinterpret_cast<const char *>(data) + len);
		ha_bool retval = parseMessage(conn->recvBuf, p2pSignalProcess, NULL);
		if (!retval) {
			// error while parsing a message, close the connection
			humbleNetState.p2pConn.reset();
			return -1;
		}
		return 0;
	}

	// called to indicate the connection is wriable.
	int on_writable (internal_socket_t* s, void* user_data) {
		assert(s != NULL);
		if (!humbleNetState.p2pConn) {
			// there is no signaling connection in humbleNetState
			// this one must be obsolete, close it
			return -1;
		}

		// temporary copy, doesn't transfer ownership
		P2PSignalConnection *conn = humbleNetState.p2pConn.get();
		if (conn->wsi != s) {
			// this connection is not the one currently active in humbleNetState.
			// this one must be obsolete, close it
			return -1;
		}

		if (conn->sendBuf.empty()) {
			// no data in sendBuf
			return 0;
		}

		int retval = internal_write_socket( conn->wsi, &conn->sendBuf[0], conn->sendBuf.size() );
		if (retval < 0) {
			// error while sending, close the connection
			// TODO: should try to reopen after some time
			humbleNetState.p2pConn.reset();
			return -1;
		}

		// successful write
		conn->sendBuf.erase(conn->sendBuf.begin(), conn->sendBuf.begin() + retval);

		return 0;
	}

	// called when the conenction is terminated (from either side)
	int on_disconnect( internal_socket_t* s, void* user_data ) {

		if( humbleNetState.p2pConn ) {
			if( s == humbleNetState.p2pConn->wsi ) {

				// handle retry...
				humbleNetState.p2pConn.reset();

				return 0;
			}
		}

		return 0;
	}

	void register_protocol(internal_context_t* context) {
		internal_callbacks_t callbacks;

		memset(&callbacks, 0, sizeof(callbacks));

		callbacks.on_accept = on_accept;
		callbacks.on_connect = on_connect;
		callbacks.on_data = on_data;
		callbacks.on_disconnect = on_disconnect;
		callbacks.on_writable = on_writable;

		internal_register_protocol( humbleNetState.context, "humblepeer", &callbacks );
	}
}

static ha_bool p2pSignalProcess(const humblenet::HumblePeer::Message *msg, void *user_data)
{
	using namespace humblenet;

	auto msgType = msg->message_type();

	switch (msgType) {
		case HumblePeer::MessageType::P2POffer:
		{
			auto p2p = reinterpret_cast<const HumblePeer::P2POffer*>(msg->message());
			PeerId peer = static_cast<PeerId>(p2p->peerId());

			if (humbleNetState.pendingPeerConnectionsIn.find(peer) != humbleNetState.pendingPeerConnectionsIn.end()) {
				// error, already a pending incoming connection to this peer
				LOG("p2pSignalProcess: already a pending connection to peer %u\n", peer);
				return true;
			}

			bool emulated = ( p2p->flags() & 0x1 );

			if (emulated || !humbleNetState.webRTCSupported) {
				// webrtc connections not supported
				assert(humbleNetState.p2pConn);
				sendPeerRefused(humbleNetState.p2pConn.get(), peer);
			}

			Connection *connection = new Connection(Incoming);
			connection->status = HUMBLENET_CONNECTION_CONNECTING;
			connection->otherPeer = peer;
			connection->socket = internal_create_webrtc(humbleNetState.context);
			internal_set_data( connection->socket, connection );

			humbleNetState.pendingPeerConnectionsIn.insert(std::make_pair(peer, connection));

			auto offer = p2p->offer();

			std::vector<char> payloadv(offer->begin(), offer->end());

			LOG("P2PConnect SDP got %u's offer = \"%s\"\n", peer, offer->c_str());
			if( ! internal_set_offer( connection->socket, payloadv.data() ) )
			{
				humblenet_connection_close( connection );

				sendPeerRefused(humbleNetState.p2pConn.get(), peer);
				}
		}
			break;

		case HumblePeer::MessageType::P2PAnswer:
		{
			auto p2p = reinterpret_cast<const HumblePeer::P2PAnswer*>(msg->message());
			PeerId peer = static_cast<PeerId>(p2p->peerId());

			auto it = humbleNetState.pendingPeerConnectionsOut.find(peer);
			if (it == humbleNetState.pendingPeerConnectionsOut.end()) {
				LOG("P2PResponse for connection we didn't initiate: %u\n", peer);
				return true;
			}

			Connection *conn = it->second;
			assert(conn != NULL);
			assert(conn->otherPeer == peer);

			assert(conn->socket != NULL);
			// TODO: deal with _CLOSED
			assert(conn->status == HUMBLENET_CONNECTION_CONNECTING);

			auto offer = p2p->offer();

			std::vector<char> payloadv(offer->begin(), offer->end());

			LOG("P2PResponse SDP got %u's response offer = \"%s\"\n", peer, offer->c_str());
			if( !internal_set_answer( conn->socket, payloadv.data() ) ) {
				humblenet_connection_set_closed( conn );
			}
		}
			break;

		case HumblePeer::MessageType::HelloClient:
		{
			auto hello = reinterpret_cast<const HumblePeer::HelloClient*>(msg->message());
			PeerId peer = static_cast<PeerId>(hello->peerId());

			if (humbleNetState.myPeerId != 0) {
				LOG("Error: got HelloClient but we already have a peer id\n");
				return true;
			}
			LOG("My peer id is %u\n", peer);
			humbleNetState.myPeerId = peer;

			humbleNetState.iceServers.clear();

			if (hello->iceServers()) {
				auto iceList = hello->iceServers();
				for (const auto& it : *iceList) {
					if (it->type() == HumblePeer::ICEServerType::STUNServer) {
						humbleNetState.iceServers.emplace_back(it->server()->str());
					} else if (it->type() == HumblePeer::ICEServerType::TURNServer) {
						auto username = it->username();
						auto pass = it->password();
						if (pass && username) {
							humbleNetState.iceServers.emplace_back(it->server()->str(), username->str(), pass->str());
						}
					}
				}
			} else {
				LOG("No STUN/TURN credentials provided by the server\n");
			}

			std::vector<const char*> stunServers;
			for (auto& it : humbleNetState.iceServers) {
				if (it.type == HumblePeer::ICEServerType::STUNServer) {
					stunServers.emplace_back(it.server.c_str());
				}
			}
			internal_set_stun_servers(humbleNetState.context, stunServers.data(), stunServers.size());
			//            internal_set_turn_server( server.c_str(), username.c_str(), password.c_str() );
		}
			break;

		case HumblePeer::MessageType::ICECandidate:
		{
			auto iceCandidate = reinterpret_cast<const HumblePeer::ICECandidate*>(msg->message());
			PeerId peer = static_cast<PeerId>(iceCandidate->peerId());

			auto it = humbleNetState.pendingPeerConnectionsIn.find( peer );

			if( it == humbleNetState.pendingPeerConnectionsIn.end() )
			{
				it = humbleNetState.pendingPeerConnectionsOut.find( peer );
				if( it == humbleNetState.pendingPeerConnectionsOut.end() )
				{
					// no connection waiting on a peer.
					return true;
				}
			}

			if( it->second->socket && it->second->status == HUMBLENET_CONNECTION_CONNECTING ) {
				auto offer = iceCandidate->offer();
				LOG("Got ice candidate from peer: %d, %s\n", it->second->otherPeer, offer->c_str() );

				internal_add_ice_candidate( it->second->socket, offer->c_str() );
			}
		}
			break;

		case HumblePeer::MessageType::P2PReject:
		{
			auto reject = reinterpret_cast<const HumblePeer::P2PReject*>(msg->message());
			PeerId peer = static_cast<PeerId>(reject->peerId());

			auto it = humbleNetState.pendingPeerConnectionsOut.find(peer);
			if (it == humbleNetState.pendingPeerConnectionsOut.end()) {
				switch (reject->reason()) {
					case HumblePeer::P2PRejectReason::NotFound:
						LOG("Peer %u does not exist\n", peer);
						break;
					case HumblePeer::P2PRejectReason::PeerRefused:
						LOG("Peer %u rejected our connection\n", peer);
						break;
				}
				return true;
			}

			Connection *conn = it->second;
			assert(conn != NULL);

			blacklist_peer(peer);
			humblenet_connection_set_closed(conn);
		}
			break;

		case HumblePeer::MessageType::P2PConnected:
		{
			auto connect = reinterpret_cast<const HumblePeer::P2PConnected*>(msg->message());

			LOG("Established connection to peer %u", connect->peerId());
		}
			break;

		case HumblePeer::MessageType::P2PDisconnect:
		{
			auto disconnect = reinterpret_cast<const HumblePeer::P2PDisconnect*>(msg->message());

			LOG("Disconnecting peer %u", disconnect->peerId());
		}
			break;

		case HumblePeer::MessageType::P2PRelayData:
		{
			auto relay = reinterpret_cast<const HumblePeer::P2PRelayData*>(msg->message());
			auto peer = relay->peerId();
			auto data = relay->data();

			LOG("Got %d bytes relayed from peer %u\n", data->Length(), peer );

			// Brute force...
			auto it = humbleNetState.connections.begin();
			for( it = humbleNetState.connections.begin(); it != humbleNetState.connections.end(); ++it ) {
			   if( it->second->otherPeer == peer )
				   break;
			}
			if( it == humbleNetState.connections.end() ) {
				LOG("Peer %u does not exist\n", peer);
			} else {
				Connection* conn = it->second;

				conn->recvBuffer.insert(conn->recvBuffer.end()
									 , reinterpret_cast<const char *>(data->Data())
									 , reinterpret_cast<const char *>(data->Data()) + data->Length());
				humbleNetState.pendingDataConnections.insert( conn );
			}
		}
			break;
		case HumblePeer::MessageType::AliasResolved:
		{
			auto reolved = reinterpret_cast<const HumblePeer::AliasResolved*>(msg->message());

			internal_alias_resolved_to( reolved->alias()->c_str(), reolved->peerId() );
		}
			break;

		default:
			LOG("p2pSignalProcess unhandled %s\n", HumblePeer::EnumNameMessageType(msgType));
			break;
	}

	return true;
}

ha_bool humblenet_p2p_connect_server() {
	using namespace humblenet;

	if (humbleNetState.p2pConn) {
		humbleNetState.p2pConn->disconnect();
		humbleNetState.p2pConn.reset();
		humbleNetState.myPeerId = 0;
	}

	LOG("connecting to signaling server \"%s\" with gameToken \"%s\" \n", humbleNetState.signalingServerAddr.c_str(), humbleNetState.gameToken.c_str());

	humbleNetState.p2pConn.reset(new P2PSignalConnection);
	humbleNetState.p2pConn->wsi = internal_connect_websocket(humbleNetState.signalingServerAddr.c_str(), "humblepeer");

	if (humbleNetState.p2pConn->wsi == NULL) {
		humbleNetState.p2pConn.reset();
		// TODO: can we get more specific reason ?
		humblenet_set_error("WebSocket connection to signaling server failed");
		return false;
	}

	LOG("new wsi: %p\n", humbleNetState.p2pConn->wsi);

	internal_poll_io();
	return true;
}
// END SIGNALING

// BEGIN INITIALIZATION

ha_bool HUMBLENET_CALL humblenet_init() {
	return true;
}

ha_bool internal_p2p_register_protocol() {
	internal_callbacks_t callbacks;

	memset(&callbacks, 0, sizeof(callbacks));

	callbacks.on_sdp = on_sdp;
	callbacks.on_ice_candidate = on_ice_candidate;
	callbacks.on_accept = on_accept;
	callbacks.on_connect = on_connect;
	callbacks.on_accept_channel = on_accept_channel;
	callbacks.on_connect_channel = on_connect_channel;
	callbacks.on_data = on_data;
	callbacks.on_disconnect = on_disconnect;
	callbacks.on_writable = on_writable;

	humbleNetState.context = internal_init(  &callbacks );
	if (humbleNetState.context == NULL) {
		return false;
	}

	humblenet::register_protocol(humbleNetState.context);

	humbleNetState.webRTCSupported = internal_supports_webRTC( humbleNetState.context );

	return true;
}

#ifndef EMSCRIPTEN
extern "C" void poll_deinit();
#endif

void HUMBLENET_CALL humblenet_shutdown() {
	// Destroy all connections
	for( auto it = humbleNetState.connections.begin(); it != humbleNetState.connections.end(); ) {
		Connection* conn = it->second;
		++it;
		humblenet_connection_close( conn );
	}
	// drop the server
	if( humbleNetState.p2pConn ) {
		humbleNetState.p2pConn->disconnect();
		humbleNetState.p2pConn.reset();
	}

	internal_deinit(humbleNetState.context);
	humbleNetState.context = NULL;

#ifndef EMSCRIPTEN
	poll_deinit();
#endif
}

// END INITIALIZATION

// BEGIN MISC

ha_bool HUMBLENET_CALL humblenet_p2p_supported() {
	// This function should really be "humblenet_has_webrtc"
	// but could be removed entirely from the API
	return humbleNetState.webRTCSupported;
}

#if defined(WIN32)
#define THREAD_LOCAL __declspec(thread)
#else // Everyone else
#define THREAD_LOCAL __thread
#endif

THREAD_LOCAL const char* errorString = nullptr;

const char * HUMBLENET_CALL humblenet_get_error() {
	return errorString;
}

void HUMBLENET_CALL humblenet_set_error(const char *error) {
	errorString = error;
}

void HUMBLENET_CALL humblenet_clear_error() {
	errorString = nullptr;
}

// END MISC

// BEGIN DEPRECATED

void *humblenet_connection_read_all(Connection *connection, int *retval) {
	assert(connection != NULL);

	if (connection->status == HUMBLENET_CONNECTION_CONNECTING) {
		// not open yet
		return 0;
	}

	if (connection->recvBuffer.empty()) {
		// must not be in poll-returnable connections anymore
		assert(humbleNetState.pendingDataConnections.find(connection) == humbleNetState.pendingDataConnections.end());

		if (connection->status == HUMBLENET_CONNECTION_CLOSED) {
			// TODO: Connection should contain reason it was closed and we should report that
			humblenet_set_error("Connection closed");
			*retval = -1;
			return NULL;
		}

		*retval = 0;
		return NULL;
	}

	size_t dataSize = connection->recvBuffer.size();
	void *buf = malloc(dataSize);

	if (buf == NULL) {
		humblenet_set_error("Memory allocation failed");
		*retval = -1;
		return NULL;
	}

	memcpy(buf, &connection->recvBuffer[0], dataSize);
	connection->recvBuffer.clear();

	auto it = humbleNetState.pendingDataConnections.find(connection);
	assert(it != humbleNetState.pendingDataConnections.end());
	humbleNetState.pendingDataConnections.erase(it);

	*retval = dataSize;
	return buf;
}

Connection *humblenet_poll_all(int timeout_ms) {
	{
		// check for connections closed by remote and notify user
		auto it = humbleNetState.remoteClosedConnections.begin();
		if (it != humbleNetState.remoteClosedConnections.end()) {
			Connection *conn = *it;
			humbleNetState.remoteClosedConnections.erase(it);
			return conn;
		}

		it = humbleNetState.pendingDataConnections.begin();
		if (it != humbleNetState.pendingDataConnections.end()) {
			// don't remove it from the set, _recv will do that
			Connection *conn = *it;
			assert(conn != NULL);
			assert(!conn->recvBuffer.empty());
			return conn;
		}
	}

	// call service if no outstanding data on any connection
	internal_poll_io(/*timeout_ms*/);

	{
		auto it = humbleNetState.pendingDataConnections.begin();
		if (it != humbleNetState.pendingDataConnections.end()) {
			// don't remove it from the set, _recv will do that
			Connection *conn = *it;
			assert(conn != NULL);
			assert(!conn->recvBuffer.empty());
			return conn;
		}
	}

	return NULL;
}

Connection *humblenet_connection_accept() {
	{
		auto it = humbleNetState.pendingNewConnections.begin();

		if (it != humbleNetState.pendingNewConnections.end()) {
			Connection *conn = *it;
			humbleNetState.pendingNewConnections.erase(it);
			return conn;
		}
	}

	// call service so something happens
	// TODO: if we replace poll loop with our own we could poll only the master socket
	internal_poll_io();

	{
		auto it = humbleNetState.pendingNewConnections.begin();
		if (it != humbleNetState.pendingNewConnections.end()) {
			Connection *conn = *it;
			humbleNetState.pendingNewConnections.erase(it);
			return conn;
		}
	}

	return NULL;
}

// END DEPRECATED

static std::unordered_map<std::string, std::string> hints;

/*
 * Set the value of a hint
 */
HUMBLENET_API ha_bool HUMBLENET_CALL humblenet_set_hint(const char* name, const char* value) {
	auto it = hints.find( name );
	if( it != hints.end() )
		it->second = value;
	else
		hints.insert( std::make_pair( name, value ) );
}

/*
 * Get the value of a hint
 */
HUMBLENET_API const char* HUMBLENET_CALL humblenet_get_hint(const char* name) {
	auto it = hints.find( name );
	if( it != hints.end() )
		return it->second.c_str();
	else
		return NULL;
}

#ifndef EMSCRIPTEN

#include "libpoll.h"	// SKIP_AMALGAMATOR_INCLUDE

void humblenet_lock() {
	poll_lock();
}

void humblenet_unlock() {
	poll_unlock();
}

#else

void humblenet_lock() {
}

void humblenet_unlock() {
}

#endif

/*** End of inlined file: humblenet_core.cpp ***/


// Datagram

/*** Start of inlined file: humblenet_datagram.cpp ***/

/*** Start of inlined file: humblenet_datagram.h ***/
#ifndef HUMBLENET_DATAGRAM_H
#define HUMBLENET_DATAGRAM_H

#define HUMBLENET_MSG_PEEK 0x1
#define HUMBLENET_MSG_BUFFERED 0x02

/*
* Send a message to a connection
*/
int humblenet_datagram_send( const void* message, size_t length, int flags, struct Connection* toconn, uint8_t channel );

/*
* Receive a message sent from a connection
*/
int humblenet_datagram_recv( void* buffer, size_t length, int flags, struct Connection** fromconn, uint8_t channel );

/*
* See if there is a message waiting on the specified channel
*/
ha_bool humblenet_datagram_select( size_t* length, uint8_t channel );

/*
* Flush any pending packets
*/
ha_bool humblenet_datagram_flush();

#endif // HUMBLENET_DATAGRAM_H

/*** End of inlined file: humblenet_datagram.h ***/

// TODO : If this had access to the internals of Connection it could be further optimized.

#include <map>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <algorithm>

struct datagram_connection {
	Connection*         conn;           // established connection.
	PeerId              peer;           // "address"

	std::vector<char>   buf_in;         // data we have received buy not yet processed.
	std::vector<char>   buf_out;        // packet combining...
	int                 queued;

	uint32_t seq_out = 0;
	uint32_t seq_in = 0;

	datagram_connection( Connection* conn, bool outgoing )
	:conn( conn )
	,peer( humblenet_connection_get_peer_id( conn ) )
	,queued( 0 )
	,seq_out( 0 )
	,seq_in( 0 )
	{
	}
};

typedef std::map<Connection*, datagram_connection> ConnectionMap;

static ConnectionMap    connections;
static bool             queuedPackets = false;

struct datagram_header {
	uint16_t size;
	uint8_t  channel;
	uint32_t seq;

	uint8_t data[];
};

static int datagram_get_message( datagram_connection& conn, const void* buffer, size_t length, int flags, uint8_t channel ) {

	std::vector<char>& in = conn.buf_in;
	std::vector<char>::iterator start = in.begin();

restart:

	uint16_t available = in.end() - start;

	if( available <= sizeof( datagram_header ) )
		return -1;

	datagram_header* hdr = reinterpret_cast<datagram_header*>(&in[start - in.begin()]);

	if ((hdr->size + sizeof(datagram_header)) > available) {
		// incomplete packet
		LOG("Incomplete packet from %u\n", conn.peer );
		return -1;
	}

	auto end = start + sizeof(datagram_header) + hdr->size;

	if( hdr->channel != channel ) {
		TRACE("Incorrect channel: wanted %d but got %d(%u) from %u\n", channel, hdr->channel, hdr->size, conn.peer );

		// skip to next packet.
		start = end;

		goto restart;
	}

	if( flags & HUMBLENET_MSG_PEEK )
		return hdr->size;

	// prevent buffer overrins on read.
	// this WILL truncate the message if the supplied buffer is not big enough -- see IEEE Std -> recvfrom.
	length = std::min<size_t>( length, hdr->size );
	memcpy((char*)buffer, hdr->data, length);

	// since we are accesing hdr directly out of the buffer, we need a local to store the msg size that was read.
	uint16_t size = hdr->size;
	in.erase(start, end);

	return size;
}

static void datagram_flush( datagram_connection& dg, const char* reason ) {
	if( ! dg.buf_out.empty() )
	{
		if( ! humblenet_connection_is_writable( dg.conn ) ) {
			LOG("Waiting(%s) %d packets (%zu bytes) to  %p\n", reason, dg.queued, dg.buf_out.size(), dg.conn );
			return;
		}

		if( dg.queued > 1 )
			LOG("Flushing(%s) %d packets (%zu bytes) to  %p\n", reason, dg.queued, dg.buf_out.size(), dg.conn );
		int ret = humblenet_connection_write( dg.conn, &dg.buf_out[0], dg.buf_out.size() );
		if( ret < 0 ) {
			LOG("Error flushing packets: %s", humblenet_get_error() );
			humblenet_clear_error();
		}
		dg.buf_out.clear();
		dg.queued = 0;
	}
}

int humblenet_datagram_send( const void* message, size_t length, int flags, Connection* conn, uint8_t channel )
{
	// if were still connecting, we cant write yet
	// TODO: Should we queue that data up?
	switch( humblenet_connection_status( conn ) ) {
		case HUMBLENET_CONNECTION_CONNECTING: {
			// If send using buffered, then allow messages to be queued till were connected.
			if( flags & HUMBLENET_MSG_BUFFERED )
				break;

			humblenet_set_error("Connection is still being establisted");
			return 0;
		}
		case HUMBLENET_CONNECTION_CLOSED: {
			humblenet_set_error("Connection is closed");
			// should this wipe the state ?
			return -1;
		}
		default: {
			break;
		}
	}

	ConnectionMap::iterator it = connections.find( conn );
	if( it == connections.end() ) {
		connections.insert( ConnectionMap::value_type( conn, datagram_connection( conn, false ) ) );
		it = connections.find( conn );
	}

	datagram_connection& dg = it->second;

	datagram_header hdr;

	hdr.size = length;
	hdr.channel = channel;
	hdr.seq = dg.seq_out++;

	dg.buf_out.reserve( dg.buf_out.size() + length + sizeof(datagram_header) );

	dg.buf_out.insert( dg.buf_out.end(), reinterpret_cast<const char*>( &hdr ), reinterpret_cast<const char*>( &hdr ) + sizeof( datagram_header ) );
	dg.buf_out.insert( dg.buf_out.end(), reinterpret_cast<const char*>( message ), reinterpret_cast<const char*>( message ) + length );

	dg.queued++;

	if( !( flags & HUMBLENET_MSG_BUFFERED ) ) {
		datagram_flush( dg, "no-delay" );
	} else if( dg.buf_out.size() > 1024 ) {
		datagram_flush( dg, "max-length" );
	} else {
		queuedPackets = true;
		//if( dg.queued > 1 )
		//    LOG("Queued %d packets (%zu bytes) for  %p\n", dg.queued, dg.buf_out.size(), dg.conn );
	}
	return length;
}

int humblenet_datagram_recv( void* buffer, size_t length, int flags, Connection** fromconn, uint8_t channel )
{
	// flush queued packets
	if( queuedPackets ) {
		for( ConnectionMap::iterator it = connections.begin(); it != connections.end(); ++it ) {
			datagram_flush( it->second, "auto" );
		}
		queuedPackets = false;
	}

	// first we drain all existing packets.
	for( ConnectionMap::iterator it = connections.begin(); it != connections.end(); ++it ) {
		int ret = datagram_get_message( it->second, buffer, length, flags, channel );
		if( ret > 0 ) {
			*fromconn = it->second.conn;
			return ret;
		}
	}

	// next check for incomming data on existing connections...
	while(true) {
		Connection* conn = humblenet_poll_all(0);
		if( conn == NULL )
			break;

		PeerId peer = humblenet_connection_get_peer_id( conn );

		ConnectionMap::iterator it = connections.find( conn );
		if( it == connections.end() ) {
			// hmm connection not cleaned up properly...
			LOG("received data from peer %u, but we have no datagram_connection for them\n", peer );
			connections.insert( ConnectionMap::value_type( conn, datagram_connection( conn, false ) ) );
			it = connections.find( conn );
		}

		// read whatever we can...
		int retval = 0;
		char* buf = (char*)humblenet_connection_read_all(conn, &retval );
		if( retval < 0 ) {
			free( buf );
			connections.erase( it );
			LOG("read from peer %u(%p) failed with %s\n", peer, conn, humblenet_get_error() );
			humblenet_clear_error();
			if( humblenet_connection_status( conn ) == HUMBLENET_CONNECTION_CLOSED ) {
				*fromconn = conn;
				return -1;
			}
			continue;
		} else {
			it->second.buf_in.insert( it->second.buf_in.end(), buf, buf+retval );
			free( buf );
			retval = datagram_get_message( it->second, buffer, length, flags, channel );
			if( retval > 0 ) {
				*fromconn = it->second.conn;
				return retval;
			}
		}
	}

	// no existing connections have a packet ready, see if we have any new connections
	while( true ) {
		Connection* conn = humblenet_connection_accept();
		if( conn == NULL )
			break;

		PeerId peer = humblenet_connection_get_peer_id( conn );
		if( peer == 0 ) {
			// Not a peer connection?
			LOG("Accepted connection, but not a peer connection: %p\n", conn);
		   // humblenet_connection_close( conn );
			continue;
		}

		connections.insert( ConnectionMap::value_type( conn, datagram_connection( conn, false ) ) );
	}

	return 0;
}

/*
* See if there is a message waiting on the specified channel
*/
ha_bool humblenet_datagram_select( size_t* length, uint8_t channel ) {
	Connection* conn = NULL;
	int ret = humblenet_datagram_recv( NULL, 0, HUMBLENET_MSG_PEEK, &conn, channel );
	if( ret > 0 )
		*length = ret;
	else
		*length = 0;

	return *length > 0;
}

ha_bool humblenet_datagram_flush() {
	// flush queued packets
	if( queuedPackets ) {
		for( ConnectionMap::iterator it = connections.begin(); it != connections.end(); ++it ) {
			datagram_flush( it->second, "manual" );
		}
		queuedPackets = false;
		return true;
	}
	return false;
}

/*** End of inlined file: humblenet_datagram.cpp ***/


// P2P

/*** Start of inlined file: humblenet_p2p.cpp ***/
#include <string>
#include <map>

#define P2P_INIT_GUARD( ... )    INIT_GUARD( "humblenet_p2p_init has not been called", initialized, __VA_ARGS__ )

// These are the connections managed by p2p...
std::map<PeerId, Connection*> p2pconnections;

static bool initialized = false;

ha_bool humblenet_p2p_connect_server();

/*
 * Is the peer-to-peer network initialized.
 */
ha_bool HUMBLENET_CALL humblenet_p2p_is_initialized() {
	return initialized;
}

/*
 * Initialize the peer-to-peer library.
 */
ha_bool HUMBLENET_CALL humblenet_p2p_init(const char* server, const char* game_token, const char* game_secret, const char* auth_token) {
	if( initialized ) {
		return 1;
	}

	if (!server || !game_token || !game_secret) {
		humblenet_set_error("Must specify server, game_token, and game_secret");
		return 0;
	}
	initialized = true;
	humbleNetState.signalingServerAddr = server;
	humbleNetState.gameToken = game_token;
	humbleNetState.gameSecret = game_secret;
	humbleNetState.reconnectToken = "";

	if( auth_token ) {
		humbleNetState.authToken = auth_token;
	} else {
		humbleNetState.authToken = "";
	}

	internal_p2p_register_protocol();

	humblenet_p2p_connect_server();

	return 1;
}

/*
 * Shut down the networking library
 */
void HUMBLENET_CALL humblenet_p2p_shutdown() {
	// disconnect from signaling server, shutdown all p2p connections, etc.
	initialized = false;
	humblenet_shutdown();
}

/*
 * Get the current peer ID of this client
 * returns 0 if not yet connected
 */
PeerId HUMBLENET_CALL humblenet_p2p_get_my_peer_id() {
	P2P_INIT_GUARD( 0 );

	return humbleNetState.myPeerId;
}

/*
 * Register an alias for this peer so it can be found by name
 */
ha_bool HUMBLENET_CALL humblenet_p2p_register_alias(const char* name) {
	P2P_INIT_GUARD( false );

	HUMBLENET_GUARD();

	return internal_alias_register( name );
}

/*
 * Unregister an alias of this peer.
 */
ha_bool HUMBLENET_CALL humblenet_p2p_unregister_alias(const char* name) {
	P2P_INIT_GUARD( false );

	HUMBLENET_GUARD();

	return internal_alias_unregister( name );
}

/*
 * Find the PeerId of a named peer (registered on the server)
 */
PeerId HUMBLENET_CALL humblenet_p2p_virtual_peer_for_alias(const char* name) {
	P2P_INIT_GUARD( 0 );

	HUMBLENET_GUARD();

	return internal_alias_lookup( name );
}

/*
 * Send a message to a peer.
 */
int HUMBLENET_CALL humblenet_p2p_sendto(const void* message, uint32_t length, PeerId topeer, SendMode sendmode, uint8_t channel) {
	P2P_INIT_GUARD( -1 );

	HUMBLENET_GUARD();

	Connection* conn = NULL;

	auto cit = p2pconnections.find( topeer );
	if( cit != p2pconnections.end() ) {
		// we have an active connection
		conn = cit->second;
	} else if( internal_alias_is_virtual_peer( topeer ) ) {
		// lookup/create a connection to the virutal peer.
		conn = internal_alias_find_connection( topeer );
		if( conn == NULL )
			conn = internal_alias_create_connection( topeer );
	} else {
		// create a new connection to the peer
		conn = humblenet_connect_peer( topeer );
	}

	if( conn == NULL ) {
		humblenet_set_error("Unable to get a connection for peer");
		return -1;
	} else if( cit == p2pconnections.end() ) {
		p2pconnections.insert( std::make_pair( topeer, conn ) );
		LOG("Connection to peer opened: %u\n", topeer );
	}

	int flags = 0;

	if( sendmode & SEND_RELIABLE_BUFFERED )
		flags = HUMBLENET_MSG_BUFFERED;
	// if were still connecting and reliable, treat it as a buffered request
	else if( conn->status == HUMBLENET_CONNECTION_CONNECTING )
		flags = HUMBLENET_MSG_BUFFERED;

	int ret = humblenet_datagram_send( message, length, flags, conn, channel );
	TRACE("Sent packet for channel %d to %u(%u): %d\n", channel, topeer, conn->otherPeer, ret );
	if( ret < 0 ) {
		LOG("Peer  %p(%u) write failed: %s\n", conn, topeer, humblenet_get_error() );
		if( humblenet_connection_status( conn ) == HUMBLENET_CONNECTION_CLOSED ) {
			LOG("Peer connection was closed\n");

			p2pconnections.erase( conn->otherPeer );
			p2pconnections.erase( topeer );
			humblenet_connection_close(conn);

			humblenet_set_error("Connection to peer was closed");
			return -1;
		}
	}
	return ret;
}

/*
 * See if there is a message available on the specified channel
 */
ha_bool HUMBLENET_CALL humblenet_p2p_peek(uint32_t* length, uint8_t channel) {
	P2P_INIT_GUARD( false );

	HUMBLENET_GUARD();

	Connection* from;
	int ret = humblenet_datagram_recv( NULL, 0, 1/*MSG_PEEK*/, &from, channel );
	if( ret > 0 )
		*length = ret;
	else
		*length = 0;

	return *length > 0;
}

/*
 * Receive a message sent from a peer
 */
int HUMBLENET_CALL humblenet_p2p_recvfrom(void* buffer, uint32_t length, PeerId* frompeer, uint8_t channel) {
	P2P_INIT_GUARD( 0 );

	HUMBLENET_GUARD();

	Connection* conn = NULL;
	int ret = humblenet_datagram_recv( buffer, length, 0, &conn, channel );
	if( !conn || !ret ) {
		*frompeer = 0;
	} else {
		PeerId vpeer = internal_alias_get_virtual_peer( conn );
		PeerId peer = conn->otherPeer;

		if( vpeer )
			*frompeer = vpeer;
		else
			*frompeer = peer;

		if( ret > 0 ) {
			TRACE("Got packet for channel %d from %u(%u)\n", channel, *frompeer, peer );
			if( p2pconnections.find( *frompeer ) == p2pconnections.end() ) {
				LOG("Tracking inbound connection to peer %u(%u)\n", *frompeer, peer );
				p2pconnections.insert( std::make_pair( *frompeer, conn ) );
			}
		} else {
			p2pconnections.erase( *frompeer );
			p2pconnections.erase( peer );
			humblenet_connection_close(conn);
			LOG("closing connection to peer: %u(%u)\n",*frompeer,peer);
		}
	}
	return ret;
}

/*
 * Disconnect a peer
 */
ha_bool HUMBLENET_CALL humblenet_p2p_disconnect(PeerId peer) {
	P2P_INIT_GUARD( false );

	HUMBLENET_GUARD();

	auto it = p2pconnections.find( peer );
	if( it != p2pconnections.end() )
		humblenet_connection_set_closed( it->second );

	// TODO: Should we see if the peer that was passed in is the "real" peer instead of the VPeer?
	return 1;
}

void internal_poll_io() {
	humblenet_p2p_wait(0);
}

#ifndef EMSCRIPTEN

#include "libpoll.h"	// SKIP_AMALGAMATOR_INCLUDE

// Native only API, should be moved to its own file
int HUMBLENET_CALL humblenet_p2p_select(int nfds, fd_set *readfds, fd_set *writefds,
															 fd_set *exceptfds, struct timeval *timeout) {

	// not guard needed poll_select is internally init and thread safe.
	return poll_select( nfds, readfds, writefds, exceptfds, timeout );
}

ha_bool HUMBLENET_CALL humblenet_p2p_wait(int ms) {
	P2P_INIT_GUARD( false );

	struct timeval tv;

	// This is not really needed in a threaded environment,
	// e.g. if this is being used as a sleep till something is ready,
	// we need this. If its being used as a "let IO run" (e.g. threaded IO) then we dont.
	if( ms > 0 ) {
		HUMBLENET_GUARD();

		if( ! humbleNetState.pendingDataConnections.empty() ) {
			ms = 0;
		}
	}

	tv.tv_sec = ms / 1000;
	tv.tv_usec = 1000 * (ms % 1000);

	if( poll_select( 0, NULL, NULL, NULL, &tv ) > 0 )
		return true;
	else
	{
		HUMBLENET_GUARD();

		return ! humbleNetState.pendingDataConnections.empty() || ! humbleNetState.pendingNewConnections.empty() || ! humbleNetState.remoteClosedConnections.empty();
	}
}

#else
ha_bool HUMBLENET_CALL humblenet_p2p_wait(int ms) {
	P2P_INIT_GUARD( false );

	return ! humbleNetState.pendingDataConnections.empty() || ! humbleNetState.pendingNewConnections.empty() || ! humbleNetState.remoteClosedConnections.empty();
}
#endif

/*** End of inlined file: humblenet_p2p.cpp ***/



/*** Start of inlined file: humblenet_alias.cpp ***/
#include <cassert>
#include <map>

#define VIRTUAL_PEER 0x80000000

static BidiractionalMap<PeerId, std::string> virtualPeerNames;
static BidiractionalMap<PeerId, Connection*> virtualPeerConnections;

static PeerId nextVirtualPeer = 0;

static std::string virtualName;

ha_bool internal_alias_register( const char* name ) {
	if( !name || !name[0] ) {
		humblenet_set_error("No name or empty name provided");
		return 0;
	}

	humblenet::P2PSignalConnection *conn = humbleNetState.p2pConn.get();

	return humblenet::sendAliasRegister(conn, name);
}

ha_bool internal_alias_unregister( const char* name ) {
	if (name && !name[0] ) {
		humblenet_set_error("Empty name provided");
		return 0;
	}

	humblenet::P2PSignalConnection *conn = humbleNetState.p2pConn.get();
	if (!name) name = "";

	return humblenet::sendAliasUnregister(conn, name);
}

PeerId internal_alias_lookup( const char* name ) {
	auto it = virtualPeerNames.find( name );
	if( ! virtualPeerNames.is_end(it) ) {
		return it->second;
	}

	// allocate a new VPeerId
	PeerId vpeer = (++nextVirtualPeer) | VIRTUAL_PEER;
	virtualPeerNames.insert( vpeer, name );

	return vpeer;
}

void internal_alias_resolved_to( const std::string& alias, PeerId peer ) {
	Connection* connection = NULL;

	auto it = humbleNetState.pendingAliasConnectionsOut.find(alias);
	if (it == humbleNetState.pendingAliasConnectionsOut.end()) {
		LOG("Got resolve message for alias \"%s\" which we're not connecting to\n", alias.c_str());
		return;
	} else {
		connection = it->second;
		humbleNetState.pendingAliasConnectionsOut.erase(it);
	}

	assert(connection != NULL);

	if( peer == 0 ) {
		LOG("AliasError: unable to resolve \"%s\"\n", alias.c_str());

		humblenet_connection_set_closed( connection );
		return;
	}

	connection->otherPeer = peer;

	humbleNetState.pendingPeerConnectionsOut.emplace(peer, connection);

	if( is_peer_blacklisted(peer) ) {
		humblenet_set_error("peer blacklisted");
		LOG("humblenet_connect_peer: peer blacklisted %u\n", peer);

		humblenet_connection_set_closed(connection);
	} else if( !internal_create_offer(connection->socket ) ) {
		LOG("Unable to create offer, aborting connection to alias\n");
		humblenet_connection_set_closed( connection );
	}

}

ha_bool internal_alias_is_virtual_peer( PeerId peer ) {
	return (peer & VIRTUAL_PEER) == VIRTUAL_PEER;
}

PeerId internal_alias_get_virtual_peer( Connection* conn ) {
	auto it = virtualPeerConnections.find( conn );
	if( virtualPeerConnections.is_end(it) )
		return 0;
	else
		return it->second;
}

Connection* internal_alias_find_connection( PeerId peer ) {
	if( ! internal_alias_is_virtual_peer(peer) ) {
		return NULL;
	}

	// resolve the VPeer
	auto it = virtualPeerConnections.find( peer );
	if( virtualPeerConnections.is_end(it) ) {
		return NULL;
	} else if( humblenet_connection_status( it->second ) == HUMBLENET_CONNECTION_CLOSED ) {
		virtualPeerConnections.erase( it );
		return NULL;
	} else {
		return it->second;
	}
}

Connection* internal_alias_create_connection( PeerId peer ) {
	Connection* conn = internal_alias_find_connection( peer );
	if( conn == NULL ) {
		auto nit = virtualPeerNames.find( peer );
		if( virtualPeerNames.is_end( nit ) ) {
			// Invalid VPeerId !!!
			humblenet_set_error("Not a valid VPeerId");
			return NULL;
		}

		std::string name = nit->second;

		if (!sendAliasLookup(humbleNetState.p2pConn.get(), name)) {
			return NULL;
		}

		conn = new Connection(Outgoing);

		conn->socket = internal_create_webrtc(humbleNetState.context);
		internal_set_data( conn->socket, conn);

		humbleNetState.pendingAliasConnectionsOut.emplace(name, conn);

		LOG("Establishing a connection to \"%s\"...\n", nit->second.c_str() );

		virtualPeerConnections.insert( peer, conn );
	}

	return conn;
}

void internal_alias_remove_connection( Connection* conn ) {
	virtualPeerConnections.erase( conn );
}

/*** End of inlined file: humblenet_alias.cpp ***/


/*** Start of inlined file: humblepeer.cpp ***/
#include <cassert>
#include <cstdio>
#include <cstring>

#include <limits>


/*** Start of inlined file: crc.h ***/
#ifndef __CRC_H__
#define __CRC_H__

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The definition of the used algorithm.
 *
 * This is not used anywhere in the generated code, but it may be used by the
 * application code to call algoritm-specific code, is desired.
 *****************************************************************************/
#define CRC_ALGO_TABLE_DRIVEN 1

/**
 * The type of the CRC values.
 *
 * This type must be big enough to contain at least 32 bits.
 *****************************************************************************/
typedef uint_fast32_t crc_t;

/**
 * Calculate the initial crc value.
 *
 * \return     The initial crc value.
 *****************************************************************************/
static inline crc_t crc_init(void)
{
	return 0xffffffff;
}

/**
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const void *data, size_t data_len);

/**
 * Calculate the final crc value.
 *
 * \param crc  The current crc value.
 * \return     The final crc value.
 *****************************************************************************/
static inline crc_t crc_finalize(crc_t crc)
{
	return crc ^ 0xffffffff;
}

#ifdef __cplusplus
}           /* closing brace for extern "C" */
#endif

#endif      /* __CRC_H__ */

/*** End of inlined file: crc.h ***/


/*** Start of inlined file: hmac.h ***/
#ifndef HMAC_H
#define HMAC_H


/*** Start of inlined file: sha1.h ***/
#ifndef _SHA1_H_
#define _SHA1_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
 *  int_least16_t    integer of >= 16 bits
 *
 */

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
	shaSuccess = 0,
	shaNull,            /* Null pointer parameter */
	shaInputTooLong,    /* input data too long */
	shaStateError       /* called Input after Result */
};
#endif
#define SHA1HashSize 20

/*
 *  This structure will hold context information for the SHA-1
 *  hashing operation
 */
typedef struct SHA1Context
{
	uint32_t Intermediate_Hash[SHA1HashSize/4]; /* Message Digest  */

	uint32_t Length_Low;            /* Message length in bits      */
	uint32_t Length_High;           /* Message length in bits      */

							   /* Index into message block array   */
	int_least16_t Message_Block_Index;
	uint8_t Message_Block[64];      /* 512-bit message blocks      */

	int Computed;               /* Is the digest computed?         */
	int Corrupted;             /* Is the message digest corrupted? */
} SHA1Context;

/*
 *  Function Prototypes
 */

int SHA1Reset(  SHA1Context *);
int SHA1Input(  SHA1Context *,
				const uint8_t *,
				unsigned int);
int SHA1Result( SHA1Context *,
				uint8_t Message_Digest[SHA1HashSize]);

#ifdef __cplusplus
}
#endif
#endif

/*** End of inlined file: sha1.h ***/

#ifdef __cplusplus
extern "C" {
#endif

#define HMAC_BLOCKSIZE 64
#define HMAC_DIGEST_SIZE SHA1HashSize

typedef struct HMACContext {
	SHA1Context i_ctx;
	SHA1Context o_ctx;
} HMACContext;

void HMACInit(HMACContext *ctx, const uint8_t* key, unsigned key_len);
int HMACInput(HMACContext *ctx, const uint8_t* data, unsigned data_len);
int HMACResult(HMACContext *ctx, uint8_t Message_Digest[HMAC_DIGEST_SIZE]);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>
void HMACResultToHex(uint8_t digest[HMAC_DIGEST_SIZE], std::string& out_hex);
#endif

#endif /* HMAC_H */

/*** End of inlined file: hmac.h ***/

#include <ctime>

#define LOG printf

#define DEFAULT_FBB_SIZE 512

namespace humblenet {
	const size_t PEER_OFFSET_SIZE = 8;

	class peer_allocator : public flatbuffers::simple_allocator {
		const size_t _offset;
	public:
		peer_allocator(size_t offset) : _offset(offset) {}

		uint8_t *allocate(size_t size) const {

			uint8_t *p = new uint8_t[size + _offset];
			return p ? (p + _offset) : nullptr;
		}
		void deallocate(uint8_t *p) const {
			if (p) {
				delete[] (p - _offset);
			}
		}
	};

	static peer_allocator peer_fbb_allocator(PEER_OFFSET_SIZE);

	flatbuffers::Offset<flatbuffers::String> CreateFBBStringIfNotEmpty(flatbuffers::FlatBufferBuilder &fbb, const std::string &str)
	{
		if (str.empty()) {
			return 0;
		} else {
			return fbb.CreateString(str);
		}
	}

	template<typename T>
	flatbuffers::Offset<flatbuffers::Vector<T>> CreateFBBVectorIfNotEmpty(flatbuffers::FlatBufferBuilder &fbb, const std::vector<T> &v)
	{
		if (v.empty()) {
			return 0;
		} else {
			return fbb.CreateVector(v);
		}
	}

	// Sending and parsing

	inline ha_bool WARN_UNUSED_RESULT sendP2PMessage(P2PSignalConnection *conn, const flatbuffers::FlatBufferBuilder& fbb)
	{
		uint8_t *buff = fbb.GetBufferPointer();
		flatbuffers::uoffset_t size = fbb.GetSize();

		uint8_t *base = buff - PEER_OFFSET_SIZE;

		memset(base, 0, PEER_OFFSET_SIZE);
		flatbuffers::WriteScalar(base, size);

		auto crc = crc_init();
		crc = crc_update(crc, buff, size);
		crc = crc_finalize(crc);

		flatbuffers::WriteScalar(base + sizeof(flatbuffers::uoffset_t), flatbuffers::uoffset_t(crc));

		return sendP2PMessage(conn, base, size + PEER_OFFSET_SIZE);
	}

	ha_bool parseMessage(std::vector<uint8_t> &recvBuf, ProcessMsgFunc processFunc, void *user_data)
	{
		if (recvBuf.empty()) {
			// nothing to do
			return true;
		}

		// first PEER_OFFSET_SIZE bytes are our packet header
		flatbuffers::uoffset_t fbSize = flatbuffers::ReadScalar<flatbuffers::uoffset_t>(recvBuf.data());
		// make sure we have enough data!

		if (recvBuf.size() < (fbSize + PEER_OFFSET_SIZE)) {
			// partial payload, try again later
			return true;
		}

		const uint8_t* buff = recvBuf.data() + PEER_OFFSET_SIZE;

		auto crc = crc_init();
		crc = crc_update(crc, buff, fbSize);
		crc = crc_finalize(crc);

		flatbuffers::uoffset_t fbCrc = flatbuffers::ReadScalar<flatbuffers::uoffset_t>(recvBuf.data() + sizeof(flatbuffers::uoffset_t));

		if (fbCrc != crc) {
			// TODO should we disconnect in this case?
			return false;
		}

		// Now validate our buffer based on the expected size
		flatbuffers::Verifier v(buff, fbSize);
		if (!HumblePeer::VerifyMessageBuffer(v)) {
			// TODO should we disconnect in this case?
			return false;
		}

		auto message = HumblePeer::GetMessage(buff);

		// process it
		ha_bool messageOk = processFunc(message, user_data);
		if (!messageOk) {
			// processFunc didn't like this message for some reason
			return false;
		}

		recvBuf.erase(recvBuf.begin(), recvBuf.begin() + fbSize + PEER_OFFSET_SIZE);

		// no need to check if recvBuf is empty since parseMessage will do it
		return parseMessage(recvBuf, processFunc, user_data);
	}

	// ** Peer server connection

	ha_bool sendHelloServer(P2PSignalConnection *conn, uint8_t flags,
							const std::string& gametoken, const std::string& gamesecret,
							const std::string& authToken, const std::string& reconnectToken,
							const std::map<std::string, std::string>& attributes)
	{
		assert(!gametoken.empty());
		assert(!gamesecret.empty());

		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);

		std::vector<flatbuffers::Offset<HumblePeer::Attribute>> tempAttribs;

		// build up attributes
		tempAttribs.reserve(attributes.size() + 1);

		for (auto& it : attributes) {
			if (it.first == "timestamp") continue;
			tempAttribs.emplace_back( HumblePeer::CreateAttribute(fbb, fbb.CreateString(it.first), fbb.CreateString(it.second)) );
		}

		tempAttribs.emplace_back( HumblePeer::CreateAttribute(fbb, fbb.CreateString("timestamp"), fbb.CreateString(std::to_string(time(NULL)))) );

		uint32_t version = 0;

		HMACContext hmac;
		HMACInit(&hmac, (const uint8_t*)gamesecret.data(), gamesecret.size());

		HMACInput(&hmac, (const uint8_t*)authToken.data(), authToken.size());
		HMACInput(&hmac, (const uint8_t*)reconnectToken.data(), reconnectToken.size());

		flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<HumblePeer::Attribute>>> attribs;
		if (!tempAttribs.empty()) {
			attribs = fbb.CreateVectorOfSortedTables(&tempAttribs);
			// tempAttribs is sorted now
			for (const auto& it : tempAttribs) {
				auto attr = flatbuffers::EndianScalar(reinterpret_cast<const HumblePeer::Attribute *>(fbb.GetCurrentBufferPointer() + fbb.GetSize() - it.o));
				auto key = attr->key();
				auto value = attr->value();
				HMACInput(&hmac, key->Data(), key->size());
				HMACInput(&hmac, value->Data(), value->size());
			}
		}

		uint8_t hmacresult[HMAC_DIGEST_SIZE];

		HMACResult(&hmac, hmacresult);

		std::string signature;

		HMACResultToHex(hmacresult, signature);

		auto packet = HumblePeer::CreateHelloServer(fbb,
													version,
													flags,
													fbb.CreateString(gametoken),
													fbb.CreateString(signature),
													CreateFBBStringIfNotEmpty(fbb, authToken),
													CreateFBBStringIfNotEmpty(fbb, reconnectToken),
													attribs);

		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::HelloServer, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendHelloClient(P2PSignalConnection *conn, PeerId peerId, const std::string& reconnectToken, const std::vector<ICEServer>& iceServers)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);

		std::vector<flatbuffers::Offset<HumblePeer::ICEServer>> tempServers;
		tempServers.reserve(iceServers.size());

		for( auto& it : iceServers) {
			auto server = fbb.CreateString(it.server);
			flatbuffers::Offset<HumblePeer::ICEServer> s;

			if (it.type == HumblePeer::ICEServerType::STUNServer) {
				s = HumblePeer::CreateICEServer(fbb, HumblePeer::ICEServerType::STUNServer, server);
			} else { // turn server
				s = HumblePeer::CreateICEServer(fbb, HumblePeer::ICEServerType::TURNServer, server, fbb.CreateString(it.username), fbb.CreateString(it.password));
			}
			tempServers.emplace_back( s );
		}

		auto packet = HumblePeer::CreateHelloClient(fbb, peerId,
													CreateFBBStringIfNotEmpty(fbb, reconnectToken),
													CreateFBBVectorIfNotEmpty(fbb, tempServers));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::HelloClient, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	// ** P2P Negotiation messages

	ha_bool sendNoSuchPeer(P2PSignalConnection *conn, PeerId peerId)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2PReject(fbb, peerId, HumblePeer::P2PRejectReason::NotFound);
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2PReject, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendPeerRefused(P2PSignalConnection *conn, PeerId peerId)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2PReject(fbb, peerId, HumblePeer::P2PRejectReason::PeerRefused);
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2PReject, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendP2PConnect(P2PSignalConnection *conn, PeerId peerId, uint8_t flags, const char* offer)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2POffer(fbb, peerId, flags, fbb.CreateString(offer));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2POffer, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendP2PResponse(P2PSignalConnection *conn, PeerId peerId, const char* offer)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2PAnswer(fbb, peerId, fbb.CreateString(offer));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2PAnswer, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendICECandidate(P2PSignalConnection *conn, PeerId peerId, const char* offer)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateICECandidate(fbb, peerId, fbb.CreateString(offer));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::ICECandidate, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendP2PDisconnect(P2PSignalConnection *conn, PeerId peerId)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2PDisconnect(fbb, peerId);
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2PDisconnect, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);

	}

	ha_bool sendP2PRelayData(humblenet::P2PSignalConnection *conn, PeerId peerId, const void* data, uint16_t length) {
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateP2PRelayData(fbb, peerId, fbb.CreateVector((int8_t*)data, length));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::P2PRelayData, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	// ** Name Alias messages

	ha_bool sendAliasRegister(P2PSignalConnection *conn, const std::string& alias)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateAliasRegister(fbb, fbb.CreateString(alias));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::AliasRegister, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendAliasUnregister(P2PSignalConnection *conn, const std::string& alias)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateAliasUnregister(fbb, CreateFBBStringIfNotEmpty(fbb, alias));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::AliasUnregister, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendAliasLookup(P2PSignalConnection *conn, const std::string& alias)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateAliasLookup(fbb, fbb.CreateString(alias));
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::AliasLookup, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}

	ha_bool sendAliasResolved(P2PSignalConnection *conn, const std::string& alias, PeerId peer)
	{
		flatbuffers::FlatBufferBuilder fbb(DEFAULT_FBB_SIZE, &peer_fbb_allocator);
		auto packet = HumblePeer::CreateAliasResolved(fbb, fbb.CreateString(alias), peer);
		auto msg = HumblePeer::CreateMessage(fbb, HumblePeer::MessageType::AliasResolved, packet.Union());
		fbb.Finish(msg);

		return sendP2PMessage(conn, fbb);
	}
}  // namespace humblenet

/*** End of inlined file: humblepeer.cpp ***/

// socket layer

/*** Start of inlined file: libsocket.cpp ***/
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>

#ifdef EMSCRIPTEN

/*** Start of inlined file: libwebsockets_asmjs.h ***/
#ifndef EMSCRIPTEN
#error "This should only be used under emscripten"
#endif

#ifndef LIBWEBSOCKETS_ASMJS_H
#define LIBWEBSOCKETS_ASMJS_H

// ABI compatible subset of libwebsockets

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

enum libwebsocket_callback_reasons {
	LWS_CALLBACK_ESTABLISHED = 1,
	LWS_CALLBACK_CLIENT_CONNECTION_ERROR = 2,
//    LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH,
	LWS_CALLBACK_CLIENT_ESTABLISHED = 3,
	LWS_CALLBACK_CLOSED = 4,
 //   LWS_CALLBACK_CLOSED_HTTP,
	LWS_CALLBACK_RECEIVE = 5,
	LWS_CALLBACK_CLIENT_RECEIVE = 6,
 //   LWS_CALLBACK_CLIENT_RECEIVE_PONG,
	LWS_CALLBACK_CLIENT_WRITEABLE = 7,
	LWS_CALLBACK_SERVER_WRITEABLE = 8,
 //   LWS_CALLBACK_HTTP,
 //   LWS_CALLBACK_HTTP_BODY,
 //   LWS_CALLBACK_HTTP_BODY_COMPLETION,
 //   LWS_CALLBACK_HTTP_FILE_COMPLETION,
 //   LWS_CALLBACK_HTTP_WRITEABLE,
 //   LWS_CALLBACK_FILTER_NETWORK_CONNECTION,
 //   LWS_CALLBACK_FILTER_HTTP_CONNECTION,
 //   LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED,
	LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION = 9,
 //   LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS,
//    LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS,
//    LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION,
//    LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER,
//    LWS_CALLBACK_CONFIRM_EXTENSION_OKAY,
//    LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED,
//    LWS_CALLBACK_PROTOCOL_INIT,
//    LWS_CALLBACK_PROTOCOL_DESTROY,
	LWS_CALLBACK_WSI_CREATE = 10, /* always protocol[0] */
	LWS_CALLBACK_WSI_DESTROY = 11, /* always protocol[0] */
//    LWS_CALLBACK_GET_THREAD_ID,

	/* external poll() management support */
//    LWS_CALLBACK_ADD_POLL_FD,
//    LWS_CALLBACK_DEL_POLL_FD,
//    LWS_CALLBACK_CHANGE_MODE_POLL_FD,
//    LWS_CALLBACK_LOCK_POLL,
//    LWS_CALLBACK_UNLOCK_POLL,

};

#define CONTEXT_PORT_NO_LISTEN 0

#define LWS_SEND_BUFFER_PRE_PADDING 0
#define LWS_SEND_BUFFER_POST_PADDING 0

enum libwebsocket_write_protocol {
//        LWS_WRITE_TEXT,
		LWS_WRITE_BINARY,
};

typedef int (callback_function)(struct libwebsocket_context *context,
	struct libwebsocket *wsi,
			 enum libwebsocket_callback_reasons reason, void *user,
	void *in, size_t len);

struct libwebsocket_protocols {
	const char *name;
	callback_function *callback;
	size_t per_session_data_size;
	size_t rx_buffer_size;
	int no_buffer_all_partial_tx;

	/*
	 * below are filled in on server init and can be left uninitialized,
	 * no need for user to use them directly either
	 */

	struct libwebsocket_context *owning_server;
	int protocol_index;
};

struct lws_context_creation_info {
	int port;
	const char *iface;
	struct libwebsocket_protocols *protocols;
	struct libwebsocket_extension *extensions;
	struct lws_token_limits *token_limits;
	const char *ssl_cert_filepath;
	const char *ssl_private_key_filepath;
	const char *ssl_ca_filepath;
	const char *ssl_cipher_list;
	const char *http_proxy_address;
	unsigned int http_proxy_port;
	int gid;
	int uid;
	unsigned int options;
	void *user;
	int ka_time;
	int ka_probes;
	int ka_interval;
};

struct libwebsocket_context* libwebsocket_create_context( struct lws_context_creation_info* info );
struct libwebsocket_context* libwebsocket_create_context_extended( struct lws_context_creation_info* info );

void libwebsocket_context_destroy(struct libwebsocket_context* ctx );

struct libwebsocket* libwebsocket_client_connect_extended( struct libwebsocket_context*, const char* url, const char* protocol, void* user_data );
int libwebsocket_write( struct libwebsocket* socket, const void* data, int len, enum libwebsocket_write_protocol protocol );
void libwebsocket_callback_on_writable( struct libwebsocket_context* context, struct libwebsocket* socket );

#ifdef __cplusplus
}
#endif

#endif // LIBWEBSOCKETS_ASMJS_H

/*** End of inlined file: libwebsockets_asmjs.h ***/


#else
#include "libwebsockets_native.h"	// SKIP_AMALGAMATOR_INCLUDE
#include "cert_pem.h"				// SKIP_AMALGAMATOR_INCLUDE
#include <openssl/ssl.h>
#endif


/*** Start of inlined file: libwebrtc.h ***/
#ifndef LIBWEBRTC_H
#define LIBWEBRTC_H

// shared ABI to Microstack WebRTC and Browsers WebRTC.

#ifdef __cplusplus
extern "C" {
#endif

enum libwebrtc_callback_reasons {
	LWRTC_CALLBACK_LOCAL_DESCRIPTION = 1,
	LWRTC_CALLBACK_ICE_CANDIDATE = 2,
	LWRTC_CALLBACK_ESTABLISHED = 3,
	LWRTC_CALLBACK_DISCONNECTED = 4,

	LWRTC_CALLBACK_CHANNEL_ACCEPTED = 5,
	LWRTC_CALLBACK_CHANNEL_CONNECTED = 6,
	LWRTC_CALLBACK_CHANNEL_RECEIVE = 7,
	LWRTC_CALLBACK_CHANNEL_CLOSED = 8,

	LWRTC_CALLBACK_ERROR = 9,

	LWRTC_CALLBACK_DESTROY = 10
};

struct libwebrtc_context;

// this represents the connection to the peer.
struct libwebrtc_connection;

// this represents an active data stream to the peer.
struct libwebrtc_data_channel;

typedef int (*lwrtc_callback_function)(struct libwebrtc_context *context,
	struct libwebrtc_connection *connection, struct libwebrtc_data_channel* channel,
			 enum libwebrtc_callback_reasons reason, void *user,
	void *in, int len);

struct libwebrtc_context* libwebrtc_create_context( lwrtc_callback_function );
void libwebrtc_destroy_context( struct libwebrtc_context* );

void libwebrtc_set_stun_servers( struct libwebrtc_context* ctx, const char** servers, int count);

struct libwebrtc_connection* libwebrtc_create_connection_extended( struct libwebrtc_context*, void* user_data );
struct libwebrtc_data_channel* libwebrtc_create_channel( struct libwebrtc_connection* conn, const char* name );

int libwebrtc_create_offer( struct libwebrtc_connection* );
int libwebrtc_set_offer( struct libwebrtc_connection* , const char* sdp );
int libwebrtc_set_answer( struct libwebrtc_connection*, const char* sdp );
int libwebrtc_add_ice_candidate( struct libwebrtc_connection*, const char* candidate );

int libwebrtc_write( struct libwebrtc_data_channel*, const void*, int len );

void libwebrtc_close_channel( struct libwebrtc_data_channel* );
void libwebrtc_close_connection( struct libwebrtc_connection* );

#ifdef __cplusplus
}
#endif

#endif // LIBWEBRTC_H

/*** End of inlined file: libwebrtc.h ***/

// TODO: should have a way to disable this on release builds
#define LOG printf

struct internal_socket_t {
	bool owner;
	bool closing;           // if this is set, ignore close attempts as the close process has already been initiated.
	void* user_data;
	internal_callbacks_t callbacks;

	// web socket connection info
	struct libwebsocket *wsi;
	std::string url;

	// webrtc connection info
	struct libwebrtc_connection* webrtc;
	struct libwebrtc_data_channel* webrtc_channel;

	internal_socket_t(bool owner=true)
	:owner(owner)
	,closing(false)
	,user_data(NULL)
	,wsi(NULL)
	,webrtc(NULL)
	,webrtc_channel(NULL)
	{}

	~internal_socket_t(){
		assert( owner );
	}
};

struct internal_context_t {
	internal_callbacks_t callbacks;

	std::map<std::string,internal_callbacks_t> protocols;

	std::string turnServer;
	std::string turnUsername;
	std::string turnPassword;
	std::vector<std::string> stunServerList;

	// websocket
	struct libwebsocket_context *websocket;

	// webrtc
	struct libwebrtc_context* webrtc;
};

static internal_context_t* g_context;

int websocket_protocol(struct libwebsocket_context *context
					   , struct libwebsocket *wsi
					   , enum libwebsocket_callback_reasons reason
					   , void *user, void *in, size_t len) {

//    LOG("%p %p %d %p\n", context, wsi, reason, user );

	internal_socket_t* socket = reinterpret_cast<internal_socket_t*>( user );

	int ret = 0;

	switch (reason) {
		case LWS_CALLBACK_WSI_CREATE: {
			socket->wsi = wsi;
		}
		break;

		case LWS_CALLBACK_WSI_DESTROY: {
			ret = socket->callbacks.on_destroy( socket, socket->user_data );
			if( socket->owner )
				delete socket;
		}
		break;

		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
			if( socket ) {
				socket->closing = true;
				ret = socket->callbacks.on_disconnect( socket, socket->user_data );
			}
		} break;

		case LWS_CALLBACK_ESTABLISHED:
		{
			ret = socket->callbacks.on_accept( socket, socket->user_data );
		}
		break;

		case LWS_CALLBACK_CLIENT_ESTABLISHED:
		{
			 ret = socket->callbacks.on_connect( socket, socket->user_data );
		}
		break;

		case LWS_CALLBACK_CLOSED:
		{
			socket->closing = true;
			ret = socket->callbacks.on_disconnect( socket, socket->user_data );
		}
		break;

		case LWS_CALLBACK_RECEIVE:
		case LWS_CALLBACK_CLIENT_RECEIVE:
		{
			ret = socket->callbacks.on_data( socket, in, len, socket->user_data );
		}
		break;

		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: {
			std::map<std::string, internal_callbacks_t>::iterator it = g_context->protocols.find( std::string( (const char*)in, len ) );
			if( it == g_context->protocols.end() ) {
				LOG("Unknown protocol: %s\n", (const char*)in);
				return -1;
			}

			socket->callbacks = it->second;
			return 0;
		} break;

		case LWS_CALLBACK_CLIENT_WRITEABLE:
		case LWS_CALLBACK_SERVER_WRITEABLE:
		{
			ret = socket->callbacks.on_writable( socket, socket->user_data );
		}
		break;

#if !defined(EMSCRIPTEN)
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
		{
			int i, count = 0;
			SSL_CTX *ctx = (SSL_CTX*)user;
			BIO *in = NULL;
			X509 *x = NULL;
			in = BIO_new_mem_buf((void*)cert_pem, strlen(cert_pem));
			if (in == NULL) {
				break;
			}

			X509_STORE *store = SSL_CTX_get_cert_store( ctx );

			for (;;) {
				x = PEM_read_bio_X509_AUX(in, NULL, NULL, NULL);
				if (x == NULL) {
					if ((ERR_GET_REASON(ERR_peek_last_error()) == PEM_R_NO_START_LINE) && (count > 0)) {
						ERR_clear_error();
						break;
					} else {
						OPENSSL_PUT_ERROR(X509, ERR_R_PEM_LIB);
						break;
					}
				}
				i = X509_STORE_add_cert(store, x);
				if (!i) break;
				count++;
				X509_free(x);
				x = NULL;
			}
		}
			break;
#endif

		default:
			//LOG("callback_humblenet %p %p %u %p %p %u\n", context, wsi, reason, user, in, static_cast<unsigned int>(len));
			break;
	}

	return ret;
}

int webrtc_protocol(struct libwebrtc_context *context,
							  struct libwebrtc_connection *connection, struct libwebrtc_data_channel* channel,
							  enum libwebrtc_callback_reasons reason, void *user,
							  void *in, int len)
{
	internal_socket_t* socket = reinterpret_cast<internal_socket_t*>( user );

//    LOG("%p %p %p %d %p\n", context, connection, channel, reason, user );

	int ret = 0;

	switch( reason ) {
		case LWRTC_CALLBACK_LOCAL_DESCRIPTION:
			ret = socket->callbacks.on_sdp( socket, (const char*)in, socket->user_data );
			break;

		case LWRTC_CALLBACK_ICE_CANDIDATE:
			ret = socket->callbacks.on_ice_candidate( socket, (const char*)in, socket->user_data );
			break;

		case LWRTC_CALLBACK_ESTABLISHED:
			ret = socket->callbacks.on_connect( socket, socket->user_data );
			break;

		case LWRTC_CALLBACK_DISCONNECTED:
			socket->closing = true;
			ret = socket->callbacks.on_disconnect( socket, socket->user_data );
			break;

		case LWRTC_CALLBACK_CHANNEL_ACCEPTED:
			socket->webrtc_channel = channel;
			ret = socket->callbacks.on_accept_channel( socket, (const char*)in, socket->user_data );
			break;

		case LWRTC_CALLBACK_CHANNEL_CONNECTED:
			ret = socket->callbacks.on_connect_channel( socket, (const char*)in, socket->user_data );
			break;

		case LWRTC_CALLBACK_CHANNEL_RECEIVE:
			ret = socket->callbacks.on_data( socket, in, len, socket->user_data );
			break;

		case LWRTC_CALLBACK_CHANNEL_CLOSED:
		   // Currently this isn't safe, as the connectio ncan be closed first, thus causing the destruction of the state.
		   //
		   //socket->webrtc_channel = NULL;
		   // socket->callbacks.on_disconnect_channel( socket, socket->user_data );
			break;

		case LWRTC_CALLBACK_DESTROY:
			socket->callbacks.on_destroy( socket, socket->user_data );
			if( socket->owner )
				delete socket;
			break;
		case LWRTC_CALLBACK_ERROR:
			break;
	}

	return ret;
}

#define MAX_PROTOCOLS 16

struct libwebsocket_protocols protocols[MAX_PROTOCOLS] = {
	{ "default", websocket_protocol, sizeof(internal_socket_t) }
	,{ NULL, NULL, 0 }
};

int ok_callback() {
	LOG("Ok_CB\n");
	return 0;
}

int err_callback() {
	return -1;
}

void sanitize_callbacks( internal_callbacks_t& callbacks ) {
	intptr_t* ptr = (intptr_t*)&callbacks;

	for( int i = 0; i < sizeof(internal_callbacks_t)/sizeof(void*); ++i, ++ptr ) {
		if( !*ptr ) {
			LOG("Sanitize callback #%d\n", i+1 );
			*ptr = (intptr_t)&ok_callback;
		}
	}
}

internal_context_t* internal_init(internal_callbacks_t* callbacks) {
	internal_context_t* ctx = new internal_context_t();

	if( callbacks )
		ctx->callbacks= *callbacks;

	sanitize_callbacks( ctx->callbacks );

	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));
	info.protocols = protocols;
	info.port = CONTEXT_PORT_NO_LISTEN;
	info.gid = -1;
	info.uid = -1;
#if 0
#if defined __APPLE__ || defined(__linux__)
	// test a few wll known locations
	const char* certs[] = { "./cert.pem", "/etc/openssl/cert.pem", "/opt/local/etc/openssl/cert.pem", "/etc/pki/tls/cert.pem" , NULL };
	for( const char** test = certs; *test; test++ ) {
		if( access( *test, F_OK ) != -1 ) {
			info.ssl_ca_filepath = *test;
			break;
		}
	}
#elif defined(WIN32)
	info.ssl_ca_filepath = "cert.pem";
#endif
#endif

	ctx->websocket = libwebsocket_create_context_extended(&info);
	ctx->webrtc = libwebrtc_create_context(&webrtc_protocol);

	g_context = ctx;

	return ctx;
}

bool internal_supports_webRTC(internal_context_t* ctx) {
	return ctx->webrtc != NULL;
}

void internal_set_stun_servers( internal_context_t* ctx, const char** servers, int count){
	if( ctx->webrtc )
		libwebrtc_set_stun_servers( ctx->webrtc, servers, count );

	ctx->stunServerList.clear();
	for( int i = 0; i < count; ++i ) {
		ctx->stunServerList.push_back( *servers );
		servers++;
	}
}

void internal_set_callbacks(internal_socket_t* socket, internal_callbacks_t* callbacks ) {
	if( ! callbacks ) {
		socket->callbacks = g_context->callbacks;
	} else {
		socket->callbacks = *callbacks;
		sanitize_callbacks( socket->callbacks );
	}
}

void internal_register_protocol( internal_context_t* ctx, const char* name, internal_callbacks_t* callbacks ) {
	internal_callbacks_t cb = *callbacks;
	sanitize_callbacks( cb );

	ctx->protocols.insert( std::make_pair( std::string(name), cb ) );
	// TODO: Sanatize callbacks

	libwebsocket_protocols* protocol = protocols + ctx->protocols.size();
	// make sure the next protocols is "empty"
	*(protocol + 1) = *protocol;
	// now copy the prior record
	*protocol = *(protocol-1);
	// and update the name
	protocol->name = name;
	protocol->protocol_index++;
}

void internal_deinit(internal_context_t* ctx) {
	// how to destroy connection factory
	if (!ctx) return;

	libwebsocket_context_destroy( ctx->websocket );
	if( ctx->webrtc )
		libwebrtc_destroy_context( ctx->webrtc );

	delete ctx;
}

void internal_set_data(internal_socket_t* socket, void* user_data) {
	socket->user_data = user_data;
}

void * internal_get_data(internal_socket_t* socket ) {
	return socket->user_data;
}

internal_socket_t* internal_connect_websocket( const char *server_addr, const char* protocol ) {
	internal_socket_t* socket = new internal_socket_t(true);

	socket->wsi = libwebsocket_client_connect_extended(g_context->websocket, server_addr, protocol, socket );
	if (socket->wsi == NULL) {
		delete socket;
		return NULL;
	}

	socket->callbacks = g_context->protocols.find( protocol )->second;

	socket->url = server_addr;

	return socket;
}

internal_socket_t* internal_create_webrtc(internal_context_t* ctx) {
	if( ! ctx->webrtc )
		return NULL;

	internal_socket_t* socket = new internal_socket_t(true);

	socket->webrtc = libwebrtc_create_connection_extended( ctx->webrtc, socket );
	socket->callbacks = ctx->callbacks;

	return socket;
}

int internal_create_offer(internal_socket_t* socket ) {
	assert( socket->webrtc != NULL );
	assert( socket->webrtc_channel == NULL );

	if( ! libwebrtc_create_offer( socket->webrtc ) )
		return 0;

	return 1;
}

int internal_set_offer( internal_socket_t* socket, const char* inOffer ){
	assert( socket->webrtc != NULL );
	assert( socket->webrtc_channel == NULL );

	if( ! libwebrtc_set_offer( socket->webrtc, inOffer ) )
		return 0;
	else
		return 1;
}

int internal_set_answer( internal_socket_t* socket, const char* inOffer ){
	assert( socket->webrtc != NULL );
	assert( socket->webrtc_channel == NULL );

	if( ! libwebrtc_set_answer( socket->webrtc, inOffer ) )
		return 0;
	else
		return 1;
}

int internal_add_ice_candidate( internal_socket_t* socket, const char* candidate ) {
	assert( socket->webrtc != NULL );
	return libwebrtc_add_ice_candidate( socket->webrtc, candidate );
}

int internal_create_channel( internal_socket_t* socket, const char* name ){
	assert( socket->webrtc != NULL );
	assert( socket->webrtc_channel == NULL );

	socket->webrtc_channel = libwebrtc_create_channel(socket->webrtc, name );

	if( !socket->webrtc_channel )
	   return 0;

	return 1;
}

void internal_close_socket( internal_socket_t* socket ) {
	if( socket->closing )
		// socket clos process has already started, ignore the request.
		return;
	else if( socket->wsi ) {
		libwebsocket_callback_on_writable(g_context->websocket, socket->wsi);
		// TODO: How do we clean up ?
	} else if( socket->webrtc ) {
		if( socket->webrtc_channel )
			libwebrtc_close_channel( socket->webrtc_channel );
		// this will trigger the destruction of the channel and thus the destruction of our socket object.
		libwebrtc_close_connection( socket->webrtc );
	} else {
		assert( "Destroyed socket passed to close" == NULL );
	}
}

int internal_write_socket(internal_socket_t* socket, const void *buf, int bufsize) {
	if( socket->wsi ) {
		// TODO: Should this buffer the data like the docuemntation states and only write on the writable callback ?

#if LWS_SEND_BUFFER_PRE_PADDING == 0 && LWS_SEND_BUFFER_POST_PADDING == 0
		int retval = libwebsocket_write(socket->wsi, buf, bufsize, LWS_WRITE_BINARY);
#else
		// libwebsocket requires the caller to allocate the frame prefix/suffix storage.
		std::vector<unsigned char> sendbuf(LWS_SEND_BUFFER_PRE_PADDING + bufsize + LWS_SEND_BUFFER_POST_PADDING, 0);
		memcpy(&sendbuf[LWS_SEND_BUFFER_PRE_PADDING], buf, bufsize);

		int retval = libwebsocket_write(socket->wsi, &sendbuf[LWS_SEND_BUFFER_PRE_PADDING], bufsize, LWS_WRITE_BINARY);
#endif
		assert( retval == bufsize );

		// mark it non-writable and tell websocket to inform us when it's writable again
		//connection->writable = false;
		libwebsocket_callback_on_writable(g_context->websocket, socket->wsi);

		return retval;

	} else if( socket->webrtc ) {
		return libwebrtc_write( socket->webrtc_channel, buf, bufsize );
	}

	// bad/disconnected socket

	assert(false);
	return -1;
}

/*** End of inlined file: libsocket.cpp ***/


// WEBRTC wrapper

/*** Start of inlined file: libwebrtc_asmjs.cpp ***/
#ifdef EMSCRIPTEN

#include <emscripten.h>

#define USE_STUN

struct libwebrtc_context {
	lwrtc_callback_function callback;
};

extern "C"
int EMSCRIPTEN_KEEPALIVE libwebrtc_helper(struct libwebrtc_context *context, struct libwebrtc_connection *connection, struct libwebrtc_data_channel* channel,
								  enum libwebrtc_callback_reasons reason, void *user, void *in, int len) {
	return context->callback( context, connection, channel, reason, user, in, len );
}

struct libwebrtc_context* libwebrtc_create_context( lwrtc_callback_function callback ) {
	libwebrtc_context* ctx = new libwebrtc_context();
	ctx->callback = callback;

	bool supported = EM_ASM_INT({
		var libwebrtc = {};

		libwebrtc.RTCPeerConnection = window.RTCPeerConnection || window.mozRTCPeerConnection || window.msRTCConnection || window.webkitRTCPeerConnection;
		libwebrtc.RTCIceCandidate = window.RTCIceCandidate || window.mozRTCIceCandidate || window.msRTCIceCandidate || window.webkitRTCIceCandidate;
		libwebrtc.RTCSessionDescription = window.RTCSessionDescription || window.mozRTCSessionDescription || window.msRTCSessionDescription || window.webkitRTCSessionDescription;

		if( ! libwebrtc.RTCPeerConnection || ! libwebrtc.RTCIceCandidate || ! libwebrtc.RTCSessionDescription )
			return 0;

		'createOffer createAnswer'.split(' ').forEach(function(method){
			var native = libwebrtc.RTCPeerConnection.prototype[method];
			if( native.length == 0 )
			   return;

			Module.print("Adding promise support to: " + method );

			libwebrtc.RTCPeerConnection.prototype[method] = function() {
				var self = this;

				if( arguments.length == 0 || ( arguments.length == 1 && typeof(arguments[0]) === 'object' ) ) {
					 var opts = arguments.length === 1 ? arguments[0] : undefined;
					 return new Promise(function(resolve,reject){
						  native.apply(self, [resolve,reject,opts]);
					 });
				} else {
					return native.apply(this,arguments);
				}
			};
		});

		var is_firefox = navigator.userAgent.toLowerCase().indexOf('firefox') > -1;

		'setLocalDescription setRemoteDescription addIceCandidate'.split(' ').forEach(function(method) {
			var native = libwebrtc.RTCPeerConnection.prototype[method];
			if( is_firefox )
				return;

			Module.print("Adding promise support to: " + method );

			libwebrtc.RTCPeerConnection.prototype[method] = function() {
				var self = this;
				var opts = arguments.length === 1 ? arguments[0] : undefined;
				if( arguments.length > 1 )
					return native.apply( this, arguments );
				else {
					return new Promise( function(resolve,reject) {
						native.apply(self, [opts, resolve, reject]);
					});
				}
			};
		});

		var ctx = $0;
		libwebrtc.connections = new Map();
		libwebrtc.channels = new Map();
		libwebrtc.on_event = Module.cwrap('libwebrtc_helper', 'iiiiiiii');
		libwebrtc.options = {};

		libwebrtc.create = function() {
			var connection = new this.RTCPeerConnection(this.options,null);

			connection.trickle = false; // must not use trickle till native side can handle accepting a candidate.

			connection.destroy = this.destroy;

			connection.ondatachannel = this.on_datachannel;
			connection.onicecandidate = this.on_candidate;
			connection.onsignalingstatechange = this.on_signalstatechange;
			connection.oniceconnectionstatechange = this.on_icestatechange;

			connection.id = this.connections.size + 1;

			this.connections.set( connection.id, connection );

			return connection;
		};
		libwebrtc.create_channel = function(connection, name) {
			var channel = connection.createDataChannel( name );
			channel.parent = connection;
			// use the parents data initially
			channel.user_data = connection.user_data;
			channel.binaryType = 'arraybuffer';

			channel.onopen = libwebrtc.on_channel_connected;
			channel.onclose = libwebrtc.on_channel_close;
			channel.onmessage = libwebrtc.on_channel_message;
			channel.onerror = libwebrtc.on_channel_error;

			channel._id = libwebrtc.channels.size+1;

			libwebrtc.channels.set( channel._id, channel);

			return channel;
		};

		libwebrtc.on_sdp = function(){
			if( ! this.trickle && this.iceGatheringState != "complete" ) {
				return;
			}

			var sdp = this.localDescription.sdp;
			if( sdp.indexOf('a=candidate') <= 0 ) {
				sdp += 'a=candidate:0 1 UDP 2128609534 0.0.0.0 0 typ host\n';
				//sdp += 'a=candidate:0 2 UDP 2128609534 135.27.116.245 62789 typ host\n';
			}
			var stack = Runtime.stackSave();
			// local description //
			libwebrtc.on_event( ctx, this.id, 0, 1, this.user_data, allocate(intArrayFromString(sdp), 'i8', ALLOC_STACK), sdp.length);
			Runtime.stackRestore(stack);
		};
		libwebrtc.on_candidate = function(event){
			if( !event )
				return;

			if( this.iceConnectionState != 'new' && this.iceConnectionState != 'checking' && this.iceConnectionState == 'connected'  ) {
				Module.print("ignoring ice, were not trying to connect: " + this.iceConnectionState);
				return;
			}

			if( !event.candidate ) {
				Module.print("no more candidates: " + this.iceGatheringState );
				if( ! this.trickle )
					libwebrtc.on_sdp.call(this);
				return;
			}

			Module.print("ice candidate " + event.candidate.candidate + " -- " + this.iceGatheringState);

			if( this.trickle ) {
				var stack = Runtime.stackSave();
				// ice_candidate //
				libwebrtc.on_event( ctx, this.id, 0, 2, this.user_data, allocate(intArrayFromString(event.candidate.candidate), 'i8', ALLOC_STACK), event.candidate.candidate.length);
				Runtime.stackRestore(stack);
			}
		};
		libwebrtc.on_signalstatechange = function(event){
			Module.print("signalingState: "+ this.signalingState);
		};
		libwebrtc.on_icestatechange = function(event){
			Module.print( "icestate: " + this.iceConnectionState + " / iceGatheringState: " + this.iceGatheringState);
			if( this.iceConnectionState == 'failed' || this.iceConnectionState == 'disconnected'  )
				libwebrtc.on_disconnected.call(this,event);
			else if( this.iceConnectionState == 'connected' ) // use connected instead as FF never moves outbound to completed 'completed' )
				// connected //
				libwebrtc.on_event( ctx, this.id, 0, 3, this.user_data, 0, 0);
		};
		libwebrtc.on_disconnected = function(event){
			var stack = Runtime.stackSave();
			// disconnected //
			libwebrtc.on_event( ctx, this.id, 0, 4, this.user_data, 0, 0);
			Runtime.stackRestore(stack);
			this.destroy();
		};
		libwebrtc.on_datachannel = function(event){
			Module.print("datachannel");
			var channel = event.channel;

			channel.parent = this;
			// use the parents data initially
			channel.user_data = this.user_data;
			channel.binaryType = 'arraybuffer';

			channel.onopen = libwebrtc.on_channel_accept;
			channel.onclose = libwebrtc.on_channel_close;
			channel.onmessage = libwebrtc.on_channel_message;
			channel.onerror = libwebrtc.on_channel_error;

			channel._id = libwebrtc.channels.size+1;

			libwebrtc.channels.set( channel._id, channel);
		};
		libwebrtc.on_channel_accept = function(event){
			Module.print("accept");
			var stack = Runtime.stackSave();
			// channel accepted //
			libwebrtc.on_event(ctx, this.parent.id, this._id, 5, this.user_data, allocate(intArrayFromString(this.label), 'i8', ALLOC_STACK), this.label.length);
			Runtime.stackRestore(stack);
		};
		libwebrtc.on_channel_connected = function(event){
			Module.print("connect");
			var stack = Runtime.stackSave();
			// channel connected //
			libwebrtc.on_event(ctx, this.parent.id, this._id, 6, this.user_data, allocate(intArrayFromString(this.label), 'i8', ALLOC_STACK), this.label.length);
			Runtime.stackRestore(stack);
		};
		libwebrtc.on_channel_message = function(event){
			var stack = Runtime.stackSave();
			var len = event.data.byteLength;
			var ptr = allocate( len, 'i8', ALLOC_STACK);

//            Module.print("Data: " + len );
			var data = new Uint8Array( event.data );

			for(var i =0, buf = ptr; i < len; ++i ) {
				setValue(buf, data[i], 'i8');
				buf++;
			}

			// channel data //
			libwebrtc.on_event( ctx, this.parent.id, this._id, 7, this.user_data, ptr, len);
			Runtime.stackRestore(stack);
		};
		libwebrtc.on_channel_closed = function(event){
			var stack = Runtime.stackSave();
			// close channel //
			libwebrtc.on_event(ctx, this.parent.id, this._id, 7, this.user_data, 0, 0);
			Runtime.stackRestore(stack);
		};
		libwebrtc.destroy = function() {
			libwebrtc.connections.set( this.id, undefined );

			this.ondatachannel = undefined;
			this.onicecandidate = undefined;
			this.onsignalingstatechange = undefined;
			this.oniceconnectionstatechange = undefined;

			// destroy (connection) //
			libwebrtc.on_event(ctx, this.id, 0, 10, this.user_data, 0, 0);
			this.close();
			Module.print("Destroy webrtc: " + this.id );
		};

		Module.__libwebrtc = libwebrtc;

		return 1;
	}, ctx);

	if( !supported ) {
		delete ctx;
		return NULL;
	}

	return ctx;
}

void libwebrtc_destroy_context(struct libwebrtc_context* ctx)
{
	delete ctx;
}

void libwebrtc_set_stun_servers( struct libwebrtc_context* ctx, const char** servers, int count)
{
	EM_ASM({
		Module.__libwebrtc.options.iceServers = [];
	});

	for( int i = 0; i < count; ++i ) {
		EM_ASM_INT({
			var server = {};
			server.urls = "stun:" + Pointer_stringify($0);
			Module.__libwebrtc.options.iceServers.push( server );
		}, *servers);
		servers++;
	}
}

struct libwebrtc_connection* libwebrtc_create_connection_extended(struct libwebrtc_context* ctx, void* user_data) {
	return (struct libwebrtc_connection*)EM_ASM_INT({
		var connection = Module.__libwebrtc.create();
		connection.user_data = $0;
		return connection.id;
	}, user_data);
}

void libwebrtc_set_user_data(struct libwebrtc_connection* connection, void* user_data ) {
	EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return;
		connection.user_data = $1;
	}, connection, user_data);
}

int libwebrtc_create_offer( struct libwebrtc_connection* connection ) {
	return EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return 0;

		// in order to create and offer at least one stream must have been added.
		// simply create one, then drop it.
		connection.default_channel = Module.__libwebrtc.create_channel( connection,"default");

		connection.createOffer({})
			.then(function(offer){
				connection.setLocalDescription( new Module.__libwebrtc.RTCSessionDescription( offer ) )
					.then( function() {
						Module.__libwebrtc.on_sdp.call( connection );
					}).catch(function(error){
						alert( "setLocalDescription(create): " + error );
					});
			}).catch(function(error){
				alert("createOffer: " + error);
			});

		return 1;
	}, connection, 0);
}

int libwebrtc_set_offer( struct libwebrtc_connection* connection, const char* sdp ) {
	return EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return 0;

		var offer = {};
		offer.type = 'offer';
		offer.sdp = Pointer_stringify( $1 );

		connection.setRemoteDescription( new Module.__libwebrtc.RTCSessionDescription( offer ) )
			.then(function() {
				connection.createAnswer()
					.then(function(offer){
						connection.setLocalDescription( new Module.__libwebrtc.RTCSessionDescription( offer ) )
							.then( function() {
								Module.__libwebrtc.on_sdp.call( connection );
							}).catch(function(error){
								alert( "setLocalDescription(answer): " + error );
							});
					}).catch(function(error){
						alert("createAnswer: " + error);
				});
			}).catch(function(error){
				alert("setRemoteDescriptor(answer): " + error );
			});
		return 1;
	}, connection, sdp );
}

int libwebrtc_set_answer( struct libwebrtc_connection* connection, const char* sdp ) {
	return EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return 0;

		var offer = {};
		offer.type = 'answer';
		offer.sdp = Pointer_stringify( $1 );

		connection.setRemoteDescription( new Module.__libwebrtc.RTCSessionDescription( offer ) )
			.then( function() {
				// nothing, as this is the answer to our offer
			}).catch(function(error){
				alert("setRemoteDescriptor(answer): " + error );
			});
		return 1;
	}, connection, sdp );
}

int libwebrtc_add_ice_candidate( struct libwebrtc_connection* connection, const char* candidate ) {
	return EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return 0;

		var options = {};
		options.candidate = Pointer_stringify($1);

		if( connection.iceConnectionState == 'checking' || connection.iceConnectionState == 'connected'
		   // FF workaround
		   || connection.iceConnectionState == 'new') {
			Module.print( "AddIce: " + options.candidate );
			connection.addIceCandidate( new Module.__libwebrtc.RTCIceCandidate( options ) );
		} else
			Module.print( "Not negotiating (" + connection.iceConnectionState + "), ignored candidate: " + options.candidate );

	}, connection, candidate );
}

struct libwebrtc_data_channel* libwebrtc_create_channel( struct libwebrtc_connection* connection, const char* name ) {
	return (struct libwebrtc_data_channel*)EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return 0;

		var channel;

		if( connection.default_channel ){
			channel = connection.default_channel;
			connection.default_channel = 0;
		}else
			channel = Module.__libwebrtc.create_channel( connection, Pointer_stringify($1) );

		return channel._id;

	}, connection, name );
}

int libwebrtc_write( struct libwebrtc_data_channel* channel, const void* data, int len ) {
	return EM_ASM_INT({
		var channel = Module.__libwebrtc.channels.get($0);
		if( ! channel )
			return -1;

		// alloc a Uint8Array backed by the incomming data.
		var data_in = new Uint8Array(Module.HEAPU8.buffer, $1, $2 );
		// allow the dest array
		var data = new Uint8Array($2);
		// set the dest from the src
		data.set(data_in);

		channel.send( data );
		return $2;

	}, channel, data, len );
}

void libwebrtc_close_connection( struct libwebrtc_connection* channel ) {
	EM_ASM_INT({
		var connection = Module.__libwebrtc.connections.get($0);
		if( ! connection )
			return -1;

		Module.__libwebrtc.connections.set( connection.id, undefined );

		connection.close();

	}, channel );
}

void libwebrtc_close_channel( struct libwebrtc_data_channel* channel ) {
	EM_ASM_INT({
		var channel = Module.__libwebrtc.channels.get($0);
		if( ! channel )
			return -1;

		Module.__libwebrtc.connections.set( channel.id, undefined );

		channel.close();
	}, channel );
}

#endif

/*** End of inlined file: libwebrtc_asmjs.cpp ***/


// Websockets Wrapper

/*** Start of inlined file: libwebsockets_asmjs.cpp ***/
#ifdef EMSCRIPTEN


/*** Start of inlined file: libwebsockets_asmjs.h ***/
#ifndef EMSCRIPTEN
#error "This should only be used under emscripten"
#endif

#ifndef LIBWEBSOCKETS_ASMJS_H
#define LIBWEBSOCKETS_ASMJS_H

// ABI compatible subset of libwebsockets

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

enum libwebsocket_callback_reasons {
	LWS_CALLBACK_ESTABLISHED = 1,
	LWS_CALLBACK_CLIENT_CONNECTION_ERROR = 2,
//    LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH,
	LWS_CALLBACK_CLIENT_ESTABLISHED = 3,
	LWS_CALLBACK_CLOSED = 4,
 //   LWS_CALLBACK_CLOSED_HTTP,
	LWS_CALLBACK_RECEIVE = 5,
	LWS_CALLBACK_CLIENT_RECEIVE = 6,
 //   LWS_CALLBACK_CLIENT_RECEIVE_PONG,
	LWS_CALLBACK_CLIENT_WRITEABLE = 7,
	LWS_CALLBACK_SERVER_WRITEABLE = 8,
 //   LWS_CALLBACK_HTTP,
 //   LWS_CALLBACK_HTTP_BODY,
 //   LWS_CALLBACK_HTTP_BODY_COMPLETION,
 //   LWS_CALLBACK_HTTP_FILE_COMPLETION,
 //   LWS_CALLBACK_HTTP_WRITEABLE,
 //   LWS_CALLBACK_FILTER_NETWORK_CONNECTION,
 //   LWS_CALLBACK_FILTER_HTTP_CONNECTION,
 //   LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED,
	LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION = 9,
 //   LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS,
//    LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS,
//    LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION,
//    LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER,
//    LWS_CALLBACK_CONFIRM_EXTENSION_OKAY,
//    LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED,
//    LWS_CALLBACK_PROTOCOL_INIT,
//    LWS_CALLBACK_PROTOCOL_DESTROY,
	LWS_CALLBACK_WSI_CREATE = 10, /* always protocol[0] */
	LWS_CALLBACK_WSI_DESTROY = 11, /* always protocol[0] */
//    LWS_CALLBACK_GET_THREAD_ID,

	/* external poll() management support */
//    LWS_CALLBACK_ADD_POLL_FD,
//    LWS_CALLBACK_DEL_POLL_FD,
//    LWS_CALLBACK_CHANGE_MODE_POLL_FD,
//    LWS_CALLBACK_LOCK_POLL,
//    LWS_CALLBACK_UNLOCK_POLL,

};

#define CONTEXT_PORT_NO_LISTEN 0

#define LWS_SEND_BUFFER_PRE_PADDING 0
#define LWS_SEND_BUFFER_POST_PADDING 0

enum libwebsocket_write_protocol {
//        LWS_WRITE_TEXT,
		LWS_WRITE_BINARY,
};

typedef int (callback_function)(struct libwebsocket_context *context,
	struct libwebsocket *wsi,
			 enum libwebsocket_callback_reasons reason, void *user,
	void *in, size_t len);

struct libwebsocket_protocols {
	const char *name;
	callback_function *callback;
	size_t per_session_data_size;
	size_t rx_buffer_size;
	int no_buffer_all_partial_tx;

	/*
	 * below are filled in on server init and can be left uninitialized,
	 * no need for user to use them directly either
	 */

	struct libwebsocket_context *owning_server;
	int protocol_index;
};

struct lws_context_creation_info {
	int port;
	const char *iface;
	struct libwebsocket_protocols *protocols;
	struct libwebsocket_extension *extensions;
	struct lws_token_limits *token_limits;
	const char *ssl_cert_filepath;
	const char *ssl_private_key_filepath;
	const char *ssl_ca_filepath;
	const char *ssl_cipher_list;
	const char *http_proxy_address;
	unsigned int http_proxy_port;
	int gid;
	int uid;
	unsigned int options;
	void *user;
	int ka_time;
	int ka_probes;
	int ka_interval;
};

struct libwebsocket_context* libwebsocket_create_context( struct lws_context_creation_info* info );
struct libwebsocket_context* libwebsocket_create_context_extended( struct lws_context_creation_info* info );

void libwebsocket_context_destroy(struct libwebsocket_context* ctx );

struct libwebsocket* libwebsocket_client_connect_extended( struct libwebsocket_context*, const char* url, const char* protocol, void* user_data );
int libwebsocket_write( struct libwebsocket* socket, const void* data, int len, enum libwebsocket_write_protocol protocol );
void libwebsocket_callback_on_writable( struct libwebsocket_context* context, struct libwebsocket* socket );

#ifdef __cplusplus
}
#endif

#endif // LIBWEBSOCKETS_ASMJS_H

/*** End of inlined file: libwebsockets_asmjs.h ***/

#include <emscripten.h>

// TODO: should have a way to disable this on release builds
#define LOG printf

struct libwebsocket_context {
	libwebsocket_protocols* protocols; // we dont have any state to manage.
};

extern "C" int EMSCRIPTEN_KEEPALIVE libwebsocket_helper( int protocol, struct libwebsocket_context *context,
														struct libwebsocket *wsi,
														enum libwebsocket_callback_reasons reason, void *user,
														void *in, size_t len ) {
	LOG("%d -> %d -> %p -> %d\n", protocol, reason, in, len );

	if( reason == LWS_CALLBACK_WSI_DESTROY ) {
		context->protocols[protocol].callback( context, wsi, reason, user, in, len );
		// TODO See if we need to destroy the user_data..currently we dont allocate it, so we never would need to free it.
		return 0;
	}
	else
		return context->protocols[protocol].callback( context, wsi, reason, user, in, len );
}

struct libwebsocket_context* libwebsocket_create_context( struct lws_context_creation_info* info ){
	return libwebsocket_create_context_extended( info );
}

struct libwebsocket_context* libwebsocket_create_context_extended( struct lws_context_creation_info* info ) {
	struct libwebsocket_context* ctx = new libwebsocket_context();
	ctx->protocols = info->protocols;

	EM_ASM_({
		var libwebsocket = {};
		var ctx = $0;

		libwebsocket.sockets = new Map();
		libwebsocket.on_event = Module.cwrap('libwebsocket_helper', 'iiiiiiii');
		libwebsocket.connect = function( url, protocol, user_data ) {
			try {
				var socket = new WebSocket(url,protocol);
				socket.binaryType = "arraybuffer";
				socket.user_data = user_data;
				socket.protocol_id = 0;

				socket.onopen = this.on_connect;
				socket.onmessage = this.on_message;
				socket.onclose = this.on_close;
				socket.onerror = this.on_error;
				socket.destroy = this.destroy;

				socket.id = this.sockets.size + 1;

				this.sockets.set( socket.id, socket );

				return socket;
			} catch(e) {
				Module.print("Socket creation failed:" + e);
				return 0;
			}
		};
		libwebsocket.on_connect = function() {
			var stack = Runtime.stackSave();
			// filter protocol //
			libwebsocket.on_event( 0, ctx, this.id, 9, this.user_data, allocate(intArrayFromString(this.protocol), 'i8', ALLOC_STACK), this.protocol.length );
			// client established
			libwebsocket.on_event( this.protocol_id, ctx, this.id, 3, this.user_data, 0, 0 );
			Runtime.stackRestore(stack);
		};
		libwebsocket.on_message = function(event) {
			var stack = Runtime.stackSave();
			var len = event.data.byteLength;
			var ptr = allocate( len, 'i8', ALLOC_STACK);

			var data = new Uint8Array( event.data );

			for(var i =0, buf = ptr; i < len; ++i ) {
				setValue(buf, data[i], 'i8');
				buf++;
			}

			// client receive //
			libwebsocket.on_event( this.protocol_id, ctx, this.id, 6, this.user_data, ptr, len );
			Runtime.stackRestore(stack);
		};
		libwebsocket.on_close = function() {
			// closed //
			libwebsocket.on_event( this.protocol_id, ctx, this.id, 4, this.user_data, 0, 0 );
			this.destroy();
		};
		libwebsocket.on_error = function() {
			// client connection error //
			libwebsocket.on_event( this.protocol_id, ctx, this.id, 2, this.user_data, 0, 0 );
			this.destroy();
		};
		libwebsocket.destroy = function() {
			libwebsocket.sockets.set( this.id, undefined );
			libwebsocket.on_event( this.protocol_id, ctx, this.id, 11, this.user_data, 0, 0 );
		};

		Module.__libwebsocket = libwebsocket;
	}, ctx  );

	return ctx;
}

void libwebsocket_context_destroy(struct libwebsocket_context* ctx ) {
	delete ctx;
}

struct libwebsocket* libwebsocket_client_connect_extended(struct libwebsocket_context* ctx , const char* url, const char* protocol, void* user_data ) {

	struct libwebsocket* s =  (struct libwebsocket*)EM_ASM_INT({
		var socket = Module.__libwebsocket.connect( Pointer_stringify($0), Pointer_stringify($1), $2);
		if( ! socket )
			return 0;

		return socket.id;
	}, url, protocol, user_data);

	return s;
}

int libwebsocket_write( struct libwebsocket* socket, const void* data, int len, enum libwebsocket_write_protocol protocol ) {
	return EM_ASM_INT({
		var socket = Module.__libwebsocket.sockets.get( $0 );
		if( ! socket )
			return -1;

		// alloc a Uint8Array backed by the incomming data.
		var data_in = new Uint8Array(Module.HEAPU8.buffer, $1, $2 );
		// allow the dest array
		var data = new Uint8Array($2);
		// set the dest from the src
		data.set(data_in);

		socket.send( data );

		return $2;

	}, socket, data, len );
}

void libwebsocket_callback_on_writable( struct libwebsocket_context* ctx, struct libwebsocket* socket ) {
	// no-op
}

#endif

/*** End of inlined file: libwebsockets_asmjs.cpp ***/


// 3rd party

/*** Start of inlined file: crc.c ***/
#include <stdlib.h>
#include <stdint.h>

/**
 * Static table used for the table_driven implementation.
 *****************************************************************************/
static const crc_t crc_table[256] = {
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
	0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
	0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
	0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
	0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
	0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
	0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
	0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
	0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
	0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
	0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
	0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
	0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
	0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
	0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
	0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
	0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
	0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
	0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
	0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
	0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
	0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

/**
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
	const unsigned char *d = (const unsigned char *)data;
	unsigned int tbl_idx;

	while (data_len--) {
		tbl_idx = ((crc >> 24) ^ *d) & 0xff;
		crc = (crc_table[tbl_idx] ^ (crc << 8)) & 0xffffffff;

		d++;
	}
	return crc & 0xffffffff;
}

/*** End of inlined file: crc.c ***/



/*** Start of inlined file: sha1.c ***/
/*
 *  Define the SHA1 circular left shift macro
 */
#define SHA1CircularShift(bits,word) \
				(((word) << (bits)) | ((word) >> (32-(bits))))

/* Local Function Prototyptes */
void SHA1PadMessage(SHA1Context *);
void SHA1ProcessMessageBlock(SHA1Context *);

/*
 *  SHA1Reset
 *
 *  Description:
 *      This function will initialize the SHA1Context in preparation
 *      for computing a new SHA1 message digest.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to reset.
 *
 *  Returns:
 *      sha Error Code.
 *
 */
int SHA1Reset(SHA1Context *context)
{
	if (!context)
	{
		return shaNull;
	}

	context->Length_Low             = 0;
	context->Length_High            = 0;
	context->Message_Block_Index    = 0;

	context->Intermediate_Hash[0]   = 0x67452301;
	context->Intermediate_Hash[1]   = 0xEFCDAB89;
	context->Intermediate_Hash[2]   = 0x98BADCFE;
	context->Intermediate_Hash[3]   = 0x10325476;
	context->Intermediate_Hash[4]   = 0xC3D2E1F0;

	context->Computed   = 0;
	context->Corrupted  = 0;

	return shaSuccess;
}

/*
 *  SHA1Result
 *
 *  Description:
 *      This function will return the 160-bit message digest into the
 *      Message_Digest array  provided by the caller.
 *      NOTE: The first octet of hash is stored in the 0th element,
 *            the last octet of hash in the 19th element.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to use to calculate the SHA-1 hash.
 *      Message_Digest: [out]
 *          Where the digest is returned.
 *
 *  Returns:
 *      sha Error Code.
 *
 */
int SHA1Result( SHA1Context *context,
				uint8_t Message_Digest[SHA1HashSize])
{
	int i;

	if (!context || !Message_Digest)
	{
		return shaNull;
	}

	if (context->Corrupted)
	{
		return context->Corrupted;
	}

	if (!context->Computed)
	{
		SHA1PadMessage(context);
		for(i=0; i<64; ++i)
		{
			/* message may be sensitive, clear it out */
			context->Message_Block[i] = 0;
		}
		context->Length_Low = 0;    /* and clear length */
		context->Length_High = 0;
		context->Computed = 1;

	}

	for(i = 0; i < SHA1HashSize; ++i)
	{
		Message_Digest[i] = context->Intermediate_Hash[i>>2]
							>> 8 * ( 3 - ( i & 0x03 ) );
	}

	return shaSuccess;
}

/*
 *  SHA1Input
 *
 *  Description:
 *      This function accepts an array of octets as the next portion
 *      of the message.
 *
 *  Parameters:
 *      context: [in/out]
 *          The SHA context to update
 *      message_array: [in]
 *          An array of characters representing the next portion of
 *          the message.
 *      length: [in]
 *          The length of the message in message_array
 *
 *  Returns:
 *      sha Error Code.
 *
 */
int SHA1Input(    SHA1Context    *context,
				  const uint8_t  *message_array,
				  unsigned       length)
{
	if (!length)
	{
		return shaSuccess;
	}

	if (!context || !message_array)
	{
		return shaNull;
	}

	if (context->Computed)
	{
		context->Corrupted = shaStateError;

		return shaStateError;
	}

	if (context->Corrupted)
	{
		 return context->Corrupted;
	}
	while(length-- && !context->Corrupted)
	{
	context->Message_Block[context->Message_Block_Index++] =
					(*message_array & 0xFF);

	context->Length_Low += 8;
	if (context->Length_Low == 0)
	{
		context->Length_High++;
		if (context->Length_High == 0)
		{
			/* Message is too long */
			context->Corrupted = 1;
		}
	}

	if (context->Message_Block_Index == 64)
	{
		SHA1ProcessMessageBlock(context);
	}

	message_array++;
	}

	return shaSuccess;
}

/*
 *  SHA1ProcessMessageBlock
 *
 *  Description:
 *      This function will process the next 512 bits of the message
 *      stored in the Message_Block array.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:

 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the
 *      names used in the publication.
 *
 *
 */
void SHA1ProcessMessageBlock(SHA1Context *context)
{
	const uint32_t K[] =    {       /* Constants defined in SHA-1   */
							0x5A827999,
							0x6ED9EBA1,
							0x8F1BBCDC,
							0xCA62C1D6
							};
	int           t;                 /* Loop counter                */
	uint32_t      temp;              /* Temporary word value        */
	uint32_t      W[80];             /* Word sequence               */
	uint32_t      A, B, C, D, E;     /* Word buffers                */

	/*
	 *  Initialize the first 16 words in the array W
	 */
	for(t = 0; t < 16; t++)
	{
		W[t] = context->Message_Block[t * 4] << 24;
		W[t] |= context->Message_Block[t * 4 + 1] << 16;
		W[t] |= context->Message_Block[t * 4 + 2] << 8;
		W[t] |= context->Message_Block[t * 4 + 3];
	}

	for(t = 16; t < 80; t++)
	{
	   W[t] = SHA1CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
	}

	A = context->Intermediate_Hash[0];
	B = context->Intermediate_Hash[1];
	C = context->Intermediate_Hash[2];
	D = context->Intermediate_Hash[3];
	E = context->Intermediate_Hash[4];

	for(t = 0; t < 20; t++)
	{
		temp =  SHA1CircularShift(5,A) +
				((B & C) | ((~B) & D)) + E + W[t] + K[0];
		E = D;
		D = C;
		C = SHA1CircularShift(30,B);

		B = A;
		A = temp;
	}

	for(t = 20; t < 40; t++)
	{
		temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
		E = D;
		D = C;
		C = SHA1CircularShift(30,B);
		B = A;
		A = temp;
	}

	for(t = 40; t < 60; t++)
	{
		temp = SHA1CircularShift(5,A) +
			   ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
		E = D;
		D = C;
		C = SHA1CircularShift(30,B);
		B = A;
		A = temp;
	}

	for(t = 60; t < 80; t++)
	{
		temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
		E = D;
		D = C;
		C = SHA1CircularShift(30,B);
		B = A;
		A = temp;
	}

	context->Intermediate_Hash[0] += A;
	context->Intermediate_Hash[1] += B;
	context->Intermediate_Hash[2] += C;
	context->Intermediate_Hash[3] += D;
	context->Intermediate_Hash[4] += E;

	context->Message_Block_Index = 0;
}

/*
 *  SHA1PadMessage
 *

 *  Description:
 *      According to the standard, the message must be padded to an even
 *      512 bits.  The first padding bit must be a '1'.  The last 64
 *      bits represent the length of the original message.  All bits in
 *      between should be 0.  This function will pad the message
 *      according to those rules by filling the Message_Block array
 *      accordingly.  It will also call the ProcessMessageBlock function
 *      provided appropriately.  When it returns, it can be assumed that
 *      the message digest has been computed.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to pad
 *      ProcessMessageBlock: [in]
 *          The appropriate SHA*ProcessMessageBlock function
 *  Returns:
 *      Nothing.
 *
 */

void SHA1PadMessage(SHA1Context *context)
{
	/*
	 *  Check to see if the current message block is too small to hold
	 *  the initial padding bits and length.  If so, we will pad the
	 *  block, process it, and then continue padding into a second
	 *  block.
	 */
	if (context->Message_Block_Index > 55)
	{
		context->Message_Block[context->Message_Block_Index++] = 0x80;
		while(context->Message_Block_Index < 64)
		{
			context->Message_Block[context->Message_Block_Index++] = 0;
		}

		SHA1ProcessMessageBlock(context);

		while(context->Message_Block_Index < 56)
		{
			context->Message_Block[context->Message_Block_Index++] = 0;
		}
	}
	else
	{
		context->Message_Block[context->Message_Block_Index++] = 0x80;
		while(context->Message_Block_Index < 56)
		{

			context->Message_Block[context->Message_Block_Index++] = 0;
		}
	}

	/*
	 *  Store the message length as the last 8 octets
	 */
	context->Message_Block[56] = context->Length_High >> 24;
	context->Message_Block[57] = context->Length_High >> 16;
	context->Message_Block[58] = context->Length_High >> 8;
	context->Message_Block[59] = context->Length_High;
	context->Message_Block[60] = context->Length_Low >> 24;
	context->Message_Block[61] = context->Length_Low >> 16;
	context->Message_Block[62] = context->Length_Low >> 8;
	context->Message_Block[63] = context->Length_Low;

	SHA1ProcessMessageBlock(context);
}

/*** End of inlined file: sha1.c ***/


/*** Start of inlined file: hmac.cpp ***/
#include <cstring>

void HMACInit(HMACContext *ctx, const uint8_t* key, unsigned key_len)
{
	uint8_t key_block[HMAC_BLOCKSIZE];
	uint8_t pad[HMAC_BLOCKSIZE];
	unsigned key_block_len;

	if (HMAC_BLOCKSIZE < key_len) {
		SHA1Context sha;
		SHA1Reset(&sha);
		SHA1Input(&sha, key, key_len);
		SHA1Result(&sha, key_block);
		key_block_len = HMAC_DIGEST_SIZE;
	} else {
		memcpy(key_block, key, key_len);
		key_block_len = key_len;
	}
	memset(&key_block[key_block_len], 0, sizeof(key_block) - key_block_len);

	for (int i = 0; i < HMAC_BLOCKSIZE; ++i) {
		pad[i] = 0x36 ^ key_block[i];
	}
	SHA1Reset(&ctx->i_ctx);
	SHA1Input(&ctx->i_ctx, pad, HMAC_BLOCKSIZE);

	for (int i = 0; i < HMAC_BLOCKSIZE; ++i) {
		pad[i] = 0x5c ^ key_block[i];
	}
	SHA1Reset(&ctx->o_ctx);
	SHA1Input(&ctx->o_ctx, pad, HMAC_BLOCKSIZE);
}

int HMACInput(HMACContext *ctx, const uint8_t* data, unsigned data_len)
{
	return SHA1Input(&ctx->i_ctx, data, data_len);
}

int HMACResult(HMACContext *ctx, uint8_t Message_Digest[HMAC_DIGEST_SIZE])
{
	SHA1Result(&ctx->i_ctx, Message_Digest);

	SHA1Input(&ctx->o_ctx, Message_Digest, HMAC_DIGEST_SIZE);

	SHA1Result(&ctx->o_ctx, Message_Digest);

	return shaSuccess;
}

static const char kHexLookup[] = "0123456789abcdef";

void HMACResultToHex(uint8_t digest[HMAC_DIGEST_SIZE], std::string& out_hex)
{
	out_hex.resize(HMAC_DIGEST_SIZE * 2);

	for (int i = 0; i < HMAC_DIGEST_SIZE; ++i) {
		auto b =  digest[i];
		out_hex[i * 2] = kHexLookup[b >> 4];
		out_hex[i * 2 + 1] = kHexLookup[b & 0xf];
	}
}

/*** End of inlined file: hmac.cpp ***/

