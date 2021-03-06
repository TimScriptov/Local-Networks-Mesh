#include "sc.h"
#include <stdint.h>
#include "crypto_int64.h"
#include "crypto_uint32.h"
#include "crypto_uint64.h"

static crypto_uint64 load_3(const unsigned char *in)
{
  crypto_uint64 result;
  result = (crypto_uint64) in[0];
  result |= ((crypto_uint64) in[1]) << 8;
  result |= ((crypto_uint64) in[2]) << 16;
  return result;
}

static crypto_uint64 load_4(const unsigned char *in)
{
  crypto_uint64 result;
  result = (crypto_uint64) in[0];
  result |= ((crypto_uint64) in[1]) << 8;
  result |= ((crypto_uint64) in[2]) << 16;
  result |= ((crypto_uint64) in[3]) << 24;
  return result;
}

/*
Input:
  s[0]+256*s[1]+...+256^63*s[63] = s

Output:
  s[0]+256*s[1]+...+256^31*s[31] = s mod l
  where l = 2^252 + 27742317777372353535851937790883648493.
  Overwrites s in place.
*/

void sc_reduce(unsigned char *s)
{
  int64_t s0 = 2097151 & load_3(s);
  int64_t s1 = 2097151 & (load_4(s + 2) >> 5);
  int64_t s2 = 2097151 & (load_3(s + 5) >> 2);
  int64_t s3 = 2097151 & (load_4(s + 7) >> 7);
  int64_t s4 = 2097151 & (load_4(s + 10) >> 4);
  int64_t s5 = 2097151 & (load_3(s + 13) >> 1);
  int64_t s6 = 2097151 & (load_4(s + 15) >> 6);
  int64_t s7 = 2097151 & (load_3(s + 18) >> 3);
  int64_t s8 = 2097151 & load_3(s + 21);
  int64_t s9 = 2097151 & (load_4(s + 23) >> 5);
  int64_t s10 = 2097151 & (load_3(s + 26) >> 2);
  int64_t s11 = 2097151 & (load_4(s + 28) >> 7);
  int64_t s12 = 2097151 & (load_4(s + 31) >> 4);
  int64_t s13 = 2097151 & (load_3(s + 34) >> 1);
  int64_t s14 = 2097151 & (load_4(s + 36) >> 6);
  int64_t s15 = 2097151 & (load_3(s + 39) >> 3);
  int64_t s16 = 2097151 & load_3(s + 42);
  int64_t s17 = 2097151 & (load_4(s + 44) >> 5);
  int64_t s18 = 2097151 & (load_3(s + 47) >> 2);
  int64_t s19 = 2097151 & (load_4(s + 49) >> 7);
  int64_t s20 = 2097151 & (load_4(s + 52) >> 4);
  int64_t s21 = 2097151 & (load_3(s + 55) >> 1);
  int64_t s22 = 2097151 & (load_4(s + 57) >> 6);
  int64_t s23 = (load_4(s + 60) >> 3);
  int64_t carry0;
  int64_t carry1;
  int64_t carry2;
  int64_t carry3;
  int64_t carry4;
  int64_t carry5;
  int64_t carry6;
  int64_t carry7;
  int64_t carry8;
  int64_t carry9;
  int64_t carry10;
  int64_t carry11;
  int64_t carry12;
  int64_t carry13;
  int64_t carry14;
  int64_t carry15;
  int64_t carry16;

  s11 += s23 * 666643;
  s12 += s23 * 470296;
  s13 += s23 * 654183;
  s14 -= s23 * 997805;
  s15 += s23 * 136657;
  s16 -= s23 * 683901;

  s10 += s22 * 666643;
  s11 += s22 * 470296;
  s12 += s22 * 654183;
  s13 -= s22 * 997805;
  s14 += s22 * 136657;
  s15 -= s22 * 683901;

  s9 += s21 * 666643;
  s10 += s21 * 470296;
  s11 += s21 * 654183;
  s12 -= s21 * 997805;
  s13 += s21 * 136657;
  s14 -= s21 * 683901;

  s8 += s20 * 666643;
  s9 += s20 * 470296;
  s10 += s20 * 654183;
  s11 -= s20 * 997805;
  s12 += s20 * 136657;
  s13 -= s20 * 683901;

  s7 += s19 * 666643;
  s8 += s19 * 470296;
  s9 += s19 * 654183;
  s10 -= s19 * 997805;
  s11 += s19 * 136657;
  s12 -= s19 * 683901;

  s6 += s18 * 666643;
  s7 += s18 * 470296;
  s8 += s18 * 654183;
  s9 -= s18 * 997805;
  s10 += s18 * 136657;
  s11 -= s18 * 683901;

    carry6 = (s6 + (int64_t) (1L << 20)) >> 21; s7 += carry6; s6 -= carry6 * ((uint64_t) 1L << 21);
  carry8 = (s8 + (int64_t) (1L << 20)) >> 21; s9 += carry8; s8 -= carry8 * ((uint64_t) 1L << 21);
  carry10 = (s10 + (int64_t) (1L << 20)) >> 21; s11 += carry10; s10 -= carry10 * ((uint64_t) 1L << 21);
  carry12 = (s12 + (int64_t) (1L << 20)) >> 21; s13 += carry12; s12 -= carry12 * ((uint64_t) 1L << 21);
  carry14 = (s14 + (int64_t) (1L << 20)) >> 21; s15 += carry14; s14 -= carry14 * ((uint64_t) 1L << 21);
  carry16 = (s16 + (int64_t) (1L << 20)) >> 21; s17 += carry16; s16 -= carry16 * ((uint64_t) 1L << 21);

  carry7 = (s7 + (int64_t) (1L << 20)) >> 21; s8 += carry7; s7 -= carry7 * ((uint64_t) 1L << 21);
  carry9 = (s9 + (int64_t) (1L << 20)) >> 21; s10 += carry9; s9 -= carry9 * ((uint64_t) 1L << 21);
  carry11 = (s11 + (int64_t) (1L << 20)) >> 21; s12 += carry11; s11 -= carry11 * ((uint64_t) 1L << 21);
  carry13 = (s13 + (int64_t) (1L << 20)) >> 21; s14 += carry13; s13 -= carry13 * ((uint64_t) 1L << 21);
  carry15 = (s15 + (int64_t) (1L << 20)) >> 21; s16 += carry15; s15 -= carry15 * ((uint64_t) 1L << 21);

  s5 += s17 * 666643;
  s6 += s17 * 470296;
  s7 += s17 * 654183;
  s8 -= s17 * 997805;
  s9 += s17 * 136657;
  s10 -= s17 * 683901;

  s4 += s16 * 666643;
  s5 += s16 * 470296;
  s6 += s16 * 654183;
  s7 -= s16 * 997805;
  s8 += s16 * 136657;
  s9 -= s16 * 683901;

  s3 += s15 * 666643;
  s4 += s15 * 470296;
  s5 += s15 * 654183;
  s6 -= s15 * 997805;
  s7 += s15 * 136657;
  s8 -= s15 * 683901;

  s2 += s14 * 666643;
  s3 += s14 * 470296;
  s4 += s14 * 654183;
  s5 -= s14 * 997805;
  s6 += s14 * 136657;
  s7 -= s14 * 683901;

  s1 += s13 * 666643;
  s2 += s13 * 470296;
  s3 += s13 * 654183;
  s4 -= s13 * 997805;
  s5 += s13 * 136657;
  s6 -= s13 * 683901;

  s0 += s12 * 666643;
  s1 += s12 * 470296;
  s2 += s12 * 654183;
  s3 -= s12 * 997805;
  s4 += s12 * 136657;
  s5 -= s12 * 683901;
  s12 = 0;

  carry0 = (s0 + (int64_t) (1L << 20)) >> 21; s1 += carry0; s0 -= carry0 * ((uint64_t) 1L << 21);
  carry2 = (s2 + (int64_t) (1L << 20)) >> 21; s3 += carry2; s2 -= carry2 * ((uint64_t) 1L << 21);
  carry4 = (s4 + (int64_t) (1L << 20)) >> 21; s5 += carry4; s4 -= carry4 * ((uint64_t) 1L << 21);
  carry6 = (s6 + (int64_t) (1L << 20)) >> 21; s7 += carry6; s6 -= carry6 * ((uint64_t) 1L << 21);
  carry8 = (s8 + (int64_t) (1L << 20)) >> 21; s9 += carry8; s8 -= carry8 * ((uint64_t) 1L << 21);
  carry10 = (s10 + (int64_t) (1L << 20)) >> 21; s11 += carry10; s10 -= carry10 * ((uint64_t) 1L << 21);

  carry1 = (s1 + (int64_t) (1L << 20)) >> 21; s2 += carry1; s1 -= carry1 * ((uint64_t) 1L << 21);
  carry3 = (s3 + (int64_t) (1L << 20)) >> 21; s4 += carry3; s3 -= carry3 * ((uint64_t) 1L << 21);
  carry5 = (s5 + (int64_t) (1L << 20)) >> 21; s6 += carry5; s5 -= carry5 * ((uint64_t) 1L << 21);
  carry7 = (s7 + (int64_t) (1L << 20)) >> 21; s8 += carry7; s7 -= carry7 * ((uint64_t) 1L << 21);
  carry9 = (s9 + (int64_t) (1L << 20)) >> 21; s10 += carry9; s9 -= carry9 * ((uint64_t) 1L << 21);
  carry11 = (s11 + (int64_t) (1L << 20)) >> 21; s12 += carry11; s11 -= carry11 * ((uint64_t) 1L << 21);

  s0 += s12 * 666643;
  s1 += s12 * 470296;
  s2 += s12 * 654183;
  s3 -= s12 * 997805;
  s4 += s12 * 136657;
  s5 -= s12 * 683901;
  s12 = 0;

  carry0 = s0 >> 21; s1 += carry0; s0 -= carry0 * ((uint64_t) 1L << 21);
  carry1 = s1 >> 21; s2 += carry1; s1 -= carry1 * ((uint64_t) 1L << 21);
  carry2 = s2 >> 21; s3 += carry2; s2 -= carry2 * ((uint64_t) 1L << 21);
  carry3 = s3 >> 21; s4 += carry3; s3 -= carry3 * ((uint64_t) 1L << 21);
  carry4 = s4 >> 21; s5 += carry4; s4 -= carry4 * ((uint64_t) 1L << 21);
  carry5 = s5 >> 21; s6 += carry5; s5 -= carry5 * ((uint64_t) 1L << 21);
  carry6 = s6 >> 21; s7 += carry6; s6 -= carry6 * ((uint64_t) 1L << 21);
  carry7 = s7 >> 21; s8 += carry7; s7 -= carry7 * ((uint64_t) 1L << 21);
  carry8 = s8 >> 21; s9 += carry8; s8 -= carry8 * ((uint64_t) 1L << 21);
  carry9 = s9 >> 21; s10 += carry9; s9 -= carry9 * ((uint64_t) 1L << 21);
  carry10 = s10 >> 21; s11 += carry10; s10 -= carry10 * ((uint64_t) 1L << 21);
  carry11 = s11 >> 21; s12 += carry11; s11 -= carry11 * ((uint64_t) 1L << 21);

  s0 += s12 * 666643;
  s1 += s12 * 470296;
  s2 += s12 * 654183;
  s3 -= s12 * 997805;
  s4 += s12 * 136657;
  s5 -= s12 * 683901;

  carry0 = s0 >> 21; s1 += carry0; s0 -= carry0 * ((uint64_t) 1L << 21);
  carry1 = s1 >> 21; s2 += carry1; s1 -= carry1 * ((uint64_t) 1L << 21);
  carry2 = s2 >> 21; s3 += carry2; s2 -= carry2 * ((uint64_t) 1L << 21);
  carry3 = s3 >> 21; s4 += carry3; s3 -= carry3 * ((uint64_t) 1L << 21);
  carry4 = s4 >> 21; s5 += carry4; s4 -= carry4 * ((uint64_t) 1L << 21);
  carry5 = s5 >> 21; s6 += carry5; s5 -= carry5 * ((uint64_t) 1L << 21);
  carry6 = s6 >> 21; s7 += carry6; s6 -= carry6 * ((uint64_t) 1L << 21);
  carry7 = s7 >> 21; s8 += carry7; s7 -= carry7 * ((uint64_t) 1L << 21);
  carry8 = s8 >> 21; s9 += carry8; s8 -= carry8 * ((uint64_t) 1L << 21);
  carry9 = s9 >> 21; s10 += carry9; s9 -= carry9 * ((uint64_t) 1L << 21);
  carry10 = s10 >> 21; s11 += carry10; s10 -= carry10 * ((uint64_t) 1L << 21);

  s[0] = s0 >> 0;
  s[1] = s0 >> 8;
  s[2] = (s0 >> 16) | (s1 * ((uint64_t) 1 << 5));
  s[3] = s1 >> 3;
  s[4] = s1 >> 11;
  s[5] = (s1 >> 19) | (s2 * ((uint64_t) 1 << 2));
  s[6] = s2 >> 6;
  s[7] = (s2 >> 14) | (s3 * ((uint64_t) 1 << 7));
  s[8] = s3 >> 1;
  s[9] = s3 >> 9;
  s[10] = (s3 >> 17) | (s4 * ((uint64_t) 1 << 4));
  s[11] = s4 >> 4;
  s[12] = s4 >> 12;
  s[13] = (s4 >> 20) | (s5 * ((uint64_t) 1 << 1));
  s[14] = s5 >> 7;
  s[15] = (s5 >> 15) | (s6 * ((uint64_t) 1 << 6));
  s[16] = s6 >> 2;
  s[17] = s6 >> 10;
  s[18] = (s6 >> 18) | (s7 * ((uint64_t) 1 << 3));
  s[19] = s7 >> 5;
  s[20] = s7 >> 13;
  s[21] = s8 >> 0;
  s[22] = s8 >> 8;
  s[23] = (s8 >> 16) | (s9 * ((uint64_t) 1 << 5));
  s[24] = s9 >> 3;
  s[25] = s9 >> 11;
  s[26] = (s9 >> 19) | (s10 * ((uint64_t) 1 << 2));
  s[27] = s10 >> 6;
  s[28] = (s10 >> 14) | (s11 * ((uint64_t) 1 << 7));
  s[29] = s11 >> 1;
  s[30] = s11 >> 9;
  s[31] = s11 >> 17;
}
