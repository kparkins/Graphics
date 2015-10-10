//
//  Macros.h
//  Graphics
//
//  Created by Kyle J Parkinson on 10/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef MACROS_H
#define MACROS_H

#if defined (__APPLE__) || defined(__MACH__) || defined(__GNUC__)

#define FORCE_INLINE inline __attribute__ ((always_inline))
#define ALIGN_16 __attribute__ ((aligned(16)))

#elif defined(_WIN32)

#define FORCE_INLINE inline __forceinline
#define ALIGN_16 __declspec(align(16))

#endif

#endif /* Macros_h */
