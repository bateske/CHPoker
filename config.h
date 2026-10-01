// CHPoker build switches.
//
// Keep feature switches here rather than in --build-property flags. The game
// needs the CHGame core 0.2.4+ with Optimize set to "Smallest + LTO" and the
// default Peripherals setting ("Game", which compiles out
// Serial1/tone/HardwareTimer: ~4 KB of flash). Release builds also set USB
// to "Upload only" (no Serial: ~0.6 KB).
#pragma once

#define CHPK_VERSION     "0.1"

// Which games are built in. 0: all four. If they ever stop fitting, the
// same source builds two editions (tools/device.py --edition N):
// 1 "Hold'em" (Hold'em + Omaha), 2 "Classic" (Five Card Draw + Stud).
#ifndef CHPK_EDITION
#define CHPK_EDITION     0
#endif
#define CHPK_HOLDEM      (CHPK_EDITION != 2)
#define CHPK_OMAHA       (CHPK_EDITION != 2)
#define CHPK_DRAW        (CHPK_EDITION != 1)
#define CHPK_STUD        (CHPK_EDITION != 1)

// Serial debug protocol: screenshots, input injection, lockstep, perf.
// Off in normal builds. tools/device.py turns it on with
// --build-property build.extra_flags, and leaves USB at "Serial" for it.
#ifndef CHPK_DEBUG
#ifdef CHSIM
#define CHPK_DEBUG       1       // the simulator is driven through the protocol
#else
#define CHPK_DEBUG       0
#endif
#endif

// Device debug builds carry the ~2 KB protocol, so they may leave out things
// the tests never need. The simulator (not flash-bound) and release builds
// keep everything.
#if CHPK_DEBUG && !defined(CHSIM) && !defined(CHPK_FULL)
#define CHPK_LEAN        1
#else
#define CHPK_LEAN        0
#endif

// Section profiler (dbg::prof + the T command). Opt-in: costs flash.
#ifndef CHPK_PROFILE
#define CHPK_PROFILE     0
#endif

// Frame rate the game logic is paced for.
#define CHPK_FPS         60
