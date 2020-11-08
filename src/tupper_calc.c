#include "./tupper_field.h"
#include <mpfr.h>

mpfr_prec_t prec = 2000;

int tupper(int x, mpfr_t y) {
  int inex = 0;
  int result;

  mpfr_t xx, yy, y_div_17, x_mul_17, y_mod_17, y_div_17_floored, temp4, temp5,
      temp6, temp7, yk, c;

  mpfr_inits2(prec, y_div_17, y_div_17_floored, x_mul_17, y_mod_17, temp4,
              temp5, temp6, temp7, yk, c, xx, yy, (mpfr_ptr *)0);

  inex = mpfr_set_d(xx, (double)x, MPFR_RNDN);
  inex = mpfr_set(yy, y, MPFR_RNDN);

  inex = mpfr_set_d(c, 17.0, MPFR_RNDN);
  inex = mpfr_div(y_div_17, yy, c, MPFR_RNDN);
  inex = mpfr_floor(y_div_17_floored, y_div_17);

  inex = mpfr_set_d(c, -17.0, MPFR_RNDN);
  inex = mpfr_floor(xx, xx);
  inex = mpfr_mul(x_mul_17, xx, c, MPFR_RNDN);

  inex = mpfr_set_d(c, 17.0, MPFR_RNDN);
  inex = mpfr_floor(yy, yy);
  inex = mpfr_fmod(y_mod_17, yy, c, MPFR_RNDN);

  inex = mpfr_sub(temp4, x_mul_17, y_mod_17, MPFR_RNDN);

  inex = mpfr_set_d(c, 2.0, MPFR_RNDN);
  inex = mpfr_pow(temp5, c, temp4, MPFR_RNDN);

  inex = mpfr_mul(temp6, y_div_17_floored, temp5, MPFR_RNDN);

  inex = mpfr_fmod(temp7, temp6, c, MPFR_RNDN);
  inex = mpfr_floor(temp7, temp7);

  inex = mpfr_set_d(c, 0.5, MPFR_RNDN);
  result = mpfr_cmp(temp7, c);

  mpfr_clears(y_div_17, x_mul_17, y_mod_17, temp4, temp5, temp6, temp7, yk,
              (mpfr_ptr *)0);
  return result;
}

void tupper_loop(Field *field) {
  mpfr_t k;
  mpfr_t a, temp;
  mpfr_inits2(prec, k, (mpfr_ptr *)0);

  mpfr_set_str(
      k,
      "485845063675531583314437649507738787543477804700480079077056818682685491"
      "338740948046431989808671195598522634862861259205157251920347038482297784"
      "168650281377234155007166522269961098691358424796883658706253737085596435"
      "821784280478722136969476813983497282570733401297377046950460844446807849"
      "019110898762269104161852931406840448753721461986125526838259363775980576"
      "781318277028239239124655725990212360746666521455598337649788424029641285"
      "059433707448118505714209060357598462150863734880406811212908701522505399"
      "4512537667043573283090413808140105325068",
      10, MPFR_RNDN);

  for (size_t j = 0; j < BOARD_WIDTH; ++j) {
    for (size_t i = 0; i < BOARD_HEIGHT; ++i) {
      mpfr_inits2(prec, a, temp, (mpfr_ptr *)0);
      mpfr_set_d(temp, (double)i, MPFR_RNDN);
      mpfr_add(a, k, temp, MPFR_RNDN);
      int res = tupper(j, a);
      if (res > 0) {
        Coord pos = {.x = j, .y = 16 - i};
        field->walls[i][j].pos = pos;
      }
      mpfr_clear(a);
    }
  }
  mpfr_clear(k);
}
