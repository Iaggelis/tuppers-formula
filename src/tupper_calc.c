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

  mpfr_set_str(k,
               "960939379918958884971672962127852754715004339660129"
               "306651505519271702802395266424689642842174350718121"
               "267153782770623355993237280874144307891325963941337"
               "723487857735749823926629715517173716995165232890538"
               "221612403238855866184013235585136048828693337902491"
               "454229288667081096184496091705183454067827731551705"
               "405381627380967602565625016981482083418783163849115"
               "590225610003652351370343874461848378737238198224849"
               "863465033159410054974700593138339226497249461751545"
               "728366702369745461014655997933798537483143786841806"
               "593422227898388722980000748404719",
               10, MPFR_RNDZ);

  /* mpfr_set_str(k, */
  /*              "48584506367553158331443764950773878754347780470048007907705"
   */
  /*              "6818682685491" */
  /*              "33874094804643198980867119559852263486286125920515725192034"
   */
  /*              "7038482297784" */
  /*              "16865028137723415500716652226996109869135842479688365870625"
   */
  /*              "3737085596435" */
  /*              "82178428047872213696947681398349728257073340129737704695046"
   */
  /*              "0844446807849" */
  /*              "01911089876226910416185293140684044875372146198612552683825"
   */
  /*              "9363775980576" */
  /*              "78131827702823923912465572599021236074666652145559833764978"
   */
  /*              "8424029641285" */
  /*              "05943370744811850571420906035759846215086373488040681121290"
   */
  /*              "8701522505399" */
  /*              "4512537667043573283090413808140105325068", */
  /*              10, MPFR_RNDN); */

  for (size_t j = 0; j < BOARD_WIDTH; ++j) {
    for (size_t i = 0; i < BOARD_HEIGHT; ++i) {
      mpfr_inits2(prec, a, temp, (mpfr_ptr *)0);
      mpfr_set_d(temp, (double)i, MPFR_RNDN);
      mpfr_add(a, k, temp, MPFR_RNDN);
      int res = tupper(j, a);
      if (res > 0) {
        Coord pos = {.x = 105 - j, .y = i};
        field->walls[i][j].pos = pos;
      }
      mpfr_clear(a);
    }
  }
  mpfr_clear(k);
}
