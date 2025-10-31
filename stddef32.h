#ifndef STDDEF32_H
#define STDDEF32_H

typedef char			i8;
typedef short			i16;
typedef int				i32;
typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;
// Note: Avoid using float, they are slow.
typedef float			f32;
// Note: This should never be used. 
// It is emulated on esp32 but it has very VERY bad performance.
// It does not exist on the esp8266.
typedef double			f64;

#endif
