{
  "targets": [
    {
      "target_name": "dilithium",
      "sources": [ "module.cc", "sign.c", "polyvec.c", "packing.c", "poly.c", "reduce.c", "ntt.c", "rounding.c", "fips202.c", "randombytes.c" ],
      "cflags" : ["-Wall -Wextra -march=native -mtune=native -O3 -DMODE=2 -fomit-frame-pointer"],
      "include_dirs": [ "<!(node -e \"require('nan')\")"]
    }
  ]
}
