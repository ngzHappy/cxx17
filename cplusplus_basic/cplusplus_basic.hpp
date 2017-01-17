﻿#ifndef __CPLUSPLUS_BASIC_HPP_0X97721a
#define __CPLUSPLUS_BASIC_HPP_0X97721a

#ifdef __cplusplus

#ifndef CPLUSPLUS_OBJECT
#define CPLUSPLUS_OBJECT(_objname_) inline static constexpr auto __0x21_size() noexcept(true){ return sizeof(_objname_); } MEMORY_CLASS_NEW_DELETE
#endif // !CPLUSPLUS_OBJECT

#ifndef CPLUSPLUS_EXCEPTION
#define CPLUSPLUS_EXCEPTION(_is_quit_) exception::exception_handle(static_cast<bool>(_is_quit_),__LINE__,__func__,__FILE__)
#endif // !CPLUSPLUS_EXCEPTION

#ifndef DECLTYPE
#define DECLTYPE(_v__) std::remove_cv_t<std::remove_reference_t<decltype(_v__)>>
#endif // !DECLTYPE

#ifndef PLACEMENT_NEW
#define PLACEMENT_NEW(_x_) ::new(_x_)
#endif

#include <utility>
#include <numeric>
#include <algorithm>
#include "memory/Memory.hpp"
#include "utility/type_traits.hpp"
#include "exception/Exception.hpp"
#include "thread/ShadowThread.hpp"

#endif // !__cplusplus

// EF BB BF
// /*①*/\u2460
// /*②*/\u2461
// /*③*/\u2462
// /*④*/\u2463
// /*⑤*/\u2464
// /*⑥*/\u2465
// /*⑦*/\u2466
// /*⑧*/\u2467
// /*⑨*/\u2468
// /*⑩*/\u2469
// /*⑪*/\u246a
// /*⑫*/\u246b
// /*⑬*/\u246c
// /*⑭*/\u246d
// /*⑮*/\u246e
// /*⑯*/\u246f
// /*⑰*/\u2470
// /*⑱*/\u2471
// /*⑲*/\u2472
// /*⑳*/\u2473
// /*⑴*/\u2474
// /*⑵*/\u2475
// /*⑶*/\u2476
// /*⑷*/\u2477
// /*⑸*/\u2478
// /*⑹*/\u2479
// /*⑺*/\u247a
// /*⑻*/\u247b
// /*⑼*/\u247c
// /*⑽*/\u247d
// /*⑾*/\u247e
// /*⑿*/\u247f
// /*⒀*/\u2480
// /*⒁*/\u2481
// /*⒂*/\u2482
// /*⒃*/\u2483
// /*⒄*/\u2484
// /*⒅*/\u2485
// /*⒆*/\u2486
// /*⒇*/\u2487
// /*⒈*/\u2488
// /*⒉*/\u2489
// /*⒊*/\u248a
// /*⒋*/\u248b
// /*⒌*/\u248c
// /*⒍*/\u248d
// /*⒎*/\u248e
// /*⒏*/\u248f
// /*⒐*/\u2490
// /*⒑*/\u2491
// /*⒒*/\u2492
// /*⒓*/\u2493
// /*⒔*/\u2494
// /*⒕*/\u2495
// /*⒖*/\u2496
// /*⒗*/\u2497
// /*⒘*/\u2498
// /*⒙*/\u2499
// /*⒚*/\u249a
// /*⒛*/\u249b
// /*⒜*/\u249c
// /*⒝*/\u249d
// /*⒞*/\u249e
// /*⒟*/\u249f
// /*⒠*/\u24a0
// /*⒡*/\u24a1
// /*⒢*/\u24a2
// /*⒣*/\u24a3
// /*⒤*/\u24a4
// /*⒥*/\u24a5
// /*⒦*/\u24a6
// /*⒧*/\u24a7
// /*⒨*/\u24a8
// /*⒩*/\u24a9
// /*⒪*/\u24aa
// /*⒫*/\u24ab
// /*⒬*/\u24ac
// /*⒭*/\u24ad
// /*⒮*/\u24ae
// /*⒯*/\u24af
// /*⒰*/\u24b0
// /*⒱*/\u24b1
// /*⒲*/\u24b2
// /*⒳*/\u24b3
// /*⒴*/\u24b4
// /*⒵*/\u24b5
// /*Ⓐ*/\u24b6
// /*Ⓑ*/\u24b7
// /*Ⓒ*/\u24b8
// /*Ⓓ*/\u24b9
// /*Ⓔ*/\u24ba
// /*Ⓕ*/\u24bb
// /*Ⓖ*/\u24bc
// /*Ⓗ*/\u24bd
// /*Ⓘ*/\u24be
// /*Ⓙ*/\u24bf
// /*Ⓚ*/\u24c0
// /*Ⓛ*/\u24c1
// /*Ⓜ*/\u24c2
// /*Ⓝ*/\u24c3
// /*Ⓞ*/\u24c4
// /*Ⓟ*/\u24c5
// /*Ⓠ*/\u24c6
// /*Ⓡ*/\u24c7
// /*Ⓢ*/\u24c8
// /*Ⓣ*/\u24c9
// /*Ⓤ*/\u24ca
// /*Ⓥ*/\u24cb
// /*Ⓦ*/\u24cc
// /*Ⓧ*/\u24cd
// /*Ⓨ*/\u24ce
// /*Ⓩ*/\u24cf
// /*ⓐ*/\u24d0
// /*ⓑ*/\u24d1
// /*ⓒ*/\u24d2
// /*ⓓ*/\u24d3
// /*ⓔ*/\u24d4
// /*ⓕ*/\u24d5
// /*ⓖ*/\u24d6
// /*ⓗ*/\u24d7
// /*ⓘ*/\u24d8
// /*ⓙ*/\u24d9
// /*ⓚ*/\u24da
// /*ⓛ*/\u24db
// /*ⓜ*/\u24dc
// /*ⓝ*/\u24dd
// /*ⓞ*/\u24de
// /*ⓟ*/\u24df
// /*ⓠ*/\u24e0
// /*ⓡ*/\u24e1
// /*ⓢ*/\u24e2
// /*ⓣ*/\u24e3
// /*ⓤ*/\u24e4
// /*ⓥ*/\u24e5
// /*ⓦ*/\u24e6
// /*ⓧ*/\u24e7
// /*ⓨ*/\u24e8
// /*ⓩ*/\u24e9
// /*⓪*/\u24ea
// /*⓫*/\u24eb
// /*⓬*/\u24ec
// /*⓭*/\u24ed
// /*⓮*/\u24ee
// /*⓯*/\u24ef
// /*⓰*/\u24f0
// /*⓱*/\u24f1
// /*⓲*/\u24f2
// /*⓳*/\u24f3
// /*⓴*/\u24f4
// /*⓵*/\u24f5
// /*⓶*/\u24f6
// /*⓷*/\u24f7
// /*⓸*/\u24f8
// /*⓹*/\u24f9
// /*⓺*/\u24fa
// /*⓻*/\u24fb
// /*⓼*/\u24fc
// /*⓽*/\u24fd
// /*⓾*/\u24fe
// /*⓿*/\u24ff

#endif // !__CPLUSPLUS_BASIC_HPP_0X97721

