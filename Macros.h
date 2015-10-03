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

#define force_inline inline __attribute__ ((always_inline))
#define align_16 __attribute__ ((aligned(16)))

#else

// Room for MSVC++ / GNU C++ & other variants

#endif

#endif /* Macros_h */
