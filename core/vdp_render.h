/***************************************************************************************
 *  Genesis Plus
 *  Video Display Processor (pixel output rendering)
 *
 *  Support for all TMS99xx modes, Mode 4 & Mode 5 rendering
 *  + Custom 6bpp mode for Shining Force II
 ****************************************************************************************/

#ifndef _RENDER_H_
#define _RENDER_H_

/* 3:3:2 RGB / 5:5:5 RGB / 5:6:5 RGB / 8:8:8 RGB — оставляем как было */
#if defined(USE_8BPP_RENDERING)
#define PIXEL(r,g,b) (((r) << 5) | ((g) << 2) | (b))
#define GET_R(pixel) (((pixel) & 0xe0) >> 5)
#define GET_G(pixel) (((pixel) & 0x1c) >> 2)
#define GET_B(pixel) (((pixel) & 0x03) >> 0)

#elif defined(USE_15BPP_RENDERING)
#if defined(USE_ABGR)
#define PIXEL(r,g,b) ((1 << 15) | ((b) << 10) | ((g) << 5) | (r))
#define GET_B(pixel) (((pixel) & 0x7c00) >> 10)
#define GET_G(pixel) (((pixel) & 0x03e0) >> 5)
#define GET_R(pixel) (((pixel) & 0x001f) >> 0)
#else
#define PIXEL(r,g,b) ((1 << 15) | ((r) << 10) | ((g) << 5) | (b))
#define GET_R(pixel) (((pixel) & 0x7c00) >> 10)
#define GET_G(pixel) (((pixel) & 0x03e0) >> 5)
#define GET_B(pixel) (((pixel) & 0x001f) >> 0)
#endif

#elif defined(USE_16BPP_RENDERING)
#define PIXEL(r,g,b) (((r) << 11) | ((g) << 5) | (b))
#define GET_R(pixel) (((pixel) & 0xf800) >> 11)
#define GET_G(pixel) (((pixel) & 0x07e0) >> 5)
#define GET_B(pixel) (((pixel) & 0x001f) >> 0)

#elif defined(USE_32BPP_RENDERING)
#define PIXEL(r,g,b) ((0xff << 24) | ((r) << 16) | ((g) << 8) | (b))
#define GET_R(pixel) (((pixel) & 0xff0000) >> 16)
#define GET_G(pixel) (((pixel) & 0x00ff00) >> 8)
#define GET_B(pixel) (((pixel) & 0x0000ff) >> 0)
#endif

/* LCD ghosting filter */
#define RENDER_PIXEL_LCD(in,out,table,rate) \
{ \
  PIXEL_OUT_T pixel_out = table[*in++]; \
  PIXEL_OUT_T pixel_old  = *out; \
  uint8 r = GET_R(pixel_out); \
  uint8 g = GET_G(pixel_out); \
  uint8 b = GET_B(pixel_out); \
  int r_decay = GET_R(pixel_old) - r; \
  int g_decay = GET_G(pixel_old) - g; \
  int b_decay = GET_B(pixel_old) - b; \
  if (r_decay > 0) r += (rate * r_decay) >> 8; \
  if (g_decay > 0) g += (rate * g_decay) >> 8; \
  if (b_decay > 0) b += (rate * b_decay) >> 8; \
  *out++ = PIXEL(r,g,b); \
}

/* Global variables */
extern uint16 spr_col;

/* Function prototypes */
extern void render_init(void);
extern void render_reset(void);
extern void render_line(int line);
extern void blank_line(int line, int offset, int width);
extern void remap_line(int line);
extern void window_clip(unsigned int data, unsigned int sw);

/* ==================== ОРИГИНАЛЬНЫЕ РЕЖИМЫ (НУЖНЫ ДЛЯ СОВМЕСТИМОСТИ) ==================== */
extern void render_bg_m0(int line);
extern void render_bg_m1(int line);
extern void render_bg_m1x(int line);
extern void render_bg_m2(int line);
extern void render_bg_m3(int line);
extern void render_bg_m3x(int line);
extern void render_bg_inv(int line);
extern void render_bg_m4(int line);

extern void render_obj_tms(int line);           /* ← ДОБАВЛЕНО */
extern void render_obj_m4(int line);            /* ← ДОБАВЛЕНО */

extern void parse_satb_tms(int line);
extern void parse_satb_m4(int line);
extern void parse_satb_m5(int line);
extern void parse_satb_m5_im2(int line);

extern void update_bg_pattern_cache_m4(int index);   /* ← ДОБАВЛЕНО */

/* ==================== КАСТОМНЫЙ 6 BPP ДЛЯ SHINING FORCE II ==================== */
extern void render_bg_m5_sf2(int line);
extern void render_obj_m5_sf2(int line);
extern void update_bg_pattern_cache_m5_sf2(int index);

/* Старые Mode 5 функции (оставляем, чтобы не ломать другие игры) */
extern void render_bg_m5(int line);
extern void render_bg_m5_vs(int line);
extern void render_bg_m5_vs_enhanced(int line);
extern void render_bg_m5_im2(int line);
extern void render_bg_m5_im2_vs(int line);
extern void render_obj_m5(int line);
extern void render_obj_m5_ste(int line);
extern void render_obj_m5_im2(int line);
extern void render_obj_m5_im2_ste(int line);

/* Color update */
extern void color_update_m4(int index, unsigned int data);
extern void color_update_m5(int index, unsigned int data);

/* Function pointers */
extern void (*render_bg)(int line);
extern void (*render_obj)(int line);
extern void (*parse_satb)(int line);
extern void (*update_bg_pattern_cache)(int index);

#endif /* _RENDER_H_ */